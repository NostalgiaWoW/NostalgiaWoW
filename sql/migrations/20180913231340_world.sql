DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180913231340');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180913231340');
-- Add your query below.

-- Temp mobs and should not have any loot. General Rajaxx encounter.
DELETE from creature_loot_template where entry IN (15389, 15391, 15385, 15388, 15386, 15390, 15392);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
