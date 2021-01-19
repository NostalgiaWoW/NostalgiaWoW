//Written by Rain 


#include "scriptPCH.h"
#include "Chat.h"
#include "Language.h"
#include "World.h"
#include "ScriptMgr.h"




struct Bounty
{
	uint32 headEntry;
	uint32 creatorGuid;

};

struct BountyNames
{
	std::string name;
	uint32 price;
};

uint32 BountyPayout(Player* player);
bool BountyConfirm(Player* player, GameObject* pGo);
Bounty GetHead(Player* player);
void GetBountys(Player* player, GameObject* pGo);
void CancelBounty(Player* player);


bool GOHello_bountiesGOB(Player* player, GameObject* _GameObject)
{
	/*player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TRAINER, "Testing", GOSSIP_SENDER_MAIN, 500, "Testing Message", true);*/ // pop up box one day
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "How do bounties work?", GOSSIP_SENDER_MAIN, 500);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "View open bounties.", GOSSIP_SENDER_MAIN, 501);
	//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Post a bounty on a target.", GOSSIP_SENDER_MAIN, 502);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Turn in bounty.", GOSSIP_SENDER_MAIN, 504);
	//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Last loca of bounty.", GOSSIP_SENDER_MAIN, 505);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Cancel bounty.", GOSSIP_SENDER_MAIN, 506);
	player->SEND_GOSSIP_MENU(90351, _GameObject->GetGUID());

	return true;
}


bool GOSelect_go_bountiesGOB(Player* player, GameObject* pGo, uint32 sender, uint32 action)
{


	switch (action)
	{	
	case 500: // Help
		// how bounties work
		player->SEND_GOSSIP_MENU(90404, pGo->GetGUID());
		break;
	case 501: // View
		GetBountys(player, pGo);
		break;

	case 502: // Post 
		player->SEND_GOSSIP_MENU(90402, pGo->GetGUID());
		break;

	case 503:
		// Add to existing bounty
		break;

	case 504: // Turn in
	{		
		bool bountyExists = BountyConfirm(player, pGo);

		if (!bountyExists)
			player->SEND_GOSSIP_MENU(90402, pGo->GetGUID());
		else
		{	// paid out notification
			player->SEND_GOSSIP_MENU(90401, pGo->GetGUID());
		}

		break;
	}

	case 505: // your bounties last known location
		break;
	
	case 506: // cancel bounty
		CancelBounty(player);
		break;

	case 507: // payout
	{
		uint32 payout = BountyPayout(player);
		uint32 headEntry = GetHead(player).headEntry;
		uint32 creatorGuid = GetHead(player).creatorGuid;

		player->ModifyMoney(payout * 10000);
		player->RemoveItems(headEntry, 1);

		auto result = CharacterDatabase.PQuery("SELECT targetName, bountyPrice FROM bounty WHERE posterGuid = %u", player->GetGUIDLow());

		if (result)
		{
			auto fetch = result->Fetch();

			std::string name = fetch[0].GetCppString();
			uint32 price = fetch[1].GetUInt32();

			sWorld.SendWorldText(LANG_BOUNTY_REWARDED, name, player->GetName(), price);
			delete result;

		}

		// remove item instance right away to avoid players spamming the dialogue before world server refreshes the db
		CharacterDatabase.PQuery("DELETE FROM item_instance WHERE itemEntry = %u AND creatorGuid = %u AND owner_guid = %u", headEntry, creatorGuid, player->GetGUIDLow());
		CharacterDatabase.PQuery("DELETE FROM bounty WHERE targetGuid = %u", creatorGuid);
	}
}
	return true;
	player->CLOSE_GOSSIP_MENU();
}


bool BountyConfirm(Player* player, GameObject* pGo)

{
	// Get bounty hunter's collected heads
	QueryResult* result = CharacterDatabase.PQuery("SELECT creatorGuid FROM item_instance WHERE itemEntry BETWEEN 6011143 AND 6011154 AND owner_guid = %u", player->GetGUIDLow());

	if (result)
	{
		auto bountyFetch = result->Fetch();

		//		Target's GUID
		uint32 creatorGuid = bountyFetch[0].GetUInt32();
		//		Get target's name from head
		QueryResult* result1 = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid = %u", creatorGuid);

		if (result1)
		{
			uint32 price = BountyPayout(player);

			auto bountyFetch1 = result1->Fetch();
			std::string bountyName = bountyFetch1[0].GetCppString();

			std::stringstream bountyTarget;
			bountyTarget << "[Bounty] Target: " << bountyName << " Reward: " << price;
			std::string formattedMessage = bountyTarget.str();

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, formattedMessage.c_str(), GOSSIP_SENDER_MAIN, 507);
			player->SEND_GOSSIP_MENU(90401, pGo->GetGUID());
			player->CLOSE_GOSSIP_MENU();

			return true;

		}
		delete result1;
		return true;
	}
	else
		return false;
	delete result;

}

