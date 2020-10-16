/* This file is part of the ScriptDev2 Project. See AUTHORS file for Copyright information
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

/* ScriptData
SDName: Boss_Thaddius
SD%Complete: 
SDComment: 
SDCategory: 
EndScriptData */

/* ContentData
boss_thaddius
npc_tesla_coil
boss_stalagg
boss_feugen
EndContentData */

#include "scriptPCH.h"
#include "naxxramas.h"

#include <random>
#include <algorithm>

namespace
{
enum eStalaggFeugen
{
    // Stalagg
    SAY_STAL_AGGRO      = -1533023,
    SAY_STAL_SLAY       = -1533024,
    SAY_STAL_DEATH      = -1533025,

    // Feugen
    SAY_FEUG_AGGRO      = -1533026,
    SAY_FEUG_SLAY       = -1533027,
    SAY_FEUG_DEATH      = -1533028,

    SPELL_WARSTOMP      = 28125,
    SPELL_FLASH         = 28127, // TODO: stun spell supposedly used by feugen? Cant find any sources for it
    SPELL_POWERSURGE    = 28134,
    SPELL_STATIC_FIELD  = 28135,
    SPELL_MAGNETIC_PULL = 28337,
};

enum addEvents
{
    EVENT_WARSTOMP = 1,
    EVENT_STATIC_FIELD,
    EVENT_POWERSURGE,
    EVENT_MAGNETIC_PULL,
};

enum eThaddius
{
    SAY_AGGRO_1                     = -1533030,
    SAY_AGGRO_2                     = -1533031,
    SAY_AGGRO_3                     = -1533032,

    SAY_SLAY                        = -1533033,
    SAY_ELECT                       = -1533034,
    SAY_DEATH                       = -1533035,

    //EMOTE_POLARITY_SHIFT = -1533151, // NOT used in vanilla from what I can see

    SPELL_THADIUS_SPAWN             = 28160,
    SPELL_THADIUS_LIGHTNING_VISUAL  = 28136,
    SPELL_BALL_LIGHTNING            = 28299,
    SPELL_CHAIN_LIGHTNING           = 28167,
    SPELL_BESERK                    = 27680,

    SPELL_POLARITY_SHIFT            = 28089,

    SPELL_POSITIVE_CHARGE_APPLY     = 28059,
    SPELL_POSITIVE_CHARGE_TICK      = 28062,
    SPELL_POSITIVE_CHARGE_AMP       = 29659,

    SPELL_NEGATIVE_CHARGE_APPLY     = 28084,
    SPELL_NEGATIVE_CHARGE_TICK      = 28085,
    SPELL_NEGATIVE_CHARGE_AMP       = 29660,
};

enum eCoils
{
    EMOTE_LOSING_LINK           = -1533149, // not sure if existed in vanilla
    EMOTE_TESLA_OVERLOAD        = -1533150, // confirmed existed in vanilla

    SPELL_FEUGEN_CHAIN          = 28111,
    SPELL_STALAGG_CHAIN         = 28096,
    SPELL_FEUGEN_TESLA_PASSIVE  = 28109,
    SPELL_STALAGG_TESLA_PASSIVE = 28097,
    SPELL_SHOCK_OVERLOAD        = 28159,
    SPELL_SHOCK                 = 28099,
};

enum eStalagFeugen
{
    eSTALAGG = 0,
    eFEUGEN
};

enum ThaddiusPhase
{
    THAD_NOT_STARTED,
    THAD_PHASE1,
    THAD_TRANSITION,
    THAD_PHASE2
};

enum thaddiusEvents
{
    EVENT_SHIFT = 1,                // polarity shift cast
    EVENT_SHIFT_TALK,               // polarity shift yell (hack? couldn't find any event for cast finish)
    EVENT_POLARITY_CHANGE,          // end of polarity shift cast, actually shift polarities
    EVENT_CHAIN,                    // chain lightning
    EVENT_BERSERK,                  // enrage timer
    EVENT_REVIVE_FEUGEN,            // timer until feugen is revived (if stalagg still lives)
    EVENT_REVIVE_STALAGG,           // timer until stalagg is revived (if feugen still lives)
    EVENT_TRANSITION_1,             // timer until overload emote
    EVENT_TRANSITION_2,             // timer until thaddius gets zapped by the coils
    EVENT_TRANSITION_3,             // timer until thaddius engages
    EVENT_ENABLE_BALL_LIGHTNING,    // grace period after thaddius aggro after which he starts being a baller (e.g. tossing ball lightning at out of range targets)
};

constexpr uint32 INITIAL_POLARITY_SHIFT_TIMER = 10 * IN_MILLISECONDS;   // first polarity shift happens after ten seconds
constexpr uint32 POLARITY_SHIFT_TIMER = 30 * IN_MILLISECONDS;           // subsequent polarity shifts happen every 30 seconds
constexpr uint32 POLARITY_SHIFT_DELAY = 3 * IN_MILLISECONDS;            // time between polarity shift start and actual shifting happens
constexpr uint32 ADDS_RESPAWN_TIMER = 5 * IN_MILLISECONDS;              // adds respawn after 5 sec if not both area killed in that window.
constexpr uint32 ENRAGE_TIMER = 5 * MINUTE * IN_MILLISECONDS;           // 5 min enrage once p2 starts

// Chain lightning timer. TODO: confirm timers. Atm is guess
uint32 ChainLightningTimer()
{
    return urand(5 * IN_MILLISECONDS, 7 * IN_MILLISECONDS);
}

constexpr float addPositions[2][4] =
{
    { 3449.03f, -2934.74f, 312.18f, 5.41f },
    { 3508.85f, -2994.08f, 312.18f, 2.33f },
};
constexpr float teslaCoilPositions[2][3] =
{
    //{ 3487.76f, -2911.2f, 319.406f },
    { 3487.10f, -2911.50f, 319.526f },
    { 3527.81f, -2952.38f, 319.526f }
};
}

