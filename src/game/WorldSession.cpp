/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
 * Copyright (C) 2011-2016 Nostalrius <https://nostalrius.org>
 * Copyright (C) 2016-2017 Elysium Project <https://github.com/elysium-project>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/** \file
    \ingroup u2w
*/

#include "WorldSocket.h"                                    // must be first to make ACE happy with ACE includes in it
#include "Common.h"
#include "Database/DatabaseEnv.h"
#include "Log.h"
#include "Opcodes.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "Group.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "World.h"
#include "ObjectAccessor.h"
#include "BattleGroundMgr.h"
#include "MapManager.h"
#include "SocialMgr.h"

#include "PlayerBotMgr.h"
#include "Anticheat.hpp"
#include "Language.h"
#include "Auth/Sha1.h"
#include "ChannelMgr.h"
#include "Chat.h"
#include "Channel.h"
#include "AccountMgr.h"
#include "NodeSession.h"
#include "NodesOpcodes.h"
#include "MasterPlayer.h"
#include "PacketLog.hpp"

#include "custom/transmog.h"

#include <string>

// select opcodes appropriate for processing in Map::Update context for current session state
static bool MapSessionFilterHelper(WorldSession* session, OpcodeHandler const& opHandle)
{
    // we do not process not logged in player packets
    Player * plr = session->GetPlayer();
    if (!plr)
        return false;

    // in Map::Update() we do not process packets where player is not in world!
    return plr->IsInWorld();
}


bool MapSessionFilter::Process(WorldPacket * packet)
{
    OpcodeHandler const& opHandle = opcodeTable[packet->GetOpcode()];
    // let's check if our opcode can be really processed in Map::Update()
    return MapSessionFilterHelper(m_pSession, opHandle);
}

/// WorldSession constructor
WorldSession::WorldSession(uint32 id, WorldSocket *sock, AccountTypes sec, time_t mute_time, LocaleConstant locale, const std::string &local_ip, const std::string& remote_ip) :
    m_muteTime(mute_time), m_localIp(local_ip),
    _pcktReading(nullptr), _pcktWriting(nullptr), _pcktRecvDump(nullptr), _pcktDumpFlags(0), _pcktReadSpeedRate(1.0f),
    _pcktReadTimer(0), _pcktReadLastUpdate(0), m_connected(true), m_disconnectTimer(0), m_who_recvd(false),
    m_ah_list_recvd(false), _scheduleBanLevel(0),
    _accountFlags(0), m_idleTime(WorldTimer::getMSTime()), _player(nullptr), m_Socket(sock), _security(sec), _accountId(id), _logoutTime(0), m_inQueue(false),
    m_playerLoading(false), m_playerLogout(false), m_playerRecentlyLogout(false), m_playerSave(false), m_sessionDbcLocale(sWorld.GetAvailableDbcLocale(locale)),
    m_sessionDbLocaleIndex(sObjectMgr.GetIndexForLocale(locale)), m_latency(0), m_tutorialState(TUTORIALDATA_UNCHANGED),
    m_bot(nullptr), m_lastReceivedPacketTime(0), _clientOS(CLIENT_OS_UNKNOWN), _gameBuild(0), _orderCounter(0),
    _charactersCount(10), _characterMaxLevel(0), m_masterSession(nullptr), m_nodeSession(nullptr), m_masterPlayer(nullptr),
    _lastAnticheatUpdate(0), _anticheat(nullptr)
{
    if (sock)
    {
        m_Address = remote_ip;
        sock->AddReference();
    }
    else
        m_Address = "<BOT>";

    m_ActivityDays = 0;
    m_LastBan = 0;
    m_LastClaim = 0;
    m_LoyaltyEvents.resize((uint32)LoyaltyEvent::Max, 0);

    for (uint32 i = 0; i < 835; ++i)
    {
        _extraFloodPacketsOptions[i][0] = 0;
        _extraFloodPacketsOptions[i][1] = 0;
    }
}

/// WorldSession destructor
WorldSession::~WorldSession()
{
    ///- unload player if not unloaded
    if (_player)
        LogoutPlayer(true);

    /// - If have unclosed socket, close it
    if (m_Socket)
    {
        m_Socket->CloseSocket();
        m_Socket->RemoveReference();
        m_Socket = nullptr;
    }

    ///- empty incoming packet queue
    WorldPacket* packet = nullptr;
    for (int i = 0; i < PACKET_PROCESS_MAX_TYPE; ++i)
        while (_recvQueue[i].next(packet))
            delete packet;
    SetDumpPacket(nullptr);
    SetReadPacket(nullptr);
    SetDumpRecvPackets(nullptr);
}

void WorldSession::SizeError(WorldPacket const& packet, uint32 size) const
{
    sLog.outError("Client (account %u) send packet %s (%u) with size " SIZEFMTD " but expected %u (attempt crash server?), skipped",
                  GetAccountId(), LookupOpcodeName(packet.GetOpcode()), packet.GetOpcode(), packet.size(), size);
}

/// Get the player name
char const* WorldSession::GetPlayerName() const
{
    return GetPlayer() ? GetPlayer()->GetName() : "<none>";
}

