#include "scriptPCH.h"
#include "dire_maul.h"
#include "ace/Mutex.h"

enum
{
    SPELL_BERSERKER_CHARGE  = 22886,
    SPELL_MORTAL_STRIKE     = 15708,
    SPELL_WAR_STOMP         = 16727,
    SPELL_SUNDER_ARMOR      = 15572,

    SAY_AGGRO               = -1900045,
};

struct PlayerKiteCounter
{
    uint32 count = 0;
    uint16 lastKillTime = 0;
    uint16 bAskedToLeave = 0; //uint16 for packing
};


struct boss_king_gordokAI : public ScriptedAI
{
    boss_king_gordokAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        pInstance = (instance_dire_maul*)pCreature->GetInstanceData();
        Reset();
    }

    instance_dire_maul* pInstance;

    uint32 m_uiMortalStrike_Timer;
    uint32 m_uiWarStomp_Timer;
    uint32 m_uiBerserkerCharge_Timer;
    uint32 m_uiSunderArmor_Timer;
    uint32 m_uiPhase;
    
    uint32 m_uiLinkCheckTimer;

    ///######ANTI KITE SYSTEM######

    ///How it works:
    ///Initialize all values in false
    ///We can't reach target by melee attack? Then set first value as true, and do nothing more this tick
    ///We still can't reach target by melee NEXT tick? Then set second variable as true. 
    ///Next time, if target still unreachable - add current deltaTime to KiteTimer
    ///If we can reach by melee - set all variables back to false
    bool bCanReachWithMeeleAttackState[2];
    uint32 KiteTimer;
    bool bSuperSpeed;
    static std::unordered_map<uint32, PlayerKiteCounter> PlayerKitersRegistry;
    static ACE_Mutex PlayerKitersRegistryGuard;
    static const uint32 KillSeriesTimespan = 20 * MINUTE * IN_MILLISECONDS;
       
    //Get num of times that players killing King Gordok within KillSeriesTimespan
    static uint32 GetKiteCountIfInRangeOfTimestamp(uint32 PlayerGuidLow)
    {
        ACE_Guard<ACE_Mutex> guard(PlayerKitersRegistryGuard);
        PlayerKiteCounter& KiteCounter = PlayerKitersRegistry[PlayerGuidLow];
        if (KiteCounter.lastKillTime != 0)
        {
            if (WorldTimer::getMSTimeDiffToNow(KiteCounter.lastKillTime) < KillSeriesTimespan)
            {
                return KiteCounter.count;
            }
            else
            {
                KiteCounter.count = 0;
                KiteCounter.lastKillTime = 0;
            }
        }

        return KiteCounter.count;
    }

    void WarnKitePlayer(Player* player)
    {
        ACE_Guard<ACE_Mutex> guard(PlayerKitersRegistryGuard);
        PlayerKiteCounter& KiteCounter = PlayerKitersRegistry[player->GetGUIDLow()];

        if (KiteCounter.lastKillTime != 0 && KiteCounter.bAskedToLeave == 0)
        {
            if (WorldTimer::getMSTimeDiffToNow(KiteCounter.lastKillTime) < KillSeriesTimespan)
            {
                m_creature->MonsterYell("No, not you again $N! Leave me alone!", 0, player);
                KiteCounter.bAskedToLeave = 1;
            }
        }
    }

    static uint32 IncrementKiteCount(uint32 PlayerGuidLow)
    {
        ACE_Guard<ACE_Mutex> guard(PlayerKitersRegistryGuard);
        PlayerKiteCounter& KiteCounter = PlayerKitersRegistry[PlayerGuidLow];

        uint32 Result = 1;
        if (WorldTimer::getMSTimeDiffToNow(KiteCounter.lastKillTime) < KillSeriesTimespan)
        {
            Result = ++KiteCounter.count;
        }
        else
        {
            KiteCounter.count = 1;
        }

        KiteCounter.lastKillTime = WorldTimer::getMSTime();

        return Result;
    }

    static const char* GetTextPerKiteCounter(uint32 KiteCount)
    {
        switch (KiteCount)
        {
        case 1:
            return "FIRST BLOOD!";
        case 2:
            return "DOUBLE KILL!";
        case 3:
            return "TRIPLE KILL!";
        case 4:
            return "GODLIKE!";
        case 5:
            return "M-M-M-M-MOSTER KILL!";
        default:
            return "UNSTOPPABLE!";
        }
    }

    void Reset()
    {
        m_uiWarStomp_Timer        = urand(7000, 8000);
        m_uiMortalStrike_Timer    = urand(15000, 25000);
        m_uiSunderArmor_Timer     = urand(4000, 8000);
        m_uiBerserkerCharge_Timer = urand(9000, 12000);
        m_uiPhase = 0;
        bCanReachWithMeeleAttackState[0] = false;
        bCanReachWithMeeleAttackState[1] = false;
        KiteTimer = 0;
//         if (bSuperSpeed)
//         {
//             m_creature->UpdateSpeed(UnitMoveType::MOVE_RUN, true, 1.3f);
//         }
        bSuperSpeed = false;
        
        m_uiLinkCheckTimer = 2500;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void UpdateKiteTimerIfNeccessery(const uint32 deltaTime)
    {
        if (!m_creature->CanReachWithMeleeAttack(m_creature->getVictim()))
        {
            if (bCanReachWithMeeleAttackState[0])
            {
                if (bCanReachWithMeeleAttackState[1])
                {
                    KiteTimer += deltaTime;
                }
                else
                {
                    bCanReachWithMeeleAttackState[1] = true;
                }
            }
            else
            {
                bCanReachWithMeeleAttackState[0] = true;
            }
        }
        else
        {
            bCanReachWithMeeleAttackState[0] = false;
            bCanReachWithMeeleAttackState[1] = false;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        UpdateKiteTimerIfNeccessery(uiDiff);
        if (KiteTimer > 30000 && !bSuperSpeed)
        {
            bSuperSpeed = true;
            //GOTTA GO FAST. GO FAST, GO FAST, FAST, FAST, FAST
            //Update: Okay, not so fast. Political situation is too bad
            //m_creature->MonsterYell("You gonna kill me with kite tactic? Alright. But we log that, so don't try sell this gold!");
            m_creature->MonsterYell("Why you run? I tellin' the gods on you!");
            Unit* Killer = m_creature->getVictim();
            if (Killer != nullptr)
            {
                if (Killer->IsPet())
                {
                    Killer = Killer->GetOwner();
                }
            }

            sLog.outInfo("Player '%s' (GUID: %llu) using kite tactic for King Gordok", Killer->GetName(), Killer->GetObjectGuid().GetRawValue());
            //m_creature->UpdateSpeed(UnitMoveType::MOVE_RUN, true, 15.0f);
        }

        // Sunder Armor
        if (m_uiSunderArmor_Timer < uiDiff) 
        {
            Unit* pTarget = m_creature->getVictim();
            if (pTarget) 
            {
                DoCastSpellIfCan(pTarget, SPELL_SUNDER_ARMOR);
                if (Aura* pAura = pTarget->GetAura(SPELL_SUNDER_ARMOR, EFFECT_INDEX_0)) 
                {
                    if (pAura->GetStackAmount() == 5)
                        m_uiSunderArmor_Timer = urand(15000, 25000);
                    else 
                        m_uiSunderArmor_Timer = urand(5000, 15000);
                } 
                else 
                    m_uiSunderArmor_Timer = urand(5000, 15000);
            }
        } 
        else 
            m_uiSunderArmor_Timer -= uiDiff;

        // Mortal Strike
        if (m_uiMortalStrike_Timer < uiDiff) 
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_MORTAL_STRIKE) == CAST_OK)
                m_uiMortalStrike_Timer = urand(12000, 20000);
        } 
        else 
            m_uiMortalStrike_Timer -= uiDiff;

        // War Stomp
        if (m_uiWarStomp_Timer < uiDiff) 
        {
            if (DoCastSpellIfCan(m_creature, SPELL_WAR_STOMP) == CAST_OK)
                m_uiWarStomp_Timer = urand(20000, 30000);
        } 
        else 
            m_uiWarStomp_Timer -= uiDiff;

        // Berserker Charge
        if (m_uiBerserkerCharge_Timer < uiDiff) 
        {
            if (DoCastSpellIfCan(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1, nullptr, SELECT_FLAG_PLAYER), SPELL_BERSERKER_CHARGE) == CAST_OK)
                m_uiBerserkerCharge_Timer = urand(25000, 30000);
        } 
        else 
            m_uiBerserkerCharge_Timer -= uiDiff;

        DoMeleeAttackIfReady();
        
        // Prevent splitting King from the Observer
        if (m_uiLinkCheckTimer < uiDiff)
        {
            if (Creature* pChorush = m_creature->GetMap()->GetCreature(pInstance->GetData64(NPC_CHORUSH)))
            {
                if (pChorush->isAlive() && !pChorush->isInCombat())
                    pChorush->AI()->AttackStart(m_creature->getVictim());
            }
            m_uiLinkCheckTimer = 2500;
        }
        else
            m_uiLinkCheckTimer -= uiDiff;
    }

    virtual void GetAIInformation(ChatHandler& handler) override
    {
        handler.PSendSysMessage("Kite start1: %s; Kite start2: %s", 
            ChatHandler::ToString(bCanReachWithMeeleAttackState[0]), ChatHandler::ToString(bCanReachWithMeeleAttackState[1]));
        handler.PSendSysMessage("Kite Timer: %u", KiteTimer);
        handler.PSendSysMessage("Is Super speed: %s", ChatHandler::ToString(bSuperSpeed));
    }


    virtual void JustDied(Unit* pKiller) override
    {
        if (bSuperSpeed)
        {
            Player* plKiller = nullptr;
            if (pKiller->IsPet())
            {
                if (Pet* pet = pKiller->ToPet())
                {
                    ObjectGuid playerGuid = pet->GetOwnerGuid();
                    plKiller = sObjectMgr.GetPlayer(playerGuid);
                }
            }
            else
            {
                plKiller = pKiller->ToPlayer();
            }

            if (plKiller != nullptr)
            {
                uint32 KillTimes = boss_king_gordokAI::IncrementKiteCount(plKiller->GetGUIDLow());
                //Send gratz text for every new kill
                const char* GratzTxt = GetTextPerKiteCounter(KillTimes);
                if (GratzTxt != nullptr)
                {
                    ChatHandler(plKiller).SendSysMessage(GratzTxt);
                }
            }
        }

        if (Creature* chorush = m_creature->GetMap()->GetCreature(pInstance->GetData64(NPC_CHORUSH)))
        {
            if (chorush->isAlive())
            {
                chorush->DeleteThreatList();
                chorush->CombatStop(true);
                chorush->setFaction(35);
            }
        }

        ScriptedAI::JustDied(pKiller);
    }

    virtual void MoveInLineOfSight(Unit* pWho) override
    {
        if (Player* player = pWho->ToPlayer())
        {
            WarnKitePlayer(player);
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }

};

