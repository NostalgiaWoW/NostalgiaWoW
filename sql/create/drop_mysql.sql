REVOKE ALL PRIVILEGES ON * . * FROM 'elysium'@'localhost';

REVOKE ALL PRIVILEGES ON `world` . * FROM 'elysium'@'localhost';
REVOKE GRANT OPTION ON `world` . * FROM 'elysium'@'localhost';

REVOKE ALL PRIVILEGES ON `characters` . * FROM 'elysium'@'localhost';
REVOKE GRANT OPTION ON `characters` . * FROM 'elysium'@'localhost';

REVOKE ALL PRIVILEGES ON `logon` . * FROM 'elysium'@'localhost';
REVOKE GRANT OPTION ON `logon` . * FROM 'elysium'@'localhost';

REVOKE ALL PRIVILEGES ON `logs` . * FROM 'elysium'@'localhost';
REVOKE GRANT OPTION ON `logs` . * FROM 'elysium'@'localhost';

DROP USER 'elysium'@'localhost';

DROP DATABASE IF EXISTS `world`;
DROP DATABASE IF EXISTS `characters`;
DROP DATABASE IF EXISTS `logon`;
DROP DATABASE IF EXISTS `logs`;