DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20210115002116');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20210115002116');
-- Add your query below.

DELETE FROM item_template WHERE entry BETWEEN 6001120 AND 6001142;
DELETE FROM item_loot_template WHERE entry BETWEEN 6001120 AND 6001142;

-- Alliance
INSERT INTO `item_template` VALUES (6001120, 0, 15, 0, 'Pre-Raid BiS Mage', 14006, 1, 4, 1, 0, 0, 0, 128, 77, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);

INSERT INTO `item_loot_template` VALUES (6001120, 23318, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 12103, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 23319, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 13386, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 14152, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 11766, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 13253, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 11662, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 23304, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 23291, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 12543, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 13001, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 12930, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 13968, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 13964, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 10796, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001120, 13938, 100, 0, 1, 1, 0);

-- Horde
INSERT INTO `item_template` VALUES (6001121, 0, 15, 0, 'Pre-Raid BiS Mage', 14006, 1, 4, 1, 0, 0, 0, 128, 178, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);

INSERT INTO `item_loot_template` VALUES (6001121, 23263, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 12103, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 23264, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 13386, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 14152, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 11766, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 13253, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 11662, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 22883, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 22860, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 12545, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 13001, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 12930, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 13968, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 13964, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 10796, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001121, 13938, 100, 0, 1, 1, 0);

-- Both
INSERT INTO `item_template` VALUES (6001143, 0, 15, 0, 'Pre-Raid BiS Priest', 14006, 1, 4, 1, 0, 0, 0, 16, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);

INSERT INTO `item_loot_template` VALUES (6001143, 13102, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 18723, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 13013, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 18510, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 14154, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 11766, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 10787, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 18327, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 18386, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 18507, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 16058, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 13178, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 18469, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 18371, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 11923, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 18523, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001143, 18483, 100, 0, 1, 1, 0);

-- Alliance
INSERT INTO `item_template` VALUES (6001122, 0, 15, 0, 'Pre-Raid BiS Priest', 14006, 1, 4, 1, 0, 0, 0, 16, 77, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);

INSERT INTO `item_loot_template` VALUES (6001122, 10504, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 18691, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 14112, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 13386, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 14136, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 11766, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 18407, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 11662, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 13170, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 18735, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 12543, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 13001, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 12930, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 18371, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 13349, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 10796, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001122, 13396, 100, 0, 1, 1, 0);


-- Horde
INSERT INTO `item_template` VALUES (6001123, 0, 15, 0, 'Pre-Raid BiS Priest', 14006, 1, 4, 1, 0, 0, 0, 16, 178, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001123, 10504, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 18691, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 14112, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 13386, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 14136, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 11766, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 18407, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 11662, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 13170, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 18735, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 12543, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 13001, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 12930, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 18371, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 13349, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 10796, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001123, 13396, 100, 0, 1, 1, 0);

-- Horde
INSERT INTO `item_template` VALUES (6001124, 0, 15, 0, 'Pre-Raid BiS Shaman 1', 14006, 1, 4, 1, 0, 0, 0, 64, 178, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);

INSERT INTO `item_loot_template` VALUES (6001124, 10504, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 12103, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 23260, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 18496, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 18385, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 11765, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 13253, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 11662, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 13170, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 18322, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 12545, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 13001, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 12930, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 13968, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001124, 18534, 100, 0, 1, 1, 0);

-- Horde
INSERT INTO `item_template` VALUES (6001125, 0, 15, 0, 'Pre-Raid BiS Shaman 2', 14006, 1, 4, 1, 0, 0, 0, 64, 178, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001125, 13216, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 18723, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 18757, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 13386, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 13346, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 13969, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 18527, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 14553, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 18386, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 13954, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 16058, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 13178, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 18371, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 11923, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001125, 18523, 100, 0, 1, 1, 0);


-- Horde
INSERT INTO `item_template` VALUES (6001126, 0, 15, 0, 'Pre-Raid BiS Shaman 3', 14006, 1, 4, 1, 0, 0, 0, 64, 178, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001126, 12587, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 15411, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 12927, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 13340, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 11726, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 13211, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 13957, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 22232, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 15062, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 14616, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 13098, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 18500, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 13965, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 11815, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001126, 12784, 100, 0, 1, 1, 0);


