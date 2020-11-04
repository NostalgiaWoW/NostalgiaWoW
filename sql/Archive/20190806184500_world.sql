DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190806184500');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190806184500');

DELETE FROM `creature_loot_template` WHERE `entry`='1000553';
UPDATE `creature_template` SET `minhealth`='1750000', `maxhealth`='1750000' WHERE (`entry`='1000553');
UPDATE `creature` SET `curhealth`='1750000' WHERE (`id`='1000553');

REPLACE INTO `pool_creature` (`guid`, `pool_entry`, `chance`, `description`, `flags`) VALUES 
('2090308', '41000', '0', 'Ragtheradon the Invader', '0'),
('2090309', '41000', '0', 'Ragtheradon the Invader', '0'),
('2090310', '41000', '0', 'Ragtheradon the Invader', '0'),
('2090311', '41000', '0', 'Ragtheradon the Invader', '0'),
('2090312', '41000', '0', 'Ragtheradon the Invader', '0'),
('2090313', '41000', '0', 'Ragtheradon the Invader', '0'),
('2090314', '41000', '0', 'Ragtheradon the Invader', '0'),
('2090315', '41000', '0', 'Ragtheradon the Invader', '0'),
('2090316', '41000', '0', 'Ragtheradon the Invader', '0'),
('2090317', '41000', '0', 'Ragtheradon the Invader', '0'),
('2090318', '41000', '0', 'Ragtheradon the Invader', '0');

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
