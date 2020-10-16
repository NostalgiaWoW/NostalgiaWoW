/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

// Rewritten completely by Gemt

#include "scriptPCH.h"
#include "naxxramas.h"
#include "Duration.h"

#include <algorithm>

// https://pastebin.com/AXPeUXub
// pastbin link above has various noted timers and sources. Not much useful, but it's some of my notes
// from when researching the encounter.

// Regarding summoning add spells, there are a few spells which summon both two types of mobs, 
// or multiple of the same mob in different locations with the same spell. However
// our core does not support multiple spell target coordinates due to limitations with the DB, so 
// we have to use the spells which summon a single creature.
enum eSpell
{
    SPELL_TP_CENTER           = 29231,
    SPELL_TP_BALC             = 29216,
    SPELL_CRIPPLE             = 29212, // used on players where noth blinked FROM 
    SPELL_CURSE_PLAGUEBRINGER = 29213,
    SPELL_IMMUNE_ALL          = 29230, // used on TP to balc

    SPELL_BLINK_1 = 29208,
    SPELL_BLINK_2 = 29209,
    SPELL_BLINK_3 = 29210,
    SPELL_BLINK_4 = 29211,

    SPELL_SUM_WARR_SW = 29247,
    SPELL_SUM_WARR_NW = 29248,
    SPELL_SUM_WARR_NE = 29249,

    SPELL_SUM_CHAMP_SW1 = 29217,
    SPELL_SUM_CHAMP_SW2 = 29224,
    SPELL_SUM_CHAMP_SW3 = 29225,
    SPELL_SUM_CHAMP_SW4 = 29227,
    
    SPELL_SUM_CHAMP_W   = 29238,
    
    SPELL_SUM_CHAMP_NW1 = 29255,
    SPELL_SUM_CHAMP_NW2 = 29267,
    SPELL_SUM_CHAMP_NW3 = 29257,
    
    SPELL_SUM_CHAMP_NE1 = 29258,
    SPELL_SUM_CHAMP_NE2 = 29262,
    
    SPELL_SUM_GUARD_NE = 29226,
    SPELL_SUM_GUARD_NW = 29239,
    SPELL_SUM_GUARD_SW1 = 29256,
    SPELL_SUM_GUARD_SW2 = 29268,
};

static const uint32 ChampionSpells[10] =
{
    //g1
    SPELL_SUM_CHAMP_SW1,
    SPELL_SUM_CHAMP_SW2,
    SPELL_SUM_CHAMP_SW3,
    SPELL_SUM_CHAMP_SW4,
    //g2
    SPELL_SUM_CHAMP_W,
    SPELL_SUM_CHAMP_NW1,
    SPELL_SUM_CHAMP_NW2,
    SPELL_SUM_CHAMP_NW3,
    //g3
    SPELL_SUM_CHAMP_NE1,
    SPELL_SUM_CHAMP_NE2,
};

static const uint8 g1_start = 0, g1_size = 4;
static const uint8 g2_start = 4, g2_size = 4;
static const uint8 g3_start = 8, g3_size = 2;

static const uint32 GuardianSpells[4] =
{
    SPELL_SUM_GUARD_NE,
    SPELL_SUM_GUARD_NW,
    SPELL_SUM_GUARD_SW1,
    SPELL_SUM_GUARD_SW2,
};

enum eScriptText
{
    SAY_AGGRO1                          = -1533075,
    SAY_AGGRO2                          = -1533076,
    SAY_AGGRO3                          = -1533077,
    SAY_SUMMON                          = -1533078,

    SAY_SLAY1                           = -1533079,
    SAY_SLAY2                           = -1533080,
    SAY_DEATH                           = -1533081,

    // Emotes probably only wotlk
    //EMOTE_WARRIOR                       = -1533130,
    //EMOTE_SKELETON                      = -1533131,
    //EMOTE_TELEPORT                      = -1533132,
    //EMOTE_TELEPORT_RETURN               = -1533133,
};

