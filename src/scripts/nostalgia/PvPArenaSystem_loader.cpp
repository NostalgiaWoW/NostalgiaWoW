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
    if (sender != PvPArenaSystem::SenderId)
        return false;

    player->PlayerTalkClass->CloseGossip();

    auto res = sPvPArenaSystem->Queue(player, (ArenaType)action);
    if (res != QueueResult::Okay)
        player->GetSession()->SendNotification(PvPArenaSystem::QueueResultToString(res).c_str());
    return true;
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
    script->RegisterSelfNoBind(ScriptType::Player);


}
