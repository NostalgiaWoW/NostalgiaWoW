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
SDName: Desolace
SD%Complete: 100
SDComment: Quest support: 5561, 5381
SDCategory: Desolace
EndScriptData */

/* ContentData
npc_aged_dying_ancient_kodo
go_hand_of_iruxos_crystal

EndContentData */

#include "scriptPCH.h"
#include "MoveMapSharedDefines.h"

enum
{
    SAY_SMEED_HOME_1                = -1000348,
    SAY_SMEED_HOME_2                = -1000349,
    SAY_SMEED_HOME_3                = -1000350,

    QUEST_KODO                      = 5561,

    NPC_SMEED                       = 11596,
    NPC_AGED_KODO                   = 4700,
    NPC_DYING_KODO                  = 4701,
    NPC_ANCIENT_KODO                = 4702,
    NPC_TAMED_KODO                  = 11627,

    SPELL_KODO_KOMBO_ITEM           = 18153,
    SPELL_KODO_KOMBO_PLAYER_BUFF    = 18172,
    SPELL_KODO_KOMBO_DESPAWN_BUFF   = 18377,
    SPELL_KODO_KOMBO_GOSSIP         = 18362,
    SPELL_KODO_DESPAWN              = 18269

};

struct npc_aged_dying_ancient_kodoAI : ScriptedAI
{
    explicit npc_aged_dying_ancient_kodoAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        npc_aged_dying_ancient_kodoAI::Reset();
        npc_aged_dying_ancient_kodoAI::ResetCreature();
    }

    bool m_bUsed;
    ObjectGuid m_playerGuid;

    void Reset() override
    {

    }

    void ResetCreature() override
    {
        m_bUsed = false;
        m_playerGuid.Clear();
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (m_bUsed)
            return;

        if (who->GetEntry() == NPC_SMEED)
        {
            if (m_creature->IsWithinDistInMap(who, 10.0f))
            {
                switch (urand(0, 2))
                {
                case 0:
                    DoScriptText(SAY_SMEED_HOME_1, who);
                    break;
                case 1:
                    DoScriptText(SAY_SMEED_HOME_2, who);
                    break;
                case 2:
                    DoScriptText(SAY_SMEED_HOME_3, who);
                    break;
                }

                //spell have no implemented effect (dummy), so useful to notify spellHit
                m_creature->CastSpell(m_creature, SPELL_KODO_KOMBO_GOSSIP, true);
            }
        }
    }

    void SpellHit(Unit* pCaster, SpellEntry const* pSpell) override
    {
        if (pSpell->Id == SPELL_KODO_KOMBO_GOSSIP)
        {
            m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            m_creature->ForcedDespawn(MINUTE * IN_MILLISECONDS);
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MoveIdle();
            return;
        }
        
        if (pSpell->Id == SPELL_KODO_KOMBO_ITEM && !m_creature->HasAura(SPELL_KODO_KOMBO_DESPAWN_BUFF) && !pCaster->HasAura(SPELL_KODO_KOMBO_PLAYER_BUFF))
        {          
            pCaster->CombatStop(true);
            m_creature->CombatStop(true);

            pCaster->CastSpell(pCaster, SPELL_KODO_KOMBO_PLAYER_BUFF, true);

            m_creature->UpdateEntry(NPC_TAMED_KODO);
            m_creature->CastSpell(m_creature, SPELL_KODO_KOMBO_DESPAWN_BUFF, true);

            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MoveFollow(pCaster, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);

            m_playerGuid = pCaster->ToPlayer()->GetObjectGuid();

            return;
        }

        if (pSpell->Id == SPELL_KODO_DESPAWN)
            m_creature->ForcedDespawn();
    }

    void UpdateAI(const uint32 /*uiDiff*/) override
    {
        if (m_creature->GetEntry() == NPC_TAMED_KODO)
            return;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_aged_dying_ancient_kodo(Creature* pCreature)
{
    return new npc_aged_dying_ancient_kodoAI(pCreature);
}

bool GossipHello_npc_aged_dying_ancient_kodo(Player* pPlayer, Creature* pCreature)
{
    auto pKodoAI = static_cast<npc_aged_dying_ancient_kodoAI*>(pCreature->AI());

    if (!pKodoAI || pKodoAI->m_bUsed)
        return true;

    if (pPlayer->HasAura(SPELL_KODO_KOMBO_PLAYER_BUFF) && pKodoAI->m_playerGuid == pPlayer->GetObjectGuid())
    {
        pPlayer->TalkedToCreature(pCreature->GetEntry(), pCreature->GetGUID());
        pPlayer->RemoveAurasDueToSpell(SPELL_KODO_KOMBO_PLAYER_BUFF);

        pKodoAI->m_bUsed = true;
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

/*######
## go_hand_of_iruxos_crystal
######*/

enum
{
    DEMON_SPIRIT  = 11876
};

bool GOHello_go_hand_of_iruxos_crystal(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
    {
        if (Creature* pCreature = pPlayer->SummonCreature(DEMON_SPIRIT, -346.84f, 1765.13f, 138.39f, 5.91f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000))
            pCreature->AI()->AttackStart(pPlayer);
    }

    return true;
}
/*######
## npc_melizza_brimbuzzle
######*/

enum
{
    QUEST_GET_ME_OUT_OF_HERE    = 6132,

    GO_MELIZZAS_CAGE            = 177706,

    SAY_MELIZZA_START           = -1000784,
    SAY_MELIZZA_FINISH          = -1000785,
    SAY_MELIZZA_1               = -1000786,
    SAY_MELIZZA_2               = -1000787,
    SAY_MELIZZA_3               = -1000788,

    NPC_MARAUDINE_MARAUDER      = 4659,
    NPC_MARAUDINE_BONEPAW       = 4660,
    NPC_MARAUDINE_WRANGLER      = 4655,
    NPC_HORNIZ_BRIMBUZZLE       = 6019,

    NPC_MELIZZA                 = 12277,

    POINT_ID_QUEST_COMPLETE     = 1,
    POINT_ID_EVENT_COMPLETE     = 2,

    MAX_MARAUDERS               = 2,
    MAX_WRANGLERS               = 3,
};

struct SummonLocation
{
    float m_fX, m_fY, m_fZ;
};

static const SummonLocation aMarauderSpawn[] =
{
    { -1291.492f, 2644.650f, 111.556f},
    { -1306.730f, 2675.163f, 111.561f},
};

static const SummonLocation wranglerSpawn = { -1393.194f, 2429.465f, 88.689f };

struct npc_melizza_brimbuzzleAI : public npc_escortAI
{
    npc_melizza_brimbuzzleAI(Creature* m_creature) : npc_escortAI(m_creature)
    {
        Reset();
    }

    void Reset() override
    {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
        {
            m_dialogueStep = 20;
            m_dialogueTimer = 0;
        }
    }

    void JustStartedEscort() override
    {
        m_dialogueStep = 20;
        if (GameObject* pCage = GetClosestGameObjectWithEntry(m_creature, GO_MELIZZAS_CAGE, INTERACTION_DISTANCE))
            pCage->UseDoorOrButton();
    }
    uint16 m_dialogueStep;
    uint32 m_dialogueTimer;

    void WaypointReached(uint32 uiPointId) override
    {
        switch (uiPointId)
        {
            case 1:
                if (Player* pPlayer = GetPlayerForEscort())
                    DoScriptText(SAY_MELIZZA_START, m_creature, pPlayer);

                m_creature->SetFactionTemporary(FACTION_ESCORT_N_NEUTRAL_PASSIVE, TEMPFACTION_RESTORE_RESPAWN);
                break;
            case 4:
                for (uint8 i = 0; i < MAX_MARAUDERS; ++i)
                {
                    for (uint8 j = 0; j < MAX_MARAUDERS; ++j)
                    {
                        // Summon 2 Marauders on each point
                        float fX, fY, fZ;
                        m_creature->GetRandomPoint(aMarauderSpawn[i].m_fX, aMarauderSpawn[i].m_fY, aMarauderSpawn[i].m_fZ, 7.0f, fX, fY, fZ);
                        m_creature->SummonCreature(NPC_MARAUDINE_MARAUDER, fX, fY, fZ, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
                    }
                }
                break;
            case 9:
                for (uint8 i = 0; i < MAX_WRANGLERS; ++i)
                {
                    float fX, fY, fZ;
                    m_creature->GetRandomPoint(wranglerSpawn.m_fX, wranglerSpawn.m_fY, wranglerSpawn.m_fZ, 10.0f, fX, fY, fZ);
                    m_creature->SummonCreature(NPC_MARAUDINE_BONEPAW, fX, fY, fZ, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);

                    m_creature->GetRandomPoint(wranglerSpawn.m_fX, wranglerSpawn.m_fY, wranglerSpawn.m_fZ, 10.0f, fX, fY, fZ);
                    m_creature->SummonCreature(NPC_MARAUDINE_WRANGLER, fX, fY, fZ, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
                }
                break;
            case 12:
                m_dialogueStep = 6;
                SetEscortPaused(true);
                SetMaxPlayerDistance(100); //Let's not have her despawn so easily.
                if (Player* player = GetPlayerForEscort())
                    m_creature->SetFacingToObject(player);
                m_dialogueTimer = 200;
                break;
            case 19:
                m_dialogueStep = 0;
                SetEscortPaused(true);
                break;
        }
    }
    void Dialogue(const uint32 uiDiff)
    {
        if (m_dialogueStep > 6)
            return;
        if (m_dialogueTimer < uiDiff)
        {
            //sLog.nostalrius("Melizza: DialogueStep n°%u",m_dialogueStep);
            switch (m_dialogueStep)
            {
                case 0:
                    if (Creature* pHorniz = m_creature->FindNearestCreature(NPC_HORNIZ_BRIMBUZZLE, 30.0f))
                        m_creature->SetFacingToObject(pHorniz);
                    DoScriptText(SAY_MELIZZA_1, m_creature);
                    m_dialogueTimer = 4000;
                    m_dialogueStep++;
                    break;
                case 1:
                    DoScriptText(SAY_MELIZZA_2, m_creature);
                    m_dialogueTimer = 5000;
                    m_dialogueStep++;
                    break;
                case 2:
                    DoScriptText(SAY_MELIZZA_3, m_creature);
                    m_dialogueTimer = 4000;
                    m_dialogueStep++;
                    break;
                case 3:
                    SetEscortPaused(false);
                    m_dialogueTimer = 0;
                    m_dialogueStep++;
                    break;
                case 6:
                    if (Player* pPlayer = GetPlayerForEscort())
                    {
                        DoScriptText(SAY_MELIZZA_FINISH, m_creature, pPlayer);
                        pPlayer->GroupEventHappens(QUEST_GET_ME_OUT_OF_HERE, m_creature);
                    }
                    m_dialogueTimer = 2000;
                    m_dialogueStep++;
                    m_creature->ClearTemporaryFaction();
                    SetRun(true);
                    SetEscortPaused(false);
                    break;
            }
        }
        else
            m_dialogueTimer  -= uiDiff;
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        Dialogue(uiDiff);
        npc_escortAI::UpdateAI(uiDiff);
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_melizza_brimbuzzle(Creature* pCreature)
{
    return new npc_melizza_brimbuzzleAI(pCreature);
}

bool QuestAccept_npc_melizza_brimbuzzle(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_GET_ME_OUT_OF_HERE)
    {
        if (npc_melizza_brimbuzzleAI* pEscortAI = dynamic_cast<npc_melizza_brimbuzzleAI*>(pCreature->AI()))
            pEscortAI->Start(false, pPlayer->GetGUID(), pQuest);
    }

    return true;
}

/*######
## npc_dalinda_malem
######*/

enum
{
    QUEST_RETURN_TO_VAHLARRIEL  = 1440,
};

struct npc_dalinda_malemAI : public npc_escortAI
{
    npc_dalinda_malemAI(Creature* m_creature) : npc_escortAI(m_creature)
    {
        Reset();
    }

    void Reset() override {}

    void JustStartedEscort() override
    {
        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
    }

    void WaypointReached(uint32 uiPointId) override
    {
        if (uiPointId == 18)
        {
            if (Player* pPlayer = GetPlayerForEscort())
                pPlayer->GroupEventHappens(QUEST_RETURN_TO_VAHLARRIEL, m_creature);
        }
    }
};

CreatureAI* GetAI_npc_dalinda_malem(Creature* pCreature)
{
    return new npc_dalinda_malemAI(pCreature);
}

bool QuestAccept_npc_dalinda_malem(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_RETURN_TO_VAHLARRIEL)
    {
        if (npc_dalinda_malemAI* pEscortAI = dynamic_cast<npc_dalinda_malemAI*>(pCreature->AI()))
        {
            // TODO This faction change needs confirmation, also possible that we need to drop her PASSIVE flag
            pCreature->SetFactionTemporary(FACTION_ESCORT_A_NEUTRAL_PASSIVE, TEMPFACTION_RESTORE_RESPAWN);//TEMPFACTION_RESTORE_RESPAWN | TEMPFACTION_TOGGLE_PASSIVE
            pEscortAI->Start(false, pPlayer->GetGUID(), pQuest);
        }
    }
    return true;
}
enum
{
//guid 12609 entry 177673 Serpant statue
    NPC_LORD_KRAGARU            = 12369,
    QUEST_BOOK_OF_THE_ANCIENTS  = 6027

};
struct go_serpent_statueAI: public GameObjectAI
{
    go_serpent_statueAI(GameObject* pGo) : GameObjectAI(pGo)
    {
        timer = 0;
        state = 0;
        guid_kragaru = 0;
    }
    uint64 guid_kragaru;
    uint32 timer;
    bool state;//0 = usual, can launch. //1 = in use, cannot launch

    void UpdateAI(const uint32 uiDiff)
    {
        if (state)
        {
            if (timer < uiDiff)
            {
                state = 0;
                me->SetGoState(GO_STATE_READY);
                me->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
            }
            else
                timer -= uiDiff;
        }
    }
    bool CheckCanStartEvent()
    {
        if (!state && !me->GetMap()->GetCreature(guid_kragaru))
            return true;
        return false;
    }

    void SetInUse(Creature* kragaru)
    {
        guid_kragaru = kragaru->GetGUID();
        me->SetGoState(GO_STATE_ACTIVE);
        me->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_IN_USE);
        state = 1;
        timer = 120000;
    }
};
GameObjectAI* GetAIgo_serpent_statue(GameObject *pGo)
{
    return new go_serpent_statueAI(pGo);
}
bool GOHello_go_serpent_statue(Player* pPlayer, GameObject* pGo)
{
    if (go_serpent_statueAI* pMarkAI = dynamic_cast<go_serpent_statueAI*>(pGo->AI()))
    {
        if (pMarkAI->CheckCanStartEvent())
        {
            if (pGo->GetGoType() == GAMEOBJECT_TYPE_BUTTON)
            {
                if (pPlayer->GetQuestStatus(QUEST_BOOK_OF_THE_ANCIENTS) == QUEST_STATUS_INCOMPLETE)
                {
                    if (Creature* kragaru = pGo->SummonCreature(NPC_LORD_KRAGARU, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 310000))
                    {
                        kragaru->SetRespawnDelay(350000);
                        pMarkAI->SetInUse(kragaru);
                    }
                }
            }
        }
    }
    return true;
}
enum
{
    NPC_MAGRAMI_SPECTRE                 = 11560,
    GO_GHOST_MAGNET                     = 177746,
    GO_GHOST_MAGNET_AURA                = 177749,
    SPELL_CURSE_OF_THE_FALLEN_MAGRAM    = 18159,
    SPELL_PLACE_GHOST_MAGNET            = 19588,
    SPELL_DESTROY_MAGNET                = 19571,//not used maybe.
    SPELL_BLUE_AURA                     = 17327,//neutral, walk to target
    SPELL_GREEN_AURA                    = 18951, //aura becomes green once they get to magnet. and aggressive
    FACTION_NEUTRAL                     = 634, //or 58
    FACTION_ENNEMY                      = 16
};

void DefineMagramiMagnet(Creature * crea, uint64 gobjGUID);

struct go_ghost_magnetAI: public GameObjectAI
{
    go_ghost_magnetAI(GameObject* pGo) : GameObjectAI(pGo)
    {
        bigTimer = 120000;
        timer = 5000;
        nbToSpawn = 8;

        state = 1;
        std::list<GameObject*> lGobj;
        me->GetGameObjectListWithEntryInGrid(lGobj, GO_GHOST_MAGNET_AURA, 30.0f);
        for (std::list<GameObject*>::iterator it = lGobj.begin(); it != lGobj.end(); ++it)
        {
            if ((*it)->isSpawned())
            {
                state = 0;
                break;
            }
        }
        if (state)
        {
            float mx, my, mz;
            me->GetPosition(mx, my, mz);
            me->SummonGameObject(GO_GHOST_MAGNET_AURA, mx, my, mz, 0, 0, 0, 0, 0, 120);//120sec to go with the 12000 spectre spawn
        }
    }
    uint32 timer;
    uint32 bigTimer;
    uint16 nbToSpawn;
    bool state;//0 = already are functioning magnets, do not spawn spectre. //1 = spawning.

    void UpdateAI(const uint32 uiDiff)
    {
        if (state)
        {
            if (bigTimer < uiDiff)
            {
                state=0;
            }
            else
                bigTimer -= uiDiff;
            if(nbToSpawn>0)
            {
                if (timer < uiDiff)
                {
                    spawnSpetre();
                    timer = urand(3000, 8000);
                    --nbToSpawn;
                }
                else
                    timer -= uiDiff;
            }
        }
    }

    void spawnSpetre()
    {
        float x, y, z;
        float mx, my, mz;
        me->GetPosition(mx, my, mz);
        me->GetRandomPoint(mx,my,mz, 40, x, y, z);
        if(Creature* spectre=me->SummonCreature(NPC_MAGRAMI_SPECTRE, x, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000))
        {
            spectre->SetRespawnDelay(425000);
            DefineMagramiMagnet(spectre, me->GetGUID());
        }
    }
    void MagramiSpectreDied(uint64 guid)
    {
        if (state)
            spawnSpetre();
    }
};
GameObjectAI* GetAIgo_ghost_magnet(GameObject *pGo)
{
    return new go_ghost_magnetAI(pGo);
}
struct npc_magrami_spetreAI : public ScriptedAI
{
    npc_magrami_spetreAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        isGreen = false;
        guidMagnet = 0;
        corpseTimer = 20000;
        Reset();
    }
    void Reset()
    {
        timer=0;
        curseTimer = urand(5000, 9000);
        if(isGreen)
             m_creature->AddAura(SPELL_GREEN_AURA);
        else
             m_creature->AddAura(SPELL_BLUE_AURA);
    }
    uint32 corpseTimer;
    uint32 timer;
    uint32 curseTimer;
    uint64 guidMagnet;
    bool isGreen;

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if(isGreen)
            return;
        if (uiType != POINT_MOTION_TYPE || uiPointId!=2)
            return;
        turnGreen();
    }
    void JustReachedHome()
    {
        if(!isGreen)
            turnGreen();
    }
    void turnGreen()
    {
        m_creature->RemoveAurasDueToSpell(SPELL_BLUE_AURA);
        m_creature->AddAura(SPELL_GREEN_AURA);
        m_creature->setFaction(FACTION_ENNEMY);
        isGreen=true;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if ( curseTimer < uiDiff)
        {
            if(m_creature->getVictim()->HasAura(SPELL_CURSE_OF_THE_FALLEN_MAGRAM))
                curseTimer = 5000;
            else
            {
                if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CURSE_OF_THE_FALLEN_MAGRAM) == CAST_OK)
                    curseTimer = urand(15000, 21000);
            }
        }
        else
            curseTimer -= uiDiff;
        DoMeleeAttackIfReady();
    }
    void UpdateAI_corpse(const uint32 uiDiff)
    {
        if ( corpseTimer < uiDiff)//purpose is to delay the new spawn.
        {
            if(GameObject* gobj=m_creature->GetMap()->GetGameObject(guidMagnet))
            {
                if (go_ghost_magnetAI* pMoundAI = dynamic_cast<go_ghost_magnetAI*>(gobj->AI()))
                {
                    pMoundAI->MagramiSpectreDied(m_creature->GetGUID());
                }
            }
            corpseTimer=150000;//after despawn.
        }
        else
            corpseTimer -= uiDiff;
    }
    void SetMagnetGuid(uint64 ghostMagnetGuid)
    {
        if (GameObject* gobj = m_creature->GetMap()->GetGameObject(ghostMagnetGuid))
        {
            float x,y,z;

            gobj->GetContactPoint(m_creature, x, y, z, 1);
            m_creature->SetHomePosition(x, y, z, 0);
            m_creature->GetMotionMaster()->MovePoint(2, x, y, z, MOVE_PATHFINDING);
            guidMagnet=ghostMagnetGuid;
        }
    }
};

