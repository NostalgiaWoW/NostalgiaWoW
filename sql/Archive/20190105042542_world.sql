DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190105042542');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190105042542');
-- Add your query below.

-- Booty bay bank guards.
DELETE FROM `creature` WHERE `guid`=2728848;
INSERT INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2728848, 4624, 0, 0, 588, -14427.4, 519.853, 26.3076, 5.20835, 25, 5, 0, 7296, 0, 0, 0, 0, 0, 0, 10);
DELETE FROM `creature` WHERE `guid`=2728849;
INSERT INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2728849, 4624, 0, 0, 588, -14406.7, 547.685, 21.2641, 0.580003, 25, 5, 0, 7296, 0, 0, 0, 0, 0, 0, 10);

DELETE FROM `creature_movement` WHERE `id`=2728848 AND `point`=1;
INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `waittime`, `script_id`, `textid1`, `textid2`, `textid3`, `textid4`, `textid5`, `emote`, `spell`, `wpguid`, `orientation`, `model1`, `model2`) VALUES (2728848, 1, -14406.8, 532.62, 24.6233, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.45673, 0, 0);
DELETE FROM `creature_movement` WHERE `id`=2728848 AND `point`=2;
INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `waittime`, `script_id`, `textid1`, `textid2`, `textid3`, `textid4`, `textid5`, `emote`, `spell`, `wpguid`, `orientation`, `model1`, `model2`) VALUES (2728848, 2, -14433.2, 522.016, 25.4067, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.52367, 0, 0);
DELETE FROM `creature_movement` WHERE `id`=2728849 AND `point`=1;
INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `waittime`, `script_id`, `textid1`, `textid2`, `textid3`, `textid4`, `textid5`, `emote`, `spell`, `wpguid`, `orientation`, `model1`, `model2`) VALUES (2728849, 1, -14444.7, 532.047, 22.159, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.82583, 0, 0);
DELETE FROM `creature_movement` WHERE `id`=2728849 AND `point`=2;
INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `waittime`, `script_id`, `textid1`, `textid2`, `textid3`, `textid4`, `textid5`, `emote`, `spell`, `wpguid`, `orientation`, `model1`, `model2`) VALUES (2728849, 2, -14427.1, 542.831, 22.7931, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.750432, 0, 0);
DELETE FROM `creature_movement` WHERE `id`=2728849 AND `point`=3;
INSERT INTO `creature_movement` (`id`, `point`, `position_x`, `position_y`, `position_z`, `waittime`, `script_id`, `textid1`, `textid2`, `textid3`, `textid4`, `textid5`, `emote`, `spell`, `wpguid`, `orientation`, `model1`, `model2`) VALUES (2728849, 3, -14408.1, 544.02, 22.1379, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6.21445, 0, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
