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
SDName: Npc_Professions
SD%Complete: 80
SDComment: Provides learn/unlearn/relearn-options for professions. Not supported: Unlearn engineering, re-learn engineering, re-learn leatherworking.
SDCategory: NPCs
EndScriptData */

#include "scriptPCH.h"

/*
A few notes for future developement:
- A full implementation of gossip for GO's is required. They must have the same scripting capabilities as creatures. Basically,
there is no difference here (except that default text is chosen with `gameobject_template`.`data3` (for GO type2, different dataN for a few others)
- It's possible blacksmithing still require some tweaks and adjustments due to the way we _have_ to use reputation.
*/

/*
-- UPDATE `gameobject_template` SET `ScriptName` = 'go_soothsaying_for_dummies' WHERE `entry` = 177226;
*/

/*###
# to be removed from here (->ncp_text). This is data for database projects.
###*/
#define TALK_MUST_UNLEARN_WEAPON    "You must forget your weapon type specialty before I can help you. Go to Everlook in Winterspring and seek help there."

#define TALK_HAMMER_LEARN           "Ah, a seasoned veteran you once were. I know you are capable, you merely need to ask and I shall teach you the way of the hammersmith."
#define TALK_AXE_LEARN              "Ah, a seasoned veteran you once were. I know you are capable, you merely need to ask and I shall teach you the way of the axesmith."
#define TALK_SWORD_LEARN            "Ah, a seasoned veteran you once were. I know you are capable, you merely need to ask and I shall teach you the way of the swordsmith."

#define TALK_HAMMER_UNLEARN         "Forgetting your Hammersmithing skill is not something to do lightly. If you choose to abandon it you will forget all recipes that require Hammersmithing to create!"
#define TALK_AXE_UNLEARN            "Forgetting your Axesmithing skill is not something to do lightly. If you choose to abandon it you will forget all recipes that require Axesmithing to create!"
#define TALK_SWORD_UNLEARN          "Forgetting your Swordsmithing skill is not something to do lightly. If you choose to abandon it you will forget all recipes that require Swordsmithing to create!"

/*###
# generic defines
###*/

#define GOSSIP_SENDER_LEARN         50
#define GOSSIP_SENDER_UNLEARN       51
#define GOSSIP_SENDER_CHECK         52

/*###
# gossip item and box texts
###*/

#define GOSSIP_WEAPON_LEARN         "Please teach me how to become a Weaponsmith"
#define GOSSIP_WEAPON_UNLEARN       "I wish to unlearn the art of Weaponsmithing"
#define GOSSIP_ARMOR_LEARN          "Please teach me how to become a Armorsmith"
#define GOSSIP_ARMOR_UNLEARN        "I wish to unlearn the art of Armorsmithing"

#define GOSSIP_UNLEARN_SMITH_SPEC   "I wish to unlearn my blacksmith specialty"
#define BOX_UNLEARN_ARMORORWEAPON   "Do you really want to unlearn your blacksmith specialty and lose all associated recipes? \n Cost: "

#define GOSSIP_LEARN_HAMMER         "Please teach me how to become a Hammersmith, Lilith"
#define GOSSIP_UNLEARN_HAMMER       "I wish to unlearn Hammersmithing"
#define GOSSIP_LEARN_AXE            "Please teach me how to become a Axesmith, Kilram"
#define GOSSIP_UNLEARN_AXE          "I wish to unlearn Axesmithing"
#define GOSSIP_LEARN_SWORD          "Please teach me how to become a Swordsmith, Seril"
#define GOSSIP_UNLEARN_SWORD        "I wish to unlearn Swordsmithing"

#define BOX_UNLEARN_WEAPON_SPEC     "Do you really want to unlearn your weaponsmith specialty and lose all associated recipes? \n Cost: "

#define GOSSIP_LEARN_DRAGON         "I am absolutely certain that i want to learn dragonscale leatherworking"
#define GOSSIP_UNLEARN_DRAGON       "I wish to unlearn Dragonscale Leatherworking"
#define GOSSIP_LEARN_ELEMENTAL      "I am absolutely certain that i want to learn elemental leatherworking"
#define GOSSIP_UNLEARN_ELEMENTAL    "I wish to unlearn Elemental Leatherworking"
#define GOSSIP_LEARN_TRIBAL         "I am absolutely certain that i want to learn tribal leatherworking"
#define GOSSIP_UNLEARN_TRIBAL       "I wish to unlearn Tribal Leatherworking"