CreatureAI* GetAI_npc_magrami_spetre(Creature* pCreature)
{
    return new npc_magrami_spetreAI(pCreature);
}
void DefineMagramiMagnet(Creature * crea, uint64 gobjGUID)
{
    if (npc_magrami_spetreAI* spectreAI = dynamic_cast<npc_magrami_spetreAI*>(crea->AI()))
    {
        spectreAI->SetMagnetGuid(gobjGUID);
    }
}

enum
{
    NPC_PORTAL_DEMON_DEMON  = 11937,
};

struct go_demon_portalAI: public GameObjectAI
{
    go_demon_portalAI(GameObject* pGo) : GameObjectAI(pGo)
    {
    }
    ObjectGuid _demonGuid;
    bool OnUse(Unit* caster)
    {
        Unit* demon;
        if (_demonGuid)
        {
            demon = me->GetMap()->GetCreature(_demonGuid);
            if (demon && demon->isAlive())
                return true;
        }
        demon = me->SummonCreature(NPC_PORTAL_DEMON_DEMON, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), caster ? me->GetAngle(caster) : 0.0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000);
        if (demon)
        {
            _demonGuid = demon->GetObjectGuid();
            if (caster)
                demon->AI()->AttackStart(caster);
        }
        return true;
    }
    
    void UpdateAI(uint32 const /*uiDiff*/)
    {
        if (Unit* l_Demon = me->GetMap()->GetCreature(_demonGuid))
        {
            if (!l_Demon->isAlive())
            {
                me->Despawn();
                me->DestroyForNearbyPlayers();
                _demonGuid = 0;
            }
        }
    }
};

