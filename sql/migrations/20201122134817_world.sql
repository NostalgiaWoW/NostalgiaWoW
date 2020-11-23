DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201122134817');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201122134817');
-- Add your query below.
ALTER TABLE `pvp_arena_system`
	ADD COLUMN `GateEntry` INT NOT NULL AFTER `StartPos_2_y`,
	ADD COLUMN `GateGuid_1` INT NOT NULL AFTER `GateEntry`,
	ADD COLUMN `GateGuid_2` INT NOT NULL AFTER `GateGuid_1`;



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
