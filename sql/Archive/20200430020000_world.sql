DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200430020000');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200430020000');

REPLACE INTO `mangos_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES 
('616', '%s %s%s %s (guid: %u) Account: %s (id: %s%s) GMLevel: %u Last IP: %s%s Last login: %s Latency: %ums Client: %s 2FA: %s', '', '', '', '', '', '', '', '%s %s%s %s (guid: %u) Аккаунт: %s (id: %s%s) Уровень доступа: %u Последний IP: %s%s Последний вход: %s Задержка: %ums Клиент: %s 2FA: %s');

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
