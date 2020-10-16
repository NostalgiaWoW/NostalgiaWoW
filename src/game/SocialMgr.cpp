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

#include "SocialMgr.h"
#include "Policies/SingletonImp.h"
#include "Database/DatabaseEnv.h"
#include "Opcodes.h"
#include "WorldPacket.h"
#include "MasterPlayer.h"
#include "ObjectMgr.h"
#include "World.h"
#include "Util.h"

INSTANTIATE_SINGLETON_1(SocialMgr);

PlayerSocial::PlayerSocial(): m_playerLowGuid(0)
{
}

PlayerSocial::~PlayerSocial()
{
    m_playerSocialMap.clear();
}

uint32 PlayerSocial::GetNumberOfSocialsWithFlag(SocialFlag flag)
{
    uint32 counter = 0;
    for (PlayerSocialMap::const_iterator itr = m_playerSocialMap.cbegin(); itr != m_playerSocialMap.cend(); ++itr)
    {
        if (itr->second.Flags & flag)
            ++counter;
    }
    return counter;
}

void PlayerSocial::Clear()
{
    m_playerSocialMap.clear();
    CharacterDatabase.PExecute("DELETE FROM character_social WHERE guid = '%u'", m_playerLowGuid);
}

bool PlayerSocial::AddToSocialList(ObjectGuid friend_guid, bool ignore)
{
    // check client limits
    if (ignore)
    {
        if (GetNumberOfSocialsWithFlag(SOCIAL_FLAG_IGNORED) >= SOCIALMGR_IGNORE_LIMIT)
            return false;
    }
    else
    {
        if (GetNumberOfSocialsWithFlag(SOCIAL_FLAG_FRIEND) >= SOCIALMGR_FRIEND_LIMIT)
            return false;
    }

    uint32 flag = SOCIAL_FLAG_FRIEND;
    if (ignore)
        flag = SOCIAL_FLAG_IGNORED;

    PlayerSocialMap::const_iterator itr = m_playerSocialMap.find(friend_guid.GetCounter());
    if (itr != m_playerSocialMap.cend())
    {
        CharacterDatabase.PExecute("UPDATE character_social SET flags = (flags | %u) WHERE guid = '%u' AND friend = '%u'", flag, m_playerLowGuid, friend_guid.GetCounter());
        m_playerSocialMap[friend_guid.GetCounter()].Flags |= flag;
    }
    else
    {
        CharacterDatabase.PExecute("INSERT INTO character_social (guid, friend, flags) VALUES ('%u', '%u', '%u')", m_playerLowGuid, friend_guid.GetCounter(), flag);
        FriendInfo fi;
        fi.Flags |= flag;
        m_playerSocialMap[friend_guid.GetCounter()] = fi;
    }
    return true;
}

void PlayerSocial::RemoveFromSocialList(ObjectGuid friend_guid, bool ignore)
{
    PlayerSocialMap::iterator itr = m_playerSocialMap.find(friend_guid.GetCounter());
    if (itr == m_playerSocialMap.end())                     // not exist
        return;

    uint32 flag = SOCIAL_FLAG_FRIEND;
    if (ignore)
        flag = SOCIAL_FLAG_IGNORED;

    itr->second.Flags &= ~flag;
    if (itr->second.Flags == 0)
    {
        CharacterDatabase.PExecute("DELETE FROM character_social WHERE guid = '%u' AND friend = '%u'", m_playerLowGuid, friend_guid.GetCounter());
        m_playerSocialMap.erase(itr);
    }
    else
        CharacterDatabase.PExecute("UPDATE character_social SET flags = (flags & ~%u) WHERE guid = '%u' AND friend = '%u'", flag, m_playerLowGuid, friend_guid.GetCounter());
}

