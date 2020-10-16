#include "sw_event.h"
#include "transmog.h"

struct npc_portal_sw_eventAI : public ScriptedAI
{
    npc_portal_sw_eventAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    int m_stage;
    ObjectGuid jedi_guid;
    ObjectGuid sith_guid;
    uint32 m_mainTimer;
    uint32 m_stageTimer;

    void Reset()
    {
        m_stage = 0;
        m_stageTimer = 300 * IN_MILLISECONDS;
        m_mainTimer = 600 * IN_MILLISECONDS;
        jedi_guid.Clear();
        sith_guid.Clear();
        m_creature->SetDisplayId(MODEL_ID_PORTAL);
    }

    void stageSpawn(const uint32 uiDiff)
    {
        if (m_stageTimer <= uiDiff)
        {
            if (Creature* jedi = m_creature->SummonCreature(NPC_SW_JEDI,
                m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 0.0f,
                TEMPSUMMON_DEAD_DESPAWN, 300 * IN_MILLISECONDS))
            {
                jedi_guid = jedi->GetObjectGuid();
                jedi->AddAura(SPELL_IMMUNE);
                jedi->SetWalk(false, true);
                jedi->SetFactionTemporary(35, TEMPFACTION_NONE);
                float DestX, DestY, DestZ;
                m_creature->GetRandomPoint(m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 25.0f, DestX, DestY, DestZ);

                jedi->GetMotionMaster()->MovePoint(100, DestX, DestY, DestZ);
            }

            if (Creature* sith = m_creature->SummonCreature(NPC_SW_SITH,
                m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 0.0f,
                TEMPSUMMON_DEAD_DESPAWN, 300 * IN_MILLISECONDS))
            {
                sith_guid = sith->GetObjectGuid();
                sith->AddAura(SPELL_IMMUNE);
                sith->SetWalk(false, true);
                sith->SetFactionTemporary(35, TEMPFACTION_NONE);
                float DestX, DestY, DestZ;
                m_creature->GetRandomPoint(m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 25.0f, DestX, DestY, DestZ);

                sith->GetMotionMaster()->MovePoint(100, DestX, DestY, DestZ);
            }
            m_stageTimer = 3000;
            m_stage++;
        }
        else
            m_stageTimer -= uiDiff;
    }

    void stageBeginFight(const uint32 uiDiff)
    {
        if (m_stageTimer <= uiDiff)
        {
            if (!jedi_guid || !sith_guid)
                return;

            Creature* sith = m_creature->GetMap()->GetCreature(sith_guid);
            Creature* jedi = m_creature->GetMap()->GetCreature(jedi_guid);
            if (!sith || !jedi)
                return;

            jedi->SetFactionTemporary(FACTION_JEDI, TEMPFACTION_NONE);
            sith->SetFactionTemporary(FACTION_SITH, TEMPFACTION_NONE);
            jedi->Attack(sith, true);
            sith->GetMotionMaster()->MovePoint(101, jedi->GetPositionX(),
                jedi->GetPositionY(), jedi->GetPositionZ());
            jedi->AddThreat(sith, 100.0f);
            sith->AddThreat(jedi, 100.0f);

            m_creature->SetDisplayId(MODEL_ID_INVISIBLE);
            m_stage++;
        }
        else
            m_stageTimer -= uiDiff;
    }

    void stageEndFight(const uint32 uiDiff)
    {
        if (m_stageTimer <= uiDiff)
        {
            if (!jedi_guid || !sith_guid)
                return;

            Creature* sith = m_creature->GetMap()->GetCreature(sith_guid);
            Creature* jedi = m_creature->GetMap()->GetCreature(jedi_guid);
            if (!sith || !jedi)
                return;

            m_creature->SetDisplayId(MODEL_ID_PORTAL);

            DoScriptText(SAY_SW_EVENT_JEDI2, jedi);
            sith->RemoveAuraHolderFromStack(SPELL_IMMUNE);
            jedi->RemoveAuraHolderFromStack(SPELL_IMMUNE);
            jedi->CastSpell(sith, SPELL_STUN, true);
            jedi->AddAura(SPELL_SELF_STUN);

            m_stageTimer = 4000;
            m_stage++;
        }
        else
            m_stageTimer -= uiDiff;
    }

    void stageEscapeFight(const uint32 uiDiff)
    {
        if (m_stageTimer <= uiDiff)
        {
            if (!jedi_guid || !sith_guid)
                return;

            Creature* sith = m_creature->GetMap()->GetCreature(sith_guid);
            Creature* jedi = m_creature->GetMap()->GetCreature(jedi_guid);
            if (!sith || !jedi)
                return;

            jedi->AddAura(SPELL_IMMUNE);
            jedi->RemoveAuraHolderFromStack(SPELL_SELF_STUN);
            jedi->AddThreat(sith, 100.0f);
            jedi->GetMotionMaster()->MovePoint(102, m_creature->GetPositionX(),
                m_creature->GetPositionY(), m_creature->GetPositionZ());

            m_stageTimer = 2000;
            m_stage++;
        }
        else
            m_stageTimer -= uiDiff;
    }