/// Send a packet to the client
void WorldSession::SendPacket(WorldPacket const* packet)
{
    // There is a maximum size packet.
    if (packet->size() > 0x8000)
    {
        // Packet will be rejected by client
        sLog.outInfo("[NETWORK] Packet %s size %u is too large. Not sent [Account %u Player %s]", LookupOpcodeName(packet->GetOpcode()), packet->size(), GetAccountId(), GetPlayerName());
        return;
    }
    if (!m_Socket && !m_masterSession)
    {
        if (packet->GetOpcode() == SMSG_MESSAGECHAT)
        {
            WorldPacket packet2(*packet);
            packet2.rpos(0);
            uint8 msgtype;
            uint32 lang;
            ObjectGuid guid1;
            std::string name1;
            packet2 >> msgtype >> lang;
            // Channels
            if (msgtype == CHAT_MSG_CHANNEL)
            {
                std::string chanName, message;
                uint32 unused;
                packet2 >> chanName >> unused >> guid1 >> unused;
                packet2 >> message;
                if (sObjectMgr.GetPlayerNameByGUID(guid1, name1))
                    _chatBotHistory << uint32(msgtype) << " " << name1 << " " << chanName << " " << message << std::endl;
                return;
            }
            ObjectGuid guid2;
            uint32 textLen;
            std::string message;
            uint8 chatTag;
            packet2 >> guid1;
            if (msgtype == CHAT_MSG_SAY || msgtype == CHAT_MSG_YELL || msgtype == CHAT_MSG_PARTY)
                packet2 >> guid2;
            packet2 >> textLen >> message >> chatTag;
            if (guid1.IsEmpty() || sObjectMgr.GetPlayerNameByGUID(guid1, name1))
                _chatBotHistory << uint32(msgtype) << " " << name1 << " NULL " << message << std::endl;
        }
        return;
    }

#ifdef _DEBUG

    // Code for network use statistic
    static uint64 sendPacketCount = 0;
    static uint64 sendPacketBytes = 0;

    static time_t firstTime = time(nullptr);
    static time_t lastTime = firstTime;                     // next 60 secs start time

    static uint64 sendLastPacketCount = 0;
    static uint64 sendLastPacketBytes = 0;

    time_t cur_time = time(nullptr);

    if ((cur_time - lastTime) < 60)
    {
        sendPacketCount += 1;
        sendPacketBytes += packet->size();

        sendLastPacketCount += 1;
        sendLastPacketBytes += packet->size();
    }
    else
    {
        uint64 minTime = uint64(cur_time - lastTime);
        uint64 fullTime = uint64(lastTime - firstTime);
        DETAIL_LOG("Send all time packets count: " UI64FMTD " bytes: " UI64FMTD " avr.count/sec: %f avr.bytes/sec: %f time: %u", sendPacketCount, sendPacketBytes, float(sendPacketCount) / fullTime, float(sendPacketBytes) / fullTime, uint32(fullTime));
        DETAIL_LOG("Send last min packets count: " UI64FMTD " bytes: " UI64FMTD " avr.count/sec: %f avr.bytes/sec: %f", sendLastPacketCount, sendLastPacketBytes, float(sendLastPacketCount) / minTime, float(sendLastPacketBytes) / minTime);

        lastTime = cur_time;
        sendLastPacketCount = 1;
        sendLastPacketBytes = packet->wpos();               // wpos is real written size
    }

#endif                                                  // !_DEBUG

    //sLog.outString("[%s]Send packet : %u|0x%x (%s)", GetPlayerName(), packet->GetOpcode(), packet->GetOpcode(), LookupOpcodeName(packet->GetOpcode()));
    if (Player* player = GetPlayer())
        DEBUG_UNIT_IF(packet->GetOpcode() != SMSG_MESSAGECHAT && packet->GetOpcode() != SMSG_WARDEN_DATA, player,
            DEBUG_PACKETS_SEND, "[%s] Send packet : %u/0x%x (%s)", player->GetName(), packet->GetOpcode(), packet->GetOpcode(), LookupOpcodeName(packet->GetOpcode()));


    if (m_masterSession)
    {
        m_masterSession->SendPacketToGameClient(GetAccountId(), packet);
        return;
    }

    if (m_Socket->SendPacket(*packet) == -1)
        m_Socket->CloseSocket();

    // Log du paquet
    if (_pcktWriting)
    {
        std::stringstream oss;
        oss << WorldTimer::getMSTime() << ":" << packet->GetOpcode() << ":" << packet->size() << "|";
        for (size_t i = 0; i < packet->size(); ++i)
            oss << uint32(packet->read<uint8>(i)) << " ";
        oss << "256\n";
        fprintf(_pcktWriting, oss.str().c_str());
    }
}

/// Add an incoming packet to the queue
void WorldSession::QueuePacket(WorldPacket* newPacket, NodeSession* from_node)
{
    OpcodeHandler const& opHandle = opcodeTable[newPacket->GetOpcode()];
    if (opHandle.packetProcessing >= PACKET_PROCESS_MAX_TYPE)
    {
        sLog.outError("SESSION: opcode %s (0x%.4X) will be skipped",
                      LookupOpcodeName(newPacket->GetOpcode()),
                      newPacket->GetOpcode());
        return;
    }
    m_lastReceivedPacketTime = newPacket->GetPacketTime();

    if (m_nodeSession && m_nodeSession != from_node && sNodesOpcodes->IsOpcodeForwardedToNode(newPacket->GetOpcode()))
    {
        m_nodeSession->ForwardClientPacket(GetAccountId(), newPacket);
        delete newPacket;
        return;
    }
    uint32 processing = opHandle.packetProcessing;
    if (processing != PACKET_PROCESS_WORLD && processing != PACKET_PROCESS_DB_QUERY)
        if (!IsNode() && GetMasterPlayer() && sNodesOpcodes->IsOpcodeHandledByMaster(newPacket->GetOpcode()))
            processing = PACKET_PROCESS_MASTER_SAFE;

    _recvQueue[processing].add(newPacket);
}

/// Logging helper for unexpected opcodes
void WorldSession::LogUnexpectedOpcode(WorldPacket* packet, const char *reason)
{
    DEBUG_LOG("SESSION: received unexpected opcode %s (0x%.4X) %s",
                  LookupOpcodeName(packet->GetOpcode()),
                  packet->GetOpcode(),
                  reason);
}

/// Logging helper for unexpected opcodes
void WorldSession::LogUnprocessedTail(WorldPacket *packet)
{
    sLog.outError("SESSION: opcode %s (0x%.4X) have unprocessed tail data (read stop at " SIZEFMTD " from " SIZEFMTD ")",
                  LookupOpcodeName(packet->GetOpcode()),
                  packet->GetOpcode(),
                  packet->rpos(), packet->wpos());
}

bool WorldSession::ForcePlayerLogoutDelay()
{
    if (!sWorld.IsStopped() && GetPlayer() && (GetPlayer()->IsBeingTeleportedFar() || GetPlayer()->FindMap() && GetPlayer()->IsInWorld()) && sPlayerBotMgr.ForceLogoutDelay())
    {
        sLog.out(LOG_CHAR, "Account: %d (IP: %s) Lost socket for character:[%s] (guid: %u)", GetAccountId(), GetRemoteAddress().c_str(), _player->GetName() , _player->GetGUIDLow());
        sWorld.LogCharacter(GetPlayer(), "LostSocket");
        GetPlayer()->OnDisconnected();
        SetDisconnectedSession();
        m_disconnectTimer = 120000;
        return true;
    }
    return false;
}

