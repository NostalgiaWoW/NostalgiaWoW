DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181126011628');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181126011628');
-- Add your query below.

-- Fix mob positioning. Issue # 971 - https://github.com/elysium-project/classic-bug-tracker/issues/971

DELETE FROM `creature` WHERE `guid`=45028;
INSERT INTO `creature` VALUES (45028, 1530, 0, 4631, 0, 3059.57, 658.2, 75.35, 4.85, 300, 0, 0, 204, 0, 0, 0, 0, 0, 0, 10);
DELETE FROM `creature` WHERE `guid`=45041;
INSERT INTO `creature` VALUES (45041, 1534, 0, 10752, 0, 3061.36, 652.86, 75.35, 2.24, 300, 0, 0, 179, 0, 0, 0, 0, 0, 0, 10);



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
