/* Copyright (C) 2009 - 2010 ScriptDevZero <http://github.com/scriptdevzero/scriptdevzero>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "scriptPCH.h"
#include "custom.h"
#include "transmog.h"
#include "Utilities/EventProcessor.h"

template <typename Functor>
void DoAfterTime(Player* player, uint32 p_time, Functor&& function)
{
	player->m_Events.AddEvent(new LambdaBasicEvent<Functor>(std::move(function)), player->m_Events.CalculateTime(p_time));
}

 // Teleport Arena NPC
bool GossipHello_TeleportArenaNPC(Player* player, Creature* _Creature)
{
        player->ADD_GOSSIP_ITEM(5, "I want to watch the fights! Take me to the arena!", GOSSIP_SENDER_MAIN, 11);
       
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());

    return true;
}

// Portals for 3v3 Arena Event - Portal Phase
bool GossipHello_ArenaPortalPhaseNPC(Player* player, Creature* _Creature)
{
    int NPC_PORTAL = 1200000;

    if (!player->HasAura(22356)) {
        player->ADD_GOSSIP_ITEM(5, "Reach into the nether ...", GOSSIP_SENDER_MAIN, (urand(12, 15)));


        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
    } else if (Creature* portal = player->FindNearestCreature(NPC_PORTAL, 5, true))
        portal->MonsterSay(-1999603);
    
    
	return true;
}

// Boat Teleport NPC (Nostalgia WoW)
bool GossipHello_BoatTeleportNPC(Player* player, Creature* _Creature)
{
	//player->ADD_GOSSIP_ITEM(2, "Adventurer Ship (Quests Available)", GOSSIP_SENDER_MAIN, 91);
	player->ADD_GOSSIP_ITEM(2, "Epic Gear Vendors", GOSSIP_SENDER_MAIN, 92);
	player->ADD_GOSSIP_ITEM(2, "Blue Gear Vendors", GOSSIP_SENDER_MAIN, 93);
	player->ADD_GOSSIP_ITEM(2, "Class Trainers", GOSSIP_SENDER_MAIN, 94);

	player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
	return true;
}

void SendDefaultMenu_BoatTeleportNPC(Player* player, Creature* _Creature, uint32 action)
{
	switch (action)
	{
		//case 91:
			//player->CLOSE_GOSSIP_MENU();
			//player->TeleportTo(0, -1847.98, -4246.67, 2.13, 0.89f);
			//break;
		case 92:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -1943.60, -4352.58, 6.09, 5.86f);
			break;
		case 93:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -1990.34, -4278.39, 5.93, 6.09f);
			break;
		case 94:
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -1799.76, -4336.80, 6.10, 5.10f);
			break;
	}
}


// TELEPORT NPC

bool GossipHello_TeleportNPC(Player *player, Creature *_Creature)   
{
    // HORDE
    if (player->GetTeam() == HORDE)
    {
        // player->ADD_GOSSIP_ITEM(5, "PreTBC Mall"          , GOSSIP_SENDER_MAIN, 74);
		player->ADD_GOSSIP_ITEM(5, "Nostalgia WoW Mall",		GOSSIP_SENDER_MAIN, 90);
		player->ADD_GOSSIP_ITEM(5, "Profession Zone (NOT DONE)",	GOSSIP_SENDER_MAIN, 90);
		player->ADD_GOSSIP_ITEM(5, "Duel Zone (NOT DONE)",			GOSSIP_SENDER_MAIN, 90);
		player->ADD_GOSSIP_ITEM(5, "Pet Zone",			GOSSIP_SENDER_MAIN, 90);
        player->ADD_GOSSIP_ITEM(5, "Major Cities"               , GOSSIP_SENDER_MAIN, 1);
        //player->ADD_GOSSIP_ITEM(5, "Starting Areas"       , GOSSIP_SENDER_MAIN, 3);
        //player->ADD_GOSSIP_ITEM(5, "Instances"            , GOSSIP_SENDER_MAIN, 5);
        player->ADD_GOSSIP_ITEM(5, "Raids"                 , GOSSIP_SENDER_MAIN, 101);
        //player->ADD_GOSSIP_ITEM(5, "Gurubashi Arena" , GOSSIP_SENDER_MAIN, 4015);
        //player->ADD_GOSSIP_ITEM(5, "Zones - Kalimdor"     , GOSSIP_SENDER_MAIN, 6010);
        //player->ADD_GOSSIP_ITEM(5, "Zones - Eastern Kingdoms"     , GOSSIP_SENDER_MAIN, 6020);

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
    }
    // ALLIANCE
    else
    {
        //player->ADD_GOSSIP_ITEM(5, "PreTBC Mall"          , GOSSIP_SENDER_MAIN, 74);
		player->ADD_GOSSIP_ITEM(5, "Nostalgia WoW Mall", GOSSIP_SENDER_MAIN, 90);
		player->ADD_GOSSIP_ITEM(5, "Profession Zone (NOT DONE)", GOSSIP_SENDER_MAIN, 90);
		player->ADD_GOSSIP_ITEM(5, "Duel Zone (NOT DONE)", GOSSIP_SENDER_MAIN, 90);
		player->ADD_GOSSIP_ITEM(5, "Pet Zone", GOSSIP_SENDER_MAIN, 90);
		player->ADD_GOSSIP_ITEM(5, "Major Cities", GOSSIP_SENDER_MAIN, 2);
        //player->ADD_GOSSIP_ITEM(5, "Starting Areas"       , GOSSIP_SENDER_MAIN, 4);
        //player->ADD_GOSSIP_ITEM(5, "Instances"            , GOSSIP_SENDER_MAIN, 5);
        player->ADD_GOSSIP_ITEM(5, "Raids"                 , GOSSIP_SENDER_MAIN, 101);
        //player->ADD_GOSSIP_ITEM(5, "Gurubashi Arena" , GOSSIP_SENDER_MAIN, 4015);
        //player->ADD_GOSSIP_ITEM(5, "Zones - Kalimdor"     , GOSSIP_SENDER_MAIN, 6010);
        //player->ADD_GOSSIP_ITEM(5, "Zones - Eastern Kingdoms"     , GOSSIP_SENDER_MAIN, 6020);

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
    }
    return true;
}

void SendDefaultMenu_TeleportNPC(Player *player, Creature *_Creature, uint32 action)
{
    switch (action)
    {
        case 1: // Cities [HORDE]
            player->ADD_GOSSIP_ITEM(5, "Orgrimmar"             , GOSSIP_SENDER_MAIN, 20);
            player->ADD_GOSSIP_ITEM(5, "Undercity"             , GOSSIP_SENDER_MAIN, 21);
            player->ADD_GOSSIP_ITEM(5, "Thunderbluff"          , GOSSIP_SENDER_MAIN, 22);
            //player->ADD_GOSSIP_ITEM(5, "Goldshire (Stormwind)" , GOSSIP_SENDER_MAIN, 4018);
            player->ADD_GOSSIP_ITEM(5, "<-[Main Menu]"                  , GOSSIP_SENDER_MAIN, 100);

            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
            break;
        case 2: // Cities [ALLIANCE]
            player->ADD_GOSSIP_ITEM(5, "Stormwind City"        , GOSSIP_SENDER_MAIN, 23);
            player->ADD_GOSSIP_ITEM(5, "Ironforge"             , GOSSIP_SENDER_MAIN, 24);
            player->ADD_GOSSIP_ITEM(5, "Darnassus"             , GOSSIP_SENDER_MAIN, 25);
            //player->ADD_GOSSIP_ITEM(5, "Razor Hill(Orgrimmar)" , GOSSIP_SENDER_MAIN, 4017);
            player->ADD_GOSSIP_ITEM(5, "<-[Main Menu]"                  , GOSSIP_SENDER_MAIN, 100);

            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
            break;
        case 3: // Starting Places [HORDE]
            player->ADD_GOSSIP_ITEM(5, "Shadow Grave"          , GOSSIP_SENDER_MAIN, 40);
            player->ADD_GOSSIP_ITEM(5, "Valley of Trials"      , GOSSIP_SENDER_MAIN, 41);
            player->ADD_GOSSIP_ITEM(5, "Camp Narache"          , GOSSIP_SENDER_MAIN, 42);
            player->ADD_GOSSIP_ITEM(5, "<-[Main Menu]"                  , GOSSIP_SENDER_MAIN, 100);

            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
            break;
        case 4: // Starting Places [ALLIANCE]
            player->ADD_GOSSIP_ITEM(5, "Northshire Valley"     , GOSSIP_SENDER_MAIN, 43);
            player->ADD_GOSSIP_ITEM(5, "Coldridge Valley"      , GOSSIP_SENDER_MAIN, 44);
            player->ADD_GOSSIP_ITEM(5, "Shadowglen"            , GOSSIP_SENDER_MAIN, 45);
            player->ADD_GOSSIP_ITEM(5, "<-[Main Menu]"                  , GOSSIP_SENDER_MAIN, 100);

            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
            break;
        case 5: // Instances [PAGE 1]
            player->ADD_GOSSIP_ITEM(5, "The Wailing Caverns" , GOSSIP_SENDER_MAIN, 1249);
            player->ADD_GOSSIP_ITEM(5, "Deadmines" , GOSSIP_SENDER_MAIN, 1250);
            player->ADD_GOSSIP_ITEM(5, "Shadowfang Keep" , GOSSIP_SENDER_MAIN, 1251);
            player->ADD_GOSSIP_ITEM(5, "Blackfathom Deeps" , GOSSIP_SENDER_MAIN, 1252);
            player->ADD_GOSSIP_ITEM(5, "Razorfen Kraul" , GOSSIP_SENDER_MAIN, 1254);
            player->ADD_GOSSIP_ITEM(5, "Razorfen Downs" , GOSSIP_SENDER_MAIN, 1256);
            player->ADD_GOSSIP_ITEM(5, "Scarlet Monastery" , GOSSIP_SENDER_MAIN, 1257);
            player->ADD_GOSSIP_ITEM(7, "[More] ->" , GOSSIP_SENDER_MAIN, 5551);
            player->ADD_GOSSIP_ITEM(5, "<-[Main Menu]"                  , GOSSIP_SENDER_MAIN, 100);

            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
            break;
        case 5551: // Instances [PAGE 2]
            player->ADD_GOSSIP_ITEM(5, "Uldaman" , GOSSIP_SENDER_MAIN, 1258);
            player->ADD_GOSSIP_ITEM(5, "Zul'Farrak" , GOSSIP_SENDER_MAIN, 1259);
            player->ADD_GOSSIP_ITEM(5, "Maraudon" , GOSSIP_SENDER_MAIN, 1260);
            player->ADD_GOSSIP_ITEM(5, "The Sunken Temple" , GOSSIP_SENDER_MAIN, 1261);
            player->ADD_GOSSIP_ITEM(5, "Blackrock Depths" , GOSSIP_SENDER_MAIN, 1262);
            player->ADD_GOSSIP_ITEM(5, "Dire Maul" , GOSSIP_SENDER_MAIN, 1263);
            player->ADD_GOSSIP_ITEM(5, "Blackrock Spire" , GOSSIP_SENDER_MAIN, 1264);
            player->ADD_GOSSIP_ITEM(5, "Stratholme" , GOSSIP_SENDER_MAIN, 1265);
            player->ADD_GOSSIP_ITEM(5, "Scholomance" , GOSSIP_SENDER_MAIN, 1266);
            player->ADD_GOSSIP_ITEM(7, "<- [Back]" , GOSSIP_SENDER_MAIN, 5);
            player->ADD_GOSSIP_ITEM(5, "<-[Main Menu]"                  , GOSSIP_SENDER_MAIN, 100);

            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
            break;
        case 101: // Raids
            player->ADD_GOSSIP_ITEM(5, "Molten Core" , GOSSIP_SENDER_MAIN, 4002);
			player->ADD_GOSSIP_ITEM(5, "Onyxia's Lair", GOSSIP_SENDER_MAIN, 4001);
            player->ADD_GOSSIP_ITEM(5, "Blackwing Lair" , GOSSIP_SENDER_MAIN, 4003);
			player->ADD_GOSSIP_ITEM(5, "Zul'Gurub", GOSSIP_SENDER_MAIN, 4000);
            player->ADD_GOSSIP_ITEM(5, "Ruins of Ahn'Qiraj" , GOSSIP_SENDER_MAIN, 4004);
            player->ADD_GOSSIP_ITEM(5, "Temple of Ahn'Qiraj" , GOSSIP_SENDER_MAIN, 4005);
            player->ADD_GOSSIP_ITEM(5, "Naxxramas" , GOSSIP_SENDER_MAIN, 4006);
            player->ADD_GOSSIP_ITEM(5, "<-[Main Menu]"                  , GOSSIP_SENDER_MAIN, 100);

            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
            break;
        case 6010: // Kalimdor
            player->ADD_GOSSIP_ITEM(5, "Ashenvale" , GOSSIP_SENDER_MAIN, 601);
            player->ADD_GOSSIP_ITEM(5, "Darkshore" , GOSSIP_SENDER_MAIN, 602);
            player->ADD_GOSSIP_ITEM(5, "Desolace" , GOSSIP_SENDER_MAIN, 603);
            player->ADD_GOSSIP_ITEM(5, "Durotar" , GOSSIP_SENDER_MAIN, 604);
            player->ADD_GOSSIP_ITEM(5, "Dustwallow Marsh" , GOSSIP_SENDER_MAIN, 605);
            player->ADD_GOSSIP_ITEM(5, "Feralas" , GOSSIP_SENDER_MAIN, 606);
            player->ADD_GOSSIP_ITEM(5, "Silithus" , GOSSIP_SENDER_MAIN, 607);
            player->ADD_GOSSIP_ITEM(5, "Stonetalon Mountains" , GOSSIP_SENDER_MAIN, 608);
            player->ADD_GOSSIP_ITEM(5, "Tanaris" , GOSSIP_SENDER_MAIN, 609);
            player->ADD_GOSSIP_ITEM(5, "The Barrens" , GOSSIP_SENDER_MAIN, 610);
            player->ADD_GOSSIP_ITEM(5, "Thousand Needles" , GOSSIP_SENDER_MAIN, 611);
            player->ADD_GOSSIP_ITEM(5, "Winterspring" , GOSSIP_SENDER_MAIN, 612);
            player->ADD_GOSSIP_ITEM(5, "<-[Main Menu]"                  , GOSSIP_SENDER_MAIN, 100);

            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
            break;
        case 6020: // Eastern Kingdoms
            player->ADD_GOSSIP_ITEM(5, "Arathi Highlands" , GOSSIP_SENDER_MAIN, 613);
            player->ADD_GOSSIP_ITEM(5, "Badlands" , GOSSIP_SENDER_MAIN, 614);
            player->ADD_GOSSIP_ITEM(5, "Dun Morogh" , GOSSIP_SENDER_MAIN, 615);
            player->ADD_GOSSIP_ITEM(5, "Duskwood" , GOSSIP_SENDER_MAIN, 616);
            player->ADD_GOSSIP_ITEM(5, "Eastern Plaguelands" , GOSSIP_SENDER_MAIN, 617);
            player->ADD_GOSSIP_ITEM(5, "Elwynn Forest" , GOSSIP_SENDER_MAIN, 618);
            player->ADD_GOSSIP_ITEM(5, "Hillsbrad Foothills" , GOSSIP_SENDER_MAIN, 619);
            player->ADD_GOSSIP_ITEM(5, "Redridge Mountains" , GOSSIP_SENDER_MAIN, 620);
            player->ADD_GOSSIP_ITEM(5, "Silverpine Forest" , GOSSIP_SENDER_MAIN, 621);
            player->ADD_GOSSIP_ITEM(5, "Stranglethorn Vale" , GOSSIP_SENDER_MAIN, 622);
            player->ADD_GOSSIP_ITEM(5, "Swamp of Sorrows" , GOSSIP_SENDER_MAIN, 623);
            player->ADD_GOSSIP_ITEM(5, "The Hinterlands" , GOSSIP_SENDER_MAIN, 624);
            player->ADD_GOSSIP_ITEM(5, "Tirisfal Glades" , GOSSIP_SENDER_MAIN, 625);
            player->ADD_GOSSIP_ITEM(5, "Westfall" , GOSSIP_SENDER_MAIN, 626);
            player->ADD_GOSSIP_ITEM(5, "Wetlands" , GOSSIP_SENDER_MAIN, 627);
            player->ADD_GOSSIP_ITEM(5, "<-[Main Menu]"                  , GOSSIP_SENDER_MAIN, 100);

            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
            break;


// ----### ARENA ###----
        case 11: // Entrance to Arena
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -4192.70f, 1133.19f, 161.21f, 0.01f);
            break;
        case 12: // Portal Location SOUTH
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -3819.243408f, 1095.812744f, 132.032684f, 6.257055f);
            player->AddAura(22356);
            break;
        case 13: // Portal Location NORTH
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -3687.55f, 1090.58f, 131.97f, 3.11f);
            player->AddAura(22356);
            break;
        case 14: // Portal Location WEST
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -3742.28f, 1123.63f, 132.36f, 4.64f);
            player->AddAura(22356);
            break;
        case 15: // Portal Location EAST
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -3754.29f, 1061.04f, 132.19f, 1.62f);
            player->AddAura(22356);
            break;

// ----### NOSTALGIA WOW ###----
		case 90: // Mall
			player->CLOSE_GOSSIP_MENU();
			player->TeleportTo(0, -1847.80, -4244.382, 2.13, 1.05f);
			break;

// ----### CITIES ###----

// ### HORDE ###

        case 20: // Orgrimmar
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 1437.0f, -4421.0f, 25.24f, 1.65f);
            break;
        case 21: // Undercity
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 1822.0999f, 238.638855f, 60.694809f, 0.0f);
            break;
        case 22: // Thunderbluff
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -1272.703735f, 116.886490f, 131.016861f, 0.0f);
            break;

// ### ALLIANCE ###

        case 23: // Stormwind
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -8828.231445f, 627.927490f, 94.055664f, 0.0f);
            break;
        case 24: // Ironforge
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -4917.0f, -955.0f, 502.0f, 0.0f);
            break;
        case 25: // Darnassus
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 9962.712891f, 2280.142822f, 1341.394409f, 0.0f);
            break;

// ----### STARTING PLACES ####----

// ### HORDE ###
        case 40: // Shadow Grave
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 1663.517f, 1678.187744f, 120.5303f, 0.0f);
            break;
        case 41: // Valley of Trials
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -602.1253f, -4262.4208f, 38.956341f, 0.0f);
            break;
        case 42: // Camp Narache
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -2914.16992f, -266.061798f, 53.658211f, 0.0f);
            break;

// ### ALLIANCE ###

        case 43: // Nortshire Valley
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -8943.133789f, -132.934921f, 83.704269f, 0.0f);
            break;
        case 44: // Coldridge Valley
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -6231.106445f, 332.270477f, 383.153931f, 0.0f);
            break;
        case 45: // Shadowglen
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 10329.918945f, 833.500305f, 1326.260620f, 0.0f);
            break;

// ----### INSTANCES ###----

        case 50: // Dire Maul
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -3762.340820f, 1216.537598f, 127.434608f, 0.0f);
            break;
        case 51: // Blackrock Spire
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -7528.554688f, -1222.907227f, 285.732941f, 0.0f);
            break;
        case 52: // Zul'Gurub
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -11916.179688f, -1190.977051f, 85.137901f, 0.0f);
            break;
        case 53: // Onyxia's Lair
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -4682.391602f, -3709.857422f, 46.792862f, 0.0f);
            break;
        case 54: // Searing Gorge (Moltencore, Blackwinglair)
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -7342.270020f, -1096.863892f, 277.06930f, 0.0f);
            break;
        case 55: // Naxxramas
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 3121.061768f, -3689.973389f, 133.458786f, 0.0f);
            break;
        case 56: // Stratholme Backdoor Entrance
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 3160.416992f, -4038.750244f, 104.177376f, 0.0f);
            break;
        case 57: // Stratholme Main Entrance
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 3357.214355f, -3379.713135f, 144.780853f, 0.0f);
            break;
        case 58: // Scholomance
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 1252.319824f, -2587.151123f, 92.886772f, 0.0f);
            break;

// ---### ZONES ###---

        case 70: // Silithus
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -7430.070313f, 1002.554565f, 1.249787f, 0.0f);
            break;
        case 71: // Durotar
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 1006.426819f, -4439.258789f, 11.352882f, 0.0f);
            break;
        case 72: // Ashenvale
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 1922.842651f, -2169.429688f, 94.327400f, 0.0f);
            break;
        case 73: // Tanaris
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -7180.401367f, -3773.328369f, 8.728320f, 0.0f);
            break;
        case 74: // Pretbc Mall
            //player->CLOSE_GOSSIP_MENU();
            //player->TeleportTo(1, 16201.107422f, 16205.1875f, 0.140072f, 1.630427f);
            break;
        case 4015:// Gurubashi
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -13261.3f, 168.294f, 35.0792f, 1.00688f);
            break;
        case 4017:// Razor Hill
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 315.721f, -4743.4f, 10.4867f, 0.0f);
            break;
        case 4018:// Goldshire
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -9464.0f, 62.0f, 56.0f, 0.0f);
            break;
        case 1249://teleport player to the Wailing Caverns
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -722.53f, -2226.30f, 16.94f, 2.71f);
            break;
        case 1250://teleport player to the Deadmines
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -11212.04f, 1658.58f, 25.67f, 1.45f);
            break;
        case 1251://teleport player to Shadowfang Keep
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -254.47f, 1524.68f, 76.89f, 1.56f);
            break;
        case 1252://teleport player to Blackfathom Deeps
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 4254.58f, 664.74f, -29.04f, 1.97f);
            break;
        case 1254://teleport player to Razorfen Kraul
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -4484.04f, -1739.40f, 86.47f, 1.23f);
            break;
        case 1256://teleport player to Razorfen Downs
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -4645.08f, -2470.85f, 85.53f, 4.39f);
            break;
        case 1257://teleport player to the Scarlet Monastery
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 2843.89f, -693.74f, 139.32f, 5.11f);
            break;
        case 1258://teleport player to Uldaman
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -6119.70f, -2957.30f, 204.11f, 0.03f);
            break;
        case 1259://teleport player to Zul'Farrak
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -6839.39f, -2911.03f, 8.87f, 0.41f);
            break;
        case 1260://teleport player to Maraudon
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -1433.33f, 2955.34f, 96.21f, 4.82f);
            break;
        case 1261://teleport player to the Sunken Temple
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -10346.92f, -3851.90f, -43.41f, 6.09f);
            break;
        case 1262://teleport player to Blackrock Depths
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -7301.03f, -913.19f, 165.37f, 0.08f);
            break;
        case 1263://teleport player to Dire Maul
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -3982.47f, 1127.79f, 161.02f, 0.05f);
            break;
        case 1264://teleport player to Blackrock Spire
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -7535.43f, -1212.04f, 285.45f, 5.29f);
            break;
        case 1265://teleport player to Stratholme
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 3263.54f, -3379.46f, 143.59f, 0.00f);
            break;
        case 1266://teleport player to Scholomance
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 1219.01f, -2604.66f, 85.61f, 0.50f);
            break;
        case 4000:// Teleport to Zul'Gurub
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -11916.7f, -1212.82f, 92.2868f, 4.6095f);
            break;
        case 4001:// Teleport to Onyxia's Lair
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -4707.44f, -3726.82f, 54.6723f, 3.8f);
            break;
        case 4002:// Teleport to Molten Core
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(230, 1121.451172f, -454.316772f, -101.329536f, 3.5f);
            break;
        case 4003:// Teleport to Blackwing Lair
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(469, -7665.55f, -1102.49f, 400.679f, 0.0f);
            break;
        case 4004:// Ruins of Ahn'Qiraj
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -8409.032227f, 1498.830933f, 27.361542f, 2.497567f);
            break;
        case 4005:// Temple of Ahn'Qiraj
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -8245.837891f, 1983.736206f, 129.071686f, 0.936195f);
            break;
        case 4006:// Naxxramas
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 3102.03f, -3714.53f, 132.83f, 0.0f);
            break;
        case 601: // Kalimdor -> Ashenvale
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 3469.43f, 847.62f, 6.36476f, 0.0f);
            break;
        case 602: // Kalimdor -> Darkshore
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 6207.5f, -152.833f, 80.8185f, 0.0f);
            break;
        case 603: // Kalimdor -> Desolace
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -93.1614f, 1691.15f, 90.0649f, 0.0f);
            break;
        case 604: // Kalimdor -> Durotar
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 341.42f, -4684.7f, 31.9493f, 0.0f);
            break;
        case 605: // Kalimdor -> Duswallow Marsh
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -3463.26f, -4123.13f, 18.1043f, 0.0f);
            break;
        case 606: // Kalimdor -> Ferelas
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -4458.93f, 243.415f, 65.6136f, 0.0f);
            break;
        case 607: // Kalimdor -> Silithus
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -6824.15f, 821.273f, 50.6675f, 0.0f);
            break;
        case 608: // Kalimdor -> Stonetalon Mountains
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 1145.00f, 85.664f, -6.64f, 0.0f);
            break;
        case 609: // Kalimdor -> Tanaris
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -7373.69f, -2950.2f, 11.7598f, 0.0f);
            break;
        case 610: // Kalimdor -> The Barrens
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -456.263f, -2652.7f, 96.615f, 0.0f);
            break;
        case 611: // Kalimdor -> Thousand Needles
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, -4941.66f, -1595.42f, -33.07f, 0.0f);
            break;
        case 612: // Kalimdor -> Winterspring
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(1, 6107.62f, -4181.6f, 853.322f, 0.0f);
            break;
        case 613: // Eastern Kingdoms -> Arathi Highlands
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -1544.93f, -2495.01f, 54.11f, 0.0f);
            break;
        case 614: // Eastern Kingdoms -> Badlands
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -6084.95f, -3328.44f, 253.76f, 0.0f);
            break;
        case 615: // Eastern Kingdoms -> Dun Morogh
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -5660.33f, 755.299f, 390.605f, 0.0f);
            break;
        case 616: // Eastern Kingdoms -> Duskwood
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -10879.85f, -327.06f, 37.78f, 0.0f);
            break;
        case 617: // Eastern Kingdoms -> Eastern Plaguelands
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 2280.12f, -5313.16f, 87.74f, 0.0f);
            break;
        case 618: // Eastern Kingdoms -> Elwynn Forest
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -9545.78f, -51.81f, 56.72f, 0.0f);
            break;
        case 619: // Eastern Kingdoms -> Hillsbrad Foothills
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -436.03f, -583.27f, 53.58f, 0.0f);
            break;
        case 620: // Eastern Kingdoms -> Reridge Mountains
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -9633.80f, -1875.09f, 68.39f, 0.0f);
            break;
        case 621: // Eastern Kingdoms -> Silverpine Forest
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 641.48f, 1297.84f, 85.45f, 0.0f);
            break;
        case 622: // Eastern Kingdoms -> Stranglethorn Vale
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -11393.77f, -288.94f, 58.99f, 0.0f);
            break;
        case 623: // Eastern Kingdoms -> Swamp of Sorrows
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -10522.55f, -3028.30f, 21.79f, 0.0f);
            break;
        case 624: // Eastern Kingdoms -> The Hinterlands
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 155.14f, -2014.95f, 122.55f, 0.0f);
            break;
        case 625: // Eastern Kingdoms -> Tirishfal Glades
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, 2255.5f, 288.511f, 35.1138f, 0.0f);
            break;
        case 626: // Eastern Kingdoms -> Westfall
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -10919.09f, 998.47f, 35.47f, 0.0f);
            break;
        case 627: // Eastern Kingdoms -> Wetlands
            player->CLOSE_GOSSIP_MENU();
            player->TeleportTo(0, -4086.36f, -2610.95f, 47.0143f, 0.0f);
            break;

        case 100: // Main Menu
            // HORDE
            if (player->GetTeam() == HORDE)
			{
				// player->ADD_GOSSIP_ITEM(5, "PreTBC Mall"          , GOSSIP_SENDER_MAIN, 74);
				player->ADD_GOSSIP_ITEM(5, "Nostalgia WoW Mall", GOSSIP_SENDER_MAIN, 90);
				//player->ADD_GOSSIP_ITEM(5, "Profession Zone (NOT DONE)", GOSSIP_SENDER_MAIN, 90);
				player->ADD_GOSSIP_ITEM(5, "Duel Zone (NOT DONE)", GOSSIP_SENDER_MAIN, 90);
				player->ADD_GOSSIP_ITEM(5, "Pet Zone", GOSSIP_SENDER_MAIN, 90);
				player->ADD_GOSSIP_ITEM(5, "Major Cities", GOSSIP_SENDER_MAIN, 1);
				//player->ADD_GOSSIP_ITEM(5, "Starting Areas"       , GOSSIP_SENDER_MAIN, 3);
				//player->ADD_GOSSIP_ITEM(5, "Instances"            , GOSSIP_SENDER_MAIN, 5);
				player->ADD_GOSSIP_ITEM(5, "Raids", GOSSIP_SENDER_MAIN, 101);
				//player->ADD_GOSSIP_ITEM(5, "Gurubashi Arena" , GOSSIP_SENDER_MAIN, 4015);
				//player->ADD_GOSSIP_ITEM(5, "Zones - Kalimdor"     , GOSSIP_SENDER_MAIN, 6010);
				//player->ADD_GOSSIP_ITEM(5, "Zones - Eastern Kingdoms"     , GOSSIP_SENDER_MAIN, 6020);

				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
			}
			// ALLIANCE
			else
			{
				//player->ADD_GOSSIP_ITEM(5, "PreTBC Mall"          , GOSSIP_SENDER_MAIN, 74);
				player->ADD_GOSSIP_ITEM(5, "Nostalgia WoW Mall", GOSSIP_SENDER_MAIN, 90);
				//player->ADD_GOSSIP_ITEM(5, "Profession Zone (NOT DONE)", GOSSIP_SENDER_MAIN, 90);
				player->ADD_GOSSIP_ITEM(5, "Duel Zone (NOT DONE)", GOSSIP_SENDER_MAIN, 90);
				player->ADD_GOSSIP_ITEM(5, "Pet Zone", GOSSIP_SENDER_MAIN, 90);
				player->ADD_GOSSIP_ITEM(5, "Major Cities", GOSSIP_SENDER_MAIN, 1);
				//player->ADD_GOSSIP_ITEM(5, "Starting Areas"       , GOSSIP_SENDER_MAIN, 4);
				//player->ADD_GOSSIP_ITEM(5, "Instances"            , GOSSIP_SENDER_MAIN, 5);
				player->ADD_GOSSIP_ITEM(5, "Raids", GOSSIP_SENDER_MAIN, 101);
				//player->ADD_GOSSIP_ITEM(5, "Gurubashi Arena" , GOSSIP_SENDER_MAIN, 4015);
				//player->ADD_GOSSIP_ITEM(5, "Zones - Kalimdor"     , GOSSIP_SENDER_MAIN, 6010);
				//player->ADD_GOSSIP_ITEM(5, "Zones - Eastern Kingdoms"     , GOSSIP_SENDER_MAIN, 6020);

				player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
			}
            break;
    }
}
bool GossipSelect_TeleportNPC(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    // Main menu
    if (sender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_TeleportNPC(player, _Creature, action);

    return true;
}

bool GossipSelect_TeleportArenaNPC(Player* player, Creature* _Creature, uint32 sender, uint32 action)
{
    // Main menu Arena
    if (sender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_TeleportNPC(player, _Creature, action);

    return true;
}

bool GossipSelect_BoatTeleportNPC(Player* player, Creature* _Creature, uint32 sender, uint32 action)
{
	// Main menu
	if (sender == GOSSIP_SENDER_MAIN)
		SendDefaultMenu_BoatTeleportNPC(player, _Creature, action);

	return true;
}


enum Enchants
{
    WEP2H_SUPERIOR_IMPACT = 20,
    WEP2H_AGILITY,
    WEP_CRUSADER,
    WEP1H_AGILITY,
    WEP_SPELLPOWER,
    WEP_HEAL,
    OFFHAND_SPIRIT,
    OFFHAND_STAM,
    OFFHAND_FROSTRES,
    CHEST_STATS,
    CLOAK_DODGE,
    CLOAK_SUB,
    CLOAK_ARMOR,
    CLOAK_AGILITY,
    BRACER_STAM,
    BRACER_STR,
    BRACER_HEAL,
    BRACER_INT,
    GLOVES_AGI,
    GLOVES_FIRE,
    GLOVES_FROST,
    GLOVES_SHADOW,
    GLOVES_HEALING,
    BOOTS_AGI,
    BOOTS_SPEED,
    BOOTS_STAM,
};

void Enchant(Player* player, Item* item, uint32 enchantid)
{
    if (!item)
    {
        player->GetSession()->SendNotification("You must first equip the item you are trying to enchant.");
        return;
    }

    if (!enchantid)
    {
        player->GetSession()->SendNotification("Something went wrong.");
        return;
    }

    item->ClearEnchantment(PERM_ENCHANTMENT_SLOT);
    item->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchantid, 0, 0);
    player->GetSession()->SendNotification("%s successfully enchanted", item->GetProto()->Name1);
}

bool GossipHello_EnchantNPC(Player* player, Creature* creature)
{

    player->ADD_GOSSIP_ITEM(5, "Chest", GOSSIP_SENDER_MAIN, EQUIPMENT_SLOT_CHEST);
    player->ADD_GOSSIP_ITEM(5, "Cloak", GOSSIP_SENDER_MAIN, EQUIPMENT_SLOT_BACK);
    player->ADD_GOSSIP_ITEM(5, "Bracers", GOSSIP_SENDER_MAIN, EQUIPMENT_SLOT_WRISTS);
    player->ADD_GOSSIP_ITEM(5, "Gloves", GOSSIP_SENDER_MAIN, EQUIPMENT_SLOT_HANDS);
    player->ADD_GOSSIP_ITEM(5, "Boots", GOSSIP_SENDER_MAIN, EQUIPMENT_SLOT_FEET);
    player->ADD_GOSSIP_ITEM(5, "Mainhand", GOSSIP_SENDER_MAIN, EQUIPMENT_SLOT_MAINHAND);
    player->ADD_GOSSIP_ITEM(5, "Offhand", GOSSIP_SENDER_MAIN, EQUIPMENT_SLOT_OFFHAND);

    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
    return true;
}
bool GossipSelect_EnchantNPC(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (sender != GOSSIP_SENDER_MAIN)
        return true;

    if (action < 20)
    {
        switch (action)
        {
        case EQUIPMENT_SLOT_CHEST:
            player->ADD_GOSSIP_ITEM(5, "Greater Stats", GOSSIP_SENDER_MAIN, CHEST_STATS);
            break;
        case EQUIPMENT_SLOT_BACK:
            player->ADD_GOSSIP_ITEM(5, "Agility", GOSSIP_SENDER_MAIN, CLOAK_AGILITY);
            player->ADD_GOSSIP_ITEM(5, "Armor", GOSSIP_SENDER_MAIN, CLOAK_ARMOR);
            player->ADD_GOSSIP_ITEM(5, "Dodge", GOSSIP_SENDER_MAIN, CLOAK_DODGE);
            player->ADD_GOSSIP_ITEM(5, "Subtlety", GOSSIP_SENDER_MAIN, CLOAK_SUB);
        break;
        case EQUIPMENT_SLOT_WRISTS:
            player->ADD_GOSSIP_ITEM(5, "Stamina", GOSSIP_SENDER_MAIN, BRACER_STAM);
            player->ADD_GOSSIP_ITEM(5, "Strength", GOSSIP_SENDER_MAIN, BRACER_STR);
            player->ADD_GOSSIP_ITEM(5, "Healing", GOSSIP_SENDER_MAIN, BRACER_HEAL);
            player->ADD_GOSSIP_ITEM(5, "Intellect", GOSSIP_SENDER_MAIN, BRACER_INT);
            break;
        case EQUIPMENT_SLOT_HANDS:
            player->ADD_GOSSIP_ITEM(5, "Agility", GOSSIP_SENDER_MAIN, GLOVES_AGI);
            player->ADD_GOSSIP_ITEM(5, "Fire Power", GOSSIP_SENDER_MAIN, GLOVES_FIRE);
            player->ADD_GOSSIP_ITEM(5, "Frost Power", GOSSIP_SENDER_MAIN, GLOVES_FROST);
            player->ADD_GOSSIP_ITEM(5, "Shadow Power", GOSSIP_SENDER_MAIN, GLOVES_SHADOW);
            player->ADD_GOSSIP_ITEM(5, "Healing", GOSSIP_SENDER_MAIN, GLOVES_HEALING);
            break;
        case EQUIPMENT_SLOT_FEET:
            player->ADD_GOSSIP_ITEM(5, "Stamina", GOSSIP_SENDER_MAIN, BOOTS_STAM);
            player->ADD_GOSSIP_ITEM(5, "Minor Speed", GOSSIP_SENDER_MAIN, BOOTS_SPEED);
            player->ADD_GOSSIP_ITEM(5, "Agility", GOSSIP_SENDER_MAIN, BOOTS_AGI);
            break;
        case EQUIPMENT_SLOT_MAINHAND:
            player->ADD_GOSSIP_ITEM(5, "Crusader", GOSSIP_SENDER_MAIN, WEP_CRUSADER);
            player->ADD_GOSSIP_ITEM(5, "1H Agility", GOSSIP_SENDER_MAIN, WEP1H_AGILITY);
            player->ADD_GOSSIP_ITEM(5, "2H Agility", GOSSIP_SENDER_MAIN, WEP2H_AGILITY);
            player->ADD_GOSSIP_ITEM(5, "Spellpower", GOSSIP_SENDER_MAIN, WEP_SPELLPOWER);
            player->ADD_GOSSIP_ITEM(5, "Healing", GOSSIP_SENDER_MAIN, WEP_HEAL);
            break;
        case EQUIPMENT_SLOT_OFFHAND:
            player->ADD_GOSSIP_ITEM(5, "Spirit", GOSSIP_SENDER_MAIN, OFFHAND_SPIRIT);
            player->ADD_GOSSIP_ITEM(5, "Stamina", GOSSIP_SENDER_MAIN, OFFHAND_STAM);
            player->ADD_GOSSIP_ITEM(5, "Frost Resistance", GOSSIP_SENDER_MAIN, OFFHAND_FROSTRES);
            break;
        }
        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
    }
    else
    {
        Item* item = nullptr;
        uint32 id = 0;
        switch (action)
        {
            case WEP2H_SUPERIOR_IMPACT:
            case WEP2H_AGILITY:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                if (item && (action == WEP2H_AGILITY || action == WEP2H_SUPERIOR_IMPACT))
                {
                    if (item->GetProto()->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 && item->GetProto()->SubClass != ITEM_SUBCLASS_WEAPON_MACE2
                        && item->GetProto()->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 && item->GetProto()->SubClass != ITEM_SUBCLASS_WEAPON_POLEARM
                        && item->GetProto()->SubClass != ITEM_SUBCLASS_WEAPON_STAFF)
                    {
                        player->GetSession()->SendNotification("Requires 2 handed weapon");
                        player->CLOSE_GOSSIP_MENU();
                        return true;
                    }
                }
                if (action == WEP2H_SUPERIOR_IMPACT)
                    id = 1896;
                else if (action == WEP2H_AGILITY)
                    id = 2646;
                break;

            case WEP_CRUSADER:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                id = 1900;
                break;
            case WEP1H_AGILITY:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                id = 2564;
                break;
            case WEP_SPELLPOWER:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                id = 2504;
                break;
            case WEP_HEAL:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                id = 2505;
                break;

            case OFFHAND_SPIRIT:
            case OFFHAND_STAM:
            case OFFHAND_FROSTRES:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
                if (item && item->GetProto()->SubClass != ITEM_SUBCLASS_ARMOR_SHIELD)
                {
                    player->GetSession()->SendNotification("Requires Shield");
                    player->CLOSE_GOSSIP_MENU();
                    return true;
                }
                if (action == OFFHAND_SPIRIT)
                    id = 1890;
                else if (action == OFFHAND_FROSTRES)
                    id = 926;
                else if (action == OFFHAND_STAM)
                    id = 929;
                break;
            case CHEST_STATS:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST);
                id = 1891;
                break;
            case CLOAK_DODGE:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK);
                id = 2622;
                break;
            case CLOAK_SUB:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK);
                id = 2621;
                break;
            case CLOAK_ARMOR:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK);
                id = 1889;
                break;
            case CLOAK_AGILITY:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK);
                id = 849;
                break;
            case BRACER_STAM:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS);
                id = 1886;
                break;
            case BRACER_STR:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS);
                id = 1885;
                break;
            case BRACER_HEAL:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS);
                id = 2566;
                break;
            case BRACER_INT:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS);
                id = 1883;
                break;
            case GLOVES_AGI:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
                id = 2564;
                break;
            case GLOVES_FIRE:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
                id = 2616;
                break;
            case GLOVES_FROST:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
                id = 2615;
                break;
            case GLOVES_SHADOW:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
                id = 2614;
                break;
            case GLOVES_HEALING:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);
                id = 2617;
                break;
            case BOOTS_AGI:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET);
                id = 904;
                break;
            case BOOTS_SPEED:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET);
                id = 911;
                break;
            case BOOTS_STAM:
                item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET);
                id = 929;
                break;
        }
        Enchant(player, item, id);
        player->CLOSE_GOSSIP_MENU();
    }
    return true;
}



void LearnSkillRecipesHelper(Player *player, uint32 skill_id)
{
    uint32 classmask = player->getClassMask();

    for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
    {
        SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
        if (!skillLine)
            continue;

        // wrong skill
        if (skillLine->skillId != skill_id)
            continue;

        // not high rank
        if (skillLine->forward_spellid)
            continue;

        // skip racial skills
        if (skillLine->racemask != 0)
            continue;

        // skip wrong class skills
        if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
            continue;

        SpellEntry const* spellEntry = sSpellMgr.GetSpellEntry(skillLine->spellId);
        if (!spellEntry || !SpellMgr::IsSpellValid(spellEntry, player, false))
            continue;

        player->learnSpell(skillLine->spellId, false);
    }
}
bool LearnAllRecipesInProfession(Player *pPlayer, SkillType skill)
{
    ChatHandler handler(pPlayer->GetSession());
    char* skill_name;

    SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);

    if (SkillInfo == nullptr)
    {
        sLog.outError("Profession NPC: received non-valid skill ID");
        return false;
    }

    skill_name = SkillInfo->name[sWorld.GetDefaultDbcLocale()];

    //pPlayer->SetSkill(SkillInfo->id, 300, 300);
    LearnSkillRecipesHelper(pPlayer, SkillInfo->id);
    pPlayer->GetSession()->SendNotification("All recipes for %s learned", skill_name);
    return true;
}

bool GossipHello_ProfessionNPC(Player* player, Creature* creature)
{

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Alchemy",              GOSSIP_SENDER_MAIN, 1);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Blacksmithing",        GOSSIP_SENDER_MAIN, 2);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Leatherworking",       GOSSIP_SENDER_MAIN, 3);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Tailoring",            GOSSIP_SENDER_MAIN, 4);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Engineering",          GOSSIP_SENDER_MAIN, 5);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Enchanting",           GOSSIP_SENDER_MAIN, 6);
    //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Jewelcrafting",      GOSSIP_SENDER_MAIN, 7);
    //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Inscription",        GOSSIP_SENDER_MAIN, 8);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Herbalism",            GOSSIP_SENDER_MAIN, 9);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Skinning",             GOSSIP_SENDER_MAIN, 10);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Mining",               GOSSIP_SENDER_MAIN, 11);

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "First Aid",            GOSSIP_SENDER_MAIN, 12);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Fishing",              GOSSIP_SENDER_MAIN, 13);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Cooking",              GOSSIP_SENDER_MAIN, 14);

    player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());

    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
	player->SEND_VENDORLIST(creature->GetGUID());
    return true;
}


bool GossipHello_ProfessionAlchemyNPC(Player* player, Creature* creature)
{
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Alchemy", GOSSIP_SENDER_MAIN, 1);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, 15);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "What can you train me?", GOSSIP_SENDER_MAIN, 16);
	player->SEND_GOSSIP_MENU(90373, creature->GetGUID());
	creature->HandleEmote(EMOTE_ONESHOT_BOW);
	return true;
}

bool GossipHello_ProfessionBlacksmithingNPC(Player* player, Creature* creature)
{

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Blacksmithing", GOSSIP_SENDER_MAIN, 2);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, 15);
	player->SEND_GOSSIP_MENU(90373, creature->GetGUID());
	creature->HandleEmote(EMOTE_ONESHOT_BOW);
	return true;
}

bool GossipHello_ProfessionLeatherworkingNPC(Player* player, Creature* creature)
{

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Leatherworking", GOSSIP_SENDER_MAIN, 3);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, 15);
	player->SEND_GOSSIP_MENU(90373, creature->GetGUID());
	creature->HandleEmote(EMOTE_ONESHOT_BOW);
	return true;
}

bool GossipHello_ProfessionTailoringNPC(Player* player, Creature* creature)
{

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Tailoring", GOSSIP_SENDER_MAIN, 4);
	player->SEND_GOSSIP_MENU(90373, creature->GetGUID());
	creature->HandleEmote(EMOTE_ONESHOT_BOW);
	return true;
}

bool GossipHello_ProfessionEngineeringNPC(Player* player, Creature* creature)
{

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Engineering", GOSSIP_SENDER_MAIN, 5);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, 15);
	player->SEND_GOSSIP_MENU(90373, creature->GetGUID());
	creature->HandleEmote(EMOTE_ONESHOT_BOW);
	return true;
}

bool GossipHello_ProfessionEnchantingNPC(Player* player, Creature* creature)
{

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Enchanting", GOSSIP_SENDER_MAIN, 6);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, 15);
	player->SEND_GOSSIP_MENU(90373, creature->GetGUID());
	creature->HandleEmote(EMOTE_ONESHOT_BOW);
	return true;
}

bool GossipHello_ProfessionHerbalismNPC(Player* player, Creature* creature)
{

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Herbalism", GOSSIP_SENDER_MAIN, 9);
	player->SEND_GOSSIP_MENU(90373, creature->GetGUID());
	creature->HandleEmote(EMOTE_ONESHOT_BOW);
	return true;
}

bool GossipHello_ProfessionSkinningNPC(Player* player, Creature* creature)
{

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Skinning", GOSSIP_SENDER_MAIN, 10);
	player->SEND_GOSSIP_MENU(90373, creature->GetGUID());
	creature->HandleEmote(EMOTE_ONESHOT_BOW);
	return true;
}

bool GossipHello_ProfessionMiningNPC(Player* player, Creature* creature)
{

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Mining", GOSSIP_SENDER_MAIN, 11);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, 15);
	player->SEND_GOSSIP_MENU(90373, creature->GetGUID());
	creature->HandleEmote(EMOTE_ONESHOT_BOW);
	return true;
}

bool GossipHello_ProfessionFirstAidNPC(Player* player, Creature* creature)
{

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "First Aid", GOSSIP_SENDER_MAIN, 12);
	player->SEND_GOSSIP_MENU(90373, creature->GetGUID());
	creature->HandleEmote(EMOTE_ONESHOT_BOW);
	return true;
}

bool GossipHello_ProfessionFishingNPC(Player* player, Creature* creature)
{

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Fishing", GOSSIP_SENDER_MAIN, 13);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, 15);
	player->SEND_GOSSIP_MENU(90373, creature->GetGUID());
	creature->HandleEmote(EMOTE_ONESHOT_BOW);
	return true;
}

bool GossipHello_ProfessionCookingNPC(Player* player, Creature* creature)
{

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Cooking", GOSSIP_SENDER_MAIN, 14);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, 15);
	player->SEND_GOSSIP_MENU(90373, creature->GetGUID());
	creature->HandleEmote(EMOTE_ONESHOT_BOW);
	return true;
}



void CompleteLearnProfession(Player *pPlayer, Creature *pCreature, SkillType skill)
{
    if (pPlayer->GetFreePrimaryProfessionPoints() == 0 && !(skill == SKILL_COOKING || skill == SKILL_FIRST_AID))
    {
        pPlayer->GetSession()->SendNotification("You already know two primary professions.");
    }
    else
    {
        if (!LearnAllRecipesInProfession(pPlayer, skill))
            pPlayer->GetSession()->SendNotification("Internal error.");
    }
}
bool GossipSelect_ProfessionNPC(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    switch (action)
    {
    case 1:
        if (!player->HasSkill(SKILL_ALCHEMY))
            CompleteLearnProfession(player, creature, SKILL_ALCHEMY);
		break;
    case 2:
        if (!player->HasSkill(SKILL_BLACKSMITHING))
            CompleteLearnProfession(player, creature, SKILL_BLACKSMITHING);
        break;
    case 3:
        if (!player->HasSkill(SKILL_LEATHERWORKING))
            CompleteLearnProfession(player, creature, SKILL_LEATHERWORKING);
        break;
    case 4:
        if (!player->HasSkill(SKILL_TAILORING))
            CompleteLearnProfession(player, creature, SKILL_TAILORING);
        break;
    case 5:
        if (!player->HasSkill(SKILL_ENGINEERING))
            CompleteLearnProfession(player, creature, SKILL_ENGINEERING);
        break;
    case 6:
        if (!player->HasSkill(SKILL_ENCHANTING))
            CompleteLearnProfession(player, creature, SKILL_ENCHANTING);
        break;
    case 7:
    case 8:
        break;
    case 9:
        if (!player->HasSkill(SKILL_HERBALISM))
            CompleteLearnProfession(player, creature, SKILL_HERBALISM);
        break;
    case 10:
        if (!player->HasSkill(SKILL_SKINNING))
            CompleteLearnProfession(player, creature, SKILL_SKINNING);
        break;
    case 11:
        if (!player->HasSkill(SKILL_MINING))
            CompleteLearnProfession(player, creature, SKILL_MINING);
        break;
    case 12:
        if (!player->HasSkill(SKILL_FIRST_AID))
            CompleteLearnProfession(player, creature, SKILL_FIRST_AID);
        break;
    case 13:
        if (!player->HasSkill(SKILL_FISHING))
            CompleteLearnProfession(player, creature, SKILL_FISHING);
        break;
    case 14:
        if (!player->HasSkill(SKILL_COOKING))
            CompleteLearnProfession(player, creature, SKILL_COOKING);
        break;
	case 15:
		player->SEND_VENDORLIST(creature->GetGUID());
		break;

	case 16:
		player->SEND_TRAINERLIST(creature->GetGUID());
		break;

    }

    player->CLOSE_GOSSIP_MENU();
    return true;
}

// transmogNPC
bool GossipHello_TransmogNPC(Player* player, Creature* creature)
{
    if (!sWorld.getConfig(CONFIG_BOOL_TRANSMOG_ENABLED))
        return false;

    player->PlayerTalkClass->ClearMenus();

    if (sTransmog.HasItemsForTransmog(player, EQUIPMENT_SLOT_HEAD))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_HEAD, GOSSIP_SENDER_MAIN, GOSSIP_ID_HEAD);

    if (sTransmog.HasItemsForTransmog(player, EQUIPMENT_SLOT_SHOULDERS))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_SHOULDERS, GOSSIP_SENDER_MAIN, GOSSIP_ID_SHOULDERS);

    if (sTransmog.HasItemsForTransmog(player, EQUIPMENT_SLOT_BACK))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_CLOAK, GOSSIP_SENDER_MAIN, GOSSIP_ID_CLOAK);

    if (sTransmog.HasItemsForTransmog(player, EQUIPMENT_SLOT_CHEST))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_CHEST, GOSSIP_SENDER_MAIN, GOSSIP_ID_CHEST);

    if (sTransmog.HasItemsForTransmog(player, EQUIPMENT_SLOT_WRISTS))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_WRISTS, GOSSIP_SENDER_MAIN, GOSSIP_ID_WRISTS);

    if (sTransmog.HasItemsForTransmog(player, EQUIPMENT_SLOT_HANDS))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_HANDS, GOSSIP_SENDER_MAIN, GOSSIP_ID_HANDS);

    if (sTransmog.HasItemsForTransmog(player, EQUIPMENT_SLOT_WAIST))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_WAIST, GOSSIP_SENDER_MAIN, GOSSIP_ID_WAIST);

    if (sTransmog.HasItemsForTransmog(player, EQUIPMENT_SLOT_LEGS))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_LEGS, GOSSIP_SENDER_MAIN, GOSSIP_ID_LEGS);

    if (sTransmog.HasItemsForTransmog(player, EQUIPMENT_SLOT_FEET))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_FEET, GOSSIP_SENDER_MAIN, GOSSIP_ID_FEET);

    if (Item* it = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND))
    {
        if (sTransmog.HasItemsForTransmog(player, EQUIPMENT_SLOT_MAINHAND))
            if (it->GetProto()->InventoryType == INVTYPE_WEAPON)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_MAINHAND, GOSSIP_SENDER_MAIN, GOSSIP_ID_ONEHAND_MAIN);
            else
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_MAINHAND, GOSSIP_SENDER_MAIN, it->GetProto()->InventoryType);
    }

    if (Item* it = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND))
    {
        if (sTransmog.HasItemsForTransmog(player, EQUIPMENT_SLOT_OFFHAND))
            if (it->GetProto()->InventoryType == INVTYPE_WEAPON)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_OFFHAND, GOSSIP_SENDER_MAIN, GOSSIP_ID_ONEHAND_OFF);
            else
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_OFFHAND, GOSSIP_SENDER_MAIN, it->GetProto()->InventoryType);
    }

    if (sTransmog.HasItemsForTransmog(player, EQUIPMENT_SLOT_RANGED))
        if (Item* it = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, GOSSIP_TEXT_RANGED, GOSSIP_SENDER_MAIN, it->GetProto()->InventoryType);

    player->SEND_GOSSIP_MENU(GOSSIP_TEXT_1, creature->GetGUID());
    return true;
}

bool GossipSelect_TransmogNPC(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (!sWorld.getConfig(CONFIG_BOOL_TRANSMOG_ENABLED))
        return false;

    uint8 weapon_eqType = 0;
    uint8 slotType = sTransmog.GetEquipmentSlot(action);
    switch (sender)
    {
    case GOSSIP_SENDER_MAIN:
        if (action == GOSSIP_ID_ONEHAND_MAIN)
        {
            action = INVTYPE_WEAPONMAINHAND;
            slotType = EQUIPMENT_SLOT_MAINHAND;
        }
        else if (action == GOSSIP_ID_ONEHAND_OFF)
        {
            action = INVTYPE_WEAPONOFFHAND;
            slotType = EQUIPMENT_SLOT_OFFHAND;
        }

        player->CLOSE_GOSSIP_MENU();
        sTransmog.GetTransmogItems(player, creature, action, slotType);
        break;
    case GOSSIP_SENDER_TRANSMOGRIFY:
        if (action > GOSSIP_INDEX_MAINHAND && action < GOSSIP_INDEX_OFFHAND)
        {
            weapon_eqType = EQUIPMENT_SLOT_MAINHAND;
            action -= GOSSIP_INDEX_MAINHAND;
        }
        else if (action > GOSSIP_INDEX_OFFHAND)
        {
            weapon_eqType = EQUIPMENT_SLOT_OFFHAND;
            action -= GOSSIP_INDEX_OFFHAND;
        }
        //transmog!
        if (const ItemPrototype* itemTransmogProto = sObjectMgr.GetItemPrototype(action))
        {
            uint32 buyPrice = itemTransmogProto->BuyPrice;

            uint8 iType = sTransmog.GetEquipmentSlot(itemTransmogProto->InventoryType);
            if (weapon_eqType != 0)
                iType = weapon_eqType;

            if (Item* itemToTransmog = player->GetItemByPos(INVENTORY_SLOT_BAG_0, iType))
            {
                Item* itemTransmog = Item::CreateItem(itemTransmogProto->ItemId, 1, nullptr);
                if (itemToTransmog->GetEntry() == itemTransmog->GetEntry())
                {
                    sTransmog._DoTransmog(player, itemToTransmog, itemTransmog);
                    sTransmog.DeleteTransmogItemFromDB(itemToTransmog->GetGUIDLow());
                    return true;
                }

                uint32 fakeEntry = sTransmog.GenerateFakeItemEntry(itemToTransmog->GetProto(), itemTransmogProto);
                if(fakeEntry == 0)
                    return true;

                itemTransmogProto = sTransmog.GetOrCreateFakeItemProto(fakeEntry, itemToTransmog->GetProto(), itemTransmogProto);
                if (!itemTransmogProto)
                    return true;

                itemTransmog = Item::CreateItem(itemTransmogProto->ItemId, 1, nullptr);

                if (sTransmog.CanBuy(player, buyPrice))
                {
                    if (sTransmog._DoTransmog(player, itemToTransmog, itemTransmog))
                        CharacterDatabase.PExecute("REPLACE INTO character_transmog (itemguid, fakeentry, ownerguid, oldentry, newentry) VALUES (%u, %u, %u, %u, %u)",
                            itemToTransmog->GetGUIDLow(), itemTransmog->GetEntry(), player->GetGUIDLow(), itemToTransmog->GetEntry(), action);
                }
                else
                    player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, creature, 0, 0);
            }
        }
        break;
    }

    return true;
}

// NOTE: Nostalgia WoW AOE Spell Cast for Horde & Alliance Buffs
struct SpawnLocation
{
	float m_fX, m_fY, m_fZ;
};

static const SpawnLocation aRallyGeneratorLocs[6] =
{
	{ -1812.83f, -4191.94f, 4.78f }, // (Middle)
	{ -1878.186f, -4325.56f, 0.00f }, // (East)
	{ -1972.38f, -4083.60f, 2.04f }, // (South)
	{ -1820.36f, -4050.87f, 55.79f }, // (West)
	{ -1669.12f, -4230.29f, 1.99f }, // (North)

};

enum
{
	SPELL_RALLYING_CRY_DRAGONSLAYER = 22888,
	SPELL_WARCHIEF_BLESSING = 16609,
	NPC_RALLY_CRY_GENERATOR = 1201165,

	MAX_RALLY_GENERATORS = 5,

	QUEST_ONY_HORDE = 30150,
	QUEST_ONY_ALLIANCE = 30154,
	QUEST_NEF_HORDE = 30151,
	QUEST_NEF_ALLIANCE = 30153,
	QUEST_WARCHIEF = 30152,

	YELL_ONY_REWARD_1 = -1901174,
	YELL_ONY_REWARD_2 = -1901173,

	YELL_NEF_REWARD_1 = -1901171,
	YELL_NEF_REWARD_2 = -1901172,

	YELL_WARCHIEF_BLESSING_1 = -1901175,
	YELL_WARCHIEF_BLESSING_2 = -1901176,

	GO_NEFARIANS_HEAD_HORDE = 179881,
	GO_ONYXIAS_HEAD_HORDE = 179556,
	GO_PRISON_FIRE = 184743,
	SPELL_THROW_LIQUID_FIRE = 19784,
	NPC_PRISONER = 1201192,
	NPC_PRISONER1 = 1201194,
	NPC_PRISONER2 = 1201193,
	COIN_SOUND = 1204,
	GUARD_SAY_WAIT = -1999964,
	GUARD_SAY_BURN = -1999965,
	GUARD_EMOTE_EYES = -1999966
};

struct MallAOESpellNPCAI : public ScriptedAI
{
	MallAOESpellNPCAI(Creature* pCreature) : ScriptedAI(pCreature)
	{
		Reset();
	}
	uint32 m_uiTick;
	uint32 m_uiDialogueTimer;
	bool m_bRallyingCryEvent;
	ObjectGuid m_playerGuid;
	uint32 m_currentQuest;

	void SetCurrentQuest(uint32 currentQuest)
	{
		m_currentQuest = currentQuest;
	}

	void Reset()
	{
		m_uiTick = 0;
		m_uiDialogueTimer = 2000;
		m_bRallyingCryEvent = false;
		m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
		m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
	}

	void StartRallyEvent(ObjectGuid playerGuid)
	{
		m_playerGuid = playerGuid;
		m_bRallyingCryEvent = true;
		m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
		m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
	}

	void MovementInform(uint32 uiType, uint32 uiPointId)
	{
		if (uiType != POINT_MOTION_TYPE)
			return;

		switch (uiPointId)
		{
		case 0:
			m_creature->GetMotionMaster()->MovePoint(1, -1812.9903, -4179.3437f, 7.350588f);
			break;
		case 1:
			m_uiDialogueTimer = 1000;
			m_uiTick++;
			break;
		case 2:
			m_creature->GetMotionMaster()->MovePoint(3, -1822.05f, -4189.0239f, 3.99778f);
			break;
		case 3:
			Reset();
			break;
		}
	}

	void UpdateAI(uint32 const uiDiff)
	{

		if (m_bRallyingCryEvent)
		{
			if (m_uiDialogueTimer <= uiDiff)
			{
				switch (m_uiTick)
				{
				case 0:
					m_creature->GetMotionMaster()->MovePoint(0, -1813.31f, -4177.73f, 7.77f, MOVE_PATHFINDING);
					m_uiDialogueTimer = 30000; //handled by MovementInform
					break;
				case 1:
					if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid))
					{
						if (m_currentQuest == QUEST_ONY_ALLIANCE || m_currentQuest == QUEST_ONY_HORDE) {
							m_creature->HandleEmote(EMOTE_ONESHOT_SHOUT);
							m_creature->MonsterYellToZone(YELL_ONY_REWARD_1, 0, pPlayer);
						}
						else if (m_currentQuest == QUEST_NEF_HORDE || m_currentQuest == QUEST_NEF_ALLIANCE) {
							m_creature->HandleEmote(EMOTE_ONESHOT_SHOUT);
							m_creature->MonsterYellToZone(YELL_NEF_REWARD_1, 0, pPlayer);
						}
						else if (m_currentQuest == QUEST_WARCHIEF) {
							m_creature->HandleEmote(EMOTE_ONESHOT_SHOUT);
							m_creature->MonsterYellToZone(YELL_WARCHIEF_BLESSING_1, 0, pPlayer);
						}
					}

					if (m_currentQuest == QUEST_ONY_ALLIANCE || m_currentQuest == QUEST_ONY_HORDE)
					{

						if (GameObject* pGo = m_creature->FindNearestGameObject(GO_ONYXIAS_HEAD_HORDE, 150.0f)) 
						{

							if (!pGo->isSpawned())
							{
								pGo->SetRespawnTime(7200);
								pGo->Refresh();
							}
						}

					}
					else if (m_currentQuest == QUEST_NEF_HORDE || m_currentQuest == QUEST_NEF_ALLIANCE)
					{

						if (GameObject* pGo = m_creature->FindNearestGameObject(GO_NEFARIANS_HEAD_HORDE, 150.0f))
						{

							if (!pGo->isSpawned())
							{
								pGo->SetRespawnTime(7200);
								pGo->Refresh();
							}
						}
					}
						
					m_uiDialogueTimer = 8000;
					m_uiTick++;
					break;
					
				case 2:
					if (m_currentQuest == QUEST_ONY_ALLIANCE || m_currentQuest == QUEST_ONY_HORDE) {
						m_creature->HandleEmote(EMOTE_ONESHOT_SHOUT);
						m_creature->MonsterYellToZone(YELL_ONY_REWARD_2, 0);

						if (GameObject* pGo = m_creature->FindNearestGameObject(GO_ONYXIAS_HEAD_HORDE, 150.0f))
						{
							pGo->SetGoState(GO_STATE_ACTIVE);
						}
					}
					else if (m_currentQuest == QUEST_NEF_HORDE || m_currentQuest == QUEST_NEF_ALLIANCE) {
						m_creature->HandleEmote(EMOTE_ONESHOT_SHOUT);
						m_creature->MonsterYellToZone(YELL_NEF_REWARD_2, 0);

						if (GameObject* pGo = m_creature->FindNearestGameObject(GO_NEFARIANS_HEAD_HORDE, 150.0f))
						{
							pGo->SetGoState(GO_STATE_ACTIVE);
						}
					}
					else if (m_currentQuest == QUEST_WARCHIEF) {
						m_creature->HandleEmote(EMOTE_ONESHOT_SHOUT);
						m_creature->MonsterYellToZone(YELL_WARCHIEF_BLESSING_2);
						}

					m_uiDialogueTimer = 7000;
					m_uiTick++;
					break;
				
				case 3:
					if (m_currentQuest == QUEST_ONY_ALLIANCE || m_currentQuest == QUEST_ONY_HORDE || m_currentQuest == QUEST_NEF_HORDE || m_currentQuest == QUEST_NEF_ALLIANCE) {
						m_creature->CastSpell(m_creature, SPELL_RALLYING_CRY_DRAGONSLAYER, true);
						for (uint8 i = 0; i < MAX_RALLY_GENERATORS; ++i)
						{
							if (Creature* pGenerator = m_creature->SummonCreature(NPC_RALLY_CRY_GENERATOR, aRallyGeneratorLocs[i].m_fX, aRallyGeneratorLocs[i].m_fY, aRallyGeneratorLocs[i].m_fZ, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 1000))
								pGenerator->CastSpell(pGenerator, SPELL_RALLYING_CRY_DRAGONSLAYER, true);
						}
					}
					else if (m_currentQuest == QUEST_WARCHIEF) {

						m_creature->CastSpell(m_creature, SPELL_WARCHIEF_BLESSING, true);
						for (uint8 i = 0; i < MAX_RALLY_GENERATORS; ++i)
						{
							if (Creature* pGenerator = m_creature->SummonCreature(NPC_RALLY_CRY_GENERATOR, aRallyGeneratorLocs[i].m_fX, aRallyGeneratorLocs[i].m_fY, aRallyGeneratorLocs[i].m_fZ, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 1000))
								pGenerator->CastSpell(pGenerator, SPELL_WARCHIEF_BLESSING, true);
						}
					}
					m_uiDialogueTimer = 2000;
					m_uiTick++;
					break;
				case 4:
					m_creature->GetMotionMaster()->MovePoint(2, -1822.32f, -4188.29f, 4.05919f);
					m_uiDialogueTimer = 30000; //handled by MovementInform
					return;
					
				}
			}
			else m_uiDialogueTimer -= uiDiff;
		}

		if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
			return;

		DoMeleeAttackIfReady();
	}
};

CreatureAI* GetAI_MallAOESpellNPC(Creature* pCreature)
{
	return new MallAOESpellNPCAI(pCreature);
}


bool QuestRewarded_MallAOESpellNPC(Player* pPlayer, Creature* pCreature, Quest const* quest)
{
	uint32 currentQuest = quest->GetQuestId();

	if (MallAOESpellNPCAI* pAOESpellNPC = dynamic_cast<MallAOESpellNPCAI*>(pCreature->AI()))
		pAOESpellNPC->SetCurrentQuest(currentQuest);

	if (quest->GetQuestId() == QUEST_ONY_ALLIANCE || quest->GetQuestId() == QUEST_ONY_HORDE)
	{
		if (MallAOESpellNPCAI* pAOESpellNPC = dynamic_cast<MallAOESpellNPCAI*>(pCreature->AI()))
			pAOESpellNPC->StartRallyEvent(pPlayer->GetObjectGuid());
	}

	else if (quest->GetQuestId() == QUEST_NEF_HORDE || quest->GetQuestId() == QUEST_NEF_ALLIANCE)
	{
		if (MallAOESpellNPCAI* pAOESpellNPC = dynamic_cast<MallAOESpellNPCAI*>(pCreature->AI()))
			pAOESpellNPC->StartRallyEvent(pPlayer->GetObjectGuid());
	}

	else if (quest->GetQuestId() == QUEST_WARCHIEF)
	{
		if (MallAOESpellNPCAI* pAOESpellNPC = dynamic_cast<MallAOESpellNPCAI*>(pCreature->AI()))
			pAOESpellNPC->StartRallyEvent(pPlayer->GetObjectGuid());
	}
	return true;
}

class StevenGuardEvent : public BasicEvent
{
public: 
	StevenGuardEvent(Player* plr, Creature* cr) : BasicEvent(), m_player(plr), m_creature(cr) {}

	bool Execute(uint64 /*e_time*/, uint32 /*p_time*/) override
	{

		Unit* pTarget1 = m_creature->FindNearestCreature(NPC_PRISONER1, 150.0f, true);
		Unit* pTarget2 = m_creature->FindNearestCreature(NPC_PRISONER2, 150.0f, true);
		Unit* pTarget = m_creature->FindNearestCreature(NPC_PRISONER, 150.0f, true);

		if (pTarget)
		{

			if (GameObject* pGo = m_creature->FindNearestGameObject(GO_PRISON_FIRE, 150.0f))
			{
				if (!pGo->isSpawned())
				{
					pGo->SetRespawnTime(10);
					pGo->Refresh();
				}
				else
				{
					pGo->SetGoState(GO_STATE_ACTIVE);
					m_player->CLOSE_GOSSIP_MENU();
				}

			}


			pTarget->SetHealthPercent(0.00f);
			pTarget->SetDeathState(JUST_DIED);
			pTarget1->SetHealthPercent(0.00f);
			pTarget1->SetDeathState(JUST_DIED);
			pTarget2->SetHealthPercent(0.00f);
			pTarget2->SetDeathState(JUST_DIED);

			return true;
		}
		else
			m_creature->m_Events.AddEvent(new StevenGuardEvent(m_player, m_creature), m_creature->m_Events.CalculateTime(1500));
		return true;
	}

