DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201110142244');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201110142244');
-- Add your query below.

-- Update to Arena Walls
UPDATE gameobject SET id = 3100033 WHERE id = 175353;

-- Gameobject Template updates
DELETE FROM `gameobject_template` WHERE `entry`=3100033;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100033, 5, 3614, 'Arena Walls', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
DELETE FROM `gameobject_template` WHERE `entry`=3100014;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100014, 5, 6663, 'Banner of Provocation - Large', 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
DELETE FROM `gameobject_template` WHERE `entry`=3100017;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100017, 5, 6663, 'Banner of Provocation Medium', 0, 0, 2.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
DELETE FROM `gameobject_template` WHERE `entry`=3100034;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100034, 5, 6834, 'Arena Wall Support', 1375, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');

-- Gameobject placement
DELETE FROM `gameobject` WHERE `guid`=4437083;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437083, 3100033, 0, -1889.31, -4162.28, -3.5, 2.71471, 0, 0, 0.977307, 0.211827, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437088;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437088, 3100033, 0, -1889.3, -4147.89, -3.5, 3.49692, 0, 0, 0.984259, -0.176729, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437090;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437090, 3100033, 0, -1897.08, -4134.76, -3.5, 0.679645, 0, 0, 0.33332, 0.942814, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437092;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437092, 3100033, 0, -1902.83, -4121.16, -3.5, 0.114132, 0, 0, 0.0570349, 0.998372, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437102;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437102, 3100033, 0, -1909.48, -4107.76, -3.5, 0.809994, 0, 0, 0.394016, 0.919104, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437105;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437105, 3100033, 0, -1920.19, -4097.04, -3.5, 0.744795, 0, 0, 0.363849, 0.931458, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437108;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437108, 3100033, 0, -1931.26, -4086.41, -3.5, 0.849996, 0, 0, 0.412319, 0.91104, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437135;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437135, 3100033, 0, -1944.97, -4081.53, -3.5, 1.59604, 0, 0, 0.715977, 0.698124, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437137;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437137, 3100033, 0, -1960.15, -4083.99, -3.5, 1.8638, 0, 0, 0.802755, 0.596309, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437145;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437145, 3100033, 0, -1974.42, -4098.93, -3.5, 6.06477, 0, 0, 0.10899, -0.994043, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437147;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437147, 3100033, 0, -1905.7, -4175.88, -3.5, 1.77411, 0, 0, 0.775214, 0.631699, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437165;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437165, 3100033, 0, -1919.14, -4172.49, -3.5, 0.837092, 0, 0, 0.406432, 0.913681, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437167;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437167, 3100033, 0, -1930.79, -4163.03, -3.5, 4.10107, 0, 0, 0.887116, -0.461547, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437170;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437170, 3100033, 0, -1944.62, -4156.86, -3.5, 1.32307, 0, 0, 0.614328, 0.789051, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437177;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437177, 3100033, 0, -1957.08, -4149.03, -3.5, 0.72218, 0, 0, 0.353294, 0.935512, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437179;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437179, 3100033, 0, -1964.55, -4135.46, -3.5, 3.46476, 0, 0, 0.986974, -0.160879, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437193;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437193, 3100033, 0, -1973.15, -4123.62, -3.5, 0.934166, 0, 0, 0.450284, 0.892886, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437194;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4437194, 3100033, 0, -1977.33, -4112.64, -3.5, 6.07386, 0, 0, 0.104474, -0.994528, 0, 100, 1, 0, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
