replace into npc_text (id, text0_0) values ('90000', 'Greetings. Welcome to our shop. How can I help you?');

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
(1,  'Character: Rename'),
(2,  'Character: Race'),
(3,  'Character: Faction'),
(4,  'Character: Gender'),
(5,  'Character: Hair Color'),
(6,  'Character: Hair Style'),
(7,  'Character: Skin Color'),
(8,  'Character: Features'),
(9,  'Gameplay: Miscellaneous'),
(10, 'Gameplay: Mounts'),
(11, 'Gameplay: Companions'),
(12, 'Gameplay: Enchantments');

replace into shop_items values
-- Character: General ----------------------------------
(100, 1, 50000, 'Example, do not use.', 160),
(101, 1, 50002, 'Example, do not use.', 200);

