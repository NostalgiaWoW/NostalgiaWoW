DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190804083000');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190804083000');

UPDATE `creature` SET `patch_max`='10' WHERE `id`='1000553';
REPLACE INTO `game_event` (`entry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `hardcoded`, `disabled`, `patch_min`, `patch_max`) VALUES 
('171', '0000-00-00 00:00:00', '0000-00-00 00:00:00', '1', '999999999', '0', 'Ragtheradon the Invader', '0', '0', '0', '10');

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
