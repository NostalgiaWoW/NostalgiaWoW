/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
 * Copyright (C) 2011-2016 Nostalrius <https://nostalrius.org>
 * Copyright (C) 2016-2017 Elysium Project <https://github.com/elysium-project>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _PLAYER_H
#define _PLAYER_H

#include "Common.h"
#include "ItemPrototype.h"
#include "Unit.h"
#include "Item.h"
#include "MapNodes/AbstractPlayer.h"

#include "Database/DatabaseEnv.h"
#include "NPCHandler.h"
#include "QuestDef.h"
#include "Group.h"
#include "Bag.h"
#include "WorldSession.h"
#include "Pet.h"
#include "MapReference.h"
#include "Util.h"                                           // for Tokens typedef
#include "ReputationMgr.h"
#include "BattleGround.h"
#include "DBCStores.h"
#include "SharedDefines.h"
#include "SpellMgr.h"
#include "HonorMgr.h"

#include <string>
#include <vector>
#include <functional>

struct Mail;
class Channel;
class DynamicObject;
class Creature;
class PlayerMenu;
class UpdateMask;
class SpellCastTargets;
class PlayerSocial;
class DungeonPersistentState;
class Spell;
class Item;
class ZoneScript;
class PlayerAI;
class NodeSession;
class PlayerBroadcaster;

#define PLAYER_MAX_SKILLS           127
#define PLAYER_EXPLORED_ZONES_SIZE  64

// Note: SPELLMOD_* values is aura types in fact
enum SpellModType
{
    SPELLMOD_TYPE_NONE    = 0,
    SPELLMOD_FLAT         = 107,                            // SPELL_AURA_ADD_FLAT_MODIFIER
    SPELLMOD_PCT          = 108                             // SPELL_AURA_ADD_PCT_MODIFIER
};

// 2^n values, Player::m_isunderwater is a bitmask. These are mangos internal values, they are never send to any client
enum PlayerUnderwaterState
{
    UNDERWATER_NONE                     = 0x00,
    UNDERWATER_INWATER                  = 0x01,             // terrain type is water and player is afflicted by it
    UNDERWATER_INLAVA                   = 0x02,             // terrain type is lava and player is afflicted by it
    UNDERWATER_INSLIME                  = 0x04,             // terrain type is lava and player is afflicted by it
    UNDERWATER_INDARKWATER              = 0x08,             // terrain type is dark water and player is afflicted by it

    UNDERWATER_EXIST_TIMERS             = 0x10
};

enum BuyBankSlotResult
{
    ERR_BANKSLOT_FAILED_TOO_MANY    = 0,
    ERR_BANKSLOT_INSUFFICIENT_FUNDS = 1,
    ERR_BANKSLOT_NOTBANKER          = 2,
    ERR_BANKSLOT_OK                 = 3
};

enum PlayerSpellState
{
    PLAYERSPELL_UNCHANGED = 0,
    PLAYERSPELL_CHANGED   = 1,
    PLAYERSPELL_NEW       = 2,
    PLAYERSPELL_REMOVED   = 3
};

struct PlayerSpell
{
    PlayerSpellState state : 8;
    bool active            : 1;                             // show in spellbook
    bool dependent         : 1;                             // learned as result another spell learn, skill grow, quest reward, etc
    bool disabled          : 1;                             // first rank has been learned in result talent learn but currently talent unlearned, save max learned ranks
};

typedef std::unordered_map<uint32, PlayerSpell> PlayerSpellMap;

// Spell modifier (used for modify other spells)
struct SpellModifier
{
    SpellModifier() : charges(0), ownerAura(NULL), value(0), spellId(0), op(MAX_SPELLMOD), type(SPELLMOD_TYPE_NONE) {}

    SpellModifier(SpellModOp _op, SpellModType _type, int32 _value, uint32 _spellId, uint64 _mask, int16 _charges = 0)
        : op(_op), type(_type), charges(_charges), value(_value), mask(_mask), spellId(_spellId), ownerAura(NULL)
    {}

    SpellModifier(SpellModOp _op, SpellModType _type, int32 _value, uint32 _spellId, ClassFamilyMask _mask, int16 _charges = 0)
        : op(_op), type(_type), charges(_charges), value(_value), mask(_mask), spellId(_spellId), ownerAura(NULL)
    {}

    SpellModifier(SpellModOp _op, SpellModType _type, int32 _value, SpellEntry const* spellEntry, SpellEffectIndex eff, int16 _charges = 0);

    SpellModifier(SpellModOp _op, SpellModType _type, int32 _value, Aura* aura, int16 _charges = 0);

    bool isAffectedOnSpell(SpellEntry const *spell) const;

    SpellModOp   op   : 8;
    SpellModType type : 8;
    int16 charges     : 16; // 0 = infini, negatif = plus de charge.
    int32 value;
    ClassFamilyMask mask;
    uint32 spellId;
    Aura* ownerAura;
};

typedef std::list<SpellModifier*> SpellModList;

enum TrainerSpellState
{
    TRAINER_SPELL_GREEN = 0,
    TRAINER_SPELL_RED   = 1,
    TRAINER_SPELL_GRAY  = 2,
    TRAINER_SPELL_GREEN_DISABLED = 10                       // custom value, not send to client: formally green but learn not allowed
};

enum ActionButtonUpdateState
{
    ACTIONBUTTON_UNCHANGED = 0,
    ACTIONBUTTON_CHANGED   = 1,
    ACTIONBUTTON_NEW       = 2,
    ACTIONBUTTON_DELETED   = 3
};

enum ActionButtonType
{
    ACTION_BUTTON_SPELL     = 0x00,
    ACTION_BUTTON_C         = 0x01,                         // click?
    ACTION_BUTTON_MACRO     = 0x40,
    ACTION_BUTTON_CMACRO    = ACTION_BUTTON_C | ACTION_BUTTON_MACRO,
    ACTION_BUTTON_ITEM      = 0x80
};

#define ACTION_BUTTON_ACTION(X) (uint32(X) & 0x00FFFFFF)
#define ACTION_BUTTON_TYPE(X)   ((uint32(X) & 0xFF000000) >> 24)
#define MAX_ACTION_BUTTON_ACTION_VALUE (0x00FFFFFF+1)

struct ActionButton
{
    ActionButton() : packedData(0), uState( ACTIONBUTTON_NEW ) {}

    uint32 packedData;
    ActionButtonUpdateState uState;

    // helpers
    ActionButtonType GetType() const { return ActionButtonType(ACTION_BUTTON_TYPE(packedData)); }
    uint32 GetAction() const { return ACTION_BUTTON_ACTION(packedData); }
    void SetActionAndType(uint32 action, ActionButtonType type)
    {
        uint32 newData = action | (uint32(type) << 24);
        if (newData != packedData || uState == ACTIONBUTTON_DELETED)
        {
            packedData = newData;
            if (uState != ACTIONBUTTON_NEW)
                uState = ACTIONBUTTON_CHANGED;
        }
    }
};

#define  MAX_ACTION_BUTTONS 120   // TBC 132 checked in 2.3.0

struct PlayerCreateInfoItem
{
    PlayerCreateInfoItem(uint32 id, uint32 amount) : item_id(id), item_amount(amount) {}

    uint32 item_id;
    uint32 item_amount;
};

typedef std::list<PlayerCreateInfoItem> PlayerCreateInfoItems;

struct PlayerClassLevelInfo
{
    PlayerClassLevelInfo() : basehealth(0), basemana(0) {}
    uint16 basehealth;
    uint16 basemana;
};

struct PlayerClassInfo
{
    PlayerClassInfo() : levelInfo(NULL) { }

    PlayerClassLevelInfo* levelInfo;                        //[level-1] 0..MaxPlayerLevel-1
};

struct PlayerLevelInfo
{
    PlayerLevelInfo() { for(int i=0; i < MAX_STATS; ++i ) stats[i] = 0; }

    uint8 stats[MAX_STATS];
};

typedef std::list<uint32> PlayerCreateInfoSpells;

struct PlayerCreateInfoAction
{
    PlayerCreateInfoAction() : button(0), type(0), action(0) {}
    PlayerCreateInfoAction(uint8 _button, uint32 _action, uint8 _type) : button(_button), type(_type), action(_action) {}

    uint8 button;
    uint8 type;
    uint32 action;
};

typedef std::list<PlayerCreateInfoAction> PlayerCreateInfoActions;

struct PlayerInfo
{
                                                            // existence checked by displayId != 0             // existence checked by displayId != 0
    PlayerInfo() : displayId_m(0), displayId_f(0), levelInfo(NULL), mapId(0), areaId(0), positionX(0), positionY(0), positionZ(0), orientation(0)
    {
    }

    uint32 mapId;
    uint32 areaId;
    float positionX;
    float positionY;
    float positionZ;
    float orientation;
    uint16 displayId_m;
    uint16 displayId_f;
    PlayerCreateInfoItems item;
    PlayerCreateInfoSpells spell;
    PlayerCreateInfoActions action;

    PlayerLevelInfo* levelInfo;                             //[level-1] 0..MaxPlayerLevel-1
};

struct PvPInfo
{
    PvPInfo() : inHostileArea(false), endTimer(0) {}

    bool inHostileArea;
    time_t endTimer;
};

struct DuelInfo
{
    DuelInfo() : initiator(NULL), opponent(NULL), startTimer(0), startTime(0), outOfBound(0), finished(false), transportGuid(0) {}

    Player *initiator;
    Player *opponent;
    time_t startTimer;
    time_t startTime;
    time_t outOfBound;
    uint32 transportGuid;
    bool finished;
};

struct Areas
{
    uint32 areaID;
    uint32 areaFlag;
    float x1;
    float x2;
    float y1;
    float y2;
};

struct EnchantDuration
{
    EnchantDuration() : item(NULL), slot(MAX_ENCHANTMENT_SLOT), leftduration(0) {};
    EnchantDuration(Item * _item, EnchantmentSlot _slot, uint32 _leftduration) : item(_item), slot(_slot), leftduration(_leftduration) { MANGOS_ASSERT(item); };

    Item * item;
    EnchantmentSlot slot;
    uint32 leftduration;
};

typedef std::list<EnchantDuration> EnchantDurationList;
typedef std::list<Item*> ItemDurationList;

enum RaidGroupError
{
    ERR_RAID_GROUP_REQUIRED = 1,
    ERR_RAID_GROUP_FULL     = 2
};

enum DrunkenState
{
    DRUNKEN_SOBER   = 0,
    DRUNKEN_TIPSY   = 1,
    DRUNKEN_DRUNK   = 2,
    DRUNKEN_SMASHED = 3
};

#define MAX_DRUNKEN   4

enum PlayerFlags
{
    PLAYER_FLAGS_NONE                   = 0x00000000,
    PLAYER_FLAGS_GROUP_LEADER           = 0x00000001,
    PLAYER_FLAGS_AFK                    = 0x00000002,
    PLAYER_FLAGS_DND                    = 0x00000004,
    PLAYER_FLAGS_GM                     = 0x00000008,
    PLAYER_FLAGS_GHOST                  = 0x00000010,
    PLAYER_FLAGS_RESTING                = 0x00000020,
    PLAYER_FLAGS_UNK7                   = 0x00000040,       // admin?
    PLAYER_FLAGS_FFA_PVP                = 0x00000080,
    PLAYER_FLAGS_CONTESTED_PVP          = 0x00000100,       // Player has been involved in a PvP combat and will be attacked by contested guards
    PLAYER_FLAGS_IN_PVP                 = 0x00000200,
    PLAYER_FLAGS_HIDE_HELM              = 0x00000400,
    PLAYER_FLAGS_HIDE_CLOAK             = 0x00000800,
    PLAYER_FLAGS_PARTIAL_PLAY_TIME      = 0x00001000,       // played long time
    PLAYER_FLAGS_NO_PLAY_TIME           = 0x00002000,       // played too long time
    PLAYER_FLAGS_UNK15                  = 0x00004000,
    PLAYER_FLAGS_UNK16                  = 0x00008000,       // strange visual effect (2.0.1), looks like PLAYER_FLAGS_GHOST flag
    PLAYER_FLAGS_SANCTUARY              = 0x00010000,       // player entered sanctuary
    PLAYER_FLAGS_TAXI_BENCHMARK         = 0x00020000,       // taxi benchmark mode (on/off) (2.0.1)
    PLAYER_FLAGS_PVP_TIMER              = 0x00040000,       // 3.0.2, pvp timer active (after you disable pvp manually)
};

enum PlayerDynamicFlags
{
    PLAYER_DYNFLAG_NONE                 = 0x00000000,
    PLAYER_DYNFLAG_XP_STOP              = 0x00000001,
    PLAYER_DYNFLAG_XP2                  = 0x00000002,
    PLAYER_DYNFLAG_XP3                  = 0x00000004,
    PLAYER_DYNFLAG_XP5                  = 0x00000008
};

enum PlayerDonateTokens
{
    TOKEN_XP_STOP                       = 55555,
    TOKEN_XP_X2_UNLIM                   = 50013,
    TOKEN_XP_X2_1DAY                    = 55568,
    TOKEN_XP_X2_7DAYS                   = 55569,
    TOKEN_XP_X3                         = 50014,
    TOKEN_XP_X5                         = 50015
};

// used in (PLAYER_FIELD_BYTES, 0) byte values
enum PlayerFieldByteFlags
{
    PLAYER_FIELD_BYTE_TRACK_STEALTHED   = 0x02,
    PLAYER_FIELD_BYTE_RELEASE_TIMER     = 0x08,             // Display time till auto release spirit
    PLAYER_FIELD_BYTE_NO_RELEASE_WINDOW = 0x10              // Display no "release spirit" window at all
};

// used in byte (PLAYER_FIELD_BYTES2,1) values
enum PlayerFieldByte2Flags
{
    PLAYER_FIELD_BYTE2_NONE              = 0x00,
    PLAYER_FIELD_BYTE2_STEALTH           = 0x20,
    PLAYER_FIELD_BYTE2_INVISIBILITY_GLOW = 0x40
};

enum ActivateTaxiReplies
{
    ERR_TAXIOK                      = 0,
    ERR_TAXIUNSPECIFIEDSERVERERROR  = 1,
    ERR_TAXINOSUCHPATH              = 2,
    ERR_TAXINOTENOUGHMONEY          = 3,
    ERR_TAXITOOFARAWAY              = 4,
    ERR_TAXINOVENDORNEARBY          = 5,
    ERR_TAXINOTVISITED              = 6,
    ERR_TAXIPLAYERBUSY              = 7,
    ERR_TAXIPLAYERALREADYMOUNTED    = 8,
    ERR_TAXIPLAYERSHAPESHIFTED      = 9,
    ERR_TAXIPLAYERMOVING            = 10,
    ERR_TAXISAMENODE                = 11,
    ERR_TAXINOTSTANDING             = 12
};

enum MirrorTimerType
{
    FATIGUE_TIMER      = 0,
    BREATH_TIMER       = 1,
    FIRE_TIMER         = 2
};
#define MAX_TIMERS      3
#define DISABLED_MIRROR_TIMER   -1

// 2^n values
enum AtLoginFlags
{
    AT_LOGIN_NONE              = 0x00,
    AT_LOGIN_RENAME            = 0x01,
    AT_LOGIN_RESET_SPELLS      = 0x02,
    AT_LOGIN_RESET_TALENTS     = 0x04,
    //AT_LOGIN_CUSTOMIZE         = 0x08, -- used in post-3.x
    //AT_LOGIN_RESET_PET_TALENTS = 0x10, -- used in post-3.x
    AT_LOGIN_FIRST             = 0x20,
};