/// Update the WorldSession (triggered by World update)
bool WorldSession::Update(PacketFilter& updater)
{
    uint32 sessionUpdateTime = WorldTimer::getMSTime();
    for (int i = 0; i < FLOOD_MAX_OPCODES_TYPE; ++i)
        _floodPacketsCount[i] = 0;

    ///- Retrieve packets from the receive queue and call the appropriate handlers
    ProcessPackets(updater);

    if(CharacterScreenIdleKick(sessionUpdateTime))
        return false;

    sessionUpdateTime = WorldTimer::getMSTimeDiffToNow(sessionUpdateTime);

    if (sWorld.getConfig(CONFIG_UINT32_PERFLOG_SLOW_UNIQUE_SESSION_UPDATE) && sessionUpdateTime > sWorld.getConfig(CONFIG_UINT32_PERFLOG_SLOW_UNIQUE_SESSION_UPDATE))
        sLog.out(LOG_PERFORMANCE, "Slow session update: %ums. Account %u on IP %s", sessionUpdateTime, GetAccountId(), GetRemoteAddress().c_str());

    if (m_masterSession)
        return true;

    if (m_Socket && !m_Socket->IsClosed() && _anticheat)
    {
        auto const now = WorldTimer::getMSTime();
        _anticheat->Update(WorldTimer::getMSTimeDiff(_lastAnticheatUpdate, now));
        _lastAnticheatUpdate = now;
    }

    //check if we are safe to proceed with logout
    //logout procedure should happen only in World::UpdateSessions() method!!!
    if (updater.ProcessLogout())
    {
        if (m_bot != nullptr && m_bot->state == PB_STATE_OFFLINE)
        {
            LogoutPlayer(true);
            return false;
        }

        ///- Cleanup socket pointer if need
        if (m_Socket && m_Socket->IsClosed())
        {
            m_Socket->RemoveReference();
            m_Socket = nullptr;

            // Character stays IG for 2 minutes
            return ForcePlayerLogoutDelay();
        }

        ///- If necessary, log the player out
        time_t currTime = time(nullptr);
        bool forceConnection = sPlayerBotMgr.ForceAccountConnection(this);
        if (sWorld.IsStopped())
            forceConnection = false;
        if ((!m_Socket || (ShouldLogOut(currTime) && !m_playerLoading)) && !forceConnection && m_bot == nullptr)
            LogoutPlayer(true);

        if (!m_Socket && !forceConnection && this->m_bot == nullptr)
            return false;                                       //Will remove this session from the world session map
    }
    else // Async map based update
    {
        if (GetMasterPlayer() && GetPlayer())
        {
            GetMasterPlayer()->LoadPlayer(GetPlayer());
            GetMasterPlayer()->Update();
        }
        // else
        // TODO: Broadcast MasterPlayer update to Master
    }

    if (_pcktReading)
    {
        while (true)
        {
            long int pos = ftell(_pcktReading);
            uint32 nextTime = 0;
            fscanf(_pcktReading, "%u", &nextTime);
            if (!nextTime)
            {
                SetReadPacket(nullptr);
                break;
            }
            fseek(_pcktReading, pos, SEEK_SET);
            uint32 now = WorldTimer::tickTime();
            uint32 diff = WorldTimer::getMSTimeDiff(_pcktReadLastUpdate, now);
            _pcktReadLastUpdate = now;
            _pcktReadTimer += diff * _pcktReadSpeedRate;
            if (nextTime > _pcktReadTimer) // Stop
                break;
            // Sinon on envoie encore un paquet.
            uint32 size = 0;
            uint32 opcode = 0;
            int32 readValue = 0;
            bool errorWhileReading = false;
            if (fscanf(_pcktReading, "%u:%u:%u|%u", &nextTime, &opcode, &size, &readValue) != 4)
                errorWhileReading = true;
            else
            {
                WorldPacket data(opcode, size);
                while (true)
                {
                    if (data.size() >= size && readValue != 256)
                    {
                        if (_player)
                            ChatHandler(_player).PSendSysMessage("[Replay] Invalid packet size [opcode %s|size %u|time %u]", LookupOpcodeName(opcode), size, nextTime);
                        errorWhileReading = true;
                        break;
                    }
                    if (readValue == 256)
                        break;
                    data << uint8(readValue);
                    int readCount = fscanf(_pcktReading, " %u", &readValue);
                    if (!readCount)
                    {
                        if (_player)
                            ChatHandler(_player).PSendSysMessage("[Replay] Invalid packet (truncated) [opcode %s|size %u|time %u]", LookupOpcodeName(opcode), size, nextTime);
                        errorWhileReading = true;
                        break;
                    }
                }
                if (!errorWhileReading)
                {
                    SendPacket(&data);
                    fscanf(_pcktReading, "\n");
                }
            }
            // Got an error
            if (errorWhileReading)
            {
                SetReadPacket(nullptr);
                break;
            }
        }
    }
    return true;
}

bool WorldSession::CanProcessPackets() const
{
    if (GetMasterSession())
        return true;
    return ((m_Socket && !m_Socket->IsClosed()) || (_player && sPlayerBotMgr.IsChatBot(_player->GetGUIDLow())));
}

void WorldSession::ProcessPackets(PacketFilter& updater)
{
    WorldPacket* packet = nullptr;
    _receivedPacketType[updater.PacketProcessType()] = false;
    while (CanProcessPackets() && _recvQueue[updater.PacketProcessType()].next(packet, updater))
    {
        if (_packetLog)
        {
            if (auto const wpos = packet->wpos())
                _packetLog->Push(packet->GetOpcode(), packet->contents(), wpos);
            else
                _packetLog->Push(packet->GetOpcode(), nullptr, 0);
        }

        _receivedPacketType[updater.PacketProcessType()] = true;
        if (!AllowPacket(packet->GetOpcode()))
            break;

        if (!AdditionalAllowPacket(packet->GetOpcode()))
            break;

        // Reading packets
        if (_pcktReading)
        {
            switch (packet->GetOpcode())
            {
                case CMSG_MESSAGECHAT:
                case MSG_MOVE_STOP:
                case MSG_MOVE_HEARTBEAT:
                case CMSG_ITEM_TEXT_QUERY:
                case CMSG_ITEM_NAME_QUERY:
                case CMSG_NAME_QUERY:
                case CMSG_PET_NAME_QUERY:
                case CMSG_ITEM_QUERY_SINGLE:
                case CMSG_ITEM_QUERY_MULTIPLE:
                    // Allow chat packets for GM commands (speed modification for example)
                    // Allow movement packets to have exact position for "gm fly on" command
                    break;
                default:
                    // Otherwise we simply ignore
                    delete packet;
                    continue;
            }
        }
        ALL_SESSION_SCRIPTS(this, OnPacket(packet->GetOpcode()));
        OpcodeHandler const& opHandle = opcodeTable[packet->GetOpcode()];
        try
        {
            if (!IsNode() && GetMasterPlayer() && sNodesOpcodes->IsOpcodeHandledByMaster(packet->GetOpcode()))
            {
                ExecuteOpcode(opHandle, packet);
                delete packet;
                continue;
            }
            uint32 packetTime = WorldTimer::getMSTime();
            switch (opHandle.status)
            {
                case STATUS_LOGGEDIN:

                    if (!_player)
                    {
                        // skip STATUS_LOGGEDIN opcode unexpected errors if player logout sometime ago - this can be network lag delayed packets
                        if (!m_playerRecentlyLogout)
                            LogUnexpectedOpcode(packet, "the player has not logged in yet");
                    }
                    else if (_player->IsInWorld())
                        ExecuteOpcode(opHandle, packet);

                    // lag can cause STATUS_LOGGEDIN opcodes to arrive after the player started a transfer
                    break;
                case STATUS_LOGGEDIN_OR_RECENTLY_LOGGEDOUT:
                    if (!_player && !m_playerRecentlyLogout)
                        LogUnexpectedOpcode(packet, "the player has not logged in yet and not recently logout");
                    else
                        // not expected _player or must checked in packet hanlder
                        ExecuteOpcode(opHandle, packet);
                    break;
                case STATUS_TRANSFER:
                    if (!_player)
                        LogUnexpectedOpcode(packet, "the player has not logged in yet");
                    else if (_player->IsInWorld())
                        LogUnexpectedOpcode(packet, "the player is still in world");
                    else
                        ExecuteOpcode(opHandle, packet);
                    break;
                case STATUS_AUTHED:
                    // prevent cheating with skip queue wait
                    if (m_inQueue)
                    {
                        LogUnexpectedOpcode(packet, "the player not pass queue yet");
                        break;
                    }

                    // single from authed time opcodes send in to after logout time
                    // and before other STATUS_LOGGEDIN_OR_RECENTLY_LOGGOUT opcodes.
                    m_playerRecentlyLogout = false;

                    ExecuteOpcode(opHandle, packet);
                    break;
                case STATUS_NEVER:
                    sLog.outError("SESSION: received not allowed opcode %s (0x%.4X)",
                                  opHandle.name,
                                  packet->GetOpcode());
                    break;
                case STATUS_UNHANDLED:
                    DEBUG_LOG("SESSION: received not handled opcode %s (0x%.4X)",
                              opHandle.name,
                              packet->GetOpcode());
                    break;
                default:
                    sLog.outError("SESSION: received wrong-status-req opcode %s (0x%.4X)",
                                  opHandle.name,
                                  packet->GetOpcode());
                    break;
            }
            packetTime = WorldTimer::getMSTimeDiffToNow(packetTime);
            if (sWorld.getConfig(CONFIG_UINT32_PERFLOG_SLOW_PACKET) && packetTime > sWorld.getConfig(CONFIG_UINT32_PERFLOG_SLOW_PACKET))
                sLog.out(LOG_PERFORMANCE, "Slow packet opcode %s: %ums. Account %u on IP %s", opHandle.name, packetTime, GetAccountId(), GetRemoteAddress().c_str());
        }
        catch (ForwardToMaster_Exception& )
        {
            ASSERT(GetMasterSession());
            GetMasterSession()->ForwardClientPacket(GetAccountId(), packet);
        }
        catch (ForwardToNode_Exception& )
        {
            ASSERT(GetNodeSession());
            GetMasterSession()->ForwardClientPacket(GetAccountId(), packet);
        }
        catch (ByteBufferException &)
        {
            sLog.outError("WorldSession::Update ByteBufferException occured while parsing a packet (opcode:0x%x) from client %s, accountid=%i.",
                          packet->GetOpcode(), GetRemoteAddress().c_str(), GetAccountId());
            if (sLog.HasLogLevelOrHigher(LOG_LVL_DEBUG))
            {
                DEBUG_LOG("Dumping error causing packet:");
                packet->hexlike();
            }

            if (sWorld.getConfig(CONFIG_BOOL_KICK_PLAYER_ON_BAD_PACKET))
            {
                DETAIL_LOG("Disconnecting session [account id %u / address %s] for badly formatted packet.",
                           GetAccountId(), GetRemoteAddress().c_str());
                _anticheat->RecordCheat(CHEAT_ACTION_INFO_LOG, "Anticrash", "ByteBufferException");
                KickPlayer();
            }
        }
        catch (std::runtime_error &e)
        {
            sLog.outInfo("CATCH Exception 'ASSERT' for account %u / IP %s", GetAccountId(), GetRemoteAddress().c_str());
            sLog.outInfo(e.what());
            _anticheat->RecordCheat(CHEAT_ACTION_KICK, "Anticrash", "ASSERT failed");
            KickPlayer();
        }
        catch (...)
        {
            sLog.outInfo("CATCH Unknown exception. Account %u / IP %s", GetAccountId(), GetRemoteAddress().c_str());
            _anticheat->RecordCheat(CHEAT_ACTION_KICK, "Anticrash", "Exception raised");
            KickPlayer();
        }
        delete packet;
    }
}

