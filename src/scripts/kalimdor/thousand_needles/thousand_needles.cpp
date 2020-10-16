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
SDName: Thousand_Needles
SD%Complete: 90
SDComment: Quest support: 1950, 4770, 4904, 4966
SDCategory: Thousand Needles
EndScriptData
*/

/* ContentData
npc_kanati
npc_lakota_windsong
npc_paoka_swiftmountain
npc_plucky_johnson
EndContentData */

#include "scriptPCH.h"

/*######
# npc_kanati
######*/

enum
{
    SAY_KAN_START              = -1000410,

    QUEST_PROTECT_KANATI        = 4966,
    NPC_GALAK_ASS               = 10720
};

const float m_afGalakLoc[] = { -4867.387695f, -1357.353760f, -48.226f};

struct npc_kanatiAI : public npc_escortAI
{
    npc_kanatiAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        Reset();
    }

    void Reset() { }

    void WaypointReached(uint32 uiPointId)
    {
        switch (uiPointId)
        {
            case 0:
                DoScriptText(SAY_KAN_START, m_creature);
                DoSpawnGalak();
                break;
            case 1:
                if (Player* pPlayer = GetPlayerForEscort())
                    pPlayer->GroupEventHappens(QUEST_PROTECT_KANATI, m_creature);
                break;
        }
    }

    void DoSpawnGalak()
    {
        for (int i = 0; i < 3; ++i)
            m_creature->SummonCreature(NPC_GALAK_ASS,
                                       m_afGalakLoc[0], m_afGalakLoc[1], m_afGalakLoc[2], 0.0f,
                                       TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
    }

    void JustSummoned(Creature* pSummoned)
    {
        pSummoned->AI()->AttackStart(m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        // set quest to failed
        if (Player* pPlayer = GetPlayerForEscort())
            pPlayer->FailQuest(QUEST_PROTECT_KANATI);
    }
};

CreatureAI* GetAI_npc_kanati(Creature* pCreature)
{
    return new npc_kanatiAI(pCreature);
}

bool QuestAccept_npc_kanati(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_PROTECT_KANATI)
    {
        if (npc_kanatiAI* pEscortAI = dynamic_cast<npc_kanatiAI*>(pCreature->AI()))
            pEscortAI->Start(false, pPlayer->GetGUID(), pQuest, true);
    }
    return true;
}

/*######
# npc_lakota_windsong
######*/

enum
{
    SAY_LAKO_START              = -1000365,
    SAY_LAKO_LOOK_OUT           = -1000366,
    SAY_LAKO_HERE_COME          = -1000367,
    SAY_LAKO_MORE               = -1000368,
    SAY_LAKO_END                = -1000369,

    QUEST_FREE_AT_LAST          = 4904,
    NPC_GRIM_BANDIT             = 10758,

    ID_AMBUSH_1                 = 0,
    ID_AMBUSH_2                 = 2,
    ID_AMBUSH_3                 = 4
};

float m_afBanditLoc[6][6] =
{
    { -4905.479492f, -2062.732666f, 84.352f},
    { -4915.201172f, -2073.528320f, 84.733f},
    { -4878.883301f, -1986.947876f, 91.966f},
    { -4877.503906f, -1966.113403f, 91.859f},
    { -4767.985352f, -1873.169189f, 90.192f},
    { -4788.861328f, -1888.007813f, 89.888f}
};

struct npc_lakota_windsongAI : public npc_escortAI
{
    npc_lakota_windsongAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        Reset();
    }

    void Reset() { }

    void WaypointReached(uint32 uiPointId)
    {
        switch (uiPointId)
        {
            case 8:
                DoScriptText(SAY_LAKO_LOOK_OUT, m_creature);
                DoSpawnBandits(ID_AMBUSH_1);
                break;
            case 14:
                DoScriptText(SAY_LAKO_HERE_COME, m_creature);
                DoSpawnBandits(ID_AMBUSH_2);
                break;
            case 21:
                DoScriptText(SAY_LAKO_MORE, m_creature);
                DoSpawnBandits(ID_AMBUSH_3);
                break;
            case 45:
                if (Player* pPlayer = GetPlayerForEscort())
                    pPlayer->GroupEventHappens(QUEST_FREE_AT_LAST, m_creature);
                break;
        }
    }

    void DoSpawnBandits(int uiAmbushId)
    {
        for (int i = 0; i < 2; ++i)
            m_creature->SummonCreature(NPC_GRIM_BANDIT,
                                       m_afBanditLoc[i + uiAmbushId][0], m_afBanditLoc[i + uiAmbushId][1], m_afBanditLoc[i + uiAmbushId][2], 0.0f,
                                       TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
    }
};

