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

/* ScriptData
SDName: The_Barrens
SD%Complete: 90
SDComment: Quest support: 863, 898, 1719, 2458, 4921, 6981
SDCategory: Barrens
EndScriptData */

/* ContentData
npc_beaten_corpse
npc_gilthares
npc_taskmaster_fizzule
npc_twiggy_flathead
at_twiggy_flathead
npc_wizzlecrank_shredder
EndContentData */

#include "scriptPCH.h"

/*######
## npc_beaten_corpse
######*/

enum
{
    QUEST_LOST_IN_BATTLE    = 4921
};

bool GossipHello_npc_beaten_corpse(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_LOST_IN_BATTLE) == QUEST_STATUS_INCOMPLETE ||
            pPlayer->GetQuestStatus(QUEST_LOST_IN_BATTLE) == QUEST_STATUS_COMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Examine corpse in detail...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    pPlayer->SEND_GOSSIP_MENU(3557, pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_beaten_corpse(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->SEND_GOSSIP_MENU(3558, pCreature->GetGUID());
        pPlayer->TalkedToCreature(pCreature->GetEntry(), pCreature->GetGUID());
    }
    return true;
}
bool GossipHello_npc_Gizmotronic(Player* pPlayer, Creature* pCreature)
{
    if ((pPlayer->GetQuestStatus(2381) == QUEST_STATUS_INCOMPLETE))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,
                                 "Give me what I need stupid machine !",
                                 GOSSIP_SENDER_MAIN,
                                 GOSSIP_ACTION_INFO_DEF + 10);
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature),
                                  pCreature->GetObjectGuid());
    }
    return true;
}

bool GossipSelect_npc_Gizmotronic(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction >= GOSSIP_ACTION_INFO_DEF + 10)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        if (!pPlayer->HasItemCount(5060, 1, true))
        {
            uint32 noSpaceForCount = 0;
            ItemPosCountVec dest;
            uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT,
                                                 dest, 5060, 1, &noSpaceForCount);

            if (msg == EQUIP_ERR_OK)
            {
                Item* pItem = pPlayer->StoreNewItem(dest, 5060,
                                                    true, Item::GenerateItemRandomPropertyId(5060));
                pPlayer->SendNewItem(pItem, 1, true, false);
            }
        }
        if (!pPlayer->HasItemCount(7970, 1, true))
        {
            uint32 noSpaceForCount = 0;
            ItemPosCountVec dest;
            uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT,
                                                 dest, 7970, 1, &noSpaceForCount);
            if (msg == EQUIP_ERR_OK)
            {
                Item* pItem = pPlayer->StoreNewItem(dest, 7970,
                                                    true, Item::GenerateItemRandomPropertyId(7970));
                pPlayer->SendNewItem(pItem, 1, true, false);
            }
        }
    }
    return true;
}

struct npc_pollyAI : public ScriptedAI
{
    npc_pollyAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    bool b_text;

    void Reset()
    {
        b_text = false;
    }

    void Aggro(Unit* pWho)
    {
        if (b_text == false)
        {
            m_creature->MonsterSay("MmmmmMmmmm... Enormous chemically altered cracker...", 0, 0);
            m_creature->MonsterSay("What the squawk? Squawk squawk, squawk? SQUAWK!", 0, 0);
            b_text = true;
        }
    }
};

CreatureAI* GetAI_npc_polly(Creature* pCreature)
{
    return new npc_pollyAI(pCreature);
}


/*######
# npc_gilthares
######*/

enum
{
    SAY_GIL_START               = -1000370,
    SAY_GIL_AT_LAST             = -1000371,
    SAY_GIL_PROCEED             = -1000372,
    SAY_GIL_FREEBOOTERS         = -1000373,
    SAY_GIL_AGGRO_1             = -1000374,
    SAY_GIL_AGGRO_2             = -1000375,
    SAY_GIL_AGGRO_3             = -1000376,
    SAY_GIL_AGGRO_4             = -1000377,
    SAY_GIL_ALMOST              = -1000378,
    SAY_GIL_SWEET               = -1000379,
    SAY_GIL_FREED               = -1000380,

    QUEST_FREE_FROM_HOLD        = 898,
    AREA_MERCHANT_COAST         = 391
};

