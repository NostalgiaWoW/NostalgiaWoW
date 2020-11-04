DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200625232403');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200625232403');
-- Add your query below.
-- Ogre Pet

-- Creature Template Creation
DELETE FROM `creature_template` WHERE `entry`=1101104 AND `patch`=0;
INSERT INTO `creature_template` (`entry`, `patch`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Civilian`, `RacialLeader`, `RegenHealth`, `equipment_id`, `trainer_id`, `vendor_id`, `MechanicImmuneMask`, `SchoolImmuneMask`, `flags_extra`, `aggroRadius`, `ScriptName`) VALUES (1101104, 0, 0, 0, 10704, 655, 11571, 0, 'Dee\'Dos', '', 0, 1, 1, 821, 1007, 0, 0, 7, 35, 35, 1, 1, 1.14286, 0.5, 0, 38, 48, 0, 112, 1, 2000, 2000, 1, 0, 0, 0, 0, 0, 0, 0, 38.28, 52.635, 100, 7, 0, 3815, 0, 3815, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 37, 53, '', 0, 3, 0, 0, 1, 106002, 0, 0, 0, 0, 2, 0, 'npc_OgrePet');

-- Creature inventory
DELETE FROM `creature_equip_template` WHERE `entry`=106002 AND `patch`=0;
INSERT INTO `creature_equip_template` (`entry`, `patch`, `equipentry1`, `equipentry2`, `equipentry3`) VALUES (106002, 0, 15260, 0, 0);



-- Creature's scripts
DELETE FROM  `mangos_string` WHERE `entry` IN (60100,60101,60102,60103, 60104);
INSERT INTO `mangos_string` (`entry`, `content_default`) VALUES ('60100', 'Goblins try to pay Dee\'dos, attack server. But inn in Dustwallow already ruined. No servers there! Stupid gobbins.');
INSERT INTO `mangos_string` (`entry`, `content_default`) VALUES ('60101', 'Me not sure how me get here. Think me have leak in memory.');
INSERT INTO `mangos_string` (`entry`, `content_default`) VALUES ('60102', 'Oof. Dis stressful, like test in ogre school.');
INSERT INTO `mangos_string` (`entry`, `content_default`) VALUES ('60103', 'Dee\'dos know me not speak well. Me clan work on stronger speak.');
INSERT INTO `mangos_string` (`entry`, `content_default`) VALUES ('60104', 'He who is unable to live in society, or who has no need because he is sufficient for himself, must be either a beast or a god. Is me beast, or god? Me hungry.');

-- Pet Summon item
DELETE FROM `item_template` WHERE `entry`=60016 AND `patch`=0;
INSERT INTO `item_template` (`entry`, `patch`, `class`, `subclass`, `name`, `displayid`, `Quality`, `Flags`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `dmg_min3`, `dmg_max3`, `dmg_type3`, `dmg_min4`, `dmg_max4`, `dmg_type4`, `dmg_min5`, `dmg_max5`, `dmg_type5`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `delay`, `ammo_type`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `block`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `ScriptName`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `Duration`, `ExtraFlags`, `OtherTeamEntry`) VALUES (60016, 0, 15, 2, 'Dee\'Dos Summoning Rock', 4772, 1, 1088, 1, 0, 0, 0, -1, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27639, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Use: Smack this rock on your head to summon Dee\'Dos!', 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);

 


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
