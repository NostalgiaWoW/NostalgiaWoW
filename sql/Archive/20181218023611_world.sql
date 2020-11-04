DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181218023611');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181218023611');

INSERT INTO spell_script_target (entry, type, targetEntry) VALUES(17652, 3, 11263);

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
