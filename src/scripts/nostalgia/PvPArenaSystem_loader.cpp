#include "scriptPCH.h"
#include "Nostalgia/PvPArenaSystem.h"
#include "Chat.h"

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


bool OnPlayerGossipSelect_Command(Player* player, Player* otherPlayer, uint32 sender, uint32 action)
{

	if (sender != PvPArenaSystem::CommandSenderId)
		return false;

	if (sender == PvPArenaSystem::CommandSenderId)
	{
		player->PlayerTalkClass->CloseGossip();

		switch (action)
		{
		case 4:
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "1v1", PvPArenaSystem::SenderId, 1);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "2v2", PvPArenaSystem::SenderId, 2);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "3v3", PvPArenaSystem::SenderId, 3);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "<-- Back to main menu", PvPArenaSystem::CommandSenderId, 8);
			player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());
			break;

		case 5: 
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "COMING SOON!", PvPArenaSystem::SenderId, 0);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "<-- Back to main menu", PvPArenaSystem::CommandSenderId, 8);
			player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());
			break;


		case 7:
		{
			
			// ARENA KILLS
			QueryResult* guidResultKills = WorldDatabase.PQuery("SELECT playerlowguid FROM `pvp_arena_system_stats` GROUP BY `playerlowguid` ORDER BY SUM(`kills`) DESC LIMIT 5");
			
			if (guidResultKills) {

				std::string first;
				std::string second;
				std::string third;
				std::string fourth;
				std::string fifth;


				BarGoLink bar(guidResultKills->GetRowCount());
				do
				{
					bar.step();
					Field* fields = guidResultKills->Fetch();
					uint32 guid = fields[0].GetInt32();

					QueryResult* nameResult = CharacterDatabase.PQuery("SELECT `name` FROM `characters` WHERE `guid` = %u", guid);
					Field* nameFields = nameResult->Fetch();
					std::string name = nameFields[0].GetCppString();

					if (first == "") {
						first = name;
					}
					else if (second == "") {
						second = name;
					}
					else if (third == "") {
						third = name;
					}
					else if (fourth == "") {
						fourth = name;
					}
					else if (fifth == "") {
						fifth = name;
					}

				} while (guidResultKills->NextRow());
				delete guidResultKills;

				// String out to gossip window
				std::stringstream strstreamFirstKills;
				strstreamFirstKills << "1st: " << first;
				std::string formattedMessage1 = strstreamFirstKills.str();

				std::stringstream strstreamSecondKills;
				strstreamSecondKills << "2nd: " << second;
				std::string formattedMessage2 = strstreamSecondKills.str();

				std::stringstream strstreamthirdkills;
				strstreamthirdkills << "3rd: " << third;
				std::string formattedMessage3 = strstreamthirdkills.str();

				std::stringstream strstreamfourthkills;
				strstreamfourthkills << "4th: " << fourth;
				std::string formattedMessage4 = strstreamfourthkills.str();

				std::stringstream strstreamfifthkills;
				strstreamfifthkills << "5th: " << fifth;
				std::string formattedMessage5 = strstreamfifthkills.str();

				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-----TOP 5 KILLS-----", PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage1.c_str(), PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage2.c_str(), PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage3.c_str(), PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage4.c_str(), PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage5.c_str(), PvPArenaSystem::SenderId, 0);
				player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());
			}
			else {
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "ERROR: NO GUIDS FOUND", PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "<-- Back to main menu", PvPArenaSystem::CommandSenderId, 8);
				player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());
			}

			//ARENA WINS
			QueryResult* guidResultWins = WorldDatabase.PQuery("SELECT playerlowguid FROM `pvp_arena_system_stats` GROUP BY `playerlowguid` ORDER BY SUM(`Won`) DESC LIMIT 5");

			if (guidResultWins) {

				std::string first;
				std::string second;
				std::string third;
				std::string fourth;
				std::string fifth;


				BarGoLink bar(guidResultWins->GetRowCount());
				do
				{
					bar.step();
					Field* fields = guidResultWins->Fetch();
					uint32 guid = fields[0].GetInt32();

					QueryResult* nameResult = CharacterDatabase.PQuery("SELECT `name` FROM `characters` WHERE `guid` = %u", guid);
					Field* nameFields = nameResult->Fetch();
					std::string name = nameFields[0].GetCppString();

					if (first == "") {
						first = name;
					}
					else if (second == "") {
						second = name;
					}
					else if (third == "") {
						third = name;
					}
					else if (fourth == "") {
						fourth = name;
					}
					else if (fifth == "") {
						fifth = name;
					}

				} while (guidResultWins->NextRow());
				delete guidResultWins;

				// String out to gossip window
				std::stringstream strstreamFirstKills;
				strstreamFirstKills << "1st: " << first;
				std::string formattedMessage1 = strstreamFirstKills.str();

				std::stringstream strstreamSecondKills;
				strstreamSecondKills << "2nd: " << second;
				std::string formattedMessage2 = strstreamSecondKills.str();

				std::stringstream strstreamthirdkills;
				strstreamthirdkills << "3rd: " << third;
				std::string formattedMessage3 = strstreamthirdkills.str();

				std::stringstream strstreamfourthkills;
				strstreamfourthkills << "4th: " << fourth;
				std::string formattedMessage4 = strstreamfourthkills.str();

				std::stringstream strstreamfifthkills;
				strstreamfifthkills << "5th: " << fifth;
				std::string formattedMessage5 = strstreamfifthkills.str();

				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "-----TOP 5 ARENA WINS-----", PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage1.c_str(), PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage2.c_str(), PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage3.c_str(), PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage4.c_str(), PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage5.c_str(), PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "<-- Back to main menu", PvPArenaSystem::CommandSenderId, 8);
				player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());
			}
			else {
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "ERROR: NO GUIDS FOUND", PvPArenaSystem::SenderId, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "<-- Back to main menu", PvPArenaSystem::CommandSenderId, 8);
				player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());
			}

			break;
		}

		case 8:

			if (sPvPArenaSystem->IsInQueue(player))
			{
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Leave Queue", PvPArenaSystem::SenderId, 10);
			}
			else {
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Queue Arena", PvPArenaSystem::CommandSenderId, 4);
			}

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Spectate Arena", PvPArenaSystem::CommandSenderId, 5);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Your PvP Stats", PvPArenaSystem::CommandSenderId, 6);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Top Arena Players", PvPArenaSystem::CommandSenderId, 7);
			player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());

			break;

		case 6:
			uint32 guid = player->GetGUIDLow();

			// check for any stats to avoid null pointer
			QueryResult* guidResult = WorldDatabase.PQuery("SELECT `Id` FROM `pvp_arena_system_stats` WHERE `PlayerLowGuid` = '%u'", guid);
			
			QueryResult* wResult = WorldDatabase.PQuery("SELECT SUM(`Won`) FROM `pvp_arena_system_stats` WHERE `PlayerLowGuid` = '%u'", guid);
			Field* wins = wResult->Fetch();
			QueryResult* lResult = WorldDatabase.PQuery("SELECT SUM(`Lost`) FROM `pvp_arena_system_stats` WHERE `PlayerLowGuid` = '%u'", guid);
			Field* losses = lResult->Fetch();
			QueryResult* kResult = WorldDatabase.PQuery("SELECT SUM(`Kills`) FROM `pvp_arena_system_stats` WHERE `PlayerLowGuid` = '%u'", guid);
			Field* kills = kResult->Fetch();
			QueryResult* dResult = WorldDatabase.PQuery("SELECT SUM(`Died`) FROM `pvp_arena_system_stats` WHERE `PlayerLowGuid` = '%u'", guid);
			Field* deaths = dResult->Fetch();


			if (!guidResult)
			{
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "You have not participated in any PvP Arenas.", GOSSIP_SENDER_MAIN, 0);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<-- Back to main menu", PvPArenaSystem::CommandSenderId, 8);
				player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());
			
			}

			else
			{
				uint32 killsCalc = kills[0].GetUInt32();
				uint32 deathsCalc = deaths[0].GetUInt32();

				double kdr = killsCalc / deathsCalc;

				uint32 winsCalc = wins[0].GetUInt32();
				uint32 lossCalc = losses[0].GetUInt32();

				double winLossRatio = winsCalc / lossCalc;

				std::stringstream strstreamWins;
				strstreamWins << "Wins: " << wins->GetUInt32();
				std::string formattedMessage1 = strstreamWins.str();

				std::stringstream strstreamLosses;
				strstreamLosses << "Losses: " << losses->GetUInt32();
				std::string formattedMessage2 = strstreamLosses.str();

				std::stringstream strstreamKills;
				strstreamKills << "Kills: " << kills->GetUInt32();
				std::string formattedMessage3 = strstreamKills.str();

				std::stringstream strstreamDeaths;
				strstreamDeaths << "Deaths: " << deaths->GetUInt32();
				std::string formattedMessage4 = strstreamDeaths.str();

				std::stringstream strstreamKDR;
				strstreamKDR << "-----Kill Death Ratio: " << kdr << " -----";
				std::string formattedMessage5 = strstreamKDR.str();

				std::stringstream strstreamWinLoss;
				strstreamWinLoss << "-----Win/Loss Ratio: " << winLossRatio << " -----";
				std::string formattedMessage6 = strstreamWinLoss.str();

					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage6.c_str(), GOSSIP_SENDER_MAIN, 0);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage1.c_str(), GOSSIP_SENDER_MAIN, 0);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage2.c_str(), GOSSIP_SENDER_MAIN, 0);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage5.c_str(), GOSSIP_SENDER_MAIN, 0);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage3.c_str(), GOSSIP_SENDER_MAIN, 0);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage4.c_str(), GOSSIP_SENDER_MAIN, 0);
					player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "<-- Back to main menu", PvPArenaSystem::CommandSenderId, 8);
					player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());
			
			}
			break;

			delete wResult;
			delete lResult;
			delete kResult;
			delete dResult;
		}

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

	script = new Script;
	script->Name = "PvPArena_Command";
	script->pPlrGossipSelect = &OnPlayerGossipSelect_Command;
	script->RegisterSelfNoBind(ScriptType::Player);

}