#define BOX_UNLEARN_LEATHER_SPEC    "Do you really want to unlearn your leatherworking specialty and lose all associated recipes? \n Cost: "

#define GOSSIP_LEARN_GOBLIN         "I am absolutely certain that i want to learn Goblin engineering"
#define GOSSIP_LEARN_GNOMISH        "I am absolutely certain that i want to learn Gnomish engineering"

/*###
# spells defines
###*/

#define S_WEAPON                9787
#define S_ARMOR                 9788
#define S_HAMMER                17040
#define S_AXE                   17041
#define S_SWORD                 17039

#define S_LEARN_WEAPON          9789
#define S_LEARN_ARMOR           9790
#define S_LEARN_HAMMER          17044
#define S_LEARN_AXE             17043
#define S_LEARN_SWORD           17042

#define S_UNLEARN_WEAPON        36436
#define S_UNLEARN_ARMOR         36435
#define S_UNLEARN_HAMMER        36441
#define S_UNLEARN_AXE           36439
#define S_UNLEARN_SWORD         36438

#define S_REP_ARMOR             17451
#define S_REP_WEAPON            17452

#define REP_ARMOR               46
#define REP_WEAPON              289
#define REP_HAMMER              569
#define REP_AXE                 570
#define REP_SWORD               571

#define S_DRAGON                10656
#define S_ELEMENTAL             10658
#define S_TRIBAL                10660

#define S_LEARN_DRAGON          10657
#define S_LEARN_ELEMENTAL       10659
#define S_LEARN_TRIBAL          10661

#define S_UNLEARN_DRAGON        36434
#define S_UNLEARN_ELEMENTAL     36328
#define S_UNLEARN_TRIBAL        36433

#define S_GOBLIN                20222
#define S_GNOMISH               20219

#define S_LEARN_GOBLIN          20221
#define S_LEARN_GNOMISH         20220

/*###
# formulas to calculate unlearning cost
###*/

int32 GetUnlearnCostMedium(Player* pPlayer)                 //blacksmith, leatherwork
{
    uint32 level = pPlayer->getLevel();

    if (level < 51)
        return 250000;
    else if (level < 66)
        return 500000;
    else
        return 1000000;
}

int32 GetUnlearnCostLow(Player* pPlayer)                    //blacksmith
{
    if (pPlayer->getLevel() < 66)
        return 50000;
    else
        return 100000;
}

/*###
# unlearning related profession spells
###*/

bool EquippedOk(Player* pPlayer, uint32 spellId)
{
    SpellEntry const* spell = sSpellMgr.GetSpellEntry(spellId);

    if (!spell)
        return false;

    for (int i = 0; i < 3; ++i)
    {
        uint32 reqSpell = spell->EffectTriggerSpell[i];
        if (!reqSpell)
            continue;

        Item* pItem;
        for (int j = EQUIPMENT_SLOT_START; j < EQUIPMENT_SLOT_END; ++j)
        {
            pItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, j);
            if (pItem)
                if (pItem->GetProto()->RequiredSpell == reqSpell)
                {
                    //pPlayer has item equipped that require specialty. Not allow to unlearn, player has to unequip first
                    sLog.outDebug("player attempt to unlearn spell %u, but item %u is equipped.", reqSpell, pItem->GetProto()->ItemId);
                    return false;
                }
        }
    }
    return true;
}