CreatureAI* GetAI_npc_lakota_windsong(Creature* pCreature)
{
    return new npc_lakota_windsongAI(pCreature);
}

bool QuestAccept_npc_lakota_windsong(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_FREE_AT_LAST)
    {
        DoScriptText(SAY_LAKO_START, pCreature, pPlayer);
        pCreature->setFaction(FACTION_ESCORT_H_NEUTRAL_ACTIVE);

        if (npc_lakota_windsongAI* pEscortAI = dynamic_cast<npc_lakota_windsongAI*>(pCreature->AI()))
            pEscortAI->Start(false, pPlayer->GetGUID(), pQuest);
    }
    return true;
}

/*######
# npc_paoka_swiftmountain
######*/

enum
{
    SAY_START           = -1000362,
    SAY_WYVERN          = -1000363,
    SAY_COMPLETE        = -1000364,

    QUEST_HOMEWARD      = 4770,
    NPC_WYVERN          = 4107
};

float m_afWyvernLoc[3][3] =
{
    { -4990.606f, -906.057f, -5.343f},
    { -4970.241f, -927.378f, -4.951f},
    { -4985.364f, -952.528f, -5.199f}
};

struct npc_paoka_swiftmountainAI : public npc_escortAI
{
    npc_paoka_swiftmountainAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        Reset();
    }

    void Reset() { }

    void WaypointReached(uint32 uiPointId)
    {
        switch (uiPointId)
        {
            case 15:
                DoScriptText(SAY_WYVERN, m_creature);
                DoSpawnWyvern();
                break;
            case 26:
                DoScriptText(SAY_COMPLETE, m_creature);
                break;
            case 27:
                if (Player* pPlayer = GetPlayerForEscort())
                    pPlayer->GroupEventHappens(QUEST_HOMEWARD, m_creature);
                break;
        }
    }

    void DoSpawnWyvern()
    {
        for (int i = 0; i < 3; ++i)
            m_creature->SummonCreature(NPC_WYVERN,
                                       m_afWyvernLoc[i][0], m_afWyvernLoc[i][1], m_afWyvernLoc[i][2], 0.0f,
                                       TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
    }
};

CreatureAI* GetAI_npc_paoka_swiftmountain(Creature* pCreature)
{
    return new npc_paoka_swiftmountainAI(pCreature);
}

bool QuestAccept_npc_paoka_swiftmountain(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_HOMEWARD)
    {
        DoScriptText(SAY_START, pCreature, pPlayer);
        pCreature->setFaction(FACTION_ESCORT_H_NEUTRAL_ACTIVE);

        if (npc_paoka_swiftmountainAI* pEscortAI = dynamic_cast<npc_paoka_swiftmountainAI*>(pCreature->AI()))
            pEscortAI->Start(false, pPlayer->GetGUID(), pQuest);
    }
    return true;
}

/*######
# "Plucky" Johnson
######*/

enum
{
    FACTION_FRIENDLY        = 35,
    QUEST_SCOOP             = 1950,
    SPELL_PLUCKY_HUMAN      = 9192,
    SPELL_PLUCKY_CHICKEN    = 9220
};

#define GOSSIP_ITEM_QUEST   "Please tell me the Phrase.."

