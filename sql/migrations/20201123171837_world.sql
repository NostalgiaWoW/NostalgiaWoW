DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201123171837');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201123171837');
-- Add your query below.
-- Arena Locations
DELETE FROM `pvp_arena_system` WHERE `Id`=1;
INSERT INTO `pvp_arena_system` (`Id`, `Type`, `Radius`, `Position_x`, `Position_y`, `MapId`, `StartPos_1_x`, `StartPos_1_y`, `StartPos_2_x`, `StartPos_2_y`) VALUES (1, 1, 30, -1930.67, -4131.62, 0, -1957.31, -4105.89, -1920.1, -4144.49);
DELETE FROM `pvp_arena_system` WHERE `Id`=2;
INSERT INTO `pvp_arena_system` (`Id`, `Type`, `Radius`, `Position_x`, `Position_y`, `MapId`, `StartPos_1_x`, `StartPos_1_y`, `StartPos_2_x`, `StartPos_2_y`) VALUES (2, 2, 30, -1722.74, -4227.54, 0, -1703.88, -4272.63, -1749.32, -4190.95);
DELETE FROM `pvp_arena_system` WHERE `Id`=3;
INSERT INTO `pvp_arena_system` (`Id`, `Type`, `Radius`, `Position_x`, `Position_y`, `MapId`, `StartPos_1_x`, `StartPos_1_y`, `StartPos_2_x`, `StartPos_2_y`) VALUES (3, 3, 30, -1722.74, -4227.54, 0, -1703.88, -4272.63, -1749.32, -4190.95);

-- Various npcs and emotes/equipment on Mall
DELETE FROM `creature` WHERE `guid`=3042394;
INSERT INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (3042394, 12998, 0, 0, 106005, -1773.93, -4116.04, 14.3207, 0.348727, 25, 5, 0, 644, 0, 0, 0, 0, 0, 0, 10);
DELETE FROM `creature` WHERE `guid`=3042394;
INSERT INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (3042394, 12998, 0, 0, 106005, -1773.93, -4116.04, 14.3207, 0.348727, 25, 5, 0, 644, 0, 0, 0, 0, 0, 0, 10);

DELETE FROM `creature_equip_template` WHERE `entry`=106005 AND `patch`=0;
INSERT INTO `creature_equip_template` (`entry`, `patch`, `equipentry1`, `equipentry2`, `equipentry3`) VALUES (106005, 0, 19014, 0, 0);

DELETE FROM `creature_addon` WHERE `guid`=3042394 AND `patch`=0;
INSERT INTO `creature_addon` (`guid`, `patch`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_flags`, `emote`, `moveflags`, `auras`) VALUES (3042394, 0, 0, 0, 0, 0, 234, 0, NULL);
DELETE FROM `creature_addon` WHERE `guid`=3049373 AND `patch`=0;
INSERT INTO `creature_addon` (`guid`, `patch`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_flags`, `emote`, `moveflags`, `auras`) VALUES (3049373, 0, 0, 0, 0, 0, 173, 0, NULL);


-- New gameobjects for mall
DELETE FROM `gameobject_template` WHERE `entry`=3100035;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100035, 5, 249, 'Stone Pillar small', 0, 0, 0.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
DELETE FROM `gameobject_template` WHERE `entry`=3100036;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100036, 5, 249, 'Stone Pillar medium', 0, 0, 1.2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
DELETE FROM `gameobject_template` WHERE `entry`=3100037;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100037, 5, 249, 'Stone Pillar large', 0, 0, 1.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
DELETE FROM `gameobject_template` WHERE `entry`=3100038;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `faction`, `flags`, `size`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (3100038, 5, 249, 'Stone Pillar x large', 0, 0, 1.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;