void ProfessionUnlearnSpells(Player* pPlayer, uint32 type)
{
    switch (type)
    {
        case 36436:                                         // S_UNLEARN_WEAPON
            pPlayer->removeSpell(36125);                     // Light Earthforged Blade
            pPlayer->removeSpell(36128);                     // Light Emberforged Hammer
            pPlayer->removeSpell(36126);                     // Light Skyforged Axe
            break;
        case 36435:                                         // S_UNLEARN_ARMOR
            pPlayer->removeSpell(36122);                     // Earthforged Leggings
            pPlayer->removeSpell(36129);                     // Heavy Earthforged Breastplate
            pPlayer->removeSpell(36130);                     // Stormforged Hauberk
            pPlayer->removeSpell(34533);                     // Breastplate of Kings
            pPlayer->removeSpell(34529);                     // Nether Chain Shirt
            pPlayer->removeSpell(34534);                     // Bulwark of Kings
            pPlayer->removeSpell(36257);                     // Bulwark of the Ancient Kings
            pPlayer->removeSpell(36256);                     // Embrace of the Twisting Nether
            pPlayer->removeSpell(34530);                     // Twisting Nether Chain Shirt
            pPlayer->removeSpell(36124);                     // Windforged Leggings
            break;
        case 36441:                                         // S_UNLEARN_HAMMER
            pPlayer->removeSpell(36262);                     // Dragonstrike
            pPlayer->removeSpell(34546);                     // Dragonmaw
            pPlayer->removeSpell(34545);                     // Drakefist Hammer
            pPlayer->removeSpell(36136);                     // Lavaforged Warhammer
            pPlayer->removeSpell(34547);                     // Thunder
            pPlayer->removeSpell(34567);                     // Deep Thunder
            pPlayer->removeSpell(36263);                     // Stormherald
            pPlayer->removeSpell(36137);                     // Great Earthforged Hammer
            break;
        case 36439:                                         // S_UNLEARN_AXE
            pPlayer->removeSpell(36260);                     // Wicked Edge of the Planes
            pPlayer->removeSpell(34562);                     // Black Planar Edge
            pPlayer->removeSpell(34541);                     // The Planar Edge
            pPlayer->removeSpell(36134);                     // Stormforged Axe
            pPlayer->removeSpell(36135);                     // Skyforged Great Axe
            pPlayer->removeSpell(36261);                     // Bloodmoon
            pPlayer->removeSpell(34543);                     // Lunar Crescent
            pPlayer->removeSpell(34544);                     // Mooncleaver
            break;
        case 36438:                                         // S_UNLEARN_SWORD
            pPlayer->removeSpell(36258);                     // Blazefury
            pPlayer->removeSpell(34537);                     // Blazeguard
            pPlayer->removeSpell(34535);                     // Fireguard
            pPlayer->removeSpell(36131);                     // Windforged Rapier
            pPlayer->removeSpell(36133);                     // Stoneforged Claymore
            pPlayer->removeSpell(34538);                     // Lionheart Blade
            pPlayer->removeSpell(34540);                     // Lionheart Champion
            pPlayer->removeSpell(36259);                     // Lionheart Executioner
            break;
        case 36434:                                         // S_UNLEARN_DRAGON
            pPlayer->removeSpell(36076);                     // Dragonstrike Leggings
            pPlayer->removeSpell(36079);                     // Golden Dragonstrike Breastplate
            pPlayer->removeSpell(35576);                     // Ebon Netherscale Belt
            pPlayer->removeSpell(35577);                     // Ebon Netherscale Bracers
            pPlayer->removeSpell(35575);                     // Ebon Netherscale Breastplate
            pPlayer->removeSpell(35582);                     // Netherstrike Belt
            pPlayer->removeSpell(35584);                     // Netherstrike Bracers
            pPlayer->removeSpell(35580);                     // Netherstrike Breastplate
            break;
        case 36328:                                         // S_UNLEARN_ELEMENTAL
            pPlayer->removeSpell(36074);                     // Blackstorm Leggings
            pPlayer->removeSpell(36077);                     // Primalstorm Breastplate
            pPlayer->removeSpell(35590);                     // Primalstrike Belt
            pPlayer->removeSpell(35591);                     // Primalstrike Bracers
            pPlayer->removeSpell(35589);                     // Primalstrike Vest
            break;
        case 36433:                                         // S_UNLEARN_TRIBAL
            pPlayer->removeSpell(35585);                     // Windhawk Hauberk
            pPlayer->removeSpell(35587);                     // Windhawk Belt
            pPlayer->removeSpell(35588);                     // Windhawk Bracers
            pPlayer->removeSpell(36075);                     // Wildfeather Leggings
            pPlayer->removeSpell(36078);                     // Living Crystal Breastplate
            break;
    }
}

/*###
# start menues blacksmith
###*/

bool HasWeaponSub(Player* pPlayer)
{
    if (pPlayer->HasSpell(S_HAMMER) || pPlayer->HasSpell(S_AXE) || pPlayer->HasSpell(S_SWORD))
        return true;
    return false;
}

