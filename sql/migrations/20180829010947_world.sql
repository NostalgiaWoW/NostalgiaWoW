DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180829010947');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180829010947');
-- Add your query below.

DELETE FROM `spell_mod` WHERE `id` = 26656;
INSERT INTO `spell_mod` (`Id`, `CastingTimeIndex`) VALUES ('26656', '1');

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