private:
	Player* m_player;
	Creature* m_creature;

};


bool GossipHello_StevenGuardNPC(Player* player, Creature* _Creature)
{
	player->PlayerTalkClass->ClearMenus();
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, "What are they guilty of?", GOSSIP_SENDER_MAIN, 200);
	player->SEND_GOSSIP_MENU(120001, _Creature->GetGUID());
	return true;
}


bool GossipDefault_StevenGuardNPC(Player* player, Creature* _Creature, uint32 action)
{
	Unit* pTarget = _Creature->FindNearestCreature(NPC_PRISONER, 150.0f, true);

	switch (action)
	{
	case 200:

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Here's 100g - torch 'em.", GOSSIP_SENDER_MAIN, 201);
		player->SEND_GOSSIP_MENU(120002, _Creature->GetGUID());
		break;

	case 201:
		float cOrientation = _Creature->GetOrientation();
		
		if (!pTarget)
			{
			_Creature->MonsterSay("Let's give their corpses a minute to cool off before we light em up again."); 
			player->CLOSE_GOSSIP_MENU();
			}
		else
		{

			if (player->GetMoney() < 1000000)
			{
				_Creature->MonsterSay("Come back when you've got enough gold.");
				player->CLOSE_GOSSIP_MENU();
				return false;
			}
			else {
				player->ModifyMoney(-1000000); // Take payment
				_Creature->HandleEmote(EMOTE_ONESHOT_ATTACK1H);
				_Creature->PlayDirectSound(COIN_SOUND, player); // Coin sound

				
				_Creature->MonsterTextEmote(GUARD_EMOTE_EYES);
				_Creature->MonsterSay(GUARD_SAY_BURN);
				_Creature->CastSpell(pTarget, SPELL_THROW_LIQUID_FIRE, false);

				_Creature->m_Events.AddEvent(new StevenGuardEvent(player, _Creature), _Creature->m_Events.CalculateTime(1500));
				_Creature->SetOrientation(cOrientation);
			}
		}  player->CLOSE_GOSSIP_MENU();
		
		break;

	}
	return true;
}