struct npc_tesla_coilAI : public Scripted_NoMovementAI
{
    npc_tesla_coilAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        Reset();
    }

    instance_naxxramas* m_pInstance;
    bool m_bToFeugen;
    ObjectGuid m_guid;
    uint32 m_shockTimer;
    bool m_hadLink;

    void Reset() override
    {
        m_creature->SetRespawnRadius(0.01f);
        m_creature->SetDefaultMovementType(RANDOM_MOTION_TYPE);
        m_creature->GetMotionMaster()->Initialize();
        m_shockTimer = 0;
        m_hadLink = true;
    }

    void MoveInLineOfSight(Unit* /*pWho*/) override {}

    void Aggro(Unit* /*pWho*/) override
    {
        //m_creature->SetInCombatWithZone();
    }

    void ReApplyChain(uint32 uiEntry, ObjectGuid guid)
    {
        m_guid = guid;
        if (uiEntry == NPC_FEUGEN)
            m_bToFeugen = true;
        else if (uiEntry == NPC_STALAGG)
            m_bToFeugen = false;
        else
            sLog.outError("npc_tesla_coilAI::ReApplyChain got entry which was not stalagg or feugen.");


        DoCastSpellIfCan(m_creature, m_bToFeugen ? SPELL_FEUGEN_CHAIN : SPELL_STALAGG_CHAIN);
    }
 
    void UpdateAI(const uint32 uiDiff) override
    {
        if (Creature* add = m_pInstance->GetCreature(m_guid))
        {
            if (add->isInCombat() && !m_creature->isInCombat())
            {
                m_creature->SetInCombatWithZone();
            }

            if (m_creature->GetDistance2d(add) > 60.0f)
            {
                m_creature->InterruptNonMeleeSpells(true);
                //if (add->HasAura(m_bToFeugen ? SPELL_FEUGEN_CHAIN : SPELL_STALAGG_CHAIN))
                if (m_hadLink)
                    DoScriptText(EMOTE_LOSING_LINK, m_creature);
                m_hadLink = false;
                if (m_shockTimer < uiDiff)
                {
                    m_shockTimer = 1500;
                    // todo: not sure if should target nearest or random target
                    if (Unit* shockTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_NEAREST, 0, nullptr, SELECT_FLAG_PLAYER))
                    {
                        m_creature->CastSpell(shockTarget, SPELL_SHOCK, true);
                    }
                }
                else
                    m_shockTimer -= uiDiff;
            }
            else
            {
                m_shockTimer = 0;
                if (!m_creature->IsNonMeleeSpellCasted(true))
                    DoCastSpellIfCan(m_creature, m_bToFeugen ? SPELL_FEUGEN_CHAIN : SPELL_STALAGG_CHAIN);
                m_hadLink = true;
            }
        }
    }
};

struct boss_thaddiusAddsAI : public ScriptedAI
{
    boss_thaddiusAddsAI(Creature* pCreature, eStalagFeugen sOrF) :
        ScriptedAI(pCreature),
        m_pInstance((instance_naxxramas*)pCreature->GetInstanceData()),
        m_SorF(sOrF)
    {
        Reset();
    }

    instance_naxxramas * const m_pInstance;
    const eStalagFeugen m_SorF;

    bool m_bFakeDeath;
    uint32 m_fakeDeathTimer;
    bool m_bothDead;
    uint32 m_timeSincePull;
    EventMap m_events;
    ObjectGuid m_otherAdd;

    void Reset() override
    {
        m_events.Reset();
        m_timeSincePull = 0;
        m_fakeDeathTimer = 0;
        m_bFakeDeath = false;
        m_bothDead = false;

        // We might Reset while faking death, so undo this
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetHealth(m_creature->GetMaxHealth());
        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
    }

