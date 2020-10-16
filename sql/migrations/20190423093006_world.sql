DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190423093006');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190423093006');

-- 

-- Add your query below.
UPDATE `item_template` SET `spellcharges_1` = '-5' WHERE `item_template`.`entry` = 5880 AND `item_template`.`patch` = 0;
-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