// Nostalrius
enum PlayerCheatOptions
{
    PLAYER_CHEAT_GOD           = 0x001,
    PLAYER_CHEAT_NO_COOLDOWN   = 0x002,
    PLAYER_CHEAT_NO_CAST_TIME  = 0x004,
    PLAYER_CHEAT_NO_POWER      = 0x008,
    PLAYER_CHEAT_NO_MOD_SPEED  = 0x010,
    PLAYER_CHEAT_ALWAYS_CRIT   = 0x020,
    PLAYER_CHEAT_NO_CHECK_CAST = 0x040,
    PLAYER_CHEAT_ALWAYS_PROC   = 0x080,
    PLAYER_VIDEO_MODE          = 0x100,
    PLAYER_CHEAT_UNRANDOMIZE   = 0x200,
};

typedef std::map<uint32, QuestStatusData> QuestStatusMap;

enum QuestSlotOffsets
{
    QUEST_ID_OFFSET           = 0,
    QUEST_COUNT_STATE_OFFSET  = 1,                          // including counters 6bits+6bits+6bits+6bits + state 8bits
    QUEST_TIME_OFFSET         = 2
};

#define MAX_QUEST_OFFSET 3

enum QuestSlotStateMask
{
    QUEST_STATE_NONE     = 0x0000,
    QUEST_STATE_COMPLETE = 0x0001,
    QUEST_STATE_FAIL     = 0x0002
};

enum SkillUpdateState
{
    SKILL_UNCHANGED     = 0,
    SKILL_CHANGED       = 1,
    SKILL_NEW           = 2,
    SKILL_DELETED       = 3
};

struct SkillStatusData
{
    SkillStatusData(uint8 _pos, SkillUpdateState _uState) : pos(_pos), uState(_uState)
    {
    }
    uint8 pos;
    SkillUpdateState uState;
};

typedef std::unordered_map<uint32, SkillStatusData> SkillStatusMap;

enum PlayerSlots
{
    // first slot for item stored (in any way in player m_items data)
    PLAYER_SLOT_START           = 0,
    // last+1 slot for item stored (in any way in player m_items data)
    PLAYER_SLOT_END             = 118,
    PLAYER_SLOTS_COUNT          = (PLAYER_SLOT_END - PLAYER_SLOT_START)
};

#define INVENTORY_SLOT_BAG_0    255

enum EquipmentSlots                                         // 19 slots
{
    EQUIPMENT_SLOT_START        = 0,
    EQUIPMENT_SLOT_HEAD         = 0,
    EQUIPMENT_SLOT_NECK         = 1,
    EQUIPMENT_SLOT_SHOULDERS    = 2,
    EQUIPMENT_SLOT_BODY         = 3,
    EQUIPMENT_SLOT_CHEST        = 4,
    EQUIPMENT_SLOT_WAIST        = 5,
    EQUIPMENT_SLOT_LEGS         = 6,
    EQUIPMENT_SLOT_FEET         = 7,
    EQUIPMENT_SLOT_WRISTS       = 8,
    EQUIPMENT_SLOT_HANDS        = 9,
    EQUIPMENT_SLOT_FINGER1      = 10,
    EQUIPMENT_SLOT_FINGER2      = 11,
    EQUIPMENT_SLOT_TRINKET1     = 12,
    EQUIPMENT_SLOT_TRINKET2     = 13,
    EQUIPMENT_SLOT_BACK         = 14,
    EQUIPMENT_SLOT_MAINHAND     = 15,
    EQUIPMENT_SLOT_OFFHAND      = 16,
    EQUIPMENT_SLOT_RANGED       = 17,
    EQUIPMENT_SLOT_TABARD       = 18,
    EQUIPMENT_SLOT_END          = 19
};

enum InventorySlots                                         // 4 slots
{
    INVENTORY_SLOT_BAG_START    = 19,
    INVENTORY_SLOT_BAG_END      = 23
};

enum InventoryPackSlots                                     // 16 slots
{
    INVENTORY_SLOT_ITEM_START   = 23,
    INVENTORY_SLOT_ITEM_END     = 39
};

enum BankItemSlots                                          // 28 slots
{
    BANK_SLOT_ITEM_START        = 39,
    BANK_SLOT_ITEM_END          = 63
};

enum BankBagSlots                                           // 6 slots
{
    BANK_SLOT_BAG_START         = 63,
    BANK_SLOT_BAG_END           = 69
};

enum BuyBackSlots                                           // 12 slots
{
    // stored in m_buybackitems
    BUYBACK_SLOT_START          = 69,
    BUYBACK_SLOT_END            = 81
};

enum KeyRingSlots                                           // 32 slots
{
    KEYRING_SLOT_START          = 81,
    KEYRING_SLOT_END            = 97
};

struct ItemPosCount
{
    ItemPosCount(uint16 _pos, uint8 _count) : pos(_pos), count(_count) {}
    bool isContainedIn(std::vector<ItemPosCount> const& vec) const;
    uint16 pos;
    uint8 count;
};
typedef std::vector<ItemPosCount> ItemPosCountVec;

enum TradeSlots
{
    TRADE_SLOT_COUNT            = 7,
    TRADE_SLOT_TRADED_COUNT     = 6,
    TRADE_SLOT_NONTRADED        = 6,
    TRADE_SLOT_INVALID          = -1
};

enum TransferAbortReason
{
    TRANSFER_ABORT_MAX_PLAYERS                  = 0x01,     // Transfer Aborted: instance is full
    TRANSFER_ABORT_NOT_FOUND                    = 0x02,     // Transfer Aborted: instance not found
    TRANSFER_ABORT_TOO_MANY_INSTANCES           = 0x03,     // You have entered too many instances recently.
    TRANSFER_ABORT_SILENTLY                     = 0x04,     // no message shown; the same effect give values above 5
    TRANSFER_ABORT_ZONE_IN_COMBAT               = 0x05,     // Unable to zone in while an encounter is in progress.
};

enum InstanceResetWarningType
{
    RAID_INSTANCE_WARNING_HOURS     = 1,                    // WARNING! %s is scheduled to reset in %d hour(s).
    RAID_INSTANCE_WARNING_MIN       = 2,                    // WARNING! %s is scheduled to reset in %d minute(s)!
    RAID_INSTANCE_WARNING_MIN_SOON  = 3,                    // WARNING! %s is scheduled to reset in %d minute(s). Please exit the zone or you will be returned to your bind location!
    RAID_INSTANCE_WELCOME           = 4                     // Welcome to %s. This raid instance is scheduled to reset in %s.
};

enum RestType
{
    REST_TYPE_NO        = 0,
    REST_TYPE_IN_TAVERN = 1,
    REST_TYPE_IN_CITY   = 2
};

enum DuelCompleteType
{
    DUEL_INTERUPTED = 0,
    DUEL_WON        = 1,
    DUEL_FLED       = 2
};

/// Type of environmental damages
enum EnvironmentalDamageType
{
    DAMAGE_EXHAUSTED = 0,
    DAMAGE_DROWNING  = 1,
    DAMAGE_FALL      = 2,
    DAMAGE_LAVA      = 3,
    DAMAGE_SLIME     = 4,
    DAMAGE_FIRE      = 5,
    DAMAGE_FALL_TO_VOID = 6                                 // custom case for fall without durability loss
};

enum PlayedTimeIndex
{
    PLAYED_TIME_TOTAL = 0,
    PLAYED_TIME_LEVEL = 1
};

#define MAX_PLAYED_TIME_INDEX 2

// used at player loading query list preparing, and later result selection
enum PlayerLoginQueryIndex
{
    PLAYER_LOGIN_QUERY_LOADFROM,
    PLAYER_LOGIN_QUERY_LOADGROUP,
    PLAYER_LOGIN_QUERY_LOADBOUNDINSTANCES,
    PLAYER_LOGIN_QUERY_LOADAURAS,
    PLAYER_LOGIN_QUERY_LOADSPELLS,
    PLAYER_LOGIN_QUERY_LOADQUESTSTATUS,
    PLAYER_LOGIN_QUERY_LOADHONORCP,
    PLAYER_LOGIN_QUERY_LOADREPUTATION,
    PLAYER_LOGIN_QUERY_BROKEN_ITEMS,
    PLAYER_LOGIN_QUERY_LOADINVENTORY,
    PLAYER_LOGIN_QUERY_LOADITEMLOOT,
    PLAYER_LOGIN_QUERY_LOADACTIONS,
    PLAYER_LOGIN_QUERY_LOADSOCIALLIST,
    PLAYER_LOGIN_QUERY_LOADHOMEBIND,
    PLAYER_LOGIN_QUERY_LOADSPELLCOOLDOWNS,
    PLAYER_LOGIN_QUERY_LOADGUILD,
    PLAYER_LOGIN_QUERY_LOADBGDATA,
    PLAYER_LOGIN_QUERY_LOADSKILLS,
    PLAYER_LOGIN_QUERY_LOADMAILS,
    PLAYER_LOGIN_QUERY_LOADMAILEDITEMS,
    PLAYER_LOGIN_QUERY_BATTLEGROUND_DATA,

    MAX_PLAYER_LOGIN_QUERY
};

enum PlayerDelayedOperations
{
    DELAYED_SAVE_PLAYER           = 0x01,
    DELAYED_RESURRECT_PLAYER      = 0x02,
    DELAYED_SPELL_CAST_DESERTER   = 0x04,
    DELAYED_CAST_HONORLESS_TARGET = 0x08,
    DELAYED_END
};

enum PlayerMountResult
{
    MOUNTRESULT_INVALIDMOUNTEE  = 0,    // You can't mount that unit!
    MOUNTRESULT_TOOFARAWAY      = 1,    // That mount is too far away!
    MOUNTRESULT_ALREADYMOUNTED  = 2,    // You're already mounted!
    MOUNTRESULT_NOTMOUNTABLE    = 3,    // That unit can't be mounted!
    MOUNTRESULT_NOTYOURPET      = 4,    // That mount isn't your pet!
    MOUNTRESULT_OTHER           = 5,    // internal
    MOUNTRESULT_LOOTING         = 6,    // You can't mount while looting!
    MOUNTRESULT_RACECANTMOUNT   = 7,    // You can't mount because of your race!
    MOUNTRESULT_SHAPESHIFTED    = 8,    // You can't mount while shapeshifted!
    MOUNTRESULT_FORCEDDISMOUNT  = 9,    // You dismount before continuing.
    MOUNTRESULT_OK              = 10    // no error
};

enum PlayerDismountResult
{
    DISMOUNTRESULT_NOPET        = 0,    // internal
    DISMOUNTRESULT_NOTMOUNTED   = 1,    // You're not mounted!
    DISMOUNTRESULT_NOTYOURPET   = 2,    // internal
    DISMOUNTRESULT_OK           = 3     // no error
};

enum ReputationSource
{
    REPUTATION_SOURCE_KILL,
    REPUTATION_SOURCE_QUEST,
    REPUTATION_SOURCE_SPELL
};

// Player summoning auto-decline time (in secs)
#define MAX_PLAYER_SUMMON_DELAY                   (2*MINUTE)
#define MAX_MONEY_AMOUNT                       (0x7FFFFFFF-1)

struct InstancePlayerBind
{
    DungeonPersistentState *state;
    bool perm;
    /* permanent PlayerInstanceBinds are created in Raid instances for players
       that aren't already permanently bound when they are inside when a boss is killed
       or when they enter an instance that the group leader is permanently bound to. */
    InstancePlayerBind() : state(NULL), perm(false) {}
};

#define MAX_INSTANCE_PER_ACCOUNT_PER_HOUR 5

class MANGOS_DLL_SPEC PlayerTaxi
{
    public:
        PlayerTaxi();
        ~PlayerTaxi() {}
        // Nodes
        void InitTaxiNodes(uint32 race, uint32 level);
        void LoadTaxiMask(const char* data);

        bool IsTaximaskNodeKnown(uint32 nodeidx) const
        {
            uint8  field   = uint8((nodeidx - 1) / 32);
            uint32 submask = 1<<((nodeidx-1)%32);
            return (m_taximask[field] & submask) == submask;
        }
        bool SetTaximaskNode(uint32 nodeidx)
        {
            uint8  field   = uint8((nodeidx - 1) / 32);
            uint32 submask = 1<<((nodeidx-1)%32);
            if ((m_taximask[field] & submask) != submask )
            {
                m_taximask[field] |= submask;
                return true;
            }
            else
                return false;
        }
        void AppendTaximaskTo(ByteBuffer& data, bool all);

        // Destinations
        bool LoadTaxiDestinationsFromString(const std::string& values, Team team);
        std::string SaveTaxiDestinationsToString() const;

        void ClearTaxiDestinations() { m_TaxiDestinations.clear(); }
        void AddTaxiDestination(uint32 dest) { m_TaxiDestinations.push_back(dest); }
        uint32 GetTaxiSource() const { return m_TaxiDestinations.empty() ? 0 : m_TaxiDestinations.front(); }
        uint32 GetTaxiDestination() const { return m_TaxiDestinations.size() < 2 ? 0 : m_TaxiDestinations[1]; }
        uint32 GetCurrentTaxiPath() const;
        uint32 NextTaxiDestination()
        {
            m_TaxiDestinations.pop_front();
            return GetTaxiDestination();
        }
        bool empty() const { return m_TaxiDestinations.empty(); }

        friend std::ostringstream& operator<< (std::ostringstream& ss, PlayerTaxi const& taxi);
    private:
        TaxiMask m_taximask;
        std::deque<uint32> m_TaxiDestinations;
};

std::ostringstream& operator<< (std::ostringstream& ss, PlayerTaxi const& taxi);

/// Holder for BattleGround data
struct BGData
{
    BGData() : bgInstanceID(0), bgTypeID(BATTLEGROUND_TYPE_NONE), bgAfkReportedCount(0), bgAfkReportedTimer(0),
        bgTeam(TEAM_NONE), m_needSave(false) {}

    uint32 bgInstanceID;                                    ///< This variable is set to bg->m_InstanceID, saved
                                                            ///  when player is teleported to BG - (it is battleground's GUID)
    BattleGroundTypeId bgTypeID;

    std::set<uint32>   bgAfkReporter;
    uint8              bgAfkReportedCount;
    time_t             bgAfkReportedTimer;

    Team bgTeam;                                            ///< What side the player will be added to, saved

    WorldLocation joinPos;                                  ///< From where player entered BG, saved

    bool m_needSave;                                        ///< true, if saved to DB fields modified after prev. save (marked as "saved" above)
};

struct TransactionPart;

class TradeData
{
    public:                                                 // constructors
        TradeData(Player* player, Player* trader) :
            m_player(player),  m_trader(trader), m_accepted(false), m_acceptProccess(false),
            m_money(0), m_spell(0), m_lastModificationTime(0), m_scamPreventionDelay(0){}

    public:                                                 // access functions

        Player* GetTrader() const { return m_trader; }
        TradeData* GetTraderData() const;

        Item* GetItem(TradeSlots slot) const;
        bool HasItem(ObjectGuid item_guid) const;

        uint32 GetSpell() const { return m_spell; }
        Item*  GetSpellCastItem() const;
        bool HasSpellCastItem() const { return !m_spellCastItem.IsEmpty(); }

        uint32 GetMoney() const { return m_money; }

        bool IsAccepted() const { return m_accepted; }
        bool IsInAcceptProcess() const { return m_acceptProccess; }

        TradeSlots GetTradeSlotForItem(ObjectGuid itemGuid) const;

        void FillTransactionLog(TransactionPart& log) const;

        time_t GetLastModificationTime() const { return m_lastModificationTime; }
        void SetLastModificationTime(time_t t) { m_lastModificationTime = t; }

		time_t GetScamPreventionDelay() const { return m_scamPreventionDelay; }
		void SetScamPreventionDelay(time_t t) { m_scamPreventionDelay = t; }
    public:                                                 // access functions

        void SetItem(TradeSlots slot, Item* item);
        void SetSpell(uint32 spell_id, Item* castItem = NULL);
        void SetMoney(uint32 money);

        void SetAccepted(bool state, bool crosssend = false);