uint32 BountyPayout(Player* player)

{
	// Get bounty hunter's collected heads
	QueryResult* result = CharacterDatabase.PQuery("SELECT creatorGuid FROM item_instance WHERE itemEntry BETWEEN 6001143 AND 6001154 AND owner_guid = %u", player->GetGUIDLow());

	if (result)
	{
		auto bountyFetch = result->Fetch();

		//		Target's GUID
		uint32 creatorGuid = bountyFetch[0].GetUInt32();
		//		Get target's name from head
			QueryResult* result = CharacterDatabase.PQuery("SELECT SUM(bountyPrice) FROM bounty WHERE targetGuid = %u", creatorGuid);

			auto bountyPrice = result->Fetch();
			// Get sum of bountys for head
			uint32 price = bountyPrice[0].GetUInt32();

			return price;
			delete result;
	}
	else
		return 0;


}

Bounty GetHead(Player* player)
{
	QueryResult* result = CharacterDatabase.PQuery("SELECT itemEntry, creatorGuid FROM item_instance WHERE itemEntry BETWEEN 6001143 AND 6001154 AND owner_guid = %u", player->GetGUIDLow());


	if (result)
	{
		auto bountyFetch = result->Fetch();

		//		Target's GUID
		uint32 entry = bountyFetch[0].GetUInt32();
		uint32 creatorGuid = bountyFetch[1].GetUInt32();
		
		Bounty result = { entry , creatorGuid };
		return result;

	}

}

void GetBountys(Player* player, GameObject* pGo)

{
	QueryResult* result = CharacterDatabase.PQuery("SELECT targetName, bountyPrice, posterName FROM bounty LIMIT 10");

	if (result)
	{
		do
		{
			auto nameFetch = result->Fetch();
			std::string names = nameFetch[0].GetString();
			uint32 price = nameFetch[1].GetUInt32();
			std::string names2 = nameFetch[2].GetString();

			std::stringstream bountyTarget;
			bountyTarget << "[Target] " << names << " - " << price << "g" <<" [Issuer] " << names2;
			std::string formattedMessage = bountyTarget.str();

			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, formattedMessage.c_str(), GOSSIP_SENDER_MAIN, 0);
		} while (result->NextRow());


	}
	else
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "NO BOUNTIES POSTED!", GOSSIP_SENDER_MAIN, 0);
		player->SEND_GOSSIP_MENU(90400, pGo->GetGUID());
	}
		player->SEND_GOSSIP_MENU(90400, pGo->GetGUID());
}

void CancelBounty(Player* player)
{
	QueryResult* result = CharacterDatabase.PQuery("SELECT bountyPrice, targetName FROM bounty WHERE posterGuid = %u", player->GetGUIDLow());

	if (result)
	{
		auto bountyPrice = result->Fetch();

		auto price = bountyPrice[0].GetUInt32();
		std::string name = bountyPrice[1].GetCppString();

		QueryResult* time = CharacterDatabase.PQuery("SELECT TIMESTAMPDIFF (MINUTE, timePosted, CURRENT_TIME()) FROM bounty WHERE posterGuid = %u", player->GetGUIDLow());

		if (time)
		{
			auto time1 = time->Fetch();

			auto time2 = time1[0].GetUInt32();
			if (time2 < 1440)
			{
				ChatHandler(player).PSendSysMessage("This bounty is less than 24 hours old and cannot be cancelled yet.");
			}
				else
				{
					player->ModifyMoney((price * .90) * 10000);
					sWorld.SendWorldText(LANG_BOUNTY_CANCELLED, name);
					CharacterDatabase.PQuery("DELETE FROM bounty WHERE posterGuid = %u", player->GetGUIDLow());
				}
		}
		
	}
	else
	{
		ChatHandler(player).PSendSysMessage("You do not have a bounty to cancel.");
	}

}


void AddSC_gOb_bounties()
{
	Script* newscript;

	newscript = new Script;
	newscript->Name = "gob_bounties";
	newscript->pGOHello = &GOHello_bountiesGOB;
	newscript->pGOGossipSelect = &GOSelect_go_bountiesGOB;
	newscript->RegisterSelf();
}