DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180901122340');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180901122340');
-- Add your query below.

-- Whatever happened to Rag's loot it's weird. 

DELETE FROM `creature_loot_template` WHERE `entry` = 11502;
INSERT INTO `creature_loot_template` VALUES 
(11502,7078,40,0,1,9,0),
(11502,17204,3,0,1,1,72),
(11502,19017,-100,0,1,1,0),
(11502,21110,100,0,1,1,9),
(11502,324923,100,2,-324923,1,0),
(11502,324925,100,4,-324925,1,0),
(11502,330000,100,7,-330000,2,0),
(11502,330001,100,8,-330001,1,0),
(11502,330096,100,9,-330096,2,0),
(11502,936302,100,10,-936302,1,0),
(11502,936303,100,11,-936303,1,0);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
