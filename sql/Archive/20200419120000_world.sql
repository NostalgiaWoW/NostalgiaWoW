DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200419120000');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200419120000');

REPLACE INTO `command` (`name`, `security`, `help`) VALUES ('scan multibox', '3', 'Syntax: .scan multibox');

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
