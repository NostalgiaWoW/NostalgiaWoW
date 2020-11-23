DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201116010036');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201116010036');
-- Add your query below.

-- Add Playground Token to quest requirements for T3
UPDATE quest_template
SET ReqItemId3 = 80002, ObjectiveText3 = "Collect 1 Playground Token", ReqItemCount3 = 1, Objectives = "Destroy your foes across Azeroth and through arenas. Return to the battle hardened orc with 250 Arena Tokens, 500 PVP tokens and 1 Playground Token."
WHERE entry BETWEEN 30064 AND 30081;


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
