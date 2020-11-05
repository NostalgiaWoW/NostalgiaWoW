#include "scriptPCH.h"
#include "Nostalgia/PvPArenaSystem.h"

void OnStartup()
{
    sPvPArenaSystem->LoadFromDB();
}

void AddSC_PvPArenaSystem_Loader()
{
    Script* script = new Script;
    script->Name = "PvPArenaSystem_Loader";
    script->pOnStartup = &OnStartup;
    script->RegisterSelfNoBind(ScriptType::World);
}