    void stageEscapeFight2(const uint32 uiDiff)
    {
        if (m_stageTimer <= uiDiff)
        {
            if (!jedi_guid || !sith_guid)
                return;

            Creature* sith = m_creature->GetMap()->GetCreature(sith_guid);
            Creature* jedi = m_creature->GetMap()->GetCreature(jedi_guid);
            if (!sith || !jedi)
                return;

            DoScriptText(SAY_SW_EVENT_SITH1, sith);
            jedi->ForcedDespawn();

            m_stageTimer = 3000;
            m_stage++;
        }
        else
            m_stageTimer -= uiDiff;
    }

    void stageEscapeFight3(const uint32 uiDiff)
    {
        if (m_stageTimer <= uiDiff)
        {
            if (!sith_guid)
                return;

            if (Creature* sith = m_creature->GetMap()->GetCreature(sith_guid))
            {
                sith->AddAura(SPELL_IMMUNE);
                sith->RemoveAuraHolderFromStack(SPELL_STUN);
                sith->AttackStop();
                sith->SetFactionTemporary(35);
                sith->GetMotionMaster()->MovePoint(102, m_creature->GetPositionX(),
                    m_creature->GetPositionY(), m_creature->GetPositionZ());

                m_stageTimer = 1000;
                m_stage++;
            }
        }
        else
            m_stageTimer -= uiDiff;
    }

    void stageEndEvent(const uint32 uiDiff)
    {
        if (m_stageTimer <= uiDiff)
        {
            if (!sith_guid)
                return;

            if (Creature* sith = m_creature->GetMap()->GetCreature(sith_guid))
                sith->ForcedDespawn();

            m_creature->ForcedDespawn(5);
            m_stage++;
        }
        else
            m_stageTimer -= uiDiff;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_mainTimer <= uiDiff)
        {
            if (!jedi_guid || !sith_guid)
                return;

            Creature* sith = m_creature->GetMap()->GetCreature(sith_guid);
            Creature* jedi = m_creature->GetMap()->GetCreature(jedi_guid);
            if (!sith || !jedi)
                return;

            float DestX, DestY, DestZ;
            m_creature->GetRandomPoint(m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 15.0f, DestX, DestY, DestZ);

            if (!m_creature->FindNearestGameObject(SW_END_EVENT_GO, 90))
                m_creature->SummonGameObject(SW_END_EVENT_GO, DestX, DestY, DestZ, 0.0f);

            DoScriptText(SAY_SW_EVENT_JEDI1, jedi);
            m_mainTimer = 600 * IN_MILLISECONDS;
        }
        else
            m_mainTimer -= uiDiff;

        switch (m_stage)
        {
        case 0:
            stageSpawn(uiDiff);
            break;
        case 1:
            stageBeginFight(uiDiff);
            break;
        case 3:
            stageEndFight(uiDiff);
            break;
        case 4:
            stageEscapeFight(uiDiff);
            break;
        case 5:
            stageEscapeFight2(uiDiff);
            break;
        case 6:
            stageEscapeFight3(uiDiff);
            break;
        case 7:
            stageEndEvent(uiDiff);
            break;
        default:
            break;
        }
    }
};

bool GOHello_transmog_sw(Player* player, GameObject* go)
{
    if (go->GetEntry() != RED_SWORD_T_GO && go->GetEntry() != BLUE_SWORD_T_GO)
        return true;

    Item* itemTransmog = Item::CreateItem(go->GetEntry() == RED_SWORD_T_GO ? RED_SWORD_ID : BLUE_SWORD_ID, 1, nullptr);
    Item* itemToTransmog = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

    return sTransmog.DoTransmog(player, itemToTransmog, itemTransmog, true, false);
    go->Despawn();
    go->DestroyForNearbyPlayers();

    return true;
}

bool GOHello_end_sw_event(Player* player, GameObject* go)
{
    if (Creature* portal = player->FindNearestCreature(NPC_SW_PORTAL, 100))
        if (npc_portal_sw_eventAI* portalAI = dynamic_cast<npc_portal_sw_eventAI*>(portal->AI()))
            {
                portalAI->m_stage = 3;
                go->Despawn();
                go->DestroyForNearbyPlayers();
            }

    return true;
}

CreatureAI* GetAI_npc_portal_sw_event(Creature* pCreature)
{
    return new npc_portal_sw_eventAI(pCreature);
}

void AddSC_sw_event()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "go_transmog_sw_sword";
    newscript->pGOGossipHello = &GOHello_transmog_sw;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_end_sw_event";
    newscript->pGOGossipHello = &GOHello_end_sw_event;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "custom_portal_sw_event";
    newscript->GetAI = &GetAI_npc_portal_sw_event;
    newscript->RegisterSelf();
}
