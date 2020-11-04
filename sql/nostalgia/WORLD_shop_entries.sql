replace into npc_text (id, text0_0) values ('90000', 'Greetings, welcome to our shop!\nHow can I help you?');

drop table if exists shop_categories;
create table shop_categories (
  id int(11) unsigned not null auto_increment,
  name text,
  primary key (id)
) engine=innodb default charset=utf8;

drop table if exists shop_items;
create table shop_items (
  id int(11) unsigned not null auto_increment,
  category tinyint(3) unsigned not null default '0',
  item int(11) unsigned not null default '0',
  description text,
  price int(11) unsigned default '0',
  primary key (id)
) engine=innodb auto_increment=10 default charset=utf8;

replace into shop_categories values
(1, 'Character Management'),
(2, 'Gameplay: Miscellaneous'),
(3, 'Gameplay: Mounts'),
(4, 'Gameplay: Companions'),
(5, 'Gameplay: Enchantments');

replace into shop_items values
-- Character: General
(100, 1, 40000, 'Character: Rename', 100),
(101, 1, 40001, 'Character: Change Race', 100),
(102, 1, 40002, 'Character: Change Faction', 100),
(103, 1, 40003, 'Summon: Barber Goblin', 100),
(104, 1, 40004, 'Summon: Plastic Surgeon Goblin', 100),
-- Gameplay: Miscellaneous
(200, 2, 40005, 'Summon: Talent Reset', 100),
(201, 2, 40006, 'Summon: Repair Bot', 100),
(202, 2, 40007, 'Summon: Bank (Alliance)', 100),
(203, 2, 40008, 'Summon: Bank (Horde)', 100),
(204, 2, 40009, 'Summon: Auctioneer', 100),
(205, 2, 40010, 'Summon: Mailbox', 100),
(206, 2, 40011, 'Backpack: 28 slots', 100),
(207, 2, 40012, 'Backpack: 36 slots', 100),
-- Gameplay: Mounts 
(300, 3, 23720, 'Riding Turtle', 100),
-- Gameplay: Companions
(400, 4, 20371, 'Blue Murloc Egg', 100),
-- Gameplay: Enchantments
(500, 5, 23548, 'Might of the Scourge', 100);
