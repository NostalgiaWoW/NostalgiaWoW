#include "scriptPCH.h"
#include "Nostalgia/InspectSystem.h"

 
bool GossipSelect_player_inspect_code(Player* player, Player* otherPlayer, uint32 sender, uint32 action, const char* code)
{
    if (sender != InspectSystem::SenderId || action != InspectSystem::SenderId)
        return false;


    return true;
}

void AddSC_inspect_gossip()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "inspect_gossip";
    newscript->pPlrGossipSelectWithCode = &GossipSelect_player_inspect_code;
    newscript->RegisterSelfNoBind(ScriptType::Player);
} 