INSERT INTO `item_template` VALUES (6001127, 0, 15, 0, 'Pre-Raid BiS Warrior 1', 14006, 1, 4, 1, 0, 0, 0, 1, 253, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001127, 12952, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 13091, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 14552, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 18495, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 14624, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 18754, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 13072, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 14620, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 11927, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 14621, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 11669, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 10795, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 11810, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 10779, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 15806, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 12602, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001127, 18323, 100, 0, 1, 1, 0);

INSERT INTO `item_template` VALUES (6001128, 0, 15, 0, 'Pre-Raid BiS Warrior Orc 1', 14006, 1, 4, 1, 0, 0, 0, 1, 2, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001128, 12952, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 13091, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 14552, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 18495, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 14624, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 18754, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 13072, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 14620, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 11927, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 14621, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 11669, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 10795, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 11810, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 10779, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 811, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 12602, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001128, 18323, 100, 0, 1, 1, 0);

INSERT INTO `item_template` VALUES (6001129, 0, 15, 0, 'Pre-Raid BiS Warrior Human', 14006, 1, 4, 1, 0, 0, 0, 1, 1, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001129, 13404, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 15411, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 12927, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 13340, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 11726, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 12936, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 15063, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 13959, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 15062, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 12555, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 17713, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 13098, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 13965, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 11815, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 12940, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 12939, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001129, 18323, 100, 0, 1, 1, 0);

INSERT INTO `item_template` VALUES (6001130, 0, 15, 0, 'Pre-Raid BiS Warrior Orc 2', 14006, 1, 4, 1, 0, 0, 0, 1, 2, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001130, 13404, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 15411, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 12927, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 13340, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 11726, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 12936, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 15063, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 13959, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 15062, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 12555, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 17713, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 13098, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 13965, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 11815, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 811, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 871, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001130, 18323, 100, 0, 1, 1, 0);

INSERT INTO `item_template` VALUES (6001131, 0, 15, 0, 'Pre-Raid BiS Warrior 2', 14006, 1, 4, 1, 0, 0, 0, 1, 251, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001131, 13404, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 15411, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 12927, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 13340, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 11726, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 12936, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 14551, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 13142, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 14554, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 14616, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 17713, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 13098, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 13965, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 11815, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 12940, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 12939, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001131, 18323, 100, 0, 1, 1, 0);

INSERT INTO `item_template` VALUES (6001132, 0, 15, 0, 'Pre-Raid BiS Hunter', 14006, 1, 4, 1, 0, 0, 0, 4, -1, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001132, 18421, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 15411, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 13358, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 13340, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 11726, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 13211, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 15063, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 18393, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 15062, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 13967, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 18500, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 13965, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 18473, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 18520, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001132, 18738, 100, 0, 1, 1, 0);

INSERT INTO `item_template` VALUES (6001133, 0, 15, 0, 'Pre-Raid BiS Paladin 1', 14006, 1, 4, 1, 0, 0, 0, 2, 77, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001133, 18490, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 18723, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 18720, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 18510, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 13346, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 13969, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 18527, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 18702, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 18386, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 18507, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 16058, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 18103, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 11819, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 12930, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 11923, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001133, 18523, 100, 0, 1, 1, 0);

INSERT INTO `item_template` VALUES (6001134, 0, 15, 0, 'Pre-Raid BiS Paladin 2', 14006, 1, 4, 1, 0, 0, 0, 2, 77, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001134, 13404, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 15411, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 12927, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 13340, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 11726, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 12936, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 13957, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 13959, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 14554, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 14616, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 13098, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 12548, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 13965, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 11815, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001134, 12784, 100, 0, 1, 1, 0);

INSERT INTO `item_template` VALUES (6001135, 0, 15, 0, 'Pre-Raid BiS Paladin 3', 14006, 1, 4, 1, 0, 0, 0, 2, 77, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001135, 12952, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 13091, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 14552, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 18495, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 14624, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 18754, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 14622, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 14620, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 14623, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 14621, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 11669, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 10795, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 11810, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 10779, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 18396, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001135, 12602, 100, 0, 1, 1, 0);

INSERT INTO `item_template` VALUES (6001136, 0, 15, 0, 'Pre-Raid BiS Rogue 1', 14006, 1, 4, 1, 0, 0, 0, 8, -1, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001136, 13404, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 13091, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 14552, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 18495, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 14624, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 18754, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 14622, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 14620, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 14623, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 14621, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 11669, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 10795, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 11810, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 10779, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 18396, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001136, 12602, 100, 0, 1, 1, 0);

