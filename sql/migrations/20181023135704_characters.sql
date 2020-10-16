DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181023135704');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181023135704');
-- Add your query below.

ALTER TABLE `store_gold` MODIFY `gold` int(11);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
