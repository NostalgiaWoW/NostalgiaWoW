DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201106184006');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201106184006');
-- Add your query below.
ALTER TABLE `pvp_arena_system`
	ADD COLUMN `StartPos_1_x` FLOAT NOT NULL AFTER `MapId`,
	ADD COLUMN `StartPos_1_y` FLOAT NOT NULL AFTER `StartPos_1_x`,
	ADD COLUMN `StartPos_2_x` FLOAT NOT NULL AFTER `StartPos_1_y`,
	ADD COLUMN `StartPos_2_y` FLOAT NOT NULL AFTER `StartPos_2_x`;


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
