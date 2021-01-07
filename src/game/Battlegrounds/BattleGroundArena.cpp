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


#include "Object.h"
#include "Player.h"
#include "BattleGround.h"
#include "BattleGroundArena.h"
#include "Creature.h"
#include "GameObject.h"
#include "BattleGroundMgr.h"
#include "Language.h"
#include "Util.h"
#include "WorldPacket.h"
#include "MapManager.h"

BattleGroundArena::BattleGroundArena()
{
    m_BuffChange = true;

    m_StartMessageIds[BG_STARTING_EVENT_FIRST]  = 0;
    m_StartMessageIds[BG_STARTING_EVENT_SECOND] = LANG_BG_AB_START_ONE_MINUTE;
    m_StartMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_BG_AB_START_HALF_MINUTE;
    m_StartMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_BG_AB_HAS_BEGUN;
}

BattleGroundArena::~BattleGroundArena()
{
}

void BattleGroundArena::Update(uint32 diff)
{
    if (GetStatus() == STATUS_IN_PROGRESS)
    {
        int team_points[BG_TEAMS_COUNT] = { 0, 0 };

        // Test win condition														/fix? Win condition here?
        if (m_TeamScores[BG_TEAM_ALLIANCE] >= 1)
            EndBattleGround(ALLIANCE);
        if (m_TeamScores[BG_TEAM_HORDE] >= 1)
            EndBattleGround(HORDE);
    }
    // Execute this at the end, since it can delete the BattleGround object!
    BattleGround::Update(diff);
}

void BattleGroundArena::AddPlayer(Player *plr)
{
	BattleGround::AddPlayer(plr);
    //create score and add it to map, default values are set in the constructor
	BattleGroundArenaScore* sc = new BattleGroundArenaScore;

    m_PlayerScores[plr->GetObjectGuid()] = sc;
}

void BattleGroundArena::RemovePlayer(Player * /*plr*/, ObjectGuid /*guid*/)
{

}

void BattleGroundArena::PlayerDied(Player* killer, Player* killed, bool disconnected) // handled by battleground i think
{
}

void BattleGroundArena::HandleAreaTrigger(Player *Source, uint32 Trigger)
{
    
}


void BattleGroundArena::FillInitialWorldStates(WorldPacket& data, uint32& count)
{

}

void BattleGroundArena::_SendNodeUpdate(uint8 node)
{

}

void BattleGroundArena::_NodeOccupied(uint8 node, Team team)
{

}


void BattleGroundArena::EventPlayerClickedOnFlag(Player *source, GameObject* target_obj)
{
    
}

//bool BattleGroundArena::SetupBattleGround()
//{
//   
//}

void BattleGroundArena::Reset()
{
    //call parent's class reset
    BattleGround::Reset();

    //for (uint8 i = 0; i < BG_TEAMS_COUNT; ++i)
    //{
    //    m_TeamScores[i]          = 0;
    //    m_lastTick[i]            = 0;
    //    m_HonorScoreTics[i]      = 0;
    //    m_ReputationScoreTics[i] = 0;
    //}

}

void BattleGroundArena::EndBattleGround(Team winner)
{
    //win reward
    if (winner == ALLIANCE)
    {
        						// add in rewards
    }
    if (winner == HORDE)
    {
       
    }

    BattleGround::EndBattleGround(winner);
}

//WorldSafeLocsEntry const* BattleGroundArena::GetClosestGraveYard(Player* player)
//{
//}

void BattleGroundArena::UpdatePlayerScore(Player *Source, uint32 type, uint32 value)
{
    BattleGroundScoreMap::iterator itr = m_PlayerScores.find(Source->GetObjectGuid());
    if (itr == m_PlayerScores.end())                          // player not found...
        return;

    switch (type)
    {
        case SCORE_BASES_ASSAULTED:
            ((BattleGroundArenaScore*)itr->second)->Kills += value;
            break;
        case SCORE_BASES_DEFENDED:
            ((BattleGroundArenaScore*)itr->second)->Deaths += value;
            break;
        default:
            BattleGround::UpdatePlayerScore(Source, type, value);
            break;
    }
}
