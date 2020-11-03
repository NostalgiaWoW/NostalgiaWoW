
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
set @display = 3020;
set @quality = 1;
set @bonding = 1;
set @stackable = 20;
set @spell = 1575;
set @charges = 0;
set @cooldown = 1000;
set @script = 'shop_brainwashing_device';

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

-- replace into gameobject_template values (1000333, 0, 2, 6424, 'Brainwashing Device', 35, 0, 0.7, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'go_brainwashing_device');

