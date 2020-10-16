DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190310192009');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190310192009');
-- Add your query below.

-- Shop unicorn level fix
update item_template set itemlevel = 60 and requiredlevel = 1 where entry = 55571;


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
