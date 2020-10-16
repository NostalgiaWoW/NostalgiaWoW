//Giperion March 2018
//[EUREKA] 3.6
//Elysium Project

/*
* Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
* Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
* Copyright (C) 2011-2016 Nostalrius <https://nostalrius.org>
* Copyright (C) 2016-2018 Elysium Project <https://github.com/elysium-project>
*
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

#include "scriptPCH.h"
#include "LootMgr.h"
#include "IVMapManager.h"
#include "Cell.h"
#include "world_nobblegarden_elysium.h"


bool go_nobblegarden_egg_Open(Player* pl, GameObject* go)
{
    EggOpenEffectId Effect = (EggOpenEffectId)urand(0, 2);

    uint32 noSpaceForCount = 0;

    switch (Effect)
    {
    case STINK_EFFECT:
        pl->AddAura(24918, ADD_AURA_NEGATIVE);
        break;
    case RABBIT_MORPH:
        pl->CastSpell(pl, SPELL_RABBIT_MORPH, true);
        break;
    case LOOT:
        //TODO!
//         go->loot.FillLoot(LOOT_ID_EGG, LootTemplates_Gameobject, pl, true, false);
//         go->SetLootState(GO_ACTIVATED);
//         pl->SendLoot(go->GetObjectGuid(), LOOT_CORPSE, go->loot, OWNER_PERMISSION);

        //Place item in inventory immidiatly
    {
        bool bBigEgg = false;
        if (go->GetEntry() == GO_BIG_EGG)
        {
            sLog.outInfo("[EASTER]: Player %s (GUID: %llu) loot (GUID: %llu) big egg", pl->GetName(), pl->GetObjectGuid().GetRawValue(), go->GetObjectGuidSafe().GetRawValue());
            bBigEgg = true;
            pl->AddItem(ITEM_BIG_EASTER_EGG, 1, &noSpaceForCount);
        }
        else
        {
            sLog.outInfo("[EASTER]: Player %s (GUID: %llu) loot (GUID: %llu) small egg", pl->GetName(), pl->GetObjectGuid().GetRawValue(), go->GetObjectGuidSafe().GetRawValue());
            pl->AddItem(ITEM_SMALL_EASTER_EGG, 1, &noSpaceForCount);
        }
        if (noSpaceForCount > 0)
        {
            ChatHandler(pl).SendSysMessage("You don't have a free space to store egg!");
            sLog.outInfo("[EASTER]: Player %s (GUID: %llu) loot (GUID: %llu) small egg FAILED - no inventory space for item", pl->GetName(), pl->GetObjectGuid().GetRawValue(), go->GetObjectGuidSafe().GetRawValue());
        }
        else
        {
            std::shared_ptr<EasterStatistic> pStat = sObjectMgr.GetEasterStatisticForPlayer(pl->GetObjectGuid());
            if (pStat)
            {
                if (bBigEgg)
                {
                    pStat->BigEggsCollected++;
                }
                else
                {
                    pStat->SmallEggsCollected++;
                }
            }
        }
    }
        break;
    default:
        break;
    }
    //despawn
    if (noSpaceForCount == 0)
    {
        go->Despawn();
    }

    return true;
}



enum VendorSelection
{
    LuckyRabbitFoot_1 = 1,
    EasterDress_1 = 2,
    BeautufulWildflowers_1 = 3,
    RabbitSpeedBuff_1 = 4,
    CottonailRabbitPet_1 = 5,
    SpriteDarterEgg_1 = 6,
    ApprenticeRidingSkill_1 = 7,

    BeautufulWildflowers_2 = 10,
    CottonailRabbitPet_2 = 11,
    SpriteDarterEgg_2 = 12,
    OrbOfEaster_2 = 13,
    CarrotOnStick_2 = 14,
    EpicRidingSkill_2 = 15
};

bool GossipHello_npc_nobblegarden_vendor(Player *player, Creature *_Creature)
{
    //Small eggs exchange options
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Lucky Rabbit's Foot [5 Small Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::LuckyRabbitFoot_1);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Easter Dress [10 Small Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::EasterDress_1);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Beautuful Wildflowers [10 Small Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::BeautufulWildflowers_1);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Rabbit Speed Buff [10 Small Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::RabbitSpeedBuff_1);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Cottonail Rabbit Pet[50 Small Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::CottonailRabbitPet_1);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Sprite Darter Egg[200 Small Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::SpriteDarterEgg_1);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Apprentice Riding Skill[300 Small Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::ApprenticeRidingSkill_1);

    //big eggs exchange options
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Beautuful Wildflowers [5 Big Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::BeautufulWildflowers_2);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Cottonail Rabbit [10 Big Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::CottonailRabbitPet_2);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Sprite Darter Egg [100 Big Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::SpriteDarterEgg_2);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Orb of Easter [150 Big Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::OrbOfEaster_2);
    //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Carrot on a Stick [200 Big Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::CarrotOnStick_2);
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_2, "Epic Riding Skill [300 Big Eggs]", GOSSIP_SENDER_MAIN, VendorSelection::EpicRidingSkill_2);

    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _Creature->GetGUID());
    return true;
}

bool IsPlayerHaveSmallEggCount(Player* player, uint32 ReqCount)
{
    uint32 SmallEggsCount = player->GetItemCount(ITEM_SMALL_EASTER_EGG);
    if (SmallEggsCount < ReqCount)
    {
        ChatHandler(player).PSendSysMessage(NOST_TEXT(TXT_NEED_MORE_SMALL_EGGS), ReqCount - SmallEggsCount);
        return false;
    }
    return true;
}

bool IsPlayerHaveBigEggCount(Player* player, uint32 ReqCount)
{
    uint32 BigEggsCount = player->GetItemCount(ITEM_BIG_EASTER_EGG);
    if (BigEggsCount < ReqCount)
    {

        ChatHandler(player).PSendSysMessage(NOST_TEXT(TXT_NEED_MORE_BIG_EGGS), ReqCount - BigEggsCount);
        return false;
    }
    return true;
}

bool RemoveSmallEggsFromPlayer(Player* player, uint32 ReqCount)
{
    if (IsPlayerHaveSmallEggCount(player, ReqCount))
    {
        std::shared_ptr<EasterStatistic> pStat = sObjectMgr.GetEasterStatisticForPlayer(player->GetObjectGuid());
        if (pStat)
        {
            pStat->SmallEggsWasted += ReqCount;
        }
        sLog.outInfo("[EASTER]: Player %s (GUID: %llu) spend %u small eggs", player->GetName(), player->GetObjectGuid().GetRawValue(), ReqCount);
        return player->RemoveItems(ITEM_SMALL_EASTER_EGG, ReqCount);
    }
    return false;
}

bool RemoveBigEggsFromPlayer(Player* player, uint32 ReqCount)
{
    if (IsPlayerHaveBigEggCount(player, ReqCount))
    {
        std::shared_ptr<EasterStatistic> pStat = sObjectMgr.GetEasterStatisticForPlayer(player->GetObjectGuid());
        if (pStat)
        {
            pStat->BigEggsWasted += ReqCount;
        }
        sLog.outInfo("[EASTER]: Player %s (GUID: %llu) spend %u big eggs", player->GetName(), player->GetObjectGuid().GetRawValue(), ReqCount);
        return player->RemoveItems(ITEM_BIG_EASTER_EGG, ReqCount);
    }
    return false;
}

bool CanStoreNewItem(Player* player, int32 itemId)
{
    ItemPosCountVec dest;
    InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, 1);
    if (msg != InventoryResult::EQUIP_ERR_OK)
    {
        ChatHandler(player).PSendSysMessage(TXT_CANT_STORE_NEW_ITEM);
        return false;
    }

    return true;
}

bool GossipSelect_npc_nobblegarden_vendor(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    auto AddItemIfEverythingOkAndWeHaveSmallEggsFunc = [player](int32 itemId, int32 EggCount)
    {
        if (CanStoreNewItem(player, itemId) && RemoveSmallEggsFromPlayer(player, EggCount))
        {
            ItemPrototype const *pProto = ObjectMgr::GetItemPrototype(itemId);
            sLog.outInfo("[EASTER]: Player %s (GUID: %llu) buy %s", player->GetName(), player->GetObjectGuid().GetRawValue(), pProto->Name1);
            player->AddItem(itemId);
        }
    };

    auto AddItemIfEverythingOkAndWeHaveBigEggsFunc = [player](int32 itemId, int32 EggCount)
    {
        if (CanStoreNewItem(player, itemId) && RemoveBigEggsFromPlayer(player, EggCount))
        {
            ItemPrototype const *pProto = ObjectMgr::GetItemPrototype(itemId);
            sLog.outInfo("[EASTER]: Player %s (GUID: %llu) buy %s", player->GetName(), player->GetObjectGuid().GetRawValue(), pProto->Name1);
            player->AddItem(itemId);
        }
    };

    if (sender == GOSSIP_SENDER_MAIN)
    {
        VendorSelection eAction = (VendorSelection)action;
        switch (eAction)
        {
        case LuckyRabbitFoot_1: //5 small eggs
            AddItemIfEverythingOkAndWeHaveSmallEggsFunc(ITEM_LUCKY_RABBIT_FOOT, 5);
            break;
        case EasterDress_1: // 10 small eggs
            AddItemIfEverythingOkAndWeHaveSmallEggsFunc(ITEM_EASTER_DRESS, 10);
            break;
        case BeautufulWildflowers_1: //10 small eggs
            AddItemIfEverythingOkAndWeHaveSmallEggsFunc(ITEM_BEAUTIFUL_WILDFLOWERS, 10);
            break;
        case RabbitSpeedBuff_1: //10 small eggs
            if (RemoveSmallEggsFromPlayer(player, 10))
            {
                player->CastSpell(player, SPELL_SPEED_BUFF, true);
                sLog.outInfo("[EASTER]: Player %s (GUID: %llu) buy speed buff", player->GetName(), player->GetObjectGuid().GetRawValue());
            }
            break;
        case CottonailRabbitPet_1: //50 small eggs
            AddItemIfEverythingOkAndWeHaveSmallEggsFunc(ITEM_COTTONTAIL_RABBIT_MINION, 50);
            break;
        case SpriteDarterEgg_1: //200 small eggs
            AddItemIfEverythingOkAndWeHaveSmallEggsFunc(ITEM_SPRITE_DARTER_EGG, 200);
            break;
        case ApprenticeRidingSkill_1: //300 small eggs
            if (RemoveSmallEggsFromPlayer(player, 300))
            {
                player->CastSpell(player, SPELL_LEARN_APPRENTICE_RIDING, true);
                sLog.outInfo("[EASTER]: Player %s (GUID: %llu) buy APPRENTICE_RIDING", player->GetName(), player->GetObjectGuid().GetRawValue());
            }
            break;
        case BeautufulWildflowers_2: //5 big eggs
            AddItemIfEverythingOkAndWeHaveBigEggsFunc(ITEM_BEAUTIFUL_WILDFLOWERS, 5);
            break;
        case CottonailRabbitPet_2: //10 big eggs
            AddItemIfEverythingOkAndWeHaveBigEggsFunc(ITEM_COTTONTAIL_RABBIT_MINION, 10);
            break;
        case SpriteDarterEgg_2: //100 big eggs
            AddItemIfEverythingOkAndWeHaveBigEggsFunc(ITEM_SPRITE_DARTER_EGG, 100);
            break;
        case OrbOfEaster_2: //150 big eggs
            AddItemIfEverythingOkAndWeHaveBigEggsFunc(ITEM_ORB_OF_EASTER, 150);
            break;
//         case CarrotOnStick_2: //200 big eggs
//             AddItemIfEverythingOkAndWeHaveBigEggsFunc(ITEM_CARROT_ON_STICK, 200);
//             break;
        case EpicRidingSkill_2: //300 big eggs
            if (RemoveBigEggsFromPlayer(player, 300))
            {
                player->CastSpell(player, SPELL_LEARN_JOURNEYMAN_RIDING, true);
                sLog.outInfo("[EASTER]: Player %s (GUID: %llu) buy JOURNEYMAN_RIDING", player->GetName(), player->GetObjectGuid().GetRawValue());
            }
            break;
        default:
            break;
        }
    }
    player->CLOSE_GOSSIP_MENU();
    return true;
}


uint32 npc_rabbit_boss::EnrageTime = 30 * MINUTE * IN_MILLISECONDS; //30 min;
uint32 npc_rabbit_boss::CalmDownTime = 30 * MINUTE * IN_MILLISECONDS; //30 min;
uint32 npc_rabbit_boss::WarnTime = 5 * IN_MILLISECONDS;
float npc_rabbit_boss::VisionRadius = 28.0f;
uint32 npc_rabbit_boss::ChangeOrientationTime = 3 * IN_MILLISECONDS;
uint32 npc_rabbit_boss::EnrageFlamestrikeTime = 500;
uint32 npc_rabbit_boss::BurnDamageRadius = 10;
uint32 npc_rabbit_boss::BurnDamagePercent = 10;

void npc_rabbit_boss::JustDied(Unit*)
{
    Reset();
}

void npc_rabbit_boss::Reset()
{
    SetCombatMovement(false);
    ChangeOrientationTimer = ChangeOrientationTime;
    EnrageTimer = EnrageTime;
    CalmDownTimer = CalmDownTime;
    EnrageFlamestrikeTimer = EnrageFlamestrikeTime;

    for (ObjectGuid RabbitGuid : SpawnedRabbitsGuids)
    {
        if (Map* map = m_creature->GetMap())
        {
            if (Creature* Rabbit = map->GetCreature(RabbitGuid))
            {
                if (TemporarySummon* tempSum = dynamic_cast<TemporarySummon*>(Rabbit))
                {
                    tempSum->UnSummon();
                }
                else
                {
                    Rabbit->DisappearAndDie();
                }
            }
        }
    }
}

void npc_rabbit_boss::UpdateAI(const uint32 deltaTime)
{
    //search all players in Field of View
    //Apply debuff if found
    if (!bOnceSpawned)
    {
        bOnceSpawned = true;
        //Cast shadowform on self
        m_creature->CastSpell(m_creature, 16592, true);
        SpawnRabbits();
        SaySpawnPhrase();
    }

    for (auto PlayerInSightIter = PlayersInSight.begin(); PlayerInSightIter != PlayersInSight.end(); PlayerInSightIter++)
    {
        if (PlayerInSightIter->second < deltaTime)
        {
            //Timer elapsed, polymorph player if it's not out of range
            if (Player* player = m_creature->GetMap()->GetPlayer(PlayerInSightIter->first))
            {
                if (IsPlayerInSight(player))
                {

                    //tobi pizda
                    m_creature->CastSpell(player, SPELL_RABBIT_FEAR, true);
                    //m_creature->MonsterWhisper("[PH] CAST FEAR", player);
                    PlayerInSightIter = PlayersInSight.erase(PlayerInSightIter);
                    if (PlayerInSightIter == PlayersInSight.end()) break;
                }
                else
                {
                    PlayerInSightIter = PlayersInSight.erase(PlayerInSightIter);
                    if (PlayerInSightIter == PlayersInSight.end()) break;
                }
            }
            else
            {
                PlayerInSightIter = PlayersInSight.erase(PlayerInSightIter);
                if (PlayerInSightIter == PlayersInSight.end()) break;
            }
        }
        else
        {
            PlayerInSightIter->second -= deltaTime;
        }
    }


    //Burning Aura around rabbit
    //SpellNonMeleeDamageLog
    if (BurnAuraTimer < deltaTime)
    {

        std::list<Player*> targets;
        // Use visibility modifier for long range players
        MaNGOS::AnyPlayerInObjectRangeCheck check(m_creature, (float)BurnDamageRadius);
        MaNGOS::PlayerListSearcher<MaNGOS::AnyPlayerInObjectRangeCheck> searcher(targets, check);
        Cell::VisitWorldObjects(m_creature, searcher, (float)BurnDamageRadius);
        float fBurnPercent = float(BurnDamagePercent) / 100.0f;
        for (Player* pl : targets)
        {
            m_creature->SpellNonMeleeDamageLog(pl, 14796, pl->GetMaxHealth() * fBurnPercent);
        }

        uint32 elapsed = deltaTime - BurnAuraTimer;
        elapsed = std::min<uint32>(elapsed, 1000);
        BurnAuraTimer = 1000 - elapsed;
    }
    else
        BurnAuraTimer -= deltaTime;


    //Every 15 sec change direction
    if (ChangeOrientationTimer < deltaTime)
    {
        float randOrientation = frand(0.0f, 2 * M_PI_F);
        m_creature->SetFacingTo(randOrientation);
        ChangeOrientationTimer = ChangeOrientationTime;
    }
    else
        ChangeOrientationTimer -= deltaTime;

    if (EnrageTimer < deltaTime)
    {
        Enrage();
    }
    else if (!bEnrageMode)
    {
        EnrageTimer -= deltaTime;
    }

    if (bEnrageMode)
    {
        if (EnrageFlamestrikeTimer < deltaTime)
        {
            EnrageFlamestrikeTimer = EnrageFlamestrikeTime;
            DoCastSpellIfCan(m_creature, SPELL_FLAMESTRIKE_ID, CAST_FORCE_CAST | CAST_TRIGGERED);
        }
        else
            EnrageFlamestrikeTimer -= deltaTime;


        if (m_creature->GetHealthPercent() < 50.0f || CalmDownTimer < deltaTime)
        {
            //Drop enrage mode
            Calmdown();
        }
        else
            CalmDownTimer -= deltaTime;
    }
}

void npc_rabbit_boss::MoveInLineOfSight(Unit* unit)
{
    if (Player* player = unit->ToPlayer())
    {
        //make additional check for direction
        if (IsPlayerInSight(player) && !player->HasAura(SPELL_RABBIT_FEAR))
        {
            //add to list with back timer
            auto PlayerIter = PlayersInSight.find(player->GetObjectGuid());
            if (PlayerIter == PlayersInSight.end())
            {
                PlayersInSight.insert(std::pair<ObjectGuid, uint32>(player->GetObjectGuid(), WarnTime));

                //Warn player once
                WarnPlayer(player);
            }
        }
    }
}

void npc_rabbit_boss::GetAIInformation(ChatHandler& handler)
{
    handler.PSendSysMessage("npc_rabbit_boss info");
    for (auto PlayerInSightIter = PlayersInSight.begin(); PlayerInSightIter != PlayersInSight.end(); PlayerInSightIter++)
    {
        if (Player* player = m_creature->GetMap()->GetPlayer(PlayerInSightIter->first))
        {
            handler.PSendSysMessage("GUID: %llu, player: \"%s\", Timer: %d", PlayerInSightIter->first.GetRawValue(), player->GetName(), PlayerInSightIter->second);
        }
        else
        {
            handler.PSendSysMessage("GUID: %llu, player offline, Timer: %d", PlayerInSightIter->first.GetRawValue(), PlayerInSightIter->second);
        }
    }
    handler.PSendSysMessage("Spawned rabbits: %zu", SpawnedRabbitsGuids.size());
    handler.PSendSysMessage("Change Orientation Timer: %u", ChangeOrientationTimer);
    handler.PSendSysMessage("Is Enrage: %s; Enrage Timer: %u; Enrage Flamestrike Timer: %u", bEnrageMode ? "Yes" : "No", EnrageTimer, EnrageFlamestrikeTimer);
    handler.PSendSysMessage("CalmDown Timer: %u", CalmDownTimer);
    //ScriptedAI::GetAIInformation(handler);
}

void npc_rabbit_boss::SpawnRabbits()
{
    for (int32 i = 0; i < RABBIT_COUNT; ++i)
    {
        float x = m_creature->GetPositionX() + frand(-2.0f, 2.0f);
        float y = m_creature->GetPositionY() + frand(-2.0f, 2.0f);
        float z = m_creature->GetMap()->GetHeight(x, y, m_creature->GetPositionZ() + 5.0f, true, 15.0f);
        if (z > VMAP_INVALID_HEIGHT)
        {
            if (Creature* pRabbit = m_creature->SummonCreature(NPC_RABBIT_MINION, x, y, z, m_creature->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN))
            {
                SpawnedRabbitsGuids.push_back(pRabbit->GetObjectGuid());
            }
        }
    }
}

void npc_rabbit_boss::SaySpawnPhrase()
{
    int32 RandomedGreetingTxt = urand(0, 1);
    m_creature->MonsterYellToZone(NOST_TEXT(RABBIT_BOSS_GREETINGS_TXT_ID) + RandomedGreetingTxt);
}

void npc_rabbit_boss::SayEnragePhrase()
{
    int32 RandomedEnrageTxt = urand(0, 2);
    m_creature->MonsterYellToZone(NOST_TEXT(RABBIT_BOSS_ENRAGE_TXT_ID) + RandomedEnrageTxt);
}

void npc_rabbit_boss::SayBattlePhrase()
{
    int32 RandomedEnrageTxt = urand(0, 2);
    m_creature->MonsterYell(NOST_TEXT(RABBIT_BOSS_BATTLE_TXT_ID) + RandomedEnrageTxt);
}

void npc_rabbit_boss::SayCalmPhrase()
{
    //Get random player nearly
    const char* PhraseParam = "People";
    if (Player* player = GetPlayerAtMinimumRange(300.0f))
    {
        PhraseParam = player->GetName();
    }
    int32 RandomedCalmdownTxt = urand(0, 5);
    m_creature->PMonsterSay(NOST_TEXT(RABBIT_BOSS_CALM_TXT_ID) + RandomedCalmdownTxt, PhraseParam);
}

void npc_rabbit_boss::Calmdown()
{
    bEnrageMode = false;
    SayCalmPhrase();
    m_creature->SetObjectScale(m_creature->getNativeScale());
    m_creature->ClearTemporaryFaction();
    m_creature->SetHealth(m_creature->GetMaxHealth());
    CalmDownTimer = CalmDownTime;
    m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
    m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    m_creature->RemoveAllAttackers();
}

void npc_rabbit_boss::Enrage()
{
    bEnrageMode = true;
    EnrageTimer = EnrageTime;
    SayEnragePhrase();
    m_creature->SetObjectScale(7.0f);
    m_creature->SetFactionTemporary(168); //FACTION_ENEMY
    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
}

void npc_rabbit_boss::GetData(uint32 dataIndx, float& Data)
{
    ChatHandler::EasterDataIndexes eDataIndx = (ChatHandler::EasterDataIndexes)dataIndx;

    if (eDataIndx == ChatHandler::EasterDataIndexes::VisionRadius)
    {
        Data = VisionRadius;
    }
}

void npc_rabbit_boss::GetData(uint32 dataIndx, uint32& Data)
{
    ChatHandler::EasterDataIndexes eDataIndx = (ChatHandler::EasterDataIndexes)dataIndx;

    switch (eDataIndx)
    {
    case ChatHandler::EnrageTime:
        Data = EnrageTime;
        break;
    case ChatHandler::CalmdownTime:
        Data = CalmDownTime;
        break;
    case ChatHandler::WarnTime:
        Data = WarnTime;
        break;
    case ChatHandler::OrientationTime:
        Data = ChangeOrientationTime;
        break;
    case ChatHandler::EnrageFlamestrikeTime:
        Data = EnrageFlamestrikeTime;
    case ChatHandler::BurnAuraDamagePercent:
        Data = BurnDamagePercent;
        break;
    case ChatHandler::BurnAuraDamageRadius:
        Data = BurnDamageRadius;
        break;
    default:
        break;
    }
}

void npc_rabbit_boss::SetData(uint32 dataIndx, float Data)
{
    ChatHandler::EasterDataIndexes eDataIndx = (ChatHandler::EasterDataIndexes)dataIndx;

    if (eDataIndx == ChatHandler::EasterDataIndexes::VisionRadius)
    {
        VisionRadius = Data;
    }
}

void npc_rabbit_boss::SetData(uint32 dataIndx, uint32 Data)
{
    ChatHandler::EasterDataIndexes eDataIndx = (ChatHandler::EasterDataIndexes)dataIndx;

    switch (eDataIndx)
    {
    case ChatHandler::EnrageTime:
        EnrageTime = Data;
        break;
    case ChatHandler::CalmdownTime:
        CalmDownTime = Data;
        break;
    case ChatHandler::WarnTime:
        WarnTime = Data;
        break;
    case ChatHandler::OrientationTime:
        ChangeOrientationTime = Data;
        break;
    case ChatHandler::EnrageFlamestrikeTime:
        EnrageFlamestrikeTime = Data;
        break;
    case ChatHandler::BurnAuraDamagePercent:
        BurnDamagePercent = Data;
        break;
    case ChatHandler::BurnAuraDamageRadius:
        BurnDamageRadius = Data;
        break;
    default:
        break;
    }
}

void npc_rabbit_boss::DoAction(const uint32 actionId)
{
    if (actionId == 1)
    {
        Enrage();
    }
    else if (actionId == 2)
    {
        Calmdown();
    }
}

void npc_rabbit_boss::AttackStart(Unit* unit)
{
    m_creature->AttackStop();
}

void npc_rabbit_boss::EnterCombat(Unit*)
{
    m_creature->AttackStop();
}

bool npc_rabbit_boss::IsPlayerInSight(Player* player)
{
    return m_creature->HasInArc(M_PI_F, player) && m_creature->GetDistance2d(player) < VisionRadius && !player->isGameMaster();
}

void npc_rabbit_boss::WarnPlayer(Player* player)
{
    //m_creature->MonsterSay()
    uint32 RandomedTextId = urand(0, 4);
    const char* PlayerWarnText = player->GetSession()->GetMangosString(NOST_TEXT(RABBIT_BOSS_WARN_TXT_ID + RandomedTextId));
    char TempBuffer[1024];
    memset(TempBuffer, 0, sizeof(TempBuffer));
    snprintf(TempBuffer, 1024, PlayerWarnText, player->GetName());
    player->SendRaidWarning(TempBuffer);
}

uint32 npc_rabbit_minion::EggTime = 300 * IN_MILLISECONDS; //5 min;

void npc_rabbit_minion::Reset()
{
    layEggTimer = 0.0f;

}

void npc_rabbit_minion::UpdateAI(const uint32 deltaTime)
{
    //LAY EGGS!
    if (layEggTimer < deltaTime)
    {
        LayEgg();
    }
    else
        layEggTimer -= deltaTime;


    ScriptedAI::UpdateAI(deltaTime);
}

void npc_rabbit_minion::GetAIInformation(ChatHandler& handler)
{
    handler.PSendSysMessage("Lay Egg Timer: %u", layEggTimer);
    handler.PSendSysMessage("GLOBAL Lay Egg cooldown: %u", EggTime);
}

void npc_rabbit_minion::GetData(uint32 dataIndx, uint32& Data)
{
    ChatHandler::EasterDataIndexes eDataIndx = (ChatHandler::EasterDataIndexes)dataIndx;

    if (eDataIndx == ChatHandler::EasterDataIndexes::RabbitLayEggTime)
    {
        Data = EggTime;
    }
}

void npc_rabbit_minion::SetData(uint32 dataIndx, uint32 Data)
{
    ChatHandler::EasterDataIndexes eDataIndx = (ChatHandler::EasterDataIndexes)dataIndx;

    if (eDataIndx == ChatHandler::EasterDataIndexes::RabbitLayEggTime)
    {
        EggTime = Data;
    }
}

void npc_rabbit_minion::LayEgg()
{
    float dZ = m_creature->GetMap()->GetHeight(m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ() + 2.0f);
    m_creature->SummonGameObject(GO_SMALL_EGG,
        m_creature->GetPositionX(), m_creature->GetPositionY(), dZ, //Position
        0.73f, 0.0f, 0.0f, 0.0f, 0.0f, //Rotation stuff
        EggTime, true);
    layEggTimer = EggTime;
}



CreatureAI* Create_npc_rabbit_boss(Creature* creature)
{
    return new npc_rabbit_boss(creature);
}

CreatureAI* Create_npc_rabbit_minion(Creature* creature)
{
    return new npc_rabbit_minion(creature);
}

void AddSC_world_nobblegarden_elysium()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "go_nobblegarden_egg";
    //newscript->GOOpen = go_nobblegarden_egg_Open;
    newscript->pGOHello = go_nobblegarden_egg_Open;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_nobblegarden_rabbit_boss";
    newscript->GetAI = Create_npc_rabbit_boss;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_nobblegarden_rabbit_minion";
    newscript->GetAI = Create_npc_rabbit_minion;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_nobblegarden_vendor";
    newscript->pGossipHello = GossipHello_npc_nobblegarden_vendor;
    newscript->pGossipSelect = GossipSelect_npc_nobblegarden_vendor;
    newscript->RegisterSelf();
}

