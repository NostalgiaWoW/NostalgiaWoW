DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181105104218');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181105104218');
-- Add your query below.

ALTER TABLE `log_store_gold`
  ADD COLUMN `goldBefore` INT(11) DEFAULT 0  NOT NULL AFTER `gold`,
  ADD COLUMN `goldAfter` INT(11) DEFAULT 0  NOT NULL AFTER `goldBefore`;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
