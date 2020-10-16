/*
 * Copyright (C) 2010-2016 Anathema Script Engine project <http://valkyrie-wow.com/>
 * Copyright (C) 2006-2014 ScriptDev2 <http://www.scriptdev2.com/>
 */

#pragma once

#include "scriptPCH.h"
#include <array>

enum
{
    QUEST_COUNTERATTACK         = 4021,

    SAY_EVENT_START             = -1000643,
    SAY_DEFENDER_FALLEN         = -1000644,
    SAY_DEFEND_BUNKERS          = -1000645,
    SAY_SPAWN                   = -1000646,
    SAY_FOES_FALL               = -1000647,
    SAY_FOR_THE_HORDE           = -1000648,
    SAY_EVENT_END               = -1000649,

    NPC_INVISIBLE_TRIGGER_ONE   = 14495,
    NPC_WARLORD_KROMZAR         = 9456,
    NPC_HORDE_DEFENDER          = 9457,
    NPC_HORDE_AXE_THROWER       = 9458,
    NPC_KOLKAR_STORMSEER        = 9523,
    NPC_KOLKAR_INVADER          = 9524,
    NPC_LANTI_GAH               = 9990,

    GO_SMOKE_EMITTER            = 164870,
    GO_BIG_FLAME                = 176746,
    GO_SMALL_FLAME              = 176747,

    SPELL_STRIKE                = 11976,
    SPELL_KROMZAR_BANNER        = 13965,
    SPELL_FLING_TORCH           = 14292,

    MAX_DEFENDERS               = 5,
    MAX_ATTACKERS               = 12,
    MAX_SPAWNRANGE_ATTACKERS    = 60,
    MAX_SPAWNRANGE_DEFENDERS    = 15
};

#define GOSSIP_ITEM_REGTHAR   "Where is Warlord Krom'zar?"

struct SummonLocation
{
    float m_fX, m_fY, m_fZ, m_fO;
};

static const SummonLocation aSummonLocations[] = 
{
    {-317.47f, -1828.39f, 96.198914f, 5.339108f},   // Warlord Krom'zar rush from position
    {-307.16f, -1971.95f, 96.396935f, 0.0f},        // Regthar Deathgate
    {-290.07f, -1857.47f, 92.492996f, 4.994370f},   // Warlord Krom'zar
    {-298.09f, -1843.92f, 93.508827f, 4.592978f},   // Enemy Spawn point
    {-287.49f, -1907.47f, 91.666824f, 1.549561f},   // Friendly Spawn point
    {-317.42f, -1898.82f, 91.721024f, 3.473787f},   // Lanti'gah work position
    {-323.84f, -1861.82f, 94.236595f, 4.501592f},   // Throw torch 1
    {-274.76f, -1851.94f, 93.128578f, 5.569736f}    // Throw torch 2
};

static const SummonLocation aGOSummonLocations[] = 
{
    {-339.0f, -1896.0f, 107.017f, -2.0f},           // Smokes
    {-331.0f, -1889.0f, 105.352f, 0.541f},
    {-255.0f, -1878.0f, 93.256f, -2.0f},
    {-250.0f, -1868.0f, 93.291f, 2.845f},
    {-241.0f, -1880.0f, 94.031f, -3.0f},
    //{-340.0f, -1896.0f, 103.064f, 0.14f},           // Big flame
    {-336.0f, -1892.0f, 107.946f, 1.553f},          // Small flames
    {-324.0f, -1901.0f, 105.747f, 0.105f},
    {-252.0f, -1872.0f, 94.82f, -2.0f},
    {-240.0f, -1880.0f, 94.067f, 2.635f}
};

/*######
## npc_warlord_kromzar
######*/

struct npc_warlord_kromzarAI : public ScriptedAI
{
    npc_warlord_kromzarAI(Creature* pCreature);

    uint32 m_uiHardEventTimer;
    uint32 m_uiCheckResummonsTimer;
    uint32 m_uiTorchTimer;
    uint32 m_uiStrikeTimer;
    uint32 m_uiKillCount;
    uint32 m_uiDefenderCount;
    uint32 m_uiAttackerCount;
    uint32 m_uiSummonEntry;

    bool m_bInitial;
    bool m_bStarted;

    ObjectGuid m_uiTriggerOneGUID;
    GuidList m_lGameobjects;
    GuidList m_lDefenders;
    GuidList m_lKolkars;

    void Reset() override;
    void JustDied(Unit* pKiller) override;
    void JustSummoned(Creature* pSummoned) override;
    void JustSummoned(GameObject* pSummoned) override;
    void SummonedCreatureJustDied(Creature* pSummoned) override;
    void SummonedMovementInform(Creature* pSummoned, uint32 uiMotionType, uint32 uiPointId) override;
    void SummonGameobjects();
    void SummonDefenders();
    void SummonAttackers();
    void TryJoinFight();
    void EndEvent();
    void UpdateAI(const uint32 diff);
};
