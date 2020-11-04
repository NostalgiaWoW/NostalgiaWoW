DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180927032831');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180927032831');
-- Add your query below.

UPDATE `item_template` SET `RandomProperty`='878' WHERE (`entry`='6565') AND (`patch`='0');
-- Correct properties for Shimmering Gloves (users have to clear cache, stop fixing this item, it's ok!)
UPDATE `item_template` SET `stat_type1`='0', `stat_value1`='0', `stat_type2`='0', `stat_value2`='0' WHERE (`entry`='6565') AND (`patch`='0');
UPDATE `item_template` SET `RandomProperty`='878' WHERE (`entry`='6565') AND (`patch`='0');

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
