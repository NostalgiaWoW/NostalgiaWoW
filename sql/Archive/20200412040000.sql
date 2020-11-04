DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200412040000');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200412040000');

REPLACE INTO `creature_template` (`entry`, `patch`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Civilian`, `RacialLeader`, `RegenHealth`, `equipment_id`, `trainer_id`, `vendor_id`, `MechanicImmuneMask`, `SchoolImmuneMask`, `flags_extra`, `aggroRadius`, `ScriptName`) VALUES 
(1100023, 0, 0, 0, 10357, 0, 0, 0, 'King Vol\'Jin', 'King of the Darkspear Trolls', 0, 63, 63, 3462000, 3462000, 612320, 612320, 8401, 85, 85, 2, 1.1, 1.14286, 0, 0, 99, 210, 0, 272, 1, 2000, 2000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0, 0, 1, 1896, 0, 0, 0, 0, 0, 0, 'virus_event_nax_helper'),
(1100022, 0, 0, 0, 2970, 0, 0, 0, 'Lady Jaina Proudmoore', 'Ruler of Theramore', 0, 63, 63, 3462000, 3462000, 612320, 612320, 8401, 11, 11, 2, 1.25, 1.14286, 0, 3, 571, 737, 0, 290, 1, 2000, 2000, 8, 4160, 0, 0, 0, 0, 0, 0, 220.81, 320.77, 100, 7, 12, 0, 0, 0, 0, 15, 15, 15, 15, 15, 0, 0, 0, 0, 0, 700000, 750000, '', 0, 3, 0, 0, 1, 1745, 0, 0, 617299803, 0, 2, 0, 'virus_event_nax_helper');

REPLACE INTO locales_creature (entry, name_loc8, subname_loc8) VALUES 
(1100022,'Леди Джайна Праудмур','Правитель Терамора'),
(1100023,'Король Вол\'Джин','Король троллей Черного Копья');

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
