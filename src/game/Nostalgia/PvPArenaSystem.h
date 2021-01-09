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
    
    EVENT_ARENA_ENDED,
    EVENT_ARENA_RESS,
    EVENT_ARENA_STARTS
};

struct PvPArena
{
    uint32 Id;
    ArenaType Type;
    float Radius;
    float Position_x;
    float Position_y;
	float Position_z;
    uint32 MapId;   
    std::array<Position, 3> TeamPositions;
    uint32 GateEntry;
    std::array<uint32, 2> GateGuids;
};

enum class ConfirmationStatus
{
    Blank = 0,
    Accepted,
    Declined
};

struct PartyInfo
{
    ObjectGuid LeaderGuid;
    std::vector<std::pair<ObjectGuid, ConfirmationStatus>> Group;
    ArenaType Type;
    bool WaitingConfirmation;
};


struct ArenaPlayer
{
    ArenaPlayer(ObjectGuid guid) : IsAlive(true), Guid(guid), Kills(0) {}
    ObjectGuid Guid;
    bool IsAlive;
    WorldLocation OldPosition;
    uint32 Kills;
};

enum class TeamOrder
{
    Team1,
    Team2
};

struct TeamInfo
{
    std::vector<ArenaPlayer> Group;
    ArenaType Type;
    TeamOrder Order;
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
    void PlayerDied(Player* killer, Player* killed, bool disconnected = false);
    void Update(uint32 diff);
    void EndGame(OutcomeResult result);
    void EventArenaActive();
    void ToggleDoors(bool open);
    void AddSpectator(Player* player);

    static void RestoreResources(Player* player);

private:
    OutcomeResult CheckOutcome(OutcomeCheck);
    void CheckEarlyConditions() { m_earlyConditionsCheck = true; }

    template <typename F>
    void DoForAllPlayers(F f)
    {
        for (auto& team : m_teams)
        {
            for (auto& arenaPlayer : team.Group)
            {
                f(arenaPlayer.Guid, team, arenaPlayer);
            }
        }
    }

    EventMap m_events;
    uint32 m_gameId;
    std::array<TeamInfo, 2> m_teams;
    std::vector<ArenaPlayer> m_specatators;
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

struct ConfirmationInfo
{
    PvPArena* Arena;
    uint32 WaitTime;
    std::array<PartyInfo*, 2> Parties;
};

enum class QueueResult
{
    Okay,
    NoGroup,
    MemberCount,
    NoLeader,
    AlreadyInQueue,
	ResSickness,
	BGSickness,
	AFK
};

struct ArenaTotal
{
    ArenaTotal() {}

    ArenaType Type;
    uint32 TotalKills;
    uint32 TotalDeaths;
    uint32 TotalWins;
    uint32 TotalLosses;
    uint32 TotalDraws;
    uint32 TotalGames;
};

struct ArenaStats
{
    ArenaStats() : PlayerLowGuid(0) {}

    uint32 PlayerLowGuid;
    std::unordered_map<ArenaType, ArenaTotal> Stats;
};

class PvPArenaSystem
{
    DECLARE_SINGLETON(PvPArenaSystem)
public:
    static const uint32 SenderId = 8916;
	static const uint32 CommandSenderId = 8917;
    static const uint32 ConfirmationSenderId = 7309;

    static const uint32 LeaveQueueAction = 9000;

    void LoadFromDB();
    void HandlePlayerRelocation(Player* player, const Position& newPos);
    void HandlePvPKill(Player* killer, Player* killed);
    void HandleWorldUpdate(uint32 diff);
    void HandleLogout(Player* player);
	//void HandleAFK(Player* player); // One day my sweet prince. One day.
    bool HandleRequestRepop(Player* player);
    bool HandleGroupInvite(Player* player);
    bool HandleGroupRemovePlayer(Player* player);

    QueueResult Queue(Player* player, ArenaType type);
    void SetupConfirmation(ConfirmationInfo* info);
    void ConfirmationReceived(Player* player, bool leave, uint32 arenaId, bool force = false);
    void StartGame(ConfirmationInfo* info);
    void AbortGame(ConfirmationInfo* info);
    void ScheduleQueueUpdate();
    void ArenaGameEnded(ArenaGame* game);
    void SaveStats(TeamInfo& playerTeam, ArenaPlayer& arenaPlayer, OutcomeResult result);

    void LeaveQueue(Player* player, bool disconnected = false);

    bool IsInQueue(Player* player);

    static std::string QueueResultToString(QueueResult result);

private:
    uint32 GenerateArenaId();
    PvPArena PickArenaTemplate(ArenaType type);

    std::unordered_multimap<ArenaType, std::reference_wrapper<PvPArena>> m_freeArenas; // all free arenas to play in at this moment per arena type
    std::unordered_multimap<ArenaType, PvPArena> m_arenas; // all available arenas from the template per arena type
    std::unordered_map<ObjectGuid, PartyInfo> m_queuedPlayers; // players that are queued, <leader guid, partyinfo>
    std::unordered_map<ObjectGuid, uint32> m_playerLookup; // players that are in an active arena game <player guid, arenaId>
    std::unordered_map<uint32, ArenaGame> m_activeGames; // active games going on <arenaId, ArenaGame>
    std::unordered_map<uint32, ConfirmationInfo> m_waitingConfirmation; //players waiting for confirmation for a game
    std::unordered_map<uint32, ArenaStats> m_playerStats; //arena stats per player <player LOW GUID, ArenaStats>
    std::unordered_set<uint32> m_requiredStatsUpdate; //set with lowGUID players of stats that require DB saving
    std::vector<uint32> m_deletedArenas; // arenas to be deleted by game id.

    std::recursive_mutex m_freeArenaLock;
    std::recursive_mutex m_lookupLock;
    std::recursive_mutex m_confirmationLock;
    std::recursive_mutex m_queueLock;
    std::recursive_mutex m_activeGamesLock;
    std::recursive_mutex m_deletedArenasLock;
    std::recursive_mutex m_statsLock;
    std::recursive_mutex m_requiredStatsLock;

    uint32 m_saveTimer = 300 * IN_MILLISECONDS;
};

#define sPvPArenaSystem PvPArenaSystem::Instance()