DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181105190456');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181105190456');
-- Add your query below.

-- Remove XP Gain from killing some Argent Dawn NPCs
UPDATE creature_template SET flags_extra = flags_extra | 0x40 WHERE `subname` LIKE '%The Argent Dawn%' AND `maxdmg` < 100 AND `maxhealth` < 1200;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
