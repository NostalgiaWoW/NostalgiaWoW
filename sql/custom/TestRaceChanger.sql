DROP PROCEDURE IF EXISTS insert_racechange_request;
delimiter ??
CREATE PROCEDURE `insert_racechange_request`(TargetPlayer varchar(14), OutfitDonor varchar(14))
BEGIN

DECLARE TargetGUID INT(11) UNSIGNED DEFAULT 1;
DECLARE DonorRace TINYINT;
DECLARE DonorGender TINYINT;
DECLARE DonorPlayerByte1 INT UNSIGNED;
DECLARE DonorPlayerByte2 INT UNSIGNED;

-- get donor race, gender, playerbyte1, playerbyte2
SELECT race, gender, playerBytes, playerBytes2 INTO DonorRace, DonorGender, DonorPlayerByte1, DonorPlayerByte2 FROM `characters` WHERE name LIKE OutfitDonor;

-- get guid of requested player
SELECT guid INTO TargetGUID FROM `characters` WHERE name LIKE TargetPlayer;

INSERT INTO `store_racechange` (`guid`, `race`, `gender`, `playerbytes1`, `playerbytes2`, `transaction`) VALUES (TargetGUID, DonorRace, DonorGender, DonorPlayerByte1, DonorPlayerByte2, '42');

END??
delimiter ;


-- #######INSERT YOU PLAYER NAMES HERE #######
-- CALL insert_racechange_request('Electrik', 'Adon');