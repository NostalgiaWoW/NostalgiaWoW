DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181115050036');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181115050036');
-- Add your query below.

-- Edits to Mute & Unmute notifications to players.
DELETE FROM `mangos_string` WHERE `entry`=300;
INSERT INTO `mangos_string` VALUES (300, 'Your chat has been disabled for %u minutes. Reason: %s. Please review our Terms of Use @ Forum.Elysium-Project.org/topic/70878-terms-of-use-rules-regulations/', NULL, 'Votre tchat a été désactivé pour %u minutes. Raison: %s. Veuillez consulter nos conditions d\'utilisation @ Forum.Elysium-Project.org/topic/70878-terms-of-use-rules-regulations/', NULL, NULL, NULL, NULL, NULL, 'Ваш чат заблокирован на %u минут. Причина: %s. Ознакомьтесь с нашими Условиями использования @ Forum.Elysium-Project.org/topic/70878-terms-of-use-rules-regulations/');
DELETE FROM `mangos_string` WHERE `entry`=303;
INSERT INTO `mangos_string` VALUES (303, 'Your chat has been enabled. Please ensure you review our Terms of Use @ Forum.Elysium-Project.org/topic/70878-terms-of-use-rules-regulations/', NULL, 'Votre tchat a été activé.', NULL, NULL, NULL, NULL, NULL, 'Ваш чат теперь разблокирован.');
DELETE FROM `mangos_string` WHERE `entry`=301;
INSERT INTO `mangos_string` VALUES (301, 'You have disabled %s\'s chat for %u minutes. They have been notified and asked to review the ToU.', NULL, 'Vous avez désactivé le tchat de %s pour %u minutes.', NULL, NULL, NULL, NULL, NULL, 'Вы заблокировали чат %s на %u минут.');
DELETE FROM `mangos_string` WHERE `entry`=304;
INSERT INTO `mangos_string` VALUES (304, 'You have enabled %s\'s chat. They have been notified and asked to review the TOU.', NULL, 'Vous avez activé le tchat de %s.', NULL, NULL, NULL, NULL, NULL, 'Вы разблокировали чат %s.');



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
