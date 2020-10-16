#include "scriptPCH.h"
#include "stratholme.h"

#define TEXTE_PORTE_SERVICE "Intruders at the service gate! Baron Rivendare must be warned!"

#define SPELL_DRAININGBLOW      16793
#define SPELL_CROWDPUMMEL       10887
#define SPELL_MIGHTYBLOW        14099
#define SPELL_FURIOUS_ANGER     16791

#define MODEL_NORMAL            10433
#define MODEL_HUMAN             3637

static const Position MagistrateServiceGateRunOutWaypoints[] =
{
    { 3668.3f, -3607.4f, 137.2f, 0.0f },
    { 3725.5f, -3600.0f, 142.4f, 0.0f }
};

struct boss_magistrate_barthilasAI : public ScriptedAI
{
    boss_magistrate_barthilasAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 DrainingBlow_Timer;
    uint32 CrowdPummel_Timer;
    uint32 MightyBlow_Timer;
    uint32 FuriousAnger_Timer;
    uint32 AngerCount;
    bool bServiceGateEvent;
    char m_mvt_id;
    bool bMoving;

    void Reset()
    {
        DrainingBlow_Timer = 16000;
        CrowdPummel_Timer = 12000;
        MightyBlow_Timer = 8000;
        FuriousAnger_Timer = 5000;
        AngerCount = 0;
        m_mvt_id = 0;
        bMoving = false;
        bServiceGateEvent = false;

        if (m_creature->isAlive())
            m_creature->SetDisplayId(MODEL_NORMAL);
        else
            m_creature->SetDisplayId(MODEL_HUMAN);
    }

    void ReceiveEmote(Player* pPlayer, uint32 emote)
    {
        if (emote == 1000 && m_mvt_id == 0)
        {
            m_creature->MonsterYell(TEXTE_PORTE_SERVICE, LANG_UNIVERSAL);
            bServiceGateEvent = true;
        }
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (!bServiceGateEvent && who->GetTypeId() == TYPEID_PLAYER && m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE) && m_creature->IsWithinDistInMap(who, 10.0f))
        {
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
        ScriptedAI::MoveInLineOfSight(who);
    }

    void JustDied(Unit* Killer)
    {
        m_creature->SetDisplayId(MODEL_HUMAN);
    }

    void UpdateAI(const uint32 diff)
    {
        if (bServiceGateEvent)
        {
            if (bMoving) return;

            if (m_mvt_id == 2)
            {
                m_creature->NearTeleportTo(4066.3f, -3534.5f, 122.6f, 2.48137f, 0);
                bServiceGateEvent = false;
            }
            else
            {
                me->GetMotionMaster()->MovePoint(m_mvt_id,
                    MagistrateServiceGateRunOutWaypoints[m_mvt_id].x, MagistrateServiceGateRunOutWaypoints[m_mvt_id].y, MagistrateServiceGateRunOutWaypoints[m_mvt_id].z,
                    MoveOptions::MOVE_RUN_MODE, 0.0f);
                bMoving = true;
                return;
            }
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (FuriousAnger_Timer < diff)
        {
            FuriousAnger_Timer = 4000;
            if (AngerCount > 25)
                return;

            ++AngerCount;
            m_creature->CastSpell(m_creature, SPELL_FURIOUS_ANGER, false);
        }
        else FuriousAnger_Timer -= diff;

        //DrainingBlow
        if (DrainingBlow_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_DRAININGBLOW);
            DrainingBlow_Timer = 15000;
        }
        else DrainingBlow_Timer -= diff;

        //CrowdPummel
        if (CrowdPummel_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CROWDPUMMEL);
            CrowdPummel_Timer = 15000;
        }
        else CrowdPummel_Timer -= diff;

        //MightyBlow
        if (MightyBlow_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_MIGHTYBLOW);
            MightyBlow_Timer = 20000;
        }
        else MightyBlow_Timer -= diff;

        DoMeleeAttackIfReady();
    }

    virtual void MovementInform(uint32 type, uint32 id) override
    {
        m_mvt_id = id + 1;
        bMoving = false;
    }

};
CreatureAI* GetAI_boss_magistrate_barthilas(Creature* pCreature)
{
    return new boss_magistrate_barthilasAI(pCreature);
}

void AddSC_boss_magistrate_barthilas()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_magistrate_barthilas";
    newscript->GetAI = &GetAI_boss_magistrate_barthilas;
    newscript->RegisterSelf();
}
