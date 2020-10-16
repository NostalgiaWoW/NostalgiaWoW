DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200922002925');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200922002925');
-- Add your query below.

-- Light's Hope chapel guards addition.
DELETE FROM `creature` WHERE `guid`=3023497;
INSERT INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (3023497, 16378, 0, 0, 2079, 2298.25, -5327.38, 101.716, 2.15451, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
DELETE FROM `creature` WHERE `guid`=3023502;
INSERT INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (3023502, 16378, 0, 0, 2079, 2286.03, -5341.21, 100.186, 3.35617, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);

DELETE FROM `creature_addon` WHERE `guid`=3023497 AND `patch`=0;
INSERT INTO `creature_addon` (`guid`, `patch`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_flags`, `emote`, `moveflags`, `auras`) VALUES (3023497, 0, 0, 8, 1, 16, 0, 0, NULL);
DELETE FROM `creature_addon` WHERE `guid`=3023502 AND `patch`=0;
INSERT INTO `creature_addon` (`guid`, `patch`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_flags`, `emote`, `moveflags`, `auras`) VALUES (3023502, 0, 0, 8, 1, 16, 0, 0, NULL);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
