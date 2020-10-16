#
# SQL Export
# Created by Querious (201048)
# Created: November 22, 2018 at 3:06:48 PM CST
# Encoding: Unicode (UTF-8)
#


SET @PREVIOUS_FOREIGN_KEY_CHECKS = @@FOREIGN_KEY_CHECKS;
SET FOREIGN_KEY_CHECKS = 0;


DROP TABLE IF EXISTS `zk_select`;
DROP TABLE IF EXISTS `zk_lvl30higher`;
DROP TABLE IF EXISTS `zk_emailbatch_1`;
DROP TABLE IF EXISTS `warden_penalty`;
DROP TABLE IF EXISTS `warden_failed`;
DROP TABLE IF EXISTS `warden_checks`;
DROP TABLE IF EXISTS `vote`;
DROP TABLE IF EXISTS `uptime`;
DROP TABLE IF EXISTS `system_fingerprint_usage`;
DROP TABLE IF EXISTS `statistics_online_alt`;
DROP TABLE IF EXISTS `statistics_online`;
DROP TABLE IF EXISTS `statistics_detail`;
DROP TABLE IF EXISTS `realmlist_copy`;
DROP TABLE IF EXISTS `realmlist`;
DROP TABLE IF EXISTS `realmcharacters`;
DROP TABLE IF EXISTS `pdump_automatic_system`;
DROP TABLE IF EXISTS `migrations`;
DROP TABLE IF EXISTS `massmail_unsub`;
DROP TABLE IF EXISTS `massmail_status_old`;
DROP TABLE IF EXISTS `massmail_status_may18`;
DROP TABLE IF EXISTS `massmail_status_mar18`;
DROP TABLE IF EXISTS `massmail_status_jun18`;
DROP TABLE IF EXISTS `massmail_status_jul18`;
DROP TABLE IF EXISTS `massmail_status_firstwave`;
DROP TABLE IF EXISTS `massmail_status_apr18`;
DROP TABLE IF EXISTS `massmail_status`;
DROP TABLE IF EXISTS `ip_banned`;
DROP TABLE IF EXISTS `ip2nationCountries`;
DROP TABLE IF EXISTS `ip2nation`;
DROP TABLE IF EXISTS `emails`;
DROP TABLE IF EXISTS `elysium_lp_log_demo_table`;
DROP TABLE IF EXISTS `elysium_lp_demo_table`;
DROP TABLE IF EXISTS `antispam_unicode_replacement`;
DROP TABLE IF EXISTS `antispam_replacement`;
DROP TABLE IF EXISTS `antispam_regex`;
DROP TABLE IF EXISTS `antispam_normalize_masks`;
DROP TABLE IF EXISTS `antispam_group_scores`;
DROP TABLE IF EXISTS `antispam_detected`;
DROP TABLE IF EXISTS `antispam_client`;
DROP TABLE IF EXISTS `antispam_blacklist`;
DROP TABLE IF EXISTS `agent_queue`;
DROP TABLE IF EXISTS `account_loyalty_event`;
DROP TABLE IF EXISTS `account_loyalty`;
DROP TABLE IF EXISTS `account_log_ip`;
DROP TABLE IF EXISTS `account_emaillog`;
DROP TABLE IF EXISTS `account_banned`;
DROP TABLE IF EXISTS `account_access`;
DROP TABLE IF EXISTS `account_2fa_011117`;
DROP TABLE IF EXISTS `account`;


