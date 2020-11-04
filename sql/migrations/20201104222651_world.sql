DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201104222651');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201104222651');
-- Add your query below.

-- Adjust .Account Set GMLEVEL command to be more clear and choose correct realmID.
DELETE FROM `mangos_string` WHERE `entry`=401;
INSERT INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (401, 'You changed GM security level of account %s to %i on realm %i.', NULL, 'Vous modifiez le niveau de sécurité du compte %s à %i.', NULL, NULL, NULL, NULL, NULL, 'Вы изменили уровень доступа %s на %i.');
DELETE FROM `command` WHERE `name`='account set gmlevel';
INSERT INTO `command` (`name`, `security`, `help`, `flags`) VALUES ('account set gmlevel', 6, 'Syntax: .account set gmlevel [$accountId|$accountName] $level\r\n\r\nSet the security level for targeted player (can\'t be used at self) or for $accountId or $accountName to a level of $level.\r\n\r\n$level must be less than your current security.\r\n\r\n\r\n', 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
