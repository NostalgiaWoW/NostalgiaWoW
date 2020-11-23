#include "scriptPCH.h"
#include "Nostalgia/PvPArenaSystem.h"

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


}
