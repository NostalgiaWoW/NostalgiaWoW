DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181226180322');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181226180322');
-- Add your query below.

-- Metzen the Reindeer quest fix
UPDATE `quest_template` SET `SpecialFlags`=0 WHERE `entry` in (8746,8762);

-- Winter Veil quests
-- Shaken present
REPLACE INTO `item_loot_template` (`entry`, `item`, `mincountOrRef`, `maxcount`) VALUES (21271, 21241, 5, 5);

-- Ticking Present
UPDATE `item_loot_template` SET `ChanceOrQuestChance`=100 WHERE `entry`=21327 AND `item`=21213;
UPDATE `item_loot_template` SET `ChanceOrQuestChance`=100 WHERE `entry`=21327 AND `item`=21325;

-- Gaily Wrapped Present
DELETE FROM `item_loot_template` WHERE `entry`=21310;
REPLACE INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `groupid`, `mincountOrRef`, `maxcount`, `condition_id`) VALUES 
(21310, 21308, 25, 1, 1, 1, 0),(21310, 21305, 25, 1, 1, 1, 0),(21310, 21309, 25, 1, 1, 1, 0),(21310, 21301, 25, 1, 1, 1, 0);

-- Winters Veil quests
REPLACE INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`) VALUES 
(8744, 0, 0, -22, 1, 60, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'A Carefully Wrapped Present', '', '', 'The tag on this present reads:$b$bTo $N,$b$bMay your feast of Great-Winter be merry and bright!', NULL, '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21191, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(8767, 0, 0, -22, 1, 60, 1, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'A Gently Shaken Gift', '', '', 'This present looks like it has been shaken a few times. The tag on it reads:$B$BTo a very special $R $C.', NULL, '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21270, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(8768, 0, 0, -22, 20, 60, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'A Gaily Wrapped Present', '', '', 'This festively-wrapped present has your name on it.$b$bWait, did it just move?', NULL, '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21310, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(8769, 0, 0, -22, 40, 60, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'A Ticking Present', '', '', 'Have a joyous Feast of Great-Winter from your friends at Smokeywood Pastures.', NULL, '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21327, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(8788, 0, 0, -22, 1, 60, 1, 0, 1494, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'A Gently Shaken Gift', '', '', 'This present looks like it has been shaken a few times. The tag on it reads:$B$BTo a very special $r $c.', NULL, '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21271, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(8803, 0, 0, -22, 10, 60, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'A Festive Gift', '', '', 'The note on this present reads:$b$bTo $n,$b$bIn hoping this will help you spread warm tidings and holiday cheer to all of Azeroth.$b$bFrom Greatfather Winter', NULL, '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21363, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(8827, 0, 0, -22, 1, 60, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'Winter\'s Presents', 'I hear Greatfather Winter - with the generous support of Smokeywood Pastures - has put presents for everyone under the tree in Ironforge. I wish I could go, but I\'ve got to look after the PX-238 Winter Wondervolt.$b$bBut you should definitely check it out. I\'m sure Greatfather Winter has some presents with your name on them.', 'Speak with Greatfather Winter. He is located near the Smokywood Pastures vendor area in Ironforge.', 'Oh, ho hello there! You can only be here for one reason: to open your Winter Veil presents.$B$BNow, don\'t you worry, Greatfather Winter hasn\'t forgotten about his favorite $R $C. Look under the tree and you\'ll find your gifts.$B$BDuring this season of giving, perhaps your friends would also enjoy receiving some of Smokeywood Pasture\'s excellent products?', NULL, NULL, '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(8828, 0, 0, -22, 1, 60, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'Winter\'s Presents', 'I hear Greatfather Winter - with the generous support of Smokeywood Pastures - has put presents for everyone under the tree in Orgrimmar. I wish I could go, but I\'ve got to look after the PX-238 Winter Wondervolt.$b$bBut you should definitely check it out. I\'m sure Greatfather Winter has some presents with your name on them.', 'Speak with Greatfather Winter. He is located near the Smokywood Pastures vendor area in Orgrimmar.', 'Oh, ho hello there! You can only be here for one reason: to open your Winter Veil presents.$B$BNow, don\'t you worry, Greatfather Winter hasn\'t forgotten about his favorite $R $C. Look under the tree and you\'ll find your gifts.$B$BDuring this season of giving, perhaps your friends would also enjoy receiving some of Smokeywood Pasture\'s excellent products?', NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
REPLACE INTO `creature_questrelation` (`id`, `quest`) VALUES (15732, 8828);
REPLACE INTO `creature_involvedrelation` (`id`, `quest`) VALUES (13445, 8828);
UPDATE `quest_template` SET `RequiredRaces`=77 WHERE  `entry`=8827;
UPDATE `quest_template` SET `RequiredRaces`=178 WHERE  `entry`=8828;

-- Winters Veil Gifts quests
REPLACE INTO `game_event_quest` (`quest`, `event`) VALUES 
(8827, 21),(8828, 21);

REPLACE INTO `gameobject_questrelation` (`id`, `quest`) VALUES 
(180746, 8788),
(180746, 8767),
(180743, 8744),
(180747, 8768),
(180748, 8769),
(180793, 8803);
	
REPLACE INTO `gameobject_involvedrelation` (`id`, `quest`) VALUES 
(180743, 8744),
(180746, 8767),
(180746, 8788),
(180747, 8768),
(180748, 8769),
(180793, 8803);

UPDATE `gameobject_template` SET flags = 0 WHERE entry in (180746, 180743, 180747, 180748, 180793);


-- Present gobs
UPDATE `gameobject_template` SET `data3`=0 WHERE `entry` IN (180747,180748,180793);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES 
(151761, 180747, 0, -4919.58, -980.674, 501.46, 2.15958, 0, 0, 0, 0, 300, 0, 1, 0, 0),
(151762, 180747, 1, 1626.71, -4414.16, 15.8292, 2.2784, 0, 0, 0, 0, 300, 0, 1, 0, 0),
(151763, 180748, 1, 1625.77, -4413.86, 16.0883, 4.80049, 0, 0, 0, 0, 300, 0, 1, 0, 0),
(151764, 180748, 0, -4921.04, -981.624, 501.464, 1.81635, 0, 0, 0, 0, 300, 0, 1, 0, 0),
(151765, 180793, 0, -4916.73, -982.109, 501.884, 1.72839, 0, 0, 0, 0, 300, 0, 1, 0, 0),
(151766, 180793, 1, 1625.46, -4415.83, 15.4469, 2.11818, 0, 0, 0, 0, 300, 0, 1, 0, 0),
(151767, 180743, 0, -4915.83, -981.304, 501.759, 1.99149, 0, 0, 0, 0, 300, 0, 1, 0, 0),
(151768, 180743, 1, 1623.6, -4415.36, 15.1169, 0.75159, 0, 0, 0, 0, 300, 0, 1, 0, 0),
(151769, 180746, 0, -4915.18, -978.104, 501.451, 5.56505, 0, 0, 0, 0, 300, 0, 1, 0, 0),
(151770, 180746, 1, 1624.53, -4414.58, 15.9044, 1.30844, 0, 0, 0, 0, 300, 0, 1, 0, 0);

REPLACE INTO `game_event_gameobject` (`guid`, `event`) VALUES 
(151761, 21),
(151762, 21),
(151763, 21),
(151764, 21),
(151765, 21),
(151766, 21),
(151767, 21),
(151768, 21),
(151769, 21),
(151770, 21);

-- Adds Mechanical Greench
UPDATE `creature_template` SET `subname`='', `minlevel`=58, `maxlevel`=58, `mindmg`=80, `maxdmg`=100, `scale` = 0  WHERE `entry`=15721;

-- Summon Green Helper
DELETE FROM `spell_scripts` WHERE `id`=26532;
REPLACE INTO `spell_scripts` (`id`, `command`, `datalong`, `comments`) VALUES (26532, 15, 26533, 'Summon Green Helper');

-- Summon Red Helper
UPDATE `creature_template` SET `subname`='' WHERE `entry`=15705;
DELETE FROM `spell_scripts` WHERE `id`=26541;
REPLACE INTO `spell_scripts` (`id`, `command`, `datalong`, `comments`) VALUES (26541, 15, 26536, 'Summon Red Helper');

-- Summon Snowman
UPDATE `creature_template` SET `subname`='', `spell1`=23973, `ScriptName`='generic_spell_ai' WHERE  `entry`=15710;
DELETE FROM `spell_scripts` WHERE `id`=26469;
REPLACE INTO `spell_scripts` (`id`, `command`, `datalong`, `comments`) VALUES (26469, 15, 26045, 'Summon Snowman');

-- Summon Reindeer
UPDATE `creature_template` SET `subname`='' WHERE `entry`=15710;
DELETE FROM `spell_scripts` WHERE `id`=26528;
REPLACE INTO `spell_scripts` (`id`, `command`, `datalong`, `comments`) VALUES (26528, 15, 26529, 'Summon Reindeer');

-- Gifts and quest completion items
UPDATE `quest_template` SET `RewMailTemplateId`=122, `RewMailDelaySecs`=172800 WHERE `entry`=8746;
UPDATE `quest_template` SET `RewMailTemplateId`=161, `RewMailDelaySecs`=172800 WHERE `entry`=8762;
UPDATE `quest_template` SET `RewMailTemplateId`=102, `RewMailDelaySecs`=86400 WHERE `entry`=7025;
UPDATE `quest_template` SET `RewMailTemplateId`=108, `RewMailDelaySecs`=86400 WHERE `entry`=6984;
UPDATE `quest_template` SET `RewMailTemplateId`=117, `RewMailDelaySecs`=86400 WHERE `entry`=7045;
UPDATE `quest_template` SET `RequiredRaces`=178, `RewMailTemplateId`=118, `RewMailDelaySecs`=86400 WHERE `entry`=6962;
REPLACE INTO `mail_loot_template` (`entry`, `item`) VALUES (102, 17685),(118, 17685),(122,21216),(161,21216),(108,17712),(117,17712);

-- Snowball modification
REPLACE INTO `spell_effect_mod` (`Id`, `EffectIndex`, `Effect`, `EffectDieSides`, `EffectBaseDice`, `EffectDicePerLevel`, `EffectRealPointsPerLevel`, `EffectBasePoints`, `EffectAmplitude`, `EffectPointsPerComboPoint`, `EffectChainTarget`, `EffectMultipleValue`, `EffectMechanic`, `EffectImplicitTargetA`, `EffectImplicitTargetB`, `EffectRadiusIndex`, `EffectApplyAuraName`, `EffectItemType`, `EffectMiscValue`, `EffectTriggerSpell`, `Comment`) VALUES 
(21167, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, 'Snowball Knockdown allow selfcast'),
(21167, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, 'Snowball Knockdown allow selfcast');

-- Cleanup
DELETE from quest_template where entry IN (8788, 8767, 8744, 8768, 8769, 8803, 6161) and patch = 6;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
