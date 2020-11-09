
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
set @name = 'Deprecated Race Change Token';
set @description = '';
set @display = 30658;
set @quality = 0;
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
set @name = 'Deprecated Faction Change Token';
set @description = '';
set @display = 30658;
set @quality = 0;
set @bonding = 1;
set @stackable = 20;
set @spell = 0;
set @charges = 0;
set @cooldown = 0;
set @script = '';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Summon: Barber

set @entry = 40003;
set @class = 15;
set @subclass = 0;
set @name = 'Summon: Barber';
set @description = '';
set @display = 9825;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 28505;
set @charges = 0;
set @cooldown = 1000;
set @script = '';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Summon: Surgeon

set @entry = 40004;
set @class = 15;
set @subclass = 0;
set @name = 'Summon: Surgeon';
set @description = '';
set @display = 22464;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 28505;
set @charges = 0;
set @cooldown = 1000;
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
set @description = '';
set @display = 7494;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 28505;
set @charges = 0;
set @cooldown = 1000;
set @script = '';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Summon: Bank (Alliance)

set @entry = 40007;
set @class = 15;
set @subclass = 0;
set @name = 'Summon: Bank';
set @description = '';
set @display = 13108;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 28505;
set @charges = 0;
set @cooldown = 1000;
set @script = '';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Summon: Bank (Horde)

set @entry = 40008;
set @class = 15;
set @subclass = 0;
set @name = 'Summon: Bank';
set @description = '';
set @display = 29448;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 28505;
set @charges = 0;
set @cooldown = 1000;
set @script = '';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Summon: Auctioneer

set @entry = 40009;
set @class = 15;
set @subclass = 0;
set @name = 'Summon: Auctioneer';
set @description = '';
set @display = 7260;
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

-- Backpacks

replace into item_template values 
(40011, 0, 1, 0, 'Hexweave Bag', 20709, 4, 0, 1, 320000, 80000, 18, -1, -1, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, '', 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1),

(40012, 0, 1, 0, 'Silkweave Bag', 31783, 4, 0, 1, 320000, 80000, 18, -1, -1, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, '', 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 1);

-- Race Change Token: Human

set @entry = 40013;
set @class = 15;
set @subclass = 0;
set @name = 'Race Change Token: Human';
set @description = 'Right click to use.';
set @display = 30658;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 1575;
set @charges = -1;
set @cooldown = 1000;
set @script = 'shop_racechange';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Race Change Token: Gnome

set @entry = 40014;
set @class = 15;
set @subclass = 0;
set @name = 'Race Change Token: Gnome';
set @description = 'Right click to use.';
set @display = 30658;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 1575;
set @charges = -1;
set @cooldown = 1000;
set @script = 'shop_racechange';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Race Change Token: Dwarf

set @entry = 40015;
set @class = 15;
set @subclass = 0;
set @name = 'Race Change Token: Dwarf';
set @description = 'Right click to use.';
set @display = 30658;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 1575;
set @charges = -1;
set @cooldown = 1000;
set @script = 'shop_racechange';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Race Change Token: Night Elf

set @entry = 40016;
set @class = 15;
set @subclass = 0;
set @name = 'Race Change Token: Night Elf';
set @description = 'Right click to use.';
set @display = 30658;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 1575;
set @charges = -1;
set @cooldown = 1000;
set @script = 'shop_racechange';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Race Change Token: Orc

set @entry = 40017;
set @class = 15;
set @subclass = 0;
set @name = 'Race Change Token: Orc';
set @description = 'Right click to use.';
set @display = 30658;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 1575;
set @charges = -1;
set @cooldown = 1000;
set @script = 'shop_racechange';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Race Change Token: Troll

set @entry = 40018;
set @class = 15;
set @subclass = 0;
set @name = 'Race Change Token: Troll';
set @description = 'Right click to use.';
set @display = 30658;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 1575;
set @charges = -1;
set @cooldown = 1000;
set @script = 'shop_racechange';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Race Change Token: Tauren

set @entry = 40019;
set @class = 15;
set @subclass = 0;
set @name = 'Race Change Token: Tauren';
set @description = 'Right click to use.';
set @display = 30658;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 1575;
set @charges = -1;
set @cooldown = 1000;
set @script = 'shop_racechange';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Race Change Token: Undead