GameObjectAI* GetAI_go_demon_portal(GameObject *go)
{
    return new go_demon_portalAI(go);
}

/*
 * Gizelton Caravan, Bodyguard For Hire support
 */

struct GizeltonStruct
{
    int32 onLeave, onAnnounce, onAmbush0, onAmbush1, onAmbush2, onComplete;
};

const GizeltonStruct CaravanTalk[] = 
{
    { -1001000, -1001001, -1001002, -1001003, -1001004, -1001005 },
    { -1001006, -1001007, -1001008, -1001009, -1001010, -1001011 }
};

enum
{
    NPC_RIGGER_GIZELTON     = 11626,
    NPC_CORK_GIZELTON       = 11625,
    NPC_SUPER_SELLER_680    = 12246,
    NPC_VENDOR_TRON_1000    = 12245,
    NPC_CARAVAN_KODO        = 11564,
    NPC_DOOMWARDER          = 4677,
    NPC_NETHER_SORCERESS    = 4684,
    NPC_LESSER_INFERNAL     = 4676,
    NPC_KOLKAR_AMBUSHER     = 12977,
    NPC_KOLKAR_WAYLAYER     = 12976,

    POINT_BOT_CAMP          = 279,
    POINT_BOT_ANNOUNCE      = 14,
    POINT_BOT_AMBUSH_0      = 28,
    POINT_BOT_AMBUSH_1      = 34,
    POINT_BOT_AMBUSH_2      = 40,
    POINT_BOT_COMPLETE      = 42,

