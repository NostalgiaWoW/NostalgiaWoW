/* Copyright (C) 2006 - 2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_BLACKWING_LAIR
#define DEF_BLACKWING_LAIR

enum
{
    TYPE_RAZORGORE              = 0,
    TYPE_VAELASTRASZ            = 1,
    TYPE_LASHLAYER              = 2,
    TYPE_FIREMAW                = 3,
    TYPE_EBONROC                = 4,
    TYPE_FLAMEGOR               = 5,
    TYPE_CHROMAGGUS             = 6,
    TYPE_NEFARIAN               = 7,
    TYPE_VAEL_EVENT             = 8,
    TYPE_SCEPTER_RUN            = 9,
    MAX_ENCOUNTER               = 10,

    DATA_RAZORGORE_GUID         = 0,
    DATA_VAELASTRASZ_GUID       = 1,
    DATA_LASHLAYER_GUID         = 2,
    DATA_FIREMAW_GUID           = 3,
    DATA_EBONROC_GUID           = 4,
    DATA_FLAMEGOR_GUID          = 5,
    DATA_CHROMAGGUS_GUID        = 6,
    DATA_NEFARIUS_GUID          = 7,
    DATA_NEFARIAN_GUID          = 8,
    DATA_GRETOK_GUID            = 9,
    DATA_TRIGGER_GUID           = 10,
    DATA_ORB_DOMINATION_GUID    = 11,
    DATA_EGG                    = 12,
    DATA_HOW_EGG                = 13,
    DATA_CHROM_BREATH           = 14,
    DATA_NEF_COLOR              = 15,
    DATA_DOOR_RAZORGORE_ENTER   = 16,
    DATA_DOOR_RAZORGORE_EXIT    = 17,
    DATA_DOOR_VAELASTRASZ       = 18,
    DATA_DOOR_LASHLAYER         = 19,
    DATA_DOOR_CHROMAGGUS_ENTER  = 20,
    DATA_DOOR_CHROMAGGUS_EXIT   = 21,
    DATA_DOOR_CHROMAGGUS_SIDE   = 22,
    DATA_DOOR_NEFARIAN          = 23,
    DATA_SCEPTER_CHAMPION       = 24,
    DATA_SCEPTER_RUN_TIME       = 25,
    MAX_DATAS                   = 26,

    // TO FIX : explode at the end
    // Damage done increased by 100%. Attack speed increased by 100%. Spells become instant cast. Reduces max health by 5% every second; eventually causes player to die. Vael only casts Burning Adrenaline in two scenarios: He will cast it on random mana users every 15 seconds and he will cast it on the current tank every 45 seconds. When mana-using raid members are afflicted, they must move away to a designated area or bomb the raid with a 4376 to 5624 AoE blast. Non mana users will not be afflicted unless they are currently tanking Vaelastrasz. Note that ice blocks or divine shield will not prevent this debuff from killing the player.
    SPELL_BURNING_ADRENALINE = 23620, // 18173 ?
};

#endif