CREATE TABLE `account` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Identifier',
  `username` varchar(32) NOT NULL,
  `sha_pass_hash` varchar(40) NOT NULL,
  `gmlevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `sessionkey` longtext,
  `v` longtext,
  `s` longtext,
  `reg_mail` text,
  `email` text,
  `joindate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `tfa_verif` varchar(255) DEFAULT NULL,
  `last_ip` varchar(30) NOT NULL DEFAULT '0.0.0.0',
  `last_local_ip` varchar(30) NOT NULL DEFAULT '0.0.0.0',
  `failed_logins` int(11) unsigned NOT NULL DEFAULT '0',
  `locked` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `last_login` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `online` tinyint(4) NOT NULL DEFAULT '0',
  `expansion` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `mutetime` bigint(40) NOT NULL DEFAULT '0',
  `mutereason` varchar(255) NOT NULL DEFAULT '',
  `muteby` varchar(50) NOT NULL DEFAULT '',
  `locale` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `os` varchar(4) NOT NULL DEFAULT '',
  `current_realm` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `banned` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `flags` int(10) unsigned NOT NULL DEFAULT '0',
  `security` varchar(255) DEFAULT NULL,
  `pass_verif` varchar(255) DEFAULT NULL COMMENT 'Web recover password',
  `email_verif` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Email verification',
  `email_check` varchar(255) DEFAULT NULL,
  `elysium_token_enabled` tinyint(1) NOT NULL DEFAULT '0',
  `elysium_email` text,
  `elysium_token` text,
  `nostalrius_token` text,
  `nostalrius_email` text,
  `nostalrius_last_ip` varchar(30) DEFAULT NULL,
  `nostalrius_token_enabled` tinyint(1) NOT NULL DEFAULT '0',
  `nostalrius_recover` tinyint(1) NOT NULL DEFAULT '0',
  `nostalrius_reason` text,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_username` (`username`),
  KEY `idx_gmlevel` (`gmlevel`)
) ENGINE=InnoDB AUTO_INCREMENT=3726579 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Account System';


CREATE TABLE `account_2fa_011117` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Identifier',
  `username` varchar(32) NOT NULL,
  `sha_pass_hash` varchar(40) NOT NULL,
  `gmlevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `sessionkey` longtext,
  `v` longtext,
  `s` longtext,
  `email` text,
  `joindate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `tfa_verif` varchar(255) DEFAULT NULL,
  `last_ip` varchar(30) NOT NULL DEFAULT '0.0.0.0',
  `failed_logins` int(11) unsigned NOT NULL DEFAULT '0',
  `locked` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `last_login` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `online` tinyint(4) NOT NULL DEFAULT '0',
  `expansion` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `mutetime` bigint(40) NOT NULL DEFAULT '0',
  `mutereason` varchar(255) NOT NULL DEFAULT '',
  `muteby` varchar(50) NOT NULL DEFAULT '',
  `locale` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `os` varchar(4) NOT NULL DEFAULT '',
  `current_realm` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `banned` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `flags` int(10) unsigned NOT NULL DEFAULT '0',
  `security` varchar(255) DEFAULT NULL,
  `pass_verif` varchar(255) DEFAULT NULL COMMENT 'Web recover password',
  `email_verif` tinyint(1) NOT NULL DEFAULT '0' COMMENT 'Email verification',
  `email_check` varchar(255) DEFAULT NULL,
  `elysium_token_enabled` tinyint(1) NOT NULL DEFAULT '0',
  `elysium_email` text,
  `elysium_token` text,
  `nostalrius_token` text,
  `nostalrius_email` text,
  `nostalrius_last_ip` varchar(30) DEFAULT NULL,
  `nostalrius_token_enabled` tinyint(1) NOT NULL DEFAULT '0',
  `nostalrius_recover` tinyint(1) NOT NULL DEFAULT '0',
  `nostalrius_reason` text,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_username` (`username`),
  KEY `idx_gmlevel` (`gmlevel`)
) ENGINE=InnoDB AUTO_INCREMENT=3502029 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Account System';


