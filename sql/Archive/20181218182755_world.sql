DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181218182755');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181218182755');

DELETE FROM spell_disabled WHERE entry = 24417;
DELETE FROM spell_disabled WHERE entry = 30003;

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
