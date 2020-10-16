DROP TABLE IF EXISTS `received_surprise_box`;
CREATE TABLE `received_surprise_box` (
  `guid` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `account` int(11) unsigned NOT NULL DEFAULT '0',
  `charGuid` int(11) unsigned NOT NULL DEFAULT '0',
  `boxSended` int(3) unsigned NOT NULL DEFAULT '0',
  `cdReseted` int(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;
