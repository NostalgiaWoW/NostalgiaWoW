
#include "scriptPCH.h"
enum
{
    SPELL_SHADOW_VOLLEY = 27382,
    SPELL_ZOMBIE_FORM = 7293,
    SPELL_SHADOW_WRATH = 27286,
    SPELL_DEMONIC_TRANSFORMATION = 24992,
    SPELL_CURSE_OF_BLOOD = 24673,
    SPELL_CURSE_OF_TONGUES = 25195,
    SPELL_DARK_GLARE = 26029,
    SPELL_DARK_CHANNELING = 21157,
    SPELL_VOID_BLAST = 27812,
    SPELL_STUN = 27880,
    SPELL_DEATH_TOUCH = 5,
    SPELL_PAL_DIVINE_INTERVENTION_EFFECT = 19753,
    SPELL_ENRAGE = 28798,

    NPC_RELEASED_DEMON = 1000555,
    NPC_UNRELEASED_DEMON = 1000554,

    SAY_REJECTED_GIFT = -1999933,
    SAY_REJECTED_GIFT2 = -1999934,
    SAY_TAKE_GIFT = -1999835,
    SAY_TAKE_GIFT2 = -1999836,
    SAY_GO_AWAY = -1999937,
    SAY_RELEASED_DEMON = -1999938,
    SAY_RELEASED_DEMON2 = -1999939,
    SAY_LIKE_DEMON = -1999840,
    SAY_LIKE_DEMON2 = -1999841,
    SAY_SHADOWSTORM = -1999842,
    SAY_SHADOWSTORM2 = -1999943,
    SAY_SO_MANY_SOULS = -1999944,
    SAY_SO_MANY_SOULS2 = -1999945,
    ITEM_BLOOD_OF_RAGTHERADON = 600004,
    ITEM_POTION = 23123,
    ITEM_POTION2 = 23122
};

struct boss_halloween_zombieAI : public ScriptedAI
{
    boss_halloween_zombieAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 CTongue_Timer;
    uint32 CBlood_Timer;
    uint32 ZombieForm_Timer;
    uint32 UnreleasedDemon_Timer;
    uint32 ReleasedDemon_Timer;
    uint32 ShadowStorm_Timer;
    uint32 ShadowRage_Timer;
    bool ShadowStorm;
    ObjectGuid previousTarget;
    std::list<Player*> demonPlayers;
    std::vector<uint32> lootItems;

	void Reset()
	{
		ZombieForm_Timer = 7000;
		UnreleasedDemon_Timer = 8000;
		CTongue_Timer = 10000;
		CBlood_Timer = 11000;
		ShadowStorm_Timer = 15000;
		ShadowRage_Timer = 20000;
		ReleasedDemon_Timer = urand(9, 16) * IN_MILLISECONDS;
		m_creature->RemoveAurasDueToSpell(SPELL_SHADOW_VOLLEY);
		m_creature->RemoveAurasDueToSpell(SPELL_ENRAGE);
		ShadowStorm = false;
		previousTarget = 0;
		demonPlayers.clear();
	}


    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (ZombieForm_Timer < diff)
        {
            DoDemonForm();
            ZombieForm_Timer = 7000;
        }
        else
            ZombieForm_Timer -= diff;

        if (UnreleasedDemon_Timer < diff)
        {
            DoUnreleasedDemon();
            UnreleasedDemon_Timer = 8000;
        }
        else
            UnreleasedDemon_Timer -= diff;

