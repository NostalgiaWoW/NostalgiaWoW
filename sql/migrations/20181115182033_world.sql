DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181115182033');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181115182033');
-- Add your query below.

-- Re-add trigger flag to trigger

UPDATE `creature_template` SET flags_extra = 130 WHERE entry IN (11500, 14030, 14026, 14027, 14028, 14029, 14031);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;