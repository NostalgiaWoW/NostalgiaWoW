/*
* Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
* Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
* Copyright (C) 2011-2016 Nostalrius <https://nostalrius.org>
* Copyright (C) 2016-2018 Elysium Project <https://github.com/elysium-project>
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

//Giperion April 2018
//[EUREKA] 3.6
#include <Policies/SingletonImp.h>
#include "World.h"
#include "Language.h"
#include "Chat.h"
#include "Group.h"
#include "ObjectMgr.h"
#include "Unit.h"
#include "Player.h"
#include "SuspiciousStatisticMgr.h"

INSTANTIATE_SINGLETON_1(SuspiciousStatisticMgr);

void FormatPlayerNameToLink(const char* InPlayerName, char* OutPlayerLink, size_t OutBufferSize)
{
    int FormattedStrLen = snprintf(OutPlayerLink, OutBufferSize, "|cffffc0c0|Hplayer:%s|h[%s]|h|r", InPlayerName, InPlayerName);
    OutPlayerLink[FormattedStrLen] = 0;
}

void SuspiciousStatisticMgr::OnNpcKilledInDungeon(Player* player, Unit* NPC)
{
    if (!bEnable || !bNpcKilledEnable) return;
    //Player ptr is always valid

    //Gamemasters can do anything, should'nt be logged
    if (player->isGameMaster()) return;

    if (IsPlayerInDungeonWithoutParty(player))
    {
        if (Creature* npcCreature = NPC->ToCreature())
        {
            int32 creatureLevel = (int32)NPC->getLevel();
            int32 playerLevel = (int32)player->getLevel();

            ///HACKER
            ///Killing elites that equal (or almost equal) player level without a party
            if (npcCreature->IsElite())
            {
                if (playerLevel < (creatureLevel + 3))
                {
                    RecordSuspiciousActivity(SuspiciousType::KILL_ELITE, player, NPC->GetEntry(), 0, npcCreature->GetName());
                    return;
                }
            }

            ///BOOSTER
            ///Killing monster by high level character with party of one player
            if (playerLevel > (creatureLevel + 15))
            {
                //#TODO: Maybe I should enable detection for party then greater two?
                if (Group* group = player->GetGroup())
                {
                    if (group->GetMembersCount() == 2)
                    {
                        //we already check inactivity before, but boosted player can be outside map or offline
                        Player* boostedPlayer = nullptr;
                        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
                        {
                            if (itr->getSource() != player)
                            {
                                boostedPlayer = itr->getSource();
                                if (boostedPlayer->FindMap() == player->FindMap() && boostedPlayer->getLevel() < 55)
                                {
                                    break;
                                }
                                else
                                {
                                    boostedPlayer = nullptr;
                                }
                            }
                        }

                        if (boostedPlayer != nullptr)
                        {
                            const char* boostDesc = nullptr;
                            std::stringstream message;

                            char PlayerLink[64] = { 0 };
                            FormatPlayerNameToLink(boostedPlayer->GetName(), PlayerLink, sizeof(PlayerLink));
                            message << "Boosted player name: "
                                    << PlayerLink;
                            boostDesc = message.str().c_str();
                            RecordSuspiciousActivity(SuspiciousType::BOOSTING, player, boostedPlayer ? boostedPlayer->GetGUIDLow() : 0, 0, boostDesc);
                        }

                        return;
                    }
                }
            }

            ///FARMERS
            ///Killing a lot of mobs in dungeons to get a loot
            //#TODO: Farmers
        }
    }
}

void SuspiciousStatisticMgr::OnNpcKilledInWorld(Player* player, Unit* NPC)
{
    if (!bEnable || !bNpcKilledEnable) return;

    //Player ptr is always valid
    //#TODO: Farmers
}


void SuspiciousStatisticMgr::OnFishingAttempt(Player* player)
{
    if (!bEnable || !bFishingEnable) return;

    //Player ptr is always valid
    ACE_Guard<ACE_Thread_Mutex> guard(FishingTimeCounterMapGuard);

    auto pTimestampIter = FishingTimeCounterMap.find(player->GetGUIDLow());
    if (pTimestampIter != FishingTimeCounterMap.end())
    {
        FishingTracker& tracker = pTimestampIter->second;
        //Ensure that it's still same fishing session, otherwise delete
        uint32 currentTime = WorldTimer::getMSTime();

        if (WorldTimer::getMSTimeDiff(tracker.LastAttemptTimestamp, currentTime) > 1 * MINUTE * IN_MILLISECONDS)
        {
            //It's another fishing session, update counters and exit
            tracker.LastAttemptTimestamp = currentTime;
            tracker.StartTimestamp = currentTime;
        }
        else
        {
            //Same session, let's check
            tracker.LastAttemptTimestamp = currentTime;

            if (WorldTimer::getMSTimeDiff(tracker.StartTimestamp, currentTime) > 30 * MINUTE * IN_MILLISECONDS)
            {
                //Fishing too long, report if we don't already do that
                auto pReportedPlayerIter = std::find(FishingReportedPlayers.begin(), FishingReportedPlayers.end(), player->GetGUIDLow());
                if (pReportedPlayerIter == FishingReportedPlayers.end())
                {
                    RecordSuspiciousActivity(SuspiciousType::FISHING_TOO_LONG, player, tracker.StartTimestamp, currentTime);
                    FishingReportedPlayers.push_back(player->GetGUIDLow());
                }
            }
        }
    }
    else
    {
        //Create new fishing tracker with current time
        //FishingTimeCounterMap.insert(std::pair<uint32, FishingTracker>(player->GetGUIDLow(), FishingTracker(WorldTimer::getMSTime(), WorldTimer::getMSTime())));
        FishingTimeCounterMap[player->GetGUIDLow()] = FishingTracker(WorldTimer::getMSTime(), WorldTimer::getMSTime());
    }

    ClearFishingTracker();
}

void SuspiciousStatisticMgr::OnMovement(Player* player, MovementInfo& newInfo)
{
    if (!bEnable || !bMovementEnable) return;

    //Player ptr can be invalid
#if 0
    if (player == nullptr || player->IsDeleted()) return;

    //GM's can move whatever he want
    if (player->isGameMaster()) return;

    MovementInfo& prevInfo = player->m_movementInfo;

    //prevInfo.GetPos()
#endif

    //#TEMP: Just check calculated velocity for now
    if (player == nullptr || player->IsDeleted()) return;

    //GM's can move whatever he want
    if (player->isGameMaster()) return;

    if (player->GetVelocityPerSecond() > MovementDetectValue && !player->bIsReportedAsSpeedhacker && player->GetTransport() == nullptr)
    {
        player->bIsReportedAsSpeedhacker = true;
        
        RecordSuspiciousActivity(SuspiciousType::MOVING_TOO_FAST, player, std::lround(player->GetVelocityPerSecond()), std::lround((uint32)MovementDetectValue));
    }
}


void SuspiciousStatisticMgr::PrintAllActiveFishers(Player* receiver)
{
    ChatHandler chatHandler(receiver);
    for (auto iter = FishingTimeCounterMap.begin(); iter != FishingTimeCounterMap.end(); ++iter)
    {
        if (Player* fisher = sObjectMgr.GetPlayer(ObjectGuid(iter->first)))
        {
            FishingTracker& tracker = iter->second;
            uint32 currentTime = WorldTimer::getMSTime();
            float flDeltaSinceStart = float(currentTime - tracker.StartTimestamp);
            flDeltaSinceStart /= 1000.0f;
            float flDeltaSinceLastFishAttempt = float(currentTime - tracker.LastAttemptTimestamp);
            flDeltaSinceLastFishAttempt /= 1000.0f;

            char PlayerLink[64] = { 0 };
            FormatPlayerNameToLink(fisher->GetName(), PlayerLink, sizeof(PlayerLink));
            std::stringstream ss;
            ss << "Player:" << PlayerLink
                << " Start fishing " << flDeltaSinceStart
                << " Last attempt " << flDeltaSinceLastFishAttempt;

            chatHandler.SendSysMessage(ss.str().c_str());
        }
    }
}

void SuspiciousStatisticMgr::RecordSuspiciousActivity(SuspiciousType::Value type, Player* player, uint32 Param1, uint32 Param2, const char* OptDescMessage /*= nullptr*/)
{
    //SQL
    LogsDatabase.PExecute("INSERT INTO `logs_suspicious` (`realmId`, `type`, `time`, `guid`, `accountId`, `posX`, `posY`, `posZ`, `mapId`, `param1`, `param2`)"
        " VALUES ('%u', '%u', NOW(), '%u', '%u', '%f', '%f', '%f', '%u', '%u', '%u')",
        realmID, (uint32)type, player->GetGUIDLow(), player->GetSession()->GetAccountId(), player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetMapId(), Param1, Param2);

    //Log file
    sLog.out(LOG_SUSPICIOUS, "Player: '%s' (GUID: '%u'), act '%s' Param1: '%u' Param2: '%u'", 
        player->GetName(), player->GetGUIDLow(), SuspiciousType::ToString(type), Param1, Param2);

    //GM announce
    std::stringstream message;

    char PlayerLink[64] = {0};
    FormatPlayerNameToLink(player->GetName(), PlayerLink, sizeof(PlayerLink));

    message << "Player:" << PlayerLink
        << " IP: " << player->GetSession()->GetRemoteAddress()
        << " Account ID: " << player->GetSession()->GetAccountId()
        << " Action: " << SuspiciousType::ToString(type)
        << " Param 1: " << Param1
        << " Param 2: " << Param2;

    if (OptDescMessage != nullptr)
    {
        message << " " << OptDescMessage;
    }

    sWorld.SendGMTextFlags(ACCOUNT_FLAG_SHOW_SUSPICIOUS, LANG_GM_ANNOUNCE_COLOR, "Suspicious", message.str().c_str());
}

