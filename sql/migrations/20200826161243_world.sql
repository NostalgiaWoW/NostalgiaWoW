DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200826161243');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200826161243');
-- Add your query below.

-- Sprinter's Sword item 18410 speed spell is incorrect. This one is also not correct but looks like a dbc needs to be fixed? Unsure. Temp fix.
UPDATE item_template
SET spellid_1 = 14530
WHERE entry = 18410;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
