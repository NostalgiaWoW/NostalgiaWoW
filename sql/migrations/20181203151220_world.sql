DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181203151220');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181203151220');
-- Add your query below.

-- Fix a bug where Ornate Spy Glass would disappear on relog
UPDATE `item_template` SET `BagFamily`=0, `Map`=0 WHERE `entry`=5507;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
