DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181023134120');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181023134120');
-- Add your query below.

ALTER TABLE `groups` ADD COLUMN `masterLooterGuid` INT(10) UNSIGNED NOT NULL AFTER `isRaid`;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
