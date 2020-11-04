DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181020013252');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181020013252');
-- Add your query below.
-- Set incremental sale time to 2 hours for "Shimmering Gloves" on NPC
update npc_vendor
set incrtime = 7200
where item = 6565;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
