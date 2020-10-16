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

void AddSC_zero_scripts()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "go_auto_fireworks";
	newscript->GOGetAI = GetAI_go_auto_fireworks;
	newscript->RegisterSelf();
	//AddSC_zero_creatures();
	AddSC_custom_creatures();
}