        // must be called only from accept handler helper functions
        void SetInAcceptProcess(bool state) { m_acceptProccess = state; }

    private:                                                // internal functions

        void Update(bool for_trader = true);

    private:                                                // fields

        Player*    m_player;                                // Player who own of this TradeData
        Player*    m_trader;                                // Player who trade with m_player

        bool       m_accepted;                              // m_player press accept for trade list
        bool       m_acceptProccess;                        // one from player/trader press accept and this processed

        uint32     m_money;                                 // m_player place money to trade

        uint32     m_spell;                                 // m_player apply spell to non-traded slot item
        ObjectGuid m_spellCastItem;                         // applied spell casted by item use

        ObjectGuid m_items[TRADE_SLOT_COUNT];               // traded itmes from m_player side including non-traded slot

        time_t     m_lastModificationTime;                  // to prevent scam (change gold before the other validates)
		time_t	   m_scamPreventionDelay;					// to prevent scam, set a delay in milliseconds (CANNOT be less than or equal to 10ms) before accepting trade.
};

struct CinematicWaypointEntry
{
        uint32 cinematic_id;
        uint32 time;
        Position position;
};

#define MAX_RACIAL_SPELLS 10

struct RacialSpells
{
    uint8 raceId;
    uint32 spells[MAX_RACIAL_SPELLS];
};

class PlayerAnticheatInterface;

struct AuraSaveStruct
{
    ObjectGuid caster_guid;
    uint32 item_lowguid;
    uint32 spellid;
    uint32 stackcount;
    uint32 remaincharges;
    int32  damage[MAX_EFFECT_INDEX];
    uint32 periodicTime[MAX_EFFECT_INDEX];

    int32 maxduration;
    int32 remaintime;
    uint32 effIndexMask;
};

struct ScheduledTeleportData
{
    ScheduledTeleportData() : targetMapId(0), x(0.0f), y(0.0f), z(0.0f),
        orientation(0.0f), options(0), recover(std::function<void()>()) {};

    ScheduledTeleportData(uint32 mapid, float x, float y, float z, float o,
        uint32 options, std::function<void()> recover)
        : targetMapId(mapid), x(x), y(y), z(z),
        orientation(o), options(options), recover(recover) {};

    uint32 targetMapId;
    float x;
    float y;
    float z;
    float orientation;

    uint32 options;

    std::function<void()> recover;
};

class MANGOS_DLL_SPEC Player final: public Unit
{
    friend class WorldSession;
    friend void Item::AddToUpdateQueueOf(Player *player);
    friend void Item::RemoveFromUpdateQueueOf(Player *player);
    public:
        explicit Player (WorldSession *session);
        ~Player();

        void CleanupsBeforeDelete();

        static UpdateMask updateVisualBits;
        static void InitVisibleBits();

        void AddToWorld();
        void RemoveFromWorld();

        // Nostalgia WoW Custom
        void LegitCooldownReset();
        bool IsBlockingInspect();
        void SetInspectState(bool block);
        bool ShouldReplenish();
        void SetDuelReplenishState(bool enable);
        void Replenish();
        void ApplyLegitReplenishment(bool force = false);
        bool RemoveItemCurrency(uint32 itemId, uint32 count);

        /* Switch from instanceId of same map.
         * Assumes that you can enter the map.
         * Should be called in a thread-safe environnement (not in map update for example !)
         */
        bool SwitchInstance(uint32 newInstanceId);
        bool TeleportTo(uint32 mapid, float x, float y, float z, float orientation, uint32 options = 0, std::function<void()> recover = std::function<void()>());

        bool TeleportTo(WorldLocation const &loc, uint32 options = 0, std::function<void()> recover = std::function<void()>())
        {
            return TeleportTo(loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z, loc.orientation, options, recover);
        }

        // _NOT_ thread-safe. Must be executed by the map manager after map updates, since we
         // remove objects from the map
        bool ExecuteTeleportFar(ScheduledTeleportData* data);

        bool TeleportToBGEntryPoint();

        void restorePendingTeleport();

        void SetSummonPoint(uint32 mapid, float x, float y, float z)
        {
            m_summon_expire = time(NULL) + MAX_PLAYER_SUMMON_DELAY;
            m_summon_mapid = mapid;
            m_summon_x = x;
            m_summon_y = y;
            m_summon_z = z;
        }
        void SummonIfPossible(bool agree);

        bool Create( uint32 guidlow, const std::string& name, uint8 race, uint8 class_, uint8 gender, uint8 skin, uint8 face, uint8 hairStyle, uint8 hairColor, uint8 facialHair, uint8 outfitId );

        void Update(uint32 update_diff, uint32 time) override;
        void SetTransport(Transport * t) override;
        void DismountCheck();

        static bool BuildEnumData( QueryResult * result,  WorldPacket * p_data );

        void LoadShopItem(QueryResult* result);
        void LoadShopLevel(QueryResult* result);
        void LoadShopGold(QueryResult* result);
        void LoadShopRaceChange(QueryResult* result);

        bool _shopCallBackInitialized = false;

        // knockback/jumping states
        bool IsLaunched() const { return launched; }
        void SetLaunched(bool apply) { launched = apply; }
        float GetXYSpeed() { return xy_speed; }
        void SetXYSpeed(float speed) { xy_speed = speed; }

        // knockback/jumping states
        bool launched;
        // not null only is player has knockback state
        float xy_speed;

        void SetInWater(bool apply);

        bool IsInWater() const { return m_isInWater; }

        void SendInitialPacketsBeforeAddToMap();
        void SendInitialPacketsAfterAddToMap(bool login = true);
        void SendTransferAborted(uint8 reason);
        void SendInstanceResetWarning(uint32 mapid, uint32 time);

        Creature* GetNPCIfCanInteractWith(ObjectGuid guid, uint32 npcflagmask);
        GameObject* GetGameObjectIfCanInteractWith(ObjectGuid guid, uint32 gameobject_type = MAX_GAMEOBJECT_TYPE) const;

