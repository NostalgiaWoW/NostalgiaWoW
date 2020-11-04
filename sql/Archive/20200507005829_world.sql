DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200507005829');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200507005829');
-- Add your query below.

-- WSG invis walls

DELETE FROM `gameobject` WHERE `guid`=4346696;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346696, 500000, 489, 989.42, 1436.7, 350.5, 4.10922, 0, 0, 0.885228, -0.465157, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346698;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346698, 500001, 489, 1107, 1450.5, 320.4, 1.51192, 0, 0, 0.685986, 0.727615, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346697;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346697, 500001, 489, 1105.25, 1451.15, 322, 4.53177, 0, 0, 0.767997, -0.640454, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346695;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346695, 500001, 489, 1098.33, 1357.54, 326, 5.91169, 0, 0, 0.184682, -0.982798, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346694;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346694, 500001, 489, 1098.85, 1359.5, 326, 5.80173, 0, 0, 0.238408, -0.971165, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346693;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346693, 500001, 489, 1100.23, 1361.99, 326, 5.44202, 0, 0, 0.408292, -0.912852, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346691;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346691, 500001, 489, 1103.61, 1364.21, 325, 5.54805, 0, 0, 0.359348, -0.933204, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346692;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346692, 500001, 489, 1101.85, 1362.94, 325.8, 5.3517, 0, 0, 0.449089, -0.893487, 0, 100, 1, 0, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
