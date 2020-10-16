DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200625200851');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200625200851');
-- Add your query below.



-- Elysium Custom 3v3 Arena Event in DM Arena. 
-- Created by Rain.


-- Event
REPLACE INTO `game_event` (`entry`,  `occurence`, `length`, `holiday`, `description`, `hardcoded`, `disabled`, `patch_min`, `patch_max`) VALUES (200, 1, 999999999, 0, '3v3 Arena Event - Stage 1 (Setup)', 0, 1, 0, 10);
REPLACE INTO `game_event` (`entry`,  `occurence`, `length`, `holiday`, `description`, `hardcoded`, `disabled`, `patch_min`, `patch_max`) VALUES (201, 1, 999999999, 0, '3v3 Arena Event - Stage 2 (Fire)', 0, 1, 0, 10);
REPLACE INTO `game_event` (`entry`,  `occurence`, `length`, `holiday`, `description`, `hardcoded`, `disabled`, `patch_min`, `patch_max`) VALUES (202, 1, 999999999, 0, '3v3 Arena Event - Stage 3 (Crystals)', 0, 1, 0, 10);
REPLACE INTO `game_event` (`entry`,  `occurence`, `length`, `holiday`, `description`, `hardcoded`, `disabled`, `patch_min`, `patch_max`) VALUES (203, 1, 999999999, 0, '3v3 Arena Event - Stage 4 (Shadow Portals)', 0, 1, 0, 10);
REPLACE INTO `game_event` (`entry`,  `occurence`, `length`, `holiday`, `description`, `hardcoded`, `disabled`, `patch_min`, `patch_max`) VALUES (204, 1, 999999999, 0, '3v3 Arena Event - START FIGHT', 0, 1, 0, 10);

-- Arena viewing area GOBs including: Ghost Walls & Crates.
-- GOBs  180352 Standing Torch // 3100013 Brazier Large // 3100014 Banner Large // 3100017 Banner Medium // 3100015 Wall Torch // 3100019 Wall Torch LARGE // 183269 Weapon Rack // 3100016 Barrel Large // 3100018 Upwards Flame Brazier // 3100012 Crystal Light // 3100020 SUN // 3100021 & 3100023 & 3100024 Crystal

REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416475, 3100024, 1, -3822.1, 1090.1, 132.084, 4.46005, 0, 0, 0.790466, -0.612506, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416474, 3100024, 1, -3784.59, 1093.82, 131.969, 4.01708, 0, 0, 0.90571, -0.423898, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416473, 3100024, 1, -3763.65, 1118.34, 131.969, 2.46985, 0, 0, 0.944123, 0.329594, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416472, 3100024, 1, -3729.85, 1085.89, 131.969, 2.73924, 0, 0, 0.979832, 0.199823, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416471, 3100024, 1, -3701.19, 1073.7, 131.969, 2.73924, 0, 0, 0.979832, 0.199823, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416470, 3100023, 1, -3730.7, 1116.28, 131.97, 3.20262, 0, 0, 0.999534, -0.0305099, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416469, 3100023, 1, -3710.01, 1096.43, 131.97, 3.20262, 0, 0, 0.999534, -0.0305099, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416468, 3100023, 1, -3727.35, 1066.93, 131.969, 6.19734, 0, 0, 0.0429076, -0.999079, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416467, 3100023, 1, -3779.31, 1078.01, 131.969, 6.19734, 0, 0, 0.0429076, -0.999079, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416466, 3100023, 1, -3788.54, 1111.19, 131.969, 6.19734, 0, 0, 0.0429076, -0.999079, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416460, 3100021, 1, -3750.95, 1095.07, 131.969, 3.17749, 0, 0, 0.999839, -0.0179457, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416438, 3100020, 1, -3756.13, 1092.6, 184.587, 2.88853, 0, 0, 0.992006, 0.126194, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416352, 3100019, 1, -3826.31, 1114.09, 152.177, 5.73289, 0, 0, 0.271687, -0.962386, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416351, 3100019, 1, -3826.48, 1074.19, 151.691, 0.588536, 0, 0, 0.290039, 0.957015, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416350, 3100019, 1, -3831.06, 1095.27, 152.055, 6.1369, 0, 0, 0.0730775, -0.997326, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416348, 3100019, 1, -3682.67, 1065.23, 152.438, 2.43081, 0, 0, 0.93751, 0.347957, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416347, 3100019, 1, -3677.54, 1114.62, 151.979, 3.62195, 0, 0, 0.971295, -0.237877, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416346, 3100019, 1, -3671.97, 1089.59, 151.591, 3.1539, 0, 0, 0.999981, -0.00615132, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416334, 3100012, 1, -3756.48, 1097.33, 131.969, 6.22669, 0, 0, 0.0282449, -0.999601, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416333, 3100012, 1, -3757.04, 1087.51, 131.969, 6.22669, 0, 0, 0.0282449, -0.999601, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416332, 3100012, 1, -3759.48, 1092.74, 131.969, 6.22669, 0, 0, 0.0282449, -0.999601, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416331, 3100012, 1, -3753.37, 1092.4, 131.969, 6.22669, 0, 0, 0.0282449, -0.999601, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416329, 3100017, 1, -3841.79, 1110.18, 154.796, 2.87145, 0, 0, 0.990892, 0.13466, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416328, 3100017, 1, -3844.86, 1081.44, 154.798, 3.25237, 0, 0, 0.998466, -0.0553605, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416327, 3100017, 1, -3825.25, 1055.65, 154.787, 4.12024, 0, 0, 0.882652, -0.470027, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416326, 3100017, 1, -3795.56, 1042.14, 154.787, 4.7996, 0, 0, 0.675609, -0.73726, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416325, 3100017, 1, -3771.49, 1038.01, 154.781, 4.69358, 0, 0, 0.713727, -0.700424, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416324, 3100017, 1, -3737.91, 1033.69, 154.776, 4.66295, 0, 0, 0.72437, -0.689412, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416323, 3100017, 1, -3711.08, 1040.39, 154.788, 4.37627, 0, 0, 0.815421, -0.578868, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416322, 3100017, 1, -3688.39, 1045.79, 154.787, 5.10984, 0, 0, 0.553595, -0.832786, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416321, 3100017, 1, -3661.81, 1076.24, 154.796, 5.85989, 0, 0, 0.210072, -0.977686, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416319, 3100017, 1, -3667.96, 1124.15, 154.788, 0.762656, 0, 0, 0.372153, 0.928171, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416318, 3100017, 1, -3694.91, 1144.58, 154.788, 1.17185, 0, 0, 0.552969, 0.833202, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416317, 3100017, 1, -3731.14, 1148.42, 154.788, 1.66508, 0, 0, 0.739642, 0.673001, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416316, 3100017, 1, -3795.53, 1146.75, 154.788, 1.61009, 0, 0, 0.720861, 0.693079, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416315, 3100017, 1, -3826.07, 1133.82, 154.788, 2.24391, 0, 0, 0.900951, 0.433922, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416314, 3100018, 1, -3650.89, 1010.83, 158.207, 0.0188813, 0, 0, 0.00944052, 0.999955, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416313, 3100018, 1, -3603.58, 1010.88, 158.208, 4.77447, 0, 0, 0.684821, -0.728712, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416312, 3100018, 1, -3603.21, 1035.81, 158.209, 4.70535, 0, 0, 0.709589, -0.704615, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416311, 3100018, 1, -3601.96, 1150.62, 158.209, 3.19346, 0, 0, 0.999664, -0.0259328, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416310, 3100018, 1, -3602.43, 1175.29, 158.207, 0.0518701, 0, 0, 0.0259321, 0.999664, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416309, 3100018, 1, -3649.13, 1175.65, 158.208, 6.22117, 0, 0, 0.0310006, -0.999519, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416308, 3100018, 1, -3855.35, 1177.48, 158.207, 6.2738, 0, 0, 0.00469245, -0.999989, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416307, 3100018, 1, -3902.15, 1177.98, 158.207, 4.73049, 0, 0, 0.700677, -0.713479, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416306, 3100018, 1, -3902.18, 1152.72, 158.214, 1.51114, 0, 0, 0.685705, 0.727879, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416305, 3100018, 1, -3903.19, 1038.2, 158.215, 4.64096, 0, 0, 0.731905, -0.681406, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416304, 3100018, 1, -3903.13, 1012.9, 158.214, 1.86614, 0, 0, 0.803452, 0.595369, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416303, 3100018, 1, -3856.72, 1012.99, 158.215, 4.70143, 0, 0, 0.710969, -0.703223, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416302, 177015, 1, -3612.07, 1110.55, 154.788, 1.14044, 0, 0, 0.539818, 0.841782, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416301, 177015, 1, -3892.62, 1106.37, 154.789, 2.16539, 0, 0, 0.883224, 0.468952, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416282, 3100013, 1, -3962.98, 1146.29, 161.04, 6.24082, 0, 0, 0.0211813, -0.999776, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416281, 3100013, 1, -3962.91, 1111.57, 161.042, 6.26438, 0, 0, 0.00940181, -0.999956, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416280, 3100014, 1, -3990.03, 1129.66, 161.027, 3.18956, 0, 0, 0.999712, -0.0239807, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416279, 3100013, 1, -3990.31, 1139.07, 161.027, 3.14243, 0, 0, 1, -0.000421091, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416278, 3100013, 1, -3990.3, 1119.99, 161.027, 3.14243, 0, 0, 1, -0.000421091, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416277, 180352, 1, -3990.08, 1209.13, 161.071, 6.2589, 0, 0, 0.0121442, -0.999926, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416276, 180352, 1, -3990.59, 1193.78, 161.048, 6.28246, 0, 0, 0.000363262, -1, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416275, 180352, 1, -3994.23, 1209.19, 161.075, 6.25105, 0, 0, 0.0160682, -0.999871, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416274, 180352, 1, -3994.72, 1193.9, 161.064, 6.25105, 0, 0, 0.0160682, -0.999871, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416273, 180352, 1, -3998.08, 1209.17, 161.081, 6.25105, 0, 0, 0.0160682, -0.999871, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416272, 180352, 1, -3998.59, 1194.13, 161.077, 6.25105, 0, 0, 0.0160682, -0.999871, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416271, 180352, 1, -4002.29, 1194.28, 161.09, 6.25105, 0, 0, 0.0160682, -0.999871, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416270, 180352, 1, -4001.81, 1209.17, 161.088, 6.25105, 0, 0, 0.0160682, -0.999871, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416269, 184287, 1, -3977.75, 1207.61, 161.048, 0.321292, 0, 0, 0.159956, 0.987124, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416268, 184287, 1, -3979.67, 1058.1, 161.049, 5.74054, 0, 0, 0.268005, -0.963417, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416265, 180352, 1, -3994.29, 1056.23, 161.074, 6.28246, 0, 0, 0.000360401, -1, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416263, 180352, 1, -3997.78, 1056.38, 161.079, 0.00162983, 0, 0, 0.000814915, 1, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416262, 180352, 1, -4000.27, 1056.26, 161.083, 0.0330471, 0, 0, 0.0165228, 0.999864, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416261, 180352, 1, -4002.82, 1056.17, 161.089, 6.27539, 0, 0, 0.00389685, -0.999992, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416260, 180352, 1, -3992.98, 1071.51, 161.053, 0.0000612302, 0, 0, 0.0000306151, 1, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416259, 180352, 1, -3996.27, 1071.51, 161.065, 0.0000612302, 0, 0, 0.0000306151, 1, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416258, 180352, 1, -4000.09, 1071.51, 161.079, 0.0000612302, 0, 0, 0.0000306151, 1, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416257, 180352, 1, -4002.82, 1071.51, 161.089, 0.0000612302, 0, 0, 0.0000306151, 1, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416256, 3100017, 1, -3976.62, 1063.06, 161.044, 0.000850195, 0, 0, 0.000425098, 1, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416255, 3100017, 1, -3975.32, 1201.63, 161.046, 6.20942, 0, 0, 0.0368718, -0.99932, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416253, 177015, 1, -4059.95, 1063.93, 161.218, 3.16365, 0, 0, 0.999939, -0.0110299, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416250, 177015, 1, -4057.02, 1202.58, 161.218, 3.08433, 0, 0, 0.99959, 0.0286268, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416249, 3100016, 1, -4082.38, 1146.15, 161.214, 1.55439, 0, 0, 0.701282, 0.712884, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416248, 3100016, 1, -4088.62, 1122.66, 161.214, 4.70933, 0, 0, 0.708186, -0.706026, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416247, 3100016, 1, -4082.48, 1122.78, 161.214, 4.51298, 0, 0, 0.77398, -0.63321, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416246, 3100016, 1, -4087.6, 1145.71, 161.214, 1.53633, 0, 0, 0.694816, 0.719188, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416243, 183269, 1, -4091.69, 1122.18, 161.213, 3.16602, 0, 0, 0.999925, -0.0122132, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416242, 183269, 1, -4085.28, 1122.34, 161.213, 3.16602, 0, 0, 0.999925, -0.0122132, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416241, 183269, 1, -4079.57, 1122.11, 161.213, 3.10711, 0, 0, 0.999851, 0.0172382, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416240, 183269, 1, -4079.44, 1146.74, 161.213, 3.14167, 0, 0, 1, -0.000039502, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416239, 183269, 1, -4084.85, 1146.74, 161.213, 3.14167, 0, 0, 1, -0.000039502, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416238, 183269, 1, -4090.16, 1146.74, 161.213, 3.14167, 0, 0, 1, -0.000039502, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416223, 3100015, 1, -4049.5, 1096.81, 162.261, 6.21896, 0, 0, 0.0321087, -0.999484, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416222, 3100015, 1, -4049.67, 1085.95, 163.185, 6.20787, 0, 0, 0.0376464, -0.999291, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416221, 3100015, 1, -4020.07, 1086.87, 163.817, 3.09151, 0, 0, 0.999687, 0.0250375, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416220, 3100015, 1, -4019.48, 1098.66, 163.817, 3.09151, 0, 0, 0.999687, 0.0250375, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416219, 3100015, 1, -4018.81, 1178.66, 163.423, 3.10606, 0, 0, 0.999842, 0.017765, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416218, 3100015, 1, -4018.84, 1168.84, 164.078, 3.09486, 0, 0, 0.999727, 0.0233648, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416217, 3100015, 1, -4048.78, 1180.24, 164.868, 6.25585, 0, 0, 0.0136683, -0.999907, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416216, 3100015, 1, -4049.08, 1169.17, 164.868, 6.27941, 0, 0, 0.00188795, -0.999998, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416210, 185284, 1, -4063.9, 1115.76, 161.213, 1.59844, 0, 0, 0.716811, 0.697268, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416209, 185284, 1, -4063.68, 1151.05, 161.214, 2.77418, 0, 0, 0.983173, 0.182676, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416208, 177015, 1, -4010.14, 1131.48, 161.091, 0.0402038, 0, 0, 0.0201005, 0.999798, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416197, 3100013, 1, -4143.79, 1155.49, 161.213, 6.28177, 0, 0, 0.000707539, -1, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416196, 3100013, 1, -4123.38, 1154.9, 161.214, 6.26449, 0, 0, 0.0093465, -0.999956, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416195, 3100013, 1, -4143.26, 1116.54, 161.215, 0.00565672, 0, 0, 0.00282836, 0.999996, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416194, 3100013, 1, -4124.96, 1115.66, 161.215, 0.00172949, 0, 0, 0.000864744, 1, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416193, 3100014, 1, -4098.76, 1119.07, 161.214, 6.26528, 0, 0, 0.00895265, -0.99996, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416192, 3100014, 1, -4098.02, 1149.46, 161.213, 6.20638, 0, 0, 0.0383947, -0.999263, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416187, 3100013, 1, -4102.52, 1154.55, 161.214, 0.0567198, 0, 0, 0.0283561, 0.999598, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416186, 3100013, 1, -4104.68, 1114.97, 161.214, 6.21031, 0, 0, 0.0364272, -0.999336, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416173, 181255, 1, -3739.85, 1146.31, 162.83, 3.13791, 0, 0, 0.999998, 0.00183947, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416172, 181255, 1, -3739.85, 1145.55, 162.828, 3.13791, 0, 0, 0.999998, 0.00183947, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416171, 181255, 1, -3739.85, 1145.12, 162.262, 3.13791, 0, 0, 0.999998, 0.00183947, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416170, 181255, 1, -3739.85, 1144.68, 161.696, 3.13791, 0, 0, 0.999998, 0.00183947, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416169, 181255, 1, -3739.86, 1144.24, 161.13, 3.13791, 0, 0, 0.999998, 0.00183947, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416168, 181255, 1, -3739.86, 1143.8, 160.563, 3.13791, 0, 0, 0.999998, 0.00183947, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416166, 181255, 1, -3740.03, 1041, 163.397, 3.19132, 0, 0, 0.999691, -0.024862, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416165, 181255, 1, -3740.07, 1041.76, 163.394, 3.19132, 0, 0, 0.999691, -0.024862, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416164, 181255, 1, -3740.09, 1042.2, 162.827, 3.19132, 0, 0, 0.999691, -0.024862, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416163, 181255, 1, -3740.12, 1042.64, 162.261, 3.19132, 0, 0, 0.999691, -0.024862, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416162, 181255, 1, -3740.13, 1042.97, 161.695, 3.19132, 0, 0, 0.999691, -0.024862, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416161, 181255, 1, -3740.15, 1043.41, 161.129, 3.19132, 0, 0, 0.999691, -0.024862, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416160, 181255, 1, -3740.14, 1043.73, 160.563, 3.21881, 0, 0, 0.999255, -0.0385995, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416159, 181255, 1, -3762.14, 1041.39, 163.367, 0.00653503, 0, 0, 0.00326751, 0.999995, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416158, 181255, 1, -3762.15, 1041.72, 162.801, 0.00653503, 0, 0, 0.00326751, 0.999995, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416157, 181255, 1, -3762.15, 1042.04, 162.235, 0.00653503, 0, 0, 0.00326751, 0.999995, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416156, 181255, 1, -3762.15, 1042.49, 161.669, 0.00653503, 0, 0, 0.00326751, 0.999995, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416155, 181255, 1, -3762.15, 1042.93, 161.103, 0.00653503, 0, 0, 0.00326751, 0.999995, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416154, 181255, 1, -3762.16, 1043.36, 160.537, 0.00653503, 0, 0, 0.00326751, 0.999995, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416153, 181255, 1, -3842.11, 1085.21, 163.484, 0.396094, 0, 0, 0.196755, 0.980453, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416152, 181255, 1, -3841.85, 1084.6, 163.221, 0.396094, 0, 0, 0.196755, 0.980453, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416151, 181255, 1, -3841.64, 1084.1, 162.799, 0.396094, 0, 0, 0.196755, 0.980453, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416150, 181255, 1, -3841.51, 1083.79, 162.233, 0.396094, 0, 0, 0.196755, 0.980453, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416149, 181255, 1, -3841.26, 1083.18, 161.96, 0.396094, 0, 0, 0.196755, 0.980453, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416148, 181255, 1, -3841.01, 1082.59, 161.677, 0.396094, 0, 0, 0.196755, 0.980453, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416147, 181255, 1, -3840.89, 1082.29, 161.111, 0.396094, 0, 0, 0.196755, 0.980453, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416146, 181255, 1, -3840.45, 1081.29, 160.545, 1.83337, 0, 0, 0.79359, 0.608453, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416145, 181255, 1, -3839.72, 1081.49, 160.446, 1.88364, 0, 0, 0.80863, 0.588318, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416144, 181255, 1, -3838.98, 1081.73, 160.356, 1.89542, 0, 0, 0.812081, 0.583545, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416143, 181255, 1, -3829.35, 1062.51, 160.093, 2.16283, 0, 0, 0.882624, 0.47008, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416142, 181255, 1, -3829.99, 1062.08, 159.766, 2.16283, 0, 0, 0.882624, 0.47008, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416141, 181255, 1, -3830.45, 1061.77, 159.318, 2.16283, 0, 0, 0.882624, 0.47008, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416140, 181255, 1, -3830.81, 1061.53, 158.752, 2.16283, 0, 0, 0.882624, 0.47008, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416139, 181255, 1, -3831.18, 1061.28, 158.186, 2.16283, 0, 0, 0.882624, 0.47008, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416138, 181255, 1, -3831.54, 1061.03, 157.619, 2.16283, 0, 0, 0.882624, 0.47008, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416137, 181255, 1, -3831.9, 1060.79, 157.053, 2.16283, 0, 0, 0.882624, 0.47008, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416136, 181255, 1, -3832.27, 1060.54, 156.487, 2.16283, 0, 0, 0.882624, 0.47008, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416135, 181255, 1, -3832.54, 1060.36, 155.921, 2.16283, 0, 0, 0.882624, 0.47008, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416134, 181255, 1, -3832.88, 1060.13, 155.355, 2.16283, 0, 0, 0.882624, 0.47008, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416133, 181255, 1, -3833.24, 1059.89, 154.789, 2.16283, 0, 0, 0.882624, 0.47008, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416132, 181255, 1, -3816.05, 1050.76, 160.07, 2.56531, 0, 0, 0.958774, 0.284169, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416131, 181255, 1, -3816.59, 1049.93, 160.212, 2.56531, 0, 0, 0.958774, 0.284169, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416130, 181255, 1, -3816.89, 1049.47, 159.765, 2.56531, 0, 0, 0.958774, 0.284169, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416129, 181255, 1, -3817.13, 1049.11, 159.198, 2.56531, 0, 0, 0.958774, 0.284169, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416128, 181255, 1, -3817.37, 1048.74, 158.632, 2.56531, 0, 0, 0.958774, 0.284169, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416127, 181255, 1, -3817.54, 1048.47, 158.066, 2.56531, 0, 0, 0.958774, 0.284169, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416126, 181255, 1, -3817.84, 1048.01, 157.619, 2.56531, 0, 0, 0.958774, 0.284169, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416125, 181255, 1, -3818.08, 1047.64, 157.053, 2.56531, 0, 0, 0.958774, 0.284169, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416124, 181255, 1, -3818.26, 1047.36, 156.487, 2.56531, 0, 0, 0.958774, 0.284169, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416123, 181255, 1, -3818.43, 1047.09, 155.921, 2.56531, 0, 0, 0.958774, 0.284169, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416122, 181255, 1, -3818.67, 1046.72, 155.355, 2.56531, 0, 0, 0.958774, 0.284169, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416121, 181255, 1, -3818.92, 1046.35, 154.788, 2.56531, 0, 0, 0.958774, 0.284169, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416120, 181255, 1, -3782.11, 1043.21, 160.128, 3.12137, 0, 0, 0.999949, 0.0101087, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416119, 181255, 1, -3782.13, 1042.44, 160.129, 3.12137, 0, 0, 0.999949, 0.0101087, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416118, 181255, 1, -3782.14, 1041.68, 160.117, 3.12137, 0, 0, 0.999949, 0.0101087, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416117, 181255, 1, -3782.16, 1041.13, 159.712, 3.12137, 0, 0, 0.999949, 0.0101087, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416116, 181255, 1, -3782.21, 1040.67, 159.154, 3.10302, 0, 0, 0.999814, 0.0192831, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416115, 181255, 1, -3782.22, 1040.23, 158.588, 3.10302, 0, 0, 0.999814, 0.0192831, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416114, 181255, 1, -3782.24, 1039.8, 158.021, 3.10302, 0, 0, 0.999814, 0.0192831, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416113, 181255, 1, -3782.25, 1039.47, 157.455, 3.10302, 0, 0, 0.999814, 0.0192831, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416112, 181255, 1, -3782.27, 1039.14, 156.889, 3.10302, 0, 0, 0.999814, 0.0192831, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416111, 181255, 1, -3782.28, 1038.7, 156.323, 3.10302, 0, 0, 0.999814, 0.0192831, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416110, 181255, 1, -3782.3, 1038.37, 155.757, 3.10302, 0, 0, 0.999814, 0.0192831, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416109, 181255, 1, -3782.31, 1038.04, 155.191, 3.10302, 0, 0, 0.999814, 0.0192831, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416108, 181255, 1, -3782.33, 1037.5, 154.783, 3.10302, 0, 0, 0.999814, 0.0192831, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416107, 181255, 1, -3800.49, 1044.62, 160.175, 2.91139, 0, 0, 0.993383, 0.114849, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416106, 181255, 1, -3800.62, 1044.09, 159.746, 2.91139, 0, 0, 0.993383, 0.114849, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416105, 181255, 1, -3800.69, 1043.77, 159.18, 2.91139, 0, 0, 0.993383, 0.114849, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416104, 181255, 1, -3800.77, 1043.45, 158.614, 2.91139, 0, 0, 0.993383, 0.114849, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416103, 181255, 1, -3800.89, 1042.92, 158.184, 2.91139, 0, 0, 0.993383, 0.114849, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416102, 181255, 1, -3800.97, 1042.6, 157.618, 2.91139, 0, 0, 0.993383, 0.114849, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416101, 181255, 1, -3801.04, 1042.28, 157.052, 2.91139, 0, 0, 0.993383, 0.114849, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416100, 181255, 1, -3801.12, 1041.96, 156.485, 2.91139, 0, 0, 0.993383, 0.114849, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416099, 181255, 1, -3801.22, 1041.54, 155.919, 2.91139, 0, 0, 0.993383, 0.114849, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416098, 181255, 1, -3801.31, 1041.12, 155.353, 2.91139, 0, 0, 0.993383, 0.114849, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416097, 181255, 1, -3801.41, 1040.69, 154.787, 2.91139, 0, 0, 0.993383, 0.114849, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416096, 181255, 1, -3702.82, 1044.07, 159.97, 3.27424, 0, 0, 0.997801, -0.0662753, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416095, 181255, 1, -3702.73, 1043.42, 159.643, 3.27424, 0, 0, 0.997801, -0.0662753, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416094, 181255, 1, -3702.69, 1043.09, 159.077, 3.27424, 0, 0, 0.997801, -0.0662753, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416093, 181255, 1, -3702.63, 1042.66, 158.51, 3.27424, 0, 0, 0.997801, -0.0662753, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416092, 181255, 1, -3702.59, 1042.34, 157.944, 3.27424, 0, 0, 0.997801, -0.0662753, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416091, 181255, 1, -3702.53, 1041.9, 157.378, 3.27424, 0, 0, 0.997801, -0.0662753, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416090, 181255, 1, -3702.47, 1041.47, 156.812, 3.27424, 0, 0, 0.997801, -0.0662753, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416089, 181255, 1, -3702.42, 1041.03, 156.246, 3.27424, 0, 0, 0.997801, -0.0662753, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416088, 181255, 1, -3702.36, 1040.6, 155.68, 3.27424, 0, 0, 0.997801, -0.0662753, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416087, 181255, 1, -3702.29, 1040.09, 155.208, 3.27424, 0, 0, 0.997801, -0.0662753, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416086, 181255, 1, -3702.22, 1039.55, 154.787, 3.27424, 0, 0, 0.997801, -0.0662753, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416085, 181255, 1, -3721.88, 1042.6, 159.546, 3.1313, 0, 0, 0.999987, 0.00514715, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416084, 181255, 1, -3721.89, 1041.94, 159.348, 3.1313, 0, 0, 0.999987, 0.00514715, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416083, 181255, 1, -3721.89, 1041.28, 159.149, 3.1313, 0, 0, 0.999987, 0.00514715, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416082, 181255, 1, -3721.9, 1040.73, 158.745, 3.1313, 0, 0, 0.999987, 0.00514715, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416081, 181255, 1, -3721.9, 1040.3, 158.179, 3.1313, 0, 0, 0.999987, 0.00514715, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416080, 181255, 1, -3721.91, 1039.97, 157.613, 3.1313, 0, 0, 0.999987, 0.00514715, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416079, 181255, 1, -3721.91, 1039.54, 157.047, 3.1313, 0, 0, 0.999987, 0.00514715, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416078, 181255, 1, -3721.91, 1039.21, 156.481, 3.1313, 0, 0, 0.999987, 0.00514715, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416077, 181255, 1, -3721.92, 1038.87, 155.915, 3.1313, 0, 0, 0.999987, 0.00514715, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416076, 181255, 1, -3721.92, 1038.43, 155.349, 3.18156, 0, 0, 0.9998, -0.0199843, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416075, 181255, 1, -3721.9, 1038, 154.783, 3.18156, 0, 0, 0.9998, -0.0199843, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416074, 181255, 1, -3665.86, 1070.94, 160.377, 2.10242, 0, 0, 0.868025, 0.49652, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416073, 181255, 1, -3666.05, 1069.28, 160.716, 4.31175, 0, 0, 0.833669, -0.552265, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416072, 181255, 1, -3666.93, 1067.21, 160.43, 4.31175, 0, 0, 0.833669, -0.552265, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416071, 181255, 1, -3668.11, 1065.46, 160.326, 3.99366, 0, 0, 0.910611, -0.413264, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416070, 181255, 1, -3670.06, 1064.77, 160.042, 2.56109, 0, 0, 0.958172, 0.286192, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416069, 181255, 1, -3682.74, 1051.4, 160.231, 5.3332, 0, 0, 0.457332, -0.889296, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416068, 181255, 1, -3681.1, 1050.51, 160.112, 0.315292, 0, 0, 0.156994, 0.9876, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416067, 181255, 1, -3679.04, 1051.81, 159.953, 0.876189, 0, 0, 0.424214, 0.905562, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416066, 181255, 1, -3677.47, 1053.69, 159.829, 0.876189, 0, 0, 0.424214, 0.905562, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416065, 181255, 1, -3676.3, 1055.4, 159.724, 1.36628, 0, 0, 0.63123, 0.775595, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416064, 181255, 1, -3676.47, 1057.02, 159.639, 2.3873, 0, 0, 0.929718, 0.368271, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416063, 181255, 1, -3673.5, 1060.46, 159.838, 3.94425, 0, 0, 0.920543, -0.390641, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416062, 181255, 1, -3673.03, 1060, 159.534, 3.94425, 0, 0, 0.920543, -0.390641, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416061, 181255, 1, -3672.71, 1059.7, 158.968, 3.94425, 0, 0, 0.920543, -0.390641, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416060, 181255, 1, -3672.47, 1059.42, 158.402, 3.84717, 0, 0, 0.938412, -0.345518, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416059, 181255, 1, -3672.26, 1059.17, 157.835, 3.84717, 0, 0, 0.938412, -0.345518, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416058, 181255, 1, -3671.9, 1058.75, 157.386, 3.84717, 0, 0, 0.938412, -0.345518, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416057, 181255, 1, -3671.62, 1058.42, 156.819, 3.84717, 0, 0, 0.938412, -0.345518, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416056, 181255, 1, -3671.4, 1058.17, 156.253, 3.84717, 0, 0, 0.938412, -0.345518, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416055, 181255, 1, -3671.12, 1057.83, 155.687, 3.84717, 0, 0, 0.938412, -0.345518, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416054, 181255, 1, -3670.76, 1057.42, 155.237, 3.84717, 0, 0, 0.938412, -0.345518, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416053, 181255, 1, -3670.41, 1057, 154.787, 3.84717, 0, 0, 0.938412, -0.345518, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416052, 181255, 1, -3681.42, 1134.42, 160.19, 0.447491, 0, 0, 0.221883, 0.975073, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416051, 181255, 1, -3679.37, 1134.58, 160.127, 5.62798, 0, 0, 0.321776, -0.946816, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416049, 181255, 1, -3677.7, 1133.46, 160.077, 5.49289, 0, 0, 0.384945, -0.922939, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416048, 181255, 1, -3676.22, 1131.64, 159.984, 5.3955, 0, 0, 0.429414, -0.903108, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416046, 181255, 1, -3674.86, 1130.25, 159.907, 5.59028, 0, 0, 0.339564, -0.940583, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416045, 181255, 1, -3675.6, 1128.67, 159.821, 3.89303, 0, 0, 0.930245, -0.36694, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416043, 181255, 1, -3667.83, 1118.06, 158.693, 5.14441, 0, 0, 0.539116, -0.842232, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416042, 181255, 1, -3667.03, 1118.43, 158.628, 5.14441, 0, 0, 0.539116, -0.842232, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416041, 181255, 1, -3666.54, 1118.66, 158.186, 5.14441, 0, 0, 0.539116, -0.842232, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416040, 181255, 1, -3666.24, 1118.79, 157.62, 5.14441, 0, 0, 0.539116, -0.842232, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416039, 181255, 1, -3665.94, 1118.93, 157.053, 5.14441, 0, 0, 0.539116, -0.842232, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416038, 181255, 1, -3665.62, 1119.08, 156.487, 5.14441, 0, 0, 0.539116, -0.842232, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416037, 181255, 1, -3665.23, 1119.26, 155.921, 5.14441, 0, 0, 0.539116, -0.842232, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416036, 181255, 1, -3664.83, 1119.45, 155.355, 5.14441, 0, 0, 0.539116, -0.842232, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416035, 181255, 1, -3664.53, 1119.58, 154.789, 5.14441, 0, 0, 0.539116, -0.842232, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416034, 181255, 1, -3716.05, 1144.75, 159.788, 0.852967, 0, 0, 0.413672, 0.910426, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416033, 181255, 1, -3714.02, 1145.57, 159.912, 6.25415, 0, 0, 0.0145169, -0.999895, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416032, 181255, 1, -3711.57, 1145.68, 160.098, 6.03188, 0, 0, 0.125321, -0.992116, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416029, 181255, 1, -3710.08, 1145.1, 160.194, 6.01674, 0, 0, 0.132829, -0.991139, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416028, 181255, 1, -3707.87, 1144.49, 159.92, 6.16439, 0, 0, 0.0593603, -0.998237, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416027, 181255, 1, -3707.19, 1143.44, 159.928, 4.58968, 0, 0, 0.749134, -0.662418, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416025, 181255, 1, -3702.34, 1142.9, 159.954, 6.1432, 0, 0, 0.0699377, -0.997551, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416024, 181255, 1, -3702.23, 1143.7, 159.954, 6.1432, 0, 0, 0.0699377, -0.997551, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416023, 181255, 1, -3702.18, 1144.44, 159.884, 6.20714, 0, 0, 0.0380147, -0.999277, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416022, 181255, 1, -3702.15, 1144.88, 159.319, 6.20714, 0, 0, 0.0380147, -0.999277, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416021, 181255, 1, -3702.12, 1145.2, 158.752, 6.20714, 0, 0, 0.0380147, -0.999277, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416020, 181255, 1, -3702.1, 1145.53, 158.186, 6.20714, 0, 0, 0.0380147, -0.999277, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416019, 181255, 1, -3702.07, 1145.87, 157.62, 6.20714, 0, 0, 0.0380147, -0.999277, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416018, 181255, 1, -3702.04, 1146.2, 157.053, 6.20714, 0, 0, 0.0380147, -0.999277, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416017, 181255, 1, -3701.93, 1146.5, 156.487, 6.16611, 0, 0, 0.0585052, -0.998287, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416016, 181255, 1, -3701.89, 1146.85, 155.921, 6.16611, 0, 0, 0.0585052, -0.998287, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416015, 181255, 1, -3701.85, 1147.24, 155.355, 6.16611, 0, 0, 0.0585052, -0.998287, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416014, 181255, 1, -3701.85, 1147.24, 154.789, 6.16611, 0, 0, 0.0585052, -0.998287, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416013, 181255, 1, -3701.74, 1148.11, 154.789, 6.16611, 0, 0, 0.0585052, -0.998287, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416418, 179900, 1, -3704.78, 1094.05, 131.97, 0.655655, 0, 0, 0.321987, 0.946744, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416417, 179900, 1, -3704.78, 1094.05, 131.97, 0.655655, 0, 0, 0.321987, 0.946744, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416416, 179900, 1, -3704.22, 1073.2, 131.97, 2.35211, 0, 0, 0.923097, 0.384567, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416415, 179900, 1, -3704.22, 1073.2, 131.97, 2.02225, 0, 0, 0.847429, 0.530909, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416414, 179900, 1, -3761.73, 1066.13, 131.969, 1.3036, 0, 0, 0.60662, 0.794992, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416413, 179900, 1, -3761.73, 1066.13, 131.969, 1.3036, 0, 0, 0.60662, 0.794992, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416412, 179900, 1, -3720.15, 1093.1, 131.969, 2.89997, 0, 0, 0.992711, 0.120518, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416411, 179900, 1, -3720.15, 1093.1, 131.969, 2.89997, 0, 0, 0.992711, 0.120518, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416410, 179900, 1, -3691.69, 1106.92, 131.969, 5.57817, 0, 0, 0.345252, -0.93851, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416409, 179900, 1, -3691.69, 1106.92, 131.969, 6.01407, 0, 0, 0.134153, -0.990961, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416408, 179900, 1, -3713.6, 1115.41, 131.969, 6.2811, 0, 0, 0.00104037, -0.999999, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416407, 179900, 1, -3713.6, 1115.41, 131.969, 6.2811, 0, 0, 0.00104037, -0.999999, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416406, 179900, 1, -3740.09, 1111.74, 131.969, 0.245319, 0, 0, 0.122352, 0.992487, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416405, 179900, 1, -3740.09, 1111.74, 131.969, 0.245319, 0, 0, 0.122352, 0.992487, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416404, 179900, 1, -3781.84, 1096.9, 131.969, 4.61999, 0, 0, 0.739009, -0.673695, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416403, 179900, 1, -3780.13, 1118.18, 131.969, 0.0921643, 0, 0, 0.0460658, 0.998938, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416402, 179900, 1, -3805.97, 1114.15, 131.97, 1.32524, 0, 0, 0.615184, 0.788383, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416401, 179900, 1, -3805.97, 1114.15, 131.97, 1.45876, 0, 0, 0.666406, 0.745589, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416400, 179900, 1, -3804.9, 1069.27, 132.038, 5.79808, 0, 0, 0.24018, -0.970728, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416399, 179900, 1, -3804.9, 1069.27, 132.038, 5.1462, 0, 0, 0.538361, -0.842714, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416398, 179900, 1, -3816.03, 1091.83, 131.969, 6.09654, 0, 0, 0.0931889, -0.995648, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416397, 179900, 1, -3816.03, 1091.83, 131.969, 2.08708, 0, 0, 0.864191, 0.503165, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416396, 179900, 1, -3785, 1072.38, 131.969, 2.89997, 0, 0, 0.992711, 0.12052, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416395, 179900, 1, -3785, 1072.38, 131.969, 2.89997, 0, 0, 0.992711, 0.12052, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416394, 179900, 1, -3737.19, 1065.39, 132.514, 3.10024, 0, 0, 0.999786, 0.0206734, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416393, 179900, 1, -3737.19, 1065.39, 132.514, 3.10024, 0, 0, 0.999786, 0.0206734, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416392, 148996, 1, -3737.54, 1065.5, 132.474, 0.221758, 0, 0, 0.110652, 0.993859, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416391, 148996, 1, -3804.64, 1069.49, 132.043, 5.18548, 0, 0, 0.521709, -0.853123, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416390, 148996, 1, -3815.3, 1091.6, 131.97, 4.31369, 0, 0, 0.833133, -0.553073, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416389, 148996, 1, -3806.46, 1113.94, 131.97, 3.41441, 0, 0, 0.990711, -0.135985, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416388, 148996, 1, -3779.76, 1118.76, 131.97, 1.64726, 0, 0, 0.733618, 0.679562, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416387, 148996, 1, -3782, 1096.44, 131.97, 1.47055, 0, 0, 0.67079, 0.741647, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416386, 148996, 1, -3784.78, 1072.56, 131.97, 2.86856, 0, 0, 0.990696, 0.136095, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416385, 148996, 1, -3761.63, 1065.95, 131.97, 4.29405, 0, 0, 0.838523, -0.544867, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416384, 148996, 1, -3750.25, 1092, 131.97, 4.18802, 0, 0, 0.866217, -0.499669, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416383, 148996, 1, -3741.03, 1111.71, 131.97, 3.18664, 0, 0, 0.999746, -0.0225219, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416382, 148996, 1, -3691.39, 1107.13, 131.97, 0.912913, 0, 0, 0.44077, 0.89762, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416381, 148996, 1, -3704.88, 1093.73, 131.97, 1.5216, 0, 0, 0.6895, 0.724286, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416380, 148996, 1, -3704.09, 1073.09, 131.97, 4.53752, 0, 0, 0.766151, -0.64266, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416379, 148996, 1, -3720.92, 1093.73, 131.97, 4.52182, 0, 0, 0.771175, -0.636623, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416378, 148996, 1, -3714.35, 1115.08, 131.97, 3.60683, 0, 0, 0.973066, -0.230527, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416438, 3100020, 1, -3756.13, 1092.6, 184.587, 2.88853, 0, 0, 0.992006, 0.126194, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370592, 500000, 1, -3866.35, 1229.52, 149.695, 4.66918, 0, 0, 0.722218, -0.691665, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370591, 500000, 1, -3861.89, 1229.25, 149.735, 4.66918, 0, 0, 0.722218, -0.691665, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370579, 500000, 1, -3832.18, 1085.85, 159.595, 3.59764, 0, 0, 0.974115, -0.226054, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370578, 500000, 1, -3830.85, 1082.93, 159.594, 3.47197, 0, 0, 0.986387, -0.164441, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370577, 500000, 1, -3829.21, 1078.16, 159.601, 3.47197, 0, 0, 0.986387, -0.164441, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370576, 500000, 1, -3820.79, 1065.11, 159.611, 3.82147, 0, 0, 0.942774, -0.333431, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370575, 500000, 1, -3824.61, 1069.63, 159.609, 3.77828, 0, 0, 0.949756, -0.312992, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370574, 500000, 1, -3816.66, 1060.92, 159.607, 4.17096, 0, 0, 0.870448, -0.492261, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370573, 500000, 1, -3813.19, 1058.83, 159.607, 4.17096, 0, 0, 0.870448, -0.492261, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370572, 500000, 1, -3809.26, 1056.47, 159.6, 4.17096, 0, 0, 0.870448, -0.492261, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370571, 500000, 1, -3803.17, 1054.14, 159.574, 4.48119, 0, 0, 0.783948, -0.620827, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370570, 500000, 1, -3799.86, 1053.36, 159.58, 4.48119, 0, 0, 0.783948, -0.620827, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370569, 500000, 1, -3795.7, 1052.38, 159.586, 4.48119, 0, 0, 0.783948, -0.620827, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370568, 500000, 1, -3786.56, 1051.69, 159.583, 4.68539, 0, 0, 0.716589, -0.697496, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370567, 500000, 1, -3783.11, 1051.6, 159.584, 4.68539, 0, 0, 0.716589, -0.697496, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370566, 500000, 1, -3778.2, 1051.47, 159.587, 4.68539, 0, 0, 0.716589, -0.697496, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370565, 500000, 1, -3771.49, 1051.35, 159.588, 4.83068, 0, 0, 0.664073, -0.747668, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370564, 500000, 1, -3768.16, 1051.31, 159.589, 4.76785, 0, 0, 0.687229, -0.726441, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370563, 500000, 1, -3763.55, 1051.2, 159.589, 4.71916, 0, 0, 0.704709, -0.709496, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370562, 500000, 1, -3756.35, 1050.43, 159.715, 4.74665, 0, 0, 0.69489, -0.719116, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370561, 500000, 1, -3752.86, 1050.55, 159.655, 4.74665, 0, 0, 0.69489, -0.719116, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370560, 500000, 1, -3747.94, 1050.72, 159.598, 4.74665, 0, 0, 0.69489, -0.719116, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370559, 500000, 1, -3741.88, 1051.02, 159.588, 4.99542, 0, 0, 0.600306, -0.799771, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370558, 500000, 1, -3737.7, 1051, 159.588, 4.73624, 0, 0, 0.698623, -0.71549, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370557, 500000, 1, -3733.21, 1051.08, 159.587, 4.63414, 0, 0, 0.734223, -0.678908, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370556, 500000, 1, -3726.77, 1050.96, 159.588, 4.86976, 0, 0, 0.649338, -0.7605, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370555, 500000, 1, -3723.47, 1051.16, 159.581, 4.67498, 0, 0, 0.720209, -0.693757, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370554, 500000, 1, -3718, 1051.29, 159.578, 4.67498, 0, 0, 0.720209, -0.693757, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370553, 500000, 1, -3710.46, 1051.07, 159.595, 4.88704, 0, 0, 0.642744, -0.766081, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370552, 500000, 1, -3707.24, 1051.91, 159.592, 4.84777, 0, 0, 0.657659, -0.753316, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370551, 500000, 1, -3702.17, 1052.71, 159.592, 4.87133, 0, 0, 0.648739, -0.761011, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370550, 500000, 1, -3685.28, 1060.11, 159.595, 5.12659, 0, 0, 0.546598, -0.837395, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370549, 500000, 1, -3688.93, 1057.98, 159.594, 5.21298, 0, 0, 0.509928, -0.860217, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370548, 500000, 1, -3693.14, 1055.67, 159.594, 5.21298, 0, 0, 0.509928, -0.860217, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370547, 500000, 1, -3677.96, 1068.4, 159.592, 5.5507, 0, 0, 0.358108, -0.93368, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370546, 500000, 1, -3681.33, 1064.2, 159.594, 5.56641, 0, 0, 0.350764, -0.936464, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370545, 500000, 1, -3671.47, 1081.01, 159.593, 5.90021, 0, 0, 0.190321, -0.981722, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370544, 500000, 1, -3673.36, 1076.18, 159.593, 5.86094, 0, 0, 0.209559, -0.977796, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370543, 500000, 1, -3669.05, 1090.72, 159.596, 0.0183668, 0, 0, 0.00918325, 0.999958, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370542, 500000, 1, -3669.15, 1096.54, 159.597, 6.27799, 0, 0, 0.00259653, -0.999997, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370541, 500000, 1, -3670.58, 1103.27, 159.595, 0.334891, 0, 0, 0.166664, 0.986014, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370540, 500000, 1, -3672.09, 1107.61, 159.595, 0.334891, 0, 0, 0.166664, 0.986014, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370539, 500000, 1, -3673.86, 1112.62, 159.599, 0.480191, 0, 0, 0.237795, 0.971315, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370538, 500001, 1, -3675.59, 1115.31, 159.593, 0.638836, 0, 0, 0.314014, 0.949418, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370537, 500001, 1, -3677.9, 1118.25, 159.595, 0.678106, 0, 0, 0.332594, 0.94307, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370536, 500001, 1, -3680.91, 1121.99, 159.595, 0.678106, 0, 0, 0.332594, 0.94307, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370535, 500000, 1, -3688.3, 1128.1, 159.594, 1.03939, 0, 0, 0.496615, 0.867971, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370534, 500000, 1, -3692.58, 1130.72, 159.594, 1.01975, 0, 0, 0.48807, 0.872804, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370533, 500000, 1, -3701.14, 1134.03, 159.596, 1.36612, 0, 0, 0.631169, 0.775645, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370532, 500000, 1, -3706.17, 1134.98, 159.596, 1.39754, 0, 0, 0.643275, 0.765635, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370531, 500000, 1, -3718.65, 1135.82, 159.596, 1.62923, 0, 0, 0.727461, 0.686149, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370528, 500000, 1, -3724.16, 1135.77, 159.595, 1.52948, 0, 0, 0.692351, 0.721561, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370527, 500000, 1, -3731.56, 1135.97, 159.596, 1.62609, 0, 0, 0.726384, 0.68729, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370526, 500000, 1, -3734.84, 1136.07, 159.597, 1.70071, 0, 0, 0.751513, 0.659718, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370525, 500000, 1, -3739.79, 1136.02, 159.595, 1.60253, 0, 0, 0.718237, 0.695798, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370524, 500000, 1, -3832.75, 1099.13, 159.594, 3.18232, 0, 0, 0.999793, -0.0203621, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370523, 500000, 1, -3833.06, 1095.75, 159.607, 3.17447, 0, 0, 0.999865, -0.0164358, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370522, 500000, 1, -3832.89, 1090.63, 159.594, 3.17447, 0, 0, 0.999865, -0.0164358, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370521, 500000, 1, -3830.66, 1105.96, 159.593, 2.7904, 0, 0, 0.984623, 0.174693, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370520, 500000, 1, -3828.77, 1111.1, 159.593, 2.7904, 0, 0, 0.984623, 0.174693, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370519, 500000, 1, -3817.83, 1126.79, 159.596, 2.28225, 0, 0, 0.909103, 0.416571, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370518, 500000, 1, -3823.85, 1119.21, 159.593, 2.36473, 0, 0, 0.925504, 0.378739, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370517, 500000, 1, -3820.57, 1123.11, 159.592, 2.41185, 0, 0, 0.93417, 0.356829, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370516, 500000, 1, -3813.7, 1128.99, 159.595, 2.12735, 0, 0, 0.874146, 0.485663, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370515, 500000, 1, -3807.37, 1132.55, 159.595, 1.96242, 0, 0, 0.83117, 0.556019, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370514, 500000, 1, -3803.53, 1134.12, 159.597, 1.79836, 0, 0, 0.782816, 0.622254, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370513, 500000, 1, -3799.49, 1135.05, 159.602, 1.79836, 0, 0, 0.782816, 0.622254, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370512, 500000, 1, -3794.73, 1135.72, 159.598, 1.70411, 0, 0, 0.752634, 0.658439, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370511, 500000, 1, -3745.6, 1136.57, 159.614, 1.58473, 0, 0, 0.712015, 0.702164, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370510, 500000, 1, -3749.76, 1136.66, 159.633, 1.58473, 0, 0, 0.712015, 0.702164, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370509, 500000, 1, -3755.22, 1136.68, 159.621, 1.58473, 0, 0, 0.712015, 0.702164, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370505, 500000, 1, -3760.86, 1136.14, 159.597, 1.55438, 0, 0, 0.701278, 0.712888, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370504, 500000, 1, -3764.69, 1136.21, 159.597, 1.55438, 0, 0, 0.701278, 0.712888, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370503, 500000, 1, -3769.7, 1136.28, 159.597, 1.5583, 0, 0, 0.702676, 0.71151, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370502, 500000, 1, -3776.7, 1136.51, 159.598, 1.58187, 0, 0, 0.711011, 0.703181, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370501, 500000, 1, -3781.11, 1136.33, 159.597, 1.62899, 0, 0, 0.727381, 0.686234, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4370500, 500000, 1, -3785.52, 1136.53, 159.597, 1.47584, 0, 0, 0.672751, 0.739869, 25, 100, 1, 0, 0);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770065, 1200000, 1, 0, 0, -3819.24, 1095.81, 132.033, 6.25706, 25, 5, 0, 2284, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770064, 1200000, 1, 0, 0, -3754.29, 1061.04, 132.19, 1.63499, 25, 5, 0, 2284, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770063, 1200000, 1, 0, 0, -3742.28, 1123.63, 132.36, 4.77265, 25, 5, 0, 2284, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770062, 1200000, 1, 0, 0, -3687.55, 1090.58, 131.97, 3.11547, 25, 5, 0, 2284, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416481, 187080, 1, -3688.03, 1090.3, 131.97, 0.486726, 0, 0, 0.240968, 0.970533, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416480, 187080, 1, -3754.68, 1061.1, 132.141, 0.0822453, 0, 0, 0.0411111, 0.999155, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416479, 187080, 1, -3819.05, 1095.8, 132.028, 3.00158, 0, 0, 0.997551, 0.0699496, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416478, 187080, 1, -3741.78, 1123.5, 132.335, 3.04478, 0, 0, 0.998829, 0.0483894, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416488, 1211023, 1, -3823.14, 1095.97, 132.4, 3.121, 0, 0, 0.999947, 0.010298, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416487, 1211023, 1, -3683.27, 1090.32, 131.971, 6.18719, 0, 0, 0.0479782, -0.998848, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416486, 1211023, 1, -3742.46, 1127.41, 132.525, 1.37663, 0, 0, 0.635236, 0.772318, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416485, 1211023, 1, -3754, 1058.28, 132.433, 1.65387, 0, 0, 0.735861, 0.677133, 25, 100, 1, 0, 0);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770066, 1101200, 1, 0, 0, -1257.05, 63.683, 127.875, 2.02223, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770067, 1101200, 0, 0, 0, 1627.31, 217.265, -43.1035, 1.97623, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770165, 1101200, 1, 0, 0, 9926.42, 2505.84, 1318.21, 5.0045, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770172, 1101200, 1, 0, 0, 9949.16, 2437.08, 1324.25, 4.74689, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416490, 181476, 1, -4192.7, 1133.18, 157.5, 0.01, 0, 0, 0.00499998, 0.999987, 25, 100, 1, 0, 0);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770180, 1101201, 1, 0, 0, -4110.95, 1136.79, 161.214, 6.18873, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770177, 1101201, 1, 0, 0, -4103.49, 1129.79, 161.214, 0.0406296, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770178, 1101201, 1, 0, 0, -4106.42, 1132.38, 161.214, 6.13846, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770179, 1101201, 1, 0, 0, -4109.18, 1127.13, 161.214, 6.18873, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770189, 1101201, 1, 0, 0, -4117.2, 1135.52, 161.214, 6.18873, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770187, 1101201, 1, 0, 0, -4106.21, 1136.66, 161.214, 6.18873, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770188, 1101201, 1, 0, 0, -4105.6, 1125.95, 161.214, 6.18873, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770186, 1101201, 1, 0, 0, -4100.71, 1138.89, 161.214, 6.18873, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770184, 1101201, 1, 0, 0, -4113.42, 1132.39, 161.214, 6.18873, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770185, 1101201, 1, 0, 0, -4101.28, 1132.9, 161.214, 6.18873, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770181, 1101201, 1, 0, 0, -4105.11, 1140.63, 161.214, 6.18873, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770182, 1101201, 1, 0, 0, -4102.23, 1136.54, 161.214, 6.18873, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770183, 1101201, 1, 0, 0, -4109.44, 1140.27, 161.214, 6.18873, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770196, 1101201, 1, 0, 0, -4067.27, 1146.48, 161.213, 4.81271, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770195, 1101201, 1, 0, 0, -4066.97, 1143.77, 161.213, 1.67897, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770193, 1101201, 1, 0, 0, -4021.68, 1086.92, 159.668, 1.62399, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770194, 1101201, 1, 0, 0, -4058.01, 1112.87, 161.213, 2.79031, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770222, 1101201, 1, 0, 0, -3780.13, 1137.12, 160.564, 5.07105, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770220, 1101201, 1, 0, 0, -3753.37, 1137.24, 159.844, 4.39954, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770221, 1101201, 1, 0, 0, -3768.08, 1136.84, 160.564, 4.84721, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770192, 1101201, 1, 0, 0, -4021.83, 1090.57, 159.67, 4.64149, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770190, 1101201, 1, 0, 0, -4021, 1171.55, 159.668, 1.59336, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770191, 1101201, 1, 0, 0, -4020.84, 1175.76, 159.668, 4.65013, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770219, 1101201, 1, 0, 0, -3719.39, 1136.58, 160.564, 5.00431, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770209, 1101201, 1, 0, 0, -3721.29, 1050.36, 160.563, 1.46531, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770208, 1101201, 1, 0, 0, -3722.68, 1050.48, 160.563, 1.46531, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770207, 1101201, 1, 0, 0, -3732.8, 1050.39, 160.563, 1.36713, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770206, 1101201, 1, 0, 0, -3771.53, 1050.54, 160.579, 1.61454, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770218, 1101201, 1, 0, 0, -3707.07, 1135.74, 160.564, 4.47809, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770217, 1101201, 1, 0, 0, -3674.12, 1114.88, 159.52, 3.53876, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770216, 1101201, 1, 0, 0, -3679.73, 1121.76, 160.563, 3.8215, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770215, 1101201, 1, 0, 0, -3671.84, 1110.38, 160.564, 3.35026, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770214, 1101201, 1, 0, 0, -3676.24, 1068.95, 160.562, 2.35673, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770213, 1101201, 1, 0, 0, -3692.65, 1055.16, 160.563, 2.25463, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770212, 1101201, 1, 0, 0, -3686.57, 1058.24, 160.563, 2.11719, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770211, 1101201, 1, 0, 0, -3704.08, 1051.81, 160.397, 1.71663, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770210, 1101201, 1, 0, 0, -3701.33, 1052.06, 160.563, 1.63024, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770205, 1101201, 1, 0, 0, -3761.87, 1049.99, 160.564, 1.51637, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770204, 1101201, 1, 0, 0, -3782.28, 1050.67, 160.563, 1.42997, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770203, 1101201, 1, 0, 0, -3795.82, 1051.45, 160.563, 1.06476, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770202, 1101201, 1, 0, 0, -3831.46, 1106.97, 160.564, 5.67112, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770200, 1101201, 1, 0, 0, -3820.65, 1124.07, 160.563, 5.6311, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770201, 1101201, 1, 0, 0, -3825.05, 1118.99, 160.563, 5.57219, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770199, 1101201, 1, 0, 0, -3981.49, 1208.5, 161.055, 0.0971777, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770198, 1101201, 1, 0, 0, -4013.77, 1140.68, 161.091, 4.8724, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2770197, 1101201, 1, 0, 0, -4009.45, 1141.38, 161.091, 4.4797, 25, 5, 0, 3517, 0, 0, 0, 0, 0, 0, 10);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416501, 186286, 1, -3811.89, 1123.94, 131.962, 2.22009, 0, 0, 0.89572, 0.444619, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416502, 186286, 1, -3819.08, 1116.11, 132.187, 2.78951, 0, 0, 0.984545, 0.175134, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416503, 186286, 1, -3825.85, 1100.41, 132.564, 2.91517, 0, 0, 0.993599, 0.112968, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416504, 186286, 1, -3825.24, 1084.95, 132.656, 3.32751, 0, 0, 0.995683, -0.0928232, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416505, 186286, 1, -3821.84, 1075.17, 132.202, 3.52386, 0, 0, 0.98179, -0.18997, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416506, 186286, 1, -3815.2, 1066.17, 132.055, 3.81445, 0, 0, 0.943939, -0.33012, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416507, 186286, 1, -3805.06, 1059.22, 132.473, 4.22286, 0, 0, 0.857383, -0.514678, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416508, 186286, 1, -3793.49, 1056.26, 132.288, 4.85118, 0, 0, 0.656376, -0.754434, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416509, 186286, 1, -3780.64, 1055.89, 132.222, 4.76871, 0, 0, 0.686916, -0.726736, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416510, 186286, 1, -3769.78, 1055.75, 132.49, 4.76871, 0, 0, 0.686916, -0.726736, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416511, 186286, 1, -3758.06, 1055.67, 132.333, 4.76871, 0, 0, 0.686916, -0.726736, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416512, 186286, 1, -3741.86, 1055.56, 132.377, 4.76871, 0, 0, 0.686916, -0.726736, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416513, 186286, 1, -3728.42, 1055.4, 132.54, 4.76871, 0, 0, 0.686916, -0.726736, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416514, 186286, 1, -3718.45, 1055.31, 132.422, 4.76871, 0, 0, 0.686916, -0.726736, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416515, 186286, 1, -3705.27, 1056.33, 132.749, 4.76871, 0, 0, 0.686916, -0.726736, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416516, 186286, 1, -3697.88, 1059.03, 132.239, 5.49912, 0, 0, 0.382066, -0.924135, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416517, 186286, 1, -3689.06, 1066.04, 132.792, 5.49912, 0, 0, 0.382066, -0.924135, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416518, 186286, 1, -3683.35, 1075.84, 131.969, 5.97429, 0, 0, 0.153836, -0.988096, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416519, 186286, 1, -3680.45, 1085.05, 132.126, 6.19027, 0, 0, 0.0464395, -0.998921, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416520, 186286, 1, -3680.11, 1093.11, 131.969, 0.205539, 0, 0, 0.102589, 0.994724, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416521, 186286, 1, -3680.71, 1101.87, 132.061, 0.221247, 0, 0, 0.110398, 0.993887, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416522, 186286, 1, -3682.71, 1110.09, 132.605, 0.468647, 0, 0, 0.232185, 0.972672, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416523, 186286, 1, -3688.06, 1118.23, 131.969, 0.912397, 0, 0, 0.440539, 0.897734, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416524, 186286, 1, -3693.13, 1123.67, 132.122, 0.861346, 0, 0, 0.417483, 0.908685, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416525, 186286, 1, -3699.62, 1128.35, 131.977, 1.49359, 0, 0, 0.679291, 0.733869, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416526, 186286, 1, -3712.55, 1130.87, 132.579, 1.46218, 0, 0, 0.66768, 0.744448, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416527, 186286, 1, -3721.94, 1130.89, 132.833, 1.51715, 0, 0, 0.687889, 0.725816, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416528, 186286, 1, -3731.47, 1130.9, 131.973, 1.72136, 0, 0, 0.758285, 0.651923, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416529, 186286, 1, -3744.11, 1130.96, 132.778, 1.72136, 0, 0, 0.758285, 0.651923, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416530, 186286, 1, -3780.81, 1131.68, 131.979, 1.87058, 0, 0, 0.804772, 0.593584, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416531, 186286, 1, -3790.42, 1131.68, 132.863, 1.85488, 0, 0, 0.800085, 0.599886, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416532, 186286, 1, -3802.38, 1129.62, 132.327, 2.1494, 0, 0, 0.879447, 0.475996, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416546, 210345, 1, -3728.43, 1080.73, 160.479, 3.34477, 0, 0, 0.994844, -0.101415, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416547, 210345, 1, -3758.22, 1076.85, 155.269, 3.47593, 0, 0, 0.98606, -0.166393, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416548, 210345, 1, -3770.29, 1095.16, 152.816, 2.58136, 0, 0, 0.961024, 0.276466, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416549, 210345, 1, -3765.69, 1114.02, 150.552, 1.33022, 0, 0, 0.617147, 0.786848, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416550, 210345, 1, -3797.94, 1097.81, 146.366, 3.50499, 0, 0, 0.983538, -0.180702, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416551, 210345, 1, -3712.11, 1102.95, 152.841, 0.0641625, 0, 0, 0.0320757, 0.999485, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416552, 210348, 1, -3733.9, 1112.59, 160.196, 3.19633, 0, 0, 0.999626, -0.0273648, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416553, 210348, 1, -3770.06, 1105.03, 164.869, 3.18455, 0, 0, 0.999769, -0.0214761, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416554, 210348, 1, -3786.37, 1077.4, 158.489, 4.24483, 0, 0, 0.851677, -0.524068, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416555, 210348, 1, -3816.56, 1094.4, 158.879, 2.30568, 0, 0, 0.913921, 0.405892, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416556, 210348, 1, -3696.8, 1070.51, 157.142, 0.188248, 0, 0, 0.0939853, 0.995574, 25, 100, 1, 0, 0);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416557, 210348, 1, -3698.01, 1110.75, 146.263, 5.35224, 0, 0, 0.448845, -0.893609, 25, 100, 1, 0, 0);


