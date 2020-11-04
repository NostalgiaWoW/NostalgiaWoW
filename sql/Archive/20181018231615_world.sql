DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181018231615');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181018231615');
-- Add your query below.

/*Quest 7862 Issue*/
UPDATE `quest_template` SET `Objectives`= 'You have been tasked with the decimation of 20 Vilebranch Berserkers, 20 Vilebranch Shadow Hunters, 20 Vilebranch Blood Drinkers, and 20 Vilebranch Soul Eaters.$B$BShould you complete this task, return to Primal Torntusk at Revantusk Village in the Hinterlands.' WHERE `entry`= 7862;
UPDATE `locales_quest` SET `Objectives_loc2`= REPLACE(`Objectives_loc2`,'10','20'), `Objectives_loc3`= REPLACE(`Objectives_loc3`,'10','20'), `Objectives_loc4`= REPLACE(`Objectives_loc4`,'10','20'), `Objectives_loc6`= REPLACE(`Objectives_loc6`,'10','20'), `Objectives_loc7`= REPLACE(`Objectives_loc7`,'10','20'), `Objectives_loc8`= REPLACE(`Objectives_loc8`,'10','20') WHERE `entry`= 7862;
UPDATE `locales_quest` SET `Objectives_loc2`= REPLACE(`Objectives_loc2`,'5','20'), `Objectives_loc3`= REPLACE(`Objectives_loc3`,'5','20'), `Objectives_loc4`= REPLACE(`Objectives_loc4`,'5','20'), `Objectives_loc6`= REPLACE(`Objectives_loc6`,'5','20'), `Objectives_loc7`= REPLACE(`Objectives_loc7`,'5','20'), `Objectives_loc8`= REPLACE(`Objectives_loc8`,'5','20') WHERE `entry`= 7862;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