struct npc_giltharesAI : public npc_escortAI
{
    npc_giltharesAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        Reset();
    }

    void Reset() { }

    void WaypointReached(uint32 uiPointId)
    {
        Player* pPlayer = GetPlayerForEscort();

        if (!pPlayer)
            return;

        switch (uiPointId)
        {
            case 16:
                DoScriptText(SAY_GIL_AT_LAST, m_creature, pPlayer);
                break;
            case 17:
                DoScriptText(SAY_GIL_PROCEED, m_creature, pPlayer);
                break;
            case 18:
                DoScriptText(SAY_GIL_FREEBOOTERS, m_creature, pPlayer);
                break;
            case 37:
                DoScriptText(SAY_GIL_ALMOST, m_creature, pPlayer);
                break;
            case 47:
                DoScriptText(SAY_GIL_SWEET, m_creature, pPlayer);
                break;
            case 53:
                DoScriptText(SAY_GIL_FREED, m_creature, pPlayer);
                pPlayer->GroupEventHappens(QUEST_FREE_FROM_HOLD, m_creature);
                break;
        }
    }

    void Aggro(Unit* pWho)
    {
        //not always use
        if (urand(0, 3))
            return;

        //only aggro text if not player and only in this area
        if (pWho->GetTypeId() != TYPEID_PLAYER && m_creature->GetAreaId() == AREA_MERCHANT_COAST)
        {
            //appears to be pretty much random (possible only if escorter not in combat with pWho yet?)
            switch (urand(0, 3))
            {
                case 0:
                    DoScriptText(SAY_GIL_AGGRO_1, m_creature, pWho);
                    break;
                case 1:
                    DoScriptText(SAY_GIL_AGGRO_2, m_creature, pWho);
                    break;
                case 2:
                    DoScriptText(SAY_GIL_AGGRO_3, m_creature, pWho);
                    break;
                case 3:
                    DoScriptText(SAY_GIL_AGGRO_4, m_creature, pWho);
                    break;
            }
        }
    }
};

CreatureAI* GetAI_npc_gilthares(Creature* pCreature)
{
    return new npc_giltharesAI(pCreature);
}

bool QuestAccept_npc_gilthares(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_FREE_FROM_HOLD)
    {
        pCreature->setFaction(FACTION_ESCORT_H_NEUTRAL_ACTIVE);
        pCreature->SetStandState(UNIT_STAND_STATE_STAND);

        DoScriptText(SAY_GIL_START, pCreature, pPlayer);

        if (npc_giltharesAI* pEscortAI = dynamic_cast<npc_giltharesAI*>(pCreature->AI()))
            pEscortAI->Start(false, pPlayer->GetGUID(), pQuest);
    }
    return true;
}

/*######
## npc_taskmaster_fizzule
######*/

enum
{
    FACTION_FRIENDLY_F  = 35,
    SPELL_FLARE         = 10113,
    SPELL_FOLLY         = 10137,
};

