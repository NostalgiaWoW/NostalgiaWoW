DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180831032640');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180831032640');
-- Add your query below.

-- Gameobjects added to block path for certain map issues. Temp fix.

DELETE FROM `gameobject` WHERE `guid`=4058480;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058480, 180779, 1, -8040.91, -5330.4, 1.64976, 1.83448, 0, 0, 0.793925, 0.608016, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058478;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058478, 180779, 1, -8041.3, -5330.21, 0.671941, 1.94522, 0, 0, 0.826357, 0.563146, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058476;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058476, 180779, 1, -8042.6, -5328.53, 2.25275, 3.71707, 0, 0, 0.958888, -0.283784, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058474;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058474, 180779, 1, -8042.09, -5329.09, 1.64472, 0.957964, 0, 0, 0.460876, 0.887465, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058473;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058473, 180779, 1, -8043.28, -5328.43, 1.66429, 0.169424, 0, 0, 0.0846107, 0.996414, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058472;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058472, 180779, 1, -8043.19, -5327.29, 1.5276, 6.01279, 0, 0, 0.134788, -0.990874, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058471;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058471, 180779, 1, -8043.17, -5328.85, 0.674467, 0.320221, 0, 0, 0.159427, 0.98721, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058470;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058470, 180779, 1, -8042.24, -5329.1, 0.654522, 0.532279, 0, 0, 0.263009, 0.964794, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058468;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058468, 180779, 1, -8043.09, -5327.84, 0.633436, 0.532279, 0, 0, 0.263009, 0.964794, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058466;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058466, 180779, 1, -8040.84, -5325.39, 2.45829, 1.96013, 0, 0, 0.830535, 0.556967, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058465;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058465, 180779, 1, -8040.63, -5325.9, 1.53847, 2.30257, 0, 0, 0.913288, 0.407315, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058464;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058464, 180779, 1, -8040.05, -5326.55, 1.13686, 2.30257, 0, 0, 0.913288, 0.407315, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058463;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058463, 180779, 1, -8040.31, -5324.77, 2.02111, 5.07502, 0, 0, 0.568006, -0.823025, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058462;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058462, 180779, 1, -8040.82, -5324.96, 1.08873, 5.32321, 0, 0, 0.461768, -0.887001, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058461;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058461, 180779, 1, -8042.43, -5326.56, 1.52677, 5.32321, 0, 0, 0.461768, -0.887001, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058460;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058460, 180779, 1, -8041.52, -5325.92, 1.58266, 5.27294, 0, 0, 0.483913, -0.875116, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058459;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058459, 180779, 1, -8039.61, -5324.37, 1.57704, 5.27294, 0, 0, 0.483913, -0.875116, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058458;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058458, 180779, 1, -8038.76, -5323.83, 1.57671, 5.27294, 0, 0, 0.483913, -0.875116, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058456;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058456, 180779, 1, -8042.84, -5326.94, 0.617643, 5.36876, 0, 0, 0.441447, -0.897287, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058455;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058455, 180779, 1, -8041.98, -5326.27, 0.604647, 5.36876, 0, 0, 0.441447, -0.897287, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058454;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058454, 180779, 1, -8041.2, -5325.67, 0.592976, 5.36876, 0, 0, 0.441447, -0.897287, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058453;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058453, 180779, 1, -8040.13, -5324.85, 0.588547, 5.36876, 0, 0, 0.441447, -0.897287, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058452;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058452, 180779, 1, -8039.35, -5324.25, 0.58761, 5.36876, 0, 0, 0.441447, -0.897287, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058451;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058451, 180779, 1, -8038.48, -5323.76, 0.586107, 5.07345, 0, 0, 0.568652, -0.822578, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058450;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058450, 180779, 1, -8036.85, -5324.15, 1.58208, 3.50423, 0, 0, 0.983607, -0.180326, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058449;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058449, 180779, 1, -8036.49, -5325.1, 1.59041, 3.50423, 0, 0, 0.983607, -0.180326, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058448;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058448, 180779, 1, -8036.17, -5325.94, 1.60423, 3.50423, 0, 0, 0.983607, -0.180326, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058447;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058447, 180779, 1, -8036.9, -5324.2, 0.592853, 4.09563, 0, 0, 0.888367, -0.459135, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058446;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058446, 180779, 1, -8036.55, -5325.16, 0.600058, 3.80032, 0, 0, 0.946248, -0.323443, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058445;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058445, 180779, 1, -8036.36, -5326.14, 0.614075, 3.85137, 0, 0, 0.937684, -0.347488, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058444;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058444, 3658, 1, 16235.5, 16266, 13.6808, 3.19495, 0, 0, 0.999644, -0.026675, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058443;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058443, 184863, 1, 16231.8, 16265.8, 13.3806, 3.19495, 0, 0, 0.999644, -0.026675, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4058442;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4058442, 180779, 1, 16226.1, 16257, 13.1967, 1.65007, 0, 0, 0.734572, 0.678531, 25, 100, 1, 0, 0);


-- Removal of invis walls that arent working at ground level in this area for some reason.
DELETE FROM `gameobject` WHERE `guid`=4058441;
DELETE FROM `gameobject` WHERE `guid`=4058440;
DELETE FROM `gameobject` WHERE `guid`=4058439;



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