void WorldSession::SetPacketLogging(bool value)
{
    if (!value)
    {
        _packetLog.reset();
        SetAccountFlags(GetAccountFlags() & ~ACCOUNT_FLAG_PACKETLOG);
    }
    else
    {
        SetAccountFlags(GetAccountFlags() | ACCOUNT_FLAG_PACKETLOG);
        _packetLog.reset(new PacketLog(this));
    }
}

void WorldSession::ClearIncomingPacketsByType(PacketProcessing type)
{
    ASSERT(type < PACKET_PROCESS_MAX_TYPE);
    WorldPacket* data = nullptr;
    while (_recvQueue[type].next(data))
        delete data;
}

void WorldSession::SetBot(PlayerBotEntry* b)
{
    m_bot = b;
    _anticheat.reset(new NullSessionAnticheat(this));
}

void WorldSession::SetDisconnectedSession()
{
    m_connected = false;
    _anticheat->Disconnect();
    sWorld.SetSessionDisconnected(this);
}

bool WorldSession::UpdateDisconnected(uint32 diff)
{
    ASSERT(!m_connected);
    if (!_player || !(_player->IsInWorld() || !_player->FindMap()) && !_player->IsBeingTeleportedFar())
        return false;
    if (m_disconnectTimer < diff)
        return false; // Delete this session
    m_disconnectTimer -= diff;
    return true;
}