struct npc_taskmaster_fizzuleAI : public ScriptedAI
{
    npc_taskmaster_fizzuleAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        factionNorm = pCreature->getFaction();
        Reset();
    }

    uint32 factionNorm;
    bool IsFriend;
    uint32 Reset_Timer;
    uint8 FlareCount;

    void Reset()
    {
        IsFriend = false;
        Reset_Timer = 120000;
        FlareCount = 0;
        m_creature->setFaction(factionNorm);
    }

    void DoFriend()
    {
        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        m_creature->CombatStop(true);

        m_creature->StopMoving();
        m_creature->GetMotionMaster()->MoveIdle();

        m_creature->setFaction(FACTION_FRIENDLY_F);
        m_creature->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
    }

    void SpellHit(Unit *caster, const SpellEntry *spell)
    {
        if (spell->Id == SPELL_FLARE || spell->Id == SPELL_FOLLY)
        {
            ++FlareCount;

            if (FlareCount >= 2)
                IsFriend = true;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (IsFriend)
        {
            if (Reset_Timer < diff)
                EnterEvadeMode();
            else Reset_Timer -= diff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }

    void ReceiveEmote(Player* pPlayer, uint32 emote)
    {
        if (emote == TEXTEMOTE_SALUTE)
        {
            if (FlareCount >= 2)
            {
                if (m_creature->getFaction() == FACTION_FRIENDLY_F)
                    return;

                DoFriend();
            }
        }
    }
};

CreatureAI* GetAI_npc_taskmaster_fizzule(Creature* pCreature)
{
    return new npc_taskmaster_fizzuleAI(pCreature);
}

/*#####
## npc_twiggy_flathead
#####*/

#define SAY_BIG_WILL_READY                  -1000123
#define SAY_TWIGGY_BEGIN                    -1000124
#define SAY_TWIGGY_FRAY                     -1000125
#define SAY_TWIGGY_DOWN                     -1000126
#define SAY_TWIGGY_OVER                     -1000127

#define NPC_TWIGGY                          6248
#define NPC_BIG_WILL                        6238
#define NPC_AFFRAY_CHALLENGER               6240
#define NPC_AFFRAY_SPECTATOR                6249
#define QUEST_AFFRAY                        1719

float AffrayChallengerLoc[6][4] =
{
    { -1683.0f, -4326.0f, 2.79f, 0.00f},
    { -1682.0f, -4329.0f, 2.79f, 0.00f},
    { -1683.0f, -4330.0f, 2.79f, 0.00f},
    { -1680.0f, -4334.0f, 2.79f, 1.49f},
    { -1674.0f, -4326.0f, 2.79f, 3.49f},
    { -1677.0f, -4334.0f, 2.79f, 1.66f}
};

struct npc_twiggy_flatheadAI : public ScriptedAI
{
    npc_twiggy_flatheadAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    bool EventInProgress;

    uint32 Event_Timer;
    uint32 Step;
    uint32 Challenger_Count;
    uint32 ChallengerDeath_Timer;
    uint32 Emote_Timer;

    uint64 PlayerGUID;
    uint64 BigWillGUID;
    uint64 AffrayChallenger[6];

    void Reset()
    {
        EventInProgress = false;

        Event_Timer = 2000;
        Emote_Timer = 1000;
        Step = 0;
        Challenger_Count = 0;
        ChallengerDeath_Timer = 0;

        PlayerGUID = 0;
        BigWillGUID = 0;

        for (uint8 i = 0; i < 6; ++i)
            AffrayChallenger[i] = 0;
    }

    bool CanStartEvent(Player* pPlayer)
    {
        if (!EventInProgress)
        {
            EventInProgress = true;
            PlayerGUID = pPlayer->GetGUID();
            DoScriptText(SAY_TWIGGY_BEGIN, m_creature, pPlayer);
            return true;
        }

        sLog.outDebug("npc_twiggy_flathead event already in progress, need to wait.");
        return false;
    }

    void SetChallengers()
    {
        for (uint8 i = 0; i < 6; ++i)
        {
            Creature* pCreature = m_creature->SummonCreature(NPC_AFFRAY_CHALLENGER, AffrayChallengerLoc[i][0], AffrayChallengerLoc[i][1], AffrayChallengerLoc[i][2], AffrayChallengerLoc[i][3], TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 600000);
            if (!pCreature)
            {
                sLog.outDebug("npc_twiggy_flathead event cannot summon challenger as expected.");
                continue;
            }

            pCreature->setFaction(35);
            pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            pCreature->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
            AffrayChallenger[i] = pCreature->GetGUID();
        }
    }

    void SetChallengerReady(Unit *pUnit)
    {
        pUnit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        pUnit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        pUnit->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
        pUnit->setFaction(14);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!EventInProgress)
            return;

        if (ChallengerDeath_Timer)
        {
            if (ChallengerDeath_Timer <= diff)
            {
                for (uint8 i = 0; i < 6; ++i)
                {
                    Creature *challenger = m_creature->GetMap()->GetCreature(AffrayChallenger[i]);
                    if (challenger && !challenger->isAlive() && challenger->isDead())
                    {
                        DoScriptText(SAY_TWIGGY_DOWN, m_creature);
                        challenger->RemoveCorpse();
                        AffrayChallenger[i] = 0;
                        continue;
                    }
                }
                ChallengerDeath_Timer = 2500;
            }
            else ChallengerDeath_Timer -= diff;
        }
        if (Event_Timer < diff)
        {
            Player* pPlayer = m_creature->GetMap()->GetPlayer(PlayerGUID);

            if (!pPlayer || pPlayer->isDead())
                Reset();

            switch (Step)
            {
                case 0:
                    SetChallengers();
                    ChallengerDeath_Timer = 2500;
                    Event_Timer = 5000;
                    ++Step;
                    break;
                case 1:
                    DoScriptText(SAY_TWIGGY_FRAY, m_creature);
                    if (Unit *challenger = m_creature->GetMap()->GetUnit(AffrayChallenger[Challenger_Count]))
                        SetChallengerReady(challenger);
                    else Reset();
                    ++Challenger_Count;
                    Event_Timer = 25000;
                    if (Challenger_Count == 6)
                        ++Step;
                    break;
                case 2:
                    if (Unit *temp = m_creature->SummonCreature(NPC_BIG_WILL, -1713.79f, -4342.09f, 6.05f, 6.15f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000))
                    {
                        BigWillGUID = temp->GetGUID();
                        temp->setFaction(35);
                        temp->GetMotionMaster()->MovePoint(0, -1682.31f, -4329.68f, 2.78f);
                    }
                    Event_Timer = 15000;
                    ++Step;
                    break;
                case 3:
                    if (Unit *will = m_creature->GetMap()->GetUnit(BigWillGUID))
                    {
                        will->setFaction(32);
                        DoScriptText(SAY_BIG_WILL_READY, will, pPlayer);
                    }
                    Event_Timer = 5000;
                    ++Step;
                    break;
                case 4:
                    Unit *will = m_creature->GetMap()->GetUnit(BigWillGUID);
                    if (will && will->isDead())
                    {
                        DoScriptText(SAY_TWIGGY_OVER, m_creature);
                        Reset();
                    }
                    else if (!will)
                        Reset();
                    Event_Timer = 5000;
                    break;
            }
        }
        else Event_Timer -= diff;
        if (Emote_Timer < diff)
        {
            for (uint8 i = Challenger_Count; i < 6; i++)
            {
                if (Unit* creaChallenger = m_creature->GetMap()->GetUnit(AffrayChallenger[i]))
                {
                    if (!urand(0, 4))
                        creaChallenger->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                }
            }
            std::list<Creature*> lCrea;
            m_creature->GetCreatureListWithEntryInGrid(lCrea, NPC_AFFRAY_SPECTATOR, 30.0f);
            for (std::list<Creature*>::iterator it = lCrea.begin(); it != lCrea.end(); ++it)
            {
                switch (urand(0, 10))
                {
                    case 0:
                        (*it)->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                        break;
                    case 1:
                        (*it)->HandleEmoteCommand(EMOTE_ONESHOT_RUDE);
                        break;
                }
            }
            Emote_Timer = 2000;
        }
        else
            Emote_Timer -= diff;
    }
};

