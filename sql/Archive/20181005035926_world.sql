DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181005035926');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181005035926');
-- Add your query below.

/* Give Twin Emperors correct health */
UPDATE creature_template SET maxhealth = 2165150 WHERE entry = 15275;
UPDATE creature_template SET maxhealth = 1732250 WHERE entry = 15276;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
