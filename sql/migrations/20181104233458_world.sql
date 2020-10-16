DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181104233458');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181104233458');
-- Add your query below.

DELETE FROM `creature_linking_template` WHERE `entry` = 11373;
INSERT INTO `creature_linking_template` VALUE
(11373, 309, 14507, 0x1|0x80|0x400|0x2000, 300);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