CreatureAI* GetAI_npc_twiggy_flathead(Creature* pCreature)
{
    return new npc_twiggy_flatheadAI(pCreature);
}

bool AreaTrigger_at_twiggy_flathead(Player* pPlayer, const AreaTriggerEntry* pAt)
{
    if (!pPlayer->isDead() && pPlayer->GetQuestStatus(QUEST_AFFRAY) == QUEST_STATUS_INCOMPLETE)
    {
        Creature* pCreature = GetClosestCreatureWithEntry(pPlayer, NPC_TWIGGY, 30.0f);

        if (!pCreature)
            return true;

        if (((npc_twiggy_flatheadAI*)pCreature->AI())->CanStartEvent(pPlayer))
            return false;                                   //ok to let mangos process further
        else
            return true;
    }
    return true;
}

/*#####
## npc_wizzlecranks_shredder
#####*/

enum
{
    SAY_START           = -1000298,
    SAY_STARTUP1        = -1000299,
    SAY_STARTUP2        = -1000300,
    SAY_MERCENARY       = -1000301,
    SAY_PROGRESS_1      = -1000302,
    SAY_PROGRESS_2      = -1000303,
    SAY_PROGRESS_3      = -1000304,
    SAY_END             = -1000305,

    QUEST_ESCAPE        = 863,
    FACTION_RATCHET     = 637,
    NPC_PILOT_WIZZ      = 3451,
    NPC_MERCENARY       = 3282
};

