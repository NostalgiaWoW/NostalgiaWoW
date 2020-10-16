DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180929204924');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180929204924');
-- Add your query below.

/*Battle Shout Issue*/
INSERT IGNORE INTO `spell_threat` (`entry`, `Threat`, `multiplier`, `ap_bonus`) VALUES
(27578, 56, 1, 0);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;