    uint32 WarstompTimer() const
    {
        // best guess timer based on 
        // https://www.youtube.com/watch?v=GmE5JufAcT0
        // and https://www.youtube.com/watch?v=3hen_d6cb-Y
        return urand(15 * IN_MILLISECONDS, 20 * IN_MILLISECONDS);
    }

    uint32 PowerSurgeTimer() const
    {
        // https://www.youtube.com/watch?v=3hen_d6cb-Y
        // Timer seems correct based on above video
        return urand(25 * IN_MILLISECONDS, 30 * IN_MILLISECONDS);
    }

    uint32 MagneticPullTimer() const
    {
        // according to http://wowwiki.wikia.com/wiki/Thaddius_(original)?oldid=2179319 this happens every 20.6 seconds
        return 20600; 
    }

    uint32 StaticFiledTimer() const
    {
        //https://www.youtube.com/watch?v=GmE5JufAcT0
        // animation can be seen in video, pretty much exactly every 6 seconds
        return 6 * IN_MILLISECONDS;
    }
    
    Creature* GetOtherAdd()
    {
        if (!m_pInstance)
            return nullptr;

        return m_pInstance->GetCreature(m_otherAdd);
    }

    void Aggro(Unit* pWho) override
    {
        if (m_bFakeDeath)
            return;

        if (!m_pInstance)
            return;

        m_creature->SetInCombatWithZone();
        m_pInstance->SetData(TYPE_THADDIUS, IN_PROGRESS);

        // when the first mob enters combat, the other one should target whoever is closest to him
        if (auto const pOtherAdd = GetOtherAdd())
            if (!pOtherAdd->isInCombat())
            {
                auto const& lPlayers = m_pInstance->GetMap()->GetPlayers();

                Player *nearest = nullptr;
                float distance = -1.f;

                for (auto const& p : lPlayers)
                {
                    auto const player = p.getSource();

                    if (player->isDead())
                        continue;

                    auto const dist2 = player->GetDistance2d(pOtherAdd);

                    if (distance < 0.f || dist2 < distance)
                    {
                        distance = dist2;
                        nearest = player;
                    }
                }

                pOtherAdd->AI()->AttackStart(nearest ? nearest : pWho);
            }
    }

    void JustRespawned() override
    {
        Reset();                                            // Needed to reset the flags properly
    }

    void JustReachedHome() override
    {
        if (!m_pInstance)
            return;

        m_events.Reset();
        m_pInstance->SetData(TYPE_THADDIUS, FAIL);
    }

    // this currently is on a timer run only under Stalagg
    bool HandleMagneticPull()
    {
        if (m_bFakeDeath)
            return false;

        auto const stalaggTank = m_creature->getVictim();

        if (!stalaggTank)
            return false;

        Creature* feugen = GetOtherAdd();

        if (!feugen)
            return false;

        if (boss_thaddiusAddsAI* feugenAI = dynamic_cast<boss_thaddiusAddsAI*>(feugen->AI()))
        {
            if (feugenAI->m_bFakeDeath)
                return false; // can, presumably, only do it when both are alive
        }

        // unit being pulled
        auto const feugenTank = feugen->getVictim();

        if (!feugenTank)
            return false;

        auto& stalaggThreat = m_creature->getThreatManager();
        auto& feugenThreat = feugen->getThreatManager();

        // Stalagg threat for his tank
        auto const stalaggTankThreat = stalaggThreat.getThreat(stalaggTank);

        // Stalagg's threat for Feugen's tank
        auto const stalaggOtherTankThreat = stalaggThreat.getThreat(feugenTank);

        // Feugen threat for his tank
        auto const feugenTankThreat = feugenThreat.getThreat(feugenTank);

        // Feugen's threat for Stalagg's tank
        auto const feugenOtherTankThreat = feugenThreat.getThreat(stalaggTank);

        // for the new tanks of both mobs, add however much threat is necessary to both threat tables
        // to effectively swap threat entries
        stalaggThreat.addThreat(feugenTank, feugenTankThreat - stalaggOtherTankThreat);
        feugenThreat.addThreat(stalaggTank, stalaggTankThreat - feugenOtherTankThreat);

        // for the old tanks, subtract however much threat is necessary to both threat tables to
        // complete the threat swap
        stalaggThreat.addThreat(stalaggTank, feugenOtherTankThreat - stalaggTankThreat);
        feugenThreat.addThreat(feugenTank, stalaggOtherTankThreat - feugenTankThreat);

        m_creature->InterruptNonMeleeSpells(true);
        m_creature->CastSpell(feugenTank, SPELL_MAGNETIC_PULL, true);
        feugen->InterruptNonMeleeSpells(true);
        feugen->CastSpell(stalaggTank, SPELL_MAGNETIC_PULL, true);

        // and make both attack their respective new tanks
        AttackStart(feugenTank);
        feugen->AI()->AttackStart(stalaggTank);

        return true;
    }