enum eNPCs
{
    NPC_PLAGUED_GUARDIAN  = 16981,
    NPC_PLAGUED_CONSTRUCT = 16982, // unknown if this was ever used
    NPC_PLAGUED_CHAMPION  = 16983,
    NPC_PLAGUED_WARRIOR   = 16984,
};

enum eEvents
{
    EVENT_BLINK = 1,
    EVENT_CURSE,
    EVENT_TP_BALC,
    EVENT_TP_GROUND,
    EVENT_RMV_INVULN,
    EVENT_BALC_ADDS,
    EVENT_WARRIORS
};

// custom virus event
enum
{
    NPC_VIRUS_EVENT_GOSSIP = 91000,
    NPC_VIRUS_EVENT_TEXT = 1100022,
    SPELL_VOLJIN_CHAINLIGHTNING = 421,

    SPELL_VOLJIN_POWERTOTEM = 13910,
    SPELL_VOLJIN_ICETOTEM = 18975,

    SPELL_JAINA_FROSTBOLT = 116,
    SPELL_JAINA_WHIRLWIND = 568,
    SPELL_JAINA_EVOCATION = 12051,

    SAY_VIRUS_EVENT_JAINA1 = -1999946,
    YELL_VIRUS_EVENT_JAINA2 = -1999947,
    SAY_VIRUS_EVENT_JAINA3 = -1999948,

    SAY_VIRUS_EVENT_VOLJIN1 = -1999949,
    YELL_VIRUS_EVENT_VOLJIN2 = -1999950,
    SAY_VIRUS_EVENT_VOLJIN3 = -1999951,

    PORTAL_DARNASS = 183317,
    PORTAL_IRONFORGE = 183322,
    PORTAL_STORMWIND = 183325,

    PORTAL_UNDERCITY = 183327,
    PORTAL_ORGRIMMAR = 183323,
    PORTAL_THUNDER = 183326,

    FACTION_HORDE = 85,
    FACTION_ALLIANCE = 11,
};

uint32 ve_h_portals[] = { PORTAL_UNDERCITY , PORTAL_ORGRIMMAR , PORTAL_THUNDER };
uint32 ve_a_portals[] = { PORTAL_DARNASS , PORTAL_IRONFORGE , PORTAL_STORMWIND };

struct virus_event_locations
{
    float x, y, z, o;
};

virus_event_locations ve_points[] =
{
    {2968.84f, -3470.74f, 297.72f, 0.74f}, //spawnpoint
    {2953.25f, -3486.05f, 297.63f, 3.95f}, //1
    {2910.79f, -3509.99f, 297.86f, 2.67f}, //2
    {2848.00f, -3490.21f, 297.86f, 3.09f}, //3
    {2834.14f, -3490.59f, 297.85f, 3.16f}, //4
    {2815.10f, -3490.66f, 285.98f, 3.14f}, //5
    {2802.73f, -3490.57f, 285.93f, 3.14f}, //6
    {2783.36f, -3490.30f, 274.06f, 3.14f}, //7
    {2771.37f, -3490.21f, 274.01f, 3.15f}, //8
    {2751.78f, -3490.47f, 262.14f, 3.15f}, //9

    {2732.87f, -3489.03f, 262.09f, 3.13f}, //10
    {2685.02f, -3502.47f, 261.31f, 3.39f}  //center
};

