DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20200403050001');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20200403050001');

-- log table
DROP TABLE IF EXISTS `logs_virus_event`;
CREATE TABLE `logs_virus_event` (
  `char_name` varchar(40) NOT NULL DEFAULT '',
  `infected_player` int(11) unsigned NOT NULL DEFAULT '0',
  `infected_npc` int(11) unsigned NOT NULL DEFAULT '0',
  `infected_go` int(11) unsigned NOT NULL DEFAULT '0',
  `sanitized_player` int(11) unsigned NOT NULL DEFAULT '0',
  `sanitized_npc` int(11) unsigned NOT NULL DEFAULT '0',
  `sanitized_go` int(11) unsigned NOT NULL DEFAULT '0',
  `cured` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`char_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Custom virus event';


END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
