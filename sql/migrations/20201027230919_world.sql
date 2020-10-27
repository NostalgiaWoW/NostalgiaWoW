DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201027230919');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201027230919');
-- Add your query below.

REPLACE INTO `item_template` (entry, class, subclass, displayid, name, quality, bonding, inventorytype, stackable) values (80000, 15, 0, 32277, 'PvP Token', 2, 1, 0, 200);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
