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

#include "scriptPCH.h"
#include "naxxramas.h"

#include <algorithm>

namespace
{
enum
{
    SAY_SUMMON_MINIONS = -1533105,              //start of phase 1

    EMOTE_PHASE2 = -1533135,                    // %s strikes!, cant find use of it in vanilla
    SAY_AGGRO1 = -1533094,                      // pray for mercy
    SAY_AGGRO2 = -1533095,                      // Scream your dying breath!
    SAY_AGGRO3 = -1533096,                      // The end is upon you!

    SAY_SLAY1 = -1533097,
    SAY_SLAY2 = -1533098,

    SAY_DEATH = -1533099,

    SAY_CHAIN1 = -1533100,                      // Your soul, is bound to me now!
    SAY_CHAIN2 = -1533101,                      // there will be  no escape
    SAY_FROST_BLAST = -1533102,                 // I will freeze the blood in your veins!

    SAY_REQUEST_AID = -1533103,                 // Master! I require aid! 
    SAY_ANSWER_REQUEST = -1533104,              // Very well... warriors of the frozen wastes, rise up! I command you to fight, kill, and die for your master. Let none survive...

    SAY_SPECIAL1_MANA_DET = -1533106,           // Your petty magics are no challenge to the might of the Scourge! 
    SAY_SPECIAL3_MANA_DET = -1533107,           // Enough! I grow tired of these distractions! 
    SAY_SPECIAL2_DISPELL = -1533108,            // Fools, you have spread your powers too thin. Be free, my minions!

    EMOTE_GUARDIAN = -1533134,                  // at each guardian summon, cant see that it's used in vanilla

    SPELL_VISUAL_CHANNEL = 29423,               // channeled throughout phase one

    //spells to be casted
    SPELL_FROST_BOLT = 28478,
    SPELL_FROST_BOLT_NOVA = 28479,

    SPELL_CHAINS_OF_KELTHUZAD = 28408,
    SPELL_CHAINS_OF_KELTHUZAD_SCALE = 28409,
    SPELL_CHAINS_OF_KELTHUZAD_EFFECTS = 28410,

    SPELL_MANA_DETONATION = 27819,
    SPELL_SHADOW_FISSURE = 27810,
    SPELL_VOID_BLAST = 27812,
    SPELL_FROST_BLAST = 27808,
    SPELL_BERSERK = 28498,

    SPELL_DISPELL_SHACKLES = 28471,             // not used, doing it "manually"
};

constexpr float M_F_ANGLE = 0.2f;               // to adjust for map rotation
constexpr float M_F_HEIGHT = 2.0f;              // adjust for height difference
constexpr float M_F_RANGE = 55.0f;              // ~ range from center of chamber to center of alcove
constexpr float centerCoord[] = { 3716.379883f, -5106.779785f, 141.289993f };

enum AddSpells
{
    // guardian of icecrown
    SPELL_BLOOD_TAP = 28470,

    // Soul Weaver
    SPELL_WAIL_SOULS_AUR = 28460,

    // Warrior
    SPELL_DARK_BLAST_AUR = 28458,
    SPELL_DARK_BLAST_TRIG = 28457,

    // Abomination
    SPELL_MORTAL_WOUND = 28467,
};

enum Events
{
    // phase one
    EVENT_SKELETON = 1,
    EVENT_SOUL_WEAVER,
    EVENT_ABOMINATION,
    EVENT_PHASE_TWO_INTRO,
    EVENT_PHASE_TWO_START,
    EVENT_DESPAWN_PORTAL,
    EVENT_PUT_IN_COMBAT,

    // phase two
    EVENT_FROSTBOLT_NOVA,   // fixed
    EVENT_FROST_BLAST,      // fixed
    EVENT_FROSTBOLT,        // fixed
    EVENT_SHADOW_FISSURE,   // fixed
    EVENT_DETONATE_MANA,    // fixed
    EVENT_CHAINS,           // fixed

    // phase three
    EVENT_REQUEST_REPLY,    // fixed
    EVENT_SUMMON_GUARDIAN,  // fixed
};

// the shiny thing in center that despawns after pull
constexpr float pullPortal[3] = { 3716.379883f, -5106.779785f, 132.9f };

// Center position of each alcove
constexpr uint32 NUM_ALCOVES = 7;
constexpr float alcoves[7][2] =
{
    { 3768.40f, -5072.00f},
    { 3729.30f, -5044.10f},
    { 3683.00f, -5054.05f},
    { 3654.15f, -5093.48f},
    { 3664.55f, -5140.50f},
    { 3704.00f, -5170.00f},
    { 3751.95f, -5158.90f}
};

// z-coordinate in the alcoves
constexpr float alcoveZ = 143.5f;

// number of soulweavers total, one in each alcove
constexpr uint32 NUM_SOULWEAVER = 7;
// each soulweaver position
constexpr float soulweaverPos[NUM_SOULWEAVER][2] =
{
    {3754.95f, -5164.93f},
    {3701.89f, -5176.95f},
    {3656.83f, -5145.56f},
    {3647.53f, -5093.56f},
    {3678.48f, -5050.46f},
    {3730.87f, -5035.93f},
    {3774.78f, -5067.68f},
};
// number of abominations, 3 in each alcove
constexpr uint32 NUM_ABOM = 21;

// each abomination position
constexpr float abomPos[NUM_ABOM][2] =
{
    {3740.70f, -5160.89f},
    {3756.42f, -5151.09f},
    {3748.99f, -5155.72f},

    {3694.11f, -5163.96f},
    {3713.90f, -5168.14f},
    {3704.76f, -5166.21f},

    {3661.65f, -5132.06f},
    {3672.37f, -5147.84f},
    {3666.83f, -5139.67f},

    {3658.81f, -5086.46f},
    {3654.80f, -5104.04f},
    {3656.76f, -5095.47f},

    {3691.83f, -5052.45f},
    {3675.15f, -5062.94f},
    {3683.48f, -5057.71f},

    {3738.15f, -5050.12f},
    {3717.76f, -5046.03f},
    {3728.48f, -5047.99f},

    {3772.53f, -5083.21f},
    {3760.03f, -5064.65f},
    {3765.85f, -5073.22f}
};

// total number of soulweaver and abomination waves 
constexpr uint32 NUM_UNDEAD_SPAWNS = 14;

// milliseconds since pull for each abomination spawn
constexpr uint32 abominationSpawnMs[NUM_UNDEAD_SPAWNS] =
{
    44000,
    72000,
    100000,
    130000,
    153000,
    176000,
    193000,
    212000,
    232000,
    252000,
    268000,
    285000,
    300000,
    318000,
};

// milliseconds since pull for each soulweaver spawn
constexpr uint32 soulweaverSpawnMs[NUM_UNDEAD_SPAWNS] =
{
    44000,
    68000,
    97000,
    130000,
    155000,
    170000,
    190000,
    213000,
    235000,
    256000,
    271000,
    285000,
    294000,
    300000,
};

constexpr uint32 NUM_WINDOW_PORTALS = 4;
constexpr float windowPortals[NUM_WINDOW_PORTALS][2] =
{
    {3760.57f, -5173.93f},
    {3700.14f, -5185.68f},
    {3732.62f, -5027.67f},
    {3783.36f, -5062.35f}
};

//todo: no idea what the pull range should be
constexpr float ALCOVE_ADD_PULL_RADIUS = 30.0f;
}

