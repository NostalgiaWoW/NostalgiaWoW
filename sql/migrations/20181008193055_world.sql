DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181008193055');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181008193055');
-- Add your query below.

-- Added Ultrasafe Transporter: Gadgetzan to vendor Buzzek in Gadgetzan as intended
-- https://classicdb.ch/?npc=8736#teaches-ability:50+1

DELETE FROM `npc_trainer` WHERE `entry`=8736 AND `spell`=23489;
INSERT INTO `npc_trainer` VALUES (8736, 23489, 20000, 202, 260, 0);


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