struct npc_wizzlecranks_shredderAI : public npc_escortAI
{
    npc_wizzlecranks_shredderAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_bIsPostEvent = false;
        m_uiPostEventTimer = 1000;
        m_uiPostEventCount = 0;
        Reset();
    }

    bool m_bIsPostEvent;
    uint32 m_uiPostEventTimer;
    uint32 m_uiPostEventCount;

    void Reset()
    {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
        {
            if (m_creature->getStandState() == UNIT_STAND_STATE_DEAD)
                m_creature->SetStandState(UNIT_STAND_STATE_STAND);

            m_bIsPostEvent = false;
            m_uiPostEventTimer = 1000;
            m_uiPostEventCount = 0;
        }
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch (uiPointId)
        {
            case 0:
                if (Player* pPlayer = GetPlayerForEscort())
                    DoScriptText(SAY_STARTUP1, m_creature, pPlayer);
                break;
            case 9:
                SetRun(false);
                break;
            case 17:
                if (Creature* pTemp = m_creature->SummonCreature(NPC_MERCENARY, 1128.489f, -3037.611f, 92.701f, 1.472f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000))
                {
                    DoScriptText(SAY_MERCENARY, pTemp);
                    m_creature->SummonCreature(NPC_MERCENARY, 1160.172f, -2980.168f, 97.313f, 3.690f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                }
                break;
            case 24:
                m_bIsPostEvent = true;
                break;
        }
    }

    void WaypointStart(uint32 uiPointId)
    {
        switch (uiPointId)
        {
            case 9:
                if (Player* pPlayer = GetPlayerForEscort())
                    DoScriptText(SAY_STARTUP2, m_creature, pPlayer);
                break;
            case 18:
                if (Player* pPlayer = GetPlayerForEscort())
                    DoScriptText(SAY_PROGRESS_1, m_creature, pPlayer);
                SetRun();
                break;
        }
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_PILOT_WIZZ)
            m_creature->SetStandState(UNIT_STAND_STATE_DEAD);

        if (pSummoned->GetEntry() == NPC_MERCENARY)
            pSummoned->AI()->AttackStart(m_creature);
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (m_bIsPostEvent)
            {
                if (m_uiPostEventTimer < uiDiff)
                {
                    switch (m_uiPostEventCount)
                    {
                        case 0:
                            DoScriptText(SAY_PROGRESS_2, m_creature);
                            break;
                        case 1:
                            DoScriptText(SAY_PROGRESS_3, m_creature);
                            break;
                        case 2:
                            DoScriptText(SAY_END, m_creature);
                            break;
                        case 3:
                            if (Player* pPlayer = GetPlayerForEscort())
                            {
                                pPlayer->GroupEventHappens(QUEST_ESCAPE, m_creature);
                                m_creature->SummonCreature(NPC_PILOT_WIZZ, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 180000);
                            }
                            break;
                    }

                    ++m_uiPostEventCount;
                    m_uiPostEventTimer = 5000;
                }
                else
                    m_uiPostEventTimer -= uiDiff;
            }

            return;
        }

        DoMeleeAttackIfReady();
    }
};

bool QuestAccept_npc_wizzlecranks_shredder(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_ESCAPE)
    {
        DoScriptText(SAY_START, pCreature);
        pCreature->setFaction(FACTION_RATCHET);

        if (npc_wizzlecranks_shredderAI* pEscortAI = dynamic_cast<npc_wizzlecranks_shredderAI*>(pCreature->AI()))
            pEscortAI->Start(true, pPlayer->GetGUID(), pQuest);
    }
    return true;
}

CreatureAI* GetAI_npc_wizzlecranks_shredder(Creature* pCreature)
{
    return new npc_wizzlecranks_shredderAI(pCreature);
}

/*######
## npc_razormane_stalker
######*/

#define SPELL_STEALTH                1784
#define SPELL_SINISTERSTRIKE         15667
#define NPC_RAZORMANE_STALKER        3457

struct npc_razormane_stalkerAI : public ScriptedAI
{
    npc_razormane_stalkerAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 SinisterStrike_Timer;
    uint32 SinisterStrike_Counter;

    void Reset() override
    {
        SinisterStrike_Timer = 8000;
        SinisterStrike_Counter = 0;
        DoCastSpellIfCan(m_creature, SPELL_STEALTH);
    }