bool GossipSelect_StevenGuardNPC(Player* player, Creature* _Creature, uint32 sender, uint32 action)
{
	// Main menu
	if (sender == GOSSIP_SENDER_MAIN)
		GossipDefault_StevenGuardNPC(player, _Creature, action);

	return true;

}


struct MallGuardSwitchAI : public ScriptedAI
{

	MallGuardSwitchAI(Creature* pCreature) : ScriptedAI(pCreature)
	{
		JustRespawned();
	}

	void Reset() 
	{
	}

	void JustRespawned() {
		if (m_creature->GetDisplayId() == 15896) // if is horde
		{
			m_creature->SetDisplayId(7308); // set to alliance
		}
		else if (m_creature->GetDisplayId() == 7308)
			m_creature->SetDisplayId(15896);
	}
};

CreatureAI* GetAI_MallGuardSwitchNPC(Creature* pCreature)
{
	return new MallGuardSwitchAI(pCreature);
};





void AddSC_custom_creatures()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "custom_TeleportNPC";
    newscript->pGossipHello = &GossipHello_TeleportNPC;
    newscript->pGossipSelect = &GossipSelect_TeleportNPC;
    newscript->RegisterSelf(true);

    newscript = new Script;
    newscript->Name = "custom_ArenaTeleportNPC";
    newscript->pGossipHello = &GossipHello_TeleportArenaNPC;
    newscript->pGossipSelect = &GossipSelect_TeleportArenaNPC;
    newscript->RegisterSelf(true);

    newscript = new Script;
    newscript->Name = "custom_PortalTeleportNPC";
    newscript->pGossipHello = &GossipHello_ArenaPortalPhaseNPC;
    newscript->pGossipSelect = &GossipSelect_TeleportArenaNPC;
    newscript->RegisterSelf(true);

    newscript = new Script;
    newscript->Name = "custom_EnchantNPC";
    newscript->pGossipHello = &GossipHello_EnchantNPC;
    newscript->pGossipSelect = &GossipSelect_EnchantNPC;
    newscript->RegisterSelf(true);

    newscript = new Script;
    newscript->Name = "custom_ProfessionsNPC";
    newscript->pGossipHello = &GossipHello_ProfessionNPC;
    newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
    newscript->RegisterSelf(true);

    newscript = new Script;
    newscript->Name = "custom_TransmogNPC";
    newscript->pGossipHello = &GossipHello_TransmogNPC;
    newscript->pGossipSelect = &GossipSelect_TransmogNPC;
    newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_BoatTeleportNPC";
	newscript->pGossipHello = &GossipHello_BoatTeleportNPC;
	newscript->pGossipSelect = &GossipSelect_BoatTeleportNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_ProfessionsAlchemyNPC";
	newscript->pGossipHello = &GossipHello_ProfessionAlchemyNPC;
	newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_ProfessionsBlacksmithingNPC";
	newscript->pGossipHello = &GossipHello_ProfessionBlacksmithingNPC;
	//newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_ProfessionsLeatherworkingNPC";
	newscript->pGossipHello = &GossipHello_ProfessionLeatherworkingNPC;
	//newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_ProfessionsTailoringNPC";
	newscript->pGossipHello = &GossipHello_ProfessionTailoringNPC;
