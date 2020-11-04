DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180912200832');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180912200832');
-- Add your query below.

-- Removed spell from all trainers. Should not be obtainable. 
DELETE FROM `npc_trainer` WHERE `spell`=12124;

-- Added PATTERN learning to proper NPC trainers.
INSERT INTO 
	`npc_trainer` 
	(`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) 
	VALUES 
	(1797, 212173, 20000, 197, 235, 0),
	(7481, 212173, 20000, 197, 235, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
