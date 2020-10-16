//This file included in Anticheat.hpp. This private table information

static ChatCommand anticheatFingerprintCommandTable[] =
{
    { NODE, "list",      SEC_ADMINISTRATOR, false, &ChatHandler::HandleAnticheatFingerprintListCommand,      "", nullptr },
    { NODE, "history",   SEC_ADMINISTRATOR, false, &ChatHandler::HandleAnticheatFingerprintHistoryCommand,      "", nullptr },
    { NODE, "ahistory",  SEC_ADMINISTRATOR, false, &ChatHandler::HandleAnticheatFingerprintAHistoryCommand,      "", nullptr },
    { MSTR, nullptr,   0,                  false, nullptr,                                             "", nullptr },
};

static ChatCommand anticheatCommandTable[] =
{
    { NODE, "info",         SEC_GAMEMASTER,    true,  &ChatHandler::HandleAnticheatInfoCommand,           "", nullptr },
    { NODE, "enable",       SEC_ADMINISTRATOR, true,  &ChatHandler::HandleAnticheatEnableCommand,         "", nullptr },
    { NODE, "silence",      SEC_GAMEMASTER,    false, &ChatHandler::HandleAnticheatSilenceCommand,        "", nullptr },
    { NODE, "unsilence",    SEC_GAMEMASTER,    false, &ChatHandler::HandleAnticheatUnsilenceCommand,      "", nullptr },
    { NODE, "spaminfo",     SEC_ADMINISTRATOR, false, &ChatHandler::HandleAnticheatSpaminfoCommand,       "", nullptr },
    { NODE, "fingerprint",  SEC_ADMINISTRATOR, false, nullptr,                                            "", anticheatFingerprintCommandTable },
    { NODE, "cheatinform",  SEC_GAMEMASTER,    false, &ChatHandler::HandleAnticheatCheatinformCommand,    "", nullptr },
    { NODE, "spaminform",   SEC_GAMEMASTER,    false, &ChatHandler::HandleAnticheatSpaminformCommand,     "", nullptr },
    { NODE, "blacklist",    SEC_GAMEMASTER,    false, &ChatHandler::HandleAnticheatBlacklistCommand,      "", nullptr },
    { NODE, "debugextrap",  SEC_ADMINISTRATOR, true,  &ChatHandler::HandleAnticheatDebugExtrapCommand,    "", nullptr },
    { MSTR, nullptr,   0,                  false, nullptr,                                             "", nullptr },
};