struct kt_p1AddAI : public ScriptedAI
{
    kt_p1AddAI(Creature* pCreature) : ScriptedAI(pCreature), hasAggroed(false)
    {
        me->SetNoSearchAssistance(true);
    }

    bool hasAggroed;

    virtual void Reset() = 0;

    void ActualAttack(Unit* target)
    {
        m_creature->AddThreat(target, 300.0f);
        ScriptedAI::AttackStart(target);
        hasAggroed = true;
    }

    void Aggro(Unit* pWho) override
    {
        // want to prevent the creature from aggroing unless we explicitly do it through base class
    }

    void AttackStart(Unit* pWho) override
    {
        if (hasAggroed)
            ScriptedAI::AttackStart(pWho);
        // want to prevent the creature from aggroing unless we explicitly do it through this class
        else if (m_creature->GetDistance2d(pWho) < ALCOVE_ADD_PULL_RADIUS)
        {
            ActualAttack(pWho);
        }
    }

    void MoveInLineOfSight(Unit* pWho) override
    {
        if (hasAggroed)
            ScriptedAI::MoveInLineOfSight(pWho);
        else if (m_creature->IsHostileTo(pWho) && m_creature->GetDistance2d(pWho) < ALCOVE_ADD_PULL_RADIUS) //todo: no idea what the pull range should be
            ScriptedAI::MoveInLineOfSight(pWho);
    }

    void SpellHit(Unit* unit, const SpellEntry*) override 
    {
        if (!hasAggroed)
            ActualAttack(unit);
    }
};

struct boss_kelthuzadAI : public ScriptedAI
{
    boss_kelthuzadAI(Creature* pCreature) : ScriptedAI(pCreature), m_pInstance((instance_naxxramas*)pCreature->GetInstanceData())
    {
        Reset();
        pCreature->SetLootAndXPModDist(100.0f);
    }

    instance_naxxramas* const m_pInstance;

    std::vector<ObjectGuid> guardians;
    std::vector<int> availableGuardianEntrances;
    std::vector<ObjectGuid> p1_adds;
    
    int p1Timer;
    bool hasPutInCombat;
    bool p3Started;
    EventMap events;
    ObjectGuid pullPortalGuid;
    uint32 nextBanshee, nextAbom;
    uint32 numSkeletons, numAboms, numBanshees;
    uint32 enrageTimer;
    uint32 timeSinceLastFrostBlast;
    uint32 timeSinceLastShadowFissure;
    uint32 killSayTimer;
    uint32 combatUpdateTimer = 0;

    void Reset()
    {
        m_creature->SetHealth(m_creature->GetMaxHealth());
        events.Reset();

        // no info on enragetimer in vanilla, but wotlk has a 19min enrage and uses a spell from 1.11 dbc
        enrageTimer = 1000 * 60 * 19; 
        numSkeletons = 0;
        numAboms = 0;
        numBanshees = 0;
        nextBanshee = 30000;
        nextAbom = 30000;
        p3Started = false;
        timeSinceLastFrostBlast = 0;
        timeSinceLastShadowFissure = 0;
        killSayTimer = 0;
        combatUpdateTimer = 0;
        hasPutInCombat = false;

        m_creature->RemoveAurasDueToSpell(SPELL_VISUAL_CHANNEL);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);

        EvadeAllGuardians();

        if (!pullPortalGuid)
        {
            if (GameObject* pGO = m_creature->SummonGameObject(GO_HUB_PORTAL, pullPortal[0], pullPortal[1], pullPortal[2], 0))
            {
                pGO->SetObjectScale(2);
                pullPortalGuid = pGO->GetObjectGuid();
                // the add remove seems to be needed to  make the gobj update scale
                if (m_pInstance)
                {
                    m_pInstance->GetMap()->Remove(pGO, false);
                    m_pInstance->GetMap()->Add(pGO);
                }
            }
        }

