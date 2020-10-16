/*
 * Copyright (C) 2016-2018 Elysium Core project <https://elysium-project.org/>
 * Copyright (C) 2010-2016 Anathema Script Engine project <http://valkyrie-wow.com/>
 * Copyright (C) 2006-2014 ScriptDev2 <http://www.scriptdev2.com/>
 * 
 */

#include "scriptPCH.h"
#include "quest_counterattack.h"

npc_warlord_kromzarAI::npc_warlord_kromzarAI(Creature* pCreature)
    : ScriptedAI(pCreature)
{
    m_bStarted = false;
    Reset();
}


void npc_warlord_kromzarAI::Reset()
{
    // Initial spawns n more
    if (!m_bStarted)
    {
        if (Creature* pTrigger = m_creature->SummonCreature(NPC_INVISIBLE_TRIGGER_ONE, aSummonLocations[1].m_fX, aSummonLocations[1].m_fY, aSummonLocations[1].m_fZ, aSummonLocations[1].m_fO, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 20 * MINUTE * IN_MILLISECONDS))
            m_uiTriggerOneGUID = pTrigger->GetObjectGuid();

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PASSIVE);
        m_creature->SetVisibility(VISIBILITY_OFF);

        m_lGameobjects.clear();
        m_lDefenders.clear();
        m_lKolkars.clear();
        
        m_uiHardEventTimer          = 20 * MINUTE * IN_MILLISECONDS;
        m_uiCheckResummonsTimer     = 1000;
        m_uiKillCount               = 0;
        m_uiDefenderCount           = 0;
        m_uiAttackerCount           = 0;
        m_uiSummonEntry             = 0;
        m_bInitial                  = false;
        m_bStarted                  = true;
    }

    m_uiTorchTimer = 7500;
    m_uiStrikeTimer = urand(5000, 10000);
}

#define GO_FLAG 164690

void npc_warlord_kromzarAI::JustDied(Unit* pKiller)
{
    //DoCastSpellIfCan(m_creature, SPELL_KROMZAR_BANNER, CAST_INTERRUPT_PREVIOUS);
    GameObject* BannerGO = m_creature->SummonGameObject(GO_FLAG, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 25000, false);
    BannerGO->SetGoState(GO_STATE_READY);

    if (m_creature->IsTemporarySummon())
        if (Unit* pSummoner = m_creature->GetMap()->GetUnit(((TemporarySummon*)m_creature)->GetSummonerGuid()))
            DoScriptText(SAY_EVENT_END, pSummoner);

    EndEvent();
}

void npc_warlord_kromzarAI::JustSummoned(Creature* pSummoned)
{
    switch (pSummoned->GetEntry())
    {
    case NPC_KOLKAR_INVADER:
    case NPC_KOLKAR_STORMSEER:
        m_lKolkars.push_back(pSummoned->GetObjectGuid());
        break;
    case NPC_HORDE_AXE_THROWER:
        if (urand(0, 1) == 1)
        {
            switch (urand(0, 2))
            {
            case 0:
                DoScriptText(SAY_DEFEND_BUNKERS, pSummoned);
                break;
            case 1:
                DoScriptText(SAY_FOES_FALL, pSummoned);
                break;
            case 2:
                DoScriptText(SAY_FOR_THE_HORDE, pSummoned);
                break;
            }
        }
    case NPC_HORDE_DEFENDER:
        m_lDefenders.push_back(pSummoned->GetObjectGuid());
        break;
    }
}

void npc_warlord_kromzarAI::JustSummoned(GameObject* pSummoned)
{
    if (pSummoned->GetEntry() == GO_FLAG) return;

    m_lGameobjects.push_back(pSummoned->GetObjectGuid());
}

void npc_warlord_kromzarAI::SummonedCreatureJustDied(Creature* pSummoned)
{
    switch (pSummoned->GetEntry())
    {
    case NPC_HORDE_DEFENDER:
    case NPC_HORDE_AXE_THROWER:
        if (m_creature->IsTemporarySummon())
            if (Unit* pSummoner = m_creature->GetMap()->GetUnit(((TemporarySummon*)m_creature)->GetSummonerGuid()))
                DoScriptText(SAY_DEFENDER_FALLEN, pSummoner);

        --m_uiDefenderCount;
        m_lDefenders.remove(pSummoned->GetObjectGuid());
        pSummoned->ForcedDespawn(15000);
        break;
    case NPC_KOLKAR_INVADER:
    case NPC_KOLKAR_STORMSEER:
        // Inc killcount
        ++m_uiKillCount;
        --m_uiAttackerCount;

        // Remove from list
        m_lKolkars.remove(pSummoned->GetObjectGuid());

        TryJoinFight();
        break;
    }
}

void npc_warlord_kromzarAI::SummonedMovementInform(Creature* pSummoned, uint32 uiMotionType, uint32 uiPointId)
{
    if (uiMotionType == POINT_MOTION_TYPE)
        if (uiPointId == 1)
            pSummoned->CastSpell(pSummoned, SPELL_FLING_TORCH, false);
}

