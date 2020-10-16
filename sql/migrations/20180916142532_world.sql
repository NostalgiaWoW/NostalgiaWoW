DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180916142532');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180916142532');
-- Add your query below.

DELETE FROM `creature_template` WHERE `entry` = 50000;
INSERT INTO `creature_template` VALUES (50000, 0, 0, 0, 62, 0, 0, 0, 'Hydraling', NULL, 0, 1, 1, 5000, 5000, 0, 0, 7, 35, 35, 0, 1, 1.14286, 0.5, 0, 2, 2, 0, 44, 1, 2000, 2000, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, '');

DELETE FROM `item_template` WHERE `entry` = 50000;
INSERT INTO `item_template` VALUES ('50000','0','0','0','Hydraling','8289','4','1088','1','0','0','0','2047','255','1','0','0','0','0','0','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','27639','0','0','0','-1','0','-1','0','0','0','0','-1','0','-1','0','0','0','0','-1','0','-1','0','0','0','0','-1','0','-1','0','0','0','0','0','0','0','1','','0','0','0','0','0','-1','0','0','0','0','0','0','0','0','','0','0','0','0','0','0','1');
UPDATE `creature_template` SET `scale`='0.2' WHERE `entry`='50000';
UPDATE `item_template` SET `description`='The hydraling can be an expensive pet, as it is capable of eating from three food bowls at the same time.' WHERE `entry`='50000';
UPDATE `item_template` SET `displayid`='24730' WHERE (`entry`='50000') AND (`patch`='0');


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
