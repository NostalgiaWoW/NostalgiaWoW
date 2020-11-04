DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181014233648');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181014233648');
-- Add your query below.

-- Shimmering Gloves should never drop from objects.
DELETE FROM `gameobject_loot_template` WHERE `item`='6565';

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