CreatureAI* GetAI_boss_king_gordok(Creature* pCreature)
{
    return new boss_king_gordokAI(pCreature);
}

enum
{
    // Mage
    SPELL_ARCANE_EXPLOSION  = 13745, // // m_uiSpellTimers[1]
    SPELL_FIREBALL          = 17290, // // m_uiSpellTimers[0]
    SPELL_FROST_NOVA        = 15331, // d 8s // m_uiSpellTimers[2]
    SPELL_BLOODLUST         = 16170, // d 30s // m_uiSpellTimers[3]

    // Shaman
    SPELL_CHAIN_LIGHTNING   = 15305, // m_uiSpellTimers[1]
    SPELL_EARTHGRAB_TOTEM   = 8376, // d 30s m_uiSpellTimers[2]
    SPELL_HEALING_WAVE      = 15982, // // m_uiSpellTimers[3]
    SPELL_LIGHTNING_BOLT    = 15234, // m_uiSpellTimers[0]

    // Prist
    SPELL_MIND_BLAST        = 17194, // m_uiSpellTimers[0]
    SPELL_HEAL              = 22883, // m_uiSpellTimers[3]
    SPELL_POWER_WORD_SHIELD = 17139, // m_uiSpellTimers[1]
    SPELL_PSYCHIC_SCREAM    = 22884, // m_uiSpellTimers[2]

