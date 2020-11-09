#pragma once

#include "Database/DatabaseEnv.h"
#include "Common.h"
#include "Utilities/EventMap.h"

#include <unordered_map>
#include <array>

enum class ArenaType
{
    OnePlayer = 1,
    TwoPlayers = 2,
    ThreePlayers
};

enum class ArenaStatus
{
    None,
    Starting,
    Active,
    Ended
};

enum class OutcomeResult
{
    NoWinner,
    Team1Wins,
    Team2Wins,
    Draw
};

enum class OutcomeCheck
{
    Kill,
    Time,
    Both
};

enum ArenaEvents
{
    EVENT_ARENA_STARTING_IN_1 = 1,
    EVENT_ARENA_STARTING_IN_2 = 2,
    EVENT_ARENA_STARTING_IN_3 = 3,
    EVENT_ARENA_STARTING_IN_4 = 4,
    EVENT_ARENA_STARTING_IN_5 = 5,
    EVENT_ARENA_STARTING_IN_15 = 15,
    EVENT_ARENA_STARTING_IN_30 = 30,
    
    EVENT_ARENA_STARTS
};

struct PvPArena
{
    uint32 Id;
    ArenaType Type;
    float Radius;
    float Position_x;
    float Position_y;
    uint32 MapId;
    std::array<Position, 2> TeamPositions;
};

struct PartyInfo
{
    ObjectGuid LeaderGuid;
    std::vector<ObjectGuid> Group;
    ArenaType Type;
};

struct ArenaPlayer
{
    ArenaPlayer(ObjectGuid guid) : IsAlive(true), Guid(guid) {}
    ObjectGuid Guid;
    bool IsAlive;
    WorldLocation OldPosition;
};

struct TeamInfo
{
    std::vector<ArenaPlayer> Group;
    ArenaType Type;
};

class ArenaGame
{
public:
    friend class PvPArenaSystem;

    ArenaGame() {} // SFINAE friendly

    ArenaGame(uint32 gameId, PvPArena* arena, TeamInfo team1, TeamInfo team2)
        : m_gameId(gameId), m_arena(arena), m_map(nullptr), m_status(ArenaStatus::None), m_earlyConditionsCheck(false)
    {
        m_teams[0] = team1;
        m_teams[1] = team2;

        m_map = sMapMgr.FindMap(arena->MapId);
    }

    void Start();
    void CheckWin();
    void PlayerDied(Player* player);
    void Update(uint32 diff);
    void EndGame(OutcomeResult result);
    void EventArenaActive();

    static void RestoreResources(Player* player);

private:
    OutcomeResult CheckOutcome(OutcomeCheck);
    void CheckEarlyConditions() { m_earlyConditionsCheck = true; }

    template <typename F>
    void DoForAllPlayers(F f)
    {
        for (const auto& team : m_teams)
        {
            for (const auto& arenaPlayer : team.Group)
            {
                f(arenaPlayer.Guid, team, arenaPlayer);
            }
        }
    }

    EventMap m_events;
    uint32 m_gameId;
    std::array<TeamInfo, 2> m_teams;
    PvPArena* m_arena;
    Map* m_map;
    bool m_earlyConditionsCheck;

    ArenaStatus m_status;
};

struct ArenaInfo
{
    ArenaInfo() : InUse(false) {}

    PvPArena Arena;
    bool InUse;
};

enum class QueueResult
{
    Okay,
    NoGroup,
    MemberCount,
    NoLeader,
    AlreadyInQueue
};

class PvPArenaSystem
{
    DECLARE_SINGLETON(PvPArenaSystem)
public:

    void LoadFromDB();
    void HandlePlayerRelocation(Player* player, const Position& newPos);
    void HandlePvPKill(Player* killer, Player* killed);
    void HandleWorldUpdate(uint32 diff);


    QueueResult Queue(Player* player, ArenaType type);
    void ScheduleQueueUpdate();
    void ArenaGameEnded(ArenaGame* game);

    static std::string QueueResultToString(QueueResult result);

private:
    uint32 GenerateArenaId();
    PvPArena PickArenaTemplate(ArenaType type);

    std::unordered_multimap<ArenaType, std::reference_wrapper<PvPArena>> m_freeArenas;
    std::unordered_multimap<ArenaType, PvPArena> m_arenas;
    std::unordered_map<ObjectGuid, PartyInfo> m_queuedPlayers;
    std::unordered_map<ObjectGuid, uint32> m_playerLookup;
    std::unordered_map<uint32, ArenaGame> m_activeGames;

};

#define sPvPArenaSystem PvPArenaSystem::Instance()