void npc_warlord_kromzarAI::SummonGameobjects()
{
    for(uint32 i = 0; i < 5; ++i)
        m_creature->SummonGameObject(GO_SMOKE_EMITTER, aGOSummonLocations[i].m_fX, aGOSummonLocations[i].m_fY, aGOSummonLocations[i].m_fZ, aGOSummonLocations[i].m_fO, 0.0f, 0.0f, 0.0f, 0.0f, 20 * MINUTE * IN_MILLISECONDS);

    m_creature->SummonGameObject(GO_BIG_FLAME, -340.0f, -1896.0f, 103.064f, 0.14f, 0.0f, 0.0f, 0.0f, 0.0f, 20 * MINUTE * IN_MILLISECONDS);

    for(uint32 i = 5; i < 9; ++i)
        m_creature->SummonGameObject(GO_SMALL_FLAME, aGOSummonLocations[i].m_fX, aGOSummonLocations[i].m_fY, aGOSummonLocations[i].m_fZ, aGOSummonLocations[i].m_fO, 0.0f, 0.0f, 0.0f, 0.0f, 20 * MINUTE * IN_MILLISECONDS);
}

void npc_warlord_kromzarAI::SummonDefenders()
{
    while (m_uiDefenderCount < MAX_DEFENDERS)
    {
        switch (urand(0, 3))
        {
            case 0:
                m_uiSummonEntry = NPC_HORDE_AXE_THROWER;
                break;
            default:
                m_uiSummonEntry = NPC_HORDE_DEFENDER;
                break;
        }
        float fX, fY, fZ;
        m_creature->GetRandomPoint(aSummonLocations[4].m_fX, aSummonLocations[4].m_fY, aSummonLocations[4].m_fZ, MAX_SPAWNRANGE_DEFENDERS, fX, fY, fZ);
        m_creature->SummonCreature(m_uiSummonEntry, fX, fY, fZ, 1.75f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 20 * MINUTE * IN_MILLISECONDS);
        ++m_uiDefenderCount;
    }
}

void npc_warlord_kromzarAI::SummonAttackers()
{
    while (m_uiAttackerCount < MAX_ATTACKERS)
    {
        switch (urand(0, 3))
        {
            case 0:
                m_uiSummonEntry = NPC_KOLKAR_STORMSEER;
                break;
            default:
                m_uiSummonEntry = NPC_KOLKAR_INVADER;
                break;
        }

        float fX, fY, fZ;
        m_creature->GetRandomPoint(aSummonLocations[3].m_fX, aSummonLocations[3].m_fY, aSummonLocations[3].m_fZ, MAX_SPAWNRANGE_ATTACKERS, fX, fY, fZ);
        m_creature->SummonCreature(m_uiSummonEntry, fX, fY, fZ, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 20 * MINUTE * IN_MILLISECONDS);
        ++m_uiAttackerCount;
    }
}

void npc_warlord_kromzarAI::TryJoinFight()
{
    // Time to join the fight?
    if (m_creature->GetVisibility() == VISIBILITY_OFF)
    {
        if (m_uiKillCount >= 20)
        {
            m_creature->NearTeleportTo(aSummonLocations[0].m_fX, aSummonLocations[0].m_fY, aSummonLocations[0].m_fZ, aSummonLocations[0].m_fO);

            DoScriptText(SAY_SPAWN, m_creature);

            if (Creature* pInvader = m_creature->SummonCreature(NPC_KOLKAR_INVADER, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 20 * MINUTE * IN_MILLISECONDS))
            {
                pInvader->GetMotionMaster()->Clear();
                pInvader->GetMotionMaster()->MoveFollow(m_creature, 3.0f, 1.57f);
            }

            if (Creature* pStormseer = m_creature->SummonCreature(NPC_KOLKAR_STORMSEER, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 20 * MINUTE * IN_MILLISECONDS))
            {
                pStormseer->GetMotionMaster()->Clear();
                pStormseer->GetMotionMaster()->MoveFollow(m_creature, 3.0f, -1.57f);
            }

            m_creature->SetWalk(false);
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MovePoint(0, aSummonLocations[2].m_fX, aSummonLocations[2].m_fY, aSummonLocations[2].m_fZ);

            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PASSIVE);
            m_creature->SetVisibility(VISIBILITY_ON);
            m_uiKillCount = 0;
        }
    }
}

