DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181126010247');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181126010247');
-- Add your query below.

-- Set proper factions for Libram and Totem drops in Naxx. Issue # 977 https://github.com/elysium-project/classic-bug-tracker/issues/977
UPDATE `reference_loot_template` 
SET condition_id = 2
WHERE `item`=23005;

UPDATE `reference_loot_template` 
SET condition_id = 3
WHERE `item`=23006;
-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
