DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181019200038');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181019200038');
-- Add your query below.

-- Metzen spawn timer update
UPDATE `creature` SET `spawntimesecs`=180 WHERE `guid` IN (89440, 89432);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