    POINT_TOP_CAMP          = 141,
    POINT_TOP_ANNOUNCE      = 164,
    POINT_TOP_AMBUSH_0      = 173,
    POINT_TOP_AMBUSH_1      = 181,
    POINT_TOP_AMBUSH_2      = 188,
    POINT_TOP_COMPLETE      = 195,
    POINT_END               = 281,

    QUEST_BOTTOM            = 5943,
    QUEST_TOP               = 5821,
};

struct Coords
{
    uint32 entry;
    float x, y, z, o;
};

struct Formation
{
    float distance, angle;
};

const Coords Ambusher[] = 
{
    { NPC_DOOMWARDER,       -1814.41f, 1983.18f, 58.9549f, 0.0f },
    { NPC_NETHER_SORCERESS, -1814.41f, 1983.18f, 58.9549f, 0.0f },
    { NPC_LESSER_INFERNAL,  -1814.41f, 1983.18f, 58.9549f, 0.0f },

    { NPC_DOOMWARDER,       -1751.9f, 1917.2f, 59.0003f, 0.0f },
    { NPC_NETHER_SORCERESS, -1751.9f, 1917.2f, 59.0003f, 0.0f },
    { NPC_LESSER_INFERNAL,  -1751.9f, 1917.2f, 59.0003f, 0.0f },

    { NPC_DOOMWARDER,       -1684.12f, 1872.66f, 59.0354f, 0.0f },
    { NPC_NETHER_SORCERESS, -1684.12f, 1872.66f, 59.0354f, 0.0f },
    { NPC_LESSER_INFERNAL,  -1684.12f, 1872.66f, 59.0354f, 0.0f },

    { NPC_KOLKAR_AMBUSHER,  -792.515f, 1177.07f, 98.8327f, 0.0f },
    { NPC_KOLKAR_WAYLAYER,  -792.515f, 1177.07f, 98.8327f, 0.0f },

    { NPC_KOLKAR_AMBUSHER,  -931.15f, 1182.17f, 91.8346f, 0.0f },
    { NPC_KOLKAR_WAYLAYER,  -931.15f, 1182.17f, 91.8346f, 0.0f },

    { NPC_KOLKAR_AMBUSHER,  -1073.62f, 1186.33f, 89.7398f, 0.0f },
    { NPC_KOLKAR_WAYLAYER,  -1073.62f, 1186.33f, 89.7398f, 0.0f }
};

