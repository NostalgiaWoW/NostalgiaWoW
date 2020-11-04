DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181022155505');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181022155505');
-- Add your query below.

/*Quest Issue*/
UPDATE `creature_template` SET `ScriptName`= 'npc_servant_of_doomlord', `AIName`= '' WHERE `entry` IN (7668, 7670, 7671, 7669);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