struct npc_plucky_johnsonAI : public ScriptedAI
{
    npc_plucky_johnsonAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiNormFaction = pCreature->getFaction();
        Reset();
    }

    uint32 m_uiNormFaction;
    uint32 m_uiResetTimer;

    void Reset()
    {
        m_uiResetTimer = 120000;

        if (m_creature->getFaction() != m_uiNormFaction)
            m_creature->setFaction(m_uiNormFaction);

        if (m_creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
            m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

        m_creature->CastSpell(m_creature, SPELL_PLUCKY_CHICKEN, false);
    }

    void ReceiveEmote(Player* pPlayer, uint32 uiTextEmote)
    {
        if (pPlayer->GetQuestStatus(QUEST_SCOOP) == QUEST_STATUS_INCOMPLETE)
        {
            if (uiTextEmote == TEXTEMOTE_BECKON)
            {
                m_creature->setFaction(FACTION_FRIENDLY);
                m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                m_creature->CastSpell(m_creature, SPELL_PLUCKY_HUMAN, false);
            }
        }

        if (uiTextEmote == TEXTEMOTE_CHICKEN)
        {
            if (m_creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
                return;
            else
            {
                m_creature->setFaction(FACTION_FRIENDLY);
                m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                m_creature->CastSpell(m_creature, SPELL_PLUCKY_HUMAN, false);
                m_creature->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
        {
            if (m_uiResetTimer < uiDiff)
            {
                if (!m_creature->getVictim())
                    EnterEvadeMode();
                else
                    m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

                return;
            }
            else
                m_uiResetTimer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_plucky_johnson(Creature* pCreature)
{
    return new npc_plucky_johnsonAI(pCreature);
}

bool GossipHello_npc_plucky_johnson(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_SCOOP) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_QUEST, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(720, pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_plucky_johnson(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        pPlayer->SEND_GOSSIP_MENU(738, pCreature->GetGUID());
        pPlayer->AreaExploredOrEventHappens(QUEST_SCOOP);
    }

    return true;
}

/*#####
#npc_panter
######*/

/*
[SQL]
UPDATE creature_template SET ScriptName="npc_enraged_panther" WHERE entry=10992;
UPDATE gameobject_template SET ScriptName="go_panther_cage" WHERE entry=176195;
*/

enum ePantherCage
{
    ENRAGED_PANTHER = 10992
};

bool go_panther_cage(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(5151) == QUEST_STATUS_INCOMPLETE)
    {
        if (Creature* panther = pGo->FindNearestCreature(ENRAGED_PANTHER, 5.0f, true))
        {
            panther->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            panther->AI()->AttackStart(pPlayer);
        }
    }

    // false pour que le core ouvre la cage. Sinon elle reste fermee.
    return false;
}

struct npc_enraged_pantherAI : public ScriptedAI
{
    npc_enraged_pantherAI(Creature *c) : ScriptedAI(c) {}

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_enraged_panther(Creature* pCreature)
{
    return new npc_enraged_pantherAI(pCreature);
}

/*
 * Grenka Bloodscreech
 */

enum
{
    NPC_GRENKA              = 4490,
    NPC_SCREECHING_HARPY    = 4100
};

struct Coords
{
    uint32 entry;
    float x, y, z, o;
};

static const Coords Harpies[] = 
{
    { NPC_SCREECHING_HARPY, -5587.69f, -1571.45f, 11.21f, 6.14f },

    { NPC_SCREECHING_HARPY, -5587.69f, -1571.45f, 11.21f, 6.14f },
    { NPC_SCREECHING_HARPY, -5589.63f, -1575.89f, 11.75f, 6.02f },

    { NPC_SCREECHING_HARPY, -5587.69f, -1571.45f, 11.21f, 6.14f },
    { NPC_GRENKA,           -5589.63f, -1575.89f, 11.75f, 6.02f }
};

struct npc_grenka_bloodscreechAI : ScriptedAI
{
    explicit npc_grenka_bloodscreechAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED | UNIT_FLAG_PASSIVE);
        m_creature->SetVisibility(VISIBILITY_OFF);

        m_uiWave = 0;
        m_uiTimer = 5000;

        npc_grenka_bloodscreechAI::Reset();
    }

    uint8 m_uiWave;
    uint32 m_uiTimer;
    ObjectGuid m_PlayerGuid;

    void Reset() override
    {
        
    }

    void DoSummon(uint8 index) const
    {
        m_creature->SummonCreature(Harpies[index].entry,
            Harpies[index].x,
            Harpies[index].y,
            Harpies[index].z,
            Harpies[index].o, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, MINUTE*IN_MILLISECONDS);
    }

    void JustSummoned(Creature* pSummoned) override
    {
        if (auto pPlayer = m_creature->GetMap()->GetPlayer(m_PlayerGuid))
        {
            if (pPlayer->isAlive())
                pSummoned->AI()->AttackStart(pPlayer);
        }
    }

    void SummonedCreatureJustDied(Creature* pSummoned) override
    {
        pSummoned->loot.clear();
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (m_uiTimer < uiDiff)
        {
            switch (m_uiWave)
            {
            case 0:
                DoSummon(0);
                m_uiTimer = 15000;
                ++m_uiWave;
                break;
            case 1:
                DoSummon(1);
                DoSummon(2);
                m_uiTimer = 15000;
                ++m_uiWave;
                break;
            case 2:
                {
                    DoSummon(3);
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED | UNIT_FLAG_PASSIVE);
                    m_creature->SetVisibility(VISIBILITY_ON);
                    if (auto pPlayer = m_creature->GetMap()->GetPlayer(m_PlayerGuid))
                    {
                        if (pPlayer->isAlive())
                            m_creature->AI()->AttackStart(pPlayer);
                    }
                    ++m_uiWave;
                }
                break;
            }
        }
        else
            m_uiTimer -= uiDiff;

        ScriptedAI::UpdateAI(uiDiff);
    }
};

CreatureAI* GetAI_npc_grenka_bloodscreech(Creature* pCreature)
{
    return new npc_grenka_bloodscreechAI(pCreature);
}

/*
 * Test of Endurance
 */

bool ProcessEventId_event_test_of_endurance(uint32 eventId, Object* pSource, Object* pTarget, bool isStart)
{
    auto pGO = pTarget->ToGameObject();
    auto pPlayer = pSource->ToPlayer();

    if (!pGO || !pPlayer)
        return true;

    if (pGO->FindNearestCreature(NPC_GRENKA, 100.0f))
        return true;

    if (auto pGrenka = pGO->SummonCreature(Harpies[4].entry,
        Harpies[4].x,
        Harpies[4].y, 
        Harpies[4].z, 
        Harpies[4].o, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, MINUTE*IN_MILLISECONDS))
    {
        if (auto pGrenkaAI = static_cast<npc_grenka_bloodscreechAI*>(pGrenka->AI()))
            pGrenkaAI->m_PlayerGuid = pPlayer->GetObjectGuid();
    }

    return true;
}

enum ZamekDistractionValues
{
    QUEST_ZAMEK_DISTRACTION = 1191,
    ZAMEK_ID = 4709,
    RIZZLE_BRASSBOLTS_ID = 4720,
    UNGUARDED_PAGES_GO_ID = 13621,
    GUARDED_PAGES_GO_ID = 17087,
    SPELL_BOMB = 5134,
    THINGS_GO_BOOM_TEXT_ID = 237,
    EXPLOSIONBARREL_GOBJECT_ID = 20737, //You have no idea how much time that cost me to find this
    INVISIBLE_TRIGGER_ID = 14495
};

static const Position ZamekInitialRoutine[] =
{
    {-6239.61f, -3943.13f, -58.74f, 1.9f},
    {-6262.61f, -3921.15f, -58.83f, 1.56f},
    {-6264.33f, -3860.95f, -58.74f, 0.76f},
    {-6261.20f, -3857.53f, -58.74f, 0.75f}
};

static const Position ZamekInitialRoutine_ver2[] =
{
    { -6269.41f, -3851.76f, -58.75f, 1.0f },
    { -6266.47f, -3846.88f, -58.75f, 0.98f }
};

static const Position ZamekBombPosition      = { -6259.87f, -3856.4f, -58.74f, 0.45f };
static const Position ZamekBombPosition_ver2 = { -6265.f, -3844.67f, -58.75f, 4.0f };
static const Position ZamekAfterBombPosition = { -6264.87f, -3867.08f, -58.75f, 0.45f };

static const Position ZamekChaseLoop[] =
{
    {-6260.67f, -3873.73f, -58.74f, 5.38f},
    {-6247.f,   -3880.f,   -58.77f,  1.5f },
    {-6250.f,   -3864.f,   -58.75f, 3.69f}
};

#define ZAMEK_DISTRACTION_VER2

struct npc_rizzle_brassbolts : public ScriptedAI
{
    npc_rizzle_brassbolts(Creature* npc) : ScriptedAI(npc)
    {
        Reset();
    }

    virtual void Reset() override;

    virtual void UpdateAI(const uint32 diff) override;

    virtual void MovementInform(uint32, uint32) override;

    uint32 EventNum;
    uint32 EventSubNum;
    int32 EventTimer;
    bool bMoving;
};

struct npc_zamek : public ScriptedAI
{
    npc_zamek(Creature* npc) : ScriptedAI(npc)
    {
        Reset();
    }

    virtual void Reset() override
    {
        EventNum = 0;
        EventTimer = 0;
        ChaseTimer = 0;
        EventSubNum = 0;
        bMoving = false;
        ExplosiveBarrelDummyGUID.Clear();
        ExplosiveBarrelRef = nullptr;
        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
    }

    virtual void UpdateAI(const uint32 diff) override
    {
        if (EventNum != 0)
        {
            if (EventTimer > 0)
            {
                EventTimer -= diff;
                return;
            }
#ifdef ZAMEK_DISTRACTION_VER2
            switch (EventNum)
            {
            case 1:
                //make yourself not attackable
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
                //Remove questgiver flag
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                if (!bMoving)
                {
                    constexpr size_t WaypointCount = sizeof(ZamekInitialRoutine_ver2) / sizeof(ZamekInitialRoutine_ver2[0]);
                    if (EventSubNum == WaypointCount)
                    {
                        //go to next stage
                        EventNum = 2;
                        break;
                    }
                    me->GetMotionMaster()->MovePoint(EventSubNum,
                        ZamekInitialRoutine_ver2[EventSubNum].x, ZamekInitialRoutine_ver2[EventSubNum].y, ZamekInitialRoutine_ver2[EventSubNum].z,
                        MoveOptions::MOVE_RUN_MODE, 0.0f, ZamekInitialRoutine_ver2[EventSubNum].o);
                    bMoving = true;
                }
                break;
            case 2:
                //say line
                me->MonsterSay(NOST_TEXT(THINGS_GO_BOOM_TEXT_ID));
                //place explosion barrel
                //#TODO: Explosion barrel
                ExplosiveBarrelRef = me->SummonGameObject(EXPLOSIONBARREL_GOBJECT_ID,
                    ZamekBombPosition_ver2.x, ZamekBombPosition_ver2.y, ZamekBombPosition_ver2.z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30, true);
                if (auto creature = me->SummonCreature(INVISIBLE_TRIGGER_ID, ZamekBombPosition_ver2.x, ZamekBombPosition_ver2.y, ZamekBombPosition_ver2.z, 0.0f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30 * IN_MILLISECONDS))
                    ExplosiveBarrelDummyGUID = creature->GetGUID();
                EventNum = 3;
                EventTimer = 3 * 1000; //3 sec
                break;
            case 3:
                //Move back
                me->GetMotionMaster()->MovePoint(0,
                    ZamekInitialRoutine_ver2[0].x, ZamekInitialRoutine_ver2[0].y, ZamekInitialRoutine_ver2[0].z,
                    MoveOptions::MOVE_RUN_MODE, 0.0f, ZamekInitialRoutine_ver2[0].o);
                bMoving = true;
                EventNum = 4;
                break;
            case 4:
                if (!bMoving)
                {
                    //explode barrel, and despawn
                    if (ExplosiveBarrelRef != nullptr)
                    {
                        ExplosiveBarrelRef->Despawn();
                        ExplosiveBarrelRef->AddObjectToRemoveList();
                        ExplosiveBarrelRef = nullptr;
                    }
                    if (Creature* creature = me->GetMap()->GetCreature(ExplosiveBarrelDummyGUID))
                        creature->CastSpell(creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(),SPELL_BOMB, true);

                    //signal to Rizzle
                    if (Creature* pRizzle = me->FindNearestCreature(RIZZLE_BRASSBOLTS_ID, 75.0f))
                    {
                        if (npc_rizzle_brassbolts* pRizzleAI = dynamic_cast<npc_rizzle_brassbolts*>(pRizzle->AI()))
                        {
                            pRizzleAI->EventNum = 1;
                        }
                    }
                    //Move to home
                    me->GetMotionMaster()->MoveTargetedHome();
                    EventNum = 6;
                    bMoving = true;
                }
                break;
            case 6:
                if (!bMoving)
                {
                    Reset();
                }
                break;
            default:
                break;
            }
#else
            switch (EventNum)
            {
            case 1:
                //make yourself not attackable
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
                //Remove questgiver flag
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                //move to Gnome Drag Car
                if (!bMoving)
                {
                    constexpr size_t WaypointCount = sizeof(ZamekInitialRoutine) / sizeof(ZamekInitialRoutine[0]);
                    if (EventSubNum == WaypointCount)
                    {
                        //go to next stage
                        EventNum = 2;
                        break;
                    }
                    me->GetMotionMaster()->MovePoint(EventSubNum,
                        ZamekInitialRoutine[EventSubNum].x, ZamekInitialRoutine[EventSubNum].y, ZamekInitialRoutine[EventSubNum].z,
                        MoveOptions::MOVE_RUN_MODE, 0.0f, ZamekInitialRoutine[EventSubNum].o);
                    bMoving = true;
                }
                break;
            case 2:
                //Start use animation
                me->HandleEmote(EMOTE_STATE_WORK);
                EventTimer = 5 * 1000; //5 sec
                EventNum = 3;
                break;
            case 3:
                //Stop use animation
                me->HandleEmote(0);
                //Move back a little bit
                me->GetMotionMaster()->MovePoint(1,
                    ZamekAfterBombPosition.x, ZamekAfterBombPosition.y, ZamekAfterBombPosition.z,
                    MoveOptions::MOVE_RUN_MODE, 0.0f, ZamekAfterBombPosition.o);
                bMoving = true;
                EventTimer = 10 * 1000; //10 sec
                EventNum = 4;
                EventSubNum = 0;
                me->HandleEmote(EMOTE_ONESHOT_LAUGH);
                break;
            case 5:
                //Start chasing around
                if (!bMoving)
                {
                    constexpr size_t WaypointCount = sizeof(ZamekChaseLoop) / sizeof(ZamekChaseLoop[0]);
                    EventSubNum %= WaypointCount;
                    me->GetMotionMaster()->MovePoint(EventSubNum,
                        ZamekChaseLoop[EventSubNum].x, ZamekChaseLoop[EventSubNum].y, ZamekChaseLoop[EventSubNum].z,
                        MoveOptions::MOVE_RUN_MODE, 0.0f, ZamekChaseLoop[EventSubNum].o);
                    bMoving = true;
                }

                ChaseTimer += diff;
                if (ChaseTimer > 30 * 1000) //30 sec
                {
                    if (Creature* pRizzle = me->FindNearestCreature(RIZZLE_BRASSBOLTS_ID, 75.0f))
                    {
                        if (npc_rizzle_brassbolts* pRizzleAI = dynamic_cast<npc_rizzle_brassbolts*>(pRizzle->AI()))
                        {
                            pRizzleAI->EventNum = 4;
                        }
                    }
                    EventNum = 6;
                }
                break;
            case 6:
                //Move to home
                me->GetMotionMaster()->MoveTargetedHome();
                EventNum = 7; //This event not exist intentionaly. Do nothing
                break;
            default:
                break;
            }
#endif
        }
        ScriptedAI::UpdateAI(diff);
    }

    virtual void MovementInform(uint32 type, uint32 id) override
    {
#ifndef ZAMEK_DISTRACTION_VER2
        if (EventNum == 4)
        {
            //Draw explosion now
            me->CastSpell(ZamekBombPosition.x, ZamekBombPosition.y, ZamekBombPosition.z, SPELL_BOMB, true);
            //Explosion happens, invoke Rizzle AI
            if (Creature* pRizzle = me->FindNearestCreature(RIZZLE_BRASSBOLTS_ID, 75.0f))
            {
                if (npc_rizzle_brassbolts* pRizzleAI = dynamic_cast<npc_rizzle_brassbolts*>(pRizzle->AI()))
                {
                    pRizzleAI->EventNum = 1;
                    EventNum = 5;
                }
                else
                {
                    //Fail
                    EventNum = 6;
                }
            }
            else
            {
                //Fail
                EventNum = 6;
            }
        }
#endif
        EventSubNum = id + 1;
        bMoving = false;
    }

    int32 EventTimer;
    int32 ChaseTimer;
    uint32 EventNum;
    uint32 EventSubNum;
    bool bMoving;
    ObjectGuid ExplosiveBarrelDummyGUID;
    GameObject* ExplosiveBarrelRef;

    virtual void JustReachedHome() override
    {
        ScriptedAI::JustReachedHome();
        Reset();
    }

};

static const Position RizzleHomeOutside = { -6245.88f, -3852.23f, -58.75f, 3.6f };

static const Position RizzleHomeOutside_ver2[] =
{
    { -6245.88f, -3852.23f, -58.75f, 3.6f },
    { -6252.22f, -3860.28f, -58.75f, 2.43f }
};

void npc_rizzle_brassbolts::Reset()
{
    EventNum = 0;
    EventSubNum = 0;
    EventTimer = 0;
    me->GetMotionMaster()->MoveTargetedHome();
    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
}

void npc_rizzle_brassbolts::UpdateAI(const uint32 diff)
{
    if (EventTimer > 0)
    {
        EventTimer -= diff;
        return;
    }
#ifdef ZAMEK_DISTRACTION_VER2
    switch (EventNum)
    {
    case 1:
        //make yourself not attackable
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
        //We hear explosion, move outside, to see what happens
        if (!bMoving)
        {
            constexpr size_t WaypointCount = sizeof(RizzleHomeOutside_ver2) / sizeof(RizzleHomeOutside_ver2[0]);
            if (EventSubNum == WaypointCount)
            {
                //go to next stage
                EventNum = 2;
                break;
            }
            me->GetMotionMaster()->MovePoint(EventSubNum,
                RizzleHomeOutside_ver2[EventSubNum].x, RizzleHomeOutside_ver2[EventSubNum].y, RizzleHomeOutside_ver2[EventSubNum].z,
                MoveOptions::MOVE_RUN_MODE, 0.0f, RizzleHomeOutside_ver2[EventSubNum].o);
            bMoving = true;
        }
        break;
    case 2:
        //activate GO for a while
        if (const GameObjectData* GO_data = sObjectMgr.GetGOData(GUARDED_PAGES_GO_ID))
        {
            GameObject* GO = me->GetMap()->GetGameObject(ObjectGuid(HIGHGUID_GAMEOBJECT, GO_data->id, (uint32)GUARDED_PAGES_GO_ID));
            if (GO == nullptr)
            {
                sLog.outError("[SCRIPTS]: npc_rizzle_brassbolts can't find in world GO with ID '17087'");
                Reset();
                break;
            }

            GO->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND | GO_FLAG_NO_INTERACT);
            GO->SetLootState(GO_READY);
        }
        else
        {
            sLog.outError("[SCRIPTS]: npc_rizzle_brassbolts can't obtain GO with ID '17087'");
            Reset();
            break;
        }
        //just stay here for a while
        EventNum = 3;
        EventTimer = 30 * 1000; //30 sec
        break;
    case 3:
        if (const GameObjectData* GO_data = sObjectMgr.GetGOData(GUARDED_PAGES_GO_ID))
        {
            GameObject* GO = me->GetMap()->GetGameObject(ObjectGuid(HIGHGUID_GAMEOBJECT, GO_data->id, (uint32)GUARDED_PAGES_GO_ID));
            if (GO == nullptr)
            {
                sLog.outError("[SCRIPTS]: npc_rizzle_brassbolts can't find in world GO with ID '17087'");
                Reset();
                break;
            }

            GO->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND | GO_FLAG_NO_INTERACT);
            GO->SetLootState(GO_NOT_READY);
        }
        else
        {
            sLog.outError("[SCRIPTS]: npc_rizzle_brassbolts can't obtain GO with ID '17087'");
            Reset();
            break;
        }

        Reset();
        break;
    default:
        break;
    }
#else
    switch (EventNum)
    {
    case 1:
        //make yourself not attackable
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
        //We hear explosion, move outside, to see what happens
        me->GetMotionMaster()->MovePoint(1, RizzleHomeOutside.x, RizzleHomeOutside.y, RizzleHomeOutside.z,
            MoveOptions::MOVE_RUN_MODE, 0.0f, RizzleHomeOutside.o);
        bMoving = true;
        EventNum = 2;
        break;
    case 2:
        //Fucking goblins! By the way - spawn quest pages
        if (!bMoving)
        {
            me->HandleEmote(EMOTE_ONESHOT_POINT);
            if (const GameObjectData* GO_data = sObjectMgr.GetGOData(UNGUARDED_PAGES_GO_ID))
            {
                GameObject* GO = me->GetMap()->GetGameObject(ObjectGuid(HIGHGUID_GAMEOBJECT, GO_data->id, (uint32)UNGUARDED_PAGES_GO_ID));
                if (GO == nullptr)
                {
                    sLog.outError("[SCRIPTS]: npc_rizzle_brassbolts can't find in world GO with ID '13621'");
                    Reset();
                    break;
                }

                if (!GO->isSpawned())
                {
                    GO->SetLootState(GO_READY);
                    GO->SetRespawnTime(30); //30 sec, then despawn
                    GO->GetMap()->Add(GO);
                }
            }
            else
            {
                sLog.outError("[SCRIPTS]: npc_rizzle_brassbolts can't obtain GO with ID '13621'");
                Reset();
                break;
            }
            EventNum = 3;
            EventTimer = 3 * 1000; //3 sec
        }
        break;
    case 3:
        if (Creature* pZamek = me->FindNearestCreature(ZAMEK_ID, 150.0f))
        {
            me->GetMotionMaster()->MoveFollow(pZamek, 2.0f, 0);
            EventNum = 4;
            EventTimer = 35 * 1000; //35 sec
        }
        else
        {
            Reset();
            break;
        }
        break;
    case 4:
        Reset();
        break;
    default:
        break;
    }
#endif
    ScriptedAI::UpdateAI(diff);
}

void npc_rizzle_brassbolts::MovementInform(uint32 type, uint32 id)
{
    EventSubNum = id + 1;
    bMoving = false;
}

bool QuestRewarded_npc_zamek(Player* player, Creature* npc, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_ZAMEK_DISTRACTION)
    {
        if (npc_zamek* zamekAI = dynamic_cast<npc_zamek*>(npc->AI()))
        {
            if (zamekAI->EventNum == 0)
            {
                zamekAI->EventNum = 1;
            }
        }
    }
    return true;
}

