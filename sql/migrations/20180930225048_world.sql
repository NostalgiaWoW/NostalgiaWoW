DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180930225048');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180930225048');
-- Add your query below.


-- Temp fix for Remulos not being able to be healed
DELETE FROM `creature` WHERE `id`=11832;
INSERT INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2587485, 11832, 1, 0, 0, 7848.24, -2216.5, 470.759, 4.05463, 25, 5, 0, 56475, 89880, 0, 0, 0, 0, 0, 10);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