    void HandleReviveEvent()
    {
        Reset();
        DoResetThreat();
        if (Unit* nearestTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_NEAREST, 0))
        {
            Aggro(nearestTarget);
        }
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (m_bFakeDeath)
        {
            if (m_fakeDeathTimer < uiDiff)
            {
                if (!m_bothDead)
                    HandleReviveEvent();
            }
            else
                m_fakeDeathTimer -= uiDiff;

            return;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        m_timeSincePull += uiDiff;
        m_events.Update(uiDiff);

        while (auto l_EventId = m_events.ExecuteEvent())
        {
            switch (l_EventId)
            {
            case EVENT_WARSTOMP:
                // need to delay warstomp if we have just done the pull. If warstomp hits midair the
                // pull effect is cancelled and tanks fall down
                if (m_timeSincePull < 5 * IN_MILLISECONDS)
                {
                    m_events.Repeat(5 * IN_MILLISECONDS - m_timeSincePull);
                }
                else
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_WARSTOMP) == CAST_OK)
                        m_events.Repeat(WarstompTimer());
                    else
                        m_events.Repeat(100);
                }
                break;
            case EVENT_STATIC_FIELD:
                if (DoCastSpellIfCan(m_creature, SPELL_STATIC_FIELD) == CAST_OK)
                    m_events.Repeat(StaticFiledTimer());
                else
                    m_events.Repeat(100);
                break;  
            case EVENT_POWERSURGE:
                if (DoCastSpellIfCan(m_creature, SPELL_POWERSURGE) == CAST_OK)
                    m_events.Repeat(PowerSurgeTimer());
                else
                    m_events.Repeat(100);
                break;
            case EVENT_MAGNETIC_PULL:
                if (HandleMagneticPull())
                {
                    m_events.Repeat(MagneticPullTimer());
                    m_timeSincePull = 0;
                }
                else
                    m_events.Repeat(100);
                break;
            }
        }

        DoMeleeAttackIfReady();
    }

    void AttackStart(Unit* pWho) override
    {
        if (m_bFakeDeath)
            return;
        ScriptedAI::AttackStart(pWho);
    }

    void DamageTaken(Unit* pKiller, uint32& uiDamage) override
    {
        // if the damage taken is not enough to kill the creature, do nothing
        if (uiDamage < m_creature->GetHealth())
            return;

        // if we are already faking our death, cancel the damage and do nothing else
        if (m_bFakeDeath)
        {
            uiDamage = 0;
            return;
        }

        // if the other add is already faking its death, they will now both be dead
        if (auto const otherAdd = GetOtherAdd())
            if (auto const otherAI = dynamic_cast<boss_thaddiusAddsAI*>(otherAdd->AI()))
                if (otherAI->m_bFakeDeath)
                {
                    otherAI->m_bothDead = m_bothDead = true;

                    if (m_pInstance)
                        m_pInstance->SetData(TYPE_THADDIUS, SPECIAL);
                }

        if (m_SorF == eSTALAGG)
            DoScriptText(SAY_STAL_DEATH, m_creature);
        else
            DoScriptText(SAY_FEUG_DEATH, m_creature);

        uiDamage = 0;
        
        m_fakeDeathTimer = 5 * IN_MILLISECONDS;
        m_bFakeDeath = true;
        m_creature->InterruptNonMeleeSpells(false);
        m_creature->SetHealth(0);
        m_creature->StopMoving();
        m_creature->ClearComboPointHolders();
        m_creature->RemoveAllAurasOnDeath(); // todo: will this remove the chain?
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->ClearAllReactives();
        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MoveIdle();
        m_creature->SetStandState(UNIT_STAND_STATE_DEAD);
        m_creature->AttackStop();
    }
};