CreatureAI* GetAI_npc_zamek(Creature* npc)
{
    return new npc_zamek(npc);
}

CreatureAI* GetAI_npc_rizzle_brassbolts(Creature* npc)
{
    return new npc_rizzle_brassbolts(npc);
}

void AddSC_thousand_needles()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "npc_kanati";
    newscript->GetAI = &GetAI_npc_kanati;
    newscript->pQuestAcceptNPC = &QuestAccept_npc_kanati;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_lakota_windsong";
    newscript->GetAI = &GetAI_npc_lakota_windsong;
    newscript->pQuestAcceptNPC = &QuestAccept_npc_lakota_windsong;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_paoka_swiftmountain";
    newscript->GetAI = &GetAI_npc_paoka_swiftmountain;
    newscript->pQuestAcceptNPC = &QuestAccept_npc_paoka_swiftmountain;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_plucky_johnson";
    newscript->GetAI = &GetAI_npc_plucky_johnson;
    newscript->pGossipHello = &GossipHello_npc_plucky_johnson;
    newscript->pGossipSelect = &GossipSelect_npc_plucky_johnson;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_enraged_panther";
    newscript->GetAI = &GetAI_npc_enraged_panther;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_panther_cage";
    newscript->pGOHello = &go_panther_cage;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_grenka_bloodscreech";
    newscript->GetAI = &GetAI_npc_grenka_bloodscreech;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "event_test_of_endurance";
    newscript->pProcessEventId = &ProcessEventId_event_test_of_endurance;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_zamek";
    newscript->pQuestRewardedNPC = &QuestRewarded_npc_zamek;
    newscript->GetAI = &GetAI_npc_zamek;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_rizzle_brassbolts";
    newscript->GetAI = &GetAI_npc_rizzle_brassbolts;
    newscript->RegisterSelf();
}
