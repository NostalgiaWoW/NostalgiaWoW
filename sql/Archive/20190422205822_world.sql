DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190422205822');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190422205822');

-- fix_quest_8995

-- Add your query below.
DELETE FROM `creature_loot_template` WHERE `entry` = 16042 AND item = 22048;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `groupid`, `mincountOrRef`, `maxcount`, `condition_id`) VALUES ('16042', '22048', '-100', '0', '1', '1', '0');
-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
