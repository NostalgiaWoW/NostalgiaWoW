#include "PvPArenaSystem.h"
#include "World.h"
#include "Group.h"
#include "Chat.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "SpellAuras.h"
#include <sstream>
#include <mutex>

#define AURA_ROOT 23973
#define START_FIREWORK0 1201200
#define START_FIREWORK1 1201201
#define START_FIREWORK2 1201202
#define START_FIREWORK3 1201203

template <typename Itr, typename F>
void DoForAll(Itr begin, Itr end, F f)
{
    while (begin != end)
    {
        f(begin);
        ++begin;
    }
}

void ArenaGame::Start()
{

	for (uint32 i = 0; i < 2; ++i)
	{
		auto& arenaTeam = m_teams[i];

		for (auto& arenaPlayer : arenaTeam.Group)
		{
			auto player = sObjectMgr.GetPlayer(arenaPlayer.Guid);

			if (player)
			{
				QueryResult* result = CharacterDatabase.PQuery("SELECT * FROM `character_aura` WHERE `guid` = %u", player->GetGUIDLow());

				do
				{
					if (result)
					{
						uint32 guid;
						uint32 spell;
						uint32 remaintime;
						BarGoLink bar(result->GetRowCount());

						bar.step();
						Field* fields = result->Fetch();

						guid = fields[0].GetInt32();
						//uint32 caster_guid = fields[1].GetInt32();
						//uint32 item_guid = fields[2].GetInt32();
						spell = fields[3].GetInt32();
						//uint32 stackcount = fields[4].GetInt32();
						//uint32 remaincharges = fields[5].GetInt32();
						//uint32 basepoints0 = fields[6].GetInt32();
						//uint32 basepoints1 = fields[7].GetInt32();
						//uint32 periodictime0 = fields[8].GetInt32();
						//uint32 periodictime1 = fields[9].GetInt32();
						//uint32 periodictime2 = fields[10].GetInt32();
						//uint32 maxduration = fields[11].GetInt32();
						remaintime = fields[12].GetInt32();
						//uint32 effIndexMask = fields[13].GetInt32();

						CharacterDatabase.PExecute("INSERT INTO `character_aura_saved` (`guid`, `spell`, `remaintime`) VALUES (%u, %u, %u)", guid, spell, remaintime);

						player->RemoveAurasDueToSpell(spell);
					}
					
				} while (result->NextRow());
				  delete result;
				}
			}
		}

	for (uint32 i = 0; i < 2; ++i)
	{
		auto& arenaTeam = m_teams[i];

		for (auto& arenaPlayer : arenaTeam.Group)
		{
			auto player = sObjectMgr.GetPlayer(arenaPlayer.Guid);
			float z_arena = m_map->GetHeight(m_arena->TeamPositions[i].x, m_arena->TeamPositions[i].y, m_arena->TeamPositions[i].z);
			if (player)
			{
				player->SaveRecallPosition();
				player->GetPosition(arenaPlayer.OldPosition);
				player->TeleportTo(m_arena->MapId, m_arena->TeamPositions[i].x, m_arena->TeamPositions[i].y, m_arena->TeamPositions[i].z, 0.0f);
				player->ScheduleGenericDelayedAction([](Player* target)
					{
						target->ApplyLegitReplenishment(true);
					});
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

            case EVENT_ARENA_RESS:
            {
                DoForAllPlayers([](ObjectGuid guid, const TeamInfo& playerTeam, const ArenaPlayer& arenaPlayer)
                    {
                        Player* player = sObjectMgr.GetPlayer(guid);
                        if (player)
                        {
                            if (player->isDead())
                                player->ResurrectPlayer(100.0f, false);
                            player->SetFFAPvP(false);
                        }
                    });
                m_events.ScheduleEvent(EVENT_ARENA_ENDED, 3000);
            }break;

            case EVENT_ARENA_ENDED:
            {
                {
                    DoForAllPlayers([](ObjectGuid guid, const TeamInfo& playerTeam, const ArenaPlayer& arenaPlayer)
                        {
                            Player* player = sObjectMgr.GetPlayer(guid);
                            if (player)
                            {
                                player->ScheduleGenericDelayedAction([](Player* target)
                                    {
                                        if (target->isDead())
                                            target->ResurrectPlayer(100.0f, false);
                                        target->ApplyLegitReplenishment(true);
                                        target->SetFFAPvP(false);
                                    });
                                player->TeleportTo(arenaPlayer.OldPosition);

								QueryResult* result = CharacterDatabase.PQuery("SELECT * FROM `character_aura_saved` WHERE `guid` = %u", player->GetGUIDLow());

								if (result)
								{
									uint32 guid;
									uint32 spell;
									uint32 remaintime;
									BarGoLink bar(result->GetRowCount());

									do
									{
										bar.step();
										Field* fields = result->Fetch();

										guid = fields[0].GetInt32();
										spell = fields[1].GetInt32();
										remaintime = fields[2].GetInt32();

										if (SpellAuraHolder* aura = player->AddAura(spell))
										{
											aura->SetAuraDuration(remaintime);
										}

									} while (result->NextRow());
									delete result;
								}
								
								QueryResult* delResult = CharacterDatabase.PQuery("SELECT * FROM `character_aura_saved` WHERE `guid` = %u", player->GetGUIDLow());

								if (delResult)
									CharacterDatabase.PExecute("DELETE FROM character_aura_saved WHERE guid = %u", player->GetGUIDLow());

								delete delResult;

                            }
                            else
                            {
                                WorldLocation loc = arenaPlayer.OldPosition;
                                Player::SavePositionInDB(guid, loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z, loc.orientation,
                                    sTerrainMgr.GetZoneId(loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z));
                            }
                        });


                    ToggleDoors(false);

                    m_events.Reset();

                    sPvPArenaSystem->ArenaGameEnded(this); // deletes `this`.
                }
            }break;

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


void ArenaGame::AddSpectator(Player* player)
{

}


void ArenaGame::EventArenaActive()
{
    DoForAllPlayers([](ObjectGuid playerGuid, const TeamInfo& playerTeam, const ArenaPlayer& arenaPlayer)
        {
            Player* player = sObjectMgr.GetPlayer(playerGuid);
			// Fireworks launching for start of arena. Could be put into an array but I'm lazy.
			Unit* firework = player->FindNearestCreature(START_FIREWORK0, 50);
			Unit* firework1 = player->FindNearestCreature(START_FIREWORK1, 200);
			Unit* firework2 = player->FindNearestCreature(START_FIREWORK2, 200);
			Unit* firework3 = player->FindNearestCreature(START_FIREWORK3, 200);


            if (player)
            {
				if (firework)
					firework->CastSpell(firework, 11542, true);
				if (firework1)
					firework1->CastSpell(firework1, 11542, true);
				if (firework2)
					firework2->CastSpell(firework2, 11542, true);
				if (firework3)
					firework3->CastSpell(firework3, 11542, true);
               
				player->RemoveAurasDueToSpell(AURA_ROOT);
                player->ApplyLegitReplenishment(true);
                player->GetSession()->SendAreaTriggerMessage("Arena Started!");
                player->SetFFAPvP(true);
            }

        });


    ToggleDoors(true);

    m_status = ArenaStatus::Active;
    if (m_earlyConditionsCheck) // someone went offline in wait time, maybe its a won game already.
        CheckWin();
}

void ArenaGame::ToggleDoors(bool open)
{
    Map* map = sMapMgr.FindMap(m_arena->MapId);
    if (map)
    {
        auto gate1 = map->GetGameObject(ObjectGuid{ HIGHGUID_GAMEOBJECT, m_arena->GateEntry, m_arena->GateGuids[0] });

        if (gate1)
            open ? gate1->UseDoorOrButton() : gate1->ResetDoorOrButton();

        auto gate2 = map->GetGameObject(ObjectGuid{ HIGHGUID_GAMEOBJECT, m_arena->GateEntry, m_arena->GateGuids[1] });
        if (gate2)
            open ? gate2->UseDoorOrButton() : gate2->ResetDoorOrButton();
    }
}

void ArenaGame::CheckWin()
{
    auto result = CheckOutcome(OutcomeCheck::Kill);

    if (result == OutcomeResult::NoWinner)
        return;

    EndGame(result);
}

void ArenaGame::PlayerDied(Player* killer, Player* killed, bool disconnected)
{
    std::ostringstream ss;
    ss << killed->GetName();
    ss << (disconnected ? " disconnected." : " died.");
    std::string message = ss.str();

    bool found = false;
    for (auto& arenaTeam : m_teams)
    {
        for (auto& arenaPlayer : arenaTeam.Group)
        {
            if (killer->GetObjectGuid() == arenaPlayer.Guid && !disconnected)
                ++arenaPlayer.Kills;

            if (killed->GetObjectGuid() == arenaPlayer.Guid)
            {
                arenaPlayer.IsAlive = false;
                found = true;

                if (disconnected)
                    continue;
            }
            
            ChatHandler(sObjectMgr.GetPlayer(arenaPlayer.Guid)).SendSysMessage(message.c_str());
        }
    }

    CheckWin();
}

void ArenaGame::EndGame(OutcomeResult result)
{

	const auto& team1 = m_teams[0];
	const auto& team2 = m_teams[1];

	if (result == OutcomeResult::Team1Wins)
	{
		sWorld.SendServerMessage(SERVER_MSG_CUSTOM, "Team 1 won!");

		for (const auto& arenaPlayer : team1.Group) // Rewards for winner
		{
			auto player = sObjectMgr.GetPlayer(arenaPlayer.Guid);
			player->AddItem(80000, 1);
			player->AddItem(80001, 4);
			player->AddItem(80004, 1);
			break;
		}

		for (const auto& arenaPlayer : team2.Group) // Rewards for loser
		{
			auto player = sObjectMgr.GetPlayer(arenaPlayer.Guid);
			player->AddItem(80001, 2);
			break;
		}

	}
	else if (result == OutcomeResult::Team2Wins)
	{
		sWorld.SendServerMessage(SERVER_MSG_CUSTOM, "Team 2 won!");

		for (const auto& arenaPlayer : team2.Group) // Rewards for winner
		{
			auto player = sObjectMgr.GetPlayer(arenaPlayer.Guid);
			player->AddItem(80000, 1);
			player->AddItem(80001, 4);
			player->AddItem(80004, 1);
			break;
		}

		for (const auto& arenaPlayer : team1.Group) // Rewards for loser
		{
			auto player = sObjectMgr.GetPlayer(arenaPlayer.Guid);
			player->AddItem(80001, 2);
			break;
		}
	}
	
    {

        DoForAllPlayers([result](ObjectGuid playerGuid, TeamInfo& playerTeam, ArenaPlayer& arenaPlayer)
            {
                sPvPArenaSystem->SaveStats(playerTeam, arenaPlayer, result);
            });

    }
    //schedule teleport event later after ress otherwise client will bug out.
    m_events.ScheduleEvent(EVENT_ARENA_RESS, 2000);
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
        PvPArena arena = { fields[0].GetUInt32(), static_cast<ArenaType>(fields[1].GetUInt32()), fields[2].GetFloat(), fields[3].GetFloat(), fields[4].GetFloat(), fields[5].GetFloat(), fields[6].GetUInt32(),
            {  Position({fields[7].GetFloat(), fields[8].GetFloat(), fields[9].GetFloat() , 0.0f}), Position({fields[10].GetFloat(), fields[11].GetFloat(), fields[12].GetFloat(), 0.0f})   },
            fields[13].GetUInt32(), {fields[14].GetUInt32(), fields[15].GetUInt32()} };
        auto res = m_arenas.insert({ arena.Type, std::move(arena) });
        m_freeArenas.insert({ res->first, std::ref(res->second) });
    } while (result->NextRow());

    result = WorldDatabase.QuerySafe("SELECT PlayerLowGuid, ArenaType, SUM(Kills), SUM(Died), SUM(Won), SUM(Lost), COUNT(*) FROM `pvp_arena_system_stats` GROUP BY PlayerLowGuid, ArenaType");

    if (!result)
        return;

    uint32 lastGuid = 0;

    ArenaStats tempStats;
    do {
        auto fields = result->Fetch();

        
        ArenaTotal total;
        uint32 playerLowGuid = fields[0].GetUInt32();


        if (!lastGuid)
            lastGuid = playerLowGuid;

        if (lastGuid != playerLowGuid) // new player, save what we have for arenatypes in a bigger container and continue.
        {
            tempStats.PlayerLowGuid = lastGuid;
            m_playerStats.insert({ lastGuid, tempStats });
            tempStats.Stats.clear();
        }

        total.Type = (ArenaType)fields[1].GetUInt8();
        total.TotalKills = fields[2].GetUInt32();
        total.TotalDeaths = fields[3].GetUInt32();
        total.TotalWins = fields[4].GetUInt32();
        total.TotalLosses = fields[5].GetUInt32();
        total.TotalGames = fields[6].GetUInt32();
        tempStats.Stats[total.Type] = total;
    } while (result->NextRow());

    //dont forget last tempstats save.
    tempStats.PlayerLowGuid = lastGuid;
    m_playerStats.insert({ lastGuid, tempStats });
    tempStats.Stats.clear();
}

void PvPArenaSystem::SaveStats(TeamInfo& playerTeam, ArenaPlayer& arenaPlayer, OutcomeResult result)
{
    std::lock_guard<std::recursive_mutex> g(m_statsLock);

    auto& elem = m_playerStats[arenaPlayer.Guid.GetCounter()].Stats[playerTeam.Type];

    if (!arenaPlayer.IsAlive)
        ++elem.TotalDeaths;


    bool won = (playerTeam.Order == TeamOrder::Team1 && result == OutcomeResult::Team1Wins) || (playerTeam.Order == TeamOrder::Team2 && result == OutcomeResult::Team2Wins);
    bool draw = result == OutcomeResult::Draw;

    if (draw)
        ++elem.TotalDraws;
    else if (won)
        ++elem.TotalWins;
    else
        ++elem.TotalLosses;

    elem.TotalKills += arenaPlayer.Kills;
    ++elem.TotalGames;

    //now mark for update to DB.
    WorldDatabase.PExecute("INSERT INTO `pvp_arena_system_stats` (`PlayerLowGuid`, `ArenaType`, `Kills`, `Died`, `Won`, `Lost`) VALUES(%u, %u, %u, %u, %u, %u)",
        arenaPlayer.Guid.GetCounter(), (uint32)playerTeam.Type, arenaPlayer.Kills, arenaPlayer.IsAlive ? 0 : 1, won ? 1 : 0, !won && !draw ? 1 : 0);
}

void PvPArenaSystem::ArenaGameEnded(ArenaGame* game)
{
    //add a new free arena, remove players from active game, remove active game and schedule a new queue update for potential players.

    std::lock_guard<std::recursive_mutex> g(m_freeArenaLock);
    std::lock_guard<std::recursive_mutex> g3(m_lookupLock);
    std::lock_guard<std::recursive_mutex> g2(m_deletedArenasLock);

    m_freeArenas.insert({ game->m_arena->Type, std::ref(*game->m_arena) });

    game->DoForAllPlayers([this](ObjectGuid guid, const TeamInfo& playerTeam, const ArenaPlayer& arenaPlayer)
        {
            m_playerLookup.erase(guid);
        });

    m_deletedArenas.push_back(game->m_gameId);
}

bool PvPArenaSystem::IsInQueue(Player* player)
{
    auto guid = player->GetGroup() ? player->GetGroup()->GetLeaderGuid() : player->GetObjectGuid();

    std::lock_guard<std::recursive_mutex> g(m_queueLock);
    return m_queuedPlayers.find(guid) != m_queuedPlayers.end();
}

void PvPArenaSystem::HandlePlayerRelocation(Player* player, const Position& newPos)
{
}

void PvPArenaSystem::HandleLogout(Player* player)
{
    {
        std::lock_guard<std::recursive_mutex> g(m_lookupLock);
        auto itr = m_playerLookup.find(player->GetObjectGuid());

        if (itr != m_playerLookup.end())
        {
            std::lock_guard<std::recursive_mutex> g(m_activeGamesLock);
            auto arenaItr = m_activeGames.find(itr->second);
            if (arenaItr != m_activeGames.end())
            {
                arenaItr->second.PlayerDied(player, player, true); //kill logged out player
                return;
            }
        }
    }

    LeaveQueue(player, true);

}

void PvPArenaSystem::LeaveQueue(Player* player, bool disconnected)
{
    auto guid = player->GetObjectGuid();
    if (player->GetGroup())
        guid = player->GetGroup()->GetLeaderGuid();

    std::ostringstream ss;
    ss << "Left queue because " << player->GetName()
        << disconnected ? " disconnected." : " left.";

    std::string message = ss.str();

    std::lock_guard<std::recursive_mutex> g(m_queueLock);
    auto leaderGuid = guid;
    auto itr = m_queuedPlayers.find(leaderGuid);

    if (itr != m_queuedPlayers.end())
    {
        DoForAll(itr->second.Group.begin(), itr->second.Group.end(), [player, &message, disconnected](decltype(itr->second.Group)::iterator itr)
            {
                if (itr->first == player->GetObjectGuid() && disconnected)
                    return;

                Player* member = sObjectMgr.GetPlayer(itr->first);
                if (member)
                    ChatHandler(member).SendSysMessage(message.c_str());
            });

        if (itr->second.WaitingConfirmation)
        {
            //search confimation container too..
            std::lock_guard<std::recursive_mutex> g(m_confirmationLock);
            auto foundItr = std::find_if(m_waitingConfirmation.begin(), m_waitingConfirmation.end(), [leaderGuid](const decltype(m_waitingConfirmation)::value_type& val)
                {
                    return val.second.Parties[0]->LeaderGuid == leaderGuid || val.second.Parties[1]->LeaderGuid == leaderGuid;
                });

            if (foundItr != m_waitingConfirmation.end())
                ConfirmationReceived(player, true, foundItr->first, true); // emulate a decline from the logged out player, this will destroy the confirmationinfo too.
        }
        else
            m_queuedPlayers.erase(itr); // queuedplayers is erased in ConfirmationReceived -> AbortGame if it goes through, so else-only.
    }
}


bool PvPArenaSystem::HandleGroupInvite(Player* player)
{
    {
        std::lock_guard<std::recursive_mutex> g(m_lookupLock);
        auto itr = m_playerLookup.find(player->GetObjectGuid());
        if (itr != m_playerLookup.end())
        {
            player->GetSession()->SendNotification("You can\'t invite someone in the arena.");
            return false; //cant invite in arena.
        }
    }

    {
        std::lock_guard<std::recursive_mutex> g(m_queueLock);
        auto itr = m_queuedPlayers.find(player->GetObjectGuid());
        if (itr != m_queuedPlayers.end())
        {
            player->GetSession()->SendNotification("You can\'t invite someone in the arena queue.");
            return false; //cant invite in queue.
        }
    }
    return true;
}

bool PvPArenaSystem::HandleGroupRemovePlayer(Player* player)
{
    {
        std::lock_guard<std::recursive_mutex> g(m_lookupLock);
        auto itr = m_playerLookup.find(player->GetObjectGuid());
        if (itr != m_playerLookup.end())
        {
            player->GetSession()->SendNotification("You can\'t remove someone in the arena.");
            return false; //cant invite in arena.
        }
    }

    {
        std::lock_guard<std::recursive_mutex> g(m_queueLock);
        auto itr = m_queuedPlayers.find(player->GetObjectGuid());
        if (itr != m_queuedPlayers.end())
        {
            player->GetSession()->SendNotification("You can\'t remove someone in the arena queue.");
            return false; //cant invite in queue.
        }
    }
    return true;
}

bool PvPArenaSystem::HandleRequestRepop(Player* player)
{
    std::lock_guard<std::recursive_mutex> g(m_lookupLock);
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
    bool arenasRemoved = !m_deletedArenas.empty();
    {
        if (arenasRemoved)
        {
            std::lock_guard<std::recursive_mutex> g2(m_deletedArenasLock);
            m_activeGamesLock.lock();
            for (auto arenaId : m_deletedArenas)
            {
                m_activeGames.erase(arenaId);
            }
            m_activeGamesLock.unlock();
        }
    }

    {
        std::lock_guard<std::recursive_mutex> g2(m_activeGamesLock);
        for (auto& arenaPair : m_activeGames)
        {
            arenaPair.second.Update(diff);
        }
    }

    if (arenasRemoved)
        ScheduleQueueUpdate();
}

void PvPArenaSystem::HandlePvPKill(Player* killer, Player* killed)
{
    std::lock_guard<std::recursive_mutex> g(m_lookupLock);
    std::lock_guard<std::recursive_mutex> g2(m_activeGamesLock);
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
    game->PlayerDied(killer, killed);
}

QueueResult PvPArenaSystem::Queue(Player* player, ArenaType type)
{
    {
        std::lock_guard<std::recursive_mutex> g(m_lookupLock);
        std::lock_guard<std::recursive_mutex> g2(m_queueLock);
        auto itr = m_queuedPlayers.find(player->GetObjectGuid());

        if (itr != m_queuedPlayers.end())
            return QueueResult::AlreadyInQueue;

        auto lookupItr = m_playerLookup.find(player->GetObjectGuid());
        if (lookupItr != m_playerLookup.end())
            return QueueResult::AlreadyInQueue;
    }

    PartyInfo info;
    info.LeaderGuid = player->GetObjectGuid();
    info.Type = type;
    info.WaitingConfirmation = false;

	if (type == ArenaType::OnePlayer && player->HasAura(15007))
		return QueueResult::ResSickness;

    if (type != ArenaType::OnePlayer)
    {
        if (!player->GetGroup())
            return QueueResult::NoGroup;

		if (player->HasAura(15007))
			return QueueResult::ResSickness;

        auto group = player->GetGroup();

        if (player->GetObjectGuid() != group->GetLeaderGuid())
            return QueueResult::NoLeader;

        if (group->GetMembersCount() != (int)type)
            return QueueResult::MemberCount;

        for (auto itr = group->GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            info.Group.push_back({ itr->getSource()->GetObjectGuid(), ConfirmationStatus::Blank });
            ChatHandler(itr->getSource()).SendSysMessage("Queued.");
        }
    }
    else
    {
        info.Group.push_back({ player->GetObjectGuid(), ConfirmationStatus::Blank });
        ChatHandler(player).SendSysMessage("Queued.");
    }

    m_queuedPlayers.insert({ info.LeaderGuid, info });
    ScheduleQueueUpdate();
    return QueueResult::Okay;
}

void PvPArenaSystem::SetupConfirmation(ConfirmationInfo* info)
{
    for (const auto& party : info->Parties)
    {
        for (const auto& guidPair : party->Group)
        {
            auto player = sObjectMgr.GetPlayer(guidPair.first);
            if (player)
            {
                player->PlayerTalkClass->CloseGossip();
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I\'m ready", ConfirmationSenderId, info->Arena->Id);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Leave queue", ConfirmationSenderId,
                    LeaveQueueAction + info->Arena->Id);
                player->SEND_GOSSIP_MENU(907, player->GetGUID());
            }
        }
    }
}

void PvPArenaSystem::ConfirmationReceived(Player* player, bool leave, uint32 arenaId, bool force)
{
    ConfirmationInfo* info = nullptr;
    {
        std::lock_guard<std::recursive_mutex> g(m_confirmationLock);
        auto confirmationItr = m_waitingConfirmation.find(arenaId);
        if (confirmationItr == m_waitingConfirmation.end())
            return;
        info = &confirmationItr->second;
    }

    bool found = false;
    for (const auto& party : info->Parties)
    {
        for (auto& partyPair : party->Group)
        {
            if (partyPair.first == player->GetObjectGuid())
            {
                if (partyPair.second == ConfirmationStatus::Blank || force)
                {
                    found = true;
                    partyPair.second = leave ? ConfirmationStatus::Declined : ConfirmationStatus::Accepted;
                    break;
                }
            }
        }
    }

    if (!found) // cheating, doesnt belong to team or already accepted
        return;

    if (leave)
        AbortGame(info);
    else
    {
        //check if all parties have accepted, if so, start the game.
        bool allAccepted = std::all_of(info->Parties.begin(), info->Parties.end(), [](PartyInfo* info)
            {
                return std::all_of(info->Group.begin(), info->Group.end(), [](decltype(PartyInfo::Group)::value_type elem)
                    {
                        auto player = sObjectMgr.GetPlayer(elem.first);
                        if (player)
                            ChatHandler(player).SendSysMessage("Player Accepted.");

                        return elem.second == ConfirmationStatus::Accepted;
                    });
            });


        if (allAccepted)
            StartGame(info);
    }
}

void PvPArenaSystem::StartGame(ConfirmationInfo* info)
{
    //remove from confirmationwait queue, remove players from queue, add to player lookup and init new arenagame.

    PvPArena* arena = info->Arena;

    uint32 id = GenerateArenaId();
    std::vector<ArenaPlayer> players1;
    std::vector<ArenaPlayer> players2;

    int32 k = 0;
    {
        std::lock_guard<std::recursive_mutex> g(m_queueLock);

        for (const auto& party : info->Parties)
        {
            for (const auto& playerGuid : party->Group)
            {
                k == 0 ? players1.push_back(playerGuid.first) : players2.push_back(playerGuid.first);
                m_playerLookup.insert({ playerGuid.first, id });
            }
            ++k;
            m_queuedPlayers.erase(party->LeaderGuid);
        }
    }

    std::lock_guard<std::recursive_mutex> g(m_activeGamesLock);
    m_activeGames.insert({ id, ArenaGame{ id, arena, TeamInfo { std::move(players1), arena->Type, TeamOrder::Team1}, TeamInfo { std::move(players2), arena->Type, TeamOrder::Team2} } });
    m_activeGames[id].Start();

	{
		std::lock_guard<std::recursive_mutex> g(m_confirmationLock);
		m_waitingConfirmation.erase(arena->Id);
	}

}

void PvPArenaSystem::AbortGame(ConfirmationInfo* info)
{
    PvPArena* arena = info->Arena;

    //re-add arena into free arenas, remove players from queue, remove from confirmationwait queue, schedule queue update

    {
        std::lock_guard<std::recursive_mutex> g(m_freeArenaLock);
        m_freeArenas.insert({ arena->Type, std::ref(*arena) });
    }


    //first remove waitingconfirmation, otherwise ::Parties would be dangling.
    {
        std::lock_guard<std::recursive_mutex> g(m_confirmationLock);
        m_waitingConfirmation.erase(arena->Id);
    }

    //only remove the party of the declinees
    {
        std::lock_guard<std::recursive_mutex> g(m_queueLock);
        for (auto& party : info->Parties)
        {
            if (std::any_of(party->Group.begin(), party->Group.end(), [](decltype(PartyInfo::Group)::value_type elem)
                {
                    return elem.second == ConfirmationStatus::Declined;
                }))
            {
                m_queuedPlayers.erase(party->LeaderGuid);
            }
            else
            {
                //else remove waitingconfirmation so the party can be requeued.
                party->WaitingConfirmation = false;
                
                //and remove confirmationstatus
                for (auto& partyMember : party->Group)
                {
                    partyMember.second = ConfirmationStatus::Blank;
                }
            }
        }
    }

    ScheduleQueueUpdate(); // and off we go
}


void PvPArenaSystem::ScheduleQueueUpdate()
{
    std::lock_guard<std::recursive_mutex> g(m_queueLock);
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
                if (!info->second.WaitingConfirmation)
                {
                    teamInfo1 = &info->second;
                    team1Itr = info;
                }
            }
            else if (!teamInfo2)
            {
                if (!info->second.WaitingConfirmation)
                {
                    teamInfo2 = &info->second;
                    team2Itr = info;
                }
            }

            if (teamInfo1 && teamInfo2)
            {
                //Try to start a game. First check if there are any free arenas.
                std::lock_guard<std::recursive_mutex> g2(m_freeArenaLock);
                auto itr = m_freeArenas.find(typePair.first);
                if (itr == m_freeArenas.end())
                {
                    arenasFull = true;
                    break;
                }

                //setup the confirmation for game first.
                team1Itr->second.WaitingConfirmation = true;
                team2Itr->second.WaitingConfirmation = true;

                auto res = m_waitingConfirmation.insert({ itr->second.get().Id, ConfirmationInfo{&itr->second.get(),
                     30 * IN_MILLISECONDS,
                    {teamInfo1, teamInfo2}} });
                m_freeArenas.erase(itr);

                SetupConfirmation(&res.first->second);


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
	case QueueResult::ResSickness:
		return "You cannot queue while you have Resurrection Sickness";
    default:
        return "Error";
    }

    return "No.";
}