delimiter $$
CREATE PROCEDURE `reset_petition_id`()
	LANGUAGE SQL
	NOT DETERMINISTIC
	CONTAINS SQL
	SQL SECURITY DEFINER
BEGIN

 DECLARE maxRow INT UNSIGNED DEFAULT 0;
 DECLARE currRow INT UNSIGNED DEFAULT 0;
 DECLARE oldId INT UNSIGNED DEFAULT 0;

 DROP TABLE IF EXISTS temp_petition;
 CREATE TABLE `temp_petition` (
  `row` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `ownerguid` int(10) unsigned NOT NULL,
  `petitionguid` int(10) unsigned DEFAULT '0',
  `name` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`row`)
 );
 INSERT INTO temp_petition SELECT 0, petition.* FROM petition;

 SET currRow=1;
 SET oldId=0;
 SELECT COUNT(*) FROM temp_petition INTO maxRow;
 
 WHILE currRow <= maxRow DO 
  SELECT petitionguid FROM temp_petition WHERE row = currRow INTO oldId;
  
  UPDATE petition SET petitionguid=currRow WHERE petitionguid=oldId;
  UPDATE petition_sign SET petitionguid=currRow WHERE petitionguid=oldId;
  UPDATE item_instance SET enchantments=CONCAT(currRow,' 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ') WHERE guid=oldId and itemEntry=5863;

  SET currRow = currRow + 1;
 END WHILE;

 DROP TABLE temp_petition;

END$$
delimiter ;