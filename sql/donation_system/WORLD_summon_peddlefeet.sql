delete from playercreateinfo_spell where spell = 27570;
update creature_template set scriptname = 'npc_shop', npcflag = 1 where entry = 16085;

replace into playercreateinfo_spell (race, class, spell, note) values

-- Humans
(1, 1, 27570, 'Summon Peddlefeet'),
(1, 2, 27570, 'Summon Peddlefeet'),
(1, 4, 27570, 'Summon Peddlefeet'),
(1, 5, 27570, 'Summon Peddlefeet'),
(1, 8, 27570, 'Summon Peddlefeet'),
(1, 9, 27570, 'Summon Peddlefeet'),
-- Orcs
(2, 1, 27570, 'Summon Peddlefeet'),
(2, 3, 27570, 'Summon Peddlefeet'),
(2, 4, 27570, 'Summon Peddlefeet'),
(2, 7, 27570, 'Summon Peddlefeet'),
(2, 9, 27570, 'Summon Peddlefeet'),
-- Trolls
(8, 1, 27570, 'Summon Peddlefeet'),
(8, 3, 27570, 'Summon Peddlefeet'),
(8, 4, 27570, 'Summon Peddlefeet'),
(8, 5, 27570, 'Summon Peddlefeet'),
(8, 7, 27570, 'Summon Peddlefeet'),
(8, 8, 27570, 'Summon Peddlefeet'),
-- Dwarfs
(3, 1, 27570, 'Summon Peddlefeet'),
(3, 2, 27570, 'Summon Peddlefeet'),
(3, 3, 27570, 'Summon Peddlefeet'),
(3, 4, 27570, 'Summon Peddlefeet'),
(3, 5, 27570, 'Summon Peddlefeet'),
-- Gnomes
(7, 1, 27570, 'Summon Peddlefeet'),
(7, 4, 27570, 'Summon Peddlefeet'),
(7, 8, 27570, 'Summon Peddlefeet'),
(7, 9, 27570, 'Summon Peddlefeet'),
-- Night Elves
(4, 1, 27570, 'Summon Peddlefeet'),
(4, 3, 27570, 'Summon Peddlefeet'),
(4, 4, 27570, 'Summon Peddlefeet'),
(4, 5, 27570, 'Summon Peddlefeet'),
(4, 11, 27570, 'Summon Peddlefeet'),
-- Undeads
(5, 1, 27570, 'Summon Peddlefeet'),
(5, 4, 27570, 'Summon Peddlefeet'),
(5, 5, 27570, 'Summon Peddlefeet'),
(5, 8, 27570, 'Summon Peddlefeet'),
(5, 9, 27570, 'Summon Peddlefeet'),
-- Taurens
(6, 1, 27570, 'Summon Peddlefeet'),
(6, 3, 27570, 'Summon Peddlefeet'),
(6, 7, 27570, 'Summon Peddlefeet'),
(6, 11, 27570, 'Summon Peddlefeet');