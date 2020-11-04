DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180917014146');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180917014146');
-- Add your query below.

-- Dark Iron Deposits in BRD missing from NH DB? Temp fix I copied them from PTR.
DELETE FROM `gameobject` WHERE `guid`=43103;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (43103, 165658, 230, 502.794, -191.522, -57.5144, -0.401426, 0, 0, 0.199368, -0.979925, 604800, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=43104;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (43104, 165658, 230, 418.63, -158.696, -63.1528, 0.226893, 0, 0, 0.113203, 0.993572, 604800, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=43105;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (43105, 165658, 230, 679.721, 102.181, -73.2564, -1.18682, 0, 0, 0.559193, -0.829037, 604800, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=43106;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (43106, 165658, 230, 748.476, -53.7894, -71.278, 2.96706, 0, 0, 0.996195, 0.087156, 604800, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=43107;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (43107, 165658, 230, 1001.83, -395.972, -62.7024, 0.15708, 0, 0, 0.078459, 0.996917, 604800, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=43108;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (43108, 165658, 230, 545.169, -128.195, -60.3184, -1.72788, 0, 0, 0.760406, -0.649448, 604800, 100, 1, 0, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
