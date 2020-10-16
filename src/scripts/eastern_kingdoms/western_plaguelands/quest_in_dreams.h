/*
 * Copyright (C) 2010-2016 Anathema Script Engine project <http://valkyrie-wow.com/>
 * Copyright (C) 2006-2014 ScriptDev2 <http://www.scriptdev2.com/>
 */

#pragma once

#include "scriptPCH.h"
#include <array>

enum
{
    QUEST_SCARLET_SUBTERFUGE    = 5862,
    QUEST_IN_DREAMS             = 5944,
    
    NPC_TAELAN                  = 1842,
    NPC_CAVALIER                = 1836,
    NPC_ISILLIEN                = 1840,
    NPC_CRIMSON                 = 12128,
    NPC_TIRION                  = 12126,

    FIRST_CAVALIER_GUID         = 48190,
    SECOND_CAVALIER_GUID        = 48188,
    THIRD_CAVALIER_GUID         = 49594,
    FOURTH_CAVALIER_GUID        = 52005,

    SAY_CAVALIER_1              = -1532000,
    SAY_CAVALIER_2              = -1532001,
    SAY_CAVALIER_3              = -1532002,
    SAY_CAVALIER_4              = -1532003,
    SAY_CAVALIER_5              = -1532004,
    SAY_CAVALIER_6              = -1532005,
    SAY_CAVALIER_7              = -1532006,
    SAY_CAVALIER_8              = -1532007,
    SAY_TAELAN_NOO              = -1532008,
    SAY_TAELAN_1                = -1532009,
    SAY_TAELAN_2                = -1532010,
    SAY_TAELAN_3                = -1532011,
    EMOTE_TAELAN_1              = -1532012,
    SAY_TAELAN_4                = -1532013,
    SAY_TAELAN_5                = -1532014,
    SAY_TAELAN_6                = -1532015,
    SAY_ISILLIEN_1              = -1532016,
    SAY_ISILLIEN_2              = -1532017,
    SAY_ISILLIEN_3              = -1532018,
    SAY_ISILLIEN_4              = -1532019,
    EMOTE_ISILLIEN_1            = -1532020,
    SAY_ISILLIEN_5              = -1532021,
    SAY_ISILLIEN_6              = -1532022,
    SAY_ISILLIEN_7              = -1532023,
    SAY_TIRION_1                = -1532024,
    SAY_ISILLIEN_8              = -1532025,
    SAY_TIRION_2                = -1532026,
    SAY_TIRION_3                = -1532027,
    SAY_ISILLIEN_9              = -1532028,
    SAY_TIRION_4                = -1532029,
    SAY_TIRION_5                = -1532030,
    SAY_TIRION_6                = -1532031,
    SAY_TIRION_7                = -1532032,
    SAY_TIRION_8                = -1532033,

    TAELAN_MOUNT                = 2402,
    TIRION_MOUNT                = 2404,

    // Taelan's Spells
    SPELL_DEVOTION_AURA         = 17232,
    SPELL_HOLY_LIGHT            = 15493,
    SPELL_MURDER                = 14158,
    SPELL_HOLY_CLEAVE           = 18819,
    SPELL_TAELAN_SUFFERING      = 18810,
    SPELL_LAY_ON_HANDS          = 633,

    // Cavalierses Spells
    SPELL_BACKHAND              = 6253,
    SPELL_CLEAVE                = 15284,
    SPELL_MORTAL_STRIKE         = 16856,

    // Isillien's spells
    SPELL_DOMINATE_MIND         = 20604,
    SPELL_MANA_BURN             = 15800,
    SPELL_MIND_BLAST            = 17194,
    SPELL_MIND_FLAY             = 17165,
    SPELL_FLASH_HEAL            = 10917,
    SPELL_GREATER_HEAL          = 10965,
    SPELL_POWER_SHIELD          = 10901,
    SPELL_TAELAN_DEATH          = 18969,

    // Tirion Spells
    SPELL_CRUSADER_STRIKE       = 14518,
    SPELL_HOLY_STRIKE           = 17143,

    // Crimson Elite Spells
    SPELL_RETRIBUTION_AURA      = 8990,

    SPELL_DISGUISE              = 17961,
};

struct SpawnCoordsStruct
{
    float x, y, z, o;
};

static const SpawnCoordsStruct SpawnCoordsIsillien =
{
    2686.4042f, -1932.2364f, 72.1442f, 2.13f
};

static const SpawnCoordsStruct SpawnCoordsTirion =
{
    2640.65f, -1914.08f, 71.35f, 0.33f
};

static const SpawnCoordsStruct SpawnCoordsCrimsonInner[] = 
{
    { 2683.9707f, -1934.0002f, 72.1442f, 2.13f },
    { 2689.6513f, -1930.7386f, 72.1442f, 2.13f }
};

