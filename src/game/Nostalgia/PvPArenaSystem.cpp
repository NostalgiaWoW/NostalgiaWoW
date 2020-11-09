#include "PvPArenaSystem.h"
#include "World.h"
#include "Group.h"
#include "Chat.h"

#define AURA_ROOT 23973

void ArenaGame::Start()
{
    for (uint32 i = 0; i < 2; ++i)
    {
        auto& arenaTeam = m_teams[i];
        for (auto& arenaPlayer : arenaTeam.Group)
        {
            auto player = sObjectMgr.GetPlayer(arenaPlayer.Guid);
            float z_arena = m_map->GetHeight(m_arena->TeamPositions[i].x, m_arena->TeamPositions[i].y, 0.0f);
            if (player)
            {
                //player->SetWorldMask(i * 2 + 2); // team 0, phasemask 2, team 1, phasemask 4.
                player->SaveRecallPosition();
                player->GetPosition(arenaPlayer.OldPosition);
                player->AddAura(AURA_ROOT);
                player->TeleportTo(m_arena->MapId, m_arena->TeamPositions[i].x, m_arena->TeamPositions[i].y, z_arena, 0.0f);
                player->ApplyLegitReplenishment(true);
            }
            else
            {
                //offline in queue.
                arenaPlayer.IsAlive = false;
                CheckEarlyConditions();
            }
        }
    }
    m_status = ArenaStatus::Starting;
    m_events.ScheduleEvent(EVENT_ARENA_STARTING_IN_30, 5000);
}

void ArenaGame::Update(uint32 diff)
{
    m_events.Update(diff);

    static std::unordered_map<uint32, uint32> timingLookup =
    {
        {EVENT_ARENA_STARTING_IN_1, 1},
        {EVENT_ARENA_STARTING_IN_2, 1},
        {EVENT_ARENA_STARTING_IN_3, 1},
        {EVENT_ARENA_STARTING_IN_4, 1},
        {EVENT_ARENA_STARTING_IN_5, 1},
        {EVENT_ARENA_STARTING_IN_15, 10},
        {EVENT_ARENA_STARTING_IN_30, 15}
    };

    while (uint32 eventId = m_events.ExecuteEvent())
    {
        switch (eventId)
        {
            case EVENT_ARENA_STARTS:
            {
                EventArenaActive();
            } break;

            case EVENT_ARENA_STARTING_IN_1:
            case EVENT_ARENA_STARTING_IN_2:
            case EVENT_ARENA_STARTING_IN_3:
            case EVENT_ARENA_STARTING_IN_4:
            case EVENT_ARENA_STARTING_IN_5:
            case EVENT_ARENA_STARTING_IN_15:
            case EVENT_ARENA_STARTING_IN_30:
            {
                auto& timeout = timingLookup[eventId];
                uint32 nextEvent = eventId - timeout;

                DoForAllPlayers([eventId](ObjectGuid playerGuid, const TeamInfo& playerTeam, const ArenaPlayer& arenaPlayer)
                    {
                        Player* player = sObjectMgr.GetPlayer(playerGuid);
                        if (player)
                            ChatHandler(player).PSendSysMessage("Arena starting in %u second(s).", eventId);
                    });

                if (eventId == EVENT_ARENA_STARTING_IN_1)
                    m_events.ScheduleEvent(EVENT_ARENA_STARTS, 1 * IN_MILLISECONDS);
                else
                    m_events.ScheduleEvent(nextEvent, timeout * IN_MILLISECONDS);
            } break;
        }
    }
}

void ArenaGame::EventArenaActive()
{
    DoForAllPlayers([](ObjectGuid playerGuid, const TeamInfo& playerTeam, const ArenaPlayer& arenaPlayer)
        {
            Player* player = sObjectMgr.GetPlayer(playerGuid);
            if (player)
            {
                player->RemoveAurasDueToSpell(AURA_ROOT);
                player->ApplyLegitReplenishment(true);
                player->GetSession()->SendAreaTriggerMessage("Arena Started!");
                player->SetFFAPvP(true);
            }
        });

    m_status = ArenaStatus::Active;
    if (m_earlyConditionsCheck) // someone went offline in wait time, maybe its a won game already.
        CheckWin();
}

void ArenaGame::CheckWin()
{
    auto result = CheckOutcome(OutcomeCheck::Kill);

    if (result == OutcomeResult::NoWinner)
        return;

    EndGame(result);
}

void ArenaGame::PlayerDied(Player* player)
{
    bool found = false;
    for (auto& arenaTeam : m_teams)
    {
        for (auto& arenaPlayer : arenaTeam.Group)
        {
            if (player->GetObjectGuid() == arenaPlayer.Guid)
            {
                arenaPlayer.IsAlive = false;
                found = true;
                break;
            }

            if (found)
                break;
        }
    }

    CheckWin();
}

