DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201129000516');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201129000516');
-- Add your query below.

-- Enchanter NPC
DELETE FROM `creature_template` WHERE `entry`=1201151 AND `patch`=0;
INSERT INTO `creature_template` VALUES (1201151, 0, 0, 0, 1943, 0, 0, 0, 'Enchanting Gem Vendor', 'Nostalgia WoW', 0, 60, 60, 1337, 1337, 420, 420, 3252, 35, 35, 2, 1.26, 1.14286, 1, 3, 110, 142, 0, 272, 1, 2000, 2000, 8, 0, 0, 0, 0, 0, 0, 0, 74.448, 102.366, 100, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');


-- Quests

DELETE FROM `quest_template` WHERE `entry`=30141 AND `patch`=0;
INSERT INTO `quest_template` VALUES (30141, 0, 2, 956, 60, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '[Leg/Head] 8 Strength', 'Greetings $N. I can exchange your proof of combat tokens for valuable gems. These gems will enhance your armor.', 'Hand in 100 PvP Tokens', 'Well met $N. Here is your gem.', 'Yes?', NULL, 'Turn in 100 PvP Tokens', '', NULL, NULL, 80000, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11645, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `quest_template` WHERE `entry`=30142 AND `patch`=0;
INSERT INTO `quest_template` VALUES (30142, 0, 2, 956, 60, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '[Leg/Head] 8 Stamina', 'Greetings $N. I can exchange your proof of combat tokens for valuable gems. These gems will enhance your armor.', 'Hand in 100 PvP Tokens', 'Well met $N. Here is your gem.', 'Yes?', NULL, 'Turn in 100 PvP Tokens', '', NULL, NULL, 80000, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11646, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `quest_template` WHERE `entry`=30143 AND `patch`=0;
INSERT INTO `quest_template` VALUES (30143, 0, 2, 956, 60, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '[Leg/Head] 8 Agility', 'Greetings $N. I can exchange your proof of combat tokens for valuable gems. These gems will enhance your armor.', 'Hand in 100 PvP Tokens', 'Well met $N. Here is your gem.', 'Yes?', NULL, 'Turn in 100 PvP Tokens', '', NULL, NULL, 80000, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11647, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `quest_template` WHERE `entry`=30144 AND `patch`=0;
INSERT INTO `quest_template` VALUES (30144, 0, 2, 956, 60, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '[Leg/Head] 8 Intellect', 'Greetings $N. I can exchange your proof of combat tokens for valuable gems. These gems will enhance your armor.', 'Hand in 100 PvP Tokens', 'Well met $N. Here is your gem.', 'Yes?', NULL, 'Turn in 100 PvP Tokens', '', NULL, NULL, 80000, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11648, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `quest_template` WHERE `entry`=30145 AND `patch`=0;
INSERT INTO `quest_template` VALUES (30145, 0, 2, 956, 60, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '[Leg/Head] 8 Spirit', 'Greetings $N. I can exchange your proof of combat tokens for valuable gems. These gems will enhance your armor.', 'Hand in 100 PvP Tokens', 'Well met $N. Here is your gem.', 'Yes?', NULL, 'Turn in 100 PvP Tokens', '', NULL, NULL, 80000, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11649, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `quest_template` WHERE `entry`=30146 AND `patch`=0;
INSERT INTO `quest_template` VALUES (30146, 0, 2, 956, 60, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '[Leg/Head] 20 Fire Resistance', 'Greetings $N. I can exchange your proof of combat tokens for valuable gems. These gems will enhance your armor.', 'Hand in 100 PvP Tokens', 'Well met $N. Here is your gem.', 'Yes?', NULL, 'Turn in 100 PvP Tokens', '', NULL, NULL, 80000, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11644, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `quest_template` WHERE `entry`=30147 AND `patch`=0;
INSERT INTO `quest_template` VALUES (30147, 0, 2, 956, 60, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '[Leg/Head] 150 Mana', 'Greetings $N. I can exchange your proof of combat tokens for valuable gems. These gems will enhance your armor.', 'Hand in 100 PvP Tokens', 'Well met $N. Here is your gem.', 'Yes?', NULL, 'Turn in 100 PvP Tokens', '', NULL, NULL, 80000, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11622, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `quest_template` WHERE `entry`=30148 AND `patch`=0;
INSERT INTO `quest_template` VALUES (30148, 0, 2, 956, 60, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '[Leg/Head] 125 Armor', 'Greetings $N. I can exchange your proof of combat tokens for valuable gems. These gems will enhance your armor.', 'Hand in 100 PvP Tokens', 'Well met $N. Here is your gem.', 'Yes?', NULL, 'Turn in 100 PvP Tokens', '', NULL, NULL, 80000, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11643, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
DELETE FROM `quest_template` WHERE `entry`=30149 AND `patch`=0;
INSERT INTO `quest_template` VALUES (30149, 0, 2, 956, 60, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '[Leg/Head] 100 Hit', 'Greetings $N. I can exchange your proof of combat tokens for valuable gems. These gems will enhance your armor.', 'Hand in 100 PvP Tokens', 'Well met $N. Here is your gem.', 'Yes?', NULL, 'Turn in 100 PvP Tokens', '', NULL, NULL, 80000, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11642, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);


-- Quest linking
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`)
VALUES
(1201151, 30141, 0),
(1201151, 30142, 0),
(1201151, 30143, 0),
(1201151, 30144, 0),
(1201151, 30145, 0), 
(1201151, 30146, 0), 
(1201151, 30147, 0),
(1201151, 30148, 0),
(1201151, 30149, 0);

INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`)
VALUES
(1201151, 30141, 0),
(1201151, 30142, 0),
(1201151, 30143, 0),
(1201151, 30144, 0),
(1201151, 30145, 0), 
(1201151, 30146, 0), 
(1201151, 30147, 0),
(1201151, 30148, 0),
(1201151, 30149, 0);

-- Fix to gates
DELETE FROM `gameobject_template` WHERE `entry`=3100045;
INSERT INTO `gameobject_template` VALUES (3100045, 0, 3751, 'ArenaGate', 0, 0, 2.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
