DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20181031155100');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20181031155100');
-- Add your query below.

DROP TABLE IF EXISTS `account_log_ip`;

CREATE TABLE `account_log_ip` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `accountid` int(11) unsigned NOT NULL,
  `ip` varchar(30) NOT NULL DEFAULT '0.0.0.0',
  `date` datetime DEFAULT CURRENT_TIMESTAMP,
  `source` int(11) unsigned NOT NULL DEFAULT '0',
  `error` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `NewIndex1` (`accountid`),
  KEY `source` (`source`),
  KEY `date` (`date`),
  KEY `NewIndex2` (`accountid`,`source`)
) ENGINE=MyISAM AUTO_INCREMENT=2974 DEFAULT CHARSET=latin1;

/*Table structure for table `account_loyalty` */

DROP TABLE IF EXISTS `account_loyalty`;

CREATE TABLE `account_loyalty` (
  `AccountID` int(11) unsigned NOT NULL,
  `LastClaim` int(11) NOT NULL DEFAULT '0',
  `LastEventReset` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`AccountID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

/*Table structure for table `account_loyalty_event` */

DROP TABLE IF EXISTS `account_loyalty_event`;

CREATE TABLE `account_loyalty_event` (
  `AccountID` int(11) unsigned NOT NULL,
  `Event` int(11) unsigned NOT NULL DEFAULT '0',
  `Count` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`AccountID`,`Event`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


-- End of migration.
END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
