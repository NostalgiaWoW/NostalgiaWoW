DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190424065720');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190424065720');
-- Add your query below.

DELETE FROM `command` WHERE `name` IN (
'vip list', 'vip aura', 'vip unaura');
INSERT INTO `command` VALUES
('vip list', 6, 'Syntax: .vip list

Show list of all auras that allowed for VIPs', 0),
('vip aura', 0, 'Syntax: .vip aura

Apply one random visual aura from. Only one aura can be active at a time', 0),
('vip unaura', 0, 'Syntax: .vip unaura

Unapply visual aura', 0);

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