void PlayerSocial::SendFriendList()
{
	MasterPlayer* plr = ObjectAccessor::FindMasterPlayer(GetMasterPlayerGuid());
	if (plr == nullptr)
	{
		sLog.outError("[CRASH]: SendFriendList on nullptr MasterPlayer");
		return;
	}

    uint32 size = GetNumberOfSocialsWithFlag(SOCIAL_FLAG_FRIEND);

    WorldPacket data(SMSG_FRIEND_LIST, (1 + size * 25)); // just can guess size
    data << uint8(size);                                   // friends count

    for (PlayerSocialMap::iterator itr = m_playerSocialMap.begin(); itr != m_playerSocialMap.end(); ++itr)
    {
        if (itr->second.Flags & SOCIAL_FLAG_FRIEND)         // if IsFriend()
        {
            sSocialMgr.GetFriendInfo(plr, itr->first, itr->second);

            data << ObjectGuid(HIGHGUID_PLAYER, itr->first);// player guid
            data << uint8(itr->second.Status);              // online/offline/etc?
            if (itr->second.Status)                         // if online
            {
                data << uint32(itr->second.Area);           // player area
                data << uint32(itr->second.Level);          // player level
                data << uint32(itr->second.Class);          // player class
            }
        }
    }

    plr->GetSession()->SendPacket(&data);
    DEBUG_LOG("WORLD: Sent SMSG_FRIEND_LIST");
}

void PlayerSocial::SendIgnoreList()
{
	MasterPlayer* plr = ObjectAccessor::FindMasterPlayer(GetMasterPlayerGuid());
	if (plr == nullptr)
	{
		sLog.outError("[CRASH]: SendIgnoreList on nullptr MasterPlayer");
		return;
	}

    uint32 size = GetNumberOfSocialsWithFlag(SOCIAL_FLAG_IGNORED);

    WorldPacket data(SMSG_IGNORE_LIST, (1 + size * 8));     // just can guess size
    data << uint8(size);                                    // friends count

    for (PlayerSocialMap::const_iterator itr = m_playerSocialMap.cbegin(); itr != m_playerSocialMap.cend(); ++itr)
        if (itr->second.Flags & SOCIAL_FLAG_IGNORED)
            data << ObjectGuid(HIGHGUID_PLAYER, itr->first);// player guid


    plr->GetSession()->SendPacket(&data);
    DEBUG_LOG("WORLD: Sent SMSG_IGNORE_LIST");
}

bool PlayerSocial::HasFriend(ObjectGuid friend_guid)
{
    PlayerSocialMap::const_iterator itr = m_playerSocialMap.find(friend_guid.GetCounter());
    if (itr != m_playerSocialMap.cend())
        return itr->second.Flags & SOCIAL_FLAG_FRIEND;
    return false;
}

bool PlayerSocial::HasIgnore(ObjectGuid ignore_guid)
{
    PlayerSocialMap::const_iterator itr = m_playerSocialMap.find(ignore_guid.GetCounter());
    if (itr != m_playerSocialMap.cend())
        return itr->second.Flags & SOCIAL_FLAG_IGNORED;
    return false;
}

SocialMgr::SocialMgr()
{

}

SocialMgr::~SocialMgr()
{

}

void SocialMgr::RemovePlayerSocial(uint32 guid)
{
	m_socialMapGuard.acquire_write();
	auto Iter = m_socialMap.find(guid);
	if (Iter != m_socialMap.end())
	{
		m_socialMap.erase(Iter);
	}
	else
	{
		sLog.outError("[CRASH possible]: Attempt to delete social struct, which not in a map anymore");
	}
	m_socialMapGuard.release_write();
}

PlayerSocialPointer SocialMgr::GetPlayerSocial(ObjectGuid playerGuid)
{
    struct ReleaseReadAcquire
    {
        ReleaseReadAcquire(ACE_Based::RecursiveRWMutex* InGuard)
        {
            Guard = InGuard;
            Guard->acquire_read();
        }
        ~ReleaseReadAcquire()
        {
            Guard->release_read();
        }
        ACE_Based::RecursiveRWMutex* Guard;
    } ReleaseReadAcquireInstance(&m_socialMapGuard);

	auto Iter = m_socialMap.find(playerGuid.GetCounter());
	if (Iter != m_socialMap.end())
	{
		return PlayerSocialPointer (&(*Iter).second);
	}
	else
	{
		sLog.outError("[CRASH]: Attempt to obtain a Social struct from unloaded player");
		
		//we must return something. Return default struct
		return PlayerSocialPointer (&m_defaultSocial);
	}
}

