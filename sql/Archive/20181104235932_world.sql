DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181104235932');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181104235932');
-- Add your query below.

DELETE FROM `creature_ai_scripts` WHERE `creature_id` = 988016;
INSERT INTO `creature_ai_scripts` (`creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUE
(988016, 1, 0, 100, 33, 0, 0, 24000, 30000, 1, -190000, -190001, -190002, 1, -190003, -190004, -190005, 0, 0, 0, 0, 'Blink Dragon - Random Say OOC');

DELETE FROM `mangos_string` WHERE `entry` IN (60000, 60001, 60002, 60003, 60004, 60005);
DELETE FROM `creature_ai_texts` WHERE `entry` IN (-190000, -190001, -190002, -190003, -190004, -190005);
INSERT INTO `creature_ai_texts` (`entry`, `content_default`) VALUES
(-190000, 'REEEEEEEE!'),
(-190001, 'Praise be to SIL!'),
(-190002, 'Rainplz!'),
(-190003, 'Something else'),
(-190004, '#FreeRosen'),
(-190005, 'Did someone say Thunderf... nevermind.');

UPDATE `creature_template` SET `npcflag` = 0, `ScriptName` = '', `AIName` = 'EventAI' WHERE `entry` = 988016;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
