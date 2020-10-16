-- Old mount system: apprentice/journeyman riding skills were added in 1.12. Before that the whole price was in the mount, they were common items (white) and you could trade them.

-- Patch 1.12.1 (26-Sep-2006): The cost structure and functionality of Riding and Mounts was changed. Prior to that patch, Riding was an ability rather than a secondary Profession, and had only one rank. Each faction had its own riding skill (tiger riding, horse riding, mechanostrider piloting, ram riding) and the cost was 20Gold, available at level 40. Exalted reputation was required to learn cross-faction riding skill, but mounts were Bind on Use and purchasable by anyone for 80Gold. This meant that characters who were PvP rank 3 or higher could pass on the 10% discount directly to other characters by buying the mount for them. This is no longer possible because all mounts are now Bind on Pickup, and the majority of the cost is built into the riding skill training (which is no longer faction-specific) rather than the cost of the mount.

UPDATE item_template SET Quality = 1 WHERE entry IN (
1132,      -- Horn of the Timber Wolf
2414,      -- Pinto Bridle
5655,      -- Chestnut Mare Bridle
5656,      -- Brown Horse Bridle
5665,      -- Horn of the Dire Wolf
5668,      -- Horn of the Brown Wolf
5864,      -- Gray Ram
5872,      -- Brown Ram
2411,      -- Black Stallion Bridle
5873,      -- White Ram
8563,      -- Red Mechanostrider
8586,      -- Whistle of the Mottled Red Raptor
8588,      -- Whistle of the Emerald Raptor
8591,      -- Whistle of the Turquoise Raptor
8592,      -- Whistle of the Violet Raptor
8595,      -- Blue Mechanostrider
8629,      -- Reins of the Striped Nightsaber
8631,      -- Reins of the Striped Frostsaber
8632,      -- Reins of the Spotted Frostsaber
12302,     -- Reins of the Ancient Frostsaber
12303,     -- Reins of the Nightsaber
12330,     -- Horn of the Red Wolf
12351,     -- Horn of the Arctic Wolf
12353,     -- White Stallion Bridle
12354,     -- Palomino Bridle
13317,     -- Whistle of the Ivory Raptor
13321,     -- Green Mechanostrider
13322,     -- Unpainted Mechanostrider
13326,     -- White Mechanostrider Mod A
13327,     -- Icy Blue Mechanostrider Mod A
13328,     -- Black Ram
13329,     -- Frost Ram
13331,     -- Red Skeletal Horse
13332,     -- Blue Skeletal Horse
13333,     -- Brown Skeletal Horse
13334,     -- Green Skeletal Warhorse
15277,     -- Gray Kodo
15290,     -- Brown Kodo
15292,     -- Green Kodo
15293,     -- Teal Kodo
18766,     -- Reins of the Swift Frostsaber
18767,     -- Reins of the Swift Mistsaber
18772,     -- Swift Green Mechanostrider
18773,     -- Swift White Mechanostrider
18774,     -- Swift Yellow Mechanostrider
18776,     -- Swift Palomino
18777,     -- Swift Brown Steed
18778,     -- Swift White Steed
18785,     -- Swift White Ram
18786,     -- Swift Brown Ram
18787,     -- Swift Gray Ram
18788,     -- Swift Blue Raptor
18789,     -- Swift Olive Raptor
18790,     -- Swift Orange Raptor
18791,     -- Purple Skeletal Warhorse
18793,     -- Great White Kodo
18794,     -- Great Brown Kodo
18795,     -- Great Gray Kodo
18796,     -- Horn of the Swift Brown Wolf
18797,     -- Horn of the Swift Timber Wolf
18798,     -- Horn of the Swift Gray Wolf
18902      -- Reins of the Swift Stormsaber
);

