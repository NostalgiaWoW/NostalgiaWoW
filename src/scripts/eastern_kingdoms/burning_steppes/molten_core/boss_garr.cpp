/*
 *
 */

#include "scriptPCH.h"
#include "molten_core.h"

enum
{
    // Garr spells
    SPELL_ANTIMAGICPULSE        = 19492,
    SPELL_MAGMASHACKLES         = 19496,
    SPELL_ENRAGE                = 19516,                   //Stacking enrage (stacks to 10 times)

    // Add spells
    SPELL_IMMOLATE              = 15733,
    SPELL_THRASH                = 8876,
    SPELL_SEPARATION_ANXIETY    = 23492,
    SPELL_ADD_ERUPTION          = 19497,
    SPELL_MASSIVE_ERUPTION      = 20483,
    SPELL_ERUPTION_TRIGGER      = 20482,

    EMOTE_MASSIVE_ERUPTION      = -1409001
};

/*
 * Garr
 */

struct boss_garrAI : ScriptedAI
{
    explicit boss_garrAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = static_cast<ScriptedInstance*>(pCreature->GetInstanceData());

        boss_garrAI::Reset();
    }

    uint32 m_uiAntiMagicPulseTimer;
    uint32 m_uiMagmaShacklesTimer;
    uint32 m_uiCheckAddsTimer;
    uint32 m_uiExplodeTimer;
    std::list<ObjectGuid> m_lFiresworn;

    ScriptedInstance* m_pInstance;

    void Reset() override
    {
        m_uiAntiMagicPulseTimer = 15000;                       //These times are probably wrong
        m_uiMagmaShacklesTimer  = 10000;
        m_uiCheckAddsTimer      = 2000;
        m_uiExplodeTimer        = urand(2000, 4000);

        if (m_pInstance && m_creature->isAlive())
            m_pInstance->SetData(TYPE_GARR, NOT_STARTED);
    }

    void Aggro(Unit* /*pWho*/) override
    {
        if (m_pInstance)
        {
            if (m_pInstance->GetData(TYPE_GARR) != DONE)
                m_pInstance->SetData(TYPE_GARR, IN_PROGRESS);
            else
                m_creature->DeleteLater();

            m_creature->SetInCombatWithZone();

            // count chickens
            std::list<Creature*> firesworn;
            GetCreatureListWithEntryInGrid(firesworn, m_creature, NPC_FIRESWORN, 150.0f);
            m_lFiresworn.clear();

            for (auto itr = firesworn.begin(); itr != firesworn.end(); ++itr)
            {
                m_lFiresworn.push_back((*itr)->GetObjectGuid());
            }
        }
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_GARR, DONE);
    }

    void FireswornJustDied(ObjectGuid fireswornGuid)
    {
        m_lFiresworn.remove(fireswornGuid);

        std::ostringstream log;

        CanCastResult result = DoCastSpellIfCan(m_creature, SPELL_ENRAGE, CAST_TRIGGERED);

        if (result == CAST_OK)
        {
            if (auto enrageAura = m_creature->GetAura(SPELL_ENRAGE, EFFECT_INDEX_0))
            {
                auto amount = enrageAura->GetStackAmount();              
                log << "Enrage stacks: <" << amount << ">.";               
            }
        }
        else
        {
            log << "Failed to cast <Enrage> with reason <" << result << ">.";
        }

        m_creature->LogScriptInfo(log);
    }

    bool DoExplodeFiresworn() const
    {
        if (m_lFiresworn.empty())
            return false;

        auto itr = m_lFiresworn.begin();
        std::advance(itr, rand() % m_lFiresworn.size());

        if (auto pFiresworn = m_creature->GetMap()->GetCreature(*itr))
        { 
            DoScriptText(EMOTE_MASSIVE_ERUPTION, m_creature);
            m_creature->CastSpell(pFiresworn, SPELL_ERUPTION_TRIGGER, true);
            return true;
        }

        std::ostringstream log;
        log << "Unable to access Firesworn.";
        m_creature->LogScriptInfo(log);

        return false;
    }

    void UpdateAI(const uint32 diff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiAntiMagicPulseTimer < diff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_ANTIMAGICPULSE) == CAST_OK)
                m_uiAntiMagicPulseTimer = urand(5000, 10000);
        }
        else
            m_uiAntiMagicPulseTimer -= diff;

        if (m_uiMagmaShacklesTimer < diff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_MAGMASHACKLES) == CAST_OK)
                m_uiMagmaShacklesTimer = urand(6000, 10000);
        }
        else
            m_uiMagmaShacklesTimer -= diff;

        if (m_creature->GetHealthPercent() < 50.0f)
        {
            if (m_uiExplodeTimer < diff)
            {
                if (DoExplodeFiresworn())
                    m_uiExplodeTimer = urand(8000, 18000);
            }
            else
                m_uiExplodeTimer -= diff;
        }

        DoMeleeAttackIfReady();
    }
};