//	newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_ProfessionsEnginerringNPC";
	newscript->pGossipHello = &GossipHello_ProfessionEngineeringNPC;
//	newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_ProfessionsEnchantingNPC";
	newscript->pGossipHello = &GossipHello_ProfessionEnchantingNPC;
//	newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_ProfessionsHerbalismNPC";
	newscript->pGossipHello = &GossipHello_ProfessionHerbalismNPC;
//	newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_ProfessionsSkinningNPC";
	newscript->pGossipHello = &GossipHello_ProfessionSkinningNPC;
//	newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_ProfessionsMiningNPC";
	newscript->pGossipHello = &GossipHello_ProfessionMiningNPC;
//	newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_ProfessionsFirstAidNPC";
	newscript->pGossipHello = &GossipHello_ProfessionFirstAidNPC;
//	newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_ProfessionsFishingNPC";
	newscript->pGossipHello = &GossipHello_ProfessionFishingNPC;
//	newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_ProfessionsCookingNPC";
	newscript->pGossipHello = &GossipHello_ProfessionCookingNPC;
//	newscript->pGossipSelect = &GossipSelect_ProfessionNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_MallAOESpellNPC";
	newscript->GetAI = &GetAI_MallAOESpellNPC;
	newscript->pQuestRewardedNPC = &QuestRewarded_MallAOESpellNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_StevenGuardNPC"; 
	newscript->pGossipHello = &GossipHello_StevenGuardNPC;
	newscript->pGossipSelect = &GossipSelect_StevenGuardNPC;
	//newscript->GetAI = &GetAI_StevenGuardNPC;
	newscript->RegisterSelf(true);

	newscript = new Script;
	newscript->Name = "custom_MallGuardSwitchNPC";
	newscript->GetAI = &GetAI_MallGuardSwitchNPC;
	newscript->RegisterSelf(true);

}