struct boss_thaddiusAI : public ScriptedAI
{
    boss_thaddiusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_naxxramas*)pCreature->GetInstanceData();
        Reset();
        
        if (m_pInstance)
        {
            CheckSpawnAdds();
        }

        // Apply the "stun" aura again, which makes him darker and not moving
        if (!m_creature->HasAura(SPELL_THADIUS_SPAWN))
            m_creature->CastSpell(m_creature, SPELL_THADIUS_SPAWN, true);

        // He is not targetable other than in p2
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    instance_naxxramas* m_pInstance;
    
    uint32 m_uiBallLightningTimer;
    
    ThaddiusPhase m_Phase;
    ObjectGuid addGuids[2];
    ObjectGuid coilGuids[2];
    ObjectGuid stalaggChainCreature;
    ObjectGuid feugenChainCreature;

    EventMap m_events;

    std::random_device m_randDevice;
    std::mt19937 m_random{ m_randDevice() };
    uint32 killSayCooldown;

    // Helper for CheckSpawnAdds
    void HandleCheckSpawnAdd(eStalagFeugen whichAdd)
    {
        auto const addEntry = whichAdd == eSTALAGG ? NPC_STALAGG : NPC_FEUGEN;

        // Respawn or revive the add itself
        // Simply unsummoning the add and the coil creature if they still exist
        if (auto const addCreature = m_pInstance->GetCreature(addGuids[whichAdd]))
        { 
            if (auto const tmpSumm = dynamic_cast<TemporarySummon*>(addCreature))
                tmpSumm->UnSummon();
            else
                sLog.outError("Thaddius: HandleCheckSpawnAdd addCreature was not temp summon");
        }

        // Summonming a new add
        if (auto const add = m_creature->SummonCreature(addEntry,
            addPositions[whichAdd][0], addPositions[whichAdd][1], addPositions[whichAdd][2], addPositions[whichAdd][3],
            TEMPSUMMON_MANUAL_DESPAWN))
        {
            addGuids[whichAdd] = add->GetObjectGuid();
        }
        else
            sLog.outError("Thaddius: failed spawning add %d", whichAdd);

        if (auto const coilCreature = m_pInstance->GetCreature(coilGuids[whichAdd]))
        {
            if (auto const tmpSumm = dynamic_cast<TemporarySummon*>(coilCreature))
                tmpSumm->UnSummon();
            else
                sLog.outError("Thaddius: HandleCheckSpawnAdd coilCreature was not temp summon");
        }

        // Summoning a new coil
        if (auto const coil = m_creature->SummonCreature(NPC_TESLA_COIL,
            teslaCoilPositions[whichAdd][0], teslaCoilPositions[whichAdd][1], teslaCoilPositions[whichAdd][2], 0,
            TEMPSUMMON_MANUAL_DESPAWN))
        {
            coilGuids[whichAdd] = coil->GetObjectGuid();

            if (auto const pTeslaAI = dynamic_cast<npc_tesla_coilAI*>(coil->AI()))
                pTeslaAI->ReApplyChain(addEntry, addGuids[whichAdd]);
            else
                sLog.outError("boss_thaddiusAddsAI::EstablishLink failed to cast tesla coil to npc_tesla_coilAI*");
        }
        else
            sLog.outError("boss_thaddiusAddsAI::EstablishLink failed to spawn teslaCoil");

        // Making sure the coil GO does its animation
        auto const coilGOEntry = whichAdd == eSTALAGG ? GO_CONS_NOX_TESLA_STALAGG : GO_CONS_NOX_TESLA_FEUGEN;
        if (GameObject* tc = m_pInstance->GetSingleGameObjectFromStorage(coilGOEntry))
            tc->SetGoState(GO_STATE_ACTIVE);
    }
    
    // Respawn stalagg and feugen and the tesla coils corresponding to them. Activates the tesla coil GO and sets the chain
    void CheckSpawnAdds()
    {
        if (m_pInstance && m_pInstance->GetData(TYPE_THADDIUS) == DONE)
            return;

        HandleCheckSpawnAdd(eStalagFeugen::eSTALAGG);
        HandleCheckSpawnAdd(eStalagFeugen::eFEUGEN);

        if (Creature* pFeugen = m_pInstance->GetCreature(addGuids[eFEUGEN]))
            if (auto const addAI = dynamic_cast<boss_thaddiusAddsAI*>(pFeugen->AI()))
                addAI->m_otherAdd = addGuids[eSTALAGG];

        if (Creature* pStalagg = m_pInstance->GetCreature(addGuids[eSTALAGG]))
            if (auto const addAI = dynamic_cast<boss_thaddiusAddsAI*>(pStalagg->AI()))
                addAI->m_otherAdd = addGuids[eFEUGEN];
    }

    // Unsummons the tesla coil creature and stops animation of the coil GO
    void HandleUnsummonCoil(eStalagFeugen which)
    {
        // Unsummon the tesla coil creature
        if (Creature* tc = m_pInstance->GetCreature(coilGuids[which]))
        {
            if (TemporarySummon* tmpSumm = static_cast<TemporarySummon*>(tc)) {
                tmpSumm->UnSummon();
            }
        }
        coilGuids[which] = 0;

        // Make the tesla coil game object stop animating
        uint32 goEntry = which == eSTALAGG ? GO_CONS_NOX_TESLA_STALAGG : GO_CONS_NOX_TESLA_FEUGEN;
        if (GameObject* pG = m_pInstance->GetSingleGameObjectFromStorage(goEntry))
        {
            pG->SetGoState(GO_STATE_READY);
        }
    }

    void HandleUnsummonAdd(eStalagFeugen which)
    {
        if (Creature* add = m_pInstance->GetCreature(addGuids[which]))
        {
            if (TemporarySummon* tmpSumm = static_cast<TemporarySummon*>(add)) {
                tmpSumm->UnSummon();
            }
        }
        addGuids[which] = 0;
    }

    void SummonedCreatureDespawn(Creature* pC) override 
    {
        if (!m_pInstance)
            return;
        /*
        // Unsummoning the tesla coils when stalagg and feugen despawns
        if (pC->GetObjectGuid() == addGuids[eSTALAGG])
            HandleUnsummonCoil(eSTALAGG);
        else if (pC->GetObjectGuid() == addGuids[eFEUGEN])
            HandleUnsummonCoil(eFEUGEN);
        */
    }

    void Reset() override
    {
        m_events.Reset();
        m_uiBallLightningTimer = 1 * IN_MILLISECONDS;
        m_Phase = THAD_NOT_STARTED;
        killSayCooldown = 0;
    }

    void Aggro(Unit* /*pWho*/) override
    {
        /*
        switch (urand(0, 2))
        {
        case 0: DoScriptText(SAY_AGGRO_1, m_creature); break;
        case 1: DoScriptText(SAY_AGGRO_2, m_creature); break;
        case 2: DoScriptText(SAY_AGGRO_3, m_creature); break;
        }
        // Make Attackable
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        */
    }

    void JustReachedHome() override
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_THADDIUS, FAIL);
            CheckSpawnAdds();
        }

        // Apply the "stun" aura again, which makes him darker and not moving
        if (!m_creature->HasAura(SPELL_THADIUS_SPAWN))
            m_creature->CastSpell(m_creature, SPELL_THADIUS_SPAWN, true);

        // He is not targetable other than in p2
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }
    
    void KilledUnit(Unit* pVictim) override
    {
        if (pVictim->GetTypeId() != TYPEID_PLAYER)
            return;

        if (!killSayCooldown)
        {
            DoScriptText(SAY_SLAY, m_creature);
            killSayCooldown = 5 * IN_MILLISECONDS;
        }
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_THADDIUS, DONE);
            
            //they will despawn themself.
            // Make them TEMPSUMMON_TIMED_DEAD_DESPAWN with 10-20sec despawn time,
            /*
            // Force Despawn of Adds
            Creature* pFeugen = m_pInstance->GetSingleCreatureFromStorage(NPC_FEUGEN);
            Creature* pStalagg = m_pInstance->GetSingleCreatureFromStorage(NPC_STALAGG);

            if (pFeugen)
                pFeugen->ForcedDespawn();
            if (pStalagg)
                pStalagg->ForcedDespawn();
            */
        }
    }

    void TransitionToPhase(ThaddiusPhase newPhase)
    {
        m_Phase = newPhase;

        switch (m_Phase)
        {
        case ThaddiusPhase::THAD_NOT_STARTED:
            m_creature->OnLeaveCombat();
            break;

        case ThaddiusPhase::THAD_PHASE1:
            m_creature->SetInCombatWithZone();
            break;

        case ThaddiusPhase::THAD_TRANSITION:
            // Source: https://www.youtube.com/watch?v=GmE5JufAcT0
            // 3:18     adds dead
            // 3:28 +10 tesla coil overloads emote (link dissapears, GO still animating)
            // 3:31 +3  tesla coils shoots beam thing at thaddius. SPELL_THADIUS_SPAWN removed
            // 3:33 +2  thaddius engage. GO stops animating
            m_events.ScheduleEvent(EVENT_TRANSITION_1, 10 * IN_MILLISECONDS);
            m_events.ScheduleEvent(EVENT_TRANSITION_2, 13 * IN_MILLISECONDS);
            m_events.ScheduleEvent(EVENT_TRANSITION_3, 14 * IN_MILLISECONDS);
            break;

        case ThaddiusPhase::THAD_PHASE2:
            DoResetThreat();

            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_NEAREST, 0))
                AttackStart(pTarget);

            m_events.ScheduleEvent(EVENT_BERSERK, ENRAGE_TIMER);
            m_events.ScheduleEvent(EVENT_SHIFT, INITIAL_POLARITY_SHIFT_TIMER);
            m_events.ScheduleEvent(EVENT_CHAIN, ChainLightningTimer());
            break;
        default:
            sLog.outError("boss_thaddiusAI in undefined phase-state");
        }
    }

    void UpdateTransitionPhase(const uint32 diff)
    {
        m_events.Update(diff);

        while (auto const eventId = m_events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_TRANSITION_1:
                // stop link to adds, coils do overload emote
                HandleUnsummonAdd(eSTALAGG);
                HandleUnsummonAdd(eFEUGEN);

                if (Creature* coil = m_pInstance->GetCreature(coilGuids[0]))
                    DoScriptText(EMOTE_TESLA_OVERLOAD, coil);

                if (Creature* coil = m_pInstance->GetCreature(coilGuids[1]))
                    DoScriptText(EMOTE_TESLA_OVERLOAD, coil);

                break;
            case EVENT_TRANSITION_2:
                // coils shoot beam at thaddius. SPELL_THADIUS_SPAWN removed
                if (Creature* coil = m_pInstance->GetCreature(coilGuids[0]))
                    coil->CastSpell(m_creature, SPELL_SHOCK_OVERLOAD, true);

                if (Creature* coil = m_pInstance->GetCreature(coilGuids[1]))
                    coil->CastSpell(m_creature, SPELL_SHOCK_OVERLOAD, true);

                m_creature->RemoveAurasDueToSpell(SPELL_THADIUS_SPAWN);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                m_creature->CastSpell(m_creature, SPELL_THADIUS_LIGHTNING_VISUAL, true);
                break;
            case EVENT_TRANSITION_3:
                HandleUnsummonCoil(eSTALAGG);
                HandleUnsummonCoil(eFEUGEN);
                /*
                // Thaddius engage. GOs stops animating
                if (GameObject* pG = m_pInstance->GetSingleGameObjectFromStorage(GO_CONS_NOX_TESLA_FEUGEN))
                    pG->SetGoState(GO_STATE_READY);
                if (GameObject* pG = m_pInstance->GetSingleGameObjectFromStorage(GO_CONS_NOX_TESLA_STALAGG))
                    pG->SetGoState(GO_STATE_READY);
                */
                TransitionToPhase(THAD_PHASE2);
                break;
            }
        }
    }

    void RemoveDebuffsFromPlayer(Player* pPlayer) const
    {
        pPlayer->RemoveAurasDueToSpell(SPELL_POSITIVE_CHARGE_AMP);
        pPlayer->RemoveAurasDueToSpell(SPELL_POSITIVE_CHARGE_APPLY);
        pPlayer->RemoveAurasDueToSpell(SPELL_POSITIVE_CHARGE_TICK);
        pPlayer->RemoveAurasDueToSpell(SPELL_NEGATIVE_CHARGE_AMP);
        pPlayer->RemoveAurasDueToSpell(SPELL_NEGATIVE_CHARGE_APPLY);
        pPlayer->RemoveAurasDueToSpell(SPELL_NEGATIVE_CHARGE_TICK);
    }

    void DoPolarityShift()
    {
        DoScriptText(SAY_ELECT, m_creature);

        auto const& lPlayers = m_pInstance->GetMap()->GetPlayers();

        std::vector<Player*> players;
        players.reserve(lPlayers.getSize());

        for (auto const& p : lPlayers)
        {
            auto const pPlayer = p.getSource();

            if (pPlayer->isAlive())
                players.push_back(pPlayer);
        }

        std::shuffle(players.begin(), players.end(), m_random);

        for (auto i = 0u; i < players.size(); ++i)
        {
            auto const player = players[i];

            RemoveDebuffsFromPlayer(player);

            player->CastSpell(player, i % 2 ? SPELL_POSITIVE_CHARGE_APPLY : SPELL_NEGATIVE_CHARGE_APPLY, true);
        }
    }

    void DoSpellChain()
    {
        Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
        if (!pTarget || DoCastSpellIfCan(pTarget, SPELL_CHAIN_LIGHTNING) != CAST_OK)
            m_events.Repeat(100);
        else
            m_events.Repeat(ChainLightningTimer());
    }

    void UpdateP2(const uint32 diff)
    {
        if (!m_pInstance)
            return;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        m_events.Update(diff);
        while (auto l_EventId = m_events.ExecuteEvent())
        {
            switch (l_EventId)
            {
            case EVENT_SHIFT:
                if (DoCastSpellIfCan(m_creature, SPELL_POLARITY_SHIFT, CAST_INTERRUPT_PREVIOUS) == CAST_OK)
                {
                    m_events.Repeat(POLARITY_SHIFT_TIMER);
                    m_events.ScheduleEvent(EVENT_POLARITY_CHANGE, POLARITY_SHIFT_DELAY);
                }
                else
                    m_events.Repeat(100);

                break;
            case EVENT_CHAIN:
                DoSpellChain();
                break;
            case EVENT_BERSERK:
                if (DoCastSpellIfCan(m_creature, SPELL_BESERK) != CAST_OK)
                    m_events.Repeat(100);
                break;
            case EVENT_POLARITY_CHANGE:
                DoPolarityShift();
                break;
            }
        }
        
        // m_uiBallLightningTimer reinitialized to 1sec after a successfull melee attack, and only negated if target is oor. 
        // This will prevent the boss from starting to spam balls of lightning if the boss is being moved with lag or something
        if (!DoMeleeAttackIfReady() && !m_creature->CanReachWithMeleeAttack(m_creature->getVictim()))
            m_uiBallLightningTimer -= std::min(diff, m_uiBallLightningTimer);
        else
            m_uiBallLightningTimer = 1 * IN_MILLISECONDS;
        
        // If we did not perform a melee attack, but MH or OH attack was ready, and we were not in melee range,
        // it's time to start hurl some balls of lightning
        if (m_uiBallLightningTimer < diff && !m_creature->IsNonMeleeSpellCasted())
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_BALL_LIGHTNING) == CAST_OK)
                m_uiBallLightningTimer = 1500;
        }
    }
    
    void UpdateAI(const uint32 uiDiff) override
    {
        //return; // xxx debugging adds

        if (!m_pInstance)
            return;

        if (m_Phase != THAD_NOT_STARTED)
        {
            if (m_creature->getThreatManager().isThreatListEmpty())
            {
                TransitionToPhase(THAD_NOT_STARTED);
            }
        }
        else
        {
            // He can act a bit weird if you stand next to him on server startup :/
            if (m_creature->isInCombat())
                TransitionToPhase(THAD_NOT_STARTED);
        }

        killSayCooldown -= std::min(killSayCooldown, uiDiff);

        switch (m_Phase)
        {
        case ThaddiusPhase::THAD_NOT_STARTED:
            // IN_PROGRESS is set by the adds when pulled
            if (m_pInstance->GetData(TYPE_THADDIUS) == IN_PROGRESS)
                TransitionToPhase(THAD_PHASE1);
            break;
        case ThaddiusPhase::THAD_PHASE1:
            // if wipe during add-phase the adds will set FAIL
            if (m_pInstance->GetData(TYPE_THADDIUS) == FAIL)
            {
                TransitionToPhase(THAD_NOT_STARTED);
            }
            // if adds are successfully killed, they set SPECIAL
            else if (m_pInstance->GetData(TYPE_THADDIUS) == SPECIAL)
            {
                TransitionToPhase(THAD_TRANSITION);
            }
            break;
        case ThaddiusPhase::THAD_TRANSITION:
            UpdateTransitionPhase(uiDiff);
            break;
        case ThaddiusPhase::THAD_PHASE2:
            UpdateP2(uiDiff);
            break;
        default:
            sLog.outError("boss_thaddiusAI in undefined phase-state");
        }
    }
};