        if (CTongue_Timer < diff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CURSE_OF_TONGUES) == CAST_OK)
                CTongue_Timer = 10000;
        }
        else
            CTongue_Timer -= diff;

        if (CBlood_Timer < diff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CURSE_OF_BLOOD) == CAST_OK)
                CBlood_Timer = 11000;
        }
        else
            CBlood_Timer -= diff;

        if (ReleasedDemon_Timer < diff)
        {
            DoReleasedDemon();
            ReleasedDemon_Timer = urand(6, 13) * IN_MILLISECONDS;
        }
        else
            ReleasedDemon_Timer -= diff;

        if (ShadowStorm_Timer < diff)
        {
            if (m_creature->GetHealthPercent() < 50)
            {
                if (ShadowStorm)
                {
                    m_creature->RemoveAurasDueToSpell(SPELL_SHADOW_VOLLEY);
                    ShadowStorm = false;
                }
                else
                {
                    DoScriptText(urand(SAY_SHADOWSTORM2, SAY_SHADOWSTORM), m_creature);
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHADOW_VOLLEY, CAST_TRIGGERED);
                    ShadowStorm = true;
                }
            }
            ShadowStorm_Timer = 10000;
        }
        else
            ShadowStorm_Timer -= diff;

        if (ShadowRage_Timer < diff)
        {
            ThreatList const& tList = m_creature->getThreatManager().getThreatList();

            if (m_creature->GetHealthPercent() < 25 && tList.size() > 30)
            {

                if (!m_creature->HasAura(SPELL_ENRAGE))
                    DoCastSpellIfCan(m_creature, SPELL_ENRAGE, CAST_TRIGGERED);

                DoScriptText(urand(SAY_SO_MANY_SOULS2, SAY_SO_MANY_SOULS), m_creature);
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHADOW_WRATH, CAST_TRIGGERED);
            }
            ShadowRage_Timer = 18000;
        }
        else
            ShadowRage_Timer -= diff;

        DoMeleeAttackIfReady();
    }

    void DoReleasedDemon()
    {
        if (demonPlayers.empty())
            return;

        bool released = false;

        ObjectGuid m_creatureGuid = m_creature->GetObjectGuid();
        ObjectGuid m_previousTarget = previousTarget;

        std::list<Player*> targetPlayers;
        ThreatList tList = m_creature->getThreatManager().getThreatList();
        for (ThreatList::const_iterator iter = tList.begin(); iter != tList.end(); ++iter)
        {
            if (!(*iter)->getUnitGuid().IsPlayer())
                continue;

            if (Unit * pTempTarget = m_creature->GetMap()->GetUnit((*iter)->getUnitGuid()))
            {
                if (m_creature->GetDistance2d(m_creature->GetPositionX(), m_creature->GetPositionY()) > 35.0f || m_creature->GetObjectGuid() == m_previousTarget)
                    continue;

                targetPlayers.push_back(pTempTarget->ToPlayer());
            }
        }

        demonPlayers.remove_if([m_creatureGuid, m_previousTarget](Player* p) -> bool
        {
            Unit* c = sObjectAccessor.GetUnit(*p, m_creatureGuid);
            if (!c)
                return true;

            if (p && p->isAlive())
            {
                if (!p->HasAura(SPELL_ZOMBIE_FORM) && c->GetDistance2d(p->GetPositionX(), p->GetPositionY()) > 35.0f)
                    return true;

                return false;
            }

            return true;
        });

        for (auto p : demonPlayers)
        {
            if (p->HasAura(SPELL_ZOMBIE_FORM))
            {
                if (p->HasAura(SPELL_PAL_DIVINE_INTERVENTION_EFFECT) || m_creature->GetDistance2d(p->GetPositionX(), p->GetPositionY()) > 35.0f)
                    continue;

                if (p->GetObjectGuid() != m_previousTarget && !released)
                {
                    DoScriptText(urand(SAY_RELEASED_DEMON2, SAY_RELEASED_DEMON), m_creature, p);
                    float ori = p->GetOrientation();
                    Player* tPlayer = nullptr;
                    if (targetPlayers.size() > 1)
                    {
                        uint32 step = 0;
                        uint32 targetNum = urand(0, targetPlayers.size());
                        for (auto tPlayer : targetPlayers)
                        {
                            if (step == targetNum)
                            {
                                p->AttackStop();
                                ori = p->GetAngle(tPlayer);
                                p->SetFacingToObject(tPlayer);
                                break;
                            }
                            step++;
                        }
                    }

                    if (Creature * trigger = m_creature->SummonCreature(NPC_RELEASED_DEMON, p->GetPositionX(), p->GetPositionY(), p->GetPositionZ(), ori,
                        TEMPSUMMON_TIMED_DESPAWN, 2000))
                    {
                        p->AddAura(SPELL_STUN);
                        trigger->SetReactState(REACT_PASSIVE);
                        trigger->CastSpell(trigger, SPELL_DARK_GLARE, false);
                        DoCastSpellIfCan(p, SPELL_ZOMBIE_FORM, CAST_TRIGGERED);
                        previousTarget = p->GetObjectGuid();
                        released = true;
                        DoScriptText(urand(SAY_LIKE_DEMON2, SAY_LIKE_DEMON), m_creature, p);
                    }
                }
                DoCastSpellIfCan(p, SPELL_ZOMBIE_FORM, CAST_TRIGGERED);
            }
        }
    }

    void DoDemonForm()
    {
        Player* pTarget = nullptr;

        ThreatList tList = m_creature->getThreatManager().getThreatList();
        for (ThreatList::const_iterator iter = tList.begin(); iter != tList.end(); ++iter)
        {
            if (!(*iter)->getUnitGuid().IsPlayer())
            {
                if (!(*iter)->getUnitGuid().IsPet())
                    if (Unit * npcTarget = m_creature->GetMap()->GetUnit((*iter)->getUnitGuid()))
                        m_creature->DoKillUnit(npcTarget);

                continue;
            }

            if (Unit * pTempTarget = m_creature->GetMap()->GetUnit((*iter)->getUnitGuid()))
            {
                if (pTempTarget->HasAura(SPELL_PAL_DIVINE_INTERVENTION_EFFECT) || pTempTarget->HasAura(SPELL_ZOMBIE_FORM))
                    continue;

                pTarget = pTempTarget->ToPlayer();
            }
        }

        if (pTarget)
        {
            WorldLocation loc;
            m_creature->GetPosition(loc);
            loc.coord_x;
            loc.coord_y;
            loc.coord_z += 0.5f;
            loc.orientation;
            pTarget->TeleportTo(loc);
            DoScriptText(urand(SAY_TAKE_GIFT2, SAY_TAKE_GIFT), m_creature, pTarget);
            DoCastSpellIfCan(pTarget, SPELL_ZOMBIE_FORM, CAST_TRIGGERED);
            demonPlayers.push_back(pTarget);
        }
    }

    void DoUnreleasedDemon()
    {
        if (demonPlayers.empty())
            return;

        ObjectGuid m_creatureGuid = m_creature->GetObjectGuid();

        demonPlayers.remove_if([m_creatureGuid](Player* p) -> bool
        {
            Unit* c = sObjectAccessor.GetUnit(*p, m_creatureGuid);
            if (!c)
                return true;

            if (p && p->isAlive())
            {
                if (!p->HasAura(SPELL_ZOMBIE_FORM) && c->GetDistance2d(p->GetPositionX(), p->GetPositionY()) > 35.0f)
                    return true;

                return false;
            }

            return true;
        });

        for (auto p : demonPlayers)
        {
            if (p->HasAura(SPELL_PAL_DIVINE_INTERVENTION_EFFECT) || p->HasAura(SPELL_ZOMBIE_FORM))
                continue;

            if (Creature* trigger = m_creature->SummonCreature(NPC_UNRELEASED_DEMON, p->GetPositionX(), p->GetPositionY(), p->GetPositionZ(),
                p->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 2000))
            {
                p->AddAura(SPELL_STUN);
                DoScriptText(urand(SAY_REJECTED_GIFT2, SAY_REJECTED_GIFT), m_creature, p);
                trigger->SetReactState(REACT_PASSIVE);
                trigger->CastSpell(trigger, SPELL_VOID_BLAST, false);
                DoCastSpellIfCan(p, SPELL_DEATH_TOUCH, CAST_TRIGGERED);
                demonPlayers.remove(p);
                break;
            }
        }
    }
};


CreatureAI* GetAI_boss_halloween_zombie(Creature* pCreature)
{
    return new boss_halloween_zombieAI(pCreature);
}

void AddSC_boss_halloween_zombie()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_halloween_zombie";
    newscript->GetAI = &GetAI_boss_halloween_zombie;
    newscript->RegisterSelf();
};