        bool ToggleAFK();
        bool ToggleDND();
        bool isAFK() const { return HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_AFK); }
        bool isDND() const { return HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_DND); }
        uint8 chatTag() const;
        std::string afkMsg;
        std::string dndMsg;

        PlayerTaxi m_taxi;
        void InitTaxiNodes() { m_taxi.InitTaxiNodes(getRace(),getLevel()); }
        bool ActivateTaxiPathTo(std::vector<uint32> const& nodes, Creature* npc = NULL, uint32 spellid = 0, bool nocheck = false);
        bool ActivateTaxiPathTo(uint32 taxi_path_id, uint32 spellid = 0, bool nocheck = false);
                                                            // mount_id can be used in scripting calls
        void TaxiStepFinished();
        void ContinueTaxiFlight();
        void UnlockAllTaxiPathes();
        void Mount(uint32 mount, uint32 spellId = 0, bool IsTaxi = false) override;
        void Unmount(bool from_aura = false) override;
        void SendMountResult(PlayerMountResult result);
        void SendDismountResult(PlayerDismountResult result);
        bool isAcceptTickets() const { return GetSession()->GetSecurity() >= SEC_GAMEMASTER && (m_ExtraFlags & PLAYER_EXTRA_GM_ACCEPT_TICKETS); }
        void SetAcceptTicket(bool on) { if(on) m_ExtraFlags |= PLAYER_EXTRA_GM_ACCEPT_TICKETS; else m_ExtraFlags &= ~PLAYER_EXTRA_GM_ACCEPT_TICKETS; }

        bool isAllowedWhisperFrom(ObjectGuid guid);
        bool isEnabledWhisperRestriction() const { return m_ExtraFlags & PLAYER_EXTRA_WHISP_RESTRICTION; }
        void setWhisperRestriction(bool on) { if (on) m_ExtraFlags |= PLAYER_EXTRA_WHISP_RESTRICTION; else m_ExtraFlags &= ~PLAYER_EXTRA_WHISP_RESTRICTION; }

        bool IsAcceptWhispers() const { return m_ExtraFlags & PLAYER_EXTRA_ACCEPT_WHISPERS; }
        void SetAcceptWhispers(bool on) { if(on) m_ExtraFlags |= PLAYER_EXTRA_ACCEPT_WHISPERS; else m_ExtraFlags &= ~PLAYER_EXTRA_ACCEPT_WHISPERS; }
        uint32 GetExtraFlags() const { return m_ExtraFlags; }

        bool isGameMaster() const { return m_ExtraFlags & PLAYER_EXTRA_GM_ON; }
        void SetGameMaster(bool on);
        bool isGMChat() const { return GetSession()->GetSecurity() >= SEC_MODERATOR && (m_ExtraFlags & PLAYER_EXTRA_GM_CHAT); }
        void SetGMChat(bool on) { if(on) m_ExtraFlags |= PLAYER_EXTRA_GM_CHAT; else m_ExtraFlags &= ~PLAYER_EXTRA_GM_CHAT; }
        bool isTaxiCheater() const { return m_ExtraFlags & PLAYER_EXTRA_TAXICHEAT; }
        void SetTaxiCheater(bool on) { if(on) m_ExtraFlags |= PLAYER_EXTRA_TAXICHEAT; else m_ExtraFlags &= ~PLAYER_EXTRA_TAXICHEAT; }
        bool isGMVisible() const { return !(m_ExtraFlags & PLAYER_EXTRA_GM_INVISIBLE); }
        void SetGMVisible(bool on);
        void SetPvPDeath(bool on) { if(on) m_ExtraFlags |= PLAYER_EXTRA_PVP_DEATH; else m_ExtraFlags &= ~PLAYER_EXTRA_PVP_DEATH; }

        // Cannot be detected by creature (Should be tested in AI::MoveInLineOfSight)
        void SetCannotBeDetectedTimer(uint32 milliseconds) { m_cannotBeDetectedTimer = milliseconds; };
        bool CanBeDetected() const override { return m_cannotBeDetectedTimer <= 0; }

        uint32 _playerOptions;
        bool HasOption(uint32 o) const{ return (_playerOptions & o); }
        void EnableOption(uint32 o)   { _playerOptions |= o; }
        void RemoveOption(uint32 o)   { _playerOptions &= (~o); }
        void SetOption(PlayerCheatOptions o, bool on)
        {
            if (on)
                EnableOption(o);
            else
                RemoveOption(o);
        }

        void SetGodMode(bool on) { SetOption(PLAYER_CHEAT_GOD, on);  }
        bool IsGod() const       { return HasOption(PLAYER_CHEAT_GOD);}

        // 0 = own auction, -1 = enemy auction, 1 = goblin auction
        int GetAuctionAccessMode() const { return m_ExtraFlags & PLAYER_EXTRA_AUCTION_ENEMY ? -1 : (m_ExtraFlags & PLAYER_EXTRA_AUCTION_NEUTRAL ? 1 : 0); }
        void SetAuctionAccessMode(int state)
        {
            m_ExtraFlags &= ~ (PLAYER_EXTRA_AUCTION_ENEMY|PLAYER_EXTRA_AUCTION_NEUTRAL);

            if(state < 0)
                m_ExtraFlags |= PLAYER_EXTRA_AUCTION_ENEMY;
            else if( state > 0)
                m_ExtraFlags |= PLAYER_EXTRA_AUCTION_NEUTRAL;
        }

        void GiveXP(uint32 xp, Unit* victim, bool isQuest = false);
        void GiveLevel(uint32 level);

        void InitStatsForLevel(bool reapplyMods = false);

        // Played Time Stuff
        time_t m_logintime;
        time_t m_Last_tick;
        uint32 m_Played_time[MAX_PLAYED_TIME_INDEX];
        uint32 GetTotalPlayedTime() { return m_Played_time[PLAYED_TIME_TOTAL]; }
        uint32 GetLevelPlayedTime() { return m_Played_time[PLAYED_TIME_LEVEL]; }

        void SetDeathState(DeathState s);                   // overwrite Unit::SetDeathState

        float GetRestBonus() const { return m_rest_bonus; }
        void SetRestBonus(float rest_bonus_new);

        RestType GetRestType() const { return rest_type; }
        void SetRestType(RestType n_r_type, uint32 areaTriggerId = 0);

        time_t GetTimeInnEnter() const { return time_inn_enter; }
        void UpdateInnerTime (time_t time) { time_inn_enter = time; }

        void RemovePet(PetSaveMode mode);
        void RemoveMiniPet();
        Pet* GetMiniPet() const;

        // use only in Pet::Unsummon/Spell::DoSummon
        void _SetMiniPet(Pet* pet) { m_miniPetGuid = pet ? pet->GetObjectGuid() : ObjectGuid(); }
        void SummonCritter(uint32 pet_entry);

        float GetYellRange() const;
        void Say(const std::string& text, const uint32 language);
        void Yell(const std::string& text, const uint32 language);
        void TextEmote(const std::string& text);
        void BuildPlayerChat(WorldPacket *data, uint8 msgtype, const std::string& text, uint32 language) const;
        static void BuildPlayerChat(ObjectGuid senderGuid, uint8 senderChatTag, WorldPacket *data, uint8 msgtype, const std::string& text, uint32 language);

        //Giperion Elysium: Send message to upper place of player screen, even if he not in raid. Useful for scripts/events
        void SendRaidWarning(uint32 textId);
        void SendRaidWarning(const std::string& text);
        void SendRaidWarning(const char* text);

        /*********************************************************/
        /***                    STORAGE SYSTEM                 ***/
        /*********************************************************/

        Item* AddItem(uint32 itemId, uint32 count = 1, uint32* noSpaceForCount = nullptr);
		Item* PAddItem(uint32 itemId, uint32 count, uint32* noSpaceForCount, Unit* pVictim);
        void InterruptSpellsWithCastItem(Item* item);
        void SetVirtualItemSlot( uint8 i, Item* item);
        void SetSheath( SheathState sheathed );             // overwrite Unit version
        uint8 FindEquipSlot(ItemPrototype const* proto, uint32 slot, bool swap) const;
        uint32 GetItemCount(uint32 item, bool inBankAlso = false, Item* skipItem = NULL) const;
        Item* GetItemByGuid(ObjectGuid guid) const;
        Item* GetItemByPos( uint16 pos ) const;
        Item* GetItemByPos( uint8 bag, uint8 slot ) const;
        Item* GetWeaponForAttack(WeaponAttackType attackType) const { return GetWeaponForAttack(attackType,false,false); }
        Item* GetWeaponForAttack(WeaponAttackType attackType, bool nonbroken, bool useable) const;
        Item* GetShield(bool useable = false) const;
        static uint32 GetAttackBySlot( uint8 slot );        // MAX_ATTACK if not weapon slot
        std::vector<Item *> &GetItemUpdateQueue() { return m_itemUpdateQueue; }
        static bool IsInventoryPos( uint16 pos ) { return IsInventoryPos(pos >> 8, pos & 255); }
        static bool IsInventoryPos( uint8 bag, uint8 slot );
        static bool IsEquipmentPos( uint16 pos ) { return IsEquipmentPos(pos >> 8, pos & 255); }
        static bool IsEquipmentPos( uint8 bag, uint8 slot );
        static bool IsBagPos( uint16 pos );
        static bool IsBankPos( uint16 pos ) { return IsBankPos(pos >> 8, pos & 255); }
        static bool IsBankPos( uint8 bag, uint8 slot );
        bool IsValidPos( uint16 pos, bool explicit_pos ) const { return IsValidPos(pos >> 8, pos & 255, explicit_pos); }
        bool IsValidPos( uint8 bag, uint8 slot, bool explicit_pos ) const;
        uint8 GetBankBagSlotCount() const { return GetByteValue(PLAYER_BYTES_2, 2); }
        void SetBankBagSlotCount(uint8 count) { SetByteValue(PLAYER_BYTES_2, 2, count); }
        bool HasItemCount( uint32 item, uint32 count = 1, bool inBankAlso = false) const;
        bool HasItemFitToSpellReqirements(SpellEntry const* spellInfo, Item const* ignoreItem = NULL);
        bool CanNoReagentCast(SpellEntry const* spellInfo) const;
        bool HasItemWithIdEquipped( uint32 item, uint32 count = 1, uint8 except_slot = NULL_SLOT) const;
        InventoryResult CanTakeMoreSimilarItems(Item* pItem) const { return _CanTakeMoreSimilarItems(pItem->GetEntry(), pItem->GetCount(), pItem); }
        InventoryResult CanTakeMoreSimilarItems(uint32 entry, uint32 count) const { return _CanTakeMoreSimilarItems(entry, count, NULL); }
        InventoryResult CanStoreNewItem( uint8 bag, uint8 slot, ItemPosCountVec& dest, uint32 item, uint32 count, uint32* no_space_count = NULL ) const
        {
            return _CanStoreItem(bag, slot, dest, item, count, NULL, false, no_space_count );
        }
        InventoryResult CanStoreItem( uint8 bag, uint8 slot, ItemPosCountVec& dest, Item *pItem, bool swap = false ) const
        {
            if(!pItem)
                return EQUIP_ERR_ITEM_NOT_FOUND;
            uint32 count = pItem->GetCount();
            return _CanStoreItem( bag, slot, dest, pItem->GetEntry(), count, pItem, swap, NULL );

        }
        InventoryResult CanStoreItems( Item **pItem,int count) const;
        InventoryResult CanEquipNewItem( uint8 slot, uint16 &dest, uint32 item, bool swap ) const;
        InventoryResult CanEquipItem( uint8 slot, uint16 &dest, Item *pItem, bool swap, bool not_loading = true ) const;

        InventoryResult CanEquipUniqueItem( Item * pItem, uint8 except_slot = NULL_SLOT ) const;
        InventoryResult CanEquipUniqueItem( ItemPrototype const* itemProto, uint8 except_slot = NULL_SLOT ) const;
        InventoryResult CanUnequipItems( uint32 item, uint32 count ) const;
        InventoryResult CanUnequipItem( uint16 src, bool swap ) const;
        InventoryResult CanBankItem( uint8 bag, uint8 slot, ItemPosCountVec& dest, Item *pItem, bool swap, bool not_loading = true ) const;
        InventoryResult CanUseItem( Item *pItem, bool not_loading = true ) const;
        bool HasItemTotemCategory( uint32 TotemCategory ) const;
        InventoryResult CanUseItem( ItemPrototype const *pItem, bool not_loading = true ) const;
        InventoryResult CanUseAmmo( uint32 item ) const;
        Item* StoreNewItem( ItemPosCountVec const& pos, uint32 item, bool update,int32 randomPropertyId = 0 );
        Item* StoreItem( ItemPosCountVec const& pos, Item *pItem, bool update, bool toBank = false );
        Item* EquipNewItem( uint16 pos, uint32 item, bool update );
        Item* EquipItem( uint16 pos, Item *pItem, bool update );
        void AutoUnequipOffhandIfNeed();
        void AutoUnequipMainHandIfNeed();  // Ustaag <Nostalrius> : ajout fonction
        bool StoreNewItemInBestSlots(uint32 item_id, uint32 item_count);
        Item* StoreNewItemInInventorySlot(uint32 itemEntry, uint32 amount);

        void AutoStoreLoot(Loot& loot, bool broadcast = false, uint8 bag = NULL_BAG, uint8 slot = NULL_SLOT);

        //Giperion Elysium: More easy way to iterate through player inventory
        template<typename FuncLambda>
        bool ForEveryPlayerItem(FuncLambda functor)
        {
            for (int i = PLAYER_SLOT_START; i < PLAYER_SLOT_END; ++i)
            {
                if (Item* item = GetItemByPos(INVENTORY_SLOT_BAG_0, i))
                {
                    if (Bag* bag = dynamic_cast<Bag*>(item))
                    {
                        uint32 BagSize = bag->GetBagSize();
                        for (uint32 z = 0; z < BagSize; ++z)
                        {
                            if (Item* bagItem = bag->GetItemByPos(z))
                            {
                                if (!functor(bagItem)) return false;
                            }
                        }
                    }

                    if (!functor(item)) return false;
                }
            }

            return true;
        }
        

        InventoryResult _CanTakeMoreSimilarItems(uint32 entry, uint32 count, Item* pItem, uint32* no_space_count = NULL) const;
        InventoryResult _CanStoreItem( uint8 bag, uint8 slot, ItemPosCountVec& dest, uint32 entry, uint32 count, Item *pItem = NULL, bool swap = false, uint32* no_space_count = NULL ) const;

        virtual void ProhibitSpellSchool(SpellSchoolMask idSchoolMask, uint32 unTimeMs);
        void SendClearCooldown(uint32 spell_id, Unit* target);
        void SendSpellCooldown(uint32 spellId, uint32 cooldown, ObjectGuid target);

        void ApplyEquipCooldown( Item * pItem );
        void SetAmmo( uint32 item );
        void RemoveAmmo();
        float GetAmmoDPS() const { return m_ammoDPS; }
        bool CheckAmmoCompatibility(const ItemPrototype *ammo_proto) const;
        void QuickEquipItem( uint16 pos, Item *pItem);
        void VisualizeItem( uint8 slot, Item *pItem);
        void SetVisibleItemSlot(uint8 slot, Item *pItem);
        Item* BankItem( ItemPosCountVec const& dest, Item *pItem, bool update )
        {
            return StoreItem( dest, pItem, update, true);
        }

        void RemoveItem( uint8 bag, uint8 slot, bool update );

        //Giperion Elysium
        bool RemoveItems(uint32 itemId, uint32 count);

        void MoveItemFromInventory(uint8 bag, uint8 slot, bool update);
                                                            // in trade, auction, guild bank, mail....
        void MoveItemToInventory(ItemPosCountVec const& dest, Item* pItem, bool update, bool in_characterInventoryDB = false);
                                                            // in trade, guild bank, mail....
        void RemoveItemDependentAurasAndCasts( Item * pItem );
        void DestroyItem( uint8 bag, uint8 slot, bool update );
        void DestroyItemCount( uint32 item, uint32 count, bool update, bool unequip_check = false, bool check_bank = false);
        void DestroyItemCount( Item* item, uint32& count, bool update );
        /**
         * @brief Destroys equipped item $itemId and updates the Player
         * @param itemId
         * @return true if an item got deleted
         */
        bool DestroyEquippedItem(uint32 itemId);
        void DestroyConjuredItems( bool update );
        void DestroyZoneLimitedItem( bool update, uint32 new_zone );
        void SplitItem( uint16 src, uint16 dst, uint32 count );
        void SwapItem( uint16 src, uint16 dst );
        void AddItemToBuyBackSlot(Item* pItem, uint32 money);
        Item* GetItemFromBuyBackSlot( uint32 slot );
        void RemoveItemFromBuyBackSlot( uint32 slot, bool del );

        uint32 GetMaxKeyringSize() const { return KEYRING_SLOT_END-KEYRING_SLOT_START; }
        void SendEquipError( InventoryResult msg, Item* pItem, Item *pItem2 = NULL, uint32 itemid = 0 ) const;
        void SendBuyError( BuyResult msg, Creature* pCreature, uint32 item, uint32 param );
        void SendSellError( SellResult msg, Creature* pCreature, ObjectGuid itemGuid, uint32 param );
        void SendOpenContainer();
        void AddWeaponProficiency(uint32 newflag) { m_WeaponProficiency |= newflag; }
        void AddArmorProficiency(uint32 newflag) { m_ArmorProficiency |= newflag; }
        uint32 GetWeaponProficiency() const { return m_WeaponProficiency; }
        uint32 GetArmorProficiency() const { return m_ArmorProficiency; }
        bool IsTwoHandUsed() const
        {
            Item* mainItem = GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
            return mainItem && mainItem->GetProto()->InventoryType == INVTYPE_2HWEAPON;
        }
        void SendNewItem( Item *item, uint32 count, bool received, bool created, bool broadcast = false, bool showInChat = true );
        bool BuyItemFromVendor(ObjectGuid vendorGuid, uint32 item, uint8 count, uint8 bag, uint8 slot);
        void OnReceivedItem(Item* item, uint32 count, uint32 itemid, bool save);

        float GetReputationPriceDiscount( Creature const* pCreature ) const;

        Player* GetTrader() const { return m_trade ? m_trade->GetTrader() : NULL; }
        TradeData* GetTradeData() const { return m_trade; }
        void TradeCancel(bool sendback);

        void UpdateEnchantTime(uint32 time);
        void UpdateItemDuration(uint32 time, bool realtimeonly=false);
        void AddEnchantmentDurations(Item *item);
        void RemoveEnchantmentDurations(Item *item);
        void RemoveAllEnchantments(EnchantmentSlot slot);
        void AddEnchantmentDuration(Item *item,EnchantmentSlot slot,uint32 duration);
        void ApplyEnchantment(Item *item,EnchantmentSlot slot,bool apply, bool apply_dur = true, bool ignore_condition = false);
        void ApplyEnchantment(Item *item,bool apply);
        void SendEnchantmentDurations();
        void AddItemDurations(Item *item);
        void RemoveItemDurations(Item *item);
        void SendItemDurations();
        void LoadCorpse();
        void LoadPet();

        uint32 m_stableSlots;

        /*********************************************************/
        /***                    GOSSIP SYSTEM                  ***/
        /*********************************************************/

        void PrepareGossipMenu(WorldObject *pSource, uint32 menuId = 0);
        void SendPreparedGossip(WorldObject *pSource);
        void OnGossipSelect(WorldObject *pSource, uint32 gossipListId);

        uint32 GetGossipTextId(uint32 menuId, WorldObject const* source);
        uint32 GetGossipTextId(WorldObject *pSource);
        uint32 GetDefaultGossipMenuForSource(WorldObject *pSource);

        /*********************************************************/
        /***                    QUEST SYSTEM                   ***/
        /*********************************************************/

        uint32 GetQuestLevelForPlayer(Quest const* pQuest) const { return pQuest && (pQuest->GetQuestLevel() > 0) ? pQuest->GetQuestLevel() : getLevel(); }

        void PrepareQuestMenu(ObjectGuid guid, uint32 exceptQuestId = 0);
        void SendPreparedQuest(ObjectGuid guid);
        bool IsActiveQuest(uint32 quest_id) const;        // can be taken or taken
        bool IsCurrentQuest(uint32 quest_id, uint8 completedOrNot = 0) const;
        Quest const *GetNextQuest(ObjectGuid guid, Quest const *pQuest );
        bool CanSeeStartQuest( Quest const *pQuest ) const;
        bool CanTakeQuest( Quest const *pQuest, bool msg, bool skipStatusCheck = false ) const;
        bool CanTakeQuest(int32 questId) const;
        bool CanAddQuest( Quest const *pQuest, bool msg ) const;
        bool CanCompleteQuest( uint32 quest_id ) const;
        bool CanCompleteRepeatableQuest(Quest const *pQuest) const;
        bool CanRewardQuest( Quest const *pQuest, bool msg ) const;
        bool CanRewardQuest( Quest const *pQuest, uint32 reward, bool msg ) const;
        uint32 CountFreeInventorySlots() const;
        void AddQuest( Quest const *pQuest, Object *questGiver );
        void FullQuestComplete(uint32 questId); // Equivalent to .quest complete
        void CompleteQuest( uint32 quest_id );
        void IncompleteQuest( uint32 quest_id );
        void RewardQuest( Quest const *pQuest, uint32 reward, WorldObject* questGiver, bool announce = true );

        void FailQuest( uint32 quest_id );
        bool SatisfyQuestSkill(Quest const* qInfo, bool msg) const;
        bool SatisfyQuestLevel( Quest const* qInfo, bool msg ) const;
        bool SatisfyQuestLog( bool msg ) const;
        bool SatisfyQuestPreviousQuest( Quest const* qInfo, bool msg ) const;
        bool SatisfyQuestClass(Quest const* qInfo, bool msg) const;
        bool SatisfyQuestRace( Quest const* qInfo, bool msg ) const;
        bool SatisfyQuestReputation( Quest const* qInfo, bool msg ) const;
        bool SatisfyQuestStatus( Quest const* qInfo, bool msg ) const;
        bool SatisfyQuestTimed( Quest const* qInfo, bool msg ) const;
        bool SatisfyQuestExclusiveGroup( Quest const* qInfo, bool msg ) const;
        bool SatisfyQuestNextChain( Quest const* qInfo, bool msg ) const;
        bool SatisfyQuestPrevChain( Quest const* qInfo, bool msg ) const;
        bool CanGiveQuestSourceItemIfNeed( Quest const *pQuest, ItemPosCountVec* dest = NULL) const;
        void GiveQuestSourceItemIfNeed(Quest const *pQuest);
        bool TakeOrReplaceQuestStartItems( uint32 quest_id, bool msg, bool giveQuestStartItem );
        bool GetQuestRewardStatus( uint32 quest_id ) const;
        const QuestStatusData* GetQuestStatusData(uint32 quest_id) const;
        QuestStatus GetQuestStatus( uint32 quest_id ) const;
        void SetQuestStatus( uint32 quest_id, QuestStatus status );

        // Ces 3 fonctions n'existent plus dans MaNGOSZero
        uint8 GetQuestSlotState(uint16 slot)   const { return GetByteValue(PLAYER_QUEST_LOG_1_1 + slot*MAX_QUEST_OFFSET + QUEST_COUNT_STATE_OFFSET, 3); }
        uint8 GetQuestSlotCounter(uint16 slot, uint8 counter) const { return (GetUInt32Value(PLAYER_QUEST_LOG_1_1 + slot*MAX_QUEST_OFFSET + QUEST_COUNT_STATE_OFFSET) >> (counter*6)) & 0x3F; }
        uint32 GetQuestSlotTime(uint16 slot)    const { return GetUInt32Value(PLAYER_QUEST_LOG_1_1 + slot*MAX_QUEST_OFFSET + QUEST_TIME_OFFSET); }

        uint16 FindQuestSlot( uint32 quest_id ) const;
        uint32 GetQuestSlotQuestId(uint16 slot) const { return GetUInt32Value(PLAYER_QUEST_LOG_1_1 + slot * MAX_QUEST_OFFSET + QUEST_ID_OFFSET); }
        void SetQuestSlot(uint16 slot, uint32 quest_id, uint32 timer = 0)
        {
            SetUInt32Value(PLAYER_QUEST_LOG_1_1 + slot*MAX_QUEST_OFFSET + QUEST_ID_OFFSET,quest_id);
            SetUInt32Value(PLAYER_QUEST_LOG_1_1 + slot*MAX_QUEST_OFFSET + QUEST_COUNT_STATE_OFFSET,0);
            SetUInt32Value(PLAYER_QUEST_LOG_1_1 + slot*MAX_QUEST_OFFSET + QUEST_TIME_OFFSET,timer);
        }
        void SetQuestSlotCounter(uint16 slot,uint8 counter,uint8 count)
        {
            uint32 val = GetUInt32Value(PLAYER_QUEST_LOG_1_1 + slot*MAX_QUEST_OFFSET + QUEST_COUNT_STATE_OFFSET);
            val &= ~(0x3F << (counter*6));
            val |= ((uint32)count << (counter*6));
            SetUInt32Value(PLAYER_QUEST_LOG_1_1 + slot*MAX_QUEST_OFFSET + QUEST_COUNT_STATE_OFFSET, val);
        }
        void SetQuestSlotState(uint16 slot, uint8 state) { SetByteFlag(PLAYER_QUEST_LOG_1_1 + slot*MAX_QUEST_OFFSET + QUEST_COUNT_STATE_OFFSET, 3, state); }
        void RemoveQuestSlotState(uint16 slot,uint8 state) { RemoveByteFlag(PLAYER_QUEST_LOG_1_1 + slot*MAX_QUEST_OFFSET + QUEST_COUNT_STATE_OFFSET, 3, state); }
        void SetQuestSlotTimer(uint16 slot,uint32 timer) { SetUInt32Value(PLAYER_QUEST_LOG_1_1 + slot*MAX_QUEST_OFFSET + QUEST_TIME_OFFSET,timer); }
        void SwapQuestSlot(uint16 slot1,uint16 slot2)
        {
            for (int i = 0; i < MAX_QUEST_OFFSET ; ++i )
            {
                uint32 temp1 = GetUInt32Value(PLAYER_QUEST_LOG_1_1 + MAX_QUEST_OFFSET *slot1 + i);
                uint32 temp2 = GetUInt32Value(PLAYER_QUEST_LOG_1_1 + MAX_QUEST_OFFSET *slot2 + i);

                SetUInt32Value(PLAYER_QUEST_LOG_1_1 + MAX_QUEST_OFFSET *slot1 + i, temp2);
                SetUInt32Value(PLAYER_QUEST_LOG_1_1 + MAX_QUEST_OFFSET *slot2 + i, temp1);
            }
        }
        uint32 GetReqKillOrCastCurrentCount(uint32 quest_id, int32 entry);
        void AreaExploredOrEventHappens( uint32 questId );
        void GroupEventHappens( uint32 questId, WorldObject const* pEventObject );
        void GroupEventFailHappens( uint32 questId );
        void ItemAddedQuestCheck( uint32 entry, uint32 count );
        void ItemRemovedQuestCheck( uint32 entry, uint32 count );
        void KilledMonster( CreatureInfo const* cInfo, ObjectGuid guid );
        void KilledMonsterCredit( uint32 entry, ObjectGuid guid = ObjectGuid());
        void CastedCreatureOrGO( uint32 entry, ObjectGuid guid, uint32 spell_id, bool original_caster = true );
        void TalkedToCreature( uint32 entry, ObjectGuid guid );
        void MoneyChanged( uint32 value );
        void ReputationChanged(FactionEntry const* factionEntry );
        bool HasQuestForItem( uint32 itemid ) const;
        bool HasQuestForGO(int32 GOId) const;
        void UpdateForQuestWorldObjects();
        bool CanShareQuest(uint32 quest_id) const;

        void SendQuestCompleteEvent(uint32 quest_id);
        void SendQuestReward( Quest const *pQuest, uint32 XP, Object* questGiver );
        void SendQuestFailed( uint32 quest_id);
        void SendQuestFailedAtTaker(uint32 quest_id, uint32 reason = INVALIDREASON_DONT_HAVE_REQ) const;
        void SendQuestTimerFailed( uint32 quest_id );
        void SendCanTakeQuestResponse( uint32 msg ) const;
        void SendQuestConfirmAccept(Quest const* pQuest, Player* pReceiver);
        void SendPushToPartyResponse(Player *pPlayer, uint8 msg);
        void SendQuestUpdateAddItem( Quest const* pQuest, uint32 item_idx, uint32 count );
        void SendQuestUpdateAddCreatureOrGo(Quest const* pQuest, ObjectGuid guid, uint32 creatureOrGO_idx, uint32 count);

        ObjectGuid GetDividerGuid() const { return m_dividerGuid; }
        void SetDividerGuid(ObjectGuid guid) { m_dividerGuid = guid; }
        void ClearDividerGuid() { m_dividerGuid.Clear(); }

        uint32 GetInGameTime() { return m_ingametime; }

        void SetInGameTime( uint32 time ) { m_ingametime = time; }

        void AddTimedQuest( uint32 quest_id ) { m_timedquests.insert(quest_id); }
        void RemoveTimedQuest( uint32 quest_id ) { m_timedquests.erase(quest_id); }

        /*********************************************************/
        /***                   LOAD SYSTEM                     ***/
        /*********************************************************/

        bool LoadFromDB(ObjectGuid guid, SqlQueryHolder *holder);
        void SendPacketsAtRelogin();

        static uint32 GetZoneIdFromDB(ObjectGuid guid);
        static uint32 GetLevelFromDB(ObjectGuid guid);
        void Initialize(uint32 guid);
        static bool   LoadPositionFromDB(ObjectGuid guid, uint32& mapid, float& x,float& y,float& z,float& o, bool& in_flight);

        /*********************************************************/
        /***                   SAVE SYSTEM                     ***/
        /*********************************************************/

        void SaveToDB(bool online = true, bool force = false);
        void SaveInventoryAndGoldToDB();                    // fast save function for item/money cheating preventing
        void SaveGoldToDB();

        static void SetUInt32ValueInArray(Tokens& data,uint16 index, uint32 value);
        static void SetFloatValueInArray(Tokens& data,uint16 index, float value);
        static void SavePositionInDB(ObjectGuid guid, uint32 mapid, float x,float y,float z,float o,uint32 zone);

        static void DeleteFromDB(ObjectGuid playerguid, uint32 accountId, bool updateRealmChars = true, bool deleteFinally = false);
        static void DeleteOldCharacters();
        static void DeleteOldCharacters(uint32 keepDays);

        bool m_mailsUpdated;

        void SendPetTameFailure(PetTameFailureReason reason);

        void SetBindPoint(ObjectGuid guid);
        void SendTalentWipeConfirm(ObjectGuid guid);
        void RewardRage( uint32 damage, bool attacker );
        void SendPetSkillWipeConfirm();
        void CalcRage( uint32 damage,bool attacker );
        void RegenerateAll();
        void Regenerate(Powers power);
        void RegenerateHealth();
        void setRegenTimer(uint32 time) {m_regenTimer = time;}
        void setWeaponChangeTimer(uint32 time) {m_weaponChangeTimer = time;}

        uint32 GetMoney() const { return GetUInt32Value (PLAYER_FIELD_COINAGE); }
        void LogModifyMoney(int32 d, const char* type, ObjectGuid fromGuid = ObjectGuid(), uint32 data = 0);
        void ModifyMoney( int32 d )
        {
            if(d < 0)
                SetMoney (GetMoney() > uint32(-d) ? GetMoney() + d : 0);
            else
                SetMoney (GetMoney() < uint32(MAX_MONEY_AMOUNT - d) ? GetMoney() + d : MAX_MONEY_AMOUNT);
        }
        void LootMoney(int32 g, Loot* loot);
        std::string GetShortDescription() const; // "player:guid [username:accountId@IP]"

        void SetMoney( uint32 value )
        {
            SetUInt32Value (PLAYER_FIELD_COINAGE, value);
            MoneyChanged( value );
        }

        QuestStatusMap& getQuestStatusMap() { return mQuestStatus; };

        ObjectGuid const& GetSelectedGobj() const { return m_selectedGobj; }
        void SetSelectedGobj(ObjectGuid guid) { m_selectedGobj = guid; }

        ObjectGuid const& GetSelectionGuid( ) const { return m_curSelectionGuid; }
        void SetSelectionGuid(ObjectGuid guid) { m_curSelectionGuid = guid; SetTargetGuid(guid); }

        Unit* getSelectedUnit() { return GetMap()->GetUnit(m_curSelectionGuid); }
        Creature* getSelectedCreature() { return GetMap()->GetCreature(m_curSelectionGuid); }
        Player* getSelectedPlayer() { return GetMap()->GetPlayer(m_curSelectionGuid); }

        uint8 GetComboPoints() const { return m_comboPoints; }
        ObjectGuid const& GetComboTargetGuid() const { return m_comboTargetGuid; }

        void AddComboPoints(Unit* target, int8 count);
        void ClearComboPoints();
        void SetComboPoints();

        void PetSpellInitialize();
        void CharmSpellInitialize();
        void PossessSpellInitialize();
        void RemovePetActionBar();

        bool HasSpell(uint32 spell) const;
        bool HasActiveSpell(uint32 spell) const;            // show in spellbook
        TrainerSpellState GetTrainerSpellState(TrainerSpell const* trainer_spell) const;
        bool IsSpellFitByClassAndRace(uint32 spell_id, uint32* pReqlevel = NULL) const;
        bool IsNeedCastPassiveLikeSpellAtLearn(SpellEntry const* spellInfo) const;
        bool IsImmuneToSpellEffect(SpellEntry const *spellInfo, SpellEffectIndex index, bool castOnSelf) const;

        void SendProficiency(ItemClass itemClass, uint32 itemSubclassMask);
        void SendInitialSpells();
        bool addSpell(uint32 spell_id, bool active, bool learning, bool dependent, bool disabled);
        void learnSpell(uint32 spell_id, bool dependent);
        void removeSpell(uint32 spell_id, bool disabled = false, bool learn_low_rank = true);
        void resetSpells();
        void learnDefaultSpells();
        void learnQuestRewardedSpells();
        void learnQuestRewardedSpells(Quest const* quest);
        void learnSpellHighRank(uint32 spellid);

        uint32 GetFreeTalentPoints() const { return GetUInt32Value(PLAYER_CHARACTER_POINTS1); }
        void SetFreeTalentPoints(uint32 points) { SetUInt32Value(PLAYER_CHARACTER_POINTS1,points); }
        void UpdateFreeTalentPoints(bool resetIfNeed = true);
        bool resetTalents(bool no_cost = false);
        uint32 resetTalentsCost();
        void updateResetTalentsMultiplier();
        void InitTalentForLevel();
        void LearnTalent(uint32 talentId, uint32 talentRank);
        uint32 CalculateTalentsPoints() const;

        uint32 GetFreePrimaryProfessionPoints() const { return GetUInt32Value(PLAYER_CHARACTER_POINTS2); }
        void SetFreePrimaryProfessions(uint16 profs) { SetUInt32Value(PLAYER_CHARACTER_POINTS2, profs); }
        void InitPrimaryProfessions();

        PlayerSpellMap const& GetSpellMap() const { return m_spells; }
        PlayerSpellMap      & GetSpellMap()       { return m_spells; }

        void AddSpellMod(SpellModifier* mod, bool apply);
        void SendSpellMod(SpellModifier const* mod);
        bool IsAffectedBySpellmod(SpellEntry const *spellInfo, SpellModifier *mod, Spell* spell = NULL);
        template <class T> T ApplySpellMod(uint32 spellId, SpellModOp op, T &basevalue, Spell* spell = NULL);
        SpellModifier* GetSpellMod(SpellModOp op, uint32 spellId) const;
        void RemoveSpellMods(Spell* spell);
        void RestoreSpellMods(Spell* spell, uint32 ownerAuraId = 0, Aura* aura = NULL);
        void RestoreAllSpellMods(uint32 ownerAuraId = 0, Aura* aura = NULL);
        void DropModCharge(SpellModifier* mod, Spell* spell);

        void _LoadSpellCooldowns(QueryResult *result);
        void _SaveSpellCooldowns();

        void setResurrectRequestData(ObjectGuid guid, uint32 mapId, float X, float Y, float Z, uint32 health, uint32 mana)
        {
            m_resurrectGuid = guid;
            m_resurrectMap = mapId;
            m_resurrectX = X;
            m_resurrectY = Y;
            m_resurrectZ = Z;
            m_resurrectHealth = health;
            m_resurrectMana = mana;
        }
        void clearResurrectRequestData() { setResurrectRequestData(ObjectGuid(), 0, 0.0f, 0.0f, 0.0f, 0, 0); }
        bool isRessurectRequestedBy(ObjectGuid guid) const { return m_resurrectGuid == guid; }
        bool isRessurectRequested() const { return !m_resurrectGuid.IsEmpty(); }
        void ResurectUsingRequestData();

        uint32 m_petEntry;
        uint32 m_petSpell;

        void AutoReSummonPet();

        uint32 getCinematic() { return m_cinematic; }
        void setCinematic(uint32 cine) { m_cinematic = cine; }

        static bool IsActionButtonDataValid(uint8 button, uint32 action, uint8 type, Player* player);

        PvPInfo pvpInfo;
        void UpdatePvP(bool state, bool ovrride=false);
        bool IsFFAPvP() const { return HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_FFA_PVP); }
        void SetFFAPvP(bool state);
        bool IsInInterFactionMode() const;
        void RefreshBitsForVisibleUnits(UpdateMask* mask, uint32 objectTypeMask = TYPEMASK_UNIT);

        void UpdateZone(uint32 newZone,uint32 newArea);
        void UpdateArea(uint32 newArea);
        uint32 GetCachedZoneId() const { return m_zoneUpdateId; }
        uint32 GetCachedAreaId() const { return m_areaUpdateId; }

        void UpdateZoneDependentAuras();
        void UpdateAreaDependentAuras();                    // subzones

        void UpdatePvPFlag(time_t currTime);
        void UpdateContestedPvP(uint32 currTime);
        void SetContestedPvPTimer(uint32 newTime) {m_contestedPvPTimer = newTime;}
        void ResetContestedPvP()
        {
            clearUnitState(UNIT_STAT_ATTACK_PLAYER);
            RemoveFlag(PLAYER_FLAGS, PLAYER_FLAGS_CONTESTED_PVP);
            m_contestedPvPTimer = 0;
        }

        /** todo: -maybe move UpdateDuelFlag+DuelComplete to independent DuelHandler.. **/
        DuelInfo *duel;
        bool IsInDuelWith(Player const* player) const { return duel && duel->opponent == player && duel->startTime != 0; }
        void UpdateDuelFlag(time_t currTime);
        void CheckDuelDistance(time_t currTime);
        void DuelComplete(DuelCompleteType type);
        void SendDuelCountdown(uint32 counter);

        bool IsGroupVisibleFor(Player* p) const;
        bool IsInSameGroupWith(Player const* p) const;
        bool IsInSameRaidWith(Player const* p) const { return p==this || (GetGroup() != NULL && GetGroup() == p->GetGroup()); }
        void UninviteFromGroup();
        static void RemoveFromGroup(Group* group, ObjectGuid guid);
        void RemoveFromGroup() { RemoveFromGroup(GetGroup(), GetObjectGuid()); }
        void SendUpdateToOutOfRangeGroupMembers();

        void SetInGuild(uint32 GuildId) { SetUInt32Value(PLAYER_GUILDID, GuildId); }
        void SetRank(uint32 rankId){ SetUInt32Value(PLAYER_GUILDRANK, rankId); }
        void SetGuildIdInvited(uint32 GuildId) { m_GuildIdInvited = GuildId; }
        uint32 GetGuildId() const { return GetUInt32Value(PLAYER_GUILDID);  }
        uint32 GetRank() const { return GetUInt32Value(PLAYER_GUILDRANK); }
        static uint32 GetGuildIdFromDB(ObjectGuid guid);
        static uint32 GetRankFromDB(ObjectGuid guid);
        int GetGuildIdInvited() { return m_GuildIdInvited; }
        static void RemovePetitionsAndSigns(ObjectGuid guid);

        bool UpdateSkill(uint32 skill_id, uint32 step);
        bool UpdateSkillPro(uint16 SkillId, int32 Chance, uint32 step);

        bool UpdateCraftSkill(uint32 spellid);
        bool UpdateGatherSkill(uint32 SkillId, uint32 SkillValue, uint32 RedLevel, uint32 Multiplicator = 1);
        bool UpdateFishingSkill();

        uint32 GetBaseDefenseSkillValue() const { return GetBaseSkillValue(SKILL_DEFENSE); }
        uint32 GetBaseWeaponSkillValue(WeaponAttackType attType) const;

        uint32 GetSpellByProto(ItemPrototype *proto);

        float GetHealthBonusFromStamina();
        float GetManaBonusFromIntellect();

        bool UpdateStats(Stats stat);
        bool UpdateAllStats();
        void UpdateResistances(uint32 school);
        void UpdateArmor();
        void UpdateMaxHealth();
        void UpdateMaxPower(Powers power);
        void UpdateManaRegen() override;
        void UpdateAttackPowerAndDamage(bool ranged = false);
        void UpdateDamagePhysical(WeaponAttackType attType);
        void UpdateSpellDamageAndHealingBonus();

        void CalculateMinMaxDamage(WeaponAttackType attType, bool normalized, float& min_damage, float& max_damage, uint8 index = 0);

        void UpdateDefenseBonusesMod();
        float GetMeleeCritFromAgility();
        float GetDodgeFromAgility();
        float GetSpellCritFromIntellect();
        float OCTRegenHPPerSpirit();
        float OCTRegenMPPerSpirit();

        void UpdateBlockPercentage();
        void UpdateCritPercentage(WeaponAttackType attType);
        void UpdateAllCritPercentages();
        void UpdateParryPercentage();
        void UpdateDodgePercentage();

        void UpdateAllSpellCritChances();
        void UpdateSpellCritChance(uint32 school);

        ObjectGuid const& GetLootGuid() const { return m_lootGuid; }
        void SetLootGuid(ObjectGuid const& guid) { m_lootGuid = guid; }

        void RemovedInsignia(Player* looterPlr, Corpse *corpse);

        WorldSession* GetSession() const { return m_session; }
        void SetSession(WorldSession *s);

        void BuildCreateUpdateBlockForPlayer( UpdateData *data, Player *target ) const;
        void DestroyForPlayer( Player *target ) const;
        void SendLogXPGain(uint32 GivenXP,Unit* victim,uint32 RestXP);


        uint8 LastSwingErrorMsg() const { return m_swingErrorMsg; }
        void SwingErrorMsg(uint8 val) { m_swingErrorMsg = val; }

        // notifiers
        void SendAttackSwingCantAttack();
        void SendAttackSwingCancelAttack();
        void SendAttackSwingDeadTarget();
        void SendAttackSwingNotStanding();
        void SendAttackSwingNotInRange();
        void SendAttackSwingBadFacingAttack();
        void SendAutoRepeatCancel();
        void SendExplorationExperience(uint32 Area, uint32 Experience);

        void ResetInstances(InstanceResetMethod method);
        void SendResetInstanceSuccess(uint32 MapId);
        void SendResetInstanceFailed(uint32 reason, uint32 MapId);
        void SendResetFailedNotify(uint32 mapid);
        bool CheckInstanceCount(uint32 instanceId);
        void AddInstanceEnterTime(uint32 instanceId, time_t enterTime);

        bool SetPosition(float x, float y, float z, float orientation, bool teleport = false);
        void UpdateUnderwaterState();

        void SendMessageToSet(WorldPacket *data, bool self);// overwrite Object::SendMessageToSet
        void SendMessageToSetInRange(WorldPacket *data, float fist, bool self);
                                                            // overwrite Object::SendMessageToSetInRange
        void SendMessageToSetInRange(WorldPacket *data, float dist, bool self, bool own_team_only);

        Corpse *GetCorpse() const;
        void SpawnCorpseBones();
        Corpse* CreateCorpse();
        void KillPlayer();
        uint32 GetResurrectionSpellId();
        void ResurrectPlayer(float restore_percent, bool applySickness = false);
        void BuildPlayerRepop();
        void RepopAtGraveyard();

        void DurabilityLossAll(double percent, bool inventory);
        void DurabilityLoss(Item* item, double percent);
        void DurabilityPointsLossAll(int32 points, bool inventory);
        void DurabilityPointsLoss(Item* item, int32 points);
        void DurabilityPointLossForEquipSlot(EquipmentSlots slot);
        uint32 DurabilityRepairAll(bool cost, float discountMod);
        uint32 DurabilityRepair(uint16 pos, bool cost, float discountMod);

        void UpdateMirrorTimers();
        void StopMirrorTimers()
        {
            StopMirrorTimer(FATIGUE_TIMER);
            StopMirrorTimer(BREATH_TIMER);
            StopMirrorTimer(FIRE_TIMER);
        }

        void JoinedChannel(Channel *c);
        void LeftChannel(Channel *c);
        void CleanupChannels();
        void UpdateLocalChannels( uint32 newZone );
        void LeaveLFGChannel();

        void UpdateDefense();
        void UpdateWeaponSkill (WeaponAttackType attType);
        void UpdateCombatSkills(Unit *pVictim, WeaponAttackType attType, bool defence);

        void SetSkill(uint16 id, uint16 currVal, uint16 maxVal, uint16 step = 0);
        uint16 GetMaxSkillValue(uint32 skill) const;        // max + perm. bonus + temp bonus
        uint16 GetPureMaxSkillValue(uint32 skill) const;    // max
        uint16 GetSkillValue(uint32 skill) const;           // skill value + perm. bonus + temp bonus
        uint16 GetBaseSkillValue(uint32 skill) const;       // skill value + perm. bonus
        uint16 GetPureSkillValue(uint32 skill) const;       // skill value
        int16 GetSkillPermBonusValue(uint32 skill) const;
        int16 GetSkillTempBonusValue(uint32 skill) const;
        bool HasSkill(uint32 skill) const;
        void learnSkillRewardedSpells(uint32 id, uint32 value);

        WorldLocation& GetTeleportDest() { return m_teleport_dest; }
        bool IsBeingTeleported() const { return mSemaphoreTeleport_Near || mSemaphoreTeleport_Far || mPendingFarTeleport; }
        bool IsBeingTeleportedNear() const { return mSemaphoreTeleport_Near; }
        bool IsBeingTeleportedFar() const { return mSemaphoreTeleport_Far; }
        void SetSemaphoreTeleportNear(bool semphsetting);
        void SetSemaphoreTeleportFar(bool semphsetting);
        void SetPendingFarTeleport(bool pending) { mPendingFarTeleport = pending; }
        void ProcessDelayedOperations();

        void CheckAreaExploreAndOutdoor(void);

        static Team TeamForRace(uint8 race);
        Team GetTeam() const { return m_team; }
        TeamId GetTeamId() const { return m_team == ALLIANCE ? TEAM_ALLIANCE : TEAM_HORDE; }
        static uint32 getFactionForRace(uint8 race);
        void setFactionForRace(uint8 race);

        bool ChangeRace(uint8 newRace, uint8 newGender = 255, uint32 playerbyte1 = 0, uint32 playerbyte2 = 0);
        bool ChangeItemsForRace(uint8 oldRace, uint8 newRace);
        bool ChangeReputationsForRace(uint8 oldRace, uint8 newRace);
        bool ChangeQuestsForRace(uint8 oldRace, uint8 newRace);
        bool ConvertSpell(uint32 oldSpellId, uint32 newSpellId);
        bool ChangeSpellsForRace(uint8 oldRace, uint8 newRace);

        bool IsAtGroupRewardDistance(WorldObject const* pRewardSource) const;
        void RewardSinglePlayerAtKill(Unit* pVictim);
        void RewardPlayerAndGroupAtEvent(uint32 creature_id,WorldObject* pRewardSource);
        void RewardPlayerAndGroupAtCast(WorldObject* pRewardSource, uint32 spellid = 0);
        void RewardHonor(Unit* uVictim, uint32 groupSize);
        void RewardHonorOnDeath();
        bool isHonorOrXPTarget(Unit* pVictim) const;

        ReputationMgr&       GetReputationMgr()       { return m_reputationMgr; }
        ReputationMgr const& GetReputationMgr() const { return m_reputationMgr; }
        ReputationRank GetReputationRank(uint32 faction_id) const;
        void RewardReputation(Unit *pVictim, float rate);
        void RewardReputation(Quest const *pQuest);
        int32 CalculateReputationGain(ReputationSource source, int32 rep, int32 faction, uint32 creatureOrQuestLevel = 0, bool noAuraBonus = false);

        HonorMgr&       GetHonorMgr()       { return m_honorMgr; }
        HonorMgr const& GetHonorMgr() const { return m_honorMgr; }

        void UpdateSkillsForLevel();
        void UpdateSkillsToMaxSkillsForLevel();             // for .levelup
        void ModifySkillBonus(uint32 skillid,int32 val, bool talent);

        void SetDrunkValue(uint16 newDrunkValue, uint32 itemid=0);
        uint16 GetDrunkValue() const { return m_drunk; }
        static DrunkenState GetDrunkenstateByValue(uint16 value);

        uint32 GetDeathTimer() const { return m_deathTimer; }
        uint32 GetCorpseReclaimDelay(bool pvp) const;
        void UpdateCorpseReclaimDelay();
        void SendCorpseReclaimDelay(bool load = false);

        uint32 GetShieldBlockValue() const;                 // overwrite Unit version (virtual)
        bool CanParry() const { return m_canParry; }
        void SetCanParry(bool value);
        bool CanBlock() const { return m_canBlock; }
        void SetCanBlock(bool value);
        bool CanDualWield() const { return m_canDualWield; }
        void SetCanDualWield(bool value) { m_canDualWield = value; }

        // in 0.12 and later in Unit
        void InitStatBuffMods()
        {
            for(int i = STAT_STRENGTH; i < MAX_STATS; ++i) SetFloatValue(PLAYER_FIELD_POSSTAT0 +i, 0);
            for(int i = STAT_STRENGTH; i < MAX_STATS; ++i) SetFloatValue(PLAYER_FIELD_NEGSTAT0 +i, 0);
        }
        void ApplyStatBuffMod(Stats stat, float val, bool apply) { ApplyModSignedFloatValue((val > 0 ? PLAYER_FIELD_POSSTAT0 +stat : PLAYER_FIELD_NEGSTAT0 +stat), val, apply); }
        void ApplyStatPercentBuffMod(Stats stat, float val, bool apply)
        {
            ApplyPercentModFloatValue(PLAYER_FIELD_POSSTAT0 +stat, val, apply);
            ApplyPercentModFloatValue(PLAYER_FIELD_NEGSTAT0 +stat, val, apply);
        }
        float GetPosStat(Stats stat) const { return GetFloatValue(PLAYER_FIELD_POSSTAT0 +stat); }
        float GetNegStat(Stats stat) const { return GetFloatValue(PLAYER_FIELD_NEGSTAT0 +stat); }
        float GetResistanceBuffMods(SpellSchools school, bool positive) const { return GetFloatValue(positive ? PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE+school : PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE+school ); }
        void SetResistanceBuffMods(SpellSchools school, bool positive, float val) { SetFloatValue(positive ? PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE+school : PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE+school,val); }
        void ApplyResistanceBuffModsMod(SpellSchools school, bool positive, float val, bool apply) { ApplyModSignedFloatValue(positive ? PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE+school : PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE+school, val, apply); }
        void ApplyResistanceBuffModsPercentMod(SpellSchools school, bool positive, float val, bool apply) { ApplyPercentModFloatValue(positive ? PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE+school : PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE+school, val, apply); }

        void SetRegularAttackTime(bool resetTimer = true);
        void SetBaseModValue(BaseModGroup modGroup, BaseModType modType, float value) { m_auraBaseMod[modGroup][modType] = value; }
        void HandleBaseModValue(BaseModGroup modGroup, BaseModType modType, float amount, bool apply);
        float GetBaseModValue(BaseModGroup modGroup, BaseModType modType) const;
        float GetTotalBaseModValue(BaseModGroup modGroup) const;
        float GetTotalPercentageModValue(BaseModGroup modGroup) const { return m_auraBaseMod[modGroup][FLAT_MOD] + m_auraBaseMod[modGroup][PCT_MOD]; }
        void _ApplyAllStatBonuses();
        void _RemoveAllStatBonuses();

        void _ApplyWeaponDependentAuraMods(Item *item, WeaponAttackType attackType, bool apply);
        void _ApplyWeaponDependentAuraCritMod(Item *item, WeaponAttackType attackType, Aura* aura, bool apply);
        void _ApplyWeaponDependentAuraDamageMod(Item *item, WeaponAttackType attackType, Aura* aura, bool apply);

        void _ApplyItemMods(Item *item,uint8 slot,bool apply);
        void _RemoveAllItemMods();
        void _ApplyAllItemMods();
        void _ApplyItemBonuses(ItemPrototype const *proto,uint8 slot,bool apply);
        void _ApplyAmmoBonuses();
        void InitDataForForm(bool reapplyMods = false);

        void ApplyItemEquipSpell(Item *item, bool apply, bool form_change = false);
        void ApplyEquipSpell(SpellEntry const* spellInfo, Item* item, bool apply, bool form_change = false);
        void UpdateEquipSpellsAtFormChange();
        void CastItemCombatSpell(Unit* Target, WeaponAttackType attType);
        void CastItemUseSpell(Item *item,SpellCastTargets const& targets);

        void SendInitWorldStates(uint32 zone);
        void SendUpdateWorldState(uint32 Field, uint32 Value);
        void SendDirectMessage(WorldPacket *data);

        PlayerMenu* PlayerTalkClass;
        std::vector<ItemSetEffect *> ItemSetEff;

        void SendLoot(ObjectGuid guid, LootType loot_type, Player* pVictim = NULL);

        void SendLoot(const ObjectGuid &guid, LootType loot_type, Loot& loot, PermissionTypes permission);

        void SendLootRelease(ObjectGuid guid);
        void SendNotifyLootItemRemoved(uint8 lootSlot);
        void SendNotifyLootMoneyRemoved();

        /*********************************************************/
        /***               BATTLEGROUND SYSTEM                 ***/
        /*********************************************************/

        bool InBattleGround()       const                { return m_bgData.bgInstanceID != 0; }
        bool InArena()              const;
        uint32 GetBattleGroundId()  const                { return m_bgData.bgInstanceID; }
        BattleGroundTypeId GetBattleGroundTypeId() const { return m_bgData.bgTypeID; }
        BattleGround* GetBattleGround() const;

        static uint32 GetMinLevelForBattleGroundBracketId(BattleGroundBracketId bracket_id, BattleGroundTypeId bgTypeId);
        static uint32 GetMaxLevelForBattleGroundBracketId(BattleGroundBracketId bracket_id, BattleGroundTypeId bgTypeId);
        BattleGroundBracketId GetBattleGroundBracketIdFromLevel(BattleGroundTypeId bgTypeId) const;

        bool InBattleGroundQueue() const
        {
            for (int i=0; i < PLAYER_MAX_BATTLEGROUND_QUEUES; ++i)
                if (m_bgBattleGroundQueueID[i].bgQueueTypeId != BATTLEGROUND_QUEUE_NONE)
                    return true;
            return false;
        }

        BattleGroundQueueTypeId GetBattleGroundQueueTypeId(uint32 index) const { return m_bgBattleGroundQueueID[index].bgQueueTypeId; }
        uint32 GetBattleGroundQueueIndex(BattleGroundQueueTypeId bgQueueTypeId) const
        {
            for (int i=0; i < PLAYER_MAX_BATTLEGROUND_QUEUES; ++i)
                if (m_bgBattleGroundQueueID[i].bgQueueTypeId == bgQueueTypeId)
                    return i;
            return PLAYER_MAX_BATTLEGROUND_QUEUES;
        }
        bool IsInvitedForBattleGroundQueueType(BattleGroundQueueTypeId bgQueueTypeId) const
        {
            for (int i=0; i < PLAYER_MAX_BATTLEGROUND_QUEUES; ++i)
                if (m_bgBattleGroundQueueID[i].bgQueueTypeId == bgQueueTypeId)
                    return m_bgBattleGroundQueueID[i].invitedToInstance != 0;
            return false;
        }
        bool InBattleGroundQueueForBattleGroundQueueType(BattleGroundQueueTypeId bgQueueTypeId) const
        {
            return GetBattleGroundQueueIndex(bgQueueTypeId) < PLAYER_MAX_BATTLEGROUND_QUEUES;
        }

        void SetBattleGroundId(uint32 val, BattleGroundTypeId bgTypeId)
        {
            m_bgData.bgInstanceID = val;
            m_bgData.bgTypeID = bgTypeId;
            m_bgData.m_needSave = true;
        }
        uint32 AddBattleGroundQueueId(BattleGroundQueueTypeId val)
        {
            for (int i=0; i < PLAYER_MAX_BATTLEGROUND_QUEUES; ++i)
            {
                if (m_bgBattleGroundQueueID[i].bgQueueTypeId == BATTLEGROUND_QUEUE_NONE || m_bgBattleGroundQueueID[i].bgQueueTypeId == val)
                {
                    m_bgBattleGroundQueueID[i].bgQueueTypeId = val;
                    m_bgBattleGroundQueueID[i].invitedToInstance = 0;
                    return i;
                }
            }
            return PLAYER_MAX_BATTLEGROUND_QUEUES;
        }
        bool HasFreeBattleGroundQueueId() const;
        void RemoveBattleGroundQueueId(BattleGroundQueueTypeId val)
        {
            for (int i=0; i < PLAYER_MAX_BATTLEGROUND_QUEUES; ++i)
            {
                if (m_bgBattleGroundQueueID[i].bgQueueTypeId == val)
                {
                    m_bgBattleGroundQueueID[i].bgQueueTypeId = BATTLEGROUND_QUEUE_NONE;
                    m_bgBattleGroundQueueID[i].invitedToInstance = 0;
                    return;
                }
            }
        }
        void SetInviteForBattleGroundQueueType(BattleGroundQueueTypeId bgQueueTypeId, uint32 instanceId)
        {
            for (int i=0; i < PLAYER_MAX_BATTLEGROUND_QUEUES; ++i)
                if (m_bgBattleGroundQueueID[i].bgQueueTypeId == bgQueueTypeId)
                    m_bgBattleGroundQueueID[i].invitedToInstance = instanceId;
        }
        bool IsInvitedForBattleGroundInstance(uint32 instanceId) const
        {
            for (int i=0; i < PLAYER_MAX_BATTLEGROUND_QUEUES; ++i)
                if (m_bgBattleGroundQueueID[i].invitedToInstance == instanceId)
                    return true;
            return false;
        }
        WorldLocation const& GetBattleGroundEntryPoint() const { return m_bgData.joinPos; }
        void SetBattleGroundEntryPoint(uint32 mapId, float x, float y, float z, float orientation);
        void SetBattleGroundEntryPoint(Player* leader = NULL, bool queuedAtBGPortal = false);

        void SetBGTeam(Team team) { m_bgData.bgTeam = team; m_bgData.m_needSave = true; }
        Team GetBGTeam() const { return m_bgData.bgTeam ? m_bgData.bgTeam : GetTeam(); }

        void LeaveBattleground(bool teleportToEntryPoint = true);
        bool CanJoinToBattleground() const;

        bool GetBGAccessByLevel(BattleGroundTypeId bgTypeId) const;
        bool CanUseBattleGroundObject();
        bool isTotalImmune();
        bool CanCaptureTowerPoint();

        bool bDeclineBGInvite = false;


        /*********************************************************/
        /***               OUTDOOR PVP SYSTEM                  ***/
        /*********************************************************/

        ZoneScript * GetZoneScript() const;
        // returns true if the player is in active state for outdoor pvp objective capturing, false otherwise
        bool IsOutdoorPvPActive();

        /*********************************************************/
        /***                    REST SYSTEM                    ***/
        /*********************************************************/

        bool isRested() const { return GetRestTime() >= 10*IN_MILLISECONDS; }
        uint32 GetXPRestBonus(uint32 xp);
        uint32 GetRestTime() const { return m_restTime; }
        void SetRestTime(uint32 v) { m_restTime = v; }

        /*********************************************************/
        /***              ENVIRONMENTAL SYSTEM                  ***/
        /*********************************************************/

        uint32 EnvironmentalDamage(EnvironmentalDamageType type, uint32 damage);

        /*********************************************************/
        /***               FLOOD FILTER SYSTEM                 ***/
        /*********************************************************/

        void UpdateSpeakTime();
        bool CanSpeak() const;
        void ChangeSpeakTime(int utime);

        /// Anticheat XXX FIXME TODO CHECK THESE OTHER FUNCTIONS!!
        void OnDisconnected();
        void RelocateToLastClientPosition();
        void GetSafePosition(float &x, float &y, float &z, Transport* onTransport = NULL) const;

        /*********************************************************/
        /***                 PACKET BROADCASTER                ***/
        /*********************************************************/
        std::shared_ptr<PlayerBroadcaster> m_broadcaster;
        void DeletePacketBroadcaster();
        void CreatePacketBroadcaster();
        std::shared_ptr<PlayerBroadcaster> GetPacketBroadcaster() { return m_broadcaster; }

        /*********************************************************/
        /***                 VARIOUS SYSTEMS                   ***/
        /*********************************************************/
        float m_modManaRegen;
        float m_modManaRegenInterrupt;
        float m_SpellCritPercentage[MAX_SPELL_SCHOOL];
        float m_carryHealthRegen;

        bool HasMovementFlag(MovementFlags f) const;        // for script access to m_movementInfo.HasMovementFlag
        void UpdateFallInformationIfNeed(MovementInfo const& minfo,uint16 opcode);
        void SetFallInformation(uint32 time, float z)
        {
            m_lastFallTime = time;
            m_lastFallZ = z;
        }
        void HandleFall(MovementInfo const& movementInfo);
        bool IsFalling() const { return GetPositionZ() < m_lastFallZ; }

        //Giperion Elysium: Special function, that remind client his movement information. Movement correction packet in short
        void SendMovementInfo(OpcodesList opcode = MSG_MOVE_HEARTBEAT);

        void BuildTeleportAckMsg(WorldPacket& data, float x, float y, float z, float ang) const;

        void SetClientControl(Unit* target, uint8 allowMove);
        void SetMover(Unit* target);
        Unit* GetMover() const { return m_mover; }
        bool IsSelfMover() const { return m_mover == this; }// normal case for player not controlling other unit
        bool IsNextRelocationIgnored() const { return m_bNextRelocationsIgnored ? true : false; }
        void SetNextRelocationsIgnoredCount(uint32 count) { m_bNextRelocationsIgnored = count; }
        void DoIgnoreRelocation() { if (m_bNextRelocationsIgnored) --m_bNextRelocationsIgnored; }

        void ValidateMover();

        ObjectGuid const& GetFarSightGuid() const { return GetGuidValue(PLAYER_FARSIGHT); }

        uint32 GetSaveTimer() const { return m_nextSave; }
        void   SetSaveTimer(uint32 timer) { m_nextSave = timer; }

        // Recall position
        uint32 m_recallMap;
        float  m_recallX;
        float  m_recallY;
        float  m_recallZ;
        float  m_recallO;
        void   SaveRecallPosition();

        void SetHomebindToLocation(WorldLocation const& loc, uint32 area_id);
        void RelocateToHomebind() { SetLocationMapId(m_homebindMapId); Relocate(m_homebindX, m_homebindY, m_homebindZ); }
        bool TeleportToHomebind(uint32 options = 0, bool cooldown = true);

        ///< Premium account features
        bool HasPremiumAccount() const;
        bool CanInstantFly() const;
        bool CanInstantMail() const;
        uint32 GetSpecChangeDiscount() const;
        uint32 GetItemsRepairDiscount() const;
        uint32 GetHearthstoneCDReduction() const;
        uint32 GetSkillModifier(uint16 skillID) const;

        Object* GetObjectByTypeMask(ObjectGuid guid, TypeMask typemask);

        // Stealth detection system
        void HandleStealthedUnitsDetection();
        // currently visible objects at player client
        ObjectGuidSet m_visibleGUIDs;
        mutable ACE_Thread_Mutex m_visibleGUIDs_lock;
        std::map<ObjectGuid, bool> m_visibleGobjQuestActivated;
        mutable ACE_Thread_Mutex m_visibleGobjsQuestAct_lock;

        bool IsInVisibleList(WorldObject const* u) const;
        bool IsInVisibleList_Unsafe(WorldObject const* u) const { return this == u || m_visibleGUIDs.find(u->GetObjectGuid()) != m_visibleGUIDs.end(); }

        bool IsVisibleInGridForPlayer(Player* pl) const;
        bool IsVisibleGloballyFor(Player* pl) const;

        void UpdateVisibilityOf(WorldObject const* viewPoint, WorldObject* target);

        template<class T>
            void UpdateVisibilityOf(WorldObject const* viewPoint,T* target, UpdateData& data, std::set<WorldObject*>& visibleNow);

        Camera& GetCamera() { return m_camera; }

        bool HasAtLoginFlag(AtLoginFlags f) const { return m_atLoginFlags & f; }
        void SetAtLoginFlag(AtLoginFlags f) { m_atLoginFlags |= f; }
        void RemoveAtLoginFlag(AtLoginFlags f, bool in_db_also = false);

        // Temporarily removed pet cache
        uint32 GetTemporaryUnsummonedPetNumber() const { return m_temporaryUnsummonedPetNumber; }
        void SetTemporaryUnsummonedPetNumber(uint32 petnumber) { m_temporaryUnsummonedPetNumber = petnumber; }
        void UnsummonPetTemporaryIfAny();
        void ResummonPetTemporaryUnSummonedIfAny();
        bool IsPetNeedBeTemporaryUnsummoned() const { return !IsInWorld() || !isAlive() || IsMounted() /*+in flight*/; }

        void SendCinematicStart(uint32 CinematicSequenceId);
        // Nostalrius : Gestion des cinematiques avancee
        void UpdateCinematic(uint32 diff);
        void CinematicEnd();
        void CinematicStart(uint32 id);

        bool CanWalk() const { return true; }
        bool CanSwim() const { return true; }
        bool CanFly() const { return IsFlying(); }

        uint32 watching_cinematic_entry;
        Position cinematic_start;
        Position const* cinematic_current_waypoint;
        uint32 cinematic_last_check;
        uint32 cinematic_elapsed_time;

        // Nostalrius : Phasing
        virtual void SetWorldMask(uint32 newMask);

        // Custom Flags
        void LoadCustomFlags();

        uint32 GetCustomFlags() { return customFlags; }
        inline void SetCustomFlags(uint32 newFlags) { customFlags = newFlags; }

        inline bool HasCustomFlag(uint32 flag) { return (customFlags & flag); }
        inline void AddCustomFlag(uint32 flag) { customFlags |= flag; }
        inline void RemoveCustomFlag(uint32 flag) { customFlags &= ~flag; }
        uint32 customFlags;
        // Anti undermap
        void SaveNoUndermapPosition(float x, float y, float z)
        {
            _lastSafeX = x;
            _lastSafeY = y;
            _lastSafeZ = z;
            _undermapPosValid = true;
        }
        bool UndermapRecall()
        {
            if (!_undermapPosValid || IsBeingTeleported())
                return false;
            if (GetDistance2d(_lastSafeX, _lastSafeY) > 100.0f)
            {
                _undermapPosValid = false;
                return false;
            }
            NearTeleportTo(_lastSafeX, _lastSafeY, _lastSafeZ+2.0f, GetOrientation(), TELE_TO_NOT_LEAVE_COMBAT | TELE_TO_NOT_UNSUMMON_PET);
            _undermapPosValid = false;
            return true;
        }
        float _lastSafeX;
        float _lastSafeY;
        float _lastSafeZ;
        bool  _undermapPosValid;

        /*********************************************************/
        /***                 INSTANCE SYSTEM                   ***/
        /*********************************************************/

        typedef std::unordered_map< uint32 /*mapId*/, InstancePlayerBind > BoundInstancesMap;

        void UpdateHomebindTime(uint32 time);

        uint32 m_HomebindTimer;
        bool m_InstanceValid;
        // permanent binds and solo binds
        BoundInstancesMap m_boundInstances;
        InstancePlayerBind* GetBoundInstance(uint32 mapid);
        BoundInstancesMap& GetBoundInstances() { return m_boundInstances; }
        void UnbindInstance(uint32 mapid, bool unload = false);
        void UnbindInstance(BoundInstancesMap::iterator &itr, bool unload = false);
        InstancePlayerBind* BindToInstance(DungeonPersistentState *save, bool permanent, bool load = false);
        void SendRaidInfo();
        void SendSavedInstances();
        static void ConvertInstancesToGroup(Player *player, Group *group = NULL, ObjectGuid player_guid = ObjectGuid());
        DungeonPersistentState* GetBoundInstanceSaveForSelfOrGroup(uint32 mapid);

        /*********************************************************/
        /***                   GROUP SYSTEM                    ***/
        /*********************************************************/

        Group * GetGroupInvite() { return m_groupInvite; }
        void SetGroupInvite(Group *group) { m_groupInvite = group; }
        Group * GetGroup() { return m_group.getTarget(); }
        const Group * GetGroup() const { return (const Group*)m_group.getTarget(); }
        GroupReference& GetGroupRef() { return m_group; }
        void SetGroup(Group *group, int8 subgroup = -1);
        uint8 GetSubGroup() const { return m_group.getSubGroup(); }
        uint32 GetGroupUpdateFlag() const { return m_groupUpdateMask; }
        void SetGroupUpdateFlag(uint32 flag) { m_groupUpdateMask |= flag; }
        const uint64& GetAuraUpdateMask() const { return m_auraUpdateMask; }
        void SetAuraUpdateSlot(uint8 slot) { m_auraUpdateMask |= (uint64(1) << slot); }
        void SetAuraUpdateMask(uint64 mask) { m_auraUpdateMask = mask; }
        Player* GetNextRandomRaidMember(float radius);
        PartyResult CanUninviteFromGroup(ObjectGuid uninvitedGuid) const;
        void UpdateGroupLeaderFlag(const bool remove = false);
        // BattleGround Group System
        void SetBattleGroundRaid(Group *group, int8 subgroup = -1);
        void RemoveFromBattleGroundRaid();
        Group * GetOriginalGroup() { return m_originalGroup.getTarget(); }
        GroupReference& GetOriginalGroupRef() { return m_originalGroup; }
        uint8 GetOriginalSubGroup() const { return m_originalGroup.getSubGroup(); }
        void SetOriginalGroup(Group *group, int8 subgroup = -1);

        GridReference<Player> &GetGridRef() { return m_gridRef; }
        MapReference &GetMapRef() { return m_mapRef; }

        bool isAllowedToLoot(Creature const* creature);
        // Nostalrius
        // Gestion des PlayerAI
        PlayerAI* i_AI;
        PlayerAI* AI() { return i_AI; }
        void setAI(PlayerAI* otherAI) { i_AI = otherAI; }
        void SetControlledBy(Unit *Who);
        void RemoveAI();
        void ModPossessPet(Pet* pet, bool apply, AuraRemoveMode m_removeMode = AURA_REMOVE_BY_DEFAULT);
        // Changement de faction
        bool m_DbSaveDisabled;

        uint32 m_lastFromClientCastedSpellID;
        void SetLastCastedSpell(uint32 spell_id, bool byclient);
        uint32 GetLastCastedSpell(bool byclientonly);

        void SendDestroyGroupMembers(bool includingSelf = false);

        void RemoveDelayedOperation(uint32 operation)
        {
            m_DelayedOperations &= ~operation;
        }

        inline bool HasScheduledEvent() const { return m_Events.HasScheduledEvent(); }
        void SetAutoInstanceSwitch(bool v) { m_enableInstanceSwitch = v; }
    protected:
        bool   m_enableInstanceSwitch;
        uint32 m_skippedUpdateTime;
        uint32 m_DetectInvTimer;

    public:
        void AddSkippedUpdateTime(uint32 t) { m_skippedUpdateTime += t; }
        uint32 GetSkippedUpdateTime() const { return m_skippedUpdateTime; }
        void ResetSkippedUpdateTime() { m_skippedUpdateTime = 0; }
        uint32 GetGMInvisibilityLevel() const { return m_gmInvisibilityLevel; }
        void SetGMInvisibilityLevel(uint32 level) { m_gmInvisibilityLevel = level; }
        uint32 GetGMTicketCounter() const { return m_currentTicketCounter; }
        void SetGMTicketCounter(uint32 counter) { m_currentTicketCounter = counter; }
        bool GetSmartInstanceBindingMode() { return m_smartInstanceRebind; }
        void SetSmartInstanceBindingMode(bool smartRebinding) { m_smartInstanceRebind = smartRebinding; }

        void ScheduleDelayedOperation(uint32 operation)
        {
            if (operation < DELAYED_END)
                m_DelayedOperations |= operation;
        }

        template <typename F>
        void ScheduleGenericDelayedAction(F f) { m_delayedGenericActions.push_back(f); }

        PlayerTaxi const& GetTaxi() const { return m_taxi; }
        uint32 GetHomeBindMap() const { return m_homebindMapId; }
        uint16 GetHomeBindAreaId() const { return m_homebindAreaId; }

        void IncrementRegexFilterCounter() { ++m_RegexFilterCount; }
        uint32 GetRegexFilterCount() const { return m_RegexFilterCount; }

        //for inactivity
        void UpdateMovementActivityTimer();
        void UpdateSpellActivityTimer();
        void UpdateChatActivityTimer();
        void UpdateVelocity();
        void UpdateSavedVelocityPositionToCurrentPos();

        float GetVelocity(uint32 deltaTime, WorldLocation PrevPos) const;
        float GetVelocityPerSecond() const
        {
            return m_velocity;
        }
        float GetVelocityPer3Min() const
        {
            return m_velocityPer3Min;
        }

        uint32 GetLastMovementTime() const
        {
            return m_lastMovementTimer;
        }

        uint32 GetLastSpellCastedTime() const
        {
            return m_lastSpellTimer;
        }

        uint32 GetLastChatMessageTime() const
        {
            return m_lastChatMessageTimer;
        }

        bool IsBasicallyInactive(bool bIncludeChat = false) const;

        //#TEMP
        //#REFACTOR: Remove this later, added because of deadline
        bool bIsReportedAsSpeedhacker = false;

         void SetForced_X1_XpRate(bool forced) { m_forced_X1_XpRate = forced; }
         bool Forced_X1_XpRate() { return m_forced_X1_XpRate; }
         void ShowCurrentXpRate();

    protected:


        uint32 m_contestedPvPTimer;

        /*********************************************************/
        /***               BATTLEGROUND SYSTEM                 ***/
        /*********************************************************/

        /*
        this is an array of BG queues (BgTypeIDs) in which is player
        */
        struct BgBattleGroundQueueID_Rec
        {
            BattleGroundQueueTypeId bgQueueTypeId;
            uint32 invitedToInstance;
        };

        BgBattleGroundQueueID_Rec m_bgBattleGroundQueueID[PLAYER_MAX_BATTLEGROUND_QUEUES];
        BGData                    m_bgData;

        /*********************************************************/
        /***                    QUEST SYSTEM                   ***/
        /*********************************************************/

        //We allow only one timed quest active at the same time. Below can then be simple value instead of set.
        typedef std::set<uint32> QuestSet;
        QuestSet m_timedquests;

        ObjectGuid m_dividerGuid;
        uint32 m_ingametime;

        /*********************************************************/
        /***                   LOAD SYSTEM                     ***/
        /*********************************************************/

        void LoadAura(AuraSaveStruct& saveStruct, uint32 timediff);
        bool SaveAura(SpellAuraHolder* holder, AuraSaveStruct& saveStruct);

        void _LoadActions(QueryResult *result);
        void _LoadAuras(QueryResult *result, uint32 timediff);
        void _LoadBoundInstances(QueryResult *result);
        void _LoadBrokenItems(QueryResult* result);
        void _LoadInventory(QueryResult *result, uint32 timediff);
        void _LoadItemLoot(QueryResult *result);
        void _LoadMails(QueryResult *result);
        void _LoadMailedItems(QueryResult *result);
        void _LoadQuestStatus(QueryResult *result);
        void _LoadGroup(QueryResult *result);
        void _LoadSkills(QueryResult *result);
        void LoadSkillsFromFields();
        void _LoadSpells(QueryResult *result);
        void _LoadFriendList(QueryResult *result);
        bool _LoadHomeBind(QueryResult *result);
        void _LoadBGData(QueryResult* result);
        void _LoadIntoDataField(const char* data, uint32 startOffset, uint32 count);

        /*********************************************************/
        /***                   SAVE SYSTEM                     ***/
        /*********************************************************/

        void _SaveActions();
        void _SaveAuras();
        void _SaveInventory();
        void _SaveMail();
        void _SaveQuestStatus();
        void _SaveSkills();
        void _SaveSpells();
        void _SaveBGData();
        void _SaveStats();
        void _SaveArmoryStats();

        void _SetCreateBits(UpdateMask *updateMask, Player *target) const;
        void _SetUpdateBits(UpdateMask *updateMask, Player *target) const;

        /*********************************************************/
        /***              ENVIRONMENTAL SYSTEM                 ***/
        /*********************************************************/
        void HandleSobering();
        void SendMirrorTimer(MirrorTimerType Type, uint32 MaxValue, uint32 CurrentValue, int32 Regen);
        void StopMirrorTimer(MirrorTimerType Type);
        void HandleDrowning(uint32 time_diff);
        int32 getMaxTimer(MirrorTimerType timer);
        int32 m_MirrorTimer[MAX_TIMERS];
        uint8 m_MirrorTimerFlags;
        uint8 m_MirrorTimerFlagsLast;

        void outDebugStatsValues() const;
        ObjectGuid m_lootGuid;

        Team m_team;
        uint32 m_nextSave;
        uint32 m_atLoginFlags;

        Item* m_items[PLAYER_SLOTS_COUNT];
        uint32 m_currentBuybackSlot;

        std::vector<Item*> m_itemUpdateQueue;
        bool m_itemUpdateQueueBlocked;

        // Dynamic flags for internal usage
        uint32 m_dynamicFlags;
        void UpdateDonateTokenFlag(uint32 itemId, bool added);
        void FillDonateTokensFlags();
        bool HasDynamicFlag(PlayerDynamicFlags flag) { return (m_dynamicFlags & flag); }

        bool m_forced_X1_XpRate;

        uint32 m_ExtraFlags;
        ObjectGuid m_curSelectionGuid;

        ObjectGuid m_comboTargetGuid;
        int8 m_comboPoints;

        QuestStatusMap mQuestStatus;

        SkillStatusMap mSkillStatus;

        uint32 m_GuildIdInvited;

        PlayerSpellMap m_spells;

        float m_auraBaseMod[BASEMOD_END][MOD_END];

        SpellModList m_spellMods[MAX_SPELLMOD];
        EnchantDurationList m_enchantDuration;
        ItemDurationList m_itemDuration;

        ObjectGuid m_resurrectGuid;
        uint32 m_resurrectMap;
        float m_resurrectX, m_resurrectY, m_resurrectZ;
        uint32 m_resurrectHealth, m_resurrectMana;

        WorldSession *m_session;

        typedef std::list<Channel*> JoinedChannelsList;
        JoinedChannelsList m_channels;

        // has a value of zero when the player needs to see the initial cinematic for their race
        uint32 m_cinematic;

        TradeData* m_trade;

        uint32 m_drunkTimer;
        uint16 m_drunk;
        uint32 m_weaponChangeTimer;

        uint32 m_zoneUpdateId;
        uint32 m_zoneUpdateTimer;
        uint32 m_areaUpdateId;

        uint32 m_deathTimer;
        time_t m_deathExpireTime;

        uint32 m_restTime;

        uint32 m_WeaponProficiency;
        uint32 m_ArmorProficiency;
        bool m_canParry;
        bool m_canBlock;
        bool m_canDualWield;
        uint8 m_swingErrorMsg;
        float m_ammoDPS;

        ////////////////////Rest System/////////////////////
        time_t time_inn_enter;
        uint32 inn_trigger_id;
        float m_rest_bonus;
        RestType rest_type;
        ////////////////////Rest System/////////////////////

        uint32 m_resetTalentsMultiplier;
        time_t m_resetTalentsTime;
        uint32 m_usedTalentCount;

        // Groups
        GroupReference m_group;
        GroupReference m_originalGroup;
        Group *m_groupInvite;
        uint32 m_groupUpdateMask;
        uint64 m_auraUpdateMask;

        ObjectGuid m_miniPetGuid;

        // Player summoning
        time_t m_summon_expire;
        uint32 m_summon_mapid;
        float  m_summon_x;
        float  m_summon_y;
        float  m_summon_z;

        // GM variables
        uint32 m_gmInvisibilityLevel;
        uint32 m_currentTicketCounter;
        bool m_smartInstanceRebind;

        // to fix an 1.12 client problem with transports
        // sometimes they need a refresh before being usable
        bool m_justBoarded;
        void SetJustBoarded(bool hasBoarded) { m_justBoarded = hasBoarded; }
        bool HasJustBoarded() { return m_justBoarded; }

    private:
        // internal common parts for CanStore/StoreItem functions
        InventoryResult _CanStoreItem_InSpecificSlot( uint8 bag, uint8 slot, ItemPosCountVec& dest, ItemPrototype const *pProto, uint32& count, bool swap, Item *pSrcItem ) const;
        InventoryResult _CanStoreItem_InBag( uint8 bag, ItemPosCountVec& dest, ItemPrototype const *pProto, uint32& count, bool merge, bool non_specialized, Item *pSrcItem, uint8 skip_bag, uint8 skip_slot ) const;
        InventoryResult _CanStoreItem_InInventorySlots( uint8 slot_begin, uint8 slot_end, ItemPosCountVec& dest, ItemPrototype const *pProto, uint32& count, bool merge, Item *pSrcItem, uint8 skip_bag, uint8 skip_slot ) const;
        Item* _StoreItem( uint16 pos, Item *pItem, uint32 count, bool clone, bool update );

        void SendSurpriseBox();

        void UpdateKnownCurrencies(uint32 itemId, bool apply);
        void AdjustQuestReqItemCount( Quest const* pQuest, QuestStatusData& questStatusData );

        void SetCanDelayTeleport(bool setting) { m_bCanDelayTeleport = setting; }
        bool IsHasDelayedTeleport() const
        {
            // we should not execute delayed teleports for now dead players but has been alive at teleport
            // because we don't want player's ghost teleported from graveyard
            return m_bHasDelayedTeleport && (isAlive() || !m_bHasBeenAliveAtDelayedTeleport);
        }

        bool SetDelayedTeleportFlagIfCan()
        {
            m_bHasDelayedTeleport = m_bCanDelayTeleport;
            m_bHasBeenAliveAtDelayedTeleport = isAlive();
            return m_bHasDelayedTeleport;
        }

        bool IsAllowedToMove(Unit* unit) const;

        bool CanGetXPFromExploration() const;

        Unit *m_mover;
        //Can be not the same as WorldSession::_clientMoverGuid
        ObjectGuid m_mover_guid;

        Camera m_camera;

        GridReference<Player> m_gridRef;
        MapReference m_mapRef;

        // Homebind coordinates
        uint32 m_homebindMapId;
        uint16 m_homebindAreaId;
        float m_homebindX;
        float m_homebindY;
        float m_homebindZ;

        uint32 m_lastFallTime;
        float  m_lastFallZ;

        LiquidTypeEntry const* m_lastLiquid;
        bool m_isInWater;

        // Current teleport data
        WorldLocation m_teleport_dest;
        uint32 m_teleport_options;
        std::function<void()> m_teleportRecover;
        std::function<void()> m_teleportRecoverDelayed;
        bool mSemaphoreTeleport_Near;
        bool mSemaphoreTeleport_Far;
        bool mPendingFarTeleport;

        uint32 m_DelayedOperations;
        std::vector < std::function<void(Player*)> > m_delayedGenericActions;
        bool m_bCanDelayTeleport;
        bool m_bHasDelayedTeleport;
        bool m_bHasBeenAliveAtDelayedTeleport;
        uint32 m_areaCheckTimer; // Trigger call to UpdateUnderwaterState/CheckAreaExploreAndOutdoor

        // Temporary removed pet cache
        uint32 m_temporaryUnsummonedPetNumber;

        HonorMgr  m_honorMgr;

        ReputationMgr  m_reputationMgr;
        ObjectGuid     m_selectedGobj; // For GM commands

        int32 m_cannotBeDetectedTimer;

        uint32 m_bNextRelocationsIgnored;

        uint32_t m_RegexFilterCount = 0;

        //for inactivity checking
        uint32 m_lastMovementTimer = 0;
        uint32 m_lastSpellTimer = 0;
        uint32 m_lastChatMessageTimer = 0;

        //Velocity calculator
        //It's a 2d linear combined XY velocity

        //velocity per second
        float m_velocity = 0.0f;

        //velocity per 3 min
        float m_velocityPer3Min = 0.0f;

        uint32 m_lastUpdatedVelocityPerSecondTimer = 0;
        uint32 m_lastUpdatedVelocityPer3MinTimer = 0;

        WorldLocation m_lastSecondPosition;
        WorldLocation m_last3MinPosition;

        uint32 m_lastAreaExplorationTime = 0;

