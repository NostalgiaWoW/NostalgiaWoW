DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181203143720');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181203143720');
-- Add your query below.

-- Correct position for Wastewander Bandit
UPDATE `creature` SET `position_x`=-7274.721, `position_y`=-4543.12, `position_z`=8.89 WHERE `guid`=23555;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
