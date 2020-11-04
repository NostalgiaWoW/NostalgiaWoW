DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201102183930');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201102183930');
-- Add your query below.

-- Arena and PVP token Quests
-- Item Template
DELETE FROM `item_template` WHERE `entry`=80001 AND `patch`=0;
INSERT INTO `item_template` (`entry`, `patch`, `class`, `subclass`, `name`, `displayid`, `Quality`, `Flags`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `dmg_min3`, `dmg_max3`, `dmg_type3`, `dmg_min4`, `dmg_max4`, `dmg_type4`, `dmg_min5`, `dmg_max5`, `dmg_type5`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `Duration`, `ExtraFlags`, `OtherTeamEntry`) VALUES (80001, 0, 15, 0, 'Arena Token', 31484, 2, 0, 1, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);

-- Creature Template
DELETE FROM `creature_template` WHERE `entry`=1200040 AND `patch`=0;
INSERT INTO `creature_template` (`entry`, `patch`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Civilian`, `RacialLeader`, `RegenHealth`, `equipment_id`, `trainer_id`, `vendor_id`, `MechanicImmuneMask`, `SchoolImmuneMask`, `flags_extra`, `aggroRadius`, `ScriptName`) VALUES (1200040, 0, 0, 0, 1503, 0, 0, 0, 'Area Tier Quests', 'Nostalgia WoW', 0, 63, 63, 3462000, 3462000, 612320, 612320, 8401, 35, 35, 2, 1.25, 1.14286, 0, 3, 571, 737, 0, 290, 1, 2000, 2000, 8, 0, 0, 0, 0, 0, 0, 0, 220.81, 320.77, 100, 7, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0, 700000, 750000, '', 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');

-- Quest Templates
DELETE FROM `quest_template` WHERE `entry`=30007 AND `patch`=0;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (30007, 0, 2, 0, 1, 60, 60, 82, 1024, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Arena Reward - Tier Sets', 'Turn in bla blabla', 'Bring me things', 'Choose your rewards', 'Hey dummy wheres the stuff', NULL, 'Turn in arena stuffz', 'Turn in PVP stuffz', NULL, NULL, 80001, 80000, 0, 0, 25, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16828, 16829, 16830, 16831, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `quest_template` WHERE `entry`=30008 AND `patch`=0;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (30008, 0, 2, 0, 1, 60, 60, 82, 1024, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Arena Reward - Tier Sets', 'Turn in bla blabla', 'Bring me things', 'Choose your rewards', 'Hey dummy wheres the stuff', NULL, 'Turn in arena stuffz', 'Turn in PVP stuffz', NULL, NULL, 80001, 80000, 0, 0, 25, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16836, 16833, 16834, 16835, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- Update to Quest per class

-- Warrior
UPDATE quest_template
SET RewChoiceItemId1 =16861 , RewChoiceItemId2 =16862 , RewChoiceItemId3 =16863 , RewChoiceItemId4 =16864
WHERE entry = 30009;

UPDATE quest_template
SET RewChoiceItemId1 =16865 , RewChoiceItemId2 =16866 , RewChoiceItemId3 =16867 , RewChoiceItemId4 =16868
WHERE entry = 30019;

-- Paladin
UPDATE quest_template
SET RewChoiceItemId1 =16853 , RewChoiceItemId2 =16854 , RewChoiceItemId3 =16855 , RewChoiceItemId4 =16856
WHERE entry = 30010;

UPDATE quest_template
SET RewChoiceItemId1 =16857 , RewChoiceItemId2 =16858 , RewChoiceItemId3 =16859 , RewChoiceItemId4 =16860
WHERE entry = 30020;

-- Hunter
UPDATE quest_template
SET RewChoiceItemId1 =16845 , RewChoiceItemId2 =16846 , RewChoiceItemId3 =16847 , RewChoiceItemId4 =16848
WHERE entry = 30011;

UPDATE quest_template
SET RewChoiceItemId1 =16849 , RewChoiceItemId2 =16850 , RewChoiceItemId3 =16851 , RewChoiceItemId4 =16852
WHERE entry = 30021;

-- Rogue
UPDATE quest_template
SET RewChoiceItemId1 =16820 , RewChoiceItemId2 =16821 , RewChoiceItemId3 =16822 , RewChoiceItemId4 =16823
WHERE entry = 30012;

UPDATE quest_template
SET RewChoiceItemId1 =16824 , RewChoiceItemId2 =16825 , RewChoiceItemId3 =16826 , RewChoiceItemId4 =16827
WHERE entry = 30022;

-- Priest
UPDATE quest_template
SET RewChoiceItemId1 =16811 , RewChoiceItemId2 =16812 , RewChoiceItemId3 =16813 , RewChoiceItemId4 =16814
WHERE entry = 30013;

UPDATE quest_template
SET RewChoiceItemId1 =16815 , RewChoiceItemId2 =16816 , RewChoiceItemId3 =16817 , RewChoiceItemId4 =16819
WHERE entry = 30023;

-- Shaman
UPDATE quest_template
SET RewChoiceItemId1 =16837 , RewChoiceItemId2 =16838 , RewChoiceItemId3 =16839 , RewChoiceItemId4 =16840
WHERE entry = 30015;

UPDATE quest_template
SET RewChoiceItemId1 =16841 , RewChoiceItemId2 =16842 , RewChoiceItemId3 =16843 , RewChoiceItemId4 =16844
WHERE entry = 30025;

-- Mage
UPDATE quest_template
SET RewChoiceItemId1 =16795 , RewChoiceItemId2 =16796 , RewChoiceItemId3 =16797 , RewChoiceItemId4 =16798
WHERE entry = 30016;

UPDATE quest_template
SET RewChoiceItemId1 =16799 , RewChoiceItemId2 =16800 , RewChoiceItemId3 =16801 , RewChoiceItemId4 =16802
WHERE entry = 30026;

-- Warlock
UPDATE quest_template
SET RewChoiceItemId1 =16803 , RewChoiceItemId2 =16804 , RewChoiceItemId3 =16805 , RewChoiceItemId4 =16806
WHERE entry = 30017;

UPDATE quest_template
SET RewChoiceItemId1 =16807 , RewChoiceItemId2 =16808 , RewChoiceItemId3 =16809 , RewChoiceItemId4 =16810
WHERE entry = 30027;



-- Relations
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30007, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30008, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30009, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30019, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30010, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30020, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30011, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30021, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30012, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30022, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30013, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30023, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30014, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30024, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30015, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30025, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30016, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30026, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30017, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30027, 0);


DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30007, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30008, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30009, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30019, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30010, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30020, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30011, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30021, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30012, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30022, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30013, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30023, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30014, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30024, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30015, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30025, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30016, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30026, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30007 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30017, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1200040 AND `quest`=30008 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (1200040, 30027, 0);



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
