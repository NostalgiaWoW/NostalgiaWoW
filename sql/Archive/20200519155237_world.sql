DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200519155237');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200519155237');
-- Add your query below.

-- Mistake in patches. Max patch is 10.
UPDATE `item_template`
SET `patch` = 10
WHERE `patch` = 12;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
