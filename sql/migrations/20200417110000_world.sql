DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200417110000');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200417110000');

REPLACE INTO `mangos_string` (`entry`, `content_default`, `content_loc8`) VALUES 
('1700', 'You have been warned for: Multiboxing. Each player can only be logged on 1 character at a time, not multiple. Please log off the extra character(s) immediately. A warning has been placed on your account, and further violations may result in suspension.', 'Вы получили предупреждение: Мультибоксинг. Позволяется играть не больше чем одним персонажем одновременно. Пожалуйста, немедленно выйдите из игры другими персонажами. Предупреждение было размещено на вашем аккаунте, дальнейшие нарушения правил могут привести к блокировке аккаунта.'),
('1701', 'You have been warned for: AFK system avoidance in battlegrounds. Participating in battlegrounds is mandatory if you have queued for one. Using AFK avoidance measures is against the rules. A warning has been placed on your account, and further violations may result in suspension.', 'Вы получили предупреждение: АФК на полях боя. АФК на поле боя - нарушение правил. Предупреждение было размещено на вашем аккаунте, дальнейшие нарушения правил могут привести к блокировке аккаунта.');

UPDATE `mangos_string` SET `content_loc8`='Вы получили предупреждение:%s. Предупреждение было размещено на вашем аккаунте, дальнейшие нарушения правил могут привести к блокировке аккаунта.\r\n' WHERE (`entry`='283');

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
