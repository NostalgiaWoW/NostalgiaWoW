DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201104190910');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201104190910');
-- Add your query below.

-- Mall Gob additions
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
DELETE FROM `gameobject` WHERE `guid`=4436098;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436098, 181195, 0, -1861.4, -4217, -3, 4.53649, 0, 0, 0.766484, -0.642263, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436286;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436286, 181195, 0, -1784.82, -4275.53, -3, 3.55236, 0, 0, 0.978983, -0.203944, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436292;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436292, 181195, 0, -1771.15, -4299.06, -3, 3.80992, 0, 0, 0.944685, -0.327979, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436294;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436294, 181195, 0, -1748.52, -4312.51, -3, 4.54741, 0, 0, 0.762966, -0.646438, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436296;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436296, 181195, 0, -1720.58, -4312.3, -3, 4.90786, 0, 0, 0.634734, -0.77273, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436300;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436300, 181195, 0, -1692.8, -4306.15, -3, 4.95258, 0, 0, 0.617296, -0.786731, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436304;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436304, 181195, 0, -1666.49, -4295.72, -3, 5.24782, 0, 0, 0.494869, -0.868968, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436306;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436306, 181195, 0, -1645.4, -4277.19, -3, 5.63029, 0, 0, 0.320682, -0.947187, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436308;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436308, 181195, 0, -1627.54, -4255.31, -3, 5.57048, 0, 0, 0.348857, -0.937176, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436316;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436316, 181195, 0, -1607.67, -4235.51, -3, 5.42825, 0, 0, 0.414566, -0.910019, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436318;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436318, 181195, 0, -1585.58, -4217.48, -3, 5.35593, 0, 0, 0.447194, -0.894437, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436320;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436320, 181195, 0, -1564.01, -4198.87, -2.5, 5.50353, 0, 0, 0.380028, -0.924975, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436663;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436663, 3100014, 0, -1996.24, -4126.74, 0, 3.31848, 0, 0, 0.996091, -0.0883282, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4416280;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416280, 3100014, 1, -3990.03, 1129.66, 161.027, 3.18956, 0, 0, 0.999712, -0.0239807, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4416192;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416192, 3100014, 1, -4098.02, 1149.46, 161.213, 6.20638, 0, 0, 0.0383947, -0.999263, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4416193;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416193, 3100014, 1, -4098.76, 1119.07, 161.214, 6.26528, 0, 0, 0.00895265, -0.99996, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436048;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436048, 3100014, 0, -2006.5, -4044.91, 2, 3.40187, 0, 0, 0.991544, -0.129769, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436068;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436068, 3100014, 0, -1997.07, -4098.98, 1, 3.10421, 0, 0, 0.999825, 0.0186903, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436054;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436054, 3100014, 0, -1998.45, -4071, 1, 3.46153, 0, 0, 0.987232, -0.159286, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436662;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436662, 3100014, 0, -1982.94, -4151.86, 0.5, 3.88785, 0, 0, 0.931191, -0.364533, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436678;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436678, 3100014, 0, -1962.59, -4171.26, 0.5, 4.1079, 0, 0, 0.885534, -0.464574, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436076;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436076, 3100014, 0, -1940.61, -4189.32, -0.120897, 4.13064, 0, 0, 0.880195, -0.474612, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436078;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436078, 3100014, 0, -1916.64, -4204.9, -0.55, 4.36076, 0, 0, 0.819886, -0.572527, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436679;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436679, 3100014, 0, -1889.87, -4210.9, 1, 4.42519, 0, 0, 0.801021, -0.598637, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436285;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436285, 3100014, 0, -1790.42, -4263.22, 0.6, 4.20972, 0, 0, 0.860745, -0.509036, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436661;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436661, 3100014, 0, -1847.05, -4219.72, 1.46703, 4.1926, 0, 0, 0.865072, -0.501647, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436693;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436693, 3100014, 0, -1779.03, -4288.85, 1, 3.57855, 0, 0, 0.976228, -0.216745, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436670;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436670, 3100014, 0, -1762.14, -4310.26, 1, 4.24765, 0, 0, 0.850937, -0.525267, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436694;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436694, 3100014, 0, -1734.2, -4314.93, 0.5, 4.70165, 0, 0, 0.710895, -0.703299, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436299;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436299, 3100014, 0, -1706.14, -4309.5, 1.5, 4.91332, 0, 0, 0.632621, -0.774462, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436671;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436671, 3100014, 0, -1678.67, -4302.64, 1.5, 5.14462, 0, 0, 0.539028, -0.842288, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436711;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436711, 3100014, 0, -1653.88, -4288.24, 1, 5.32371, 0, 0, 0.461545, -0.887117, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436697;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436697, 3100014, 0, -1636.69, -4265.92, 1.2, 5.58681, 0, 0, 0.341193, -0.939993, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436695;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436695, 3100014, 0, -1617.8, -4244.31, 1.6, 5.53261, 0, 0, 0.36654, -0.930402, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436317;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436317, 3100014, 0, -1596.51, -4225.92, 2.2, 5.5413, 0, 0, 0.362494, -0.931986, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4436319;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4436319, 3100014, 0, -1573.87, -4208.89, 2.3, 5.30406, 0, 0, 0.47024, -0.882539, 25, 100, 1, 0, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
