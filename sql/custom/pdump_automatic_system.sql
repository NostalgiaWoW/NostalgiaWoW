DROP TABLE IF EXISTS `pdump_automatic_system`;
CREATE TABLE `pdump_automatic_system` (
  `guid` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `account` int(11) unsigned NOT NULL DEFAULT '0',
  `charGuidOld` int(11) unsigned NOT NULL DEFAULT '0',
  `charGuidNew` int(11) unsigned NOT NULL DEFAULT '0',
  `charName` varchar(12) NOT NULL DEFAULT '',
  `oldRealmId` int(3) unsigned NOT NULL DEFAULT '0',
  `pdump` longtext,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `state` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4;

-- ALTER TABLE `pdump_automatic_system` ADD COLUMN `oldRealmId` INT(3) UNSIGNED NOT NULL DEFAULT 0 AFTER `charName`;