const Coords Caravan[] = 
{
    { NPC_CARAVAN_KODO,     -1887.26f, 2465.12f, 59.8224f, 4.48f },
    { NPC_RIGGER_GIZELTON,  -1883.63f, 2471.68f, 59.8224f, 4.48f },
    { NPC_CARAVAN_KODO,     -1882.11f, 2476.80f, 59.8224f, 4.48f }
};

const Formation CaravanFormation[] =
{
    { 32.0f, 6.28f },
    { 26.0f, 3.14f },
    { 18.0f, 3.14f },
    { 8.0f,  3.14f }
};

struct npc_cork_gizeltonAI : npc_escortAI
{
    explicit npc_cork_gizeltonAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        npc_cork_gizeltonAI::Reset();
        npc_cork_gizeltonAI::ResetCreature();
    }

    std::list<ObjectGuid> m_lCaravanGuid;
    ObjectGuid m_currentGuid;
    ObjectGuid m_RiggerGuid;
    ObjectGuid m_playerGuid;
    uint8 m_uiEnemiesCount;
    uint8 m_uiAnnounceCount;
    uint32 m_uiInitDelayTimer;
    uint32 m_uiCampTimer;
    uint32 m_uiAnnounceTimer;
    uint32 m_uiDepartTimer;
    bool m_bInit;
    bool m_bCamp;
    bool m_bWaitingForPlayer;
    bool m_bWaitingForDepart;
    bool m_bRigger;

    void Reset() override
    {

    }

    void ResetCreature() override
    {
        m_lCaravanGuid.clear();
        m_currentGuid.Clear();
        m_RiggerGuid.Clear();
        m_playerGuid.Clear();
        m_uiEnemiesCount = 0;
        m_uiAnnounceCount = 0;
        m_uiInitDelayTimer = 2000;
        m_uiCampTimer = 10 * MINUTE * IN_MILLISECONDS;
        m_uiDepartTimer = MINUTE * IN_MILLISECONDS;
        m_uiAnnounceTimer = 0;
        m_bInit = false;
        m_bCamp = false;
        m_bWaitingForPlayer = false;
        m_bWaitingForDepart = false;
        m_bRigger = true;
    }

    void SummonCaravan()
    {
        m_lCaravanGuid.push_back(m_creature->GetObjectGuid());
        AddToFormation(m_creature, 0);

        for (uint8 i = 0; i < 3; ++i)
        {
            if (auto pCreature = m_creature->SummonCreature(Caravan[i].entry,
                Caravan[i].x,
                Caravan[i].y,
                Caravan[i].z,
                Caravan[i].o, TEMPSUMMON_DEAD_DESPAWN, 30000, true))
            {
                AddToFormation(pCreature, i + 1);
            }
            else
            {
                sLog.outError("[Desolace.GizeltonCaravan] Failed to summon caravan. Self-despawn.");
                DespawnCaravan();
            }
        }
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        FailEscort();
    }

    void FailEscort()
    {
        if (auto pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid))
            pPlayer->FailQuest(m_bRigger ? QUEST_BOTTOM : QUEST_TOP);

        DespawnCaravan();
    }

    void DespawnCaravan()
    {
        for (auto itr = m_lCaravanGuid.begin(); itr != m_lCaravanGuid.end(); ++itr)
        {
            if (*itr != m_creature->GetObjectGuid())
            {
                if (auto pKillMe = m_creature->GetMap()->GetCreature(*itr))
                    pKillMe->RemoveFromWorld();
            }
        }

        m_creature->ForcedDespawn();
    }

    void CaravanFaction(bool apply)
    {
        for (auto itr = m_lCaravanGuid.begin(); itr != m_lCaravanGuid.end(); ++itr)
        {
            if (*itr != m_creature->GetObjectGuid())
            {
                if (auto pCreature = m_creature->GetMap()->GetCreature(*itr))
                    if (apply)
                        pCreature->SetFactionTemporary(FACTION_ESCORT_N_NEUTRAL_PASSIVE, TEMPFACTION_NONE);
                    else
                        pCreature->ClearTemporaryFaction();
            }
        }

        if (apply)
            m_creature->SetFactionTemporary(FACTION_ESCORT_N_NEUTRAL_PASSIVE, TEMPFACTION_NONE);
        else
            m_creature->ClearTemporaryFaction();
    }

    void SummonAmbusher(uint8 index) const
    {
        float x = Ambusher[index].x;
        float y = Ambusher[index].y;
        float z = Ambusher[index].z;

        for (uint8 i = 0; i < 5; ++i)
        {
            if (m_creature->GetMap()->GetWalkRandomPosition(nullptr, x, y, z, 20.0f, NAV_GROUND))
                break;
        }

        m_creature->SummonCreature(Ambusher[index].entry, x, y, z, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
    }

    void Ambush(uint8 index) const
    {
        switch (index)
        {
        case POINT_BOT_AMBUSH_0:
            SummonAmbusher(0);
            SummonAmbusher(1);
            SummonAmbusher(2);
            DoTalk(CaravanTalk[0].onAmbush0);
            break;
        case POINT_BOT_AMBUSH_1:
            SummonAmbusher(3);
            SummonAmbusher(4);
            SummonAmbusher(5);
            DoTalk(CaravanTalk[0].onAmbush1);
            break;
        case POINT_BOT_AMBUSH_2:
            SummonAmbusher(6);
            SummonAmbusher(7);
            SummonAmbusher(8);
            DoTalk(CaravanTalk[0].onAmbush2);
            break;
        case POINT_TOP_AMBUSH_0:
            SummonAmbusher(9);
            SummonAmbusher(10);
            SummonAmbusher(9);
            SummonAmbusher(10);
            DoTalk(CaravanTalk[1].onAmbush0);
            break;
        case POINT_TOP_AMBUSH_1:
            SummonAmbusher(11);
            SummonAmbusher(12);
            SummonAmbusher(11);
            SummonAmbusher(12);
            DoTalk(CaravanTalk[1].onAmbush1);
            break;
        case POINT_TOP_AMBUSH_2:
            SummonAmbusher(13);
            SummonAmbusher(14);
            SummonAmbusher(13);
            SummonAmbusher(14);
            DoTalk(CaravanTalk[1].onAmbush2);
            break;
        }
    }

    void AddToFormation(Creature* pWho, uint8 index) const
    {
        pWho->JoinCreatureGroup(m_creature, CaravanFormation[index].distance, CaravanFormation[index].angle,
            OPTION_FORMATION_MOVE | OPTION_AGGRO_TOGETHER);
    }

    void JustSummoned(Creature* pSummoned) override
    {
        switch (pSummoned->GetEntry())
        {
        case NPC_RIGGER_GIZELTON:
            m_RiggerGuid = pSummoned->GetObjectGuid();
            m_currentGuid = m_RiggerGuid;
        case NPC_CARAVAN_KODO:
            m_lCaravanGuid.push_back(pSummoned->GetObjectGuid());
            return;
        }

        ++m_uiEnemiesCount;

        // pick random caravan target
        uint8 targetIndex = urand(0, 3);

        if (!targetIndex)
            pSummoned->AI()->AttackStart(m_creature);
        else
        {
            if (m_lCaravanGuid.size() > targetIndex)
            {
                auto itr = m_lCaravanGuid.begin();
                std::advance(itr, targetIndex);

                if (auto pCreature = m_creature->GetMap()->GetCreature(*itr))
                    pSummoned->AI()->AttackStart(pCreature);
            }            
        }       
    }

    void SummonedCreatureJustDied(Creature* pSummoned) override
    {
        switch (pSummoned->GetEntry())
        {
        case NPC_RIGGER_GIZELTON:
        case NPC_CARAVAN_KODO:
            FailEscort();
            return;
        }

        --m_uiEnemiesCount;

        if (!m_uiEnemiesCount)
            SetEscortPaused(false);
    }

    void PlayerHere(Player* pPlayer)
    {
        m_bWaitingForPlayer = false;
        m_bWaitingForDepart = true;
        m_uiAnnounceCount = 0;
        m_playerGuid = pPlayer->GetObjectGuid();
        GiveQuest(false);
    }

    void DoTalk(int32 textId, bool yell = false) const
    {
        auto pTalker = m_bRigger ? m_creature->GetMap()->GetCreature(m_RiggerGuid) : m_creature;

        if (pTalker)
        {
            if (yell)
                pTalker->MonsterYellToZone(textId);
            else
                pTalker->MonsterSay(textId);
        }
    }

    void GiveQuest(bool give) const
    {
        auto pGiver = m_bRigger ? m_creature->GetMap()->GetCreature(m_RiggerGuid) : m_creature;

        if (pGiver)
        {
            if (give)
                pGiver->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            else
                pGiver->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        }
    }

    void CaravanWalk(bool walk) const
    {
        auto pLeader = m_bRigger ? m_creature->GetMap()->GetCreature(m_RiggerGuid) : m_creature;

        if (pLeader)
            pLeader->SetWalk(walk);
    }

    void DoVendor(bool visible) const
    {
        auto pVendor = m_creature->FindNearestCreature(m_bRigger ? NPC_SUPER_SELLER_680 : NPC_VENDOR_TRON_1000, 100.0f);

        if (pVendor)
        {
            pVendor->SetVisibility(visible ? VISIBILITY_ON : VISIBILITY_OFF);
        }
    }

    void WaypointReached(uint32 uiPoint) override
    {
        switch (uiPoint)
        {
        case POINT_BOT_CAMP:
        case POINT_TOP_CAMP:
            SetEscortPaused(true);
            CaravanWalk(true);
            m_uiCampTimer = 10 * MINUTE * IN_MILLISECONDS;
            m_bCamp = true;
            DoVendor(true);
            break;
        case POINT_BOT_ANNOUNCE:
        case POINT_TOP_ANNOUNCE:
            SetEscortPaused(true);
            GiveQuest(true);
            m_uiAnnounceTimer = 0;
            m_uiDepartTimer = 10 * IN_MILLISECONDS;
            m_bWaitingForPlayer = true;
            break;
        case POINT_BOT_AMBUSH_0:
        case POINT_BOT_AMBUSH_1:
        case POINT_BOT_AMBUSH_2:
        case POINT_TOP_AMBUSH_0:
        case POINT_TOP_AMBUSH_1:
        case POINT_TOP_AMBUSH_2:
            SetEscortPaused(true);
            Ambush(uiPoint);
            break;
        case POINT_BOT_COMPLETE:           
        case POINT_TOP_COMPLETE:
            {
            DoTalk(CaravanTalk[m_bRigger ? 0 : 1].onComplete);

            if (auto pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid))
            {
                if (pPlayer->IsInRange(m_creature, 0.0f, 100.0f))
                    pPlayer->GroupEventHappens(m_bRigger ? QUEST_BOTTOM : QUEST_TOP, m_creature);                
            }

            CaravanFaction(false);
            CaravanWalk(false);
            m_bRigger = !m_bRigger;
            }
            break;
        case POINT_END:
            DespawnCaravan();
            break;
        }
    }

    void UpdateEscortAI(uint32 const uiDiff) override
    {
        // just summoned, do init
        if (!m_bInit)
        {
            if (m_uiInitDelayTimer < uiDiff)
            {
                SummonCaravan();
                m_bInit = true;
                Start();
            }
            else
                m_uiInitDelayTimer -= uiDiff;

            return;
        }

        // caravan is at camp point, vendor is available
        if (m_bCamp)
        {
            if (m_uiCampTimer < uiDiff)
            {
                m_bCamp = false;
                DoTalk(CaravanTalk[m_bRigger ? 0 : 1].onLeave);
                DoVendor(false);
                SetEscortPaused(false);
            }
            else
                m_uiCampTimer -= uiDiff;

            return;
        }

        // caravan is at waiting point, announcing every 3 minutes
        if (m_bWaitingForPlayer)
        {
            if (m_uiAnnounceTimer < uiDiff)
            {
                ++m_uiAnnounceCount;

                // caravan stays for 15+ minutes waiting for help
                if (m_uiAnnounceCount > 5)
                    DespawnCaravan();

                DoTalk(CaravanTalk[m_bRigger ? 0 : 1].onAnnounce, true);
                m_uiAnnounceTimer = 3 * MINUTE * IN_MILLISECONDS;
            }
            else
                m_uiAnnounceTimer -= uiDiff;

            return;
        }

        // player is here, 10 seconds more and caravan goes
        if (m_bWaitingForDepart)
        {
            if (m_uiDepartTimer < uiDiff)
            {
                m_bWaitingForDepart = false;
                CaravanFaction(true);
                SetEscortPaused(false);
            }
            else
                m_uiDepartTimer -= uiDiff;

            return;
        }

        npc_escortAI::UpdateEscortAI(uiDiff);
    }
};

