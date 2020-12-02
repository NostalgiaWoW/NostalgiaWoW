DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201202021045');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201202021045');
-- Add your query below.

-- Dargon buff on Mall
DELETE FROM `quest_template` WHERE `entry`=30150 AND `patch`=1;
INSERT INTO `quest_template` VALUES (30150, 1, 2, 956, 55, 60, 60, 0, 0, 77, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0, 0, 0, '[Repeatable] Brood Mother Slayer', 'Bring Onyxia\'s head to the mall for your reward.', 'Hand over the head and revel in your glory!', 'Choose your reward and let the celebration of your glorious victory begin.', '', '', '', '', '', '', 18422, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 76, 0, 0, 0, 0, 500, 0, 0, 0, 0, 5000000, 5000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `quest_template` WHERE `entry`=30151 AND `patch`=1;
INSERT INTO `quest_template` VALUES (30151, 1, 2, 956, 55, 60, 60, 0, 0, 77, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0, 0, 0, '[Repeatable] The Dragon Lord is Dead!', 'Bring Nefarion\'s head to the mall for your reward.', 'Hand over the head and revel in your glory!', 'Choose your reward so that I may mount the head of the beast for all to see.', '', '', '', '', '', '', 19002, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 68, 0, 0, 0, 0, 200, 0, 0, 0, 0, 5000000, 5000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `quest_template` WHERE `entry`=30152 AND `patch`=0;
INSERT INTO `quest_template` VALUES (30152, 0, 2, 956, 55, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0, 0, 0, '[Repeatable] Rend Blackhand Must Die', 'Rend Blackhand is a scourge upon our world. $n, you must sever his head and bring it to us.', 'Hand over the head and revel in your glory!', 'You have dealt a crippling blow to the forces of Blackrock, $N. With their Warchief slain, the Blackrock legion is once again thrown into the maw of chaos.$B$BIn honor of your heroics, the people of Kalimdor shall be rewarded!', '<Thrall grunts.>', '', '', '', '', '', 12630, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13966, 13968, 13965, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 530, 76, 0, 81, 68, 500, 500, 0, 500, 500, 27000, 8700, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9950);
DELETE FROM `quest_template` WHERE `entry`=30153 AND `patch`=0;
INSERT INTO `quest_template` VALUES (30153, 0, 2, 956, 55, 60, 60, 0, 0, 178, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0, 0, 0, '[Repeatable] The Dragon Lord is Dead!', 'Bring Nefarion\'s head to the mall for your reward.', 'Hand over the head and revel in your glory!', 'Choose your reward so that I may mount the head of the beast for all to see.', '', '', '', '', '', '', 19003, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 68, 0, 0, 0, 0, 200, 0, 0, 0, 0, 5000000, 5000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `quest_template` WHERE `entry`=30154 AND `patch`=1;
INSERT INTO `quest_template` VALUES (30154, 1, 2, 956, 55, 60, 60, 0, 0, 178, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 0, 0, 0, '[Repeatable] Brood Mother Slayer', 'Bring Onyxia\'s head to the mall for your reward.', 'Hand over the head and revel in your glory!', 'Choose your reward and let the celebration of your glorious victory begin.', '', '', '', '', '', '', 18423, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 76, 0, 0, 0, 0, 500, 0, 0, 0, 0, 5000000, 5000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `gameobject` WHERE `guid`=4437267;
INSERT INTO `gameobject` VALUES (4437267, 179556, 0, -1817.68, -4171.33, 0.75, 1.69217, 0, 0, 0.482591, -0.875846, -1, 100, 0, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4437276;
INSERT INTO `gameobject` VALUES (4437276, 179881, 0, -1807.11, -4165.54, 0.75, 1.72112, 0, 0, 0.390142, -0.920755, -1, 100, 0, 0, 0);

DELETE FROM `script_texts` WHERE `entry`=-1901176;
INSERT INTO `script_texts` VALUES (-1901176, 'Feel the power of our ancestors course through you and deliver you a boon from one of the past Warchiefs of Azeroth!', '', '', '', '', '', '', '', '', 0, 6, 0, 0, 'warchief blessing yell2');
DELETE FROM `script_texts` WHERE `entry`=-1901175;
INSERT INTO `script_texts` VALUES (-1901175, 'The day has finally come! Rend Blackhand has fallen. $n and $g his:her allies have ripped the head off this beast - once and for all!', '', '', '', '', '', '', '', '', 0, 6, 0, 0, 'warchief blessing yell1');
DELETE FROM `script_texts` WHERE `entry`=-1901174;
INSERT INTO `script_texts` VALUES (-1901174, 'Heroes of Azeroth, on this day, history has been made! $n and $g his:her allies have destroyed the Black Dragonflight this day. Gather round and join me in honoring our heroes.', '', '', '', '', '', '', '', '', 0, 6, 7, 0, 'ally Onyxia Head yell1');
DELETE FROM `script_texts` WHERE `entry`=-1901173;
INSERT INTO `script_texts` VALUES (-1901173, 'Behold the might of the $n and $g his:her allies! The head of the Broodmother of the Black Dragonflight, Onyxia, stuck on a pike! Let the rallying cry of the dragon slayer lift your spirits!', '', '', '', '', '', '', '', '', 0, 6, 7, 0, 'ally Onyxia Head yell2');
DELETE FROM `script_texts` WHERE `entry`=-1901172;
INSERT INTO `script_texts` VALUES (-1901172, 'Let your spirits rise! Rally around your champion, bask in $g his:her glory! Revel in the rallying cry of the dragon slayer!', '', '', '', '', '', '', '', '', 0, 6, 0, 0, 'ally Nef Head yell2');
DELETE FROM `script_texts` WHERE `entry`=-1901171;
INSERT INTO `script_texts` VALUES (-1901171, 'Citizens of Azeroth, the Lord of Blackrock is slain! Nefarian has been destroyed in his lair by $n and $g his:her allies!', '', '', '', '', '', '', '', '', 0, 6, 0, 0, 'ally Nef Head yell1');

DELETE FROM `item_template` WHERE `entry`=12630 AND `patch`=0;
INSERT INTO `item_template` VALUES (12630, 0, 12, 0, 'Head of Rend Blackhand', 1310, 1, 2048, 1, 0, 0, 0, -1, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 4, 'Sickening, bloody, foulness.', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);
DELETE FROM `item_template` WHERE `entry`=18422 AND `patch`=1;
INSERT INTO `item_template` VALUES (18422, 1, 12, 0, 'Head of Onyxia', 30794, 4, 0, 1, 0, 0, 0, -1, -1, 60, 60, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'The head of the Black Dragonflight\'s Brood Mother', 0, 0, 0, 7490, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);
DELETE FROM `item_template` WHERE `entry`=19002 AND `patch`=1;
INSERT INTO `item_template` VALUES (19002, 1, 12, 0, 'Head of Nefarian', 31434, 4, 0, 1, 0, 0, 0, -1, -1, 60, 60, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'The head of Nefarian: Brood of Deathwing.', 0, 0, 0, 7783, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);

DELETE FROM `creature_questrelation` WHERE `id`=1201164 AND `quest`=30151 AND `patch`=0;
INSERT INTO `creature_questrelation` VALUES (1201164, 30151, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1201164 AND `quest`=30152 AND `patch`=0;
INSERT INTO `creature_questrelation` VALUES (1201164, 30152, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1201164 AND `quest`=30153 AND `patch`=0;
INSERT INTO `creature_questrelation` VALUES (1201164, 30153, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1201164 AND `quest`=30154 AND `patch`=0;
INSERT INTO `creature_questrelation` VALUES (1201164, 30154, 0);
DELETE FROM `creature_questrelation` WHERE `id`=1201164 AND `quest`=30150 AND `patch`=0;
INSERT INTO `creature_questrelation` VALUES (1201164, 30150, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1201164 AND `quest`=30154 AND `patch`=0;
INSERT INTO `creature_involvedrelation` VALUES (1201164, 30154, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1201164 AND `quest`=30153 AND `patch`=0;
INSERT INTO `creature_involvedrelation` VALUES (1201164, 30153, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1201164 AND `quest`=30152 AND `patch`=0;
INSERT INTO `creature_involvedrelation` VALUES (1201164, 30152, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1201164 AND `quest`=30151 AND `patch`=0;
INSERT INTO `creature_involvedrelation` VALUES (1201164, 30151, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=1201164 AND `quest`=30150 AND `patch`=0;
INSERT INTO `creature_involvedrelation` VALUES (1201164, 30150, 0);

DELETE FROM `creature_template` WHERE `entry`=1201165 AND `patch`=0;
INSERT INTO `creature_template` VALUES (1201165, 0, 0, 0, 13069, 0, 0, 0, 'Rallying Cry Generator', NULL, 0, 1, 1, 8, 8, 0, 0, 7, 35, 35, 0, 1, 1.14286, 1, 0, 2, 2, 0, 44, 1, 2000, 2000, 1, 33554946, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, '');
DELETE FROM `creature_template` WHERE `entry`=1201164 AND `patch`=0;
INSERT INTO `creature_template` VALUES (1201164, 0, 0, 0, 5567, 0, 0, 0, 'Mall Herald', NULL, 0, 60, 60, 43341, 43341, 0, 0, 3791, 85, 85, 3, 1.1, 1.14286, 0, 1, 528, 681, 0, 272, 1, 1175, 2000, 1, 36864, 0, 0, 0, 0, 0, 0, 62.016, 85.272, 100, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'EventAI', 0, 3, 0, 0, 1, 1478, 0, 0, 0, 0, 2, 0, 'custom_MallAOESpellNPC');
DELETE FROM `creature` WHERE `guid`=3043213;
INSERT INTO `creature` VALUES (3043213, 1201164, 0, 0, 1429, -1822.31, -4188.34, 4.05636, 5.02212, 25, 5, 0, 43341, 0, 0, 0, 0, 0, 0, 10);



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
