DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181008192504');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181008192504');
-- Add your query below.

-- Add roof guard to Redridge
DELETE FROM `creature` WHERE `guid`=2625470;
INSERT INTO `creature` VALUES (2625470, 933, 0, 0, 653, -9244.2, -2160.44, 82.7603, 3.16391, 25, 5, 0, 2016, 0, 0, 0, 0, 0, 0, 10);


-- Add Kneeling emote to creature
DELETE FROM `creature_addon` WHERE `guid`=2625470;
INSERT INTO `creature_addon` VALUES (2625470, 0, 0, 8, 0, 16, 0, 0, NULL);



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
