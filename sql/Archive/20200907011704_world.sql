DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200907011704');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200907011704');
-- Add your query below.

UPDATE `item_template`
SET `spellcooldown_1` = 300000
WHERE `entry` = 18864;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