bool SuspiciousStatisticMgr::IsPlayerInDungeonWithoutParty(Player* player)
{
    if (Group* group = player->GetGroup())
    {
        //Check all group members for activity in dungeon
        for (GroupReference* itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            if (Player* groupMember = itr->getSource())
            {
                //ignore self
                if (groupMember == player) continue;

                //ignore players not in same dungeon as target player
                if (groupMember->FindMap() != player->FindMap()) continue;

                //check inactivity
                if (!groupMember->IsBasicallyInactive())
                    return false;
            }
        }
    }
    
    return true;
}

void SuspiciousStatisticMgr::ClearFishingTracker()
{
    uint32 currentTime = WorldTimer::getMSTime();

    if (WorldTimer::getMSTimeDiff(FishingClearMaintanceTimer, currentTime) > 15 * MINUTE * IN_MILLISECONDS)
    {
        FishingClearMaintanceTimer = currentTime;

        std::vector < uint32 > DeletedPlayerGuids;
        for (auto iter = FishingTimeCounterMap.begin(); iter != FishingTimeCounterMap.end(); ++iter)
        {
            FishingTracker& tracker = iter->second;
            if (WorldTimer::getMSTimeDiff(tracker.LastAttemptTimestamp, currentTime) > 1 * MINUTE * IN_MILLISECONDS)
            {
                DeletedPlayerGuids.push_back(iter->first);
                iter = FishingTimeCounterMap.erase(iter);
                if (iter == FishingTimeCounterMap.end()) break;
            }
        }

        for (uint32 playerGUID : DeletedPlayerGuids)
        {
            auto targetIter = std::find(FishingReportedPlayers.begin(), FishingReportedPlayers.end(), playerGUID);
            if (targetIter != FishingReportedPlayers.end())
            {
                FishingReportedPlayers.erase(targetIter);
            }
        }
    }
}

const char* SuspiciousType::ToString(Value value)
{
    switch (value)
    {
    case SuspiciousType::NONE:
        return "NONE";
    case SuspiciousType::KILL_ELITE:
        return "KILL_ELITE";
    case SuspiciousType::FISHING_TOO_LONG:
        return "FISHING_TOO_LONG";
    case SuspiciousType::BOOSTING:
        return "BOOSTING";
    case SuspiciousType::MOVING_TOO_FAST:
        return "MOVING_TOO_FAST";
    default:
        return "UNDEFINED";
    }
}