INSERT INTO `item_template` VALUES (6001137, 0, 15, 0, 'Pre-Raid BiS Rogue 2', 14006, 1, 4, 1, 0, 0, 0, 8, -1, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001137, 13404, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 15411, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 12927, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 13340, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 14637, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 18375, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 15063, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 18505, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 15062, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 12553, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 18500, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 13965, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 11815, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 12783, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 14555, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001137, 18323, 100, 0, 1, 1, 0);

-- Alliance
INSERT INTO `item_template` VALUES (6001138, 0, 15, 0, 'Pre-Raid BiS Warlock', 14006, 1, 4, 1, 0, 0, 0, 256, 77, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001138, 23310, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 18691, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 23311, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 13386, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 14153, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 11766, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 18407, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 11662, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 13170, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 18735, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 12543, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 13001, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 12930, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 18467, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 18372, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 10796, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001138, 13396, 100, 0, 1, 1, 0);

-- Horde
INSERT INTO `item_template` VALUES (6001139, 0, 15, 0, 'Pre-Raid BiS Warlock', 14006, 1, 4, 1, 0, 0, 0, 256, 178, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001139, 23255, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 18691, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 23256, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 13386, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 14153, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 11766, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 18407, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 11662, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 13170, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 18735, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 12545, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 13001, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 12930, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 18467, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 18372, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 10796, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001139, 13396, 100, 0, 1, 1, 0);

INSERT INTO `item_template` VALUES (6001140, 0, 15, 0, 'Pre-Raid BiS Druid 1', 14006, 1, 4, 1, 0, 0, 0, 1024, -1, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001140, 14539, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 13177, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 10783, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 12551, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 15064, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 12966, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 13258, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 13252, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 11821, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 16711, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 15855, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 11669, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 13966, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 11811, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001140, 943, 100, 0, 1, 1, 0);


INSERT INTO `item_template` VALUES (6001141, 0, 15, 0, 'Pre-Raid BiS Druid 2', 14006, 1, 4, 1, 0, 0, 0, 1024, -1, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001141, 8345, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 15411, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 12927, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 13340, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 14637, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 18375, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 15063, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 13252, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 15062, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 12553, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 17713, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 18500, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 13965, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 11815, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001141, 18420, 100, 0, 1, 1, 0);


INSERT INTO `item_template` VALUES (6001142, 0, 15, 0, 'Pre-Raid BiS Druid 3', 14006, 1, 4, 1, 0, 0, 0, 1024, -1, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 'Pre-raid BiS gear!', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);


INSERT INTO `item_loot_template` VALUES (6001142, 13102, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 18723, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 15061, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 18510, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 13346, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 18525, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 10787, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 14553, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 18386, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 13954, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 13178, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 16058, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 18470, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 18371, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 11923, 100, 0, 1, 1, 0);
INSERT INTO `item_loot_template` VALUES (6001142, 18523, 100, 0, 1, 1, 0);

DELETE FROM `npc_vendor` where entry = 1201275;
INSERT INTO `npc_vendor` VALUES 
(1201275, 6001120, 0, 0, 0),
(1201275, 6001121, 0, 0, 0),
(1201275, 6001122, 0, 0, 0),
(1201275, 6001123, 0, 0, 0),
(1201275, 6001124, 0, 0, 0),
(1201275, 6001125, 0, 0, 0),
(1201275, 6001126, 0, 0, 0),
(1201275, 6001127, 0, 0, 0),
(1201275, 6001128, 0, 0, 0),
(1201275, 6001129, 0, 0, 0),
(1201275, 6001130, 0, 0, 0),
(1201275, 6001131, 0, 0, 0),
(1201275, 6001132, 0, 0, 0),
(1201275, 6001133, 0, 0, 0),
(1201275, 6001134, 0, 0, 0),
(1201275, 6001135, 0, 0, 0),
(1201275, 6001136, 0, 0, 0),
(1201275, 6001137, 0, 0, 0),
(1201275, 6001138, 0, 0, 0),
(1201275, 6001139, 0, 0, 0),
(1201275, 6001140, 0, 0, 0),
(1201275, 6001141, 0, 0, 0),
(1201275, 6001142, 0, 0, 0),
(1201275, 6001143, 0, 0, 0); 







-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
