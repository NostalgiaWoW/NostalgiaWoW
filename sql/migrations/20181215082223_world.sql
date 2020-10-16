DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181215082223');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181215082223');
-- Add your query below.

-- Auto-Announce Updates (including TBC and Shop info)
DELETE FROM `mangos_string` WHERE `entry`=60008;
INSERT INTO `mangos_string` VALUES (60008, 'Check out the latest additions to our shop @ Elysium-Project.org. Login to the Control Panel with your in game account and check the vanity shop!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=60009;
INSERT INTO `mangos_string` VALUES (60009, 'To connect with the community around you and to help find groups for raids, dungeons and PvP along with items you may need — please join the World channel by typing /join World.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=60007;
INSERT INTO `mangos_string` VALUES (60007, 'Follow us @ Twitter: elysium_dev | Discord: 593JqdY | Facebook: facebook.com/LegacyWoW/', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=60006;
INSERT INTO `mangos_string` VALUES (60006, 'Our TBC BETA is now LIVE! If you wish to help with testing, please see our Discord for more information. Anyone can connect with the TBC Client. We\'re excited to be launching in Q1 2019! tbc.elysium-project.org', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
DELETE FROM `mangos_string` WHERE `entry`=60010;
INSERT INTO `mangos_string` VALUES (60010, 'Our TBC BETA is now LIVE! If you wish to help with testing, please see our Discord for more information. Anyone can connect with the TBC Client. We\'re excited to be launching in Q1 2019! tbc.elysium-project.org', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

DELETE FROM `autobroadcast` WHERE `delay`=1 AND `commentaire` IS NULL AND `stringId`=60006;
INSERT INTO `autobroadcast` VALUES (1, NULL, 60006);
DELETE FROM `autobroadcast` WHERE `delay`=1 AND `commentaire` IS NULL AND `stringId`=60007;
INSERT INTO `autobroadcast` VALUES (1, NULL, 60007);
DELETE FROM `autobroadcast` WHERE `delay`=1 AND `commentaire` IS NULL AND `stringId`=60008;
INSERT INTO `autobroadcast` VALUES (1, NULL, 60008);
DELETE FROM `autobroadcast` WHERE `delay`=1 AND `commentaire` IS NULL AND `stringId`=60009;
INSERT INTO `autobroadcast` VALUES (1, NULL, 60009);
DELETE FROM `autobroadcast` WHERE `delay`=1 AND `commentaire` IS NULL AND `stringId`=60010;
INSERT INTO `autobroadcast` VALUES (1, NULL, 60010);



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
