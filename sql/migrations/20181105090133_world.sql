DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181105090133');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181105090133');
-- Add your query below.

DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 988016;
DELETE FROM `creature_ai_texts` WHERE `entry` IN (-190000, -190001, -190002, -190003, -190004, -190005);
DELETE FROM `mangos_string` WHERE `entry` IN (60000, 60001, 60002, 60003, 60004, 60005);
INSERT INTO `mangos_string` (`entry`, `content_default`) VALUES
(60000, 'REEEEEEEE!'),
(60001, 'Praise be to SIL!'),
(60002, 'Rainplz!'),
(60003, 'Something else'),
(60004, '#FreeRosen'),
(60005, 'Did someone say Thunderf... nevermind.');

UPDATE `creature_template` SET `ScriptName` = 'npc_blinkdragon', `AIName` = '' WHERE `entry` = 988016;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