struct virus_event_nax_helperAI : public ScriptedAI
{
    virus_event_nax_helperAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        ResetValues();
        Reset();
    }

    instance_naxxramas* m_pInstance;
    uint32 m_castTimer;
    uint32 m_playersCheckTimer;
    uint32 m_movePoint;
    uint32 m_nextPoint;
    bool m_balcony;
    std::vector<ObjectGuid> portals;

    void JustReachedHome() override
    {
        if (m_pInstance->GetData(TYPE_NOTH) != DONE)
        {
            ResetValues();
            Reset();
        }
    }

    void ResetValues()
    {
        m_creature->setFaction(35);
        m_movePoint = 100;
        m_nextPoint = 100;
        m_balcony = false;
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
    }

    void JustRespawned() override
    {
        if (m_pInstance->GetData(TYPE_NOTH) == FAIL)
            ResetValues();
    }

    void Reset()
    {
        m_castTimer = m_creature->GetEntry() == NPC_VIRUSEVENT_JAINA ? 1500 : 2500;
        m_playersCheckTimer = 5000;

        if (m_pInstance->GetData(TYPE_NOTH) == FAIL)
            ResetValues();
    }

    void nothAggro()
    {
        DoScriptText(m_creature->GetEntry() == NPC_VIRUSEVENT_JAINA ?
            SAY_VIRUS_EVENT_JAINA1 : SAY_VIRUS_EVENT_VOLJIN1, m_creature);
    }

    void DamageTaken(Unit* /*pDoneBy*/, uint32& uiDamage) override
    {
        if (uiDamage > 0)
            uiDamage = 0;
    }

    void DamageDeal(Unit* pDoneTo, uint32& uiDamage) override
    {
        int damage = m_creature->GetEntry() == NPC_VIRUSEVENT_JAINA ? 20 : 10;

        switch (pDoneTo->GetEntry())
        {
        case 16984:
        case 16982:
        case 16983:
        case 16981:
            damage = m_creature->GetEntry() == NPC_VIRUSEVENT_JAINA ? 10000 : 5000;
            break;
        }
        if (!m_balcony)
            damage *= 2;

        uiDamage = damage;
    }

    void MoveToPoint(uint32 id)
    {
        m_movePoint = id;
        m_nextPoint = id;
        uint32 index = id-100;
        if (index < 12 && index >= 0)
            m_creature->GetMotionMaster()->MovePoint(id, ve_points[index].x, 
                ve_points[index].y, ve_points[index].z, 3.0f, ve_points[index].o);
    }

    void MovementInform(uint32 uiType, uint32 uiPointId) override
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        if (uiPointId != 100 && uiPointId > 99 && uiPointId < 110)
            m_nextPoint++;

        if (uiPointId == 110)
        {
            m_creature->GetMotionMaster()->MoveIdle();
            DoScriptText(m_creature->GetEntry() == NPC_VIRUSEVENT_JAINA ?
                SAY_VIRUS_EVENT_JAINA1 : SAY_VIRUS_EVENT_VOLJIN1, m_creature);
        }

        if (uiPointId == 111)
            m_creature->GetMotionMaster()->MoveIdle();
    }

    void PhaseStart()
    {
        MoveToPoint(111);
        DoScriptText(m_creature->GetEntry() == NPC_VIRUSEVENT_JAINA ?
            YELL_VIRUS_EVENT_JAINA2 : YELL_VIRUS_EVENT_VOLJIN2, m_creature);
        m_balcony = true;
    }

    void PhaseEnd()
    {
        m_balcony = false;
        m_castTimer = m_creature->GetEntry() == NPC_VIRUSEVENT_JAINA ? 1500 : 2500;

        if (m_creature->GetEntry() == NPC_VIRUSEVENT_VOLJIN)
            if (Creature* totem = m_creature->FindNearestCreature(12141, 30))
                totem->DisappearAndDie();
    }

    void DespawnWithPortals()
    {
        m_creature->DisappearAndDie();
        for (ObjectGuid portalGuid : portals)
            if (GameObject* go = m_creature->GetMap()->GetGameObject(portalGuid))
                go->Delete();
    }

    void EndSummonPortals()
    {
        m_creature->SetRespawnDelay(99999999);
        m_creature->GetMotionMaster()->MoveIdle();
        m_creature->SetHomePosition(ve_points[11].x, ve_points[11].y, ve_points[11].z, 3.0f);
        DoScriptText(m_creature->GetEntry() == NPC_VIRUSEVENT_JAINA ?
            SAY_VIRUS_EVENT_JAINA3 : SAY_VIRUS_EVENT_VOLJIN3, m_creature);
        int i = 0;
        float fX, fY, fZ;
        for (uint32 portalid : m_creature->GetEntry() == NPC_VIRUSEVENT_JAINA ? ve_a_portals : ve_h_portals)
        {
            float pX, pY, pZ;
            fX = i == 0 ? m_creature->GetPositionX() : fX;
            fY = i == 0 ? m_creature->GetPositionY() : fY;
            fZ = i == 0 ? m_creature->GetPositionZ() : fZ;
            m_creature->GetRandomPoint(fX, fY, fZ, 10.0f, pX, pY, pZ);
            fX = pX;
            fY = pY;
            fZ = pZ;
            if (GameObject* portal = m_creature->SummonGameObject(portalid, pX, pY, pZ, 0.0, 0.0, 0.0, 0.0, 0.0, 0, true))
                portals.push_back(portal->GetObjectGuid());
            i++;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_pInstance->GetData(TYPE_NOTH) != NOT_STARTED)
        {
            if (m_playersCheckTimer <= uiDiff)
            {
                bool despawn = true;
                std::list<Player*> players;
                MaNGOS::AnyPlayerInObjectRangeCheck check(m_creature, 70);
                MaNGOS::PlayerListSearcher<MaNGOS::AnyPlayerInObjectRangeCheck> searcher(players, check);
                Cell::VisitWorldObjects(m_creature, searcher, 70);
                for (Player* player : players)
                    if (player->isAlive() && !player->isGameMaster())
                    {
                        despawn = false;
                        break;
                    }

                if (despawn)
                {
                    if (m_pInstance->GetData(TYPE_NOTH) == DONE)
                        DespawnWithPortals();
                    else
                    {
                        ResetValues();
                        m_creature->ForcedDespawn();
                    }
                    return;
                }
                m_playersCheckTimer = 5000;
            }
            else
                m_playersCheckTimer -= uiDiff;
        }

        if (m_pInstance->GetData(TYPE_NOTH) == DONE)
            return;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (m_movePoint != 100 && m_movePoint != m_nextPoint && m_movePoint < 110)
                MoveToPoint(m_nextPoint);

            return;
        }

        if (!m_creature->getVictim()->isInCombat())
            return;

        if (m_castTimer <= uiDiff)
        {
            std::list<Creature*> creatures;
            m_creature->GetCreatureListInGrid(creatures, 50);
            Creature* target = nullptr;
            for (Creature* t : creatures)
            {
                if (!t->isAlive() || t->GetEntry() == NPC_NOTH)
                    continue;

                target = t;
                break;
            }

            if (m_creature->GetPowerPercent(POWER_MANA) < 10)
                m_creature->SetPower(POWER_MANA, m_creature->GetMaxPower(POWER_MANA));

            if (!target)
                target = m_creature->FindNearestCreature(NPC_NOTH, 50);

            if (target)
            {
                if (!m_balcony)
                {
                    uint32 spellid = m_creature->GetEntry() == NPC_VIRUSEVENT_JAINA ? SPELL_JAINA_FROSTBOLT : SPELL_VOLJIN_CHAINLIGHTNING;
                    if (DoCastSpellIfCan(target, spellid) == CAST_OK)
                        m_castTimer = m_creature->GetEntry() == NPC_VIRUSEVENT_JAINA ? 1600 : 2600;
                }
            }

            if (m_balcony)
            {
                if (m_creature->GetEntry() == NPC_VIRUSEVENT_JAINA)
                {
                    m_creature->CastSpell(m_creature, SPELL_JAINA_WHIRLWIND, true);
                    m_creature->CastSpell(m_creature, SPELL_JAINA_EVOCATION, true);
                    m_castTimer = 5000;
                }
                else
                {
                    if (target)
                    {
                        m_creature->CastSpell(target, SPELL_VOLJIN_POWERTOTEM, true);
                        m_creature->CastSpell(target, SPELL_VOLJIN_CHAINLIGHTNING, true);
                    }
                    
                    m_creature->CastSpell(m_creature, SPELL_VOLJIN_ICETOTEM, true);
                    m_castTimer = 5000;
                }
            }
        }
        else
            m_castTimer -= uiDiff;
    }
};

