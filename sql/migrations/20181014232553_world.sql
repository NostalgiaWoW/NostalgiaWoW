DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181014232553');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181014232553');
-- Add your query below.

-- Return back Shimmering Gloves
DELETE FROM `gameobject_loot_template` WHERE `item`='6565';
INSERT INTO `gameobject_loot_template` VALUES (4077, 6565, 0, 1, 1, 1, 0);
INSERT INTO `gameobject_loot_template` VALUES (4076, 6565, 0, 1, 1, 1, 0);
INSERT INTO `gameobject_loot_template` VALUES (4075, 6565, 0, 1, 1, 1, 0);
INSERT INTO `gameobject_loot_template` VALUES (4074, 6565, 0, 1, 1, 1, 0);
INSERT INTO `gameobject_loot_template` VALUES (2283, 6565, 0, 1, 1, 1, 0);
INSERT INTO `gameobject_loot_template` VALUES (2282, 6565, 0, 1, 1, 1, 0);
INSERT INTO `gameobject_loot_template` VALUES (2281, 6565, 0, 1, 1, 1, 0);
INSERT INTO `gameobject_loot_template` VALUES (2280, 6565, 0, 1, 1, 1, 0);
INSERT INTO `gameobject_loot_template` VALUES (2279, 6565, 0, 1, 1, 1, 0);
INSERT INTO `gameobject_loot_template` VALUES (9934, 6565, 0.150802, 0, 1, 1, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
