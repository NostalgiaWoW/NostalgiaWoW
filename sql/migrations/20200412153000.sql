DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200412153000');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200412153000');

REPLACE INTO `npc_text` (`ID`, `text0_0`) VALUES 
('1100022', 'Greetings $N! I\'m here to help defeat Noth and get the cure with you and your heroes. Let me know when you\'re ready.');

REPLACE INTO locales_npc_text (entry, Text0_0_loc8) VALUES 
('1100022', 'Привет $N! Я здесь, чтоб помочь тебе и твоим героям победить Нота и забрать у него анти-вирус. Дай мне знать, когда ты решишься идти.');

REPLACE INTO `mangos_string` (`entry`, `content_default`, `content_loc8`) VALUES ('91000', 'Let\'s go!', 'Пошли!');

REPLACE INTO `script_texts` (`entry`, `content_default`, `content_loc8`, type, `comment`) VALUES 
('-1999946', 'CHARGE!!', 
'В АТАКУ!!', 0,'SAY_VIRUS_EVENT_JAINA1'),
('-1999947', 'Kael\'Thas taught me this one. Keep them to me Heroes!', 
'Кель\'Тас научил меня этому. Герои, ведите их ко мне!', 6, 'YELL_VIRUS_EVENT_JAINA2'),
('-1999948', 'Quickly heroes. Time is of the essence. I have opened a portal to each major city - go and cure our citizens of this blight. And ... thank you.', 
'Быстрее, герои. Время имеет весомое значение. Я открыла порталы в крупные города - идите и вылечите наших граждан от этой чумы. И ... спасибо вам.', 0, 'SAY_VIRUS_EVENT_JAINA3'),
('-1999949', 'CHARGE MON!!', 
'А АТАКУ, ЧУВАКИ!!', 0, 'SAY_VIRUS_EVENT_VOLJIN1'),
('-1999950', 'I been savin\' dis one for too long. My brethren! I be slowin them while you pick \'em off!', 
'Я сохранял это слишком долго. Мои братья! Я буду замедлять их, пока вы им не наваляете!', 6, 'YELL_VIRUS_EVENT_VOLJIN2'),
('-1999951', 'Eyyy mon. That be a tough mudda, but we got em good. Take da cure and spread it to our people. I be openin\' portals to each city. Go!', 
'Эй-й-й, чуваки. Это был жуткий засранец, но всё же мы хорошо его отделали. Берите лекарство и раздайте его нашим людям. Я открыл порталы во все города. Идите!', 0, 'SAY_VIRUS_EVENT_VOLJIN3');

REPLACE INTO `creature` (`guid`, `id`, `map`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `spawnFlags`, `visibilitymod`, `patch_min`, `patch_max`) VALUES 
('3000000', '1100022', '533', '0', '1745', '2968.57', '-3470.91', '297.711', '0.803448', '25', '5', '0', '3462000', '612320', '0', '0', '0', '0', '0', '10'),
('3000001', '1100023', '533', '0', '1896', '2966.15', '-3468.55', '297.70', '0.803448', '25', '5', '0', '3462000', '612320', '0', '0', '0', '0', '0', '10');

REPLACE INTO `creature_template` (`entry`, `patch`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Civilian`, `RacialLeader`, `RegenHealth`, `equipment_id`, `trainer_id`, `vendor_id`, `MechanicImmuneMask`, `SchoolImmuneMask`, `flags_extra`, `aggroRadius`, `ScriptName`) VALUES 
('1100023', '0', '0', '0', '10357', '0', '0', '0', 'King Vol\'Jin', 'King of the Darkspear Trolls', '0', '63', '63', '3462000', '3462000', '612320', '612320', '8401', '35', '35', '1', '1.1', '1.14286', '0', '0', '99', '210', '0', '272', '1', '2000', '2000', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '0', '0', '1', '1896', '0', '0', '0', '0', '2', '0', 'virus_event_nax_helper'),
('1100022', '0', '0', '0', '2970', '0', '0', '0', 'Lady Jaina Proudmoore', 'Ruler of Theramore', '0', '63', '63', '3462000', '3462000', '612320', '612320', '8401', '35', '35', '1', '1.25', '1.14286', '0', '3', '571', '737', '0', '290', '1', '2000', '2000', '8', '4160', '0', '0', '0', '0', '0', '0', '220.81', '320.77', '100', '7', '12', '0', '0', '0', '0', '15', '15', '15', '15', '15', '0', '0', '0', '0', '0', '700000', '750000', '', '0', '3', '0', '0', '1', '1745', '0', '0', '617299803', '0', '2', '0', 'virus_event_nax_helper');

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