public:
        /**
         * @brief Handles serialization / unserialization of the Object.
         * Should not be called directly. Cf Serializer.h
         * @param buf
         */
        template <typename OP>
        void Serialize(OP& buf);
        /**
         * @brief Call this before reading unserialization
         * @return false iif the player is corrupt.
         */
        bool PrepareWakeUp(ObjectGuid guid);
        /**
         * @brief Call this once unserialized to get a proper Player (add to Map, etc ...)
         * @return false iif the player is corrupt.
         */
        bool WakeUp();
protected:
        template <typename OP>
        void SerializeAuras(OP& buf);
        template <typename OP>
        void SerializeInventory(OP& buf);
        template <typename OP>
        void SerializeItemLoot(OP& buf);
        template <typename OP>
        void SerializeQuestStatus(OP& buf);
        template <typename OP>
        void SerializeSkills(OP& buf);
        template <typename OP>
        void SerializeSpells(OP& buf);
        template <typename OP>
        void SerializeSpellCooldowns(OP& buf);
};

void AddItemsSetItem(Player*player,Item *item);
void RemoveItemsSetItem(Player*player,ItemPrototype const *proto);

// "the bodies of template functions must be made available in a header file"
template <class T> T Player::ApplySpellMod(uint32 spellId, SpellModOp op, T &basevalue, Spell* spell)
{
    SpellEntry const *spellInfo = sSpellMgr.GetSpellEntry(spellId);
    if (!spellInfo) return 0;
    int32 totalpct = 0;
    int32 totalflat = 0;
    for (SpellModList::iterator itr = m_spellMods[op].begin(); itr != m_spellMods[op].end(); ++itr)
    {
        SpellModifier *mod = *itr;

        if (!IsAffectedBySpellmod(spellInfo,mod,spell))
            continue;

        if (mod->type == SPELLMOD_FLAT)
            totalflat += mod->value;
        else if (mod->type == SPELLMOD_PCT)
        {
            // skip percent mods for null basevalue (most important for spell mods with charges )
            if(basevalue == T(0))
                continue;

            // special case (skip >10sec spell casts for instant cast setting)
            if( mod->op==SPELLMOD_CASTING_TIME  && basevalue >= T(10*IN_MILLISECONDS) && mod->value <= -100)
                continue;

            totalpct += mod->value;
        }

        DropModCharge(mod, spell);

        // Nostalrius : fix ecorce (22812 - +1sec incant) + rapidite nature (17116 - sorts instant) = 0sec de cast
        if (mod->op == SPELLMOD_CASTING_TIME && mod->type == SPELLMOD_PCT && mod->value == -100)
        {
            totalpct = -100;
            totalflat = 0;
            break;
        }
    }

    float diff = (float)basevalue*(float)totalpct/100.0f + (float)totalflat;
    basevalue = T((float)basevalue + diff);
    return T(diff);
}

#endif
