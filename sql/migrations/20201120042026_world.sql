DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201120042026');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201120042026');
-- Add your query below.

-- Corrections to vendors

DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 20600; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 20579; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 18544; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 20625; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 20619; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 20637; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 18545; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 20633; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 18546; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 17111; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 18547; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 20621; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200010 AND `item` = 17113; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 21682; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 21696; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 21691; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 21838; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 21648; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 21627; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 21605; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 21708; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 21626; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 21652; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 21707; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 21671; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200013 AND `item` = 21687; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200013 AND `item` = 21467; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200013 AND `item` = 21702; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200013 AND `item` = 21678; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200013 AND `item` = 21464; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200014 AND `item` = 21128; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200014 AND `item` = 21478; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200015 AND `item` = 17110; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200015 AND `item` = 18811; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200015 AND `item` = 17107; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200015 AND `item` = 19139; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200015 AND `item` = 18823; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200015 AND `item` = 18824; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200015 AND `item` = 17102; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200015 AND `item` = 18806; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200015 AND `item` = 18816;
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200016 AND `item` = 18803; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200016 AND `item` = 17077;
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200017 AND `item` = 20581; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200017 AND `item` = 20599;
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200018 AND `item` = 20579; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200019 AND `item` = 19399; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200019 AND `item` = 19433;
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200019 AND `item` = 19439; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200026 AND `item` = 22818; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200026 AND `item` = 22937;
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200026 AND `item` = 22799; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200025 AND `item` = 22943; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200025 AND `item` = 23017;


DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 20882; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 20881; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 20879; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 20878; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 20877; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 20876; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 20875; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200012 AND `item` = 20874; 

DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200013 AND `item` = 21455; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200013 AND `item` = 21710; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200013 AND `item` = 21685; 
DELETE FROM `npc_vendor_template`
WHERE `entry` = 1200013 AND `item` = 21625;  





-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