    void UpdateAI(const uint32 diff) override
    {

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (SinisterStrike_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SINISTERSTRIKE);
            SinisterStrike_Counter += 1;
            if (SinisterStrike_Counter == 1) SinisterStrike_Timer = 15000;
            else if (SinisterStrike_Counter == 2) SinisterStrike_Timer = 12000;
            else SinisterStrike_Timer = 15000;
        }
        else SinisterStrike_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_razormane_stalker(Creature* pCreature)
{
    return new npc_razormane_stalkerAI(pCreature);
}

/*
 * 'Mission: Possible But Not Probable' support:
 * Grand Foreman Puzik Gallywix
 * Mutated Venture Co. Drone
 * Venture Co. Patroller
 * Venture Co. Lookout
 */

enum
{
    NPC_MUTATED_VENTURE_CO_DRONE        = 7310,
    NPC_VENTURE_CO_PATROLLER            = 7308,
    NPC_VENTURE_CO_LOOKOUT              = 7307,
    NPC_GRAND_FOREMAN_PUZIK_GALLYWIX    = 7288,

    SPELL_JUGGLER_VEIN_RUPTURE          = 10265,
    SPELL_LUNG_PUNCTURE                 = 10266,
    SPELL_SLUSH                         = 10267,
    SPELL_DECIMATE                      = 10268
};

struct npc_mission_possible_but_not_probableAI : ScriptedAI
{
    explicit npc_mission_possible_but_not_probableAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        npc_mission_possible_but_not_probableAI::Reset();
    }

    void Reset() override
    {

    }

    void SpellHit(Unit* /*caster*/, const SpellEntry* pSpell) override
    {
        uint32 spellId = 0;

        switch (m_creature->GetEntry())
        {
        case NPC_MUTATED_VENTURE_CO_DRONE:
            if (pSpell->IsFitToFamily<SPELLFAMILY_ROGUE, CF_ROGUE_GARROTE, CF_ROGUE_AMBUSH>())
                spellId = SPELL_JUGGLER_VEIN_RUPTURE;
            break;
        case NPC_VENTURE_CO_PATROLLER:
            if (pSpell->IsFitToFamily<SPELLFAMILY_ROGUE, CF_ROGUE_RUPTURE>())
                spellId = SPELL_LUNG_PUNCTURE;
            break;
        case NPC_VENTURE_CO_LOOKOUT:
            if (pSpell->IsFitToFamily<SPELLFAMILY_ROGUE, CF_ROGUE_EVISCERATE>())
                spellId = SPELL_SLUSH;
            break;
        case NPC_GRAND_FOREMAN_PUZIK_GALLYWIX:
            if (pSpell->IsFitToFamily<SPELLFAMILY_ROGUE, CF_ROGUE_AMBUSH>())
                spellId = SPELL_DECIMATE;
            break;
        default:
            return;
        }

        DoCastSpellIfCan(m_creature, spellId);
    }
};

CreatureAI* GetAI_npc_mission_possible_but_not_probable(Creature* pCreature)
{
    return new npc_mission_possible_but_not_probableAI(pCreature);
}

/*
 * Sarilus Foulborne
 */

enum
{
    SPELL_SARILUS_ELEMENTALS_PASSIVE    = 6488,
    SPELL_SARILUS_ELEMENTALS            = 6490,
    SPELL_FEED_SARILUS_PASSIVE          = 6498,
    SPELL_FROSTBOLT                     = 20806,
};

struct npc_sarilus_foulborneAI : ScriptedAI
{
    explicit npc_sarilus_foulborneAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        npc_sarilus_foulborneAI::Reset();
    }

    uint32 m_uiElementalsTimer;
    uint32 m_uiFrostboltTimer;

    void Reset() override
    {
        m_uiElementalsTimer = urand(1500, 9000);
        m_uiFrostboltTimer = urand(3500, 4500);
    }

    void JustSummoned(Creature* pSummoned) override
    {
        pSummoned->CastSpell(pSummoned, SPELL_SARILUS_ELEMENTALS_PASSIVE, true);
        pSummoned->CastSpell(pSummoned, SPELL_FEED_SARILUS_PASSIVE, true);
    }

    void UpdateAI(uint32 const uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiElementalsTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_SARILUS_ELEMENTALS) == CAST_OK)
                m_uiElementalsTimer = 9000;
        }
        else
            m_uiElementalsTimer -= uiDiff;

        if (m_uiFrostboltTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_FROSTBOLT) == CAST_OK)
                m_uiFrostboltTimer = urand(3500, 4500);
        }
        else
            m_uiFrostboltTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_sarilus_foulborne(Creature* pCreature)
{
    return new npc_sarilus_foulborneAI(pCreature);
}

