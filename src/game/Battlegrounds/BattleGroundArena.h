///*
// * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
// * Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
// * Copyright (C) 2011-2016 Nostalrius <https://nostalrius.org>
// * Copyright (C) 2016-2017 Elysium Project <https://github.com/elysium-project>
// *
// * This program is free software; you can redistribute it and/or modify
// * it under the terms of the GNU General Public License as published by
// * the Free Software Foundation; either version 2 of the License, or
// * (at your option) any later version.
// *
// * This program is distributed in the hope that it will be useful,
// * but WITHOUT ANY WARRANTY; without even the implied warranty of
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// * GNU General Public License for more details.
// *
// * You should have received a copy of the GNU General Public License
// * along with this program; if not, write to the Free Software
// * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// */
//

#ifndef __BATTLEGROUNDARENA_H
#define __BATTLEGROUNDARENA_H

#include "Common.h"
#include "BattleGround.h"

enum BG_Arena_Timers
{
   
};

enum BG_Arena_Score
{
    
};

#define BG_AB_NODES_MAX   5


enum BG_Arena_Sounds
{
 //   BG_AB_SOUND_NODE_CLAIMED            = 8192,
 //   BG_AB_SOUND_NODE_CAPTURED_ALLIANCE  = 8173,
 //   BG_AB_SOUND_NODE_CAPTURED_HORDE     = 8213,
 //   BG_AB_SOUND_NODE_ASSAULTED_ALLIANCE = 8212,
 //   BG_AB_SOUND_NODE_ASSAULTED_HORDE    = 8174,
	//BG_AB_SOUND_NEAR_VICTORY_ALLIANCE = 8457,
	//BG_AB_SOUND_NEAR_VICTORY_HORDE = 8456
};

enum BG_Arena_NodeOccupiedCredit
{
    //BG_AB_NODE_STABLES_CREDIT       = 15001,
    //BG_AB_NODE_BLACKSMITH_CREDIT    = 15002,
    //BG_AB_NODE_FARM_CREDIT          = 15003,
    //BG_AB_NODE_LUMBER_MILL_CREDIT   = 15004,
    //BG_AB_NODE_GOLD_MINE_CREDIT     = 15005,
};

// [-PROGRESSIVE] Patch 1.9 and less code:
#define BG_AB_NotABBGWeekendHonorTicks      330
#define BG_AB_ABBGWeekendHonorTicks         200
#define BG_AB_NotABBGWeekendReputationTicks 330
#define BG_AB_ABBGWeekendReputationTicks    200

//// Tick intervals and given points: case 0,1,2,3,4,5 captured nodes
//const uint32 BG_AB_TickIntervals[6] = {0, 12000, 9000, 6000, 3000, 1000};
//const uint32 BG_AB_TickPoints[6] = {0, 10, 10, 10, 10, 30};
//
//// Honor granted depending on player's level
//const uint32 BG_AB_PerTickHonor[MAX_BATTLEGROUND_BRACKETS] = {41, 68, 113, 189, 198};
//const uint32 BG_AB_WinMatchHonor[MAX_BATTLEGROUND_BRACKETS] = {41, 68, 113, 189, 198};

// WorldSafeLocs ids for 5 nodes, and for ally, and horde starting location
//const uint32 BG_AB_GraveyardIds[7] = {895, 894, 893, 897, 896, 898, 899};

// x, y, z, o
// Nostalrius: Modified to retail 5.4.8 positions.
//const float BG_AB_BuffPositions[BG_AB_NODES_MAX][4] = {
//    {1185.566f, 1184.629f, -56.36329f, 2.303831f},         // stables
//    {989.939026f, 1008.75f, -42.60327f, 0.8203033f},       // blacksmith
//    {818.0089f, 842.3543f, -56.54062f, 3.176533f},         // farm
//    {808.8463f, 1185.417f, 11.92161f, 5.619962f},          // lumber mill
//    {1147.091f, 816.8362f, -98.39896f, 6.056293f}          // gold mine
//};

class BattleGroundArenaScore : public BattleGroundScore
{
    public:
		BattleGroundArenaScore(): Kills(0), Deaths(0) {};
        virtual ~BattleGroundArenaScore() {};
        uint32 Kills;
        uint32 Deaths;
};

class BattleGroundArena : public BattleGround
{
    friend class BattleGroundMgr;

    public:
        BattleGroundArena();
        ~BattleGroundArena();

        void Update(uint32 diff);
        void AddPlayer(Player *plr);
        //virtual void StartingEventCloseDoors();
        //virtual void StartingEventOpenDoors();
        void RemovePlayer(Player *plr, ObjectGuid guid);
        void HandleAreaTrigger(Player *Source, uint32 Trigger);
        //virtual bool SetupBattleGround();
        virtual void Reset();
        void EndBattleGround(Team winner);
        //virtual WorldSafeLocsEntry const* GetClosestGraveYard(Player* player);
		void PlayerDied(Player* killer, Player* killed, bool disconnected = false);

        /* Scorekeeping */
        virtual void UpdatePlayerScore(Player *Source, uint32 type, uint32 value);

        virtual void FillInitialWorldStates(WorldPacket& data, uint32& count);

        /* Nodes occupying */
        virtual void EventPlayerClickedOnFlag(Player *source, GameObject* target_obj);

    private:
        /* Gameobject spawning/despawning */
        void _CreateBanner(uint8 node, uint8 type, uint8 teamIndex);
        void _DelBanner(uint8 node, uint8 type, uint8 teamIndex);
        void _SendNodeUpdate(uint8 node);

        /* Creature spawning/despawning */
        // TODO: working, scripted peons spawning
        void _NodeOccupied(uint8 node,Team team);

        int32 _GetNodeNameId(uint8 node);

        /* Nodes info:
            0: neutral
            1: ally contested
            2: horde contested
            3: ally occupied
            4: horde occupied     */
        uint8               m_Nodes[BG_AB_NODES_MAX];
        uint8               m_prevNodes[BG_AB_NODES_MAX];   // used for performant wordlstate-updating
        uint32              m_NodeTimers[BG_AB_NODES_MAX];
        uint32              m_lastTick[BG_TEAMS_COUNT];
        uint32              m_HonorScoreTics[BG_TEAMS_COUNT];
        uint32              m_ReputationScoreTics[BG_TEAMS_COUNT];
        bool                m_IsInformedNearVictory;
        uint32              m_HonorTics;
        uint32              m_ReputationTics;
};
#endif