set @entry = 40020;
set @class = 15;
set @subclass = 0;
set @name = 'Race Change Token: Undead';
set @description = 'Right click to use.';
set @display = 30658;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 1575;
set @charges = -1;
set @cooldown = 1000;
set @script = 'shop_racechange';

replace into item_template (entry, class, subclass, name, description, displayid, quality, bonding, stackable, spellid_1, spellcharges_1, spellcooldown_1, scriptname) values (@entry, @class, @subclass, @name, @description, @display, @quality, @bonding, @stackable, @spell, @charges, @cooldown, @script);

-- Misc. SQL:

replace into gameobject_template values (1000333, 2, 6424, 'Goblin Brainwashing Device', 35, 0, 0.7, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'go_brainwashing_device');

replace into npc_text (id, text0_0) values('90350', 'Use this to forget your talents.');
replace into npc_text (id, text0_0) values('90370', 'Hair to cut, coins to count.\n\nThe busy life of a goblin.');
replace into npc_text (id, text0_0) values('90371', 'Hey pal, can’t get no love with that face?\n\n I’ve got what you need.');

replace into creature_template values 

(60000, 0, 0, 0, 14379, 0, 0, 0, 'Servo', NULL, 0, 50, 50, 3517, 3517, 0, 0, 0, 35, 35, 16389, 0.6, 1.14286, 0, 0, 85, 109, 0, 226, 1, 1510, 1661, 0, 0, 0, 0, 0, 0, 0, 0, 66.44, 91.355, 100, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 1, 3, 0, 0, 1, 0, 0, 0, 8405008, 0, 0, 0, ''),

(60001, 0, 0, 0, 16075, 0, 0, 0, 'Caravan Mule', NULL, 0, 55, 55, 4108, 4108, 0, 0, 4500, 120, 120, 256, 1.1, 1.14286, 0, 0, 96, 125, 0, 248, 1, 2000, 2000, 1, 512, 0, 0, 0, 0, 0, 0, 70.664, 97.163, 100, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, ''),

(60002, 0, 0, 0, 7933, 0, 0, 0, 'Caravan Kodo', NULL, 0, 55, 55, 4108, 4108, 0, 0, 4500, 120, 120, 256, 1.1, 1.14286, 0, 0, 96, 125, 0, 248, 1, 2000, 2000, 1, 512, 0, 0, 0, 0, 0, 0, 70.664, 97.163, 100, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, ''),

(60003, 0, 0, 0, 7993, 0, 0, 0, 'Drezbit', NULL, 0, 50, 50, 3517, 3517, 2103, 2103, 2999, 855, 855, 4096, 1.1, 1.14286, 0, 0, 72, 93, 0, 226, 1, 2000, 2000, 1, 4096, 0, 0, 0, 0, 0, 0, 66.44, 91.355, 100, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, ''),

(60004, 0, 0, 0, 7909, 0, 0, 0, 'Sniptip', NULL, 0, 1, 1, 300, 400, 0, 0, 20, 35, 35, 1, 1, 1.14286, 1, 0, 2, 2, 0, 44, 1, 1400, 1900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 'npc_barber'),

(60005, 0, 0, 0, 7212, 0, 0, 0, 'Sharpshear', NULL, 0, 1, 1, 300, 400, 0, 0, 20, 35, 35, 1, 1, 1.14286, 1, 0, 2, 2, 0, 44, 1, 1400, 1900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 'npc_surgeon');


update creature_template set scale = 0.45 where entry = 60001;
update creature_template set scale = 0.5 where entry = 60002;

replace into custom_pet_entry_relation (item_entry, creature_entry) values (40006, 60000);
replace into custom_pet_entry_relation (item_entry, creature_entry) values (40007, 60001);
replace into custom_pet_entry_relation (item_entry, creature_entry) values (40008, 60002);
replace into custom_pet_entry_relation (item_entry, creature_entry) values (40009, 60003);
replace into custom_pet_entry_relation (item_entry, creature_entry) values (40003, 60004);
replace into custom_pet_entry_relation (item_entry, creature_entry) values (40004, 60005);

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

update item_template set allowablerace = 77 where entry = 40007;
update item_template set allowablerace = 178 where entry = 40008;