bool GossipHello_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());
    if (pCreature->isVendor())
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
    if (pCreature->isTrainer())
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

    uint32 eCreature = pCreature->GetEntry();
    //WEAPONSMITH & ARMORSMITH
    if (pPlayer->GetBaseSkillValue(SKILL_BLACKSMITHING) >= 225)
    {
        switch (eCreature)
        {
            case 11145:                                     //Myolor Sunderfury
            case 11176:                                     //Krathok Moltenfist
                if (!pPlayer->HasSpell(S_ARMOR) && !pPlayer->HasSpell(S_WEAPON) && pPlayer->GetReputationRank(REP_ARMOR) ==  REP_FRIENDLY)
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARMOR_LEARN,   GOSSIP_SENDER_MAIN,          GOSSIP_ACTION_INFO_DEF + 1);
                if (!pPlayer->HasSpell(S_WEAPON) && !pPlayer->HasSpell(S_ARMOR) && pPlayer->GetReputationRank(REP_WEAPON) == REP_FRIENDLY)
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WEAPON_LEARN,  GOSSIP_SENDER_MAIN,          GOSSIP_ACTION_INFO_DEF + 2);
                break;
            case 11146:                                     //Ironus Coldsteel
            case 11178:                                     //Borgosh Corebender
                if (pPlayer->HasSpell(S_WEAPON))
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WEAPON_UNLEARN,    GOSSIP_SENDER_UNLEARN,   GOSSIP_ACTION_INFO_DEF + 3);
                break;
            case 5164:                                      //Grumnus Steelshaper
            case 11177:                                     //Okothos Ironrager
                if (pPlayer->HasSpell(S_ARMOR))
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARMOR_UNLEARN,     GOSSIP_SENDER_UNLEARN,   GOSSIP_ACTION_INFO_DEF + 4);
                break;
        }
    }
    //WEAPONSMITH SPEC
    if (pPlayer->HasSpell(S_WEAPON) && pPlayer->getLevel() > 49 && pPlayer->GetBaseSkillValue(SKILL_BLACKSMITHING) >= 250)
    {
        switch (eCreature)
        {
            case 11191:                                     //Lilith the Lithe
                if (!HasWeaponSub(pPlayer))
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_HAMMER,       GOSSIP_SENDER_LEARN,    GOSSIP_ACTION_INFO_DEF + 5);
                if (pPlayer->HasSpell(S_HAMMER))
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_HAMMER,     GOSSIP_SENDER_UNLEARN,  GOSSIP_ACTION_INFO_DEF + 8);
                break;
            case 11192:                                     //Kilram
                if (!HasWeaponSub(pPlayer))
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_AXE,          GOSSIP_SENDER_LEARN,    GOSSIP_ACTION_INFO_DEF + 6);
                if (pPlayer->HasSpell(S_AXE))
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_AXE,        GOSSIP_SENDER_UNLEARN,  GOSSIP_ACTION_INFO_DEF + 9);
                break;
            case 11193:                                     //Seril Scourgebane
                if (!HasWeaponSub(pPlayer))
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_SWORD,        GOSSIP_SENDER_LEARN,    GOSSIP_ACTION_INFO_DEF + 7);
                if (pPlayer->HasSpell(S_SWORD))
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_SWORD,      GOSSIP_SENDER_UNLEARN,  GOSSIP_ACTION_INFO_DEF + 10);
                break;
        }
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

