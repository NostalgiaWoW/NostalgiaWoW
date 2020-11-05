#pragma once

#include "Database/DatabaseEnv.h"
#include "Common.h"

#include <unordered_map>

enum class ArenaType
{
    TwoPlayers = 2,
    ThreePlayers
};

struct PvPArena
{
    uint32 Id;
    ArenaType Type;
    float Radius;
    float Position_x;
    float Position_y;
    uint32 MapId;
};

class PvPArenaSystem
{
    DECLARE_SINGLETON(PvPArenaSystem)
public:

    void LoadFromDB();

private:
    std::unordered_multimap<ArenaType, PvPArena> m_arenas;
};

#define sPvPArenaSystem PvPArenaSystem::Instance()