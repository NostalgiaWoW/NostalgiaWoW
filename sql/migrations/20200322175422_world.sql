DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200322175422');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200322175422');
-- Add your query below.
DELETE FROM `mangos_string` WHERE entry = 80000;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES ('80000', 'Your XP rate now is: x%s', '', '', '', '', '', '', '', 'Ваша скорость получения опыта сейчас: x%s');
-- 

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
