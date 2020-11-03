
-- Character Management: Rename

set @entry = 40000;
set @class = 15;
set @subclass = 0;
set @name = 'Character: Rename';
set @description = 'Right click to use.';
set @display = 30658;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 1575;
set @charges = -1;
set @cooldown = 1000;
set @script = 'shop_character_rename';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Race Change Token

set @entry = 40001;
set @class = 15;
set @subclass = 0;
set @name = 'Race Change Token';
set @description = 'Use command: .changerace N (where name is a name of a target character you want to look like).';
set @display = 30658;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 0;
set @charges = 0;
set @cooldown = 0;
set @script = '';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Faction Change Token

set @entry = 40002;
set @class = 15;
set @subclass = 0;
set @name = 'Faction Change Token';
set @description = 'Use command: .changerace N (where name is a name of a target character you want to look like).';
set @display = 30658;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 0;
set @charges = 0;
set @cooldown = 0;
set @script = '';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Summon: Brainwashing Device

set @entry = 40005;
set @class = 15;
set @subclass = 0;
set @name = 'Summon: Brainwashing Device';
set @description = 'Right click to use.';
set @display = 7840;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 1575;
set @charges = 0;
set @cooldown = 1000;
set @script = 'shop_brainwashing_device';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Summon: Repair Bot

set @entry = 40006;
set @class = 15;
set @subclass = 0;
set @name = 'Summon: Repair Bot';
set @description = 'Right click to use.';
set @display = 7494;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 28505;
set @charges = 0;
set @cooldown = 1000;
set @script = '';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Summon: Mailbox

set @entry = 40010;
set @class = 15;
set @subclass = 0;
set @name = 'Summon: Mailbox';
set @description = 'Right click to use.';
set @display = 3020;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 1575;
set @charges = 0;
set @cooldown = 1000;
set @script = 'shop_mailbox';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Misc. SQL:

replace into gameobject_template values (1000333, 2, 6424, 'Goblin Brainwashing Device', 35, 0, 0.7, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'go_brainwashing_device');

replace into npc_text (id, text0_0) values('90350', 'Use this to forget your talents.');

replace into creature_template values (60000, 0, 0, 0, 14379, 0, 0, 0, 'Servo', NULL, 0, 50, 50, 3517, 3517, 0, 0, 0, 35, 35, 16389, 0.6, 1.14286, 0, 0, 85, 109, 0, 226, 1, 1510, 1661, 0, 0, 0, 0, 0, 0, 0, 0, 66.44, 91.355, 100, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 1, 3, 0, 0, 1, 0, 0, 0, 8405008, 0, 0, 0, '');

replace into custom_pet_entry_relation (item_entry, creature_entry) VALUES (40006, 60000);

replace into npc_vendor values 
(60000, 5565, 0, 0, 0),
(60000, 16583, 0, 0, 0),
(60000, 17019, 0, 0, 0),
(60000, 17020, 0, 0, 0),
(60000, 17021, 0, 0, 0),
(60000, 17026, 0, 0, 0),
(60000, 17028, 0, 0, 0),
(60000, 17029, 0, 0, 0),
(60000, 17030, 0, 0, 0),
(60000, 17031, 0, 0, 0),
(60000, 17032, 0, 0, 0),
(60000, 17033, 0, 0, 0),
(60000, 17034, 0, 0, 0),
(60000, 17035, 0, 0, 0),
(60000, 17036, 0, 0, 0),
(60000, 17037, 0, 0, 0),
(60000, 17038, 0, 0, 0),
(60000, 21177, 0, 0, 0);


