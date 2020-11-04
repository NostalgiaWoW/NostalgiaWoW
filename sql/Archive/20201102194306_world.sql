DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201102194306');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201102194306');
-- Add your query below.
-- Mall Gobs

-- Gameobject Locations
DELETE FROM `gameobject` WHERE `guid`=4436069;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436069, 181195, 0, -1996.7, -4112.44, -3, 3.17174, 0, 0, 0.999886, -0.0150715, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436041;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436041, 181195, 0, -2008.8, -4030.45, -3, 3.29819, 0, 0, 0.996936, -0.0782195, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436065;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436065, 181195, 0, -1997.69, -4084.41, -3, 3.18904, 0, 0, 0.999719, -0.0237203, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436051;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436051, 181195, 0, -2002.8, -4057.1, -3, 3.4427, 0, 0, 0.988688, -0.149987, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436071;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436071, 181195, 0, -1990.07, -4139.25, -3, 3.61391, 0, 0, 0.972244, -0.23397, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436073;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436073, 181195, 0, -1972.98, -4161.67, -3, 3.9634, 0, 0, 0.916761, -0.399436, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436075;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436075, 181195, 0, -1951.91, -4180, -3, 4.02857, 0, 0, 0.90326, -0.429093, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436077;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436077, 181195, 0, -1929.05, -4196.96, -3, 4.11493, 0, 0, 0.883895, -0.467686, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436081;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436081, 181195, 0, -1904.03, -4207.92, -3, 4.49113, 0, 0, 0.780852, -0.624716, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436083;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436083, 181195, 0, -1876.19, -4214, -3, 4.50991, 0, 0, 0.774952, -0.63202, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436086;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436086, 181195, 0, -1847.8, -4217, -3, 4.70144, 0, 0, 0.710966, -0.703226, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436048;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436048, 3100014, 0, -2006.5, -4044.91, 2, 3.40187, 0, 0, 0.991544, -0.129769, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436054;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436054, 3100014, 0, -1998.45, -4071, 1, 3.46153, 0, 0, 0.987232, -0.159286, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436068;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436068, 3100014, 0, -1997.07, -4098.98, 1, 3.10421, 0, 0, 0.999825, 0.0186903, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436070;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436070, 3100014, 0, -1996.16, -4127.19, -0.5, 3.13247, 0, 0, 0.99999, 0.00456303, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436072;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436072, 3100014, 0, -1983.34, -4152.19, -0.5, 3.62882, 0, 0, 0.970472, -0.241213, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436074;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436074, 3100014, 0, -1962.27, -4171.56, 0, 4.15267, 0, 0, 0.874914, -0.484278, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436076;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436076, 3100014, 0, -1940.61, -4189.32, -0.120897, 4.13064, 0, 0, 0.880195, -0.474612, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436078;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436078, 3100014, 0, -1916.64, -4204.9, -0.55, 4.36076, 0, 0, 0.819886, -0.572527, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436082;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436082, 3100014, 0, -1889.99, -4211.18, 1, 4.4691, 0, 0, 0.787686, -0.616077, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436084;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436084, 3100014, 0, -1861.83, -4216.91, 1, 4.73531, 0, 0, 0.698956, -0.715164, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436089;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436089, 3100014, 0, -1833.57, -4217.4, 2, 4.09432, 0, 0, 0.888668, -0.458551, 25, 100, 1, 0, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
