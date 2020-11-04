DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181118143152');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181118143152');
-- Add your query below.

-- Fix duration on XP tokens
UPDATE `item_template` SET `ExtraFlags`='2', Duration='86400' WHERE `entry`='55568';
UPDATE `item_template` SET `ExtraFlags`='2', Duration='604800' WHERE `entry`='55569';

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
