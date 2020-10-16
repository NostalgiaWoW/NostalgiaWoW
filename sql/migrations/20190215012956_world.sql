DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190215012956');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190215012956');
-- Add your query below.

DELETE FROM `game_event` WHERE `entry`=8;
INSERT INTO `game_event` VALUES (8, '2019-02-10 02:00:00', '2019-02-27 02:00:00', 525600, 7200, 0, 'Love is in the Air', 0, 0, 7, 10);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