        guardians.clear();
    }

    void KilledUnit(Unit* pVictim)
    {
        if (!killSayTimer)
        {
            DoScriptText(urand(0, 1) ? SAY_SLAY1 : SAY_SLAY2, m_creature);
            killSayTimer = 5000;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
        if (m_pInstance)
            m_pInstance->SetData(TYPE_KELTHUZAD, DONE);
        
        EvadeAllGuardians();
    }

    void MoveInLineOfSight(Unit* pWho) override
    {
    }

    void AttackStart(Unit* who) override
    {
        if (!m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            ScriptedAI::AttackStart(who);
    }

    void Aggro(Unit* pWho) override
    {
        if (!m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            m_creature->SetInCombatWithZone();
    }

    void JustReachedHome()
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_KELTHUZAD, NOT_STARTED);
            m_pInstance->ToggleKelThuzadWindows(false);
        }

        DespawnAllIntroCreatures();
        EvadeAllGuardians();
    }

    void EvadeAllGuardians()
    {
        for (auto const &it : guardians)
            if (auto const creature = m_pInstance->GetCreature(it))
                creature->AI()->EnterEvadeMode();
    }

    void DespawnAllIntroCreatures()
    {
        for (auto const &it : p1_adds)
            if (auto const soldier = m_pInstance->instance->GetCreature(it))
                ((TemporarySummon*)soldier)->UnSummon();

        p1_adds.clear();
    }
  
    void StartEncounter()
    {
        m_pInstance->ToggleKelThuzadWindows(false);
        m_creature->SetHealth(m_creature->GetMaxHealth());

        // on pull there are in each alcove:
        // 3 aboms
        // 1 banshee
        // around 10 skeletons?

        // during p1, 14 aboms, 14 banshees and 120 skeletons should attack, gradually faster
        m_pInstance->SetData(TYPE_KELTHUZAD, IN_PROGRESS);
        DoScriptText(SAY_SUMMON_MINIONS, m_creature);
        DoCastAOE(SPELL_VISUAL_CHANNEL);

        events.ScheduleEvent(EVENT_DESPAWN_PORTAL,  Seconds(7));
        events.ScheduleEvent(EVENT_PUT_IN_COMBAT,   Seconds(20));
        events.ScheduleEvent(EVENT_PHASE_TWO_INTRO, Minutes(5) + Seconds(20));

        p1Timer = 320000;
        events.ScheduleEvent(EVENT_SKELETON, Seconds(20));
        events.ScheduleEvent(EVENT_SOUL_WEAVER, Seconds(35));
        events.ScheduleEvent(EVENT_ABOMINATION, Seconds(43));

        for (uint32 i = 0; i < NUM_UNDEAD_SPAWNS; i++)
            events.ScheduleEvent(EVENT_ABOMINATION, abominationSpawnMs[i]);
        for (uint32 i = 0; i < NUM_UNDEAD_SPAWNS; i++)
            events.ScheduleEvent(EVENT_SOUL_WEAVER, soulweaverSpawnMs[i]);

        m_pInstance->DoUseDoorOrButton(pullPortalGuid);

        for (int i = 0; i < NUM_ALCOVES; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                double angle = rand_norm() * 2.0 * M_PI;
                double relDistance = rand_norm() + rand_norm();
                if (relDistance > 1)
                    relDistance = 1 - relDistance;
                const float x = alcoves[i][0];
                const float y = alcoves[i][1];
                const float radius = 14.0f;
                float thisX = x + std::sin(angle)*relDistance*radius;
                float thisY = y + std::cos(angle)*relDistance*radius;
                if (Creature* pCreature = m_creature->SummonCreature(NPC_SOLDIER_FROZEN, thisX, thisY, alcoveZ, frand(0, M_PI_F * 2),
                    TEMPSUMMON_MANUAL_DESPAWN))
                {
                    p1_adds.push_back(pCreature->GetObjectGuid());
                    pCreature->SetHomePosition(x, y, alcoveZ, m_creature->GetOrientation());
                    pCreature->SetRespawnRadius(radius);
                }
            }
        }

        for (int i = 0; i < NUM_ABOM; i++)
        {
            if (Creature* pCreature = m_creature->SummonCreature(NPC_UNSTOPPABLE_ABOM, abomPos[i][0], abomPos[i][1], alcoveZ, frand(0, M_PI_F * 2),
                TEMPSUMMON_MANUAL_DESPAWN))
            {
                p1_adds.push_back(pCreature->GetObjectGuid());
                pCreature->SetRespawnRadius(5.0f);
            }

        }

        for (int i = 0; i < NUM_SOULWEAVER; i++)
        {
            if (Creature* pCreature = m_creature->SummonCreature(NPC_SOUL_WEAVER, soulweaverPos[i][0], soulweaverPos[i][1], alcoveZ, frand(0, M_PI_F * 2),
                TEMPSUMMON_MANUAL_DESPAWN))
            {
                p1_adds.push_back(pCreature->GetObjectGuid());
                pCreature->SetRespawnRadius(5.0f);
            }
        }
    }

    bool SpawnAndSendP1Creature(uint32 type)
    {
        const float* spawnLoc = alcoves[urand(0, NUM_ALCOVES - 1)];

        if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, nullptr, SELECT_FLAG_PLAYER))
        {
            float spawnAng = 3.14f + pTarget->GetAngle(spawnLoc[0], spawnLoc[1]);
            if (Creature* pAdd = m_creature->SummonCreature(type, spawnLoc[0], spawnLoc[1], alcoveZ, spawnAng, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000))
            {
                pAdd->SetInCombatWithZone();
                ((kt_p1AddAI*)pAdd->AI())->ActualAttack(pTarget);
                return true;
            }
        }

        return false;
    }

    void UpdateP1(uint32 diff)
    {
        if (m_pInstance->GetData(TYPE_KELTHUZAD) != IN_PROGRESS)
            return;
        
        p1Timer -= diff;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_DESPAWN_PORTAL:
                if (GameObject* pGO = m_pInstance->GetGameObject(pullPortalGuid))
                {
                    pullPortalGuid = 0;
                    pGO->Delete();
                }
                break;
            case EVENT_PUT_IN_COMBAT:
                m_creature->SetInCombatState(false);
                m_creature->SetInCombatWithZone();
                hasPutInCombat = true;
                break;
            case EVENT_SKELETON:
            {
                if (numSkeletons < 120)
                {

                    float t = 3.0f / 150.0f * (p1Timer / 1000.0f - 150.0f);
                    uint32 repeat_next = std::max(uint32(t * 1000 + 2000), uint32(2000));
                    if (SpawnAndSendP1Creature(NPC_SOLDIER_FROZEN))
                    {
                        uint32 repeat_next = std::max(uint32(3750 - 25 * numSkeletons), uint32(2000));
                        events.Repeat(repeat_next);
                        ++numSkeletons;
                        //sLog.outBasic("[%d] Spawn SKEL #%d, next in %dms", p1Timer, numSkeletons, repeat_next);
                    }
                    else
                        events.Repeat(100);
                }
                break;
            }
            case EVENT_ABOMINATION:
            {
                SpawnAndSendP1Creature(NPC_UNSTOPPABLE_ABOM);
                ++numAboms;
                //sLog.outBasic("[%d] Spawn ABOM #%d", p1Timer, numAboms);
                break;
            }
            case EVENT_SOUL_WEAVER:
            {
                SpawnAndSendP1Creature(NPC_SOUL_WEAVER);
                ++numBanshees;
                //sLog.outBasic("[%d] Spawn SOUL #%d", p1Timer, numBanshees);
                break;
            }
            case EVENT_PHASE_TWO_INTRO:
            {
                // ToDo: slightly hard to figure the exact delay between this event (the yell and despawn of adds)
                // until he engages. Most vanilla timers say 20 seconds, but he always engages earlier than that.
                // Seen it at around 10 seconds in a german video (https://www.youtube.com/watch?v=QafmVXupeHc),
                // and as late as ~17-18 sec in another one (https://www.youtube.com/watch?v=6RpqjIFbQYw https://www.youtube.com/watch?v=wSQtlvVebm0)
                events.Reset();
                events.ScheduleEvent(EVENT_PHASE_TWO_START, Seconds(15));
                if (numBanshees < 14)
                {
                    SpawnAndSendP1Creature(NPC_SOUL_WEAVER);
                    sLog.outBasic("(post)[%d] Spawn bansh #%d, next in %dms", p1Timer, ++numBanshees, nextBanshee);
                }
                if (numAboms < 14)
                {
                    SpawnAndSendP1Creature(NPC_UNSTOPPABLE_ABOM);
                    sLog.outBasic("(post)[%d] Spawn abom #%d, next in %dms", p1Timer, ++numAboms, nextBanshee);
                }
                if (numSkeletons < 120)
                {
                    SpawnAndSendP1Creature(NPC_SOLDIER_FROZEN);
                    sLog.outBasic("(post)[%d] Spawn skele #%d, next in %dms", p1Timer, ++numSkeletons, nextBanshee);
                }

                DoScriptText(irand(SAY_AGGRO3, SAY_AGGRO1), m_creature);
                m_creature->RemoveAurasDueToSpell(SPELL_VISUAL_CHANNEL);
                DespawnAllIntroCreatures();
                break;
            }
            case EVENT_PHASE_TWO_START:
                // engage!
                events.Reset();
                events.ScheduleEvent(EVENT_FROSTBOLT,       Seconds(10));
                events.ScheduleEvent(EVENT_SHADOW_FISSURE,  Seconds(urand(10, 15)));
                events.ScheduleEvent(EVENT_DETONATE_MANA,   Seconds(urand(20, 30)));
                events.ScheduleEvent(EVENT_FROSTBOLT_NOVA,  Seconds(15));
                events.ScheduleEvent(EVENT_FROST_BLAST,     Seconds(urand(30, 45)));
                events.ScheduleEvent(EVENT_CHAINS,          Seconds(25));       // the same in three different videos
                m_creature->RemoveAurasDueToSpell(SPELL_VISUAL_CHANNEL);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                //m_creature->CastStop();
                m_creature->InterruptNonMeleeSpells(true);
                
                DoResetThreat();
                m_creature->SetInCombatWithZone();
                if (Unit* pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_NEAREST, 0))
                    AttackStart(pUnit);

                break;
            }
        }
    }

    void UpdateP2P3(uint32 diff)
    {
        timeSinceLastFrostBlast += diff;
        timeSinceLastShadowFissure += diff;

        if (combatUpdateTimer >= 3000)
        {
            m_creature->SetInCombatWithZone(false);
            combatUpdateTimer = 0;
        }
        else
            combatUpdateTimer += diff;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->GetHealthPercent() < 40.0f && !p3Started)
        {
            DoScriptText(SAY_REQUEST_AID, m_creature);

            events.ScheduleEvent(EVENT_REQUEST_REPLY, Seconds(3));
            m_pInstance->ToggleKelThuzadWindows(true);

            // first add(s) always spawn after 15 seconds
            events.ScheduleEvent(EVENT_SUMMON_GUARDIAN, Seconds(15));

            // 0-3 represent the portals, 4 represents the back door
            availableGuardianEntrances = { 0, 1, 2, 3, 4 };

            std::random_shuffle(availableGuardianEntrances.begin(), availableGuardianEntrances.end());

            p3Started = true;
        }

        // two videos primarily used for ability timing:
        // https://www.youtube.com/watch?v=6RpqjIFbQYw
        /*
        6:02 KT engaged
        6:11 frostbolt (9 sec from start)
        6:15 shadow fissure (13 sec from start)
        6:26 mind control (24 sec from start)
        6:32 frost blast (30 sec from start)
        6:33 detonate mana (31 sec from start)
        6:38 shadow fissure (23 sec cd)
        6:49 frostbolt nova (47 sec from start)
        6:53 warning possible frost blast in 5 seconds
        6:58 shadow fissure (25 sec cd)
        7:00 detonate mana (27 sec cd)
        7:05 frostbolt nova (16 sec cd)
        7:15 shadow fissure (17 sec cd)
        7:21 frostbolt nova (16 sec cd)
        7:24 detonate mana (24 sec cd)
        7:29 shadow fissure (14 sec cd)
        7:36 frost blast (64 sec cd)
        7:41 shadow fissure (26 sec cd)
        7:45 detonate mana (21 sec cd)
        7:50 mind control (84 sec cd)
        7:51 shadow fissure (22 sec cd)
        7:56 warning possible frost blast in 5 seconds
        8:04 shadow fissure (13 sec cd)
        8:08 detonate mana (23 sec cd)
        8:10 frost blast (34 sec cd)
        8:15 shadow fissure (11 sec cd)
        8:23 frostbolt nova (62 sec cd)
        8:30 warning possible frost blast in 5 seconds
        8:35 detonate mana (27 sec cd)
        8:35 shadow fissure (20 sec cd)
        8:44 frost blast (34 sec cd)
        8:50 shadow fissure (15 sec cd)
        8:57 frostbolt nova (34 sec cd)
        9:04 warning possible frost blast in 5 seconds
        9:06 shadow fissure (16 sec cd)
        9:14 frostbolt nova (17 sec cd)
        9:19 detonate mana (44 sec cd, one skipped?)
        9:25 shadow fissure (19 sec cd)
        9:31 forstbolt nova
        9:40 shadow fissure (15 sec cd)
        9:48 frostbolt nova (35 sec cd)
        9:48 detonate mana (29 sec cd)
        9:58 shadow fissure (18 sec cd)
        10:03 frostbolt nova (15 sec cd)
        10:10 detonate mana (22 sec cd)
        10:13 shadow fissure (15 sec cd)
        10:19 frostbolt nova (16 sec cd)
        10:27 shadow fissure (14 sec cd)
        10:34 frostbolt nova (16 sec cd)
        10:42 detonate mana (32 sec cd)
        10:45 shadow fissure (18 sec cd)
        10:50 frostbolt nova (16 sec cd)
        11:01 mind control (191 sec cd)
        11:02 detonate mana (20 sec cd)
        11:06 frostbolt nova (16 sec cd)
        11:15 shadow fissure (30 sec cd)
        11:20 phase 3 say, guardians in 15 seconds
        11:22 detonate mana (20 sec cd)
        11:22 warning possible frost blast in 5 seconds
        11:23 warning guardians incoming in 10 seconds
        11:31 shadow fissure (16 sec cd)
        11:37 frost blast (173 sec cd)
        11:40 2 adds spawn including in the room
        11:44 shadow fissure (13 sec cd)
        11:44 detonate mana (22 sec cd)
        11:50 2 adds spawn
        11:54 frostbolt nova (48 sec cd)
        11:58 warning possible frost blast in 5 seconds
        12:00 1 add spawns
        12:04 detonate mana (20 sec cd)
        12:05 shadow fissure (21 sec cd)
        12:19 frost blast (42 sec cd)
        12:24 mind control (75 sec cd)
        12:25 detonate mana (21 sec cd)
        12:26 frostbolt nova (32 sec cd)
        12:34 shadow fissure (29 sec cd)
        12:39 warning possible frost blast in 5 seconds
        12:41 frostbolt nova (15 sec cd)
        12:45 detonate mana (20 sec cd)
        12:52 shadow fissure (18 sec cd)
        12:57 frostbolt nova (31 sec cd)
        13:07 frost blast (48 sec cd)
        13:13 frostbolt nova (16 sec cd)
        13:19 detonate mana (34 sec cd)
        13:25 shadow fissure (33 sec cd)
        13:27 warning possible frost blast in 5 seconds
        13:36 mind control (72 sec cd)
        13:37 shadow fissure (12 sec cd)
        13:44 frostbolt nova (31 sec cd)
        13:47 detonate mana (28 sec cd)
        13:53 frost blast (46 sec cd)
        13:56 boss dead
        */
        // https://www.youtube.com/watch?v=l1T5w399CQY
        /*
        5:28 KT engaged
        5:37 frostbolt (9 sec from start)
        5:37 shadow fissure (9 sec from start)
        5:43 frostbolt nova (15 sec from start)
        5:52 frostbolt (15 sec cd)
        5:52 mind control (24 sec from start)
        5:59 frostbolt nova (16 sec cd)
        6:03 frostbolt (11 sec cd)
        6:08 shadow fissure (31 sec cd)
        6:10 frostbolt (7 sec cd)
        6:13 frostbolt (3 sec cd)
        6:15 frostbolt nova (23 sec cd)
        6:19 detonate mana (51 sec from start)
        6:23 frostbolt (10 sec cd)
        6:24 shadow fissure (16 sec cd)
        6:30 frostbolt (7 sec cd)
        6:31 frostbolt nova (16 sec cd)
        6:37 frostbolt (7 sec cd)
        6:41 frost blast (73 sec from start)
        6:47 frostbolt nova (16 sec cd)
        6:47 frostbolt (10 sec cd)
        6:56 shadow fissure (32 sec cd)
        6:58 frostbolt (11 sec cd)
        7:03 frostbolt nova (16 sec cd)
        7:06 detonate mana (47 sec cd)
        7:06 frostbolt (8 sec cd)
        7:06 warning frost blast incoming in ~5 seconds
        7:11 shadow fissure (15 sec cd)
        7:11 warning frost blast incoming spread out!
        7:12 frostbolt (6 sec cd)
        7:18 mind control (86 sec cd)
        7:18 frost blast (37 sec cd)
        7:19 frostbolt (7 sec cd)
        7:22 shadow fissure (11 sec cd)
        7:26 detonate mana (20 sec cd)
        7:31 frostbolt (12 sec cd)
        7:34 frostbolt nova (31 sec cd)
        7:39 frostbolt (8 sec cd)
        7:43 warning frost blast incoming in ~5 seconds
        7:44 shadow fissure (22 sec cd)
        7:48 warning frost blast incoming spread out!
        7:51 frostbolt nova (17 sec cd)
        7:52 detonate mana (26 sec cd)
        7:57 frostbolt (18 sec cd) ???? check around 7:50 for other things maybe affecting the tank?
        8:01 shadow fissure (17 sec cd)
        8:08 frostbolt (11 sec cd)
        8:13 detonate mana (21 sec cd)
        8:17 frostbolt (9 sec cd)
        8:22 frostbolt nova (31 sec cd)
        8:24 frostbolt (7 sec cd)
        8:31 shadow fissure (30 sec cd)
        8:32 frostbolt (8 sec cd)
        8:35 detonate mana (43 sec cd)
        8:37 frost blast (79 sec cd)
        8:37 mind control (79 sec cd)
        8:44 shadow fissure (13 sec cd)
        8:46 frostbolt (14 sec cd) ????
        8:54 frostbolt nova (32 sec cd)
        8:56 frostbolt (10 sec cd)
        9:00 detonate mana (35 sec cd)
        9:03 warning frost blast incoming in ~5 seconds
        9:03 frostbolt (7 sec cd)
        9:04 shadow fissure (20 sec cd)
        9:08 warning frost blast incoming spread out!
        9:10 frostbolt nova (16 sec cd)
        9:17 frostbolt (14 sec cd)
        9:21 frost blast (44 sec cd)
        9:26 frostbolt (9 sec cd)
        9:26 frostbolt nova (16 sec cd)
        9:36 frostbolt (10 sec cd)
        9:36 shadow fissure (32 sec cd)
        9:40 detonate mana (40 sec cd)
        9:42 frostbolt nova (16 sec cd)
        9:43 frostbolt (7 sec cd)
        9:46 warning frost blast incoming in ~5 seconds
        9:51 warning frost blast incoming spread out!
        9:51 frostbolt (8 sec cd)
        9:52 mind control (75 sec cd)
        9:54 frost blast (33 sec cd)
        9:59 shadow fissure (23 sec cd)
        10:03 frostbolt (12 sec cd)
        10:07 detonate mana (27 sec cd)
        10:10 frostbolt (7 sec cd)
        10:14 frostbolt nova (32 sec cd)
        10:19 p3 yell "Master, I require aid!", first guardian in ~15 seconds
        10:22 frostbolt (12 sec cd)
        10:24 frost blast (30 sec cd)
        10:29 frostbolt nova (15 sec cd)
        10:31 detonate mana (24 sec cd)
        10:32 frostbolt (10 sec cd)
        10:34 first add becomes visible, probably spawned sooner, left chamber from KT
        10:41 shadow fissure (42 sec cd)
        10:44 second add spawns right chamber from KT
        10:45 third add becomes visible, probably spawned sooner, from out of view on right
        10:48 frostbolt (16 sec cd)
        10:50 warning frost blast incoming in ~5 seconds
        10:52 detonate mana (21 sec cd)
        10:53 fourth add becomes visible, probably spawned sooner, from out of view on left
        10:56 shadow fissure (15 sec cd)
        11:00 frostbolt (12 sec cd)
        11:02 frostbolt nova (33 sec cd)
        11:10 frostbolt (10 sec cd)
        11:10 shadow fissure (14 sec cd)
        11:14 detonate mana (22 sec cd)
        11:18 frostbolt nova (16 sec cd)
        11:27 shadow fissure (17 sec cd)
        11:33 frostbolt nova (15 sec cd)
        11:36 detonate mana (22 sec cd)
        11:37 frostbolt (27 sec cd)
        11:42 shadow fissure (15 sec cd)
        11:45 frostbolt (18 sec cd)
        11:49 frostbolt nova (16 sec cd)
        11:57 shadow fissure (15 sec cd)
        12:01 frostbolt (16 sec cd)
        12:05 frostbolt nova (16 sec cd)
        12:05 detonate mana (29 sec cd)
        12:08 frostbolt (7 sec cd)
        12:16 frost blast (112 sec cd)
        12:20 frostbolt nova (15 sec cd)
        12:21 frostbolt (13 sec cd)
        12:23 KT dies yells "Agghhhh! Do... not... rejoice!  Your victory is a hollow one, for I shall return with powers beyond your imagining!"
        */

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_REQUEST_REPLY:
            {
                m_pInstance->DoOrSimulateScriptTextForThisInstance(SAY_ANSWER_REQUEST, NPC_LICH_KING);
                break;
            }

            case EVENT_SUMMON_GUARDIAN:
            {
                // one or two adds spawn every 10 seconds until there are five.  no portal is ever re-used.
                auto const howMany = guardians.size() == 4 ? 1 : urand(1, 2);

                // should be impossible...
                if (availableGuardianEntrances.empty())
                    break;

                for (auto i = 0u; i < howMany; ++i)
                {
                    // get the next alcove id
                    auto const alcove = availableGuardianEntrances.back();
                    availableGuardianEntrances.pop_back();

                    // 0-3 represent the acloves with portals, 4 represents the back door alcove
                    auto const pos = alcove < NUM_WINDOW_PORTALS ? windowPortals[alcove] : alcoves[3];

                    if (Creature* pCreature = m_creature->SummonCreature(NPC_GUARDIAN, pos[0], pos[1], alcoveZ, 0.0f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 10000))
                    {
                        pCreature->SetInCombatWithZone();
                        guardians.push_back(pCreature->GetObjectGuid());

                        if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                            pCreature->AI()->AttackStart(pTarget);
                    }
                }

                // only repeat the event when there are more to spawn
                if (guardians.size() < 5)
                    events.Repeat(Seconds(10));

                break;
            }

            case EVENT_FROSTBOLT_NOVA:
            {
                // it seems from timing data that frostbolt nova cannot cast within five seconds of frost blast.
                // and this makes sense because it would mean almost certain death for the frost blast target.
                if (timeSinceLastFrostBlast < 5000)
                {
                    events.Repeat(5000 - timeSinceLastFrostBlast);
                    break;
                }

                // from the timing data, there were:
                // 26 casts with ~15 second cooldown
                // 10 casts with ~30 second cooldown
                // 2 casts with ~45 second cooldown
                // 1 cast with ~60 second cooldown
                // if we assume that the extended cooldowns are due to 15 second timers rolling on skipping the cast,
                // this means that in addition to the 39 casts, there were 17 ticks of the timer where the roll caused
                // a skip (one per ~30 second cooldown, two per ~45 second cooldown, and three per ~60 second cooldown)
                // for a total of 56 ticks of the 15 second timer.  statistically, this means that 26 / 56 ticks of the
                // timer caused a cast, or roughly 50% of the time.  therefore it would appear that there is a 50% chance
                // when the timer is up that the cast is skipped.

                const bool skip = !urand(0, 1);
                if (skip || DoCastSpellIfCan(m_creature, SPELL_FROST_BOLT_NOVA) == CAST_OK)
                    events.Repeat(Seconds(15));
                else
                    events.Repeat(Seconds(5));

                break;
            }

            case EVENT_FROST_BLAST:
            {
                // timing data indicates that frost blast is never cast within five seconds of the last shadow fissure
                // and this makes sense because if a shadow fissure spawned under the frost blasted target it would be
                // certain death
                if (timeSinceLastShadowFissure < 5000)
                {
                    events.Repeat(5000 - timeSinceLastShadowFissure);
                    break;
                }

                if (m_creature->IsNonMeleeSpellCasted())
                {
                    events.Repeat(Seconds(1));
                    break;
                }

                auto const cooldown = Seconds(urand(30, 45));

                // timing data shows cooldowns ranging from 30 seconds to 45 seconds.  there also appears to be a chance
                // for the cast to be skipped.  the data shows approximately nine skips and 15 casts, which means the
                // experimental chance to skip is 9/(9+15) or 37.5%.  my best guess is that the chance to really skip is
                // around 40% chance as it is a nice round number near our experimental value.

                // 40% chance to skip the cast
                if (urand(1, 10) > 4)
                {
                    if (Unit* pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1, nullptr, SELECT_FLAG_PLAYER))
                    {
                        if (DoCastSpellIfCan(pUnit, SPELL_FROST_BLAST) == CAST_OK)
                        {
                            events.Repeat(cooldown);
                            timeSinceLastFrostBlast = 0;
                            if (urand(0, 1))
                                DoScriptText(SAY_FROST_BLAST, m_creature);

                            break;
                        }
                    }

                    // only reaches here if we should have casted but couldnt
                    events.Repeat(Seconds(1));
                }
                else
                    events.Repeat(cooldown);

                break;
            }

            case EVENT_FROSTBOLT:
            {
                // the timing data for this is difficult to interpret.  one thing i noticed is the only time when
                // the cooldown was the minimum of three seconds was when the spell was not interrupted.  this indicates
                // that the cooldown can be as little as three seconds but should normally be delayed by the spell
                // school lockout that comes from interrupting the previous attempt to cast it.  currently the best
                // algorithm i can think of that matches the data is a consistent three second cooldown with a 75% chance
                // to skip the cast

                // if we skip or cast successfully, reset cooldown
                if (urand(0, 3) || DoCastSpellIfCan(m_creature->getVictim(), SPELL_FROST_BOLT) == CAST_OK)
                    events.Repeat(Seconds(3));
                // otherwise repeat next tick
                else
                    events.Repeat(1);

                break;
            }

            case EVENT_SHADOW_FISSURE:
            {
                // timing data shows that this spell was never cast within five seconds of frost blast
                if (timeSinceLastFrostBlast < 5000)
                {
                    events.Repeat(5000 - timeSinceLastFrostBlast);
                    break;
                }

                if (m_creature->IsNonMeleeSpellCasted())
                {
                    events.Repeat(Seconds(2));
                    break;
                }

                // timing data shows that after the first spell is cast, there is a 50% chance that the next one will
                // be cast in 15 seconds, and a 50% chance that it will be delayed by a random amount of seconds between
                // one and five.

                auto const nextCast = Seconds(15 + (!urand(0, 1) ? urand(1, 5) : 0));

                // 15% chance to skip the cast
                if (urand(1, 100) > 15)
                {
                    if (Unit* pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1, nullptr, SELECT_FLAG_PLAYER))
                    {
                        if (DoCastSpellIfCan(pUnit, SPELL_SHADOW_FISSURE) == CAST_OK)
                        {
                            events.Repeat(nextCast);
                            timeSinceLastShadowFissure = 0;
                            break;
                        }
                    }

                    // only reaches here if we should have casted but couldnt
                    events.Repeat(Seconds(1));
                }
                else
                    events.Repeat(nextCast);

                break;
            }

            case EVENT_DETONATE_MANA:
            {
                if (m_creature->IsNonMeleeSpellCasted())
                {
                    events.Repeat(Seconds(2));
                    break;
                }

                // timing data shows this spell has a timer of a random number probably between 20 and 30 seconds.
                // in 32 casts, five appeared to have skipped a timer.  this means the chance to skip is roughly
                // 5/(5+32) or roughly 15%.

                auto const cooldown = Seconds(urand(20, 30));

                // 15% chance to skip the cast
                if (urand(1, 100) > 15)
                {
                    if (Unit* pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, SPELL_MANA_DETONATION, SELECT_FLAG_POWER_MANA | SELECT_FLAG_PLAYER))
                    {
                        if (DoCastSpellIfCan(pUnit, SPELL_MANA_DETONATION) == CAST_OK)
                        {
                            events.Repeat(cooldown);

                            if (!urand(0, 4))
                                DoScriptText(urand(0,1) ? SAY_SPECIAL1_MANA_DET : SAY_SPECIAL3_MANA_DET, m_creature);

                            break;
                        }
                    }

                    // only reaches here if we should have casted but couldnt
                    events.Repeat(Seconds(1));
                }
                else
                    events.Repeat(cooldown);

                break;
            }

            case EVENT_CHAINS:
                // this spell cannot cast within five seconds of frost blast, but frost blast CAN cast right after this spell.
                // that is because once this spell casts, the mind controlled targets will no longer be suitable targets for
                // frost blast.
                if (timeSinceLastFrostBlast < 5000)
                {
                    events.Repeat(5000 - timeSinceLastFrostBlast);
                    break;
                }

                // timing data from youtube shows that this spell has a cooldown ranging from 72 to 86 seconds
                // and of nine casts, one appeared to be skipped.  this means there is a 1/(9+1) or 10% chance to skip.
                if (urand(0, 9))
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_CHAINS_OF_KELTHUZAD) != CAST_OK)
                    {
                        events.Repeat(Seconds(2));
                        return;
                    }

                    DoResetThreat();
                    DoScriptText(urand(0, 1) ? SAY_CHAIN1 : SAY_CHAIN2, m_creature);
                }

                events.Repeat(Seconds(urand(72, 86)));
                break;
            }
        }

        DoMeleeAttackIfReady();
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_pInstance)
            return;

        if (hasPutInCombat)
        {
            // won't have a victim if we are in p1, even if selectHostileTarget returns true, so check that before return
            if (!m_creature->SelectHostileTarget() || (!m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE) && !m_creature->getVictim()))
                return;
        }
        
        if (m_pInstance->GetData(TYPE_KELTHUZAD) != IN_PROGRESS)
            return;
        
        killSayTimer -= std::min(killSayTimer, diff);

        if (enrageTimer < diff)
        {
            m_creature->CastSpell(m_creature, SPELL_BERSERK, true);
            enrageTimer = 300000;
        }
        else
            enrageTimer -= diff;

        events.Update(diff);

        if (m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            UpdateP1(diff);
        else
        {

            if (!m_pInstance->HandleEvadeOutOfHome(m_creature))
                return;
            UpdateP2P3(diff);
        }
    }

};