void npc_warlord_kromzarAI::EndEvent()
{
    if (Creature* pLanti = GetClosestCreatureWithEntry(m_creature, NPC_LANTI_GAH, 150.0))
    {
        pLanti->setFaction(29);
        pLanti->GetMotionMaster()->Clear();
        pLanti->GetMotionMaster()->MoveTargetedHome();
        pLanti->HandleEmote(EMOTE_STATE_NONE);
    }

    // Remove GOs
    for (GuidList::const_iterator itr = m_lGameobjects.begin(); itr != m_lGameobjects.end(); ++itr)
    {
        if (GameObject* pTemp = m_creature->GetMap()->GetGameObject(*itr))
            pTemp->Delete();
    }
    m_lGameobjects.clear();

    // Remove Defenders
    for (GuidList::const_iterator itr = m_lDefenders.begin(); itr != m_lDefenders.end(); ++itr)
    {
        if (Creature* pTemp = m_creature->GetMap()->GetCreature(*itr))
            if (!pTemp->isInCombat())
                pTemp->ForcedDespawn();
            else
                pTemp->ForcedDespawn(60 * IN_MILLISECONDS);
    }
    m_lDefenders.clear();

    // Remove Attackers
    for (GuidList::const_iterator itr = m_lKolkars.begin(); itr != m_lKolkars.end(); ++itr)
    {
        if (Creature* pTemp = m_creature->GetMap()->GetCreature(*itr))
            if (!pTemp->isInCombat())
                pTemp->ForcedDespawn();
            else
                pTemp->ForcedDespawn(60 * IN_MILLISECONDS);
    }
    m_lKolkars.clear();

    // Despawn the trigger npc so event can be started again
    if (Creature* pTriggerOne = m_creature->GetMap()->GetCreature(m_uiTriggerOneGUID))
        pTriggerOne->ForcedDespawn(5000);

    m_creature->ForcedDespawn(3 * MINUTE * IN_MILLISECONDS);
}

void npc_warlord_kromzarAI::UpdateAI(const uint32 diff)
{
    // Hard event timer
    if (m_uiHardEventTimer < diff)
        EndEvent();
    else 
        m_uiHardEventTimer -= diff;

    // Check resummons timer
    if (m_uiCheckResummonsTimer < diff)
    {
        if (!m_bInitial)
        {
            SummonGameobjects();

            if (Creature* pLanti = GetClosestCreatureWithEntry(m_creature, NPC_LANTI_GAH, MAX_VISIBILITY_DISTANCE))
            {
                pLanti->setFaction(35);
                pLanti->SetWalk(false);
                pLanti->GetMotionMaster()->Clear();
                pLanti->GetMotionMaster()->MovePoint(0, aSummonLocations[5].m_fX, aSummonLocations[5].m_fY, aSummonLocations[5].m_fZ);
                pLanti->HandleEmote(EMOTE_STATE_WORK_MINING);
            }

            m_bInitial = true;
        }

        SummonDefenders();
        SummonAttackers();
        m_uiCheckResummonsTimer = 15000;
    }
    else 
        m_uiCheckResummonsTimer -= diff;

    // Fling torch timer
    if (m_uiTorchTimer < diff)
    {
        std::vector<Creature*> vKolkars;
        vKolkars.reserve(m_lKolkars.size());

        for (GuidList::const_iterator itr = m_lKolkars.begin(); itr != m_lKolkars.end(); ++itr)
        {
            if (Creature* pTemp = m_creature->GetMap()->GetCreature(*itr))
                if (!pTemp->isInCombat())
                    vKolkars.push_back(pTemp);
        }

        if (!vKolkars.empty())
        {
            Creature* pKolkar = vKolkars[urand(0, vKolkars.size() - 1)];

            if (pKolkar)
            {
                uint8 uiPoint = 6 + urand(0, 1);
                pKolkar->SetWalk(false);
                pKolkar->GetMotionMaster()->Clear();
                pKolkar->GetMotionMaster()->MovePoint(1, aSummonLocations[uiPoint].m_fX, aSummonLocations[uiPoint].m_fY, aSummonLocations[uiPoint].m_fZ);
                m_uiTorchTimer = 7500;
            }
            vKolkars.clear();
        }
    }
    else 
        m_uiTorchTimer -= diff;

    TryJoinFight();

    if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        return;

    // Strike
    if (m_uiStrikeTimer < diff)
    {
        if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_STRIKE) == CAST_OK)
            m_uiStrikeTimer = urand(8000, 12000);
    } 
    else 
        m_uiStrikeTimer -= diff;

    DoMeleeAttackIfReady();
}

CreatureAI* GetAI_npc_warlord_kromzar(Creature* pCreature)
{
    return new npc_warlord_kromzarAI(pCreature);
}

/*######
## npc_regthar_deathgate
######*/

bool GossipHello_npc_regthar_deathgate(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(QUEST_COUNTERATTACK) == QUEST_STATUS_INCOMPLETE)
        if (!GetClosestCreatureWithEntry(pCreature, NPC_INVISIBLE_TRIGGER_ONE, 50.0f))
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_REGTHAR, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_regthar_deathgate(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    pPlayer->SEND_GOSSIP_MENU(2534, pCreature->GetObjectGuid());

    DoScriptText(SAY_EVENT_START, pCreature, pPlayer);

    pCreature->SummonCreature(NPC_WARLORD_KROMZAR, aSummonLocations[2].m_fX, aSummonLocations[2].m_fY, aSummonLocations[2].m_fZ, aSummonLocations[2].m_fO, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3 * MINUTE * IN_MILLISECONDS, true);

    return true;
}

void AddSC_quest_counterattack()
{
    Script *pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_regthar_deathgate";
    pNewScript->pGossipHello =  &GossipHello_npc_regthar_deathgate;
    pNewScript->pGossipSelect = &GossipSelect_npc_regthar_deathgate;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_warlord_kromzar";
    pNewScript->GetAI = &GetAI_npc_warlord_kromzar;
    pNewScript->RegisterSelf();
}
