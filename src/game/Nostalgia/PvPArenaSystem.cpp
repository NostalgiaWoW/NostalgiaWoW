#include "PvPArenaSystem.h"

void PvPArenaSystem::LoadFromDB()
{
    auto result = WorldDatabase.QuerySafe("SELECT * FROM `pvp_arena_system`");

    if (!result)
        return;

    do {
        auto fields = result->Fetch();
        PvPArena arena = { fields[0].GetUInt32(), static_cast<ArenaType>(fields[1].GetUInt32()), fields[2].GetFloat(), fields[3].GetFloat(), fields[4].GetFloat(), fields[5].GetUInt32() };
        m_arenas.insert({ arena.Type, arena });
    } while (result->NextRow());
}