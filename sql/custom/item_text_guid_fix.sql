-- Fill up missing item_texts with placeholders
insert ignore into item_text select ii.text, '' from item_instance ii
left join item_text it on it.id = ii.text
where it.id IS NULL;

insert ignore into item_text select m.itemTextId, '' from mail m
left join item_text it on it.id = m.itemTextId
where it.id IS NULL;

-- Change engine type
-- ALTER TABLE `item_instance` CHANGE COLUMN `text` `text` INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER `durability`;
ALTER TABLE `item_text` ENGINE=InnoDB;

-- Create cascading foreign keys
ALTER TABLE `mail` ADD CONSTRAINT `FK_mail_item_text` FOREIGN KEY (`itemTextId`) REFERENCES `item_text` (`id`) ON UPDATE CASCADE ON DELETE NO ACTION;
-- ALTER TABLE `item_instance` ADD CONSTRAINT `FK_item_instance_item_text` FOREIGN KEY (`text`) REFERENCES `item_text` (`id`) ON UPDATE CASCADE ON DELETE NO ACTION;

-- Reorganize ids
SET @count = 0;
UPDATE `item_text` SET `id` = @count:= @count + 1;

-- Remove foreign keys
ALTER TABLE `mail` DROP FOREIGN KEY `FK_mail_item_text`;
-- ALTER TABLE `item_instance` DROP FOREIGN KEY `FK_item_instance_item_text`;

-- Revert engine type
ALTER TABLE `item_text` ENGINE=MyISAM;

-- Remove placeholder item_texts
DELETE FROM `item_text` WHERE `text`='';

update item_instance set text = 0;