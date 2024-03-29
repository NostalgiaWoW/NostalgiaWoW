DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200517172328');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200517172328');
-- Add your query below.

-- Auberdine guard correction
DELETE FROM `creature` WHERE `guid` = 38980; 

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
