DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181016005239');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181016005239');
-- Add your query below.

-- Additional decoration to the Hallow's End event.
DELETE FROM `gameobject_template` WHERE `entry`=987758;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (987758, 5, 6398, 'G_Pumpkin_02_Large', 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');

DELETE FROM `game_event_gameobject` WHERE `guid`=4100438 AND `event`=12;
INSERT INTO `game_event_gameobject` (`guid`, `event`) VALUES (4100438, 12);
DELETE FROM `game_event_gameobject` WHERE `guid`=4100858 AND `event`=12;
INSERT INTO `game_event_gameobject` (`guid`, `event`) VALUES (4100858, 12);

DELETE FROM `gameobject` WHERE `guid`=4100438;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4100438, 987758, 0, -9122.15, 339.868, 94.0406, 2.44202, 0, 0, 0.919111, -0.393999, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4100858;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4100858, 987758, 1, 1490.89, -4397.21, 25.108, 6.14177, 0, 0, 0.562389, 0.826873, 25, 100, 1, 0, 0);

-- Readded Shimmering Gloves to NPC now that they are fixed.
DELETE FROM `npc_vendor` WHERE `entry`=3572 AND `item`=6565;
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `conditionId`) VALUES (3572, 6565, 0, 0, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
