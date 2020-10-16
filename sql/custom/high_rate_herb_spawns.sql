
UPDATE  `gameobject` SET spawntimesecs = spawntimesecs / 3
 WHERE `map` != 30 AND                    -- Skip Alterac Valley
       `id` IN (142144,                   -- Ghost Mushroom
                142145, 176637,           -- Gromsblood
                176584, 176639, 180168,   -- Dreamfoil
                176586, 176640, 180166,   -- Mountain Silversage
                176587, 176641,           -- Plaguebloom
                176588,                   -- Icecap
                176589,                   -- Black Lotus
                2042,                     -- Fadeleaf
                1623,                     -- Wild Steelbloom
                1628);                    -- Grave Moss