void SendActionMenu_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch (uiAction)
    {
        case GOSSIP_ACTION_TRADE:
            pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_TRAIN:
            pPlayer->SEND_TRAINERLIST(pCreature->GetGUID());
            break;
        //Learn Armor/Weapon
        case GOSSIP_ACTION_INFO_DEF + 1:
            if (!pPlayer->HasSpell(S_ARMOR))
            {
                pPlayer->CastSpell(pPlayer, S_LEARN_ARMOR, true);
                //pCreature->CastSpell(pPlayer, S_REP_ARMOR, true);
            }
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            if (!pPlayer->HasSpell(S_WEAPON))
            {
                pPlayer->CastSpell(pPlayer, S_LEARN_WEAPON, true);
                //pCreature->CastSpell(pPlayer, S_REP_WEAPON, true);
            }
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        //Unlearn Armor/Weapon
        case GOSSIP_ACTION_INFO_DEF + 3:
            if (HasWeaponSub(pPlayer))
            {
                //unknown textID (TALK_MUST_UNLEARN_WEAPON)
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
            }
            else if (EquippedOk(pPlayer, S_UNLEARN_WEAPON))
            {
                if (pPlayer->GetMoney() >= uint32(GetUnlearnCostLow(pPlayer)))
                {
                    pPlayer->CastSpell(pPlayer, S_UNLEARN_WEAPON, true);
                    ProfessionUnlearnSpells(pPlayer, S_UNLEARN_WEAPON);
                    pPlayer->ModifyMoney(-GetUnlearnCostLow(pPlayer));
                    pCreature->CastSpell(pPlayer, S_REP_ARMOR, true);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
                else
                    pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
            }
            else
            {
                pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, NULL, NULL);
                pPlayer->CLOSE_GOSSIP_MENU();
            }
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:
            if (EquippedOk(pPlayer, S_UNLEARN_ARMOR))
            {
                if (pPlayer->GetMoney() >= uint32(GetUnlearnCostLow(pPlayer)))
                {
                    pPlayer->CastSpell(pPlayer, S_UNLEARN_ARMOR, true);
                    ProfessionUnlearnSpells(pPlayer, S_UNLEARN_ARMOR);
                    pPlayer->ModifyMoney(-GetUnlearnCostLow(pPlayer));
                    pCreature->CastSpell(pPlayer, S_REP_WEAPON, true);
                }
                else
                    pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
            }
            else
                pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, NULL, NULL);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        //Learn Hammer/Axe/Sword
        case GOSSIP_ACTION_INFO_DEF + 5:
            pPlayer->CastSpell(pPlayer, S_LEARN_HAMMER, true);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:
            pPlayer->CastSpell(pPlayer, S_LEARN_AXE, true);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:
            pPlayer->CastSpell(pPlayer, S_LEARN_SWORD, true);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        //Unlearn Hammer/Axe/Sword
        case GOSSIP_ACTION_INFO_DEF + 8:
            if (EquippedOk(pPlayer, S_UNLEARN_HAMMER))
            {
                if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
                {
                    pPlayer->CastSpell(pPlayer, S_UNLEARN_HAMMER, true);
                    ProfessionUnlearnSpells(pPlayer, S_UNLEARN_HAMMER);
                    pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
                }
                else
                    pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
            }
            else
                pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, NULL, NULL);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:
            if (EquippedOk(pPlayer, S_UNLEARN_AXE))
            {
                if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
                {
                    pPlayer->CastSpell(pPlayer, S_UNLEARN_AXE, true);
                    ProfessionUnlearnSpells(pPlayer, S_UNLEARN_AXE);
                    pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
                }
                else
                    pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
            }
            else
                pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, NULL, NULL);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:
            if (EquippedOk(pPlayer, S_UNLEARN_SWORD))
            {
                if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
                {
                    pPlayer->CastSpell(pPlayer, S_UNLEARN_SWORD, true);
                    ProfessionUnlearnSpells(pPlayer, S_UNLEARN_SWORD);
                    pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
                }
                else
                    pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
            }
            else
                pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, NULL, NULL);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
    }
}

void SendConfirmLearn_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    if (uiAction)
    {
        uint32 eCreature = pCreature->GetEntry();
        switch (eCreature)
        {
            case 11191:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_HAMMER, GOSSIP_SENDER_CHECK, uiAction);
                //unknown textID (TALK_HAMMER_LEARN)
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
                break;
            case 11192:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_AXE,    GOSSIP_SENDER_CHECK, uiAction);
                //unknown textID (TALK_AXE_LEARN)
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
                break;
            case 11193:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_SWORD,  GOSSIP_SENDER_CHECK, uiAction);
                //unknown textID (TALK_SWORD_LEARN)
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
                break;
        }
    }
}

void SendConfirmUnlearn_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    if (uiAction)
    {
        uint32 eCreature = pCreature->GetEntry();
        switch (eCreature)
        {
            case 11146:                                     //Ironus Coldsteel
            case 11178:                                     //Borgosh Corebender
            case 5164:                                      //Grumnus Steelshaper
            case 11177:                                     //Okothos Ironrager
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_SMITH_SPEC, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_ARMORORWEAPON, /*DoLowUnlearnCost(pPlayer),*/ false);
                //unknown textID (TALK_UNLEARN_AXEORWEAPON)
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
                break;

            case 11191:
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_HAMMER, GOSSIP_SENDER_CHECK, uiAction,    BOX_UNLEARN_WEAPON_SPEC, /*DoMedUnlearnCost(pPlayer),*/ false);
                //unknown textID (TALK_HAMMER_UNLEARN)
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
                break;
            case 11192:
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_AXE, GOSSIP_SENDER_CHECK, uiAction,       BOX_UNLEARN_WEAPON_SPEC, /*DoMedUnlearnCost(pPlayer),*/ false);
                //unknown textID (TALK_AXE_UNLEARN)
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
                break;
            case 11193:
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_SWORD, GOSSIP_SENDER_CHECK, uiAction,     BOX_UNLEARN_WEAPON_SPEC, /*DoMedUnlearnCost(pPlayer),*/ false);
                //unknown textID (TALK_SWORD_UNLEARN)
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
                break;
        }
    }
}

