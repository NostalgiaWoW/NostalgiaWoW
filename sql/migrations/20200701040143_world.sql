DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200701040143');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200701040143');
-- Add your query below.

-- Nighthaven specific fireworks. Not blizzlike locations or timers. Worldwide.
UPDATE game_event
SET description = "Midsummer - EEE"
WHERE `entry` = 170;


-- Accurate level requirements for EEE vendor
UPDATE item_template 
SET `RequiredLevel` = 10
WHERE entry IN (8626, 8625, 8624);

UPDATE item_template 
SET `RequiredLevel` = 20
WHERE entry IN (9312, 9313, 9318, 5740, 9314, 9317, 9315);

-- Vendors added to event
REPLACE INTO `game_event_creature` (`guid`, `event`)
VALUES
(4, 170),
(140001, 170),
(140000, 170),
(140003, 170),
(140002, 170),
(140004, 170);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
