DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181127224540');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181127224540');
-- Add your query below.

-- Wording added for GM WARN
DELETE FROM `mangos_string` WHERE `entry`=283;
INSERT INTO `mangos_string` VALUES (283, 'You have been warned for: %s . A warning has been permanently placed on your account and future violations of Elysium ToU may lead to account suspensions.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
