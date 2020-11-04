DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200421172524');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200421172524');
-- Add your query below.

UPDATE `quest_template` SET `MinLevel` = 40 WHERE `entry` IN (2847, 2848, 2849, 2850, 2851, 2852, 2853);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