struct mob_abomAI : public kt_p1AddAI
{
    mob_abomAI(Creature* pCreature) : kt_p1AddAI(pCreature)
    {
        Reset();
    }
    uint32 mortalWoundTimer;
    void Reset() override
    {
        mortalWoundTimer = 7500;
    }
    void UpdateAI(const uint32 diff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (mortalWoundTimer < diff)
        {
            if (m_creature->getVictim() && m_creature->IsWithinMeleeRange(m_creature->getVictim()))
                if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_MORTAL_WOUND) == CAST_OK)
                    mortalWoundTimer = 7500;
        }
        else
            mortalWoundTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

struct mob_soldierAI : public kt_p1AddAI
{
    mob_soldierAI(Creature* pCreature) : kt_p1AddAI(pCreature)
    {
        Reset();
    }

    void Reset() override
    {
    }

    void UpdateAI(const uint32 diff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_creature->HasAura(SPELL_DARK_BLAST_AUR))
            m_creature->CastSpell(m_creature, SPELL_DARK_BLAST_AUR, true);

        //if (m_creature->getVictim() && m_creature->getVictim()->IsPlayer()) 
        //{
        //    bool inVisibleList = m_creature->getVictim()->ToPlayer()->IsInVisibleList(m_creature);
        //    sLog.outBasic("%s visible: %d", m_creature->getVictim()->GetName(), inVisibleList);
        //}
        //m_creature->ForceValuesUpdateAtIndex(UNIT_FIELD_TARGET);