    NPC_EARTHGRAB_TOTEM     = 6066,

    MAGE_EQUIPMENT          = 12072,
    SHAMAN_EQUIPMENT        = 12071,
    PRIST_EQUIPMENT         = 12070,

    MAX_SPELLS              = 4,
    SET_MAGE                = 1,
    SET_SHAMAN              = 2,
    SET_PRIST               = 3,

    SAY_OGRE_AGGRO_1        = -359,
    SAY_OGRE_AGGRO_2        = -360,
};

std::unordered_map<uint32, PlayerKiteCounter> boss_king_gordokAI::PlayerKitersRegistry;
ACE_Mutex boss_king_gordokAI::PlayerKitersRegistryGuard;

struct boss_chorushAI : public ScriptedAI
{
    boss_chorushAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        pInstance = (instance_dire_maul*)pCreature->GetInstanceData();
        Reset();
    }

    instance_dire_maul* pInstance;

    uint8 m_uiEquipment;
    uint32 m_uiSpellTimers[MAX_SPELLS];
    bool m_bInMeele;
    
    uint32 m_uiLinkCheckTimer;

    void EnterCombat(Unit* pWho)
    {
        m_creature->MonsterSay(urand(0, 1) ? SAY_OGRE_AGGRO_1 : SAY_OGRE_AGGRO_2, 0);
    }

    void Reset()
    {
        m_uiLinkCheckTimer = 2500;
        m_uiEquipment = 0;
        m_bInMeele = true;
        if (pInstance)
            m_uiEquipment = pInstance->GetChoRushEquipment();

        for (uint8 i = 0; i < MAX_SPELLS; ++i)
            m_uiSpellTimers[i] = urand(1000, 2000);

        switch (m_uiEquipment)
        {
            case SET_MAGE: m_creature->LoadEquipment(MAGE_EQUIPMENT, true);
                SetCombatMovement(true);
                break;
            case SET_SHAMAN: m_creature->LoadEquipment(SHAMAN_EQUIPMENT, true);
                SetCombatMovement(true);
                break;
            case SET_PRIST: m_creature->LoadEquipment(PRIST_EQUIPMENT, true);
                SetCombatMovement(true);
                break;
        }
    }

    void UpdateAIMage(const uint32 uiDiff);
    void UpdateAIShaman(const uint32 uiDiff);
    void UpdateAIPrist(const uint32 uiDiff);

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        switch (m_uiEquipment)
        {
            case SET_MAGE:
                UpdateAIMage(uiDiff);
                break;
            case SET_SHAMAN:
                UpdateAIShaman(uiDiff);
                break;
            case SET_PRIST:
                UpdateAIPrist(uiDiff);
                break;
        }

        DoMeleeAttackIfReady();
        
        // Prevent splitting Observer from the King
        if (m_uiLinkCheckTimer < uiDiff)
        {
            if (Creature* pKing = m_creature->GetMap()->GetCreature(pInstance->GetData64(NPC_KING_GORDOK)))
            {
                if (!pKing->isInCombat())
                    pKing->AI()->AttackStart(m_creature->getVictim());
            }
            m_uiLinkCheckTimer = 2500;
        }
        else
            m_uiLinkCheckTimer -= uiDiff;
    }
};