CreatureAI* GetAI_virus_event_nax_helper(Creature* pCreature)
{
    return new virus_event_nax_helperAI(pCreature);
}

bool GossipHello_virus_event_nax_helper(Player* pPlayer, Creature* pCreature)
{
    auto m_pInstance = static_cast<instance_naxxramas*>(pCreature->GetInstanceData());
    if (!m_pInstance)
        return false;

    if (pPlayer->GetTeam() == ALLIANCE && pCreature->GetEntry() == NPC_VIRUSEVENT_VOLJIN)
        return false;

    if (pPlayer->GetTeam() == HORDE && pCreature->GetEntry() == NPC_VIRUSEVENT_JAINA)
        return false;

    if (m_pInstance->GetData(TYPE_NOTH) != DONE)
    {
        if (virus_event_nax_helperAI* pNaxHelperAI = dynamic_cast<virus_event_nax_helperAI*>(pCreature->AI()))
            if (pNaxHelperAI->m_movePoint == 100)
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, NPC_VIRUS_EVENT_GOSSIP, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                pPlayer->SEND_GOSSIP_MENU(NPC_VIRUS_EVENT_TEXT, pCreature->GetObjectGuid());
                return true;
            }
    }
    return false;
}

bool GossipSelect_virus_event_nax_helper(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    if (uiAction == (GOSSIP_ACTION_INFO_DEF + 1))
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (virus_event_nax_helperAI* pNaxHelperAI = dynamic_cast<virus_event_nax_helperAI*>(pCreature->AI()))
            if (pNaxHelperAI->m_movePoint == 100)
            {
                pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                pNaxHelperAI->MoveToPoint(101);
                pCreature->setFaction(pCreature->GetEntry() == NPC_VIRUSEVENT_JAINA ? FACTION_ALLIANCE : FACTION_HORDE);
            }
    }
    return true;
}
// 