CreatureAI* GetAI_npc_cork_gizelton(Creature* pCreature)
{
    return new npc_cork_gizeltonAI(pCreature);
}

bool QuestAccept_npc_cork_gizelton(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_TOP)
    {
        if (auto pCorkAI = dynamic_cast<npc_cork_gizeltonAI*>(pCreature->AI()))
            pCorkAI->PlayerHere(pPlayer);
    }

    return true;
}

bool QuestAccept_npc_rigger_gizelton(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_BOTTOM)
    {
        if (auto pCork = pCreature->FindNearestCreature(NPC_CORK_GIZELTON, 100.0f))
        {
            if (auto pCorkAI = dynamic_cast<npc_cork_gizeltonAI*>(pCork->AI()))
                pCorkAI->PlayerHere(pPlayer);
        }
    }

    return true;
}

/*
 * Vendor-Tron 1000, Super-Seller 680 (Gizelton Caravan, Bodyguard For Hire support)
 */

struct npc_caravan_vendorAI : ScriptedAI
{
    explicit npc_caravan_vendorAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        npc_caravan_vendorAI::Reset();
        
        m_creature->SetVisibility(VISIBILITY_OFF);
    }

    void Reset() override
    {

    }
};

CreatureAI* GetAI_npc_caravan_vendor(Creature* pCreature)
{
    return new npc_caravan_vendorAI(pCreature);
}

