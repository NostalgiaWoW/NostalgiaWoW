DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180909123417');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180909123417');
-- Add your query below.

DELETE FROM `creature_template` WHERE `entry` = 56006;
INSERT INTO `creature_template` VALUES (56006, 0, 0, 0, 6956, 0, 0, 0, 'Insane Southsea Freeboster', NULL, 0, 1, 1, 5000, 5000, 0, 0, 7, 35, 35, 0, 1, 1.14286, 0.4, 0, 2, 2, 0, 44, 1, 2000, 2000, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 'npc_anticrash');

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
