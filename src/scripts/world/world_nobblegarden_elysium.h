//Giperion March 2018
//[EUREKA] 3.6
//Elysium Project
#pragma once

enum EggOpenEffectId
{
    STINK_EFFECT = 0,
    RABBIT_MORPH = 1,
    LOOT = 2
};

enum
{
    ///SPELLS
    SPELL_RABBIT_MORPH = 8067,
    SPELL_FLAMESTRIKE_ID = 10216,
    SPELL_RABBIT_FEAR = 6946, //Originnaly called 'Curse of the Bleakheart', but know it's transform you to rabbit, and force player run from npc_rabbit_boss
    SPELL_SPEED_BUFF = 22863, //2 hour speed buff
    SPELL_LEARN_APPRENTICE_RIDING = 33389,
    SPELL_LEARN_JOURNEYMAN_RIDING = 33392,

    ///GAMEOBJECTS
    GO_SMALL_EGG = 113769, //Brightly Colored Egg 
    GO_BIG_EGG = 113773, //Big Colored Egg

    ///TEXTS
    RABBIT_BOSS_BETA_WARN_TXT_ID = 238, //id in for nostalrius_string. There is a 5 entries for that, choosed randomly
    //Fulzamoth texts for Rabbit boss
    RABBIT_BOSS_GREETINGS_TXT_ID = 243, //another txt id, 2 entries
    RABBIT_BOSS_WARN_TXT_ID = 245, //5 entries
    RABBIT_BOSS_ENRAGE_TXT_ID = 250, //3 entries
    RABBIT_BOSS_BATTLE_TXT_ID = 253, //3 entries
    RABBIT_BOSS_CALM_TXT_ID = 256, //6 entries
    TXT_NEED_MORE_SMALL_EGGS = 262,
    TXT_NEED_MORE_BIG_EGGS = 263,
    TXT_CANT_STORE_NEW_ITEM = 264,

    ///NPCS
    NPC_RABBIT_MINION = 17998,

    ///ITEMS
    ITEM_BEAUTIFUL_WILDFLOWERS  = 3422,
    ITEM_EASTER_DRESS           = 7809,
    ITEM_CARROT_ON_STICK        = 11122,
    ITEM_SPRITE_DARTER_EGG      = 11474,
    ITEM_SMALL_EASTER_EGG       = 25820,
    ITEM_BIG_EASTER_EGG         = 25821,
    ITEM_LUCKY_RABBIT_FOOT      = 25822,
    ITEM_ORB_OF_EASTER          = 50016,
    ITEM_COTTONTAIL_RABBIT_MINION = 50004,

};

#define RABBIT_COUNT 10

class npc_rabbit_boss : public ScriptedAI
{

public:
    static uint32 EnrageTime;
    static uint32 CalmDownTime;
    static uint32 WarnTime;
    static float VisionRadius;
    static uint32 ChangeOrientationTime;
    static uint32 EnrageFlamestrikeTime;
    static uint32 BurnDamageRadius;
    static uint32 BurnDamagePercent;

    npc_rabbit_boss(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    virtual void JustDied(Unit*) override;
    virtual void Reset() override;
    virtual void UpdateAI(const uint32 deltaTime) override;
    virtual void MoveInLineOfSight(Unit* unit) override;
    virtual void GetAIInformation(ChatHandler& handler) override;
    void SpawnRabbits();

    void SaySpawnPhrase();
    void SayEnragePhrase();
    void SayBattlePhrase();
    void SayCalmPhrase();

    void Calmdown();
    void Enrage();

    virtual void GetData(uint32 dataIndx, float& Data) override;
    virtual void GetData(uint32 dataIndx, uint32& Data) override;
    virtual void SetData(uint32 dataIndx, float Data) override;
    virtual void SetData(uint32 dataIndx, uint32 Data) override;

    virtual void DoAction(const uint32 = 0) override;


    virtual void AttackStart(Unit*) override;


    virtual void EnterCombat(Unit*) override;

private:

    bool IsPlayerInSight(Player* player);

    void WarnPlayer(Player* player);

    std::vector<ObjectGuid> SpawnedRabbitsGuids;
    std::unordered_map<ObjectGuid, uint32> PlayersInSight;
    uint32 ChangeOrientationTimer;
    uint32 EnrageTimer;
    uint32 CalmDownTimer;
    uint32 BurnAuraTimer = 1000;

    uint32 EnrageFlamestrikeTimer;
    bool bEnrageMode = false;
    bool bOnceSpawned = false;
};

class npc_rabbit_minion : public ScriptedAI
{

public:
    static uint32 EggTime;

    npc_rabbit_minion(Creature* creature)
        : ScriptedAI(creature)
    {
        Reset();
    }
    virtual void Reset() override;
    virtual void UpdateAI(const uint32 deltaTime) override;
    virtual void GetAIInformation(ChatHandler& handler) override;

    virtual void GetData(uint32 dataIndx, uint32& Data) override;
    virtual void SetData(uint32 dataIndx, uint32 Data) override;

private:
    void LayEgg();
    uint32 layEggTimer;

};

void AddSC_world_nobblegarden_elysium();