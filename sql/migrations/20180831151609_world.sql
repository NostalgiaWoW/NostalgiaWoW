DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180831151609');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180831151609');
-- Add your query below.

UPDATE `mangos_string` SET `content_default`='Group type: %s (ID: %s) Leader: %s (account %s) Player count: %d Players: %s' WHERE `entry`='640';

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