-- Gameobject Template
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100024, 5, 6451, 'Arena Crystal - Small', 0, 4, 1.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100023, 5, 6451, 'Arena Crystal - Medium', 0, 4, 2.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100021, 5, 6451, 'Arena Crystal - Large', 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100020, 5, 6333, 'SUN', 0, 0, 6, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100019, 5, 442, 'Torch', 0, 0, 4, 0, 0, 196608, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100018, 5, 2570, 'Flame Upwards Brazier', 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100017, 5, 6663, 'Banner of Provocation Medium', 0, 0, 2.5, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100016, 5, 288, 'Barrel Large', 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100015, 5, 442, 'Torch', 0, 0, 1.5, 0, 0, 196608, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100014, 5, 6663, 'Banner of Provocation - Large', 0, 0, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100013, 5, 475, 'Brazier Large', 0, 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100012, 5, 4714, 'Crystal Pillar with Beam', 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');

-- Creature template
REPLACE INTO `creature_template` (`entry`, `patch`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Civilian`, `RacialLeader`, `RegenHealth`, `equipment_id`, `trainer_id`, `vendor_id`, `MechanicImmuneMask`, `SchoolImmuneMask`, `flags_extra`, `aggroRadius`, `ScriptName`) VALUES (1200000, 0, 0, 0, 10539, 0, 0, 0, 'Nether Channeler', '', 0, 70, 70, 2284, 2284, 0, 0, 0, 35, 35, 3, 1.13, 1.14286, 2, 0, 0, 0, 0, 148, 0, 2000, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'custom_PortalTeleportNPC');
REPLACE INTO `creature_template` (`entry`, `patch`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Civilian`, `RacialLeader`, `RegenHealth`, `equipment_id`, `trainer_id`, `vendor_id`, `MechanicImmuneMask`, `SchoolImmuneMask`, `flags_extra`, `aggroRadius`, `ScriptName`) VALUES (1101200, 0, 0, 0, 7107, 0, 0, 0, 'Arena Ticket Master', '3v3 Arena - Today!', 0, 50, 50, 3517, 3517, 0, 0, 0, 35, 35, 3, 1.2, 1.14286, 1.5, 1, 123, 167, 0, 226, 1, 2000, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 66.44, 91.355, 100, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'custom_ArenaTeleportNPC');


