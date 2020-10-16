DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181018232520');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181018232520');
-- Add your query below.

/*Quest 4450 Issue*/
UPDATE `gameobject` SET `spawntimesecs`= 120 WHERE `guid`= 47578;
UPDATE `gameobject_template` SET `flags`= 0 WHERE `entry`= 173266;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
