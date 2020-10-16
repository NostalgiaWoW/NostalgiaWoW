
#include "scriptPCH.h"

enum
{
    NPC_INFERNAL = 1000550,
    NPC_FELGUARD = 1000551,
    NPC_FELHOUND = 1000552,
    MAX_DEMONS = 5,

    CUSTOM_FELGUARD_SAY1 = -1999927,
    CUSTOM_FELGUARD_SAY2 = -1999928,
    CUSTOM_FELGUARD_SAY3 = -1999929,
    CUSTOM_FELGUARD_SAY4 = -1999930,
    CUSTOM_FELGUARD_SAY5 = -1999931,
    CUSTOM_FELGUARD_SAY6 = -1999932
};

int32 felguardRandomSay[] = { CUSTOM_FELGUARD_SAY1, CUSTOM_FELGUARD_SAY2, CUSTOM_FELGUARD_SAY3, CUSTOM_FELGUARD_SAY4, CUSTOM_FELGUARD_SAY5, CUSTOM_FELGUARD_SAY6 };
uint32 randDemons[] = { NPC_INFERNAL, NPC_FELGUARD, NPC_FELHOUND };

struct npc_demon_spawnerAI : public ScriptedAI
{
    npc_demon_spawnerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiSpawnTimer;
    uint8 m_Wave;
    std::list<Creature*> m_tmpMobsList;
    std::list<Creature*> m_tmpMobsListAll;

    void Reset()
    {
        m_tmpMobsList.clear();
        m_tmpMobsListAll.clear();
        m_uiSpawnTimer = 120 * IN_MILLISECONDS;
        m_Wave = 0;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_Wave < 15)
        {
            if (m_uiSpawnTimer <= uiDiff)
            {
                std::vector<uint32> mobsEntries;
                mobsEntries.push_back(3296); // Orgrimmar
                mobsEntries.push_back(14720); // Orgrimmar
                mobsEntries.push_back(14392); // Orgrimmar
                mobsEntries.push_back(68); // Stormwind
                mobsEntries.push_back(12480); // Stormwind
                mobsEntries.push_back(12481); // Stormwind
                mobsEntries.push_back(5595); // Ironforge
                mobsEntries.push_back(5624); // Undercity
                mobsEntries.push_back(4262); // Darnas
                mobsEntries.push_back(3084); // Thunderbluff

                for (std::vector<uint32>::iterator it = mobsEntries.begin(); it != mobsEntries.end(); ++it)
                {
                    GetCreatureListWithEntryInGrid(m_tmpMobsList, m_creature, (*it), 245.0f);
                    GetCreatureListWithEntryInGrid(m_tmpMobsListAll, m_creature, (*it), 245.0f);
                }

                float DestX, DestY, DestZ;
                for (int i = 0; i < MAX_DEMONS; ++i)
                {
                    m_creature->GetRandomPoint(m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 45.0f, DestX, DestY, DestZ);
                    if (Creature* demon = m_creature->SummonCreature(randDemons[urand(0, 2)], DestX, DestY, DestZ, 0, TEMPSUMMON_TIMED_DESPAWN, 120 * IN_MILLISECONDS))
                        AggroGuards(demon);
                }

                m_creature->GetRandomPoint(m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 45.0f, DestX, DestY, DestZ);
                if (Creature * demon = m_creature->SummonCreature(NPC_FELGUARD, DestX, DestY, DestZ, 0, TEMPSUMMON_TIMED_DESPAWN, 120 * IN_MILLISECONDS))
                {
                    AggroGuards(demon);
                    DoScriptText(felguardRandomSay[urand(0, 5)], demon);
                }

                m_uiSpawnTimer = 120 * IN_MILLISECONDS;
                m_tmpMobsList.clear();
                m_tmpMobsListAll.clear();
                m_Wave++;
            }
            else m_uiSpawnTimer -= uiDiff;
        } 
        else 
        {
            m_uiSpawnTimer = 10800 * IN_MILLISECONDS;
            m_Wave = 0;
        }
    }

    void AggroGuards(Creature* demon)
    {
        for (std::list<Creature*>::iterator guard = m_tmpMobsListAll.begin(); guard != m_tmpMobsListAll.end(); ++guard)
            if (*guard)
            {
                demon->SetInCombatWith(*guard);
                demon->AddThreat((*guard), 10.0f);
                (*guard)->AddThreat(demon, 10.0f);
            }

        uint32 Var = 0;
        while (Var < 3 && !m_tmpMobsList.empty())
        {
            std::list<Creature*>::iterator itr = m_tmpMobsList.begin();
            if (Creature* guard = *itr)
            {
                demon->SetInCombatWith(guard);
                demon->AddThreat(guard, 60.0f);
                guard->AddThreat(demon, 60.0f);
                m_tmpMobsList.erase(itr);
                Var++;
            }
        }
    }
};

CreatureAI* GetAI_npc_demon_spawner(Creature* pCreature)
{
    return new npc_demon_spawnerAI(pCreature);
}

void AddSC_npc_demon_spawner()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "npc_demon_spawner";
    newscript->GetAI = &GetAI_npc_demon_spawner;
    newscript->RegisterSelf();
}
