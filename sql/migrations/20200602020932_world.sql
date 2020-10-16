DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200602020932');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200602020932');
-- Add your query below.

-- Adding in table for pdump
DROP TABLE IF EXISTS `character_db_version`;
CREATE TABLE `character_db_version` (
  `required_z2753_01_characters_new_ticket_system_sql_created` bit(1) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Last applied sql update to DB';

--

-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