        // to avoid melees being able to dps while casters hold aggro, this is most likely a logic that's supposed to exist
        if (auto const nearest = m_creature->SelectAttackingTarget(ATTACKING_TARGET_NEAREST, 0))
            if (m_creature->getVictim() != nearest && m_creature->CanReachWithMeleeAttack(nearest))
                ScriptedAI::AttackStart(nearest);

        DoMeleeAttackIfReady();
    }
};

struct mob_soulweaverAI : public kt_p1AddAI
{
    mob_soulweaverAI(Creature* pCreature) : kt_p1AddAI(pCreature)
    {
    }

    bool hasHitSomeone;

    void Reset() override
    {
        hasHitSomeone = false;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_creature->HasAura(SPELL_WAIL_SOULS_AUR))
            m_creature->CastSpell(m_creature, SPELL_WAIL_SOULS_AUR, true);

        // to avoid melees being able to dps while casters hold aggro, this is most likely a logic that's supposed to exist
        if (auto const nearest = m_creature->SelectAttackingTarget(ATTACKING_TARGET_NEAREST, 0))
            if (m_creature->getVictim() != nearest && m_creature->CanReachWithMeleeAttack(nearest))
                ScriptedAI::AttackStart(nearest);

        DoMeleeAttackIfReady();
    }
};

