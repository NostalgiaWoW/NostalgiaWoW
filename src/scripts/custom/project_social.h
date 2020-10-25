

#include <Errors.h>
#include <Objects/Player.h>

enum
{
    SPELL_CLOUDAURA = 28362,
    NPC_INFECTION_CLOUD = 1000600,
    NPC_INFECTION_CLOUD_QUEST = 1000602,
    TIMER_INFECT = 45 * IN_MILLISECONDS,
    RADIUS_INFECT = 3,

    EVENT_VIRUS = 172,

    NPC_INFECTION_PROTECT = 1000601,
    RADIUS_INFECTION_PROTECT = 10,

    NPC_NURSE = 1100005,
    NPC_MEDICAL_HEALER = 1100000,
    NPC_ALERT_BOT = 1100001,
    NPC_SUPPLIES_MULE = 1100002,
    NPC_MEDICAL_GUARD1 = 1100006,
    NPC_MEDICAL_GUARD2 = 1100008,
    NPC_MEDICAL_GUARD3 = 1100009,
    NPC_MEDICAL_DISPENSER = 1100010,

    CHANCE_BASE_INFECT = 100,
    CHANCE_OBJECT_INFECT = 50,

    MESSAGE_WARN_TICKLE = 81000,
    MESSAGE_WARN_INFECTED = 81001,
    MESSAGE_HANDS_WASHED = 81002,
    MESSAGE_HANDS_TIMETOWASH = 81003,
    MESSAGE_HANDS_WASHWITHSOAP = 81004,
    MESSAGE_CURED = 81005,
    MESSAGE_YOU_CURED_BY = 81021,

    MESSAGE_SANITIZED_OBJECT = 81006,
    MESSAGE_SANITIZED_OTHER = 81007,
    MESSAGE_SANITIZED_SELF = 81008,
    MESSAGE_TARGET_FAR_AWAY = 81009,
    MESSAGE_TARGET_NOT_FOUND = 81010,
    MESSAGE_CURED_OTHER = 81019,
    MESSAGE_ERROR_NOTINFECTED = 81020,

    ITEM_SOAP = 90001,
    ITEM_SANITIZER = 90002,
    ITEM_FACEMASK = 90003,

    CHANCE_FACEMASK_RESIST = 40,
    CHANCE_SANITIZED_RESIST = 50,

    SPELL_ONSET = 37000, // required serverside spell.dbc
    SPELL_INFECTION = 37001, // required serverside spell.dbc
    SPELL_CLEAN_HANDS = 37002, // required serverside spell.dbc
    SPELL_SANITIZE = 37003, // required serverside spell.dbc
    SPELL_INFECTION_NPC = 37004, // required serverside spell.dbc


    GOSSIP_TEXT_MAIN = 81010,
    GOSSIP_E_NOT_INFECTED = 81011,
    GOSSIP_E_BAC_DETECTED = 81012,
    GOSSIP_E_INFECTION_DETECTED = 81013,
    GOSSIP_E_CLEAN_HANDS = 81014,
    GOSSIP_E_SANITIZED = 81015,
    GOSSIP_E_MASK = 81016,
    GOSSIP_E_TARGET = 81017,
    GOSSIP_E_BEEP = 81018,

    QUEST_WASH_HANDS_A = 20001,
    QUEST_SANITIZE_OWN_A = 20002,
    QUEST_SANITIZE_SOMEONE_A = 20003,
    QUEST_SANITIZE_SURFACE_A = 20004,
    QUEST_VIRUS_TESTER_A = 20005,

    QUEST_WASH_HANDS_H = 20011,
    QUEST_SANITIZE_OWN_H = 20012,
    QUEST_SANITIZE_SOMEONE_H = 20013,
    QUEST_SANITIZE_SURFACE_H = 20014,
    QUEST_VIRUS_TESTER_H = 20015,

    GO_HANDWASH_STATION = 600001,

    GO_INFECTED_OBJECT = 3100008,

    EMOTE_DIZZY = -1999500,
    EMOTE_COUGH = -1999501,
    EMOTE_SNEEZE = -1999502,
    CHANCE_EMOTE = 5
};

void infection_CurePlayer(Player* player);
void infection_InfectPlayer(Player* player);
void infection_CleanHandsPlayer(Player* player);
void infection_PlayerTouchInfected(Player* player);
void infection_InfectNearestObjects(Unit* infector);
void infection_OnsetPlayer(Player* player, Player* infector);
void infection_OnsetNearestPlayers(Unit* infector);
void custom_HandleAuraDummy(Aura* aura, Unit* target, bool apply, AuraRemoveMode m_removeMode);
void custom_AuraUpdate(Aura* aura);
void addToDBIfNotExist(Player* player);

void AddSC_project_social();