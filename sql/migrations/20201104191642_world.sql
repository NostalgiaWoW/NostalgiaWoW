DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201104191642');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201104191642');
-- Add your query below.

-- Add syntax to Balance command
DELETE FROM `command` WHERE `name`='balance';
INSERT INTO `command` (`name`, `security`, `help`, `flags`) VALUES ('balance', 6, 'Syntax: .balance $accountName $numberOfCoinsToAdd - If this is first time purchase, you will be instructed to run the command twice.', 0);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