// MAGE
void boss_chorushAI::UpdateAIMage(const uint32 uiDiff)
{
    // Fireball
    if (m_uiSpellTimers[0] < uiDiff) 
    {
        if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_FIREBALL) == CAST_OK)
            m_uiSpellTimers[0] = (m_bInMeele ? urand(7000, 10000) : urand(3000, 4000));
    } 
    else 
        m_uiSpellTimers[0] -= uiDiff;

    // Bloodlust
    if (m_uiSpellTimers[3] < uiDiff)
    {
        Unit* pTarget = NULL;

        if (!m_creature->HasAura(SPELL_BLOODLUST))
            pTarget = m_creature;

        Unit* pKing = m_creature->FindNearestCreature(NPC_KING_GORDOK, 30.f);

        if (pKing && !pKing->HasAura(SPELL_BLOODLUST) && urand(0, 1))
            pTarget = pKing;

        if (DoCastSpellIfCan(pTarget, SPELL_BLOODLUST) == CAST_OK)
            m_uiSpellTimers[3] = urand(10000, 20000);
    } 
    else
        m_uiSpellTimers[3] -= uiDiff;

    // Arcane Explosion
    if (m_uiSpellTimers[1] < uiDiff) 
    {
        bool m_bMeleeAttackers = false;
        Unit::AttackerSet attackers = m_creature->getAttackers();
        for (Unit::AttackerSet::iterator itr = attackers.begin(); itr != attackers.end(); ++itr)
            if (Unit* attacker = m_creature->GetMap()->GetUnit((*itr)->GetGUID()))
                if (m_creature->IsInRange(attacker, 0.0f, 8.0f, false)) 
                {
                     m_bMeleeAttackers = true;
                     break;
                }
        if (m_bMeleeAttackers)
            if (DoCastSpellIfCan(m_creature, SPELL_ARCANE_EXPLOSION) == CAST_OK)
                m_uiSpellTimers[1] = (m_bInMeele ? urand(9000, 13000) : urand(15000, 25000));
    } 
    else 
        m_uiSpellTimers[1] -= uiDiff;
    
    
    // Frost Nova
    if (m_uiSpellTimers[2] < uiDiff) 
    {
        bool m_bMeleeAttackers = false;
        Unit::AttackerSet attackers = m_creature->getAttackers();
        for (Unit::AttackerSet::iterator itr = attackers.begin(); itr != attackers.end(); ++itr)
            if (Unit* attacker = m_creature->GetMap()->GetUnit((*itr)->GetGUID()))
                if (m_creature->IsInRange(attacker, 0.0f, 8.0f, false)) 
                {
                     m_bMeleeAttackers = true;
                     break;
                }
        if (m_bMeleeAttackers)
            if (DoCastSpellIfCan(m_creature, SPELL_FROST_NOVA) == CAST_OK)
                m_uiSpellTimers[2] = urand(20000, 30000);
    } 
    else 
        m_uiSpellTimers[2] -= uiDiff;

    if (!IsCombatMovement())
    { //Melee
        if (!m_bInMeele && (m_creature->GetDistance2d(m_creature->getVictim()) < 5.0f || m_creature->GetDistance2d(m_creature->getVictim()) > 30.0f
          || !m_creature->IsWithinLOSInMap(m_creature->getVictim()) || m_creature->GetPowerPercent(POWER_MANA) < 5.0f))
        {
            SetCombatMovement(true);
            DoStartMovement(m_creature->getVictim());
            m_bInMeele = true;
            return;
        }
    }
    else                
    { //Range
        if (m_bInMeele && m_creature->GetDistance2d(m_creature->getVictim()) >= 5.0f && m_creature->GetDistance2d(m_creature->getVictim()) <= 30.0f
          && m_creature->IsWithinLOSInMap(m_creature->getVictim()) && m_creature->GetPowerPercent(POWER_MANA) >= 5.0f)
        {
            SetCombatMovement(false);
            m_bInMeele = false;
            DoStartNoMovement(m_creature->getVictim());
            return;
        }
    }
};

