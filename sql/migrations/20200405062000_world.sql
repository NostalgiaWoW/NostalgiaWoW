DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200405062000');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200405062000');

REPLACE INTO `creature_template_addon` (`entry`, `bytes1`) VALUES 
('1100004', '3'),
('1100003', '3');

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