-- Event 200
REPLACE INTO `game_event_creature` (`guid`, `event`)
VALUES
(2770180, 200),
(2770177, 200),
(2770178, 200),
(2770179, 200),
(2770189, 200),
(2770187, 200),
(2770188, 200),
(2770186, 200),
(2770184, 200),
(2770185, 200),
(2770181, 200),
(2770182, 200),
(2770183, 200),
(2770196, 200),
(2770195, 200),
(2770193, 200),
(2770194, 200),
(2770222, 200),
(2770220, 200),
(2770221, 200),
(2770192, 200),
(2770190, 200),
(2770191, 200),
(2770219, 200),
(2770209, 200),
(2770208, 200),
(2770207, 200),
(2770206, 200),
(2770218, 200),
(2770217, 200),
(2770216, 200),
(2770215, 200),
(2770214, 200),
(2770213, 200),
(2770212, 200),
(2770211, 200),
(2770210, 200),
(2770205, 200),
(2770204, 200),
(2770203, 200),
(2770202, 200),
(2770200, 200),
(2770201, 200),
(2770199, 200),
(2770198, 200),
(2770197, 200),
(2770066, 200),
(2770067, 200),
(2770165, 200),
(2770172, 200);

REPLACE INTO `game_event_gameobject` (`guid`, `event`)
VALUES
(4416490, 200),
(4370611, 200),
(4370592, 200),
(4370591, 200),
(4370579, 200),
(4370578, 200),
(4370577, 200),
(4370576, 200),
(4370575, 200),
(4370574, 200),
(4370573, 200),
(4370572, 200),
(4370571, 200),
(4370570, 200),
(4370569, 200),
(4370568, 200),
(4370567, 200),
(4370566, 200),
(4370565, 200),
(4370564, 200),
(4370563, 200),
(4370562, 200),
(4370561, 200),
(4370560, 200),
(4370559, 200),
(4370558, 200),
(4370557, 200),
(4370556, 200),
(4370555, 200),
(4370554, 200),
(4370553, 200),
(4370552, 200),
(4370551, 200),
(4370550, 200),
(4370549, 200),
(4370548, 200),
(4370547, 200),
(4370546, 200),
(4370545, 200),
(4370544, 200),
(4370543, 200),
(4370542, 200),
(4370541, 200),
(4370540, 200),
(4370539, 200),
(4370535, 200),
(4370534, 200),
(4370533, 200),
(4370532, 200),
(4370531, 200),
(4370528, 200),
(4370527, 200),
(4370526, 200),
(4370509, 200),
(4370511, 200),
(4370510, 200),
(4370505, 200),
(4370504, 200),
(4370503, 200),
(4370502, 200),
(4370501, 200),
(4370500, 200),
(4370514, 200),
(4370525, 200),
(4370513, 200),
(4370512, 200),
(4370516, 200),
(4370524, 200),
(4370515, 200),
(4370519, 200),
(4370518, 200),
(4370517, 200),
(4370521, 200),
(4370520, 200),
(4370522, 200),
(4370523, 200),
(4346696, 200),
(4370419, 200),
(4370538, 200),
(4370537, 200),
(4370536, 200),
(4346698, 200),
(4346697, 200),
(4346695, 200),
(4346694, 200),
(4346693, 200),
(4346691, 200),
(4346692, 200),
(4416013, 200),
(4416014, 200),
(4416015, 200),
(4416016, 200),
(4416017, 200),
(4416018, 200),
(4416019, 200),
(4416020, 200),
(4416021, 200),
(4416022, 200),
(4416023, 200),
(4416024, 200),
(4416025, 200),
(4416027, 200),
(4416028, 200),
(4416029, 200),
(4416032, 200),
(4416033, 200),
(4416034, 200),
(4416035, 200),
(4416036, 200),
(4416037, 200),
(4416038, 200),
(4416039, 200),
(4416040, 200),
(4416041, 200),
(4416042, 200),
(4416043, 200),
(4416045, 200),
(4416046, 200),
(4416048, 200),
(4416049, 200),
(4416051, 200),
(4416052, 200),
(4416053, 200),
(4416054, 200),
(4416055, 200),
(4416056, 200),
(4416057, 200),
(4416058, 200),
(4416059, 200),
(4416060, 200),
(4416061, 200),
(4416062, 200),
(4416063, 200),
(4416064, 200),
(4416065, 200),
(4416066, 200),
(4416067, 200),
(4416068, 200),
(4416069, 200),
(4416070, 200),
(4416071, 200),
(4416072, 200),
(4416073, 200),
(4416074, 200),
(4416075, 200),
(4416076, 200),
(4416077, 200),
(4416078, 200),
(4416079, 200),
(4416080, 200),
(4416081, 200),
(4416082, 200),
(4416083, 200),
(4416084, 200),
(4416085, 200),
(4416086, 200),
(4416087, 200),
(4416088, 200),
(4416089, 200),
(4416090, 200),
(4416091, 200),
(4416092, 200),
(4416093, 200),
(4416094, 200),
(4416095, 200),
(4416096, 200),
(4416097, 200),
(4416098, 200),
(4416099, 200),
(4416100, 200),
(4416101, 200),
(4416102, 200),
(4416103, 200),
(4416104, 200),
(4416105, 200),
(4416106, 200),
(4416107, 200),
(4416108, 200),
(4416109, 200),
(4416110, 200),
(4416111, 200),
(4416112, 200),
(4416113, 200),
(4416114, 200),
(4416115, 200),
(4416116, 200),
(4416117, 200),
(4416118, 200),
(4416119, 200),
(4416120, 200),
(4416121, 200),
(4416122, 200),
(4416123, 200),
(4416124, 200),
(4416125, 200),
(4416126, 200),
(4416127, 200),
(4416128, 200),
(4416129, 200),
(4416130, 200),
(4416131, 200),
(4416132, 200),
(4416133, 200),
(4416134, 200),
(4416135, 200),
(4416136, 200),
(4416137, 200),
(4416138, 200),
(4416139, 200),
(4416140, 200),
(4416141, 200),
(4416142, 200),
(4416143, 200),
(4416144, 200),
(4416145, 200),
(4416146, 200),
(4416147, 200),
(4416148, 200),
(4416149, 200),
(4416150, 200),
(4416151, 200),
(4416152, 200),
(4416153, 200),
(4416154, 200),
(4416155, 200),
(4416156, 200),
(4416157, 200),
(4416158, 200),
(4416159, 200),
(4416160, 200),
(4416161, 200),
(4416162, 200),
(4416163, 200),
(4416164, 200),
(4416165, 200),
(4416166, 200),
(4416168, 200),
(4416169, 200),
(4416170, 200),
(4416171, 200),
(4416172, 200),
(4416173, 200),
(4416186, 200),
(4416187, 200),
(4416192, 200),
(4416193, 200),
(4416194, 200),
(4416195, 200),
(4416196, 200),
(4416197, 200),
(4416208, 200),
(4416209, 200),
(4416210, 200),
(4416216, 200),
(4416217, 200),
(4416218, 200),
(4416219, 200),
(4416220, 200),
(4416221, 200),
(4416222, 200),
(4416223, 200),
(4416238, 200),
(4416239, 200),
(4416240, 200),
(4416241, 200),
(4416242, 200),
(4416243, 200),
(4416246, 200),
(4416247, 200),
(4416248, 200),
(4416249, 200),
(4416250, 200),
(4416253, 200),
(4416255, 200),
(4416256, 200),
(4416257, 200),
(4416258, 200),
(4416259, 200),
(4416260, 200),
(4416261, 200),
(4416262, 200),
(4416263, 200),
(4416265, 200),
(4416268, 200),
(4416269, 200),
(4416270, 200),
(4416271, 200),
(4416272, 200),
(4416273, 200),
(4416274, 200),
(4416275, 200),
(4416276, 200),
(4416277, 200),
(4416278, 200),
(4416279, 200),
(4416280, 200),
(4416281, 200),
(4416282, 200),
(4416301, 200),
(4416302, 200),
(4416303, 200),
(4416304, 200),
(4416305, 200),
(4416306, 200),
(4416307, 200),
(4416308, 200),
(4416309, 200),
(4416310, 200),
(4416311, 200),
(4416312, 200),
(4416313, 200),
(4416314, 200),
(4416315, 200),
(4416316, 200),
(4416317, 200),
(4416318, 200),
(4416319, 200),
(4416321, 200),
(4416322, 200),
(4416323, 200),
(4416324, 200),
(4416325, 200),
(4416326, 200),
(4416327, 200),
(4416328, 200),
(4416329, 200),
(4416346, 200),
(4416347, 200),
(4416348, 200),
(4416350, 200),
(4416351, 200),
(4416352, 200),
(4416438, 200);