CREATE TABLE `account_access` (
  `id` int(11) unsigned NOT NULL,
  `gmlevel` tinyint(3) unsigned NOT NULL,
  `RealmID` int(11) NOT NULL,
  PRIMARY KEY (`id`,`RealmID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;


CREATE TABLE `account_banned` (
  `id` bigint(20) NOT NULL DEFAULT '0' COMMENT 'Account id',
  `bandate` bigint(40) NOT NULL DEFAULT '0',
  `unbandate` bigint(40) NOT NULL DEFAULT '0',
  `bannedby` varchar(50) NOT NULL,
  `banreason` varchar(255) NOT NULL,
  `active` tinyint(4) NOT NULL DEFAULT '1',
  `realm` tinyint(4) NOT NULL DEFAULT '1',
  `gmlevel` tinyint(4) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`,`bandate`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Ban List';


CREATE TABLE `account_emaillog` (
  `guid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `accountid` int(11) unsigned NOT NULL DEFAULT '0',
  `prev_email` text COLLATE utf8_unicode_ci,
  `new_email` text COLLATE utf8_unicode_ci,
  `date` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB AUTO_INCREMENT=69 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


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


CREATE TABLE `account_loyalty` (
  `AccountID` int(11) unsigned NOT NULL,
  `LastClaim` int(11) NOT NULL DEFAULT '0',
  `LastEventReset` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`AccountID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `account_loyalty_event` (
  `AccountID` int(11) unsigned NOT NULL,
  `Event` int(11) unsigned NOT NULL DEFAULT '0',
  `Count` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`AccountID`,`Event`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `agent_queue` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `opcode` varchar(64) NOT NULL COMMENT 'Opcode of the job to run.',
  `data` text COMMENT 'Data required for the job to run. (optional)',
  `created_at` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'The date and time the job was created.',
  `agent_id` int(11) NOT NULL DEFAULT '0' COMMENT 'Set by the agent currently handling that job.',
  `status` varchar(32) DEFAULT 'pending' COMMENT 'The current status of the job.',
  `status_reason` text COMMENT 'The reason provided for the job status. (optional)',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='Contains jobs for the Elysium agent to run.';


CREATE TABLE `antispam_blacklist` (
  `string` varchar(64) NOT NULL,
  PRIMARY KEY (`string`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `antispam_client` (
  `Regex` varchar(255) NOT NULL,
  `Note` varchar(64) DEFAULT NULL,
  PRIMARY KEY (`Regex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `antispam_detected` (
  `id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `detectScore` mediumint(5) NOT NULL DEFAULT '0',
  `detectTime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `unmuteTime` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `antispam_group_scores` (
  `group` text NOT NULL,
  `score` tinyint(3) unsigned NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `antispam_normalize_masks` (
  `mask` mediumint(5) NOT NULL DEFAULT '0',
  `comment` text,
  PRIMARY KEY (`mask`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `antispam_regex` (
  `regex` varchar(100) NOT NULL DEFAULT '',
  `normalizeMask` mediumint(5) NOT NULL DEFAULT '0',
  PRIMARY KEY (`regex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `antispam_replacement` (
  `from` varchar(32) NOT NULL DEFAULT '',
  `to` varchar(32) NOT NULL DEFAULT '',
  PRIMARY KEY (`from`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `antispam_unicode_replacement` (
  `from` mediumint(5) unsigned NOT NULL DEFAULT '0',
  `to` mediumint(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`from`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `elysium_lp_demo_table` (
  `account_id` int(11) NOT NULL COMMENT 'ID of the Elysium account',
  `loyalty_points` int(11) NOT NULL DEFAULT '0' COMMENT 'Number of loyalty points the player has.',
  PRIMARY KEY (`account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='This is a demo table to test the Loyalty Point system.';


CREATE TABLE `elysium_lp_log_demo_table` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'Operation ID',
  `account_id` int(11) NOT NULL COMMENT 'Account ID the loyalty points were applied to.',
  `loyalty_point_amount` int(11) NOT NULL COMMENT 'Number of loyalty points requested',
  `source_id` varchar(64) DEFAULT NULL COMMENT 'ID of the loyalty point source',
  `source_description` varchar(128) NOT NULL COMMENT 'Description of the source of the loyalty points',
  `attempted_at` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'The date and time the operation was attempted.',
  `loyalty_point_real_diff` int(11) NOT NULL COMMENT 'The number of loyalty points that were actually applied.',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='A demonstration table for recording loyalty points operations.';


CREATE TABLE `emails` (
  `email` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`email`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `ip2nation` (
  `ip` int(11) unsigned NOT NULL DEFAULT '0',
  `country` char(2) NOT NULL DEFAULT '',
  KEY `ip` (`ip`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `ip2nationCountries` (
  `code` varchar(4) NOT NULL DEFAULT '',
  `iso_code_2` varchar(2) NOT NULL DEFAULT '',
  `iso_code_3` varchar(3) DEFAULT '',
  `iso_country` varchar(255) NOT NULL DEFAULT '',
  `country` varchar(255) NOT NULL DEFAULT '',
  `lat` float NOT NULL DEFAULT '0',
  `lon` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`code`),
  KEY `code` (`code`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `ip_banned` (
  `ip` varchar(32) NOT NULL DEFAULT '0.0.0.0',
  `bandate` int(11) NOT NULL,
  `unbandate` int(11) NOT NULL,
  `bannedby` varchar(50) NOT NULL DEFAULT '[Console]',
  `banreason` varchar(128) NOT NULL DEFAULT 'no reason',
  PRIMARY KEY (`ip`,`bandate`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Banned IPs';


CREATE TABLE `massmail_status` (
  `guid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `accid` int(11) unsigned NOT NULL DEFAULT '0',
  `email` varchar(255) DEFAULT NULL,
  `reject` tinyint(3) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`),
  UNIQUE KEY `idx_email` (`email`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=741350 DEFAULT CHARSET=utf8;


CREATE TABLE `massmail_status_apr18` (
  `guid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `accid` int(11) unsigned NOT NULL DEFAULT '0',
  `email` varchar(255) DEFAULT NULL,
  `reject` tinyint(3) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`),
  UNIQUE KEY `idx_email` (`email`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=372659 DEFAULT CHARSET=utf8;


CREATE TABLE `massmail_status_firstwave` (
  `guid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `accid` int(11) unsigned NOT NULL DEFAULT '0',
  `email` varchar(255) DEFAULT NULL,
  `reject` tinyint(3) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`),
  UNIQUE KEY `idx_email` (`email`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=234740 DEFAULT CHARSET=utf8;


CREATE TABLE `massmail_status_jul18` (
  `guid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `accid` int(11) unsigned NOT NULL DEFAULT '0',
  `email` varchar(255) DEFAULT NULL,
  `reject` tinyint(3) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`),
  UNIQUE KEY `idx_email` (`email`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=596689 DEFAULT CHARSET=utf8;


CREATE TABLE `massmail_status_jun18` (
  `guid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `accid` int(11) unsigned NOT NULL DEFAULT '0',
  `email` varchar(255) DEFAULT NULL,
  `reject` tinyint(3) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`),
  UNIQUE KEY `idx_email` (`email`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=511495 DEFAULT CHARSET=utf8;


CREATE TABLE `massmail_status_mar18` (
  `guid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `accid` int(11) unsigned NOT NULL DEFAULT '0',
  `email` varchar(255) DEFAULT NULL,
  `reject` tinyint(3) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`),
  UNIQUE KEY `idx_email` (`email`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=369207 DEFAULT CHARSET=utf8;


CREATE TABLE `massmail_status_may18` (
  `guid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `accid` int(11) unsigned NOT NULL DEFAULT '0',
  `email` varchar(255) DEFAULT NULL,
  `reject` tinyint(3) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`),
  UNIQUE KEY `idx_email` (`email`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=463084 DEFAULT CHARSET=utf8;


CREATE TABLE `massmail_status_old` (
  `guid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `accid` int(11) unsigned NOT NULL DEFAULT '0',
  `email` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `reply` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `emailid` varchar(100) COLLATE utf8_unicode_ci DEFAULT NULL,
  `reject` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`guid`),
  UNIQUE KEY `idx_email` (`email`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=3149 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


CREATE TABLE `massmail_unsub` (
  `guid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `id` int(11) unsigned NOT NULL,
  `email` varchar(255) NOT NULL,
  `ip` varchar(30) CHARACTER SET utf8 COLLATE utf8_unicode_ci DEFAULT NULL,
  `timestamp` int(11) unsigned NOT NULL,
  PRIMARY KEY (`guid`),
  UNIQUE KEY `idx_email` (`email`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=4338 DEFAULT CHARSET=utf8;


CREATE TABLE `migrations` (
  `id` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


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
) ENGINE=InnoDB AUTO_INCREMENT=4634 DEFAULT CHARSET=utf8mb4;


CREATE TABLE `realmcharacters` (
  `realmid` int(11) unsigned NOT NULL DEFAULT '0',
  `acctid` bigint(20) unsigned NOT NULL,
  `numchars` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`realmid`,`acctid`),
  KEY `acctid` (`acctid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Realm Character Tracker';


CREATE TABLE `realmlist` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL DEFAULT '',
  `address` varchar(32) NOT NULL DEFAULT '127.0.0.1',
  `port` int(11) NOT NULL DEFAULT '8085',
  `icon` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `realmflags` tinyint(3) unsigned NOT NULL DEFAULT '2' COMMENT 'Supported masks: 0x1 (invalid, not show in realm list), 0x2 (offline, set by mangosd), 0x4 (show version and build), 0x20 (new players), 0x40 (recommended)',
  `timezone` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `allowedSecurityLevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `population` float unsigned NOT NULL DEFAULT '0',
  `realmbuilds` varchar(64) NOT NULL DEFAULT '5875',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=101 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Realm System';


CREATE TABLE `realmlist_copy` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL DEFAULT '',
  `address` varchar(32) NOT NULL DEFAULT '127.0.0.1',
  `port` int(11) NOT NULL DEFAULT '8085',
  `icon` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `realmflags` tinyint(3) unsigned NOT NULL DEFAULT '2' COMMENT 'Supported masks: 0x1 (invalid, not show in realm list), 0x2 (offline, set by mangosd), 0x4 (show version and build), 0x20 (new players), 0x40 (recommended)',
  `timezone` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `allowedSecurityLevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `population` float unsigned NOT NULL DEFAULT '0',
  `realmbuilds` varchar(64) NOT NULL DEFAULT '5875',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=56 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Realm System';


CREATE TABLE `statistics_detail` (
  `guid` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `value_1` int(8) unsigned DEFAULT '0',
  `value_2` int(8) unsigned DEFAULT '0',
  `value_3` int(8) unsigned DEFAULT '0',
  `value_4` int(8) unsigned DEFAULT '0',
  `type` tinyint(3) DEFAULT NULL,
  `realm` tinyint(3) unsigned DEFAULT '0',
  `date` int(11) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB AUTO_INCREMENT=251 DEFAULT CHARSET=utf8mb4 COMMENT='Type 1 = Active characters (Day/Week)';


CREATE TABLE `statistics_online` (
  `guid` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `online` int(8) unsigned DEFAULT '0',
  `online_alli` int(8) DEFAULT '0',
  `online_horde` int(8) DEFAULT '0',
  `connections` int(8) unsigned DEFAULT '0',
  `realm` tinyint(3) unsigned DEFAULT '0',
  `date` int(11) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB AUTO_INCREMENT=35652 DEFAULT CHARSET=utf8mb4;


CREATE TABLE `statistics_online_alt` (
  `guid` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `online` int(8) unsigned DEFAULT '0',
  `online_alli` int(8) DEFAULT '0',
  `online_horde` int(8) DEFAULT '0',
  `connections` int(8) unsigned DEFAULT '0',
  `realm` tinyint(3) unsigned DEFAULT '0',
  `date` int(11) unsigned DEFAULT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB AUTO_INCREMENT=35652 DEFAULT CHARSET=utf8mb4;


CREATE TABLE `system_fingerprint_usage` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `fingerprint` int(10) unsigned NOT NULL,
  `account` int(10) unsigned NOT NULL,
  `ip` varchar(16) NOT NULL,
  `realm` int(10) unsigned NOT NULL,
  `time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `architecture` varchar(16) DEFAULT NULL,
  `cputype` varchar(64) DEFAULT NULL,
  `activecpus` int(10) unsigned DEFAULT NULL,
  `totalcpus` int(10) unsigned DEFAULT NULL,
  `pagesize` int(10) unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `fingerprint` (`fingerprint`),
  KEY `account` (`account`),
  KEY `ip` (`ip`)
) ENGINE=InnoDB AUTO_INCREMENT=10994852 DEFAULT CHARSET=utf8;


CREATE TABLE `uptime` (
  `realmid` int(11) unsigned NOT NULL,
  `starttime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `startstring` varchar(64) NOT NULL DEFAULT '',
  `uptime` bigint(20) unsigned NOT NULL DEFAULT '0',
  `maxplayers` smallint(5) unsigned NOT NULL DEFAULT '0',
  `revision` varchar(255) NOT NULL DEFAULT 'Trinitycore',
  PRIMARY KEY (`realmid`,`starttime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Uptime system';


CREATE TABLE `vote` (
  `account_id` int(10) unsigned NOT NULL,
  `vote_id` tinyint(4) NOT NULL,
  `updated` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`account_id`,`vote_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `warden_checks` (
  `id` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  `groupId` int(2) unsigned NOT NULL DEFAULT '0',
  `type` int(2) DEFAULT '0',
  `str` text,
  `data` text,
  `address` int(8) DEFAULT '0',
  `length` int(2) DEFAULT '0',
  `result` tinytext NOT NULL,
  `result2` tinytext NOT NULL,
  `build` smallint(5) unsigned NOT NULL DEFAULT '5875',
  `comment` tinytext,
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=126 DEFAULT CHARSET=utf8;


CREATE TABLE `warden_failed` (
  `acc_id` int(11) unsigned NOT NULL,
  `acc_name` varchar(12) NOT NULL DEFAULT '',
  `check_id` int(3) DEFAULT NULL,
  `real_data` tinytext,
  `failed_data` tinytext,
  PRIMARY KEY (`acc_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `warden_penalty` (
  `groupId` smallint(5) NOT NULL,
  `action` tinyint(3) NOT NULL DEFAULT '2',
  `banTime` int(11) NOT NULL DEFAULT '259200',
  `reason` tinytext NOT NULL,
  PRIMARY KEY (`groupId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `zk_emailbatch_1` (
  `email` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `last_login` timestamp NULL DEFAULT NULL,
  `name` varchar(50) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `level` int(12) DEFAULT '0',
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


CREATE TABLE `zk_lvl30higher` (
  `guid` int(12) NOT NULL DEFAULT '0',
  `account` int(12) DEFAULT '0',
  `name` varchar(255) DEFAULT NULL,
  `level` int(12) DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `zk_select` (
  `guid` varchar(255) NOT NULL DEFAULT '0',
  `account` int(12) DEFAULT '0',
  `name` varchar(255) DEFAULT NULL,
  `level` int(8) DEFAULT '0',
  `totaltime` int(12) DEFAULT '0',
  `money` int(12) DEFAULT '0',
  `deleteDate` int(12) DEFAULT NULL,
  `reward_choice` int(12) DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;




SET FOREIGN_KEY_CHECKS = @PREVIOUS_FOREIGN_KEY_CHECKS;


DROP TRIGGER IF EXISTS `account_emaillog`;


DELIMITER //
CREATE DEFINER=`root`@`%` TRIGGER `account_emaillog` AFTER UPDATE ON `account` 
    FOR EACH ROW BEGIN
        IF OLD.email != NEW.email THEN  
            INSERT INTO account_emaillog (prev_email, new_email, accountid, date) VALUES (OLD.email, NEW.email, NEW.id, UNIX_TIMESTAMP(now()));
        END IF;
END;
//
DELIMITER ;