bool GossipSelect_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:
            SendActionMenu_npc_prof_blacksmith(pPlayer, pCreature, uiAction);
            break;
        case GOSSIP_SENDER_LEARN:
            SendConfirmLearn_npc_prof_blacksmith(pPlayer, pCreature, uiAction);
            break;
        case GOSSIP_SENDER_UNLEARN:
            SendConfirmUnlearn_npc_prof_blacksmith(pPlayer, pCreature, uiAction);
            break;
        case GOSSIP_SENDER_CHECK:
            SendActionMenu_npc_prof_blacksmith(pPlayer, pCreature, uiAction);
            break;
    }
    return true;
}

/*bool QuestComplete_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if ((pQuest->GetQuestId() == 5283) || (pQuest->GetQuestId() == 5301))             //armorsmith
        pCreature->CastSpell(pPlayer, 17451, true);

    if ((pQuest->GetQuestId() == 5284) || (pQuest->GetQuestId() == 5302))             //weaponsmith
        pCreature->CastSpell(pPlayer, 17452, true);

    return true;
}*/

/*###
# engineering trinkets
###*/

enum
{
    NPC_ZAP                     = 14742,
    NPC_JHORDY                  = 14743,
    NPC_KABLAM                  = 21493,
    NPC_SMILES                  = 21494,

    SPELL_LEARN_TO_EVERLOOK     = 23490,
    SPELL_LEARN_TO_GADGET       = 23491,
    SPELL_LEARN_TO_AREA52       = 36956,
    SPELL_LEARN_TO_TOSHLEY      = 36957,

    SPELL_TO_EVERLOOK           = 23486,
    SPELL_TO_GADGET             = 23489,
    SPELL_TO_AREA52             = 36954,
    SPELL_TO_TOSHLEY            = 36955,

    ITEM_GNOMISH_CARD           = 10790,
    ITEM_GOBLIN_CARD            = 10791
};

#define GOSSIP_ITEM_ZAP         "[PH] Unknown"
#define GOSSIP_ITEM_JHORDY      "I must build a beacon for this marvelous device!"
#define GOSSIP_ITEM_KABLAM      "[PH] Unknown"
#define GOSSIP_ITEM_SMILES      "[PH] Unknown"