/// %Log the player out
void WorldSession::LogoutPlayer(bool Save)
{
    // finish pending transfers before starting the logout
    /* while(_player && _player->IsBeingTeleportedFar())
        HandleMoveWorldportAckOpcode(); */

    m_idleTime = WorldTimer::getMSTime();
    m_playerLogout = true;
    m_playerSave = Save;
    bool doBanPlayer = false;

    if (_player)
    {
        bool inWorld = _player->IsInWorld() && _player->FindMap();

        if (!(GetAccountFlags() & ACCOUNT_FLAG_HIDDEN))
        {
            sLog.out(LOG_CHAR, "Account: %d (IP: %s) Logout Character:[%s] (guid: %u)", GetAccountId(), GetRemoteAddress().c_str(), _player->GetName() , _player->GetGUIDLow());
            sWorld.LogCharacter(_player, "Logout");
        }
        if (ObjectGuid lootGuid = GetPlayer()->GetLootGuid())
            DoLootRelease(lootGuid);

        ///- If the player just died before logging out, make him appear as a ghost
        if (inWorld && _player->GetDeathTimer())
        {
            _player->getHostileRefManager().deleteReferences();
            _player->BuildPlayerRepop();
            _player->RepopAtGraveyard();
        }
        else if (inWorld && _player->isInCombat())
        {
            _player->CombatStop();
            _player->getHostileRefManager().setOnlineOfflineState(false);
        }
        else if (inWorld && _player->HasAuraType(SPELL_AURA_SPIRIT_OF_REDEMPTION))
        {
            // this will kill character by SPELL_AURA_SPIRIT_OF_REDEMPTION
            _player->RemoveSpellsCausingAura(SPELL_AURA_MOD_SHAPESHIFT);
            //_player->SetDeathPvP(*); set at SPELL_AURA_SPIRIT_OF_REDEMPTION apply time
            _player->KillPlayer();
            _player->BuildPlayerRepop();
            _player->RepopAtGraveyard();
        }
        //drop a flag if player is carrying it
        if (BattleGround *bg = _player->GetBattleGround())
            _player->LeaveBattleground(true);

        ///- Teleport to home if the player is in an invalid instance
        if (!_player->m_InstanceValid && !_player->isGameMaster())
        {
            _player->TeleportToHomebind();
            //this is a bad place to call for far teleport because we need player to be in world for successful logout
            //maybe we should implement delayed far teleport logout?
            sMapMgr.ExecuteSingleDelayedTeleport(_player);
        }

        // FG: finish pending transfers after starting the logout
        // this should fix players being able to logout and login back with full hp at death position
        while (_player->IsBeingTeleportedFar())
        {
            HandleMoveWorldportAckOpcode();
            sMapMgr.ExecuteSingleDelayedTeleport(_player); // Execute chain teleport if there are some
        }

        // Refresh apres ca
        inWorld = _player->IsInWorld() && _player->FindMap();
        if (!inWorld)
        {
            Save = false;
            sLog.outInfo("[CRASH] Joueur %s pas dans le monde a la deco.", _player->GetName());
        }
        else if (ShouldBeBanned(_player->getLevel()))
            doBanPlayer = true;

        sBattleGroundMgr.RemovePlayerFromQueues(_player, true);

        ///- Reset the online field in the account table
        // no point resetting online in character table here as Player::SaveToDB() will set it to 1 since player has not been removed from world at this stage
        // No SQL injection as AccountID is uint32
        static SqlStatementID id;

        SqlStatement stmt = LoginDatabase.CreateStatement(id, "UPDATE account SET current_realm = ?, online = 0 WHERE id = ?");
        stmt.PExecute(uint32(0), GetAccountId());

        ///- If the player is in a guild, update the guild roster and broadcast a logout message to other guild members
        if (Guild* guild = sGuildMgr.GetGuildById(_player->GetGuildId()))
        {
            if (MemberSlot* slot = guild->GetMemberSlot(_player->GetObjectGuid()))
            {
                slot->SetMemberStats(_player);
                slot->UpdateLogoutTime();
            }

            guild->BroadcastEvent(GE_SIGNED_OFF, _player->GetObjectGuid(), _player->GetName());
        }

        ///- Remove pet
        _player->RemovePet(PET_SAVE_AS_CURRENT);

        // Dungeon anti-exploit. Should be before save
        bool removedFromMap = false;
        if (Map* map = _player->FindMap())
        {
            if (map->IsNonRaidDungeon() && _player->GetGroup())
            {
                AreaTrigger const* at = sObjectMgr.GetGoBackTrigger(map->GetId());
                if (at)
                    removedFromMap = _player->TeleportTo(at->target_mapId, at->target_X, at->target_Y, at->target_Z, _player->GetOrientation());
                else
                    removedFromMap = _player->TeleportToHomebind();

                sMapMgr.ExecuteSingleDelayedTeleport(_player);
            }
        }

        ///- empty buyback items and save the player in the database
        // some save parts only correctly work in case player present in map/player_lists (pets, etc)
        if (Save)
        {
            if (inWorld && sWorld.getConfig(CONFIG_BOOL_TRANSMOG_ENABLED))
                sTransmog.LoadTransmog(_player, true);

            _player->SaveToDB(false, removedFromMap);
        }

        ///- Leave all channels before player delete...
        _player->CleanupChannels();

        ///- If the player is in a group (or invited), remove him. If the group if then only 1 person, disband the group.
        _player->UninviteFromGroup();

        // remove player from the group if he is:
        // a) in group; b) not in raid group; c) logging out normally (not being kicked or disconnected)
        if (_player->GetGroup() && !_player->GetGroup()->isRaidGroup() && m_Socket)
            _player->RemoveFromGroup();

        ///- Send update to group
        if (Group* group = _player->GetGroup())
            group->UpdatePlayerOnlineStatus(_player, false);

        sScriptMgr.OnPlayerLogout(_player);

        ///- Remove the player from the world
        // the player may not be in the world when logging out
        // e.g if he got disconnected during a transfer to another map
        // calls to GetMap in this case may cause crashes

        if (inWorld && !removedFromMap)
        {
            Map* _map = _player->GetMap();
            _map->Remove(_player, true);
        }
        else
        {
            _player->CleanupsBeforeDelete();
            Map::DeleteFromWorld(_player);
        }

        if (GetMasterSession())
            GetMasterSession()->SendPacket(NMSG_LOGOUT_COMPLETE, GetAccountId());

        ///- Send the 'logout complete' packet to the client
        WorldPacket data(SMSG_LOGOUT_COMPLETE, 0);
        SendPacket(&data);

        DEBUG_LOG("SESSION: Sent SMSG_LOGOUT_COMPLETE Message");
    }

    if (m_masterPlayer)
    {
        ///- Broadcast a logout message to the player's friends
		sSocialMgr.SendFriendStatus(m_masterPlayer, FRIEND_OFFLINE, m_masterPlayer->GetObjectGuid(), true);
		sSocialMgr.RemovePlayerSocial(m_masterPlayer->GetGUIDLow());

        m_masterPlayer->SaveToDB();
		MasterPlayer* mPlayer = m_masterPlayer;
        m_masterPlayer = nullptr;
		MangosMemoryBarrier();
        delete mPlayer;
    }

    m_playerLogout = false;
    m_playerSave = false;
    m_playerRecentlyLogout = true;
    LogoutRequest(0);

    if (doBanPlayer)
        sWorld.BanAccount(BAN_ACCOUNT, GetUsername(), 0, _scheduleBanReason, "");
}

/// Kick a player out of the World
void WorldSession::KickPlayer()
{
    if (m_Socket)
        m_Socket->CloseSocket();
}

/// Cancel channeling handler

void WorldSession::SendAreaTriggerMessage(const char* Text, ...)
{
    va_list ap;
    char szStr [1024];
    va_start(ap, Text);
    vsnprintf(szStr, sizeof(szStr), Text, ap);
    va_end(ap);

    uint32 length = strlen(szStr) + 1;
    WorldPacket data(SMSG_AREA_TRIGGER_MESSAGE, 4 + length);
    data << length;
    data << szStr;
    SendPacket(&data);
}

void WorldSession::SendNotification(const char *format, ...)
{
    if (format)
    {
        va_list ap;
        char szStr [1024];
        va_start(ap, format);
        vsnprintf(szStr, sizeof(szStr), format, ap);
        va_end(ap);

        WorldPacket data(SMSG_NOTIFICATION, (strlen(szStr) + 1));
        data << szStr;
        SendPacket(&data);
    }
}

void WorldSession::SendNotification(int32 string_id, ...)
{
    char const* format = GetMangosString(string_id);
    if (format)
    {
        va_list ap;
        char szStr [1024];
        va_start(ap, string_id);
        vsnprintf(szStr, sizeof(szStr), format, ap);
        va_end(ap);

        WorldPacket data(SMSG_NOTIFICATION, (strlen(szStr) + 1));
        data << szStr;
        SendPacket(&data);
    }
}

const char * WorldSession::GetMangosString(int32 entry) const
{
    return sObjectMgr.GetMangosString(entry, GetSessionDbLocaleIndex());
}

void WorldSession::Handle_NULL(WorldPacket& recvPacket)
{
    sLog.outError("SESSION: received unimplemented opcode %s (0x%.4X)",
                  LookupOpcodeName(recvPacket.GetOpcode()),
                  recvPacket.GetOpcode());
}

void WorldSession::Handle_EarlyProccess(WorldPacket& recvPacket)
{
    sLog.outError("SESSION: received opcode %s (0x%.4X) that must be processed in WorldSocket::OnRead",
                  LookupOpcodeName(recvPacket.GetOpcode()),
                  recvPacket.GetOpcode());
}

void WorldSession::Handle_ServerSide(WorldPacket& recvPacket)
{
    sLog.outError("SESSION: received server-side opcode %s (0x%.4X)",
                  LookupOpcodeName(recvPacket.GetOpcode()),
                  recvPacket.GetOpcode());
}

void WorldSession::Handle_Deprecated(WorldPacket& recvPacket)
{
    sLog.outError("SESSION: received deprecated opcode %s (0x%.4X)",
                  LookupOpcodeName(recvPacket.GetOpcode()),
                  recvPacket.GetOpcode());
}

