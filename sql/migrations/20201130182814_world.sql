DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201130182814');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201130182814');
-- Add your query below.

-- Update Mule scale
UPDATE `creature_template`
SET `scale` = .65
WHERE `entry` IN (60001, 16225, 16232);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
