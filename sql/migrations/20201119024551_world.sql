DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201119024551');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201119024551');
-- Add your query below.

update creature_template set minhealth = 62042, maxhealth = 62042 where entry = 10184;
update creature_template set minhealth = 18168, maxhealth = 18168 where entry = 12129;
update map_template set maxplayers = 5 where entry = 249;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