struct boss_stalaggAI : public boss_thaddiusAddsAI
{
    boss_stalaggAI(Creature* pCreature) : 
        boss_thaddiusAddsAI(pCreature, eSTALAGG)
    {
        Reset();
    }

    void Aggro(Unit* pWho) override
    {
        DoScriptText(SAY_STAL_AGGRO, m_creature);
        m_events.ScheduleEvent(EVENT_WARSTOMP, WarstompTimer());
        m_events.ScheduleEvent(EVENT_POWERSURGE, PowerSurgeTimer());
        m_events.ScheduleEvent(EVENT_MAGNETIC_PULL, MagneticPullTimer());
        boss_thaddiusAddsAI::Aggro(pWho);
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        if (m_bothDead && m_pInstance && m_pInstance->GetData(TYPE_THADDIUS) != SPECIAL)
            m_pInstance->SetData(TYPE_THADDIUS, SPECIAL);
    }

    void KilledUnit(Unit* pVictim) override
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            DoScriptText(SAY_STAL_SLAY, m_creature);
    }
};

struct boss_feugenAI : public boss_thaddiusAddsAI
{
    boss_feugenAI(Creature* pCreature) : 
        boss_thaddiusAddsAI(pCreature, eFEUGEN)
    {
        Reset();
    }