struct mob_guardian_icecrownAI : public ScriptedAI
{
    mob_guardian_icecrownAI(Creature* pCreature) : m_pInstance((instance_naxxramas*)pCreature->GetInstanceData()), ScriptedAI(pCreature)
    {
        Reset();
    }

    instance_naxxramas* const m_pInstance;
    ObjectGuid oldTarget;

    void Reset() override
    {
        oldTarget = 0;
    }

    void JustReachedHome() override
    {
        m_creature->DeleteLater();
        ///m_creature->ForcedDespawn(1);
    }
    
    static constexpr uint32 shackleRank1 = 9484;
    static constexpr uint32 shackleRank2 = 9485;
    static constexpr uint32 shackleRank3 = 10955;

    void DispellShackle(Creature* pC)
    {
        pC->RemoveAurasDueToSpell(shackleRank1);
        pC->RemoveAurasDueToSpell(shackleRank2);
        pC->RemoveAurasDueToSpell(shackleRank3);
    }

    void SpellHit(Unit*, const SpellEntry* spell) override 
    {
        // if hit by any shackle spell we check how many other guardians are shackled.
        // If more than 3, we release everyone.
        switch (spell->Id)
        {
        case shackleRank3:
        case shackleRank2:
        case shackleRank1:
        {
            std::list<Creature*> guardians;
            GetCreatureListWithEntryInGrid(guardians, m_creature, NPC_GUARDIAN, 130.0f);

            uint32 numShackled = 0;
            for (auto const pC : guardians)
            {
                if (pC->HasAura(shackleRank1) || pC->HasAura(shackleRank2) || pC->HasAura(shackleRank3))
                    ++numShackled;
            }
                
            if (numShackled > 3)
            {
                if (m_pInstance)
                {
                    if (Creature* pKT = m_pInstance->GetSingleCreatureFromStorage(NPC_KELTHUZAD))
                        DoScriptText(SAY_SPECIAL2_DISPELL, pKT);
                }

                for (auto const pC : guardians)
                    DispellShackle(pC);
            }

            break;
        }
        }
    }

