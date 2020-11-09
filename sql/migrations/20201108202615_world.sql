DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201108202615');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201108202615');
-- Add your query below.

-- Tier items need to be BOP
UPDATE item_template
SET bonding = 1
WHERE entry IN (16804, 16806, 16825, 16827, 16840, 16838, 16858, 16857,16802, 16799, 16817, 16819, 16861, 16864);



-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
