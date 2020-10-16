DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20180831003815');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20180831003815');
-- Add your query below.

-- This a very shitty solution for the thread stucking issue we faced recently. All the mobs are placed around this spot (.go xyz -8031.19971 -5333.3335 10.25 1 (it's always the same coords, the height can change a bit)) and if the target is standing here creatures simply can't reach it, and the thread stucks. It's trying to find a polygon but can't raycast it, mostlikely beacause of the detour lib bug or weirdly extracted maps.

-- Currently I'm removing the creatures around this corner (but we will mostlikely face other cases with different coordinates, also if it was done intentionally, whoever is doing it will be able just to aggro any other creature on this position. GM should keep an eye on it.) I tried to pull some of the mobs from different places, it's still possible to reproduce the problem. Just more hard to jump over here while being in combat. However, if it's intentionally, people will find a way to crash. Place an invisible wall here for now!

-- More information here:
-- https://cryptpad.fr/code/#/2/code/edit/XEsgO4t0qu4zGOhIW43H2imt/
-- https://cryptpad.fr/code/#/2/code/view/CLnZ3Ajsc9+dsmR7By5-Yb4ucKNkWK4+3hi1QQT9CaE/

delete from creature where guid = 23354;
delete from creature where guid = 23347;
delete from creature where guid = 23340;
delete from creature where guid = 23343;
delete from creature where guid = 23344;
delete from creature where guid = 23363;
delete from creature where guid = 23367;
delete from creature where guid = 23367;
delete from creature where guid = 23307;
delete from creature where guid = 23297;

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
