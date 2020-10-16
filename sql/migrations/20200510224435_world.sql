DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200510224435');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200510224435');
-- Add your query below.

-- Cmangos fixes to Midsummer event

-- Flame of Stormwind
DELETE FROM `spell_scripts` WHERE `id`=29137;
INSERT INTO `spell_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `comments`) VALUES (29137, 0, 15, 29101, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Cleansing Flames - Create Flame of Stormwind');

-- Flame of Ironforge
DELETE FROM `spell_scripts` WHERE `id`=29135;
INSERT INTO `spell_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `comments`) VALUES (29135, 0, 15, 29102, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Cleansing Flames - Create Flame of Ironforge');

-- Flame of Darnassus
DELETE FROM `spell_scripts` WHERE `id`=29126;
INSERT INTO `spell_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `comments`) VALUES (29126, 0, 15, 29099, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Cleansing Flames - Create Flame of Darnassus');

-- Flame of Undercity
DELETE FROM `spell_scripts` WHERE `id`=29139;
INSERT INTO `spell_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `comments`) VALUES (29139, 0, 15, 29133, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Cleansing Flames - Create Flame of Undercity');

-- Flame of Orgrimmar
DELETE FROM `spell_scripts` WHERE `id`=29136;
INSERT INTO `spell_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `comments`) VALUES (29136, 0, 15, 29130, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Cleansing Flames - Create Flame of Orgrimmar');

-- Flame of Thunder Bluff
DELETE FROM `spell_scripts` WHERE `id`=29138;
INSERT INTO `spell_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `comments`) VALUES (29138, 0, 15, 29132, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Cleansing Flames - Create Flame of Thunder Bluff');


-- Add all Midsummer Bonfire spawns to Midsummer Fire Festival event.
REPLACE INTO `game_event_creature` (`guid`, `event`) VALUES 
(1882, 1),
(47575, 1),
(47614, 1),
(94864, 1),
(94865, 1),
(94866, 1),
(94867, 1),
(94868, 1),
(94869, 1),
(94870, 1),
(94871, 1),
(94872, 1),
(94873, 1),
(94875, 1),
(94876, 1),
(94877, 1),
(94878, 1),
(94879, 1),
(94880, 1),
(94881, 1),
(94882, 1),
(94883, 1),
(94884, 1),
(94886, 1),
(94887, 1),
(94888, 1),
(94889, 1),
(94890, 1),
(94891, 1),
(94892, 1),
(94893, 1),
(94894, 1),
(94895, 1),
(94896, 1),
(94897, 1),
(94898, 1),
(94899, 1),
(94900, 1),
(94901, 1),
(94902, 1),
(94903, 1),
(94904, 1),
(94905, 1),
(94906, 1),
(94907, 1),
(94908, 1),
(94909, 1),
(94910, 1),
(94911, 1),
(94912, 1),
(94913, 1),
(94914, 1),
(2769561, 1),
(2769563, 1),
(2769562, 1),
(2769564, 1),
(2769565, 1),
(2769568, 1),
(2769569, 1),
(2769570, 1),
(2769571, 1),
(2769572, 1),
(2769573, 1),
(2769517, 1),
(2769521, 1),
(2769520, 1),
(2769519, 1),
(2769518, 1),
(2769522, 1),
(2769515, 1),
(94918, 1),
(4408488, 1),
(4415421, 1),
(4415429, 1),
(4415432, 1),
(4412088, 1),
(4409579, 1),
(4405118, 1),
(4412103, 1),
(4416011, 1), 
(4412340, 1),
(4412341, 1),
(4405997, 1),
(4405222, 1);


REPLACE INTO `game_event_gameobject` (`guid`, `event`) VALUES 
(4370439, 1),
(4370438, 1),
(4370458, 1),
(4370459, 1),
(4370460, 1),
(4370461, 1),
(4370465, 1),
(4370422, 1),
(4370423, 1),
(4370431, 1),
(4370428, 1),
(4370429, 1),
(4370430, 1),
(4370435, 1),
(4370436, 1),
(4370440, 1),
(4370439, 1),
(4370438, 1),
(4370437, 1),
(4370441, 1),
(4370442, 1),
(4370443, 1),
(4370444, 1);

DELETE FROM `game_event_gameobject` WHERE `guid`=4404894 AND `event`=1;
INSERT INTO `game_event_gameobject` (`guid`, `event`) VALUES (4404894, 1);
DELETE FROM `game_event_gameobject` WHERE `guid`=4405743 AND `event`=1;
INSERT INTO `game_event_gameobject` (`guid`, `event`) VALUES (4405743, 1);
DELETE FROM `game_event_gameobject` WHERE `guid`=4411985 AND `event`=1;
INSERT INTO `game_event_gameobject` (`guid`, `event`) VALUES (4411985, 1);
DELETE FROM `game_event_gameobject` WHERE `guid`=4405809 AND `event`=1;
INSERT INTO `game_event_gameobject` (`guid`, `event`) VALUES (4405809, 1);




-- Add missing quest greetings from classic sniffs.

DELETE FROM `quest_greeting` WHERE `entry` = 1952;
DELETE FROM `quest_greeting` WHERE `entry` = 10321;
DELETE FROM `quest_greeting` WHERE `entry` = 11596;
INSERT INTO `quest_greeting` (`entry`, `type`, `content_default`, `Emote`, `EmoteDelay`) VALUES (1952, 0, 'Hello, $C.  If you\'re here, then you must know that Silverpine is saturated with our enemies.  To survive, the Forsaken must drive them back!', 0, 0);
INSERT INTO `quest_greeting` (`entry`, `type`, `content_default`, `Emote`, `EmoteDelay`) VALUES (10321, 0, '<Emberstrife acknowledges your presence.>', 0, 0);
INSERT INTO `quest_greeting` (`entry`, `type`, `content_default`, `Emote`, `EmoteDelay`) VALUES (11596, 0, 'My business plan never accounted for housing giant kodos... maybe I should have gone into the underwater basket weaving business instead.', 1, 0);
-- Add missing quest greetings from cmangos db.

DELETE FROM `quest_greeting` WHERE `entry` = 7777;
DELETE FROM `quest_greeting` WHERE `entry` = 16361;
DELETE FROM `quest_greeting` WHERE `entry` = 16478;
DELETE FROM `quest_greeting` WHERE `entry` = 16786;
DELETE FROM `quest_greeting` WHERE `entry` = 16788;
INSERT INTO `quest_greeting` (`entry`, `type`, `content_default`, `Emote`, `EmoteDelay`) VALUES (7777, 0, 'The Gordunni Ogres encroach upon our lands.  We send as many as are willing to face them in the desecrated ruins of Feralas.', 1, 0);
INSERT INTO `quest_greeting` (`entry`, `type`, `content_default`, `Emote`, `EmoteDelay`) VALUES (16361, 0, 'The Lich King has brought war against us from the frozen north, and only we of the Argent Dawn stand in his way.', 1, 0);
INSERT INTO `quest_greeting` (`entry`, `type`, `content_default`, `Emote`, `EmoteDelay`) VALUES (16478, 0, 'Good day to you, citizen. Have you come to aid us against the Scourge?', 1, 0);
INSERT INTO `quest_greeting` (`entry`, `type`, `content_default`, `Emote`, `EmoteDelay`) VALUES (16786, 0, 'Greetings, $n. If you bring me necrotic stones from the undead invaders, I can give you access to the stores of the Argent Dawn.', 66, 0);
INSERT INTO `quest_greeting` (`entry`, `type`, `content_default`, `Emote`, `EmoteDelay`) VALUES (16788, 0, 'Greetings, $c. I am the Flamekeeper. During the Midsummer Fire Festival, it is my duty to keep this fire beside me burning brightly. It is an honor to be selected for such a task; I fill it gladly.$b$b How can I help you?', 1, 0);

-- Event 24 is useless, never used.
DELETE FROM `game_event` WHERE `entry`=24;
-- Deleting gameobjects spawns for it (they are pvp sign posts).
-- These sign posts are already spawned for the call to arms events.
DELETE FROM `gameobject` WHERE `guid` IN (29295, 29296, 29297, 29298, 29302, 29303, 29593, 29594, 29595, 29596, 29597, 29598, 29968, 29969, 30653, 30654, 30688, 30689, 30690);
DELETE FROM `game_event_gameobject` WHERE `event`=24;

-- Festival Flamekeeper Spawn locations
-- Ironforge
DELETE FROM `creature` WHERE `guid`=2769514;
INSERT INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES (2769514, 16788, 0, 0, 0, -4698.93, -1217.61, 501.66, 2.01971, 25, 5, 0, 6900, 0, 0, 1, 0, 0, 0, 10);

DELETE FROM `creature_template` WHERE `entry`=16788 AND `patch`=0;
INSERT INTO `creature_template` (`entry`, `patch`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Civilian`, `RacialLeader`, `RegenHealth`, `equipment_id`, `trainer_id`, `vendor_id`, `MechanicImmuneMask`, `SchoolImmuneMask`, `flags_extra`, `aggroRadius`, `ScriptName`) VALUES (16788, 0, 0, 0, 16334, 16340, 0, 0, 'Festival Flamekeeper', NULL, 65533, 60, 60, 6900, 6900, 0, 0, 3750, 35, 35, 3, 1, 1.14286, 0, 0, 104, 138, 0, 272, 7, 2000, 2000, 1, 33536, 0, 0, 0, 0, 0, 0, 72, 106, 26, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, '');

-- Festival Flamekeeper Gossip Dialogue
DELETE FROM `npc_text` WHERE `ID`=81011;
INSERT INTO `npc_text` (`ID`, `text0_0`, `text0_1`, `lang0`, `prob0`, `em0_0`, `em0_1`, `em0_2`, `em0_3`, `em0_4`, `em0_5`, `text1_0`, `text1_1`, `lang1`, `prob1`, `em1_0`, `em1_1`, `em1_2`, `em1_3`, `em1_4`, `em1_5`, `text2_0`, `text2_1`, `lang2`, `prob2`, `em2_0`, `em2_1`, `em2_2`, `em2_3`, `em2_4`, `em2_5`, `text3_0`, `text3_1`, `lang3`, `prob3`, `em3_0`, `em3_1`, `em3_2`, `em3_3`, `em3_4`, `em3_5`, `text4_0`, `text4_1`, `lang4`, `prob4`, `em4_0`, `em4_1`, `em4_2`, `em4_3`, `em4_4`, `em4_5`, `text5_0`, `text5_1`, `lang5`, `prob5`, `em5_0`, `em5_1`, `em5_2`, `em5_3`, `em5_4`, `em5_5`, `text6_0`, `text6_1`, `lang6`, `prob6`, `em6_0`, `em6_1`, `em6_2`, `em6_3`, `em6_4`, `em6_5`, `text7_0`, `text7_1`, `lang7`, `prob7`, `em7_0`, `em7_1`, `em7_2`, `em7_3`, `em7_4`, `em7_5`) VALUES (81011, 'Greetings $N. The flame burns bright in you.', NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `gossip_menu` WHERE `entry`=65533 AND `text_id`=81011;
INSERT INTO `gossip_menu` (`entry`, `text_id`, `condition_id`) VALUES (65533, 81011, 0);




-- Midsummer Loremaster Gossip

DELETE FROM `gossip_menu` WHERE `entry` = 7326;
INSERT INTO `gossip_menu` VALUES (7326, 8703, 0);
UPDATE `creature_template` SET `gossip_menu_id`=7326 WHERE `entry` = 16817;
UPDATE `creature_template` SET `gossip_menu_id`=7326 WHERE `entry` = 16818;

-- Midsummer Loremaster Quests ALLIANCE

-- "The Festival of Fire"

DELETE FROM `creature_questrelation` WHERE `id`=16817 AND `quest`=9367 AND `patch`=9;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (16817, 9367, 9);

DELETE FROM `creature_involvedrelation` WHERE `id`=16817 AND `quest`=9367 AND `patch`=9;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16817, 9367, 9);

DELETE FROM `quest_template` WHERE `entry`=9367 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9367, 9, 2, -369, 50, 60, 60, 0, 0, 1101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'The Festival of Fire', 'Midsummer is upon us once again!$b$bEach year, as tradition dictates, Flamekeepers are chosen to tend the bonfires within our capitals. While fires are burning throughout Azeroth, it is imperative that ours be the hottest and brightest, to properly pay homage to the season.$b$bIn fact, I have a task for you, if you don\'t mind. I\'ve not yet heard if the fires in all capitals are properly burning. Travel there yourself and warm yourself by the fires--make sure they\'re hot!', 'Touch the bonfires within Stormwind, Ironforge, and Darnassus, then speak to a Festival Loremaster within the capital cities.', 'Excellent work, $N. With the shadows destroyed, it can only be a matter of time before the Lich King decides to recall his necropolises and leave us in peace.', 'Have you had any luck, $N?', NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -181332, -181333, -181334, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23247, 23246, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 650);


-- Flame Stealing Quest

DELETE FROM `creature_questrelation` WHERE `id`=16817 AND `quest`=9365 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (16817, 9365, 0);


DELETE FROM `creature_involvedrelation` WHERE `id`=16817 AND `quest`=9324 AND `patch`=9;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16817, 9324, 9);
DELETE FROM `creature_involvedrelation` WHERE `id`=16817 AND `quest`=9325 AND `patch`=9;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16817, 9325, 9);
DELETE FROM `creature_involvedrelation` WHERE `id`=16817 AND `quest`=9326 AND `patch`=9;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16817, 9326, 9);
DELETE FROM `creature_involvedrelation` WHERE `id`=16817 AND `quest`=9365 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16817, 9365, 0);

DELETE FROM `quest_template` WHERE `entry`=9324 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9324, 9, 2, -369, 50, 60, 60, 0, 0, 1101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9365, -9324, 9365, 23179, 1, 0, 'Stealing Orgrimmar\'s Flame', 'This flame, stolen from the heart of Orgrimmar itself, floods you with warmth. This raw power is foreign to you, but the Loremaster might know more...', 'Return the Flame of Orgrimmar to the Festival Loremaster.', 'What\'s this? Unless I\'m mistaken, this flame has been taken from the heart of Orgrimmar itself! The fierce hearts of the orcs and trolls are reflected in its searing heat. What a fine addition to our collection--how brave you are, stealing into the enemy\'s lair to retrieve the sacred flame!', 'You\'re practically glowing, $R. What do you have there?', '', '', '', '', '', 23179, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23435, 23327, 23326, 23211, 0, 0, 5, 5, 5, 5, 0, 0, 23247, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4950);
DELETE FROM `quest_template` WHERE `entry`=9325 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9325, 9, 2, -369, 50, 60, 60, 0, 0, 1101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9365, -9324, 9365, 23180, 1, 0, 'Stealing Thunder Bluff\'s Flame', 'This flame, stolen from the shaman of Thunder Bluff, floods you with warmth. This raw power is foreign to you, but the Loremaster might know more...', 'Return the Flame of Thunder Bluff to the Festival Loremaster.', 'Unless I miss my guess, this fire has been taken from the cliffs of Thunder Bluff! How it sings with the power of the spirits! You are quite the thief, $N. Take this as just payment for your skill. Now, if only we had the flames of all three cities...', 'You\'re practically glowing, $R. What do you have there?', '', '', '', '', '', 23180, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23435, 23327, 23326, 23211, 0, 0, 5, 5, 5, 5, 0, 0, 23247, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4950);
DELETE FROM `quest_template` WHERE `entry`=9326 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9326, 9, 2, -369, 50, 60, 60, 0, 0, 1101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9365, -9324, 9365, 23181, 1, 0, 'Stealing the Undercity\'s Flame', 'This flame, stolen from the ruins above the Undercity, floods you with warmth. This raw power is foreign to you, but the Loremaster might know more...', 'Return the Flame of the Undercity to the Festival Loremaster.', 'Hm... what a strange fire! It is subdued, nearly smoldering, but the heat is intense. And you received this from the Undercity, you say? Fascinating. With the flames of all three cities, who knows what we could accomplish?', 'You\'re practically glowing, $R. What do you have there?', '', '', '', '', '', 23181, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23435, 23327, 23326, 23211, 0, 0, 5, 5, 5, 5, 0, 0, 23247, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4950);
DELETE FROM `quest_template` WHERE `entry`=9365 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9365, 9, 0, -369, 50, 60, 60, 0, 0, 1101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'A Thief\'s Reward', 'You\'ve proved yourself today, $n.', 'While I have little else to give you, I do have this crown; a fitting gift for a conqueror. May it light your way.', 'You\'ve proved yourself today, $n. $b$bWhile I have little else to give you, I do have this crown; a fitting gift for a conqueror. May it light your way.', 'You\'ve proved yourself today, $n. \\nWhile I have little else to give you, I do have this crown; a fitting gift for a conqueror. May it light your way.', '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23323, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7500);

-- Midsummer Loremaster Quests HORDE

-- "The Festival of Fire"
DELETE FROM `creature_questrelation` WHERE `id`=16818 AND `quest`=9368 AND `patch`=9;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (16818, 9368, 9);

DELETE FROM `creature_involvedrelation` WHERE `id`=16818 AND `quest`=9368 AND `patch`=9;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16818, 9368, 9);

-- Flame Stealing
DELETE FROM `creature_questrelation` WHERE `id`=16818 AND `quest`=9339 AND `patch`=0;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (16818, 9339, 0);

DELETE FROM `creature_involvedrelation` WHERE `id`=16818 AND `quest`=9330 AND `patch`=9;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16818, 9330, 9);
DELETE FROM `creature_involvedrelation` WHERE `id`=16818 AND `quest`=9331 AND `patch`=9;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16818, 9331, 9);
DELETE FROM `creature_involvedrelation` WHERE `id`=16818 AND `quest`=9332 AND `patch`=9;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16818, 9332, 9);
DELETE FROM `creature_involvedrelation` WHERE `id`=16818 AND `quest`=9339 AND `patch`=9;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16818, 9339, 9);

DELETE FROM `quest_template` WHERE `entry`=9330 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9330, 9, 2, -369, 50, 60, 60, 0, 0, 690, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9339, -9330, 9339, 23182, 1, 0, 'Stealing Stormwind\'s Flame', 'This flame, stolen from the heart of Stormwind itself, floods you with warmth. This raw power is foreign to you, but the Talespinner might know more...', 'Return the Flame of Stormwind to the Festival Talespinner.', 'And this brightly-burning fire... you say it came from Stormwind? Remarkable! That must have been quite an adventure! I\'ll pay you for this, of course. If you find anything else like this, be sure to speak with me again.', 'You\'re practically glowing, $R. What do you have there?', '', '', '', '', '', 23182, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23435, 23327, 23326, 23211, 0, 0, 5, 5, 5, 5, 0, 0, 23247, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4950);
DELETE FROM `quest_template` WHERE `entry`=9331 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9331, 9, 2, -369, 50, 60, 60, 0, 0, 690, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9339, -9330, 9339, 23183, 1, 0, 'Stealing Ironforge\'s Flame', 'This flame, stolen from the heart of Ironforge itself, floods you with warmth. This raw power is foreign to you, but the Talespinner might know more...', 'Return the Flame of Ironforge to the Festival Talespinner.', 'This hearty flame must be from the halls of Ironforge; it\'s as stalwart as the dwarves themselves. A fine catch, $N. If I had the fires of the other cities... ah, but never mind. Here is your payment.', 'You\'re practically glowing, $R. What do you have there?', '', '', '', '', '', 23183, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23435, 23327, 23326, 23211, 0, 0, 5, 5, 5, 5, 0, 0, 23247, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4950);
DELETE FROM `quest_template` WHERE `entry`=9332 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9332, 9, 2, -369, 50, 60, 60, 0, 0, 690, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9339, -9330, 9339, 23184, 1, 0, 'Stealing Darnassus\'s Flame', 'This flame, stolen from the shores of Teldrassil, floods you with warmth. This raw power is foreign to you, but the Talespinner might know more...', 'Return the Flame of Darnassus to the Festival Talespinner.', 'This fire aches of ancient sorrow, $N. You pulled this from the roots of Teldrassil, you say? Fascinating! Here is a reward for your skill. Return to me should you find anything else like this; I may have a use for it.', 'You\'re practically glowing, $R. What do you have there?', '', '', '', '', '', 23184, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23435, 23327, 23326, 23211, 0, 0, 5, 5, 5, 5, 0, 0, 23247, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4950);
DELETE FROM `quest_template` WHERE `entry`=9339 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9339, 9, 0, -369, 50, 60, 60, 0, 0, 690, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'A Thief\'s Reward', 'You\'ve proved yourself today, $n.', 'While I have little else to give you, I do have this crown; a fitting gift for a conqueror. May it light your way.', 'You\'ve proved yourself today, $n.', 'While I have little else to give you, I do have this crown; a fitting gift for a conqueror. May it light your way.', '', '', '', '', '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23323, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7500);

-- A Light in Dark Places

DELETE FROM `creature_questrelation` WHERE `id`=16818 AND `quest`=9319 AND `patch`=9;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (16818, 9319, 9);
DELETE FROM `creature_questrelation` WHERE `id`=16788 AND `quest`=9319 AND `patch`=9;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (16788, 9319, 9);
DELETE FROM `creature_questrelation` WHERE `id`=16818 AND `quest`=9386 AND `patch`=9;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (16818, 9386, 9);
DELETE FROM `creature_questrelation` WHERE `id`=16788 AND `quest`=9386 AND `patch`=9;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (16788, 9386, 9);

DELETE FROM `creature_involvedrelation` WHERE `id`=16818 AND `quest`=9319 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16818, 9319, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=16788 AND `quest`=9319 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16788, 9319, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=16818 AND `quest`=9386 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16818, 9386, 0);
DELETE FROM `creature_involvedrelation` WHERE `id`=16788 AND `quest`=9386 AND `patch`=0;
INSERT INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16788, 9386, 0);

-- Flame locations
DELETE FROM `gameobject` WHERE `guid`=4346700;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346700, 181346, 429, 537.484, 601.511, -4.75473, 2.60135, 0, 0, 0.963738, 0.26685, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346699;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346699, 181347, 229, -15.1606, -369.905, 49.5024, 0.891834, 0, 0, 0.431286, 0.902215, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346701;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346701, 181349, 289, 100.853, 66.575, 98.1006, 0.153334, 0, 0, 0.0765919, 0.997063, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4346700;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4346700, 181348, 329, 3696.38, -3160.34, 127.314, 3.51272, 0, 0, 0.982833, -0.184499, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4404894;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4404894, 181338, 0, 2237.04, -5296.77, 82.293, 0.422697, 0, 0, 0.209779, 0.977749, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4405743;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4405743, 181341, 0, -7199.48, -1050.34, 241.633, 2.98011, 0, 0, 0.996742, 0.0806514, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4411985;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4411985, 181345, 0, 256.97, -3803.44, 142.489, 6.16238, 0, 0, 0.0603642, -0.998176, 25, 100, 1, 0, 0);






-- Flickering Flames & Wild Fires Quests Corrections & Additions
DELETE FROM `quest_template` WHERE `entry`=9322 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9322, 9, 2, -369, 50, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'Wild Fires in Kalimdor', 'The Midsummer Fire Festival is celebrated everywhere in Azeroth, and the diverse land of Kalimdor is no exception. You look fit to travel -- perhaps a journey is in order.$b$bMidsummer cannot be truly appreciated unless you\'ve seen the blistering blue fires abroad. The celebrants have lit fires in chilly western Winterspring, northeastern Azshara, near Valor\'s Rest in the wastes of Silithus, and by the entrance to lush Un\'Goro. Return once your journey is complete.', 'Visit the Midsummer camps located in Azshara, Silithus, Un\'Goro Crater, and Winterspring, then return to the Festival Flamekeeper.', 'Your spirit glows with the warmth of the Kalimdor fires, friend. Is the heat not invigorating? Once the power fades from you, perhaps these will help rekindle the feeling.', 'Are the flames of Kalimdor burning brightly?', '', 'Flame of Azshara', 'Flame of Silithus', 'Flame of Un\'Goro', 'Flame of Winterspring', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -181342, -181339, -181343, -181340, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23379, 23247, 0, 0, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3300);
DELETE FROM `quest_template` WHERE `entry`=9323 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9323, 9, 2, -369, 50, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'Wild Fires in the Eastern Kingdoms', 'Our celebration of the flame is spread throughout the land, $c. Not a single place remains untouched by the heat of this holiday, and the strongest fires burn a brilliant blue. Seek them out.$b$bYou\'ll find one just north of Blackrock Spire. The others are located deep within the Eastern Plaguelands near a decrepit town, along the road to the cliffs within the mountainous Hinterlands, and on the way to the Dark Portal within the Blasted Lands.$b$b Return once your journey is done.', 'Visit the Fire Festival camps located in Blasted Lands, Eastern Plaguelands, the Hinterlands and Searing Gorge, then speak with the Festival Flamekeeper.', 'Ah, here you are. A little wearier, a bit dustier, but enlightened! The heat touches us all during this season and unites us; your very being glows with the power of the fires you touched. Ah, but these days enlightenment is taken as a rather poor reward for being sent on a task, I suppose. Take these, then, and enjoy the celebration.', 'It will take time to prevail against this threat. How have you fared, $N?', '', 'Flame of the Blased Lands', 'Flame of the Plaguelands', 'Flame of the Hinterlands', 'Flame of Searing Gorge', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -181344, -181338, -181345, -181341, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23324, 23247, 0, 0, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3300);
DELETE FROM `quest_template` WHERE `entry`=9388 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9388, 9, 2, -369, 50, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Flickering Flames in Kalimdor', 'There are many flames burning throughout the world today, <name>. The trickiest fires to tend are those that burn green; they do not stay lit long without supervision. Make certain the emerald fires still burn on Kalimdor for our Flamekeeper, eh?\r\n\r\n$b$bYou will find them near Ratchet in the Barrens, close to the Master\'s Glaive in Darkshore, in the forest of Ashenvale by the bridge near Silverwing Outpost, and near the road to Windshear Crag along the main road in Stonetalon Mountains.', 'Visit the bonfires within Ashenvale, the Barrens, Darkshore, and Stonetalon Mountains, then speak with the Festival Flamekeeper.', 'Ahhh, so they do still burn. I am glad; it would not do for those fires to burn out before their time. You have done well, <name>. Take this with my blessing.', 'The fires cannot die until the festival is done!', NULL, 'Flame of Ashenvale', 'Flame of the Barrens', 'Flame of Darkshore', 'Flame of Stonetalon', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -181561, -181560, -181563, -181562, 1, 1, 1, 1, 0, 0, 0, 0, 23435, 23327, 23326, 23211, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15000);
DELETE FROM `quest_template` WHERE `entry`=9389 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9389, 9, 2, -369, 50, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'Flickering Flames in the Eastern Kingdoms', 'The Midsummer Fire Festival traditionally lights up the land with a myriad of flames. Some argue that the green fires are the finest, as they are the hardest to maintain and have such a distinctive hue.\r\n\r\n$b$bMake sure they still burn in the Eastern Kingdoms for our Flamekeeper. They sit near Dun Modr in the Wetlands, close to Pyrewood Village within Silverpine Forest, on the cliffs overlooking the lighthouse in Westfall, and by the ruined tower in Hillsbrad Foothills.', 'Visit the bonfires within Hillsbrad Foothills, Silverpine Forest, Westfall, and the Wetlands, then speak with the Festival Flamekeeper.', 'So you\'ve returned, and you\'ve seen to the emerald flames of the continent. What do you think, mm? A rare and wonderful sight, to be certain. I am aware, however, that tangible rewards are better appreciated... so please, take this for your trouble.', 'Have you seen to your task?', '', 'Flame of Hillsbrad', 'Flame of Silverpine', 'Flame of Westfall', 'Flame of the Wetlands', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -181566, -181564, -181565, -181567, 1, 1, 1, 1, 0, 0, 0, 0, 23435, 23327, 23326, 23211, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15000);
DELETE FROM `creature_questrelation` WHERE `id`=16788 AND `quest`=9322 AND `patch`=9;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (16788, 9322, 9);
DELETE FROM `creature_questrelation` WHERE `id`=16788 AND `quest`=9323 AND `patch`=9;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (16788, 9323, 9);
DELETE FROM `creature_questrelation` WHERE `id`=16817 AND `quest`=9388 AND `patch`=9;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (16817, 9388, 9);
DELETE FROM `creature_questrelation` WHERE `id`=16817 AND `quest`=9389 AND `patch`=9;
INSERT INTO `creature_questrelation` (`id`, `quest`, `patch`) VALUES (16817, 9389, 9);

REPLACE INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16788, 9388, 9);
REPLACE INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16788, 9389, 9);
REPLACE INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16788, 9322, 9);
REPLACE INTO `creature_involvedrelation` (`id`, `quest`, `patch`) VALUES (16788, 9323, 9);


-- Bonfire Corrections
REPLACE INTO `gameobject` (`guid`, `id`) VALUES
(50687, 187288);
DELETE FROM `gameobject` WHERE `guid`=4405118;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4405118, 181567, 0, -2617, -2505, 83, 4.89176, 0, 0, 0.640934, -0.767596, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4405222;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4405222, 181338, 0, 1904.48, -4399.67, 74.9887, 5.48537, 0, 0, 0.388411, -0.921486, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4405997;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4405997, 181344, 0, -11281.7, -3052.49, -0.157036, 4.61694, 0, 0, 0.740037, -0.672567, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4408488;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4408488, 181560, 1, -1048.22, -3408.09, 73.9554, 5.25899, 0, 0, 0.490007, -0.871719, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4409579;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4409579, 181565, 0, -11295, 1804, 42.5, 4.46456, 0, 0, 0.789082, -0.614288, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4412088;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4412088, 181564, 0, -300.026, 1198.67, 63.4885, 2.90693, 0, 0, 0.993124, 0.117064, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4412103;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4412103, 181345, 0, 90.14, -3969, 138, 2.29213, 0, 0, 0.911149, 0.412077, 0, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4412340;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4412340, 181343, 1, -7845.12, -2056.34, -272.152, 2.79601, 0, 0, 0.985109, 0.171931, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4412341;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4412341, 181339, 1, -6354.04, -246.867, -1.3813, 4.79789, 0, 0, 0.676241, -0.73668, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4415421;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4415421, 181561, 1, 1858.86, -1980.26, 114.225, 5.64539, 0, 0, 0.313519, -0.949582, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4415429;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4415429, 181563, 1, 4305.04, 211.211, 53.9006, 3.91594, 0, 0, 0.92598, -0.377572, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4415432;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4415432, 181562, 1, 542.308, 349.527, 53.1466, 2.13076, 0, 0, 0.874973, 0.484172, 25, 100, 1, 0, 0);
DELETE FROM `gameobject` WHERE `guid`=4416011;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4416011, 181342, 1, 3863.7, -5383.48, 144, 3.1475, 0, 0, 0.999996, -0.00295142, 0, 100, 1, 0, 0);


-- Some strange DB corrections
UPDATE `quest_template` SET `requiredraces` = 0 WHERE `entry` IN (9319, 9386);
UPDATE `gameobject_template` SET `displayid` = 6756 WHERE `entry` = 181346;
DELETE FROM `quest_template` WHERE `entry`=9319 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9319, 9, 2, -369, 50, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'A Light in Dark Places', 'We are not the only ones who celebrate this holiday, $n. All creatures, all cultures, are touched by the flame. Even in the darkest places, the fires are being lit.$b$bIf you wish to see them for yourself, travel into the depths. Seek out the bonfires burning within Stratholme, Scholomance, among the ogres of Dire Maul, and the halls of Blackrock Spire itself; I will await your return.', 'Find and touch the bonfires located within Blackrock Spire, Dire Maul, Scholomance, and Stratholme, then return to the Festival Flamekeeper.', 'You have proven that you are not entirely useless, mortal.', 'Have you found your way through the dark?', '', 'Flame of Blackrock Spire', 'Flame of Dire Maul', 'Flame of the Scholomance', 'Flame of Stratholme', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -181347, -181346, -181349, -181348, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23083, 23247, 0, 0, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4950);
DELETE FROM `quest_template` WHERE `entry`=9386 AND `patch`=9;
INSERT INTO `quest_template` (`entry`, `patch`, `Method`, `ZoneOrSort`, `MinLevel`, `MaxLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `RewardXP`) VALUES (9386, 9, 2, -369, 50, 60, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 1, 9319, 0, 0, 0, 0, 0, 0, 'A Light in Dark Places', 'An eager one, aren\'t you? If you\'re willing to enter the depths once more, I\'ll gladly reward you.$b$bSeek out the bonfires burning within Stratholme, Scholomance, Dire Maul, and the halls of Blackrock Spire itself; I look forward to your return, $n.', 'Find and touch the bonfires located within Blackrock Spire, Dire Maul, Scholomance, and Stratholme, then speak with the Festival Flamekeeper.', 'You have proven that you are not entirely useless, mortal.', NULL, '', 'Flame of Blackrock Spire', 'Flame of Dire Maul', 'Flame of the Scholomance', 'Flame of Stratholme', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -181347, -181346, -181349, -181348, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23247, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
replace into spell_script_target (entry, type, targetEntry) values (29705, 1, 17066);
-- Update creature movement type
UPDATE `creature_template` SET `MovementType` = 0 WHERE `entry` IN (16781, 16592, 17066);
UPDATE `creature_template` SET `scale` = 0.75, `movementtype` = 0 WHERE `entry` = 17066;
UPDATE `creature` SET `movementtype` = 0 WHERE `id` = 17066;

-- Quest Template Min Level Fix
UPDATE quest_template 
SET minLevel = 1
where entry IN (9388, 9389, 9367, 9368, 9322, 9323);

-- Bonfire fixes
-- DELETE FROM `gameobject` WHERE `guid` IN (50574,
-- DELETE FROM `game_event_gameobject` WHERE `guid` IN (50574,


DELETE FROM `gameobject` WHERE `guid`=4405809;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `spawnFlags`, `visibilitymod`) VALUES (4405809, 181344, 0, -10952.5, -3218.07, 41.348, 1.84775, 0, 0, 0.797945, 0.602731, 25, 100, 1, 0, 0);




-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
