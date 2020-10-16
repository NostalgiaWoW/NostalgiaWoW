DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190221161406');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190221161406');
-- Add your query below.

-- Quest zone fixes for PVP quests
UPDATE `quest_template` SET `ZoneOrSort` = 1637 WHERE `entry` = 8367;
UPDATE `quest_template` SET `ZoneOrSort` = 1519 WHERE `entry` = 8385;
UPDATE `quest_template` SET `ZoneOrSort` = 1637 WHERE `entry` = 8371;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