// SHAMAN
void boss_chorushAI::UpdateAIShaman(const uint32 uiDiff)
{
    // Earthgrab Totem
    if (m_uiSpellTimers[2] < uiDiff) 
    {
        bool m_bMeleeAttackers = false;
        Unit::AttackerSet attackers = m_creature->getAttackers();
        for (Unit::AttackerSet::iterator itr = attackers.begin(); itr != attackers.end(); ++itr)
            if (Unit* attacker = m_creature->GetMap()->GetUnit((*itr)->GetGUID()))
                if (m_creature->IsInRange(attacker, 0.0f, 6.0f, false)) 
                {
                     m_bMeleeAttackers = true;
                     break;
                }
        if (m_bMeleeAttackers)
            if (DoCastSpellIfCan(m_creature, SPELL_EARTHGRAB_TOTEM) == CAST_OK)
                m_uiSpellTimers[2] = urand(20000, 30000);
    } 
    else 
        m_uiSpellTimers[2] -= uiDiff;

    // Healing Wave
    if (m_uiSpellTimers[3] < uiDiff) 
    {
        Unit* pTarget = NULL;
        if (pTarget = DoSelectLowestHpFriendly(40.0f, 15000));
        else if  (m_creature->GetHealthPercent() < 50.0f)
            pTarget = m_creature;

        if (pTarget)
            if (DoCastSpellIfCan(pTarget, SPELL_HEALING_WAVE) == CAST_OK)
                m_uiSpellTimers[3] = urand(10000, 15000);
    } 
    else 
        m_uiSpellTimers[3] -= uiDiff;

    // Lightning Bolt
    if (m_uiSpellTimers[0] < uiDiff) 
    {
        if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_LIGHTNING_BOLT) == CAST_OK)
            m_uiSpellTimers[0] = (m_bInMeele ? urand(7000, 10000) : urand(3000, 4000));
    } 
    else 
        m_uiSpellTimers[0] -= uiDiff;

    // Chain Lightning
    if (m_uiSpellTimers[1] < uiDiff) 
    {
        if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CHAIN_LIGHTNING) == CAST_OK)
            m_uiSpellTimers[1] = urand(15000, 25000);
    } 
    else 
        m_uiSpellTimers[1] -= uiDiff;

    if (!IsCombatMovement())
    { //Melee
        if (!m_bInMeele && (m_creature->GetDistance2d(m_creature->getVictim()) < 5.0f || m_creature->GetDistance2d(m_creature->getVictim()) > 30.0f
          || !m_creature->IsWithinLOSInMap(m_creature->getVictim()) || m_creature->GetPowerPercent(POWER_MANA) < 5.0f))
        {
            SetCombatMovement(true);
            DoStartMovement(m_creature->getVictim());
            m_bInMeele = true;
            return;
        }
    }
    else
    { //Range
        if (m_bInMeele && m_creature->GetDistance2d(m_creature->getVictim()) >= 5.0f && m_creature->GetDistance2d(m_creature->getVictim()) <= 30.0f
          && m_creature->IsWithinLOSInMap(m_creature->getVictim()) && m_creature->GetPowerPercent(POWER_MANA) >= 5.0f)
        {
            SetCombatMovement(false);
            m_bInMeele = false;
            DoStartNoMovement(m_creature->getVictim());
            return;
        }
    }
};

