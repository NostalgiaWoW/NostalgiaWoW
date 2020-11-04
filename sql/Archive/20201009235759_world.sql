DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201009235759');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201009235759');
-- Add your query below.

UPDATE quest_template
SET `RewItemCount1` = 1
WHERE `entry` = 30001;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