UPDATE item_template SET bonding = 3 WHERE entry IN (        -- Change `bonding` back to 1 in 1.12
1132,      -- Horn of the Timber Wolf
2414,      -- Pinto Bridle
5655,      -- Chestnut Mare Bridle
5656,      -- Brown Horse Bridle
5665,      -- Horn of the Dire Wolf
5668,      -- Horn of the Brown Wolf
5864,      -- Gray Ram
5872,      -- Brown Ram
5873,      -- White Ram
8563,      -- Red Mechanostrider
8586,      -- Whistle of the Mottled Red Raptor
8588,      -- Whistle of the Emerald Raptor
8591,      -- Whistle of the Turquoise Raptor
8592,      -- Whistle of the Violet Raptor
8595,      -- Blue Mechanostrider
8629,      -- Reins of the Striped Nightsaber
8631,      -- Reins of the Striped Frostsaber
8632,      -- Reins of the Spotted Frostsaber
12302,     -- Reins of the Ancient Frostsaber
12303,     -- Reins of the Nightsaber
12330,     -- Horn of the Red Wolf
12351,     -- Horn of the Arctic Wolf
12353,     -- White Stallion Bridle
12354,     -- Palomino Bridle
13317,     -- Whistle of the Ivory Raptor
13321,     -- Green Mechanostrider
13322,     -- Unpainted Mechanostrider
13326,     -- White Mechanostrider Mod A
13327,     -- Icy Blue Mechanostrider Mod A
13328,     -- Black Ram
13329,     -- Frost Ram
13331,     -- Red Skeletal Horse
13332,     -- Blue Skeletal Horse
13333,     -- Brown Skeletal Horse
13334,     -- Green Skeletal Warhorse
15277,     -- Gray Kodo
15290,     -- Brown Kodo
15292,     -- Green Kodo
15293,     -- Teal Kodo
18766,     -- Reins of the Swift Frostsaber
18767,     -- Reins of the Swift Mistsaber
18772,     -- Swift Green Mechanostrider
18773,     -- Swift White Mechanostrider
18774,     -- Swift Yellow Mechanostrider
18776,     -- Swift Palomino
18777,     -- Swift Brown Steed
18778,     -- Swift White Steed
18785,     -- Swift White Ram
18786,     -- Swift Brown Ram
18787,     -- Swift Gray Ram
18788,     -- Swift Blue Raptor
18789,     -- Swift Olive Raptor
18790,     -- Swift Orange Raptor
18791,     -- Purple Skeletal Warhorse
18793,     -- Great White Kodo
18794,     -- Great Brown Kodo
18795,     -- Great Gray Kodo
18796,     -- Horn of the Swift Brown Wolf
18797,     -- Horn of the Swift Timber Wolf
18798,     -- Horn of the Swift Gray Wolf
18902      -- Reins of the Swift Stormsaber
);


-- WARNING! Starting this line...DON'T APPLY THIS TWICE!

UPDATE item_template SET BuyPrice = 10000000 WHERE BuyPrice = 1000000 AND entry IN (
1132,      -- Horn of the Timber Wolf
2414,      -- Pinto Bridle
5655,      -- Chestnut Mare Bridle
5656,      -- Brown Horse Bridle
5665,      -- Horn of the Dire Wolf
5668,      -- Horn of the Brown Wolf
5864,      -- Gray Ram
5872,      -- Brown Ram
5873,      -- White Ram
8563,      -- Red Mechanostrider
8586,      -- Whistle of the Mottled Red Raptor
8588,      -- Whistle of the Emerald Raptor
8591,      -- Whistle of the Turquoise Raptor
8592,      -- Whistle of the Violet Raptor
8595,      -- Blue Mechanostrider
8629,      -- Reins of the Striped Nightsaber
8631,      -- Reins of the Striped Frostsaber
8632,      -- Reins of the Spotted Frostsaber
12302,     -- Reins of the Ancient Frostsaber
12303,     -- Reins of the Nightsaber
12330,     -- Horn of the Red Wolf
12351,     -- Horn of the Arctic Wolf
12353,     -- White Stallion Bridle
12354,     -- Palomino Bridle
13317,     -- Whistle of the Ivory Raptor
13321,     -- Green Mechanostrider
13322,     -- Unpainted Mechanostrider
13326,     -- White Mechanostrider Mod A
13327,     -- Icy Blue Mechanostrider Mod A
13328,     -- Black Ram
13329,     -- Frost Ram
13331,     -- Red Skeletal Horse
13332,     -- Blue Skeletal Horse
13333,     -- Brown Skeletal Horse
13334,     -- Green Skeletal Warhorse
15277,     -- Gray Kodo
15290,     -- Brown Kodo
15292,     -- Green Kodo
15293,     -- Teal Kodo
18766,     -- Reins of the Swift Frostsaber
18767,     -- Reins of the Swift Mistsaber
18772,     -- Swift Green Mechanostrider
18773,     -- Swift White Mechanostrider
18774,     -- Swift Yellow Mechanostrider
18776,     -- Swift Palomino
18777,     -- Swift Brown Steed
18778,     -- Swift White Steed
18785,     -- Swift White Ram
18786,     -- Swift Brown Ram
18787,     -- Swift Gray Ram
18788,     -- Swift Blue Raptor
18789,     -- Swift Olive Raptor
18790,     -- Swift Orange Raptor
18791,     -- Purple Skeletal Warhorse
18793,     -- Great White Kodo
18794,     -- Great Brown Kodo
18795,     -- Great Gray Kodo
18796,     -- Horn of the Swift Brown Wolf
18797,     -- Horn of the Swift Timber Wolf
18798,     -- Horn of the Swift Gray Wolf
18902      -- Reins of the Swift Stormsaber
);

