SET @characters_max_guid  = (SELECT MAX(`guid`) FROM `nighthaven_characters`.`characters`);

UPDATE `anathema`.`characters`                  SET `guid` = `guid` + @characters_max_guid;
-- UPDATE `anathema`.`character_achievement`       SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_action`            SET `guid` = `guid` + @characters_max_guid;
-- UPDATE `anathema`.`character_armory_stats`      SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_aura`              SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_battleground_data` SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_homebind`          SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_honor_cp`          SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_instance`          SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_queststatus`       SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_reputation`        SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_skills`            SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_social`            SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_spell`             SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_spell_cooldown`    SET `guid` = `guid` + @characters_max_guid;
UPDATE `anathema`.`character_stats`             SET `guid` = `guid` + @characters_max_guid;
-- UPDATE `anathema`.`character_xp_from_log`       SET `guid` = `guid` + @characters_max_guid;

-- Force rename at login for duplicate names
UPDATE `anathema`.`characters`
  JOIN `nighthaven_characters`.`characters`
SET `anathema`.`characters`.`at_login` = `anathema`.`characters`.`at_login` | '1'
WHERE `anathema`.`characters`.`name` = `nighthaven_characters`.`characters`.`name`;


SET @character_pet_max_id_1 = (SELECT MAX(`id`) FROM `anathema`.`character_pet`);
SET @character_pet_max_id_2 = (SELECT MAX(`id`) FROM `nighthaven_characters`.`character_pet`);

-- hacky but idc
UPDATE `anathema`.`character_pet` SET `id` = `id` + @character_pet_max_id_1 + @character_pet_max_id_2 + 1;
UPDATE `anathema`.`pet_spell`     SET `guid` = `guid` + @character_pet_max_id_1 + @character_pet_max_id_2 + 1;

UPDATE `anathema`.`character_pet` SET `id` = `id` - @character_pet_max_id_1,
                                       `owner` = `owner` + @characters_max_guid;
UPDATE `anathema`.`pet_spell`     SET `guid` = `guid` - @character_pet_max_id_1;


-- SET @guild_max_id  = (SELECT MAX(`guildid`) FROM `nighthaven_characters`.`guild`);

-- UPDATE `anathema`.`guild`        SET `guildid` = `guildid` + @guild_max_id,
--                                      `leaderguid` = `leaderguid` + @characters_max_guid;
-- UPDATE `anathema`.`guild_member` SET `guildid` = `guildid` + @guild_max_id,
--                                      `guid` = `guid` + @characters_max_guid;
-- UPDATE `anathema`.`guild_rank`   SET `guildid` = `guildid` + @guild_max_id;


SET @item_intance_max_guid  = (SELECT MAX(`guid`) FROM `nighthaven_characters`.`item_instance`);

UPDATE `anathema`.`item_instance` SET `guid` = `guid` + @item_intance_max_guid;
UPDATE `anathema`.`item_instance` SET `owner_guid` = `owner_guid` + @characters_max_guid WHERE `owner_guid` != 0;
UPDATE `anathema`.`item_instance` SET `creatorGuid` = `creatorGuid` + @characters_max_guid WHERE `creatorGuid` != 0;
UPDATE `anathema`.`item_instance` SET `giftCreatorGuid` = `giftCreatorGuid` + @characters_max_guid WHERE `giftCreatorGuid` != 0;


UPDATE `anathema`.`character_gifts`     SET `guid` = `guid` + @characters_max_guid,
                                            `item_guid` = `item_guid` + @item_intance_max_guid;
UPDATE `anathema`.`character_inventory` SET `guid` = `guid` + @characters_max_guid,
                                            `item` = `item` + @item_intance_max_guid;
UPDATE `anathema`.`character_inventory` SET `bag` = `bag` + @item_intance_max_guid WHERE `bag` NOT IN (0);


-- SET @mail_max_id  = (SELECT MAX(`id`) FROM `nighthaven_characters`.`mail`);

-- UPDATE `anathema`.`mail`       SET `id` = `id` + @mail_max_id,
--                                    `sender` = `sender` + @characters_max_guid,
--                                    `receiver` = `receiver` + @characters_max_guid;
-- UPDATE `anathema`.`mail_items` SET `mail_id` = `mail_id` + @mail_max_id,
--                                    `item_guid` = `item_guid` + @item_intance_max_guid;


-- SET @auction_max_id  = (SELECT MAX(`id`) FROM `nighthaven_characters`.`auction`);

-- UPDATE `anathema`.`auction` SET `id` = `id` + @auction_max_id,
--                                 `itemguid` = `itemguid` + @item_intance_max_guid,
--                                 `itemowner` = `itemowner` + @characters_max_guid;


-- cleanup from item_intance not imported tables
-- DELETE `item_instance`
-- FROM `item_instance`
-- JOIN `auction` ON `item_instance`.`guid` = `auction`.`itemguid`
-- WHERE `auction`.`itemguid` IS NOT NULL;

-- DELETE `item_instance`
-- FROM `item_instance`
-- JOIN `mail_items` ON `item_instance`.`guid` = `mail_items`.`item_guid`
-- WHERE `mail_items`.`item_guid` IS NOT NULL;
