DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20201123184909');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20201123184909');
-- Add your query below.

CREATE TABLE `pvp_arena_system_stats` (
	`Id` INT(11) UNSIGNED NOT NULL AUTO_INCREMENT,
	`PlayerLowGuid` INT(11) UNSIGNED NOT NULL,
	`ArenaType` TINYINT(3) UNSIGNED NOT NULL,
	`Kills` TINYINT(3) UNSIGNED NOT NULL,
	`Died` TINYINT(3) UNSIGNED NOT NULL,
	`Won` TINYINT(3) UNSIGNED NOT NULL,
	`Lost` TINYINT(3) UNSIGNED NOT NULL,
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
