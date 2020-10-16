DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='##MIGRATION_NAME##');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('##MIGRATION_NAME##');

-- ##MIGRATION_NAME##

-- Add your query below.

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