/*
 * The Principle Source
 */

enum
{
    EVENT_THE_PRINCIPLE_SOURCE      = 5246,

    NPC_BURNING_BLADE_TOXICOLOGIST  = 12319
};

struct Coords
{
    uint32 entry;
    float x, y, z, o;
};

static const Coords Toxicologist[] =
{
    { NPC_BURNING_BLADE_TOXICOLOGIST, 331.52f, -2270.94f, 242.21f, 5.15f },
    { NPC_BURNING_BLADE_TOXICOLOGIST, 332.09f, -2291.26f, 241.86f, 1.05f },
    { NPC_BURNING_BLADE_TOXICOLOGIST, 345.97f, -2282.66f, 241.77f, 3.16f },
};

bool ProcessEventId_event_the_principle_source(uint32 eventId, Object* pSource, Object* /*pTarget*/, bool /*isStart*/)
{
    if (eventId != EVENT_THE_PRINCIPLE_SOURCE)
        return true;

    auto pPlayer = pSource->ToPlayer();

    if (!pPlayer)
        return true;

    for (uint8 i = 0; i < 3; ++i)
    {
        if (auto pToxicologist = pPlayer->SummonCreature(Toxicologist[i].entry,
            Toxicologist[i].x,
            Toxicologist[i].y,
            Toxicologist[i].z,
            Toxicologist[i].o, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 2*MINUTE*IN_MILLISECONDS))
        {
            pToxicologist->AI()->AttackStart(pPlayer);
        }        
    }

    return true;
}

enum
{
    EVENT_GET_WATER_SAMPLE = 2048,
    NPC_RAZORMANE_PATHFINDER = 3456
};

bool ProcessEventId_event_get_water_sample(uint32 eventId, Object* pSource, Object* /*pTarget*/, bool /*isStart*/)
{
    if (eventId != EVENT_GET_WATER_SAMPLE)
        return true;

    auto pPlayer = pSource->ToPlayer();

    if (!pPlayer)
        return true;

    if (auto quilboar = pPlayer->SummonCreature(NPC_RAZORMANE_PATHFINDER, -3592.45f, -1872.06f, 91.62f, 0.19f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 2 * MINUTE*IN_MILLISECONDS))
    {
        quilboar->AI()->AttackStart(pPlayer);
    }

    return true;
}

void AddSC_the_barrens()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_beaten_corpse";
    newscript->pGossipHello = &GossipHello_npc_beaten_corpse;
    newscript->pGossipSelect = &GossipSelect_npc_beaten_corpse;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_gilthares";
    newscript->GetAI = &GetAI_npc_gilthares;
    newscript->pQuestAcceptNPC = &QuestAccept_npc_gilthares;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_gizmotronic";
    newscript->pGossipHello = &GossipHello_npc_Gizmotronic;
    newscript->pGossipSelect = &GossipSelect_npc_Gizmotronic;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_taskmaster_fizzule";
    newscript->GetAI = &GetAI_npc_taskmaster_fizzule;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_polly";
    newscript->GetAI = &GetAI_npc_polly;
    newscript->RegisterSelf();


    newscript = new Script;
    newscript->Name = "npc_twiggy_flathead";
    newscript->GetAI = &GetAI_npc_twiggy_flathead;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "at_twiggy_flathead";
    newscript->pAreaTrigger = &AreaTrigger_at_twiggy_flathead;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_wizzlecranks_shredder";
    newscript->GetAI = &GetAI_npc_wizzlecranks_shredder;
    newscript->pQuestAcceptNPC = &QuestAccept_npc_wizzlecranks_shredder;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_razormane_stalker";
    newscript->GetAI = &GetAI_npc_razormane_stalker;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_mission_possible_but_not_probable";
    newscript->GetAI = &GetAI_npc_mission_possible_but_not_probable;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_sarilus_foulborne";
    newscript->GetAI = &GetAI_npc_sarilus_foulborne;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "event_get_water_sample";
    newscript->pProcessEventId = &ProcessEventId_event_get_water_sample;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "event_the_principle_source";
    newscript->pProcessEventId = &ProcessEventId_event_the_principle_source;
    newscript->RegisterSelf();
}