void WorldSession::SendAuthWaitQue(uint32 position)
{
    if (position == 0)
    {
        WorldPacket packet(SMSG_AUTH_RESPONSE, 1);
        packet << uint8(AUTH_OK);
        SendPacket(&packet);
    }
    else
    {
        WorldPacket packet(SMSG_AUTH_RESPONSE, 5);
        packet << uint8(AUTH_WAIT_QUEUE);
        packet << uint32(position);
        SendPacket(&packet);
    }
}

void WorldSession::LoadLoyaltyData()
{
    QueryResult* l_Activity = LoginDatabase.PQuery("SELECT CONCAT(WEEK(DATE), ' - ', DATE_FORMAT(DATE, '%Y')) AS `week`, COUNT(DISTINCT(DATE_FORMAT(DATE, '%y - %m - %d'))) `countperweek` FROM account_log_ip WHERE accountid = %u AND source > 1 AND error = 0 GROUP BY CONCAT(WEEK(DATE), ' - ', DATE_FORMAT(DATE, '%y')) ORDER BY DATE", GetAccountId());

    if (l_Activity)
    {
        do
        {
            Field* l_Fields = l_Activity->Fetch();
            uint64 l_Days = l_Fields[1].GetUInt64();

            /// Loyalty points are based on week of activity, a week of activity is at least 3 day of activity in a single week or 7 days of activity
            m_ActivityDays += l_Days > 2 ? 7 : l_Days;
        } while (l_Activity->NextRow());
    }

    QueryResult* l_LastBanDate = LoginDatabase.PQuery("SELECT MAX(bandate) FROM account_banned WHERE id = %u", GetAccountId());
    if (l_LastBanDate)
        m_LastBan = l_LastBanDate->Fetch()[0].GetUInt32();

    if (QueryResult* l_AccountLoyalty = LoginDatabase.PQuery("SELECT LastClaim, LastEventReset FROM account_loyalty WHERE AccountID = %u", GetAccountId()))
    {
        Field* l_Fields = l_AccountLoyalty->Fetch();

        m_LastClaim = l_Fields[0].GetUInt32();
        m_LastEventReset = l_Fields[1].GetUInt32();

        time_t l_NowTime = time(nullptr);

        auto l_Time = localtime(&l_NowTime);
        struct tm l_Now = *l_Time;
        auto l_LastReset = localtime(&m_LastEventReset);

        /// If now is a different day than the last event reset day, then clear event history
        if (l_LastReset->tm_year != l_Now.tm_year || l_LastReset->tm_mday != l_Now.tm_mday || l_LastReset->tm_mon != l_Now.tm_mon)
        {
            m_LastEventReset = l_NowTime;

            LoginDatabase.PExecute("DELETE FROM account_loyalty_event WHERE AccountID = %u", GetAccountId());
            LoginDatabase.PExecute("REPLACE INTO account_loyalty(AccountID, LastClaim, LastEventReset) VALUES(%u,  %u, %u)", GetAccountId(), m_LastClaim, m_LastEventReset);
        }
        /// Load event history of the day
        else
        {

            if (QueryResult* l_Events = LoginDatabase.PQuery("SELECT Event, Count FROM account_loyalty_event WHERE AccountID = %u", GetAccountId()))
            {
                do
                {
                    Field* l_Fields = l_Events->Fetch();
                    uint32 l_Event = l_Fields[0].GetUInt32();
                    uint32 l_Count = l_Fields[1].GetUInt32();

                    /// Corrupted data ?
                    if (l_Event >= (uint32)LoyaltyEvent::Max)
                        continue;

                    m_LoyaltyEvents[l_Event] = l_Count;
                } while (l_Events->NextRow());
            }
        }
    }
    else
    {
        /// Insert default row
        m_LastEventReset = time(nullptr);
        LoginDatabase.PExecute("REPLACE INTO account_loyalty(AccountID, LastClaim, LastEventReset) VALUES(%u , %u, %u)", GetAccountId(), 0, m_LastEventReset);
    }
}

void WorldSession::AddLoyaltyPoints(uint32 p_Count, std::string p_Reason)
{
    if (!sWorld.getConfig(CONFIG_BOOL_WEB_DATABASE_ENABLED))
        return;

    WebDatabase.PExecute("INSERT INTO `bonus_log` (user_id, bonus, msg) VALUES (%u, %u, '%s')", GetAccountId(), p_Count, p_Reason.c_str());
    WebDatabase.PExecute("INSERT INTO bonus (id, silver, gold) VALUE (%u, %u, 0) ON DUPLICATE KEY UPDATE silver = silver + %u", GetAccountId(), p_Count, p_Count);

    ChatHandler(this).PSendSysMessage("You've earned %u Silver Elysium Coins! (%s)", p_Count, p_Reason.c_str());
}

void WorldSession::CompleteLoyaltyEvent(LoyaltyEvent p_Event)
{
    m_LoyaltyEvents[(uint32)p_Event]++;

    if (m_LoyaltyEvents[(uint32)p_Event] == g_LoyaltyEventObjectives[(uint32)p_Event])
    {
        uint32 l_RewardPoints = g_LoyaltyEventReward[(uint32)p_Event];

        /// loyalty event can give you max 7 points per day
        int32 l_AlreadyEarnPoints = 0;
        for (uint8 l_I = 0; l_I < (uint8)LoyaltyEvent::Max; l_I++)
        {
            if (m_LoyaltyEvents[l_I] == g_LoyaltyEventObjectives[l_I])
                l_AlreadyEarnPoints += g_LoyaltyEventReward[l_I];
        }

        if ((l_AlreadyEarnPoints + l_RewardPoints) > 5)
            l_RewardPoints = std::max(5 - l_AlreadyEarnPoints, 0);

        if (!l_RewardPoints)
            return;

        AddLoyaltyPoints(l_RewardPoints, "Loyalty Event " + std::to_string((uint32)p_Event));
    }

    LoginDatabase.PExecute("REPLACE INTO account_loyalty_event(AccountID, Event, Count) VALUES (%u, %u, %u)", GetAccountId(), (uint32)p_Event, m_LoyaltyEvents[(uint32)p_Event]);
}

void WorldSession::LoadTutorialsData()
{
    for (int aX = 0 ; aX < 8 ; ++aX)
        m_Tutorials[ aX ] = 0;

    QueryResult *result = CharacterDatabase.PQuery("SELECT tut0,tut1,tut2,tut3,tut4,tut5,tut6,tut7 FROM character_tutorial WHERE account = '%u'", GetAccountId());

    if (!result)
    {
        m_tutorialState = TUTORIALDATA_NEW;
        return;
    }

    do
    {
        Field *fields = result->Fetch();

        for (int iI = 0; iI < 8; ++iI)
            m_Tutorials[iI] = fields[iI].GetUInt32();
    }
    while (result->NextRow());

    delete result;

    m_tutorialState = TUTORIALDATA_UNCHANGED;
}

void WorldSession::SendTutorialsData()
{
    WorldPacket data(SMSG_TUTORIAL_FLAGS, 4 * 8);
    for (uint32 i = 0; i < 8; ++i)
        data << m_Tutorials[i];
    SendPacket(&data);
}

