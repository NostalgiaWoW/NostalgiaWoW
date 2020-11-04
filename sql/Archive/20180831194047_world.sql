DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180831194047');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180831194047');
-- Add your query below.

UPDATE `forbidden_items` SET `AfterOrBefore` = 1, `patch` = 6 WHERE `entry` IN ( 20725, 21023, 21024, 21072, 21217);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