    void OnPlayerDeath()
    {
        if (auto const victim = m_creature->getVictim())
            DoCastSpellIfCan(victim, SPELL_BLOOD_TAP);
    }

    void UpdateAI(const uint32) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (auto const victim = m_creature->getVictim())
        {
            if (victim->GetObjectGuid() != oldTarget)
            {
                // if we have changed targets, cast blood tap
                if (oldTarget)
                    DoCastSpellIfCan(victim, SPELL_BLOOD_TAP);

                oldTarget = victim->GetObjectGuid();
            }
        }

        DoMeleeAttackIfReady();
    }
};

struct mob_shadow_fissureAI : public ScriptedAI
{
    mob_shadow_fissureAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 timer;
    bool haveCasted;

    void Reset() override
    {
        timer = 3000;
        haveCasted = false;
    }

    void Aggro(Unit*) override
    {
    }

    void AttackStart(Unit*) override
    {
    }

    void MoveInLineOfSight(Unit* pWho) override
    {
    }

    void UpdateAI(const uint32 diff) override
    {
        if (haveCasted)
            return;
        if (timer < diff)
        {
            m_creature->CastSpell(m_creature, SPELL_VOID_BLAST, true);
            haveCasted = true;
            m_creature->ForcedDespawn(2250);
        }
        else
            timer -= diff;
    }
};

