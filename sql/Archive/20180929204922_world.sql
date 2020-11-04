DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180929204922');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180929204922');
-- Add your query below.

-- Update NPC faction flags back to normal.
REPLACE INTO 
	`creature_template` 
	VALUES 
	(3191, 0, 0, 0, 3751, 0, 0, 0, 'Cook Torka', NULL, 0, 6, 6, 196, 196, 0, 0, 20, 85, 85, 2, 0.92, 1.14286, 0, 0, 6, 8, 0, 54, 1, 2000, 2145, 1, 4608, 0, 0, 0, 0, 0, 0, 10.296, 14.157, 100, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'EventAI', 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, '');


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