-- Event 201 (FIRE)
REPLACE INTO `game_event_gameobject` (`guid`, `event`)
VALUES
(4416378, 201),
(4416379, 201),
(4416380, 201),
(4416381, 201),
(4416382, 201),
(4416383, 201),
(4416384, 201),
(4416385, 201),
(4416386, 201),
(4416387, 201),
(4416388, 201),
(4416389, 201),
(4416390, 201),
(4416391, 201),
(4416392, 201),
(4416393, 201),
(4416394, 201),
(4416395, 201),
(4416396, 201),
(4416397, 201),
(4416398, 201),
(4416399, 201),
(4416400, 201),
(4416401, 201),
(4416402, 201),
(4416403, 201),
(4416404, 201),
(4416405, 201),
(4416406, 201),
(4416407, 201),
(4416408, 201),
(4416409, 201),
(4416410, 201),
(4416411, 201),
(4416412, 201),
(4416413, 201),
(4416414, 201),
(4416415, 201),
(4416416, 201),
(4416417, 201),
(4416418, 201),
(4416501, 201),
(4416502, 201),
(4416503, 201),
(4416504, 201),
(4416505, 201),
(4416506, 201),
(4416507, 201),
(4416508, 201),
(4416509, 201),
(4416510, 201),
(4416511, 201),
(4416512, 201),
(4416513, 201),
(4416514, 201),
(4416515, 201),
(4416516, 201),
(4416517, 201),
(4416518, 201),
(4416519, 201),
(4416520, 201),
(4416521, 201),
(4416522, 201),
(4416523, 201),
(4416524, 201),
(4416525, 201),
(4416526, 201),
(4416527, 201),
(4416528, 201),
(4416529, 201),
(4416530, 201),
(4416531, 201),
(4416532, 201);



