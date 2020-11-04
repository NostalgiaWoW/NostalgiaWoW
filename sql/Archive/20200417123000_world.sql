DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200417123000');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200417123000');

REPLACE INTO `mangos_string` (`entry`, `content_default`, `content_loc8`) VALUES 
('1801', '|cFFFF1100 Player "%s" has been permanently banned for: %s.|r', '|cFFFF1100 Игрок "%s" получил перманентный бан. Причина: %s.|r');

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