UPDATE item_template SET BuyPrice = 1000000 WHERE BuyPrice = 100000 AND entry IN (
1132,      -- Horn of the Timber Wolf
2414,      -- Pinto Bridle
5655,      -- Chestnut Mare Bridle
2411,      -- Black Stallion Bridle
5656,      -- Brown Horse Bridle
5665,      -- Horn of the Dire Wolf
5668,      -- Horn of the Brown Wolf
5864,      -- Gray Ram
5872,      -- Brown Ram
5873,      -- White Ram
8563,      -- Red Mechanostrider
8586,      -- Whistle of the Mottled Red Raptor
8588,      -- Whistle of the Emerald Raptor
8591,      -- Whistle of the Turquoise Raptor
8592,      -- Whistle of the Violet Raptor
8595,      -- Blue Mechanostrider
8629,      -- Reins of the Striped Nightsaber
8631,      -- Reins of the Striped Frostsaber
8632,      -- Reins of the Spotted Frostsaber
12302,     -- Reins of the Ancient Frostsaber
12303,     -- Reins of the Nightsaber
12330,     -- Horn of the Red Wolf
12351,     -- Horn of the Arctic Wolf
12353,     -- White Stallion Bridle
12354,     -- Palomino Bridle
13317,     -- Whistle of the Ivory Raptor
13321,     -- Green Mechanostrider
13322,     -- Unpainted Mechanostrider
13326,     -- White Mechanostrider Mod A
13327,     -- Icy Blue Mechanostrider Mod A
13328,     -- Black Ram
13329,     -- Frost Ram
13331,     -- Red Skeletal Horse
13332,     -- Blue Skeletal Horse
13333,     -- Brown Skeletal Horse
13334,     -- Green Skeletal Warhorse
15277,     -- Gray Kodo
15290,     -- Brown Kodo
15292,     -- Green Kodo
15293,     -- Teal Kodo
18766,     -- Reins of the Swift Frostsaber
18767,     -- Reins of the Swift Mistsaber
18772,     -- Swift Green Mechanostrider
18773,     -- Swift White Mechanostrider
18774,     -- Swift Yellow Mechanostrider
18776,     -- Swift Palomino
18777,     -- Swift Brown Steed
18778,     -- Swift White Steed
18785,     -- Swift White Ram
18786,     -- Swift Brown Ram
18787,     -- Swift Gray Ram
18788,     -- Swift Blue Raptor
18789,     -- Swift Olive Raptor
18790,     -- Swift Orange Raptor
18791,     -- Purple Skeletal Warhorse
18793,     -- Great White Kodo
18794,     -- Great Brown Kodo
18795,     -- Great Gray Kodo
18796,     -- Horn of the Swift Brown Wolf
18797,     -- Horn of the Swift Timber Wolf
18798,     -- Horn of the Swift Gray Wolf
18902      -- Reins of the Swift Stormsaber
);

UPDATE npc_trainer SET spellcost = 90000 WHERE spellcost = 900000 AND entry IN (        -- 9 Gold for Apprentice Riding (temp solution)
4753,     -- Night elf trainer
4732,     -- Human trainer
4772,     -- Dwarf trainer
7954,     -- Gnome trainer
7953,     -- Troll trainer
4752,     -- Orc trainer
4773,     -- Undead trainer
3690      -- Tauren trainer
);

UPDATE npc_trainer SET spellcost = 900000 WHERE spellcost = 9000000 AND entry IN (        -- 90 Gold for Jorneyman Riding (temp solution)
4753,     -- Night elf trainer
4732,     -- Human trainer
4772,     -- Dwarf trainer
7954,     -- Gnome trainer
7953,     -- Troll trainer
4752,     -- Orc trainer
4773,     -- Undead trainer
3690      -- Tauren trainer
);


-- TODO: Each faction had its own riding skill (tiger riding, horse riding, mechanostrider piloting, ram riding) and the cost was 20Gold, available at level 40. Exalted reputation was required to learn cross-faction riding skill, but mounts were Bind on Use and purchasable by anyone for 80 Gold. 