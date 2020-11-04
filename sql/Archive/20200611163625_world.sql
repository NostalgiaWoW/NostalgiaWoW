DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200611163625');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200611163625');
-- Add your query below.
-- Sneaky fish made their way into the general STV Loot table.
DELETE FROM `fishing_loot_template` WHERE `entry`=33 AND `item`=19807;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