bool GossipHello_npc_engineering_tele_trinket(Player* pPlayer, Creature* pCreature)
{
    uint32 uiNpcTextId = 0;
    std::string strGossipItem;
    bool bCanLearn = false;

    if (pPlayer->HasSkill(SKILL_ENGINEERING))
    {
        switch (pCreature->GetEntry())
        {
            case NPC_ZAP:
                uiNpcTextId = 7249;
                if (pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 260 && pPlayer->HasSpell(S_GOBLIN))
                {
                    if (!pPlayer->HasSpell(SPELL_TO_EVERLOOK))
                    {
                        bCanLearn = true;
                        strGossipItem = GOSSIP_ITEM_ZAP;
                    }
                    else if (pPlayer->HasSpell(SPELL_TO_EVERLOOK))
                        uiNpcTextId = 0;
                }
                break;
            case NPC_JHORDY:
                uiNpcTextId = 7251;
                if (pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 260 && pPlayer->HasSpell(S_GNOMISH))
                {
                    if (!pPlayer->HasSpell(SPELL_TO_GADGET))
                    {
                        bCanLearn = true;
                        strGossipItem = GOSSIP_ITEM_JHORDY;
                    }
                    else if (pPlayer->HasSpell(SPELL_TO_GADGET))
                        uiNpcTextId = 7252;
                }
                break;
            case NPC_KABLAM:
                uiNpcTextId = 10365;
                if (pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 350 && pPlayer->HasSpell(S_GOBLIN))
                {
                    if (!pPlayer->HasSpell(SPELL_TO_AREA52))
                    {
                        bCanLearn = true;
                        strGossipItem = GOSSIP_ITEM_KABLAM;
                    }
                    else if (pPlayer->HasSpell(SPELL_TO_AREA52))
                        uiNpcTextId = 0;
                }
                break;
            case NPC_SMILES:
                uiNpcTextId = 10363;
                if (pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 350 && pPlayer->HasSpell(S_GNOMISH))
                {
                    if (!pPlayer->HasSpell(SPELL_TO_TOSHLEY))
                    {
                        bCanLearn = true;
                        strGossipItem = GOSSIP_ITEM_SMILES;
                    }
                    else if (pPlayer->HasSpell(SPELL_TO_TOSHLEY))
                        uiNpcTextId = 0;
                }
                break;
        }
    }

    if (bCanLearn)
    {
        if (pPlayer->HasItemCount(ITEM_GOBLIN_CARD, 1) || pPlayer->HasItemCount(ITEM_GNOMISH_CARD, 1))
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, strGossipItem.c_str(), pCreature->GetEntry(), GOSSIP_ACTION_INFO_DEF + 1);
    }

    pPlayer->SEND_GOSSIP_MENU(uiNpcTextId ? uiNpcTextId : pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_engineering_tele_trinket(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
        pPlayer->CLOSE_GOSSIP_MENU();

    if (uiSender != pCreature->GetEntry())
        return true;

    switch (uiSender)
    {
        case NPC_ZAP:
            pPlayer->CastSpell(pPlayer, SPELL_LEARN_TO_EVERLOOK, false);
            break;
        case NPC_JHORDY:
            pPlayer->CastSpell(pPlayer, SPELL_LEARN_TO_GADGET, false);
            break;
        case NPC_KABLAM:
            pPlayer->CastSpell(pPlayer, SPELL_LEARN_TO_AREA52, false);
            break;
        case NPC_SMILES:
            pPlayer->CastSpell(pPlayer, SPELL_LEARN_TO_TOSHLEY, false);
            break;
    }

    return true;
}

/*###
# start menues leatherworking
###*/

enum
{
    NPC_CARYSSIA_MOONHUNTER     = 7870,

    SPELL_TRIBAL_LEATHERWORKING = 10660
};

bool MeetRequirements_npc_prof_leather(Player* pPlayer, Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        // Caryssia Moonhunter <Tribal Leatherworking Trainer>
        case NPC_CARYSSIA_MOONHUNTER:
        {
            if (!pPlayer->HasSpell(SPELL_TRIBAL_LEATHERWORKING)) // Tribal Leatherworking
                return false;
            break;
        }
        default:
            break;
    }

    return true;
}

bool GossipHello_npc_prof_leather(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());
    if (pCreature->isVendor())
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
    if (pCreature->isTrainer() && MeetRequirements_npc_prof_leather(pPlayer, pCreature))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

    

    // Unlearning specializations introduced in 2.0.3

    // uint32 eCreature = pCreature->GetEntry();
    //if (pPlayer->HasSkill(SKILL_LEATHERWORKING) && pPlayer->GetBaseSkillValue(SKILL_LEATHERWORKING) >= 250 && pPlayer->getLevel() > 49)
    //{
    //    switch (eCreature)
    //    {
    //        case 7866:                                      //Peter Galen
    //        case 7867:                                      //Thorkaf Dragoneye
    //            if (pPlayer->HasSpell(S_DRAGON))
    //                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_DRAGON,      GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 1);
    //            break;
    //        case 7868:                                      //Sarah Tanner
    //        case 7869:                                      //Brumn Winterhoof
    //            if (pPlayer->HasSpell(S_ELEMENTAL))
    //                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_ELEMENTAL,   GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 2);
    //            break;
    //        case 7870:                                      //Caryssia Moonhunter
    //        case 7871:                                      //Se'Jib
    //            if (pPlayer->HasSpell(S_TRIBAL))
    //                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_TRIBAL,      GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 3);
    //            break;
    //    }
    //}

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