void WorldSession::SaveTutorialsData()
{
    static SqlStatementID updTutorial ;
    static SqlStatementID insTutorial ;

    switch (m_tutorialState)
    {
        case TUTORIALDATA_CHANGED:
        {
            SqlStatement stmt = CharacterDatabase.CreateStatement(updTutorial, "UPDATE character_tutorial SET tut0=?, tut1=?, tut2=?, tut3=?, tut4=?, tut5=?, tut6=?, tut7=? WHERE account = ?");
            for (int i = 0; i < ACCOUNT_TUTORIALS_COUNT; ++i)
                stmt.addUInt32(m_Tutorials[i]);

            stmt.addUInt32(GetAccountId());
            stmt.Execute();
        }
        break;

        case TUTORIALDATA_NEW:
        {
            SqlStatement stmt = CharacterDatabase.CreateStatement(insTutorial, "INSERT INTO character_tutorial (account,tut0,tut1,tut2,tut3,tut4,tut5,tut6,tut7) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");

            stmt.addUInt32(GetAccountId());
            for (int i = 0; i < ACCOUNT_TUTORIALS_COUNT; ++i)
                stmt.addUInt32(m_Tutorials[i]);

            stmt.Execute();
        }
        break;
        case TUTORIALDATA_UNCHANGED:
            break;
    }

    m_tutorialState = TUTORIALDATA_UNCHANGED;
}

void WorldSession::ExecuteOpcode(OpcodeHandler const& opHandle, WorldPacket* packet)
{
    // need prevent do internal far teleports in handlers because some handlers do lot steps
    // or call code that can do far teleports in some conditions unexpectedly for generic way work code
    if (_player)
        _player->SetCanDelayTeleport(true);


    //sLog.outString("[%s] Recvd packet : %u/0x%x (%s)", GetUsername().c_str(), packet->GetOpcode(), packet->GetOpcode(), LookupOpcodeName(packet->GetOpcode()));
    if (Player* player = GetPlayer())
        DEBUG_UNIT(player, DEBUG_PACKETS_RECV, "[%s] Recvd packet : %u/0x%x (%s)", player->GetName(), packet->GetOpcode(), packet->GetOpcode(), LookupOpcodeName(packet->GetOpcode()));
    if (_pcktRecvDump)
    {
        bool skipPacketAnalysis = false;
        if (_pcktDumpFlags & PACKET_DUMP_SKIP_FREQUENT_OPCODES)
        {
            switch (packet->GetOpcode())
            {
            case CMSG_QUESTGIVER_STATUS_QUERY:
            case CMSG_ITEM_QUERY_SINGLE:
            case CMSG_NAME_QUERY:
            case CMSG_SETSHEATHED:
            case CMSG_WARDEN_DATA:
            case CMSG_REQUEST_PARTY_MEMBER_STATS:
            case CMSG_GUILD_QUERY:
                skipPacketAnalysis = true;
                break;
            }
        }
        if (!skipPacketAnalysis)
        {
            fprintf(_pcktRecvDump, "%u:%s:%zu|", WorldTimer::getMSTime(), LookupOpcodeName(packet->GetOpcode()), packet->size());
            for (size_t i = 0; i < packet->size(); ++i)
                fprintf(_pcktRecvDump, "%u ", uint32(packet->read<uint8>(i)));
            fprintf(_pcktRecvDump, "256\n");
        }
    }
    (this->*opHandle.handler)(*packet);

    if (_player)
    {
        // can be not set in fact for login opcode, but this not create porblems.
        _player->SetCanDelayTeleport(false);

        //we should execute delayed teleports only for alive(!) players
        //because we don't want player's ghost teleported from graveyard
        if (_player->IsHasDelayedTeleport())
            _player->TeleportTo(_player->m_teleport_dest, _player->m_teleport_options);
    }
    if (packet->rpos() < packet->wpos() && sLog.HasLogLevelOrHigher(LOG_LVL_DEBUG))
        LogUnprocessedTail(packet);
}

void WorldSession::SetDumpPacket(const char* file)
{
    if (!file)
    {
        if (_pcktWriting)
            fclose(_pcktWriting);
        _pcktWriting = nullptr;
        return;
    }
    SetDumpPacket(nullptr); // Clean
    _pcktWriting = fopen(file, "w+");
    if (_pcktWriting)
    {
        fprintf(_pcktWriting, "BEGIN_TIME=%u\n", WorldTimer::getMSTime());
        fprintf(_pcktWriting, "RECORDER_LOWGUID=%u\n", _player ? _player->GetGUIDLow() : 0);
    }
}

void WorldSession::SetReadPacket(const char* file)
{
    if (!file)
    {
        if (_pcktReading)
            fclose(_pcktReading);
        _pcktReading = nullptr;
        return;
    }
    SetReadPacket(nullptr); // Clean
    _pcktReading = fopen(file, "r");
    if (_pcktReading)
    {
        uint32 fileTime = 0;
        uint32 recorderGuidLow = 0;
        if (!fscanf(_pcktReading, "BEGIN_TIME=%u\n", &fileTime))
        {
            fclose(_pcktReading);
            _pcktReading = nullptr;
            return;
        }
        _pcktReadTimer = fileTime;
        _pcktReadLastUpdate = WorldTimer::tickTime();
        if (fscanf(_pcktReading, "RECORDER_LOWGUID=%u\n", &recorderGuidLow))
            _recorderGuid = ObjectGuid(HIGHGUID_PLAYER, recorderGuidLow);
        else
            _recorderGuid = ObjectGuid();
    }
}

void WorldSession::SetDumpRecvPackets(const char* file)
{
    if (!file)
    {
        if (_pcktRecvDump)
            fclose(_pcktRecvDump);
        _pcktRecvDump = nullptr;
        return;
    }
    SetDumpRecvPackets(nullptr); // Clean
    _pcktRecvDump = fopen(file, "w+");
    if (_pcktRecvDump)
        fprintf(_pcktRecvDump, "#Begin packet dump on %s [account %s]\n", GetPlayerName(), GetUsername().c_str());
}

