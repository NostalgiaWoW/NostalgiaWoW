DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181018232530');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181018232530');
-- Add your query below.

/*Server Restart Additional things*/
UPDATE `command` SET `help`= 'Command used to restart realm. Syntax: .server restart "REASON" &TimeInSeconds.' WHERE `name`= 'server restart';

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
