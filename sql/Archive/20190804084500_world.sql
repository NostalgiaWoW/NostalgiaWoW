DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190804084500');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190804084500');

REPLACE INTO `pool_template` (`entry`, `max_limit`, `description`, `flags`, `instance`) VALUES ('41000', '1', 'Ragtheradon the Invader', '0', '0');

REPLACE INTO `pool_creature` (`guid`, `pool_entry`, `chance`, `description`, `flags`) VALUES 
('2090308', '41000', '9', 'Ragtheradon the Invader', '0'),
('2090309', '41000', '9', 'Ragtheradon the Invader', '0'),
('2090310', '41000', '9', 'Ragtheradon the Invader', '0'),
('2090311', '41000', '9', 'Ragtheradon the Invader', '0'),
('2090312', '41000', '9', 'Ragtheradon the Invader', '0'),
('2090313', '41000', '9', 'Ragtheradon the Invader', '0'),
('2090314', '41000', '9', 'Ragtheradon the Invader', '0'),
('2090315', '41000', '9', 'Ragtheradon the Invader', '0'),
('2090316', '41000', '9', 'Ragtheradon the Invader', '0'),
('2090317', '41000', '9', 'Ragtheradon the Invader', '0'),
('2090318', '41000', '9', 'Ragtheradon the Invader', '0');

DELETE FROM `game_event_creature` WHERE `event` = '171';
REPLACE INTO `game_event_creature` (`guid`, `event`) VALUES 
('2090308', '171'),
('2090309', '171'),
('2090310', '171'),
('2090311', '171'),
('2090312', '171'),
('2090313', '171'),
('2090314', '171'),
('2090315', '171'),
('2090316', '171'),
('2090317', '171'),
('2090318', '171');

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
