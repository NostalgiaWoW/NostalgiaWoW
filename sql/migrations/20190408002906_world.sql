DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190408002906');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190408002906');
-- Add your query below.


-- Zamek added for quest "Keeping Pace"
DELETE FROM `creature` WHERE `guid`=2764459;
INSERT INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2764459, 4709, 1, 0, 429, -6226.72, -3945.02, -58.7496, 1.77021, 25, 5, 0, 1605, 0, 0, 0, 0, 0, 0, 10);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