void ArenaGame::EndGame(OutcomeResult result)
{
    if (result == OutcomeResult::Team1Wins)
        sWorld.SendServerMessage(SERVER_MSG_CUSTOM, "Team 1 won!");
    else if (result == OutcomeResult::Team2Wins)
        sWorld.SendServerMessage(SERVER_MSG_CUSTOM, "Team 2 won!");


    DoForAllPlayers([](ObjectGuid guid, const TeamInfo& playerTeam, const ArenaPlayer& arenaPlayer)
        {
            Player* player = sObjectMgr.GetPlayer(guid);
            if (player)
            {
                if (player->isDead())
                    player->ResurrectPlayer(100.0f, false);
                player->ApplyLegitReplenishment(true);
                player->TeleportTo(arenaPlayer.OldPosition);
                player->SetFFAPvP(false);
            }
            else
            {
                WorldLocation loc = arenaPlayer.OldPosition;
                Player::SavePositionInDB(guid, loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z, loc.orientation,
                    sTerrainMgr.GetZoneId(loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z));
            }
        });

    sPvPArenaSystem->ArenaGameEnded(this);
}

void ArenaGame::RestoreResources(Player* player)
{
    player->ApplyLegitReplenishment(true);
}

OutcomeResult ArenaGame::CheckOutcome(OutcomeCheck check)
{
    bool checkKills = check == OutcomeCheck::Both || check == OutcomeCheck::Kill;
    bool checkTime = check == OutcomeCheck::Both || check == OutcomeCheck::Time;

    if (checkKills)
    {
        const auto& team1 = m_teams[0];
        const auto& team2 = m_teams[1];

        bool team1Dead = true;
        bool team2Dead = true;

        for (const auto& arenaPlayer : team1.Group)
        {
            auto player = sObjectMgr.GetPlayer(arenaPlayer.Guid);
            if (player && player->IsInWorld() && arenaPlayer.IsAlive)
            {
                team1Dead = false;
                break;
            }
        }

        for (const auto& arenaPlayer : team2.Group)
        {
            auto player = sObjectMgr.GetPlayer(arenaPlayer.Guid);
            if (player && player->IsInWorld() && arenaPlayer.IsAlive)
            {
                team2Dead = false;
                break;
            }
        }

        if (team1Dead)
            return OutcomeResult::Team2Wins;

        if (team2Dead)
            return OutcomeResult::Team1Wins;

    }

    return OutcomeResult::NoWinner;
}

void PvPArenaSystem::LoadFromDB()
{
    auto result = WorldDatabase.QuerySafe("SELECT * FROM `pvp_arena_system`");

    if (!result)
        return;

    do {
        auto fields = result->Fetch();
        PvPArena arena = { fields[0].GetUInt32(), static_cast<ArenaType>(fields[1].GetUInt32()), fields[2].GetFloat(), fields[3].GetFloat(), fields[4].GetFloat(), fields[5].GetUInt32(),
            {  Position({fields[6].GetFloat(), fields[7].GetFloat(), 0.0f, 0.0f}), Position({fields[8].GetFloat(), fields[9].GetFloat(), 0.0f, 0.0f})   } };        
        auto res = m_arenas.insert({ arena.Type, std::move(arena) });
        m_freeArenas.insert({ res->first, std::ref(res->second) });
    } while (result->NextRow());
}

void PvPArenaSystem::ArenaGameEnded(ArenaGame* game)
{
    //add a new free arena, remove players from active game, remove active game and schedule a new queue update for potential players.

    m_freeArenas.insert({ game->m_arena->Type, std::ref(*game->m_arena) });

    game->DoForAllPlayers([this](ObjectGuid guid, const TeamInfo& playerTeam, const ArenaPlayer& arenaPlayer)
        {
            m_playerLookup.erase(guid);
        });

    m_activeGames.erase(game->m_gameId);

    ScheduleQueueUpdate();
}

void PvPArenaSystem::HandlePlayerRelocation(Player* player, const Position& newPos)
{

}

bool PvPArenaSystem::HandleRequestRepop(Player* player)
{
    auto itr = m_playerLookup.find(player->GetObjectGuid());
    if (itr != m_playerLookup.end())
    {
        player->GetSession()->SendNotification("You can\'t reclaim your corpse in an arena");
        return false;
    }
    return true;
}

void PvPArenaSystem::HandleWorldUpdate(uint32 diff)
{
    for (auto& arenaPair : m_activeGames)
    {
        arenaPair.second.Update(diff);
    }
}

void PvPArenaSystem::HandlePvPKill(Player* killer, Player* killed)
{
    auto killerItr = m_playerLookup.find(killer->GetObjectGuid());

    if (killerItr == m_playerLookup.end())
        return;

    auto killedItr = m_playerLookup.find(killed->GetObjectGuid());

    if (killedItr == m_playerLookup.end())
        return;

    auto killerGameItr = m_activeGames.find(killerItr->second);
    auto killedGameItr = m_activeGames.find(killedItr->second);

    if (killerGameItr == m_activeGames.end() || killedGameItr == m_activeGames.end())
        return;

    if (killerGameItr->second.m_gameId != killedGameItr->second.m_gameId)
        return;


    ArenaGame* game = &killerGameItr->second;
    game->PlayerDied(killed);
}

