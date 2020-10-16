DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200429213254');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200429213254');
-- Add your query below.
DELETE FROM `gameobject` WHERE `guid`=4346538;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346538, 180322, 1, 7124.71, -2105.41, 670.9, 0.896338, 0, 0, 0.433316, 0.901242, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346543;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346543, 180322, 1, 7038.65, -2182.25, 677.755, 1.2003, 0, 0, 0.564765, 0.825252, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346546;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346546, 180322, 1, 7000.86, -2275.31, 626.076, 0.603382, 0, 0, 0.297135, 0.954835, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346597;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346597, 180322, 1, 7123.11, -1791.55, 570, 1.48562, 0, 0, 0.676359, 0.736572, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346598;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346598, 180322, 1, 7143.44, -1793, 570, 1.52253, 0, 0, 0.689838, 0.723963, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346660;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346660, 180322, 1, 7013, -2312, 633, 0.740706, 0, 0, 0.361945, 0.9322, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346661;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346661, 180322, 1, 7022, -2321, 630, 0.740706, 0, 0, 0.361945, 0.9322, 25, 100, 1, 0, 0);



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
