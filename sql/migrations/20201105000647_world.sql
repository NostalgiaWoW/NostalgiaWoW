DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201105000647');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201105000647');
-- Add your query below.

update creature_template set minhealth = minhealth*0.50, maxhealth = maxhealth*0.50, mindmg = mindmg*0.8, maxdmg = maxdmg*0.8 where rank > 0 and entry in (select id from creature where map = 30);
update battleground_template set MinPlayersPerTeam = 5 and MaxPlayersPerTeam = 20 where id = 1;

replace into `creature_template` (`entry`, `KillCredit1`, `KillCredit2`, `modelid_1`, `modelid_2`, `modelid_3`, `modelid_4`, `name`, `subname`, `gossip_menu_id`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Civilian`, `RacialLeader`, `RegenHealth`, `equipment_id`, `trainer_id`, `vendor_id`, `MechanicImmuneMask`, `SchoolImmuneMask`, `flags_extra`, `ScriptName`)
values
(120000,'0','0','7209','0','0','0','Gazrik Goldenspark', 'Gambling Master', '0', '50', '50', '4000', '5000','200','300','200','35','35','3','0','0','1','1','687','967','0','226','1','1000','1000','0','0','0','0','0','0','0','0','0','0','200','0','8','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','1','0','0','1','0','0','0','0','0','2','npc_gambling');

replace into npc_text (ID, text0_1) values (120000, 'So you want to gamble, little $c!$B$BTell me how much and I\'ll throw a dice, if the roll is above 50, I will double the bet. If lower than 50, it\'s gone forever. If you win three times in a row using the same amount, the reward is tripled, but only if the 3rd roll is above 75, if below 75 on the 3rd roll, gold will be gone too.');

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