QueueResult PvPArenaSystem::Queue(Player* player, ArenaType type)
{
    auto itr = m_queuedPlayers.find(player->GetObjectGuid());

    if (itr != m_queuedPlayers.end())
        return QueueResult::AlreadyInQueue;

    auto lookupItr = m_playerLookup.find(player->GetObjectGuid());
    if (lookupItr != m_playerLookup.end())
        return QueueResult::AlreadyInQueue;

    PartyInfo info;
    info.LeaderGuid = player->GetObjectGuid();
    info.Type = type;

    if (type != ArenaType::OnePlayer)
    {
        if (!player->GetGroup())
            return QueueResult::NoGroup;

        auto group = player->GetGroup();

        if (player->GetObjectGuid() != group->GetLeaderGuid())
            return QueueResult::NoLeader;

        if (group->GetMembersCount() != (int)type)
            return QueueResult::MemberCount;

        for (auto itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            info.Group.push_back(itr->getSource()->GetObjectGuid());
            ChatHandler(itr->getSource()).SendSysMessage("Queued.");
        }
    }
    else
    {
        info.Group.push_back(player->GetObjectGuid());
        ChatHandler(player).SendSysMessage("Queued.");
    }

    m_queuedPlayers.insert({ info.LeaderGuid, info });
    ScheduleQueueUpdate();
    return QueueResult::Okay;
}

void PvPArenaSystem::ScheduleQueueUpdate()
{


    std::unordered_map<ArenaType, std::vector<decltype(m_queuedPlayers)::iterator>> queuedPlayers;

    for (auto itr = m_queuedPlayers.begin(); itr != m_queuedPlayers.end(); ++itr)
    {
        queuedPlayers[itr->second.Type].push_back(itr);
    }

    for (auto& typePair : queuedPlayers)
    {
        PartyInfo* teamInfo1 = nullptr;
        PartyInfo* teamInfo2 = nullptr;
        decltype(m_queuedPlayers)::iterator team1Itr, team2Itr;

        bool arenasFull = false;

        for (const auto& info : typePair.second)
        {
            if (!teamInfo1)
            {
                teamInfo1 = &info->second;
                team1Itr = info;
            }
            else if (!teamInfo2)
            {
                teamInfo2 = &info->second;
                team2Itr = info;
            }

            if (teamInfo1 && teamInfo2)
            {
                //Try to start a game. First check if there are any free arenas.
                auto itr = m_freeArenas.find(typePair.first);
                if (itr == m_freeArenas.end())
                {
                    arenasFull = true;
                    break;
                }

                uint32 id = GenerateArenaId();

                TeamInfo team1;
                team1.Type = typePair.first;
                std::vector<ArenaPlayer> players1;
                for (const auto& plr : teamInfo1->Group)
                {
                    players1.push_back(plr);
                    m_playerLookup.insert({ plr, id });
                }

                std::vector<ArenaPlayer> players2;
                for (const auto& plr : teamInfo2->Group)
                {
                    players2.push_back(plr);
                    m_playerLookup.insert({ plr, id });
                }

                m_queuedPlayers.erase(team1Itr);
                m_queuedPlayers.erase(team2Itr);


                m_activeGames.insert({ id, ArenaGame{ id, &itr->second.get(), TeamInfo { players1, typePair.first}, TeamInfo {players2, typePair.first} }  });
                m_freeArenas.erase(itr);
                m_activeGames[id].Start();

                teamInfo1 = nullptr;
                teamInfo2 = nullptr;
            }
        }
    }
}

uint32 PvPArenaSystem::GenerateArenaId()
{
    static uint32 arenaId = 0;
    return ++arenaId;
}

PvPArena PvPArenaSystem::PickArenaTemplate(ArenaType type)
{
    auto itrPair = m_arenas.equal_range(type);
    std::vector<std::pair<const ArenaType, PvPArena>> arenas{ itrPair.first, itrPair.second };
    return arenas[urand(0, m_arenas.size() - 1)].second;
}


std::string PvPArenaSystem::QueueResultToString(QueueResult result)
{
    switch (result)
    {
    case QueueResult::Okay:
        return "Queued";
    case QueueResult::NoGroup:
        return "You\'re not in a group";
    case QueueResult::NoLeader:
        return "You\'re not the leader of your group";
    case QueueResult::AlreadyInQueue:
        return "You\'re already in queue";
    case QueueResult::MemberCount:
        return "Your group doesn\'t match the required members for this queue";
    default:
        return "Error";
    }

    return "No.";
}