/*
 *
 */

void AddSC_desolace()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_aged_dying_ancient_kodo";
    newscript->GetAI = &GetAI_npc_aged_dying_ancient_kodo;
    newscript->pGossipHello = &GossipHello_npc_aged_dying_ancient_kodo;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_hand_of_iruxos_crystal";
    newscript->pGOHello = &GOHello_go_hand_of_iruxos_crystal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_melizza_brimbuzzle";
    newscript->GetAI = &GetAI_npc_melizza_brimbuzzle;
    newscript->pQuestAcceptNPC = &QuestAccept_npc_melizza_brimbuzzle;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_dalinda_malem";
    newscript->GetAI = &GetAI_npc_dalinda_malem;
    newscript->pQuestAcceptNPC = &QuestAccept_npc_dalinda_malem;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_serpent_statue";
    newscript->GOGetAI = &GetAIgo_serpent_statue;
    newscript->pGOHello = &GOHello_go_serpent_statue;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_ghost_magnet";
    newscript->GOGetAI = &GetAIgo_ghost_magnet;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_magrami_spetre";
    newscript->GetAI = &GetAI_npc_magrami_spetre;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_demon_portal";
    newscript->GOGetAI = &GetAI_go_demon_portal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_cork_gizelton";
    newscript->GetAI = &GetAI_npc_cork_gizelton;
    newscript->pQuestAcceptNPC = &QuestAccept_npc_cork_gizelton;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_rigger_gizelton";
    newscript->pQuestAcceptNPC = &QuestAccept_npc_rigger_gizelton;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_caravan_vendor";
    newscript->GetAI = &GetAI_npc_caravan_vendor;
    newscript->RegisterSelf();
}
