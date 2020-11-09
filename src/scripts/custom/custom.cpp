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

const uint32 FireworksNpcIDs[] =
{
	15882, //RED
	15879, //BLUE
	15880, //GREEN
	15881, //PURPLE
	15884, //WHITE
	15883, //YELLOW
};

class auto_fireworks : public GameObjectAI
{
public:
	const uint32 FIREWORKS_LAUNCH_DELAY = 10 * IN_MILLISECONDS;
	const uint32 FIREWORKS_LAUNCH_DELAY_RAND = 5 * IN_MILLISECONDS;

	auto_fireworks(GameObject* pGO)
		: GameObjectAI(pGO)
	{
		timer = 0;
	}

	virtual void UpdateAI(uint32 const deltaTime) override
	{
		if (timer < deltaTime)
		{
			timer = FIREWORKS_LAUNCH_DELAY + urand(0, FIREWORKS_LAUNCH_DELAY_RAND);

			const int32 SizeOfSpells = sizeof(FireworksNpcIDs) / sizeof(uint32);
			int NpcId = urand(0, SizeOfSpells);

			me->SummonCreature(FireworksNpcIDs[NpcId], me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f);
		}
		else
		{
			timer -= deltaTime;
		}
	}

private:
	uint32 timer;
};

GameObjectAI* GetAI_go_auto_fireworks(GameObject* pGo)
{
	return new auto_fireworks(pGo);
}

struct go_mallboat_enter_trigger : public GameObjectAI
{
	explicit go_mallboat_enter_trigger(GameObject* pGo) : GameObjectAI(pGo)
	{
		m_uiUpdateTimer = 1000;
	}

	uint32 m_uiUpdateTimer;

	void UpdateAI(uint32 const uiDiff) override
	{
		if (m_uiUpdateTimer < uiDiff)
		{
			std::list<Player*> players;
			MaNGOS::AnyPlayerInObjectRangeCheck check(me, 2.0f, true, false);
			MaNGOS::PlayerListSearcher<MaNGOS::AnyPlayerInObjectRangeCheck> searcher(players, check);

			Cell::VisitWorldObjects(me, searcher, 8.0f);

			for (Player* pPlayer : players)
			{
				if (!pPlayer->isAlive()) {
					pPlayer->ResurrectPlayer(0.5f);
					pPlayer->SpawnCorpseBones();
				}
				pPlayer->TeleportTo(0, -1846.31f, -4252.70f, 2.13f, 1.283f);
			}
			m_uiUpdateTimer = 1000;
		}
		else
		{
			m_uiUpdateTimer -= uiDiff;
		}
	}
};

GameObjectAI* GetAI_go_mallboat_enter_trigger(GameObject* gameobject)
{
	return new go_mallboat_enter_trigger(gameobject);
}

struct go_cot_exit_trigger : public GameObjectAI
{
	explicit go_cot_exit_trigger(GameObject* pGo) : GameObjectAI(pGo)
	{
		m_uiUpdateTimer = 1000;
	}

	uint32 m_uiUpdateTimer;

	void UpdateAI(uint32 const uiDiff) override
	{
		if (m_uiUpdateTimer < uiDiff)
		{
			std::list<Player*> players;
			MaNGOS::AnyPlayerInObjectRangeCheck check(me, 8.0f, true, false);
			MaNGOS::PlayerListSearcher<MaNGOS::AnyPlayerInObjectRangeCheck> searcher(players, check);

			Cell::VisitWorldObjects(me, searcher, 8.0f);

			for (Player* pPlayer : players)
			{
				//pPlayer->TeleportTo(1, -8349.90f, -4060.05f, -208.06f, 3.48f);
				pPlayer->TeleportTo(1, -8756.86f, -4191.39f, -209.49f, 5.57f);
			}
			m_uiUpdateTimer = 1000;
		}
		else
		{
			m_uiUpdateTimer -= uiDiff;
		}
	}
};

void AddSC_zero_scripts()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "go_auto_fireworks";
	newscript->GOGetAI = GetAI_go_auto_fireworks;
	newscript->RegisterSelf();
	//AddSC_zero_creatures();
	AddSC_custom_creatures();

	newscript = new Script;
    newscript->Name = "go_mallboat_enter_trigger";
    newscript->GOGetAI = &GetAI_go_mallboat_enter_trigger;
    newscript->RegisterSelf();

    //newscript = new Script;
    //newscript->Name = "go_cot_exit_trigger";
    //newscript->GOGetAI = &GetAI_go_cot_exit_trigger;
    //newscript->RegisterSelf();
}