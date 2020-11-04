DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200705012042');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200705012042');
-- Add your query below.
-- Midsummer Finale in Booty Bay


REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770327, 8121, 0, 0, 8121, -14438.6, 474.175, 15.3015, 4.02948, 25, 5, 0, 1172, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770326, 8122, 0, 0, 8122, -14427.9, 453.815, 15.3771, 3.79386, 25, 5, 0, 1172, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770325, 8122, 0, 0, 8122, -14371.7, 434.562, 7.36755, 4.83687, 25, 5, 0, 1172, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770324, 8121, 0, 0, 8121, -14311.6, 511.412, 8.61733, 5.53588, 25, 5, 0, 1172, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770323, 15911, 0, 0, 0, -14376.8, 541.628, 13.2038, 2.45162, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770322, 15911, 0, 0, 0, -14357.7, 525.634, 10.5392, 2.06991, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770321, 15911, 0, 0, 0, -14347, 505.162, 8.06784, 0.499902, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770320, 15911, 0, 0, 0, -14368.9, 493.211, 5.40325, 0.499902, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770319, 15911, 0, 0, 0, -14379.7, 483.698, 3.83511, 1.45652, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770318, 15911, 0, 0, 0, -14381.1, 471.663, 2.54044, 1.45652, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770317, 15911, 0, 0, 0, -14384.1, 451.4, 0.539771, 0.35696, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770316, 15911, 0, 0, 0, -14404.7, 444.318, 4.59476, 5.22721, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770315, 15911, 0, 0, 0, -14420.5, 463.629, 9.32415, 2.09819, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770314, 15912, 0, 0, 0, -14393.2, 459.11, 13.3184, 4.41511, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770313, 15912, 0, 0, 0, -14389.8, 470.188, 11.0557, 4.41511, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770312, 15912, 0, 0, 0, -14383, 492.345, 6.53023, 4.41511, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770311, 15912, 0, 0, 0, -14365, 544.018, 4.30563, 4.37977, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770310, 15912, 0, 0, 0, -14342.1, 546.549, 6.41279, 2.79641, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770309, 15912, 0, 0, 0, -14320, 538.585, 8.28582, 2.79641, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770308, 15912, 0, 0, 0, -14313.6, 531.106, 9.10621, 1.17692, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770307, 15915, 0, 0, 0, -14313.6, 531.106, 9.10621, 1.17692, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770306, 15915, 0, 0, 0, -14330.9, 485.779, 9.18078, 0.980567, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770305, 15915, 0, 0, 0, -14350.3, 478.211, 6.39395, 1.16121, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770304, 15915, 0, 0, 0, -14375.7, 462.884, 1.86198, 0.755157, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770303, 15915, 0, 0, 0, -14397.9, 469.831, 2.39271, 4.46066, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770302, 15915, 0, 0, 0, -14392, 492.696, 2.72236, 4.46066, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770301, 15916, 0, 0, 0, -14392, 492.696, 2.72236, 4.46066, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770300, 15916, 0, 0, 0, -14371.3, 487.368, 2.72236, 4.46066, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770299, 15916, 0, 0, 0, -14373.4, 515.403, 3.13969, 5.2335, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770298, 15916, 0, 0, 0, -14383.2, 532.734, 3.41791, 3.90696, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770297, 15916, 0, 0, 0, -14365.6, 545.751, 3.73239, 2.64168, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770296, 15916, 0, 0, 0, -14350.1, 536.012, 3.98984, 2.06284, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770295, 15918, 0, 0, 0, -14350.1, 536.012, 3.98984, 2.06284, 25, 5, 0, 4120, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770294, 15918, 0, 0, 0, -14345.2, 508.154, 4.40684, 0.774789, 25, 5, 0, 4120, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770293, 15918, 0, 0, 0, -14368.4, 485.444, 4.86011, 0.774789, 25, 5, 0, 4120, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770292, 15918, 0, 0, 0, -14383.4, 455.835, 8.7564, 1.35991, 25, 5, 0, 4120, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770291, 15918, 0, 0, 0, -14385.9, 444.497, 10.9787, 1.42667, 25, 5, 0, 4120, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770290, 15872, 0, 0, 0, -14400.3, 486.308, 10.9787, 1.68978, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770289, 15872, 0, 0, 0, -14389.1, 473.011, 12.0828, 3.03988, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770288, 15872, 0, 0, 0, -14368.5, 470.917, 13.344, 3.97843, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770287, 15872, 0, 0, 0, -14353.1, 489.464, 5.38742, 4.7866, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770286, 15872, 0, 0, 0, -14357.8, 512.667, 5.72234, 5.15417, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770285, 15872, 0, 0, 0, -14369.3, 548.589, 6.25801, 4.0876, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770284, 15872, 0, 0, 0, -14361.4, 557.216, 6.42284, 2.00079, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770283, 15873, 0, 0, 0, -14353.6, 540.134, 6.68523, 0.716667, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770282, 15874, 0, 0, 0, -14368.3, 527.332, 8.49325, 0.421357, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770281, 15874, 0, 0, 0, -14382.1, 521.168, 9.89124, 1.4518, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770280, 15875, 0, 0, 0, -14389.9, 494.144, 9.61093, 3.24958, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770279, 15877, 0, 0, 0, -14368.8, 496.436, 7.33775, 4.37741, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770278, 15877, 0, 0, 0, -14347.8, 505.475, 4.65365, 0.157462, 25, 5, 0, 5000, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770277, 15886, 0, 0, 0, -14375.3, 496.186, 1.69259, 4.27295, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770276, 15886, 0, 0, 0, -14369.2, 509.182, 2.79755, 4.27295, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770275, 15885, 0, 0, 0, -14382.5, 515.46, 2.79755, 4.27295, 25, 5, 0, 8, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770274, 15882, 0, 0, 0, -14375.3, 530.778, 4.09995, 4.27295, 25, 5, 0, 4120, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770273, 15882, 0, 0, 0, -14365.2, 527.497, 5.74984, 4.34206, 25, 5, 0, 4120, 0, 0, 0, 0, 0, 0, 10);

REPLACE INTO `game_event_creature` (`guid`, `event`)
VALUES
(2770273, 170),
(2770274, 170),
(2770275, 170),
(2770276, 170),
(2770277, 170),
(2770278, 170),
(2770279, 170),
(2770280, 170),
(2770281, 170),
(2770282, 170),
(2770283, 170),
(2770284, 170),
(2770285, 170),
(2770286, 170),
(2770287, 170),
(2770288, 170),
(2770289, 170),
(2770290, 170),
(2770291, 170),
(2770292, 170),
(2770293, 170),
(2770294, 170),
(2770295, 170),
(2770296, 170),
(2770297, 170),
(2770298, 170),
(2770299, 170),
(2770300, 170),
(2770301, 170),
(2770302, 170),
(2770303, 170),
(2770304, 170),
(2770305, 170),
(2770306, 170),
(2770307, 170),
(2770308, 170),
(2770309, 170),
(2770310, 170),
(2770311, 170),
(2770312, 170),
(2770313, 170),
(2770314, 170),
(2770315, 170),
(2770316, 170),
(2770317, 170),
(2770318, 170),
(2770319, 170),
(2770320, 170),
(2770321, 170),
(2770322, 170),
(2770323, 170),
(2770324, 170),
(2770325, 170),
(2770326, 170),
(2770327, 170),
(2770328, 170),
(2770329, 170),
(2770330, 170),
(2770331, 170),
(2770332, 170),
(2770333, 170),
(2770334, 170),
(2770335, 170),
(2770336, 170),
(2770337, 170),
(2770338, 170);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
