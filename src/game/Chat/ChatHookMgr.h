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

//Giperion February 2018
//[EUREKA] 3.6

#pragma once
#include "Common.h"
#include "Guild.h"
#include "Group.h"

class ChatHookMgr
{
public:

    void HookMessage(Group* group, WorldPacket& data);
    void HookMessage(Guild* guild, WorldPacket& data);
    //void HookMessage(Player* player, WorldPacket& data);
    void HookMessage(MasterPlayer* sender, MasterPlayer* receiver, std::string& textMessage);
    void HookMessage(Player* player, ChatMsg MessageType, std::string& textMessage);
    void HookChannelMessage(Player* player, std::string& Channel, std::string& textMessage);

    bool InstallHook(Player* receiver, Group* target);
    bool InstallHook(Player* receiver, Guild* target);
    bool InstallHook(Player* receiver, Player* target);
    bool InstallHookOnMiscChannels(Player* receiver, Player* target);

    bool RemoveHook(Player* receiver, Group* target);
    bool RemoveHook(Player* receiver, Guild* target);
    bool RemoveHook(Player* receiver, Player* target);

    bool ClearAllHooksRelatedToListener(ObjectGuid PlayerGuid);

private:

    std::unordered_multimap<uint32, ObjectGuid> groupHooks; //also cover raids and BG's
    std::unordered_multimap<uint32, ObjectGuid> guildsHooks;
    std::unordered_multimap<ObjectGuid, ObjectGuid> whisperHooks;
    std::unordered_multimap<ObjectGuid, ObjectGuid> MiscChannelsHooks;
};


#define sChatHookMgr MaNGOS::Singleton<ChatHookMgr>::Instance()