static const SpawnCoordsStruct SpawnCoordsCrimsonOuter[] =
{
    { 2701.0891f, -1864.9894f, 67.5103f, 3.86f },
    { 2703.7336f, -1866.5752f, 67.8296f, 4.01f },
    { 2699.1355f, -1861.3512f, 67.5433f, 3.99f }
};

static const SpawnCoordsStruct MoveCoordsCrimsonInner[] =
{
    { 2675.8896f, -1923.2290f, 69.5838f, 0.0f },
    { 2683.6467f, -1917.1948f, 69.0735f, 0.0f }
};

static const SpawnCoordsStruct MoveCoordsCavaliers[] =
{
    { 2944.5576f, -1389.7694f, 167.2379f, 3.19f },
    { 2941.2106f, -1388.1791f, 167.2379f, 5.39f },
    { 2940.7463f, -1391.0331f, 167.2379f, 4.73f },
    { 2942.8647f, -1392.1495f, 167.2379f, 3.94f } 
};

class QuestInDreams;

/*######
## npc_isillien
######*/

struct npc_isillienAI : npc_escortAI
{
    explicit npc_isillienAI(Creature* pCreature);

    void Reset() override;
    void SetEvent(int32 m_uiEvent);
    void EnterEvadeMode() override;
    void WaypointReached(uint32 uiPointId) override;
    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage) override;
    void TimerSayAndGo(const uint32 uiDiff, uint32 uiUpd, int32 textId, Emote emote = EMOTE_ONESHOT_NONE, bool incSub = true);
    void Event1SummonCrimson();
    void Event2TalkBeforeFight(const uint32 uiDiff);
    void Event3FightTaelan(const uint32 uiDiff);
    void Event4KillTaelan(const uint32 uiDiff);
    void Event5TalkBeforeTirionArrival(const uint32 uiDiff);
    void Event6TirionArrival(const uint32 uiDiff);
    void Event7FightTirion(const uint32 uiDiff);
    void DoAttack(const uint32 uiDiff);
    void UpdateEscortAI(const uint32 uiDiff) override;
    static void GroupRemoveDisguise(Player* player);
    bool IsPlayerGroupAlive();
    virtual void GetAIInformation(ChatHandler& handler) override;

    bool m_isTirionHere;
    //std::shared_ptr<InDreamsInterface> m_pInterface;

    std::shared_ptr <QuestInDreams> pInstance;

private:
    int8  m_uiEventCount;
    int8  m_uiSubEventCount;
    uint32 m_uiEventTimer;

    uint32 m_uiManaBurnTimer;
    uint32 m_uiPowerShieldTimer;
    uint32 m_uiMindBlastTimer;
    uint32 m_uiMindFlayTimer;
    uint32 m_uiDominateMindTimer;
    uint32 m_uiHealTimer;
    uint32 m_uiGlobalCooldownTimer;
    uint32 m_uiDominateMindFadingTimer;

    bool m_isTaelanDead;
    bool m_bControllingPlayer;
};

/*######
## npc_scarlet_cavalier
######*/

struct npc_scarlet_cavalierAI : ScriptedAI
{
    explicit npc_scarlet_cavalierAI(Creature* pCreature);

    void Reset() override;
    void Event1WhatsUp(Creature* pTaelan);
    void Event2SurroundTaelan() const;
    void Event3AttackTaelan(Creature* pTaelan);
    void DoAttack(const uint32 uiDiff);
    void UpdateAI(const uint32 uiDiff) override;
    void MovementInform(uint32 uiMotionType, uint32 uiPointId) override;
    void JustDied(Unit* /*pKiller*/) override;
    virtual void GetAIInformation(ChatHandler& handler) override;

private:
    uint8  m_uiEventCount;
    uint32 m_uiEventTimer;

    uint32 m_uiMortalStrikeTimer;
    uint32 m_uiCleaveTimer;
    uint32 m_uiBackhandTimer;

    ObjectGuid m_pTaelanGuid;
public:

};

/*######
## npc_taelan
######*/

struct npc_taelanAI : npc_escortAI
{
    explicit npc_taelanAI(Creature* pCreature);

