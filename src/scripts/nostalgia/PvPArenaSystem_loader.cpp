#include "scriptPCH.h"
#include "Nostalgia/PvPArenaSystem.h"
#include "Chat.h"

void OnStartup()
{
    sPvPArenaSystem->LoadFromDB();
}

void OnPlayerRelocation(Player* player, const MovementInfo* oldInfo, const MovementInfo* newInfo)
{
    sPvPArenaSystem->HandlePlayerRelocation(player, *newInfo->GetPos());
}

void OnPvPKill(Player* killer, Player* killed)
{
    sPvPArenaSystem->HandlePvPKill(killer, killed);
}

void OnWorldUpdate(uint32 diff)
{
    sPvPArenaSystem->HandleWorldUpdate(diff);
}

bool OnPlayerGossipSelect(Player* player, Player* otherPlayer, uint32 sender, uint32 action)
{
    if (sender != PvPArenaSystem::SenderId && sender != PvPArenaSystem::ConfirmationSenderId)
        return false;

    if (sender == PvPArenaSystem::SenderId)
    {
        player->PlayerTalkClass->CloseGossip();

        if (action == 10) // leave queue
            sPvPArenaSystem->LeaveQueue(player);
        else
        {
            auto res = sPvPArenaSystem->Queue(player, (ArenaType)action);
            if (res != QueueResult::Okay)
                player->GetSession()->SendNotification(PvPArenaSystem::QueueResultToString(res).c_str());
        }

	
    }
    else if (sender == PvPArenaSystem::ConfirmationSenderId)
    {
        //set confirmation check here.
        player->PlayerTalkClass->CloseGossip();
        bool leave = action >= PvPArenaSystem::LeaveQueueAction;
        uint32 arenaId = leave ? action - PvPArenaSystem::LeaveQueueAction : action;
        sPvPArenaSystem->ConfirmationReceived(player, leave, arenaId);
    }
    return true;
}


bool OnPlayerGossipSelect_Command(Player* player, Player* otherPlayer, uint32 sender, uint32 action)
{
	if (action)
	if (sender != PvPArenaSystem::CommandSenderId)
		return false;

	if (sender == PvPArenaSystem::CommandSenderId)
	{
		//player->PlayerTalkClass->CloseGossip();

		switch (action)
		{
			case 4:
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "1v1", PvPArenaSystem::SenderId, 1);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "2v2", PvPArenaSystem::SenderId, 2);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "3v3", PvPArenaSystem::SenderId, 3);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "<-- Back to main menu", PvPArenaSystem::CommandSenderId, 8);
				player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());
				break;

			case 5:
				player->PlayerTalkClass->ClearMenus();
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "COMING SOON!", PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "<-- Back to main menu", PvPArenaSystem::CommandSenderId, 8);
				player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());
				break;
			case 7:
				sPvPArenaSystem->GetTopStats(player);
				break;

			case 8:
			{
				player->PlayerTalkClass->ClearMenus();
				if (sPvPArenaSystem->IsInQueue(player))
				{
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Leave Queue", PvPArenaSystem::SenderId, 10);
				}
				else {
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Queue Arena", PvPArenaSystem::CommandSenderId, 4);
				}

				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Spectate Arena", PvPArenaSystem::CommandSenderId, 5);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Your PvP Stats", PvPArenaSystem::CommandSenderId, 6);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Top Arena Players", PvPArenaSystem::CommandSenderId, 7);
				player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());
				break;
			}
			case 6:
				sPvPArenaSystem->GetPvPStats(player);
				break;
		}

	}


	return true;
}

void OnLogout(Player* player)
{
    sPvPArenaSystem->HandleLogout(player);
}


void AddSC_PvPArenaSystem_Loader()
{
    Script* script = new Script;
    script->Name = "PvPArenaSystem_Loader";
    script->pOnStartup = &OnStartup;
    script->pOnWorldUpdate = &OnWorldUpdate;
    script->RegisterSelfNoBind(ScriptType::World);

    script = new Script;
    script->Name = "PvPArenaSystem_Player";
    script->pOnPlayerRelocation = &OnPlayerRelocation;
    script->pOnPvPKill = &OnPvPKill;
    script->pPlrGossipSelect = &OnPlayerGossipSelect;
    script->pOnPlayerLogout = &OnLogout;
    script->RegisterSelfNoBind(ScriptType::Player);

	script = new Script;
	script->Name = "PvPArena_Command";
	script->pPlrGossipSelect = &OnPlayerGossipSelect_Command;
	script->RegisterSelfNoBind(ScriptType::Player);

}