-- Event 202 (Crystals)
REPLACE INTO `game_event_gameobject` (`guid`, `event`)
VALUES
(4416438, 202),
(4416460, 202),
(4416466, 202),
(4416467, 202),
(4416468, 202),
(4416469, 202),
(4416470, 202),
(4416471, 202),
(4416472, 202),
(4416473, 202),
(4416474, 202),
(4416475, 202),
(4416546, 202),
(4416547, 202),
(4416548, 202),
(4416549, 202),
(4416550, 202),
(4416551, 202),
(4416552, 202),
(4416553, 202),
(4416554, 202),
(4416555, 202),
(4416556, 202),
(4416557, 202);


-- Event 203 (
REPLACE INTO `game_event_gameobject` (`guid`, `event`)
VALUES
(4416478, 203),
(4416479, 203), 
(4416480, 203),
(4416481, 203),
(4416485, 203),
(4416486, 203),
(4416488, 203),
(4416487, 203);

-- Event 203 (
REPLACE INTO `game_event_creature` (`guid`, `event`)
VALUES
(2770062, 203),
(2770063, 203),
(2770064, 203),
(2770065, 203);


-- Event 204
REPLACE INTO `game_event_gameobject` (`guid`, `event`)
VALUES
(4416331, 204),
(4416332, 204),
(4416333, 204),
(4416334, 204);


-- Event 204 Start Fight Spawn/Despawn GO objects
REPLACE INTO `game_event_gameobject` (`guid`, `event`)
VALUES 
(4416331, 204), 
(4416332, 204),
(4416333, 204),
(4416334, 204);
Replace INTO `game_event_creature` (`guid`, `event`)
VALUES
(2769762, 204);

REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2769762, 15918, 1, 0, 0, -3756.65, 1092.94, 131.969, 4.71896, 25, 5, 0, 4120, 0, 0, 0, 0, 0, 0, 10);


-- Scripts
DELETE FROM `script_texts` WHERE `entry`=-1999603;
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES (-1999603, 'sss ... you cannot enter again so soon mortal .... ', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, NULL);




-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
