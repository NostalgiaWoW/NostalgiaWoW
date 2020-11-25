DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201125042300');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201125042300');
-- Add your query below.

-- Poison Vendor Added
INSERT INTO `creature_template` (`entry`, `patch`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Civilian`, `RacialLeader`, `RegenHealth`, `equipment_id`, `trainer_id`, `vendor_id`, `MechanicImmuneMask`, `SchoolImmuneMask`, `flags_extra`, `aggroRadius`, `ScriptName`) VALUES (1201149, 0, 0, 0, 7138, 0, 0, 0, 'Poison Vendor', 'Nostalgia WoW', 0, 60, 60, 1337, 1337, 420, 420, 3252, 35, 35, 21, 1.26, 1.14286, 2, 1, 110, 142, 0, 272, 1, 2000, 2000, 8, 2, 0, 0, 0, 0, 0, 0, 74.448, 102.366, 100, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0, 0, 1, 0, 0, 1200029, 0, 0, 64, 0, '');

-- Items
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (1201149, 2928, 0, 0, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (1201149, 2930, 0, 0, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (1201149, 3371, 0, 0, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (1201149, 3777, 0, 0, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (1201149, 3372, 0, 0, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (1201149, 5060, 0, 0, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (1201149, 5140, 0, 0, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (1201149, 8923, 0, 0, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (1201149, 5173, 0, 0, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (1201149, 8924, 0, 0, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (1201149, 8925, 0, 0, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (1201149, 5530, 0, 0, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
