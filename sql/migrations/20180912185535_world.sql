DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180912185535');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180912185535');
-- Add your query below.

-- Update to Lord Falconcrest respawn timer from 25s to proper 400s
REPLACE INTO `creature_template` (`entry`, `patch`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Civilian`, `RacialLeader`, `RegenHealth`, `equipment_id`, `trainer_id`, `vendor_id`, `MechanicImmuneMask`, `SchoolImmuneMask`, `flags_extra`, `aggroRadius`, `ScriptName`) VALUES (2597, 0, 0, 0, 3985, 0, 0, 0, 'Lord Falconcrest', 'Syndicate Leader', 0, 40, 40, 11038, 11038, 0, 0, 1964, 87, 87, 0, 1.05, 1.14286, 0, 1, 215, 276, 0, 156, 1, 1316, 2000, 1, 32832, 0, 0, 0, 0, 0, 0, 47.4944, 65.3048, 100, 7, 8, 2597, 2597, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 533, 700, 'EventAI', 0, 3, 0, 0, 1, 1972, 0, 0, 0, 0, 0, 0, '');


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