/*
* Firesworn
*/

struct mob_fireswornAI : ScriptedAI
{
    explicit mob_fireswornAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = static_cast<ScriptedInstance*>(pCreature->GetInstanceData());

        mob_fireswornAI::Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiAnxietyTimer;
    bool m_bForceExplosion;

    void Reset() override
    {
        m_uiAnxietyTimer = 10000;
        m_bForceExplosion = false;
    }

    void Aggro(Unit* /*pWho*/) override
    {
        DoCastSpellIfCan(m_creature, SPELL_THRASH, CAST_TRIGGERED | CAST_AURA_NOT_PRESENT);
        DoCastSpellIfCan(m_creature, SPELL_IMMOLATE, CAST_TRIGGERED | CAST_AURA_NOT_PRESENT);

        m_creature->SetInCombatWithZone();
    }

    void JustDied(Unit*) override
    {
        if (!m_pInstance)
            return;

        if (Creature* pGarr = m_pInstance->GetSingleCreatureFromStorage(NPC_GARR))
        {
            if (pGarr->isAlive())
            {
                if (auto pGarrAI = static_cast<boss_garrAI*>(pGarr->AI()))
                    pGarrAI->FireswornJustDied(m_creature->GetObjectGuid());                
            }
        }
        else
        {
            std::ostringstream log;
            log << "Failed to obtain Garr from storage.";
            m_creature->LogScriptInfo(log);
        }

        if (!m_bForceExplosion)
        {
            m_creature->CastSpell(m_creature, SPELL_ADD_ERUPTION, true);

            std::ostringstream log;
            log << "Explode by myself.";
            m_creature->LogScriptInfo(log);
        }
    }

    void SpellHit(Unit* /*pCaster*/, const SpellEntry* pSpell) override
    {
        if (pSpell->Id == SPELL_ERUPTION_TRIGGER)
        {
            std::ostringstream log;
            log << "Ordered to explode.";
            m_creature->LogScriptInfo(log);

            m_bForceExplosion = true;
            m_creature->CastSpell(m_creature, SPELL_MASSIVE_ERUPTION, true);
        }
    }

    void UpdateAI(const uint32 diff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiAnxietyTimer < diff)
        {
            if (!m_creature->HasAura(SPELL_SEPARATION_ANXIETY))
            {
                if (!m_pInstance)
                    return;

                if (Creature* pGarr = m_pInstance->GetSingleCreatureFromStorage(NPC_GARR))
                {
                    if (m_creature->GetDistance2d(pGarr) > 45.0f)
                    {
                        CanCastResult result = DoCastSpellIfCan(m_creature, SPELL_SEPARATION_ANXIETY);
                        std::ostringstream log;

                        if (result == CAST_OK)
                        {
                            m_uiAnxietyTimer = 5000;                           
                            log << "I'm in <Separation Anxiety>.";
                        }
                        else
                        {
                            log << "Failed to cast <Separation Anxiety> with reason <" << result << ">.";
                        }

                        m_creature->LogScriptInfo(log);
                    }
                }
                else
                {
                    std::ostringstream log;
                    log << "Failed to obtain Garr from storage.";
                    m_creature->LogScriptInfo(log);
                }
            }
        }
        else
            m_uiAnxietyTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_garr(Creature* pCreature)
{
    return new boss_garrAI(pCreature);
}

CreatureAI* GetAI_mob_firesworn(Creature* pCreature)
{
    return new mob_fireswornAI(pCreature);
}

void AddSC_boss_garr()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_garr";
    newscript->GetAI = &GetAI_boss_garr;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_firesworn";
    newscript->GetAI = &GetAI_mob_firesworn;
    newscript->RegisterSelf();
}