    void Reset() override;
    void ResetCreature() override;
    void EnterEvadeMode() override;
    void JustDied(Unit* /*pKiller*/) override;
    void WaypointReached(uint32 uiPointId) override;
    bool CavaliersAreDead();
    static bool IsCavalierNear(uint32 counter);
    Player* GetPlayer() const;
    void SpellHit(Unit* /*pCaster*/, const SpellEntry* pSpell) override;
    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage) override;
    void MoveInLineOfSight(Unit* /*pWho*/) override;
    void Event1ReceivedPresent();
    void Event2FightCavaliers(const uint32 uiDiff);
    void Event4EscortStart(const uint32 uiDiff);
    void Event5MountAndGo(const uint32 uiDiff);
    void Event6FaceIsillien(const uint32 uiDiff);
    void Event7CompleteQuest();
	void MountOrUnMount(bool on);
    void TimerSayAndGo(const uint32 uiDiff, uint32 uiUpd, int32 textId, bool incSub = true);
    void DoAttack(const uint32 uiDiff);
    void DoHeal(const uint32 uiDiff);
    void UpdateEscortAI(const uint32 uiDiff) override;
    virtual void GetAIInformation(ChatHandler& handler) override;

    bool    m_isDead;
    std::shared_ptr <QuestInDreams> pInstance;

private:
    int8   m_uiEventCount;
    int8   m_uiSubEventCount;
    uint32  m_uiEventTimer;

    std::list<ObjectGuid> m_lCavaliersGUID;

    uint32  m_uiHolyCleaveTimer;
    uint32  m_uiHolyLightTimer;
    uint32  m_uiCrusaderStrikeTimer;
    uint32  m_uiLayOnHandsTimer;
    
    bool    m_killedCavaliers;
    bool    m_mountPhase;
public:

};

/*######
## npc_tirion
######*/

struct npc_tirion_fordring_in_dreamsAI : npc_escortAI
{
    explicit npc_tirion_fordring_in_dreamsAI(Creature* pCreature);

    void Reset() override;
    void WaypointReached(uint32 uiPointId) override;
    void MovementInform(uint32 uiMotionType, uint32 uiPointId) override;
    void TimerSayAndGo(const uint32 uiDiff, uint32 uiUpd, int32 textId, Emote emote = EMOTE_ONESHOT_NONE, bool incEvent = true);
    void DoAttack(const uint32 uiDiff);
    void UpdateEscortAI(const uint32 uiDiff) override;
    void JustDied(Unit* pKiller) override;
    virtual void GetAIInformation(ChatHandler& handler) override;

    //std::shared_ptr<InDreamsInterface> m_pInterface;
    std::shared_ptr <QuestInDreams> pInstance;
private:
    uint8   m_uiEventCount;
    uint32  m_uiEventTimer;

    uint32  m_uiCrusaderStrikeTimer;
    uint32  m_uiHolyStrikeTimer;
    uint32  m_uiHolyCleaveTimer;
    uint32  m_uiDevotionAuraTimer;

    bool    m_isIsillienDead;
    bool    m_IsillienReady;
};

/*
 * Crimson Elite
 */

struct npc_crimson_eliteAI : ScriptedAI
{
    explicit npc_crimson_eliteAI(Creature* pCreature);

    void Reset() override;
    void EnterEvadeMode() override;
    void DoAttack(const uint32 uiDiff);
    void UpdateAI(const uint32 uiDiff) override;

private:
    uint32 m_uiCrusaderStrikeTimer;
    uint32 m_uiHolyStrikeTimer;
    uint32 m_uiRetributionAuraCheckTimer;
};

class QuestInDreams : public QuestInstance
{

public:
    QuestInDreams(ObjectGuid InPlayerGuid) : QuestInstance(InPlayerGuid, QUEST_IN_DREAMS)
    {}

    virtual void OnQuestCanceled() override;
    virtual void OnQuestFinished() override;
    virtual void OnQuestStarted() override;
    virtual bool GoToStage(uint32 newStage) override;
    virtual void GetStatus(ChatHandler& handler) override;
    void OnQuestFailed(); //interface method candidate

    enum Stages
    {
        STAGE_IN_BARRACKS = 10,
        STAGE_IN_HEARTHGLEN = 20,
        STAGE_TOWER = 30,
        STAGE_TOWER_GUARDS_1 = 40,
        STAGE_TOWER_GUARDS_2 = 50,
        STAGE_KILL_TAELAN    = 55,
        STAGE_BEFORE_TIRION  = 58,
        STAGE_TIRION_ARRIVAL = 60,
        STAGE_COMPLETE = 100
    };

    static uint32 AllActiveQuests;
    static ObjectGuid OriginalTaelanGuid;

    npc_taelanAI* GetTaelanAI();
    npc_tirion_fordring_in_dreamsAI* GetTirionAI();
    npc_isillienAI* GetIsillienAI();

    Creature* GetTaelan();
    Creature* GetTirion();
    Creature* GetIsillien();

    Creature* GetGuard(ObjectGuid guid);

private:

    ObjectGuid TaelanGUID;
    ObjectGuid IsillienGUID;
    ObjectGuid TirionGUID;

    Map* questMap;

    std::list<ObjectGuid> SummonedGuardGUIDs;

    bool GoToStage_NoQuestMap(uint32 newStage);
    void Destroy();
};
