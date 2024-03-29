DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190711230000');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190711230000');

REPLACE INTO `creature_template` (`entry`, `patch`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Civilian`, `RacialLeader`, `RegenHealth`, `equipment_id`, `trainer_id`, `vendor_id`, `MechanicImmuneMask`, `SchoolImmuneMask`, `flags_extra`, `aggroRadius`, `ScriptName`) VALUES 
('1000552', '0', '0', '0', '1913', '0', '0', '0', 'Invading Felhound', 'Burning Crusade', '0', '60', '60', '10000', '15000', '0', '0', '3791', '103', '103', '0', '1.25', '1.14286', '0', '1', '239', '325', '0', '272', '1', '1420', '1562', '0', '0', '0', '0', '0', '0', '0', '0', '73.7264', '101.374', '100', '3', '0', '1000100', '0', '0', '0', '-1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '1', '3', '0', '0', '1', '0', '0', '0', '131073', '0', '0', '0', ''),
('1000551', '0', '0', '0', '14255', '0', '0', '0', 'Invading Felguard', 'Burning Crusade', '0', '60', '60', '10000', '15000', '0', '0', '3791', '103', '103', '0', '1.25', '1.14286', '0', '1', '239', '325', '0', '272', '1', '1420', '1562', '0', '0', '0', '0', '0', '0', '0', '0', '73.7264', '101.374', '100', '3', '0', '1000100', '0', '0', '0', '-1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '1', '3', '0', '0', '1', '1481', '0', '0', '131073', '0', '0', '0', ''),
('1000550', '0', '0', '0', '169', '0', '0', '0', 'Invading Infernal', 'Burning Crusade', '0', '60', '60', '10000', '15000', '0', '0', '3791', '103', '103', '0', '1.25', '1.14286', '0', '1', '239', '325', '0', '272', '1', '1420', '1562', '0', '0', '0', '0', '0', '0', '0', '0', '73.7264', '101.374', '100', '3', '0', '1000100', '0', '0', '0', '-1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '1', '3', '0', '0', '1', '0', '0', '0', '131073', '0', '0', '0', ''),
('1000549', '0', '0', '0', '1126', '0', '0', '0', 'Demon Spawner', '', '0', '1', '1', '8', '8', '0', '0', '20', '35', '35', '0', '0', '0', '0', '0', '2', '2', '0', '44', '1', '2000', '2000', '1', '33554432', '0', '0', '0', '0', '0', '0', '0', '0', '100', '10', '0', '0', '0', '0', '0', '-1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '1', '3', '0', '0', '1', '0', '0', '0', '0', '0', '130', '0', 'npc_demon_spawner');

DELETE FROM `creature_loot_template` WHERE `entry`='1000100';
INSERT INTO `creature_loot_template` VALUES 
('1000100', '14479', '0.02', '0', '1', '1', '0'),
('1000100', '14484', '0.02', '0', '1', '1', '0'),
('1000100', '14489', '0.02', '0', '1', '1', '0'),
('1000100', '14491', '0.02', '0', '1', '1', '0'),
('1000100', '14494', '0.02', '0', '1', '1', '0'),
('1000100', '14496', '0.02', '0', '1', '1', '0'),
('1000100', '14498', '0.02', '0', '1', '1', '0'),
('1000100', '14499', '0.02', '0', '1', '1', '0'),
('1000100', '14467', '0.02', '0', '1', '1', '0'),
('1000100', '14470', '0.02', '0', '1', '1', '0'),
('1000100', '14474', '0.02', '0', '1', '1', '0'),
('1000100', '14478', '0.02', '0', '1', '1', '0'),
('1000100', '317790', '0.0025', '13', '-317790', '1', '0'),
('1000100', '317789', '0.0025', '12', '-317789', '1', '0'),
('1000100', '317788', '0.0025', '11', '-317788', '1', '0'),
('1000100', '317787', '0.0025', '10', '-317787', '1', '0'),
('1000100', '317786', '2.5', '9', '-317786', '1', '0'),
('1000100', '317785', '0.01', '8', '-317785', '1', '0'),
('1000100', '317784', '0.5', '7', '-317784', '1', '0'),
('1000100', '317783', '0.01', '6', '-317783', '1', '0'),
('1000100', '317782', '0.5', '5', '-317782', '1', '0'),
('1000100', '317781', '0.01', '4', '-317781', '1', '0'),
('1000100', '317780', '0.5', '3', '-317780', '1', '0'),
('1000100', '317779', '0.01', '2', '-317779', '1', '0'),
('1000100', '317778', '2.5', '1', '-317778', '1', '0'),
('1000100', '19269', '0.0102', '0', '1', '1', '0'),
('1000100', '19270', '0.02', '0', '1', '1', '0'),
('1000100', '15731', '0.02', '0', '1', '1', '0'),
('1000100', '19271', '0.02', '0', '1', '1', '0'),
('1000100', '19278', '0.02', '0', '1', '1', '0'),
('1000100', '19279', '0.0034', '0', '1', '1', '0'),
('1000100', '19280', '0.02', '0', '1', '1', '0'),
('1000100', '15745', '0.02', '0', '1', '1', '0'),
('1000100', '15746', '0.02', '0', '1', '1', '0'),
('1000100', '15755', '0.02', '0', '1', '1', '0'),
('1000100', '19260', '0.0102', '0', '1', '1', '0'),
('1000100', '19259', '0.0068', '0', '1', '1', '0'),
('1000100', '16220', '0.02', '0', '1', '1', '0'),
('1000100', '16218', '0.02', '0', '1', '1', '0'),
('1000100', '19230', '0.0034', '0', '1', '1', '0'),
('1000100', '16215', '0.02', '0', '1', '1', '0'),
('1000100', '15743', '0.02', '0', '1', '1', '0'),
('1000100', '16051', '0.02', '0', '1', '1', '0'),
('1000100', '3395', '0.02', '0', '1', '1', '0'),
('1000100', '3858', '0.02', '0', '1', '1', '0'),
('1000100', '15757', '0.02', '0', '1', '1', '0'),
('1000100', '16043', '0.02', '0', '1', '1', '0'),
('1000100', '15737', '0.02', '0', '1', '1', '0'),
('1000100', '16245', '0.02', '0', '1', '1', '0'),
('1000100', '19231', '0.0068', '0', '1', '1', '0'),
('1000100', '2450', '0.02', '0', '1', '1', '0'),
('1000100', '19232', '0.02', '0', '1', '1', '0'),
('1000100', '19261', '0.02', '0', '1', '1', '0'),
('1000100', '13443', '1.34', '0', '1', '1', '0'),
('1000100', '12365', '0.02', '0', '1', '1', '0'),
('1000100', '13488', '0.02', '0', '1', '1', '0'),
('1000100', '13490', '0.02', '0', '1', '1', '0'),
('1000100', '11737', '0.0068', '0', '1', '1', '0'),
('1000100', '11736', '0.0068', '0', '1', '1', '0'),
('1000100', '11734', '0.0034', '0', '1', '1', '0'),
('1000100', '11733', '0.0203', '0', '1', '1', '0'),
('1000100', '11732', '0.0068', '0', '1', '1', '0'),
('1000100', '11225', '0.02', '0', '1', '1', '0'),
('1000100', '11208', '0.02', '0', '1', '1', '0'),
('1000100', '10620', '0.04', '0', '1', '1', '0'),
('1000100', '10320', '0.02', '0', '1', '1', '0'),
('1000100', '10315', '0.02', '0', '1', '1', '0'),
('1000100', '12662', '6.4751', '0', '1', '1', '0'),
('1000100', '12682', '0.02', '0', '1', '1', '0'),
('1000100', '12683', '0.02', '0', '1', '1', '0'),
('1000100', '13446', '2.7', '0', '1', '1', '0'),
('1000100', '13463', '0.02', '0', '1', '1', '0'),
('1000100', '13464', '0.02', '0', '1', '1', '0'),
('1000100', '13465', '0.02', '0', '1', '1', '0'),
('1000100', '13466', '0.02', '0', '1', '1', '0'),
('1000100', '13486', '0.02', '0', '1', '1', '0'),
('1000100', '12704', '0.02', '0', '1', '1', '0'),
('1000100', '12697', '0.02', '0', '1', '1', '0'),
('1000100', '12695', '0.02', '0', '1', '1', '0'),
('1000100', '12694', '0.02', '0', '1', '1', '0'),
('1000100', '12693', '0.02', '0', '1', '1', '0'),
('1000100', '12691', '0.02', '0', '1', '1', '0'),
('1000100', '12689', '0.02', '0', '1', '1', '0'),
('1000100', '12685', '0.02', '0', '1', '1', '0'),
('1000100', '12684', '0.02', '0', '1', '1', '0'),
('1000100', '10306', '0.42', '0', '1', '1', '0'),
('1000100', '10305', '0.32', '0', '1', '1', '0'),
('1000100', '8838', '0.02', '0', '1', '1', '0'),
('1000100', '8836', '0.02', '0', '1', '1', '0'),
('1000100', '8766', '2.3017', '0', '1', '1', '0'),
('1000100', '8390', '0.02', '0', '1', '1', '0'),
('1000100', '8389', '0.02', '0', '1', '1', '0'),
('1000100', '14492', '0.02', '0', '1', '1', '0'),
('1000100', '7993', '0.02', '0', '1', '1', '0'),
('1000100', '7989', '0.02', '0', '1', '1', '0'),
('1000100', '7911', '0.02', '0', '1', '1', '0'),
('1000100', '7910', '0.0271', '0', '1', '1', '0'),
('1000100', '7909', '0.0305', '0', '1', '1', '0'),
('1000100', '4500', '0.06', '0', '1', '1', '0'),
('1000100', '4426', '0.58', '0', '1', '1', '0'),
('1000100', '4425', '0.54', '0', '1', '1', '0'),
('1000100', '8952', '4.6135', '0', '1', '1', '0'),
('1000100', '9295', '0.02', '0', '1', '1', '0'),
('1000100', '9298', '0.02', '0', '1', '1', '0'),
('1000100', '13492', '0.02', '0', '1', '1', '0'),
('1000100', '14466', '0.02', '0', '1', '1', '0');

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
