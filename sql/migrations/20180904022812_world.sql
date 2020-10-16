DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180904022812');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180904022812');
-- Add your query below.

DELETE FROM `creature` WHERE `id`=2591 and `id`=2597;
DELETE FROM `creature` WHERE `guid`=2536209;
INSERT INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2536209, 2591, 0, 0, 96, -1703.89, -1800.66, 101.708, 0.0303272, 25, 5, 0, 2972, 2975, 0, 1, 0, 0, 0, 10);
DELETE FROM `creature` WHERE `guid`=2536208;
INSERT INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2536208, 2597, 0, 0, 1972, -1703.43, -1804.92, 101.708, 6.27424, 25, 5, 0, 11038, 0, 0, 0, 0, 0, 0, 10);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
