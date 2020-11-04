DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190127051347');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190127051347');
-- Add your query below.

-- Added some glowy stuff to Viper's room
DELETE FROM `gameobject` WHERE `guid`=4246713;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4246713, 181402, 1, 16229, 16383.7, -61.1767, 1.54876, 0, 0, 0.699272, 0.714856, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4246717;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4246717, 181402, 1, 16247.6, 16404, -62.0038, 3.15097, 0, 0, 0.999989, -0.00468853, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4246719;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4246719, 181402, 1, 16228.3, 16423.1, -63.018, 4.67856, 0, 0, 0.718964, -0.695047, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4246722;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4246722, 181402, 1, 16208.2, 16404, -62.4855, 6.28078, 0, 0, 0.00120488, -0.999999, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4278772;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4278772, 181402, 1, 16228.4, 16384.3, -64.3792, 1.52517, 0, 0, 0.690794, 0.723052, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4278774;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4278774, 181402, 1, 16247, 16402.9, -64.3792, 3.02843, 0, 0, 0.9984, 0.0565526, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4278775;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4278775, 181402, 1, 16228.9, 16422.5, -64.3792, 4.6275, 0, 0, 0.736475, -0.676465, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4278776;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4278776, 181402, 1, 16208.9, 16403.3, -64.3792, 6.23992, 0, 0, 0.0216321, -0.999766, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4278777;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4278777, 181402, 1, 16246.1, 16384.5, -64.3792, 2.39068, 0, 0, 0.930341, 0.366696, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4278779;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4278779, 181402, 1, 16208.6, 16384.9, -64.3783, 0.737422, 0, 0, 0.360413, 0.932793, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4278782;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4278782, 181402, 1, 16247.2, 16421.6, -64.3783, 4.13663, 0, 0, 0.878769, -0.477248, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4278780;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4278780, 181402, 1, 16209.4, 16422.6, -64.3783, 5.4506, 0, 0, 0.404372, -0.914595, 25, 100, 1, 0, 0);



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
