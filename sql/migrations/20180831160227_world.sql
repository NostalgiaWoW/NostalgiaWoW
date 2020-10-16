DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180831160227');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180831160227');
-- Add your query below.

DELETE FROM `map_template` WHERE (`Entry`='169');

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