    void Aggro(Unit* pWho) override
    {
        DoScriptText(SAY_FEUG_AGGRO, m_creature);

        m_events.ScheduleEvent(EVENT_WARSTOMP, WarstompTimer());
        m_events.ScheduleEvent(EVENT_STATIC_FIELD, StaticFiledTimer());

        boss_thaddiusAddsAI::Aggro(pWho);
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        if (m_bothDead && m_pInstance && m_pInstance->GetData(TYPE_THADDIUS) != SPECIAL)
            m_pInstance->SetData(TYPE_THADDIUS, SPECIAL);
    }

    void KilledUnit(Unit* pVictim) override
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            DoScriptText(SAY_FEUG_SLAY, m_creature);
    }
};

CreatureAI* GetAI_boss_feugen(Creature* pCreature)
{
    return new boss_feugenAI(pCreature);
}

CreatureAI* GetAI_boss_stalagg(Creature* pCreature)
{
    return new boss_stalaggAI(pCreature);
}

CreatureAI* GetAI_npc_tesla_coil(Creature* pCreature)
{
    return new npc_tesla_coilAI(pCreature);
}

CreatureAI* GetAI_boss_thaddius(Creature* pCreature)
{
    return new boss_thaddiusAI(pCreature);
}

void AddSC_boss_thaddius()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_thaddius";
    pNewScript->GetAI = &GetAI_boss_thaddius;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_stalagg";
    pNewScript->GetAI = &GetAI_boss_stalagg;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_feugen";
    pNewScript->GetAI = &GetAI_boss_feugen;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_tesla_coil";
    pNewScript->GetAI = &GetAI_npc_tesla_coil;
    pNewScript->RegisterSelf();
}