bool WorldSession::AllowPacket(uint16 opcode)
{
    // Do not count packets that are often spamed by the client when loading a zone for example.
    switch (opcode)
    {
        case CMSG_GAMEOBJECT_QUERY:
        case CMSG_CREATURE_QUERY:
        case CMSG_QUESTGIVER_STATUS_QUERY:
        case CMSG_ITEM_QUERY_SINGLE:
        case CMSG_NAME_QUERY:
        case CMSG_PET_NAME_QUERY:
        case CMSG_GUILD_QUERY:
        case CMSG_JOIN_CHANNEL:         // Can be flooded by addons upon login
        case CMSG_AUCTION_LIST_ITEMS:   // We already handle only one per session update
        case CMSG_WHO:                  // We already handle only one per session update
            return true;
        default:
            break;
    }

    _floodPacketsCount[FLOOD_TOTAL_PACKETS]++;

    switch (opcode)
    {
        case CMSG_CHAR_CREATE:
        case CMSG_CHAR_ENUM:
        case CMSG_CHAR_DELETE:
        case CMSG_OPEN_ITEM:
        case CMSG_PETITION_BUY:
        case CMSG_PETITION_SIGN:
        case CMSG_PETITION_QUERY:
        case MSG_PETITION_RENAME:
        case CMSG_SEND_MAIL:
        case CMSG_PLAYER_LOGIN:
            _floodPacketsCount[FLOOD_VERY_SLOW_OPCODES]++;
        // no break, since slow packets are also very slow packets.
        case CMSG_LOGOUT_REQUEST:
        case CMSG_ADD_FRIEND:
        case CMSG_DEL_FRIEND:
        case CMSG_BUY_ITEM:
        case CMSG_SELL_ITEM:
            _floodPacketsCount[FLOOD_SLOW_OPCODES]++;
        default:
            break;
    }

    // Check if the permitted threshold has been exceeded
    std::stringstream reason;
    if (_floodPacketsCount[FLOOD_VERY_SLOW_OPCODES] > 2)
        reason << _floodPacketsCount[FLOOD_VERY_SLOW_OPCODES] << " very slow packets";
    if (_floodPacketsCount[FLOOD_SLOW_OPCODES] > 8)
        reason << _floodPacketsCount[FLOOD_SLOW_OPCODES] << " slow packets";
    if (_floodPacketsCount[FLOOD_TOTAL_PACKETS] > 300)
        reason << _floodPacketsCount[FLOOD_TOTAL_PACKETS] << " packets";

    if (reason.str() != "")
    {
        reason << " (" << LookupOpcodeName(opcode) << ")";
        _anticheat->RecordCheat(CHEAT_ACTION_INFO_LOG| sWorld.getConfig(CONFIG_UINT32_ANTIFLOOD_SANCTION), "AntiFlood", reason.str().c_str());
        return false;
    }

    return true;
}

bool WorldSession::AdditionalAllowPacket(uint16 opcode)
{
    if (opcode != CMSG_GROUP_INVITE)
        return true;

    //if (!_extraFloodPacketsOptions[opcode][0] || !_extraFloodPacketsOptions[opcode][1])
    //    return true;

    if (_extraFloodPacketsOptions[opcode][0] < 7)
    {
        if (!_extraFloodPacketsOptions[opcode][1] || ((time(nullptr) - _extraFloodPacketsOptions[opcode][1]) > 1 * MINUTE))
        {
            _extraFloodPacketsOptions[opcode][0] = 0;
            _extraFloodPacketsOptions[opcode][1] = time(NULL);
        }

        ++_extraFloodPacketsOptions[opcode][0];
        return true;
    }
    else
    {
        if ((time(nullptr) - _extraFloodPacketsOptions[opcode][1]) > 1 * MINUTE)
        {
            _extraFloodPacketsOptions[opcode][0] = 1;
            _extraFloodPacketsOptions[opcode][1] = time(NULL);
            return true;
        }
    }
    return false;
}

void WorldSession::InitializeAnticheat(const BigNumber &K)
{
    _anticheat = std::move(sAnticheatLib->NewSession(this, K));
}

bool WorldSession::ShouldBeBanned(uint32 currentLevel) const
{
    return _scheduleBanReason.size() && urand(2, _scheduleBanLevel) <= currentLevel;
}

void WorldSession::LoginPlayerToNode(NodeSession* session)
{
    ASSERT(IsNode());
    ASSERT(IsMaster());
    ASSERT(GetPlayer());

    // Start loading display clientside:
    WorldPacket data(SMSG_TRANSFER_PENDING, 4);
    data << uint32(GetPlayer()->GetMapId());
    SendPacket(&data);

    // Set position on Node
    GetPlayer()->GetTeleportDest().mapid = GetPlayer()->GetMapId();
    GetPlayer()->GetTeleportDest().coord_x = GetPlayer()->GetPositionX();
    GetPlayer()->GetTeleportDest().coord_y = GetPlayer()->GetPositionY();
    GetPlayer()->GetTeleportDest().coord_z = GetPlayer()->GetPositionZ();
    GetPlayer()->GetTeleportDest().orientation = GetPlayer()->GetOrientation();
    GetPlayer()->SetSemaphoreTeleportFar(true);

    m_nodeSession = session;
    m_nodeSession->LoadSession(this);
    //m_nodeSession->LoginPlayer(this, GetPlayer()->GetObjectGuid());
    m_nodeSession->SendPlayer(this, GetPlayer());

    // Make a kind of Logout from the master server
    if (ObjectGuid lootGuid = GetPlayer()->GetLootGuid())
        DoLootRelease(lootGuid);

    // TODO: Handle battleground queues with MasterPlayer and not Player.
    //sBattleGroundMgr.RemovePlayerFromQueues(_player, true);

    ///- If the player is in a group (or invited), remove him. If the group if then only 1 person, disband the group.
    _player->UninviteFromGroup();

    ///- Send update to group
    if (_player->GetGroup())
        _player->GetGroup()->SendUpdate();

    ///- Remove from Map
    if (_player->IsInWorld())
        _player->GetMap()->Remove(_player, true);
    else
    {
        _player->CleanupsBeforeDelete();
        Map::DeleteFromWorld(_player);
    }

    SetPlayer(nullptr);
}

uint32 WorldSession::GenerateItemLowGuid()
{
    if (m_masterSession)
        return m_masterSession->GenerateItemLowGuid();
    return sObjectMgr.GenerateItemLowGuid();
}

uint32 WorldSession::GeneratePetNumber()
{
    if (m_masterSession)
        return m_masterSession->GeneratePetNumber();
    return sObjectMgr.GeneratePetNumber();
}

void WorldSession::ForwardPacketToMaster()
{
    if (GetMasterSession())
        throw ForwardToMaster_Exception();
}

void WorldSession::ForwardPacketToNode()
{
    if (GetNodeSession())
        throw ForwardToNode_Exception();
}

bool WorldSession::CharacterScreenIdleKick(uint32 currTime)
{
    if (GetPlayer() || m_inQueue || PlayerLoading()) // not on the character screen
        return false;

    auto maxIdle = sWorld.getConfig(CONFIG_UINT32_CHARACTER_SCREEN_MAX_IDLE_TIME);

    if (!maxIdle) // disabled
        return false;

    if ((currTime - m_idleTime) >= (maxIdle * 1000))
    {
        DEBUG_LOG("SESSION: Kicking session [%s] from character selection", GetRemoteAddress().c_str());
        return true;
    }

    return false;
}

/* Example Regex:
    ^(?=.*((?i)Y2[il]|(?i)у 2 [il]))(?=.*((?i)go[il]d|g o [il] d|g=([0-9]){1,2}\$)).*

    (?=.*((?i)Y2[il]|(?i)у 2 [il]))
    This part looks for combinations of "Y2L". Y2L, Y2I(which shows as l in game), Y 2 L, and so on.

    (?=.*((?i)go[il]d|g o [il] d|g=([0-9]){1,2}\$))
    This part looks for gold/goid (case insensitive). It also checks for things like g=5$

    With the (?=.*, they can be in any order, but both must be matched to be flagged by client.
*/
void WorldSession::SendExpectedSpamRecords()
{
    auto regexVector = sObjectMgr.GetClientSpamRegexes();
    if (regexVector.size() == 0)
        return;

    // Client Address: 0x49E6E0
    WorldPacket data(SMSG_EXPECTED_SPAM_RECORDS, 100);
    data << static_cast<uint32>(regexVector.size());
    for (const auto& itr : regexVector)
        data << itr;

    SendPacket(&data);
}

