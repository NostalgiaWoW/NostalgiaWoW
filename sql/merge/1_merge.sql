INSERT INTO `nighthaven_characters`.`characters`
(`guid`, `account`, `name`, `race`, `class`, `gender`, `level`, `xp`, `money`, `playerBytes`, `playerBytes2`, `playerFlags`, `position_x`, `position_y`, `position_z`, `map`, `orientation`, `taximask`, `online`, `cinematic`, `totaltime`, `leveltime`, `logout_time`, `is_logout_resting`, `rest_bonus`, `resettalents_multiplier`, `resettalents_time`, `trans_x`, `trans_y`, `trans_z`, `trans_o`, `transguid`, `extra_flags`, `stable_slots`, `at_login`, `zone`, `death_expire_time`, `taxi_path`, `honorRankPoints`, `honorHighestRank`, `honorStanding`, `honorLastWeekHK`, `honorLastWeekCP`, `honorStoredHK`, `honorStoredDK`, `watchedFaction`, `drunk`, `health`, `power1`, `power2`, `power3`, `power4`, `power5`, `exploredZones`, `equipmentCache`, `ammoId`, `actionBars`, `deleteInfos_Account`, `deleteInfos_Name`, `deleteDate`, `area`, `world_phase_mask`, `customFlags`)
SELECT * FROM `anathema`.`characters`;

-- INSERT INTO `nighthaven_characters`.`character_achievement`       SELECT * FROM `anathema`.`character_achievement`;
INSERT INTO `nighthaven_characters`.`character_action`            SELECT * FROM `anathema`.`character_action`;
-- INSERT INTO `nighthaven_characters`.`character_armory_stats`      SELECT * FROM `anathema`.`character_armory_stats`;
INSERT INTO `nighthaven_characters`.`character_aura`              SELECT * FROM `anathema`.`character_aura`;
INSERT INTO `nighthaven_characters`.`character_battleground_data` SELECT * FROM `anathema`.`character_battleground_data`;
INSERT INTO `nighthaven_characters`.`character_homebind`          SELECT * FROM `anathema`.`character_homebind`;
INSERT INTO `nighthaven_characters`.`character_honor_cp`          SELECT * FROM `anathema`.`character_honor_cp`;
INSERT INTO `nighthaven_characters`.`character_instance`          SELECT * FROM `anathema`.`character_instance`;
INSERT INTO `nighthaven_characters`.`character_queststatus`       SELECT * FROM `anathema`.`character_queststatus`;
INSERT INTO `nighthaven_characters`.`character_reputation`        SELECT * FROM `anathema`.`character_reputation`;
INSERT INTO `nighthaven_characters`.`character_skills`            SELECT * FROM `anathema`.`character_skills`;
INSERT INTO `nighthaven_characters`.`character_social`            SELECT * FROM `anathema`.`character_social`;
INSERT INTO `nighthaven_characters`.`character_spell`             SELECT * FROM `anathema`.`character_spell`;
INSERT INTO `nighthaven_characters`.`character_spell_cooldown`    SELECT * FROM `anathema`.`character_spell_cooldown`;
INSERT INTO `nighthaven_characters`.`character_stats`             SELECT * FROM `anathema`.`character_stats`;
-- INSERT INTO `nighthaven_characters`.`character_xp_from_log`       SELECT * FROM `anathema`.`character_xp_from_log`;


INSERT INTO `nighthaven_characters`.`character_pet` SELECT * FROM `anathema`.`character_pet`;
INSERT INTO `nighthaven_characters`.`pet_spell`     SELECT * FROM `anathema`.`pet_spell`;


-- INSERT INTO `nighthaven_characters`.`mail`       SELECT * FROM `anathema`.`mail`;
-- INSERT INTO `nighthaven_characters`.`mail_items` SELECT * FROM `anathema`.`mail_items`;

-- INSERT INTO `nighthaven_characters`.`auction` SELECT * FROM `anathema`.`auction`;


INSERT INTO `nighthaven_characters`.`item_instance`       SELECT * FROM `anathema`.`item_instance`;
INSERT INTO `nighthaven_characters`.`character_gifts`     SELECT * FROM `anathema`.`character_gifts`;
INSERT INTO `nighthaven_characters`.`character_inventory` SELECT * FROM `anathema`.`character_inventory`;