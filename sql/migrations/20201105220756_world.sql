DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201105220756');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201105220756');
-- Add your query below.

CREATE TABLE IF NOT EXISTS `pvp_arena_system` (
	`Id` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
	`Type` INT(10) UNSIGNED NOT NULL,
	`Radius` FLOAT UNSIGNED NOT NULL,
	`Position_x` FLOAT NOT NULL,
	`Position_y` FLOAT NOT NULL,
	`MapId` INT(10) UNSIGNED NOT NULL,
	PRIMARY KEY (`Id`)
)
COLLATE='utf8_general_ci'
ENGINE=InnoDB
;


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
