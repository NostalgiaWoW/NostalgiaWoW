GRANT USAGE ON * . * TO 'elysium'@'localhost' IDENTIFIED BY 'elysium' WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 ;

CREATE DATABASE `world` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
CREATE DATABASE `characters` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
CREATE DATABASE `logon` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
CREATE DATABASE `logs` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;

GRANT ALL PRIVILEGES ON `world` . * TO 'elysium'@'localhost' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `characters` . * TO 'elysium'@'localhost' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `logon` . * TO 'elysium'@'localhost' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `logs` . * TO 'elysium'@'localhost' WITH GRANT OPTION;