void SocialMgr::GetFriendInfo(MasterPlayer* player, uint32 friend_lowguid, FriendInfo &friendInfo)
{
	if (!player)
        return;

    MasterPlayer *pFriend = ObjectAccessor::FindMasterPlayer(ObjectGuid(HIGHGUID_PLAYER, friend_lowguid));

    Team team = player->GetTeam();
    AccountTypes security = player->GetSession()->GetSecurity();
    bool allowTwoSideWhoList = sWorld.getConfig(CONFIG_BOOL_ALLOW_TWO_SIDE_WHO_LIST);
    AccountTypes gmLevelInWhoList = AccountTypes(sWorld.getConfig(CONFIG_UINT32_GM_LEVEL_IN_WHO_LIST));

    //  Make a copy
	PlayerSocialPointer SocialPtr = GetPlayerSocial(player->GetObjectGuid());
    PlayerSocialMap socialMap = SocialPtr->m_playerSocialMap;

    PlayerSocialMap::const_iterator itr = socialMap.find(friend_lowguid);
	if (itr != socialMap.end())
	{
		// PLAYER see his team only and PLAYER can't see MODERATOR, GAME MASTER, ADMINISTRATOR characters
		// MODERATOR, GAME MASTER, ADMINISTRATOR can see all
		if (pFriend && pFriend->GetName() &&
			(security > SEC_PLAYER ||
			((pFriend->GetTeam() == team || allowTwoSideWhoList) && (pFriend->GetSession()->GetSecurity() <= gmLevelInWhoList))) &&
			pFriend->IsVisibleGloballyFor(player))
		{
			friendInfo.Status = FRIEND_STATUS_ONLINE;
			if (pFriend->isAFK())
				friendInfo.Status = FRIEND_STATUS_AFK;
			if (pFriend->isDND())
				friendInfo.Status = FRIEND_STATUS_DND;
			friendInfo.Area = pFriend->GetZoneId();
			friendInfo.Level = pFriend->getLevel();
			friendInfo.Class = pFriend->getClass();
		}
		else
		{
			friendInfo.Status = FRIEND_STATUS_OFFLINE;
			friendInfo.Area = 0;
			friendInfo.Level = 0;
			friendInfo.Class = 0;
		}
	}
}

void SocialMgr::MakeFriendStatusPacket(FriendsResult result, uint32 guid, WorldPacket *data)
{
    data->Initialize(SMSG_FRIEND_STATUS, 5);
    *data << uint8(result);
    *data << ObjectGuid(HIGHGUID_PLAYER, guid);
}

void SocialMgr::SendFriendStatus(MasterPlayer *player, FriendsResult result, ObjectGuid friend_guid, bool broadcast)
{
    uint32 friend_lowguid = friend_guid.GetCounter();

    FriendInfo fi;

    WorldPacket data;
    MakeFriendStatusPacket(result, friend_lowguid, &data);
    GetFriendInfo(player, friend_lowguid, fi);

    switch (result)
    {
        case FRIEND_ADDED_ONLINE:
        case FRIEND_ONLINE:
            data << uint8(fi.Status);
            data << uint32(fi.Area);
            data << uint32(fi.Level);
            data << uint32(fi.Class);
            break;
        default:
            break;
    }

    if (broadcast)
        BroadcastToFriendListers(player, &data);
    else
        player->GetSession()->SendPacket(&data);
}

void SocialMgr::BroadcastToFriendListers(MasterPlayer *player, WorldPacket *packet)
{
    if (!player)
        return;

    Team team = player->GetTeam();
    AccountTypes security = player->GetSession()->GetSecurity();
    uint32 guid     = player->GetGUIDLow();
    AccountTypes gmLevelInWhoList = AccountTypes(sWorld.getConfig(CONFIG_UINT32_GM_LEVEL_IN_WHO_LIST));
    bool allowTwoSideWhoList = sWorld.getConfig(CONFIG_BOOL_ALLOW_TWO_SIDE_WHO_LIST);

	m_socialMapGuard.acquire_read();
    for (SocialMap::const_iterator itr = m_socialMap.begin(); itr != m_socialMap.end(); ++itr)
    {
        PlayerSocialMap::const_iterator itr2 = itr->second.m_playerSocialMap.find(guid);
        if (itr2 != itr->second.m_playerSocialMap.cend() && (itr2->second.Flags & SOCIAL_FLAG_FRIEND))
        {
            MasterPlayer *pFriend = ObjectAccessor::FindMasterPlayer(ObjectGuid(HIGHGUID_PLAYER, itr->first));

            // PLAYER see his team only and PLAYER can't see MODERATOR, GAME MASTER, ADMINISTRATOR characters
            // MODERATOR, GAME MASTER, ADMINISTRATOR can see all
            if (pFriend &&
                    (pFriend->GetSession()->GetSecurity() > SEC_PLAYER ||
                     ((pFriend->GetTeam() == team || allowTwoSideWhoList) && security <= gmLevelInWhoList)) &&
                    player->IsVisibleGloballyFor(pFriend))
                pFriend->GetSession()->SendPacket(packet);
        }
    }
	m_socialMapGuard.release_read();
}

PlayerSocial *SocialMgr::LoadFromDB(QueryResult *result, ObjectGuid guid)
{
	m_socialMapGuard.acquire_write();
    PlayerSocial *social = &m_socialMap[guid.GetCounter()];
	m_socialMapGuard.release_write();
    social->SetPlayerGuid(guid);

    if (!result)
        return social;

    uint32 friend_guid = 0;
    uint32 flags = 0;

    // used to speed up check below. Using GetNumberOfSocialsWithFlag will cause unneeded iteration
    uint32 friendCounter = 0, ignoreCounter = 0;

    do
    {
        Field *fields  = result->Fetch();

        friend_guid = fields[0].GetUInt32();
        flags = fields[1].GetUInt32();

        if ((flags & SOCIAL_FLAG_IGNORED) && ignoreCounter >= SOCIALMGR_IGNORE_LIMIT)
            continue;
        if ((flags & SOCIAL_FLAG_FRIEND) && friendCounter >= SOCIALMGR_FRIEND_LIMIT)
            continue;

        social->m_playerSocialMap[friend_guid] = FriendInfo(flags);

        if (flags & SOCIAL_FLAG_IGNORED)
            ignoreCounter++;
        else
            friendCounter++;
    }
    while (result->NextRow());
    return social;
}

PlayerSocialPointer::PlayerSocialPointer(PlayerSocial* InSocialData)
{
	pSocialData = InSocialData;
    Init();
}

PlayerSocialPointer::PlayerSocialPointer(const PlayerSocialPointer& other)
{
	pSocialData = other.pSocialData;
	Counter = other.Counter;
	//(*Counter)++;
    int IncrementedCounter = ++(*Counter);
    if (IncrementedCounter == 1) //rare case, when the object just deleted in another thread
    {
        Init();
    }
}

void PlayerSocialPointer::Init()
{
    Counter = new std::atomic<int>;
    *Counter = 1;
    sSocialMgr.m_socialMapGuard.acquire_read();
}

PlayerSocialPointer::~PlayerSocialPointer()
{
	//--(*Counter);
    int DecrementedCounter = --(*Counter);
	if (DecrementedCounter == 0)
	{
		sSocialMgr.m_socialMapGuard.release_read();
		delete Counter; Counter = nullptr;
	}
}

PlayerSocial* PlayerSocialPointer::operator->() const
{
	return pSocialData;
}
