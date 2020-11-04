DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200518054200');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200518054200');
-- Add your query below.
-- Ghost gate in WSG
DELETE FROM `gameobject` WHERE `guid`=4370419;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370419, 500001, 489, 988.78, 1437.89, 351, 4.45231, 0, 0, 0.79283, -0.609443, 25, 100, 1, 0, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
