DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200520001104');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200520001104');
-- Add your query below.


-- Fix Idol of Brutality appearance is loot tables. Should only be in NPC Magistrate Barthilas 10435
DELETE FROM creature_loot_template WHERE item = 23198;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
