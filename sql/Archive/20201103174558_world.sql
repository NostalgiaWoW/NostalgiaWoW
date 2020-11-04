DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201103174558');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201103174558');
-- Add your query below.

-- Update all Tier Vendors
UPDATE `creature_template`
SET `trainer_class` = 0
WHERE entry BETWEEN 1200009 AND 1200041;



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
