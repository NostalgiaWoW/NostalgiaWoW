DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201105000647');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201105000647');
-- Add your query below.

update creature_template set minhealth = minhealth*0.50, maxhealth = maxhealth*0.50, mindmg = mindmg*0.8, maxdmg = maxdmg*0.8 where rank > 0 and entry in (select id from creature where map = 30);
update battleground_template set MinPlayersPerTeam = 5 and MaxPlayersPerTeam = 20 where id = 1;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
