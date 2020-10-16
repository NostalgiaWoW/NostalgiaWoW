DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181106013511');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181106013511');
-- Add your query below.
-- 1.11 Scourge bosses spawntimer fixed.

update creature set spawntimesecs = 604800
where id IN (14684, 14695, 14690, 14693, 14682, 14686);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