// PRIEST
void boss_chorushAI::UpdateAIPrist(const uint32 uiDiff)
{
    // Heal
    if (m_uiSpellTimers[3] < uiDiff) 
    {
        Unit* pTarget = NULL;
        if (pTarget = DoSelectLowestHpFriendly(40.0f, 15000));
        else if  (m_creature->GetHealthPercent() < 50.0f)
            pTarget = m_creature;

        if (pTarget)
            if (DoCastSpellIfCan(pTarget, SPELL_HEAL) == CAST_OK)
                m_uiSpellTimers[3] = urand(10000, 15000);
    } 
    else 
        m_uiSpellTimers[3] -= uiDiff;

    // Mind Blast
    if (m_uiSpellTimers[0] < uiDiff) 
    {
        if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_MIND_BLAST) == CAST_OK)
            m_uiSpellTimers[0] = (m_bInMeele ? urand(7000, 10000) : urand(2000, 3000));
    } 
    else 
        m_uiSpellTimers[0] -= uiDiff;

    // Power Word Shield
    if (m_uiSpellTimers[1] < uiDiff)
    {
        if (Unit* pTarget = DoSelectLowestHpFriendly(40.0f))
        {
            if (DoCastSpellIfCan(pTarget, SPELL_POWER_WORD_SHIELD) == CAST_OK)
                m_uiSpellTimers[1] = urand(17000, 22000);
        }
    } 
    else
        m_uiSpellTimers[1] -= uiDiff;

    // Psychic Scream
    if (m_uiSpellTimers[2] < uiDiff) 
    {
        bool m_bMeleeAttackers = false;
        Unit::AttackerSet attackers = m_creature->getAttackers();
        for (Unit::AttackerSet::iterator itr = attackers.begin(); itr != attackers.end(); ++itr)
            if (Unit* attacker = m_creature->GetMap()->GetUnit((*itr)->GetGUID()))
                if (m_creature->IsInRange(attacker, 0.0f, 8.0f, false)) 
                {
                     m_bMeleeAttackers = true;
                     break;
                }
        if (m_bMeleeAttackers)
            if (DoCastSpellIfCan(m_creature, SPELL_PSYCHIC_SCREAM) == CAST_OK)
                m_uiSpellTimers[2] = urand(15000, 20000);
    } 
    else 
        m_uiSpellTimers[2] -= uiDiff;

    if (!IsCombatMovement())
    { //Melee
        if (!m_bInMeele && (m_creature->GetDistance2d(m_creature->getVictim()) < 5.0f || m_creature->GetDistance2d(m_creature->getVictim()) > 30.0f
            || !m_creature->IsWithinLOSInMap(m_creature->getVictim()) || m_creature->GetPowerPercent(POWER_MANA) < 5.0f))
        {
            SetCombatMovement(true);
            DoStartMovement(m_creature->getVictim());
            m_bInMeele = true;
            return;
        }
    }
    else
    { //Range
        if (m_bInMeele && m_creature->GetDistance2d(m_creature->getVictim()) >= 5.0f && m_creature->GetDistance2d(m_creature->getVictim()) <= 30.0f
            && m_creature->IsWithinLOSInMap(m_creature->getVictim()) && m_creature->GetPowerPercent(POWER_MANA) >= 5.0f)
        {
            SetCombatMovement(false);
            m_bInMeele = false;
            DoStartNoMovement(m_creature->getVictim());
            return;
        }
    }
};

CreatureAI* GetAI_boss_chorush(Creature* pCreature)
{
    return new boss_chorushAI(pCreature);
}

void AddSC_npc_king_gordok()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_king_gordok";
    pNewScript->GetAI = &GetAI_boss_king_gordok;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_chorush";
    pNewScript->GetAI = &GetAI_boss_chorush;
    pNewScript->RegisterSelf();
}
