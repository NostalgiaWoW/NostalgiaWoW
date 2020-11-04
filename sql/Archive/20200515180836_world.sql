DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200515180836');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200515180836');
-- Add your query below.

-- Extra sign that shouldn't be here.
DELETE from `gameobject` WHERE `guid` = 42936;
DELETE FROM `gameobject_template` WHERE `entry` = 23301;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
