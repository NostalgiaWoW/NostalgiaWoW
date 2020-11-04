DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180828220122');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180828220122');
-- Add your query below.

-- Remove (non-functional) account name from groupinfo command

UPDATE `mangos_string` SET `content_default`='Group type: %s (ID: %s) Leader: %s Player count: %d Players: %s' WHERE `entry`='640';

-- Cadaverous Worm should not have loot. https://github.com/TrinityCore/TrinityCore/commit/5c04590fddcb84e58fc9f699ccf4723d9aa4fc96

DELETE FROM `creature_loot_template` WHERE `entry`=14370;

UPDATE `creature_template` SET `lootid`=0 WHERE `entry`=14370;
	
-- High Potency Radioactive Fallout should have a 2 hour duration.
-- https://vanillawowdb.com/?quest=2962
-- https://github.com/cmangos/classic-db/commit/66529dfe02cd49efcc2d307f6c2500fae331a55a

UPDATE `item_template` SET `Duration` = 7200 WHERE `entry` = 9365;

-- Scourge Warder has too high chance to drop Essence of Undeath.
-- https://github.com/cmangos/classic-db/commit/b596e265432d9000a3f2ac8272bea8cfc477fd34

UPDATE `creature_loot_template` SET `ChanceOrQuestChance` = 2 WHERE `entry` IN (8525, 8529) AND `item` = 12808;

-- Pattern: Runic Leather Headband should be sold by Jase Farlane. (Limited Supply)
-- https://web.archive.org/web/20060216103740/http://wow.allakhazam.com:80/db/item.html?witem=15756
-- https://github.com/cmangos/classic-db/commit/9190e8384e6a71670928a89800490c875128482f

DELETE FROM `npc_vendor` WHERE `entry` = 12941 AND `item` = 15756;
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`) VALUES (12941, 15756, 1, 3600);

-- Fix Testing Equipment being unusable after completing only 1 of the involved quests.

UPDATE `gameobject_template` SET `flags`=0 WHERE `entry` IN (174848, 175265);
UPDATE `quest_template` SET `PrevQuestId`=0 WHERE `entry` IN (4561, 4661);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