void SendActionMenu_npc_prof_leather(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch (uiAction)
    {
        case GOSSIP_ACTION_TRADE:
            pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_TRAIN:
            pPlayer->SEND_TRAINERLIST(pCreature->GetGUID());
            break;
        //Unlearn Leather
        case GOSSIP_ACTION_INFO_DEF + 1:
            if (EquippedOk(pPlayer, S_UNLEARN_DRAGON))
            {
                if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
                {
                    pPlayer->CastSpell(pPlayer, S_UNLEARN_DRAGON, true);
                    ProfessionUnlearnSpells(pPlayer, S_UNLEARN_DRAGON);
                    pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
                }
                else
                    pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
            }
            else
                pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, NULL, NULL);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            if (EquippedOk(pPlayer, S_UNLEARN_ELEMENTAL))
            {
                if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
                {
                    pPlayer->CastSpell(pPlayer, S_UNLEARN_ELEMENTAL, true);
                    ProfessionUnlearnSpells(pPlayer, S_UNLEARN_ELEMENTAL);
                    pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
                }
                else
                    pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
            }
            else
                pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, NULL, NULL);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            if (EquippedOk(pPlayer, S_UNLEARN_TRIBAL))
            {
                if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
                {
                    pPlayer->CastSpell(pPlayer, S_UNLEARN_TRIBAL, true);
                    ProfessionUnlearnSpells(pPlayer, S_UNLEARN_TRIBAL);
                    pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
                }
                else
                    pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
            }
            else
                pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, NULL, NULL);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
    }
}

void SendConfirmUnlearn_npc_prof_leather(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    if (uiAction)
    {
        uint32 eCreature = pCreature->GetEntry();
        switch (eCreature)
        {
            case 7866:                                      //Peter Galen
            case 7867:                                      //Thorkaf Dragoneye
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_DRAGON, GOSSIP_SENDER_CHECK, uiAction,    BOX_UNLEARN_LEATHER_SPEC, /*DoMedUnlearnCost(pPlayer),*/false);
                //unknown textID ()
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
                break;
            case 7868:                                      //Sarah Tanner
            case 7869:                                      //Brumn Winterhoof
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_ELEMENTAL, GOSSIP_SENDER_CHECK, uiAction, BOX_UNLEARN_LEATHER_SPEC, /*DoMedUnlearnCost(pPlayer),*/false);
                //unknown textID ()
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
                break;
            case 7870:                                      //Caryssia Moonhunter
            case 7871:                                      //Se'Jib
                pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_UNLEARN_TRIBAL, GOSSIP_SENDER_CHECK, uiAction,    BOX_UNLEARN_LEATHER_SPEC, /*DoMedUnlearnCost(pPlayer),*/false);
                //unknown textID ()
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
                break;
        }
    }
}

bool GossipSelect_npc_prof_leather(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:
            SendActionMenu_npc_prof_leather(pPlayer, pCreature, uiAction);
            break;
        case GOSSIP_SENDER_UNLEARN:
            SendConfirmUnlearn_npc_prof_leather(pPlayer, pCreature, uiAction);
            break;
        case GOSSIP_SENDER_CHECK:
            SendActionMenu_npc_prof_leather(pPlayer, pCreature, uiAction);
            break;
    }
    return true;
}

/*###
# start menues for GO (engineering and leatherworking)
###*/

/*bool GOHello_go_soothsaying_for_dummies(Player* pPlayer, GameObject* pGo)
{
    pPlayer->ADD_GOSSIP_ITEM(0,GOSSIP_LEARN_DRAGON, GOSSIP_SENDER_INFO, GOSSIP_ACTION_INFO_DEF);
    pPlayer->SEND_GOSSIP_MENU(5584, pGo->GetGUID());

    return true;
}*/

/*###
#
###*/

void AddSC_npc_professions()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_prof_blacksmith";
    newscript->pGossipHello =  &GossipHello_npc_prof_blacksmith;
    newscript->pGossipSelect = &GossipSelect_npc_prof_blacksmith;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_engineering_tele_trinket";
    newscript->pGossipHello =  &GossipHello_npc_engineering_tele_trinket;
    newscript->pGossipSelect = &GossipSelect_npc_engineering_tele_trinket;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_prof_leather";
    newscript->pGossipHello =  &GossipHello_npc_prof_leather;
    newscript->pGossipSelect = &GossipSelect_npc_prof_leather;
    newscript->RegisterSelf();

    /*newscript = new Script;
    newscript->Name = "go_soothsaying_for_dummies";
    newscript->pGOHello =  &GOHello_go_soothsaying_for_dummies;
    //newscript->pGossipSelect = &GossipSelect_go_soothsaying_for_dummies;
    newscript->RegisterSelf();*/
}