CreatureAI* GetAI_boss_kelthuzad(Creature* pCreature)
{
    return new boss_kelthuzadAI(pCreature);
}

CreatureAI* GetAI_mob_abom(Creature* pCreature)
{
    return new mob_abomAI(pCreature);
}

CreatureAI* GetAI_mob_soldier(Creature* pCreature)
{
    return new mob_soldierAI(pCreature);
}

CreatureAI* GetAI_mob_soulweaver(Creature* pCreature)
{
    return new mob_soulweaverAI(pCreature);
}

CreatureAI* GetAI_mob_guardian_icecrown(Creature* pCreature)
{
    return new mob_guardian_icecrownAI(pCreature);
}

CreatureAI* GetAI_mob_shadow_fissure(Creature* pCreature)
{
    return new mob_shadow_fissureAI(pCreature);
}

void instance_naxxramas::OnKTAreaTrigger(const AreaTriggerEntry* pAT)
{
    if (GetData(TYPE_KELTHUZAD) != NOT_STARTED)
        return;

    if (Creature* pKT = GetSingleCreatureFromStorage(NPC_KELTHUZAD))
        if (auto const ai = dynamic_cast<boss_kelthuzadAI *>(pKT->AI()))
            ai->StartEncounter();
}

void instance_naxxramas::OnKTPlayerDeath(Player* p)
{
    std::list<Creature*> guardians;
    GetCreatureListWithEntryInGrid(guardians, p, NPC_GUARDIAN, 130.0f);

    for (auto guardian : guardians)
        if (auto ai = dynamic_cast<mob_guardian_icecrownAI *>(guardian->AI()))
            ai->OnPlayerDeath();
}

void AddSC_boss_kelthuzad()
{
    Script* NewScript;

    NewScript = new Script;
    NewScript->Name = "boss_kelthuzad";
    NewScript->GetAI = &GetAI_boss_kelthuzad;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "unstoppable_abomination_ai";
    NewScript->GetAI = &GetAI_mob_abom;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "soldier_frozen_wastes_ai";
    NewScript->GetAI = &GetAI_mob_soldier;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "soul_weaver_ai";
    NewScript->GetAI = &GetAI_mob_soulweaver;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_guardian_icecrownAI";
    NewScript->GetAI = &GetAI_mob_guardian_icecrown;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_shadow_fissure";
    NewScript->GetAI = &GetAI_mob_shadow_fissure;
    NewScript->RegisterSelf();
}