struct boss_nothAI : public ScriptedAI
{
    boss_nothAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        Reset();
        pCreature->SetLootAndXPModDist(100.0f);
    }

    instance_naxxramas* m_pInstance;
    uint8 phaseCounter;
    uint32 killSayCooldown;
    EventMap m_events;
    bool isOnBalc;
    void Reset()
    {
        isOnBalc = false;
        phaseCounter = 0;
        m_events.Reset();
        killSayCooldown = 5000;
    }
    
    void JustReachedHome() override
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_NOTH, FAIL);

        std::list<Creature*> clist;
        GetCreatureListWithEntryInGrid(clist, m_creature, { NPC_PLAGUED_GUARDIAN, NPC_PLAGUED_CONSTRUCT, NPC_PLAGUED_CHAMPION, NPC_PLAGUED_WARRIOR }, 150.0f);
        for (Creature* pC : clist)
        {
            pC->DeleteLater();
        }
    }

    void Aggro(Unit* pWho)
    {
        // custom virus event
        if (sGameEventMgr.IsActiveEvent(172) && m_pInstance->GetData(TYPE_NOTH) != IN_PROGRESS)
        {
            if (Player* iPlayer = m_pInstance->GetPlayerInMap(false, false))
            {
                if (Creature* naxHelper = m_pInstance->GetSingleCreatureFromStorage(iPlayer->GetTeam() == ALLIANCE ? NPC_VIRUSEVENT_JAINA : NPC_VIRUSEVENT_VOLJIN))
                    if (virus_event_nax_helperAI* pNaxHelperAI = dynamic_cast<virus_event_nax_helperAI*>(naxHelper->AI()))
                        pNaxHelperAI->nothAggro();
            }
        }

        m_creature->SetInCombatWithZone();

        m_events.ScheduleEvent(EVENT_CURSE,    Seconds(urand(8,12)));
        m_events.ScheduleEvent(EVENT_BLINK,    Seconds(urand(30,40)));
        m_events.ScheduleEvent(EVENT_WARRIORS, Seconds(10));
        m_events.ScheduleEvent(EVENT_TP_BALC,  Seconds(90));

        DoScriptText(urand(SAY_AGGRO3, SAY_AGGRO1), m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_NOTH, IN_PROGRESS);
    }

    void SpawnWarriorsAndRepeatEvent()
    {
        DoScriptText(SAY_SUMMON, m_creature);

        DoCastSpellIfCan(m_creature, SPELL_SUM_WARR_SW, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_SUM_WARR_NW, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_SUM_WARR_NE, CAST_TRIGGERED);

        m_events.Repeat(Seconds(30));
    }

    void BlinkAndRepeatEvent()
    {
        static uint32 const auiSpellBlink[4] =
        {
            SPELL_BLINK_1, SPELL_BLINK_2, SPELL_BLINK_3, SPELL_BLINK_4
        };

        DoCastSpellIfCan(m_creature, SPELL_CRIPPLE, CAST_TRIGGERED | CAST_FORCE_CAST);
        DoCastSpellIfCan(m_creature, auiSpellBlink[urand(0, 3)], CAST_TRIGGERED|CAST_FORCE_CAST);
        m_events.Repeat(Seconds(urand(30, 40)));
        DoResetThreat();
        if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            AttackStart(target);
    }

    void CurseAndRepeatEvent()
    {
        // From what I can understand, the plague should always target the current target,
        // and will then also target the next 19 closest players to the current target
        if (Unit* pTarget = m_creature->getVictim())
        {
            DoCastSpellIfCan(pTarget, SPELL_CURSE_PLAGUEBRINGER);
            m_events.Repeat(Seconds(urand(50,60))); //It's somewhere around 50seconds+

        }
        else {
            m_events.Repeat(100);
        }
    }

    void TeleportToBalc()
    {
        if (DoCastSpellIfCan(m_creature, SPELL_TP_BALC, CAST_TRIGGERED | CAST_FORCE_CAST) != CAST_OK)
        {
            m_events.Repeat(100); // try again
            return;
        }

        isOnBalc = true;
        m_events.Reset();
        // 70, 95 and 120 seconds for 1st, 2nd and 3rd balc phase respectively.
        m_events.ScheduleEvent(EVENT_TP_GROUND, Seconds(70 + 25 * phaseCounter));

        auto first_spawn = Seconds(urand(5, 7));
        m_events.ScheduleEvent(EVENT_BALC_ADDS, first_spawn);
        switch (phaseCounter)
        {
        case 0:
            m_events.ScheduleEvent(EVENT_BALC_ADDS, first_spawn + Seconds(25 + urand(0, 5)));
            break;
        case 1:
            m_events.ScheduleEvent(EVENT_BALC_ADDS, first_spawn + Seconds(44 + urand(0, 5)));
            break;
        case 2:
            m_events.ScheduleEvent(EVENT_BALC_ADDS, first_spawn + Seconds(57 + urand(0, 5)));
            break;
        }

        m_creature->CastSpell(m_creature, SPELL_IMMUNE_ALL, true);

        m_creature->GetMotionMaster()->MoveIdle();
        DoStopAttack();


        // custom virus event
        if (sGameEventMgr.IsActiveEvent(172))
            if (Player* iPlayer = m_pInstance->GetPlayerInMap(false, false))
                if (Creature* naxHelper = m_pInstance->GetSingleCreatureFromStorage(iPlayer->GetTeam() == ALLIANCE ? NPC_VIRUSEVENT_JAINA : NPC_VIRUSEVENT_VOLJIN))
                    if (virus_event_nax_helperAI* pNaxHelperAI = dynamic_cast<virus_event_nax_helperAI*>(naxHelper->AI()))
                        pNaxHelperAI->PhaseStart();
    }

    void TeleportFromBalc()
    {
        if (DoCastSpellIfCan(m_creature, SPELL_TP_CENTER, CAST_TRIGGERED) != CAST_OK)
        {
            m_events.Repeat(100); // try again
            return;
        }
        m_events.Reset();
        m_events.ScheduleEvent(EVENT_RMV_INVULN, Seconds(2));

        // custom virus event
        if (sGameEventMgr.IsActiveEvent(172))
            if (Player* iPlayer = m_pInstance->GetPlayerInMap(false, false))
                if (Creature* naxHelper = m_pInstance->GetSingleCreatureFromStorage(iPlayer->GetTeam() == ALLIANCE ? NPC_VIRUSEVENT_JAINA : NPC_VIRUSEVENT_VOLJIN))
                    if (virus_event_nax_helperAI* pNaxHelperAI = dynamic_cast<virus_event_nax_helperAI*>(naxHelper->AI()))
                        pNaxHelperAI->PhaseEnd();
    }

    void Summon4Champions()
    {
        // We need to spawn 4 champions. We have 10 different possible locations,
        // and the adds need to be somewhat evenly spread out, yet somewhat randomized.

        std::vector<uint32> champs(ChampionSpells, ChampionSpells + sizeof(ChampionSpells)/sizeof(uint32));
        
        // First selecting one random champ from each of the 3 main groups
        uint32 champ1 = champs[urand(g1_start, g1_start+g1_size-1)];
        uint32 champ2 = champs[urand(g2_start, g2_start+g2_size-1)];
        uint32 champ3 = champs[urand(g3_start, g3_start+g3_size-1)];
        
        // Moving the selected champions to the end of the vector
        std::remove(champs.begin(), champs.end(), champ1);
        std::remove(champs.begin(), champs.end(), champ2);
        std::remove(champs.begin(), champs.end(), champ3);

        // Summoning the selected 3 guardians
        DoCastSpellIfCan(m_creature, champ1, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, champ2, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, champ3, CAST_TRIGGERED);
        
        // Choosing the final champion at random between the remaining 7 locations
        uint32 champ4 = champs[urand(0, 6)];
        DoCastSpellIfCan(m_creature, champ4, CAST_TRIGGERED);
    }

    void Summon2Guardians()
    {
        // Choose one of two locations south-west, and either the north-east or north-west location
        DoCastSpellIfCan(m_creature, urand(0, 1) ? SPELL_SUM_GUARD_SW1 : SPELL_SUM_GUARD_SW2, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, urand(0, 1) ? SPELL_SUM_GUARD_NE : SPELL_SUM_GUARD_NW, CAST_TRIGGERED);
    }

    void Summon3Constructs()
    {
        m_creature->SummonCreature(NPC_PLAGUED_CONSTRUCT, 2649.0f, -3456.0f, 264.0f, 5.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
        m_creature->SummonCreature(NPC_PLAGUED_CONSTRUCT, 2727.0f, -3458.0f, 263.5f, 3.8f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
        m_creature->SummonCreature(NPC_PLAGUED_CONSTRUCT, 2727.0f, -3534.0f, 268.0f, 0.1f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
    }

    void SpawnBalcAdds()
    {
        DoScriptText(SAY_SUMMON, m_creature);
        switch (phaseCounter)
        {
        case 0:
            Summon4Champions();
            break;
        case 1:
            Summon4Champions();
            Summon2Guardians();
            break;
        default: // third balc phase and onwards
            Summon4Champions();
            Summon2Guardians();
            Summon3Constructs();
            break;
        }
    }

    void OnRemoveVulnerability()
    {
        isOnBalc = false;

        m_events.Reset();
        m_events.ScheduleEvent(EVENT_BLINK,    Seconds(urand(2, 10)));
        m_events.ScheduleEvent(EVENT_CURSE,    Seconds(urand(2, 10)));
        m_events.ScheduleEvent(EVENT_WARRIORS, Seconds(urand(2,10)));
        m_creature->RemoveAurasDueToSpell(SPELL_IMMUNE_ALL);

        DoResetThreat();
        if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            AttackStart(target);

        // note that we increment phaseCounter here
        switch (++phaseCounter) 
        {
        // case 0: won't happen, its initialized from Aggro()
        case 1:
            m_events.ScheduleEvent(EVENT_TP_BALC, Seconds(110));
            break;
        case 2:
            m_events.ScheduleEvent(EVENT_TP_BALC, Seconds(180));
            break;
        default:
            // No good sources on duration of 4th ground phase, all guides explain it as a wipe
            // if you don't kill him during the 3rd ground phase. We'll just repeat previous phase logic
            // after this. It's highly unlikely that any guild get to this stage without killing him or wiping.
            m_events.ScheduleEvent(EVENT_TP_BALC, Seconds(180));
            //sLog.outError("boss_nothAI::OnRemoveVulnerability() called with phaseCounter: %d", phaseCounter);
        }
    }

    virtual void SummonedCreatureJustDied(Creature* unit) 
    {
        unit->ForcedDespawn(3000);
    }

    void JustSummoned(Creature* pSummoned)
    {
        pSummoned->SetInCombatWithZone();
    }

    void KilledUnit(Unit* pVictim)
    {
        if (!killSayCooldown)
        {
            DoScriptText(urand(0, 1) ? SAY_SLAY1 : SAY_SLAY2, m_creature);
            killSayCooldown = 5000;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_NOTH, DONE);

        // custom virus event
        if (sGameEventMgr.IsActiveEvent(172))
            if (Player* iPlayer = m_pInstance->GetPlayerInMap(false, false))
                if (Creature* naxHelper = m_pInstance->GetSingleCreatureFromStorage(iPlayer->GetTeam() == ALLIANCE ? NPC_VIRUSEVENT_JAINA : NPC_VIRUSEVENT_VOLJIN))
                    if (virus_event_nax_helperAI* pNaxHelperAI = dynamic_cast<virus_event_nax_helperAI*>(naxHelper->AI()))
                        pNaxHelperAI->EndSummonPortals();
    }

    void AttackStart(Unit* pWho)
    {
        if (!isOnBalc)
            ScriptedAI::AttackStart(pWho);
    }
    void DamageTaken(Unit* /*pDoneBy*/, uint32& uiDamage) override 
    {
        if (isOnBalc && uiDamage > 0)
            uiDamage = 0;
    }
    void UpdateAI(const uint32 uiDiff)
    {
        if (!isOnBalc)
        {
            if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
                return;
            if (!m_pInstance->HandleEvadeOutOfHome(m_creature))
                return;
        }
        else
        {
            // Will make him TP down rather thank walk through the air on a reset/wipe
            if (m_creature->getThreatManager().isThreatListEmpty())
            {
                if (m_events.GetTimeUntilEvent(EVENT_RMV_INVULN) > 2000)
                {
                    TeleportFromBalc();
                }
            }
        }
        
        killSayCooldown -= std::min(killSayCooldown, uiDiff);
        m_events.Update(uiDiff);
        while (auto l_EventId = m_events.ExecuteEvent())
        {
            switch (l_EventId)
            {
            case EVENT_BLINK:
                BlinkAndRepeatEvent();
                break;
            case EVENT_CURSE:
                CurseAndRepeatEvent();
                break;
            case EVENT_TP_BALC:
                TeleportToBalc();
                break;
            case EVENT_TP_GROUND:
                TeleportFromBalc();
                break;
            case EVENT_RMV_INVULN:
                OnRemoveVulnerability();
                break;
            case EVENT_BALC_ADDS:
                SpawnBalcAdds();
                break;
            case EVENT_WARRIORS:
                SpawnWarriorsAndRepeatEvent();
                break;
            }
        }
        if (!isOnBalc)
            DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_noth(Creature* pCreature)
{
    return new boss_nothAI(pCreature);
}

void AddSC_boss_noth()
{
    Script* NewScript;
    NewScript = new Script;
    NewScript->Name = "boss_noth";
    NewScript->GetAI = &GetAI_boss_noth;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "virus_event_nax_helper";
    NewScript->GetAI = &GetAI_virus_event_nax_helper;
    NewScript->pGossipHello = &GossipHello_virus_event_nax_helper;
    NewScript->pGossipSelect = &GossipSelect_virus_event_nax_helper;
    NewScript->RegisterSelf();
}
