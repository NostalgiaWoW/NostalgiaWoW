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

#include "AccountMgr.h"
#include "Database/DatabaseEnv.h"
#include "ObjectAccessor.h"
#include "ObjectGuid.h"
#include "Player.h"
#include "Policies/SingletonImp.h"
#include "Util.h"
#include "Auth/Sha1.h"
#include "World.h"
#include "Chat.h"
#include "WorldSession.h"
#include "Chat.h"
#include "MasterPlayer.h"

#include <mutex>
#include <unordered_map>

extern DatabaseType LoginDatabase;

INSTANTIATE_SINGLETON_1(AccountMgr);

AccountMgr::AccountMgr() : _banlistUpdateTimer(0)
{}

AccountOpResult AccountMgr::CreateAccount(std::string username, std::string password) const
{
    if (utf8length(username) > MAX_ACCOUNT_STR)
        return AOR_NAME_TOO_LONG;                           // username's too long

    normalizeString(username);
    normalizeString(password);

    if (GetId(username))
        return AOR_NAME_ALREDY_EXIST;                       // username does already exist

    if (!LoginDatabase.PExecute("INSERT INTO account(username,sha_pass_hash,joindate) VALUES('%s','%s',NOW())", username.c_str(), CalculateShaPassHash(username, password).c_str()))
        return AOR_DB_INTERNAL_ERROR;                       // unexpected error
    LoginDatabase.Execute("INSERT INTO realmcharacters (realmid, acctid, numchars) SELECT realmlist.id, account.id, 0 FROM realmlist,account LEFT JOIN realmcharacters ON acctid=account.id WHERE acctid IS NULL");

    return AOR_OK;                                          // everything's fine
}

AccountOpResult AccountMgr::DeleteAccount(uint32 accountId)
{
    QueryResult *result = LoginDatabase.PQuery("SELECT 1 FROM account WHERE id='%u'", accountId);
    if (!result)
        return AOR_NAME_NOT_EXIST;                          // account doesn't exist
    delete result;

    // existing characters list
    result = CharacterDatabase.PQuery("SELECT guid FROM characters WHERE account='%u'", accountId);
    if (result)
    {
        do
        {
            Field *fields = result->Fetch();
            uint32 guidlo = fields[0].GetUInt32();
            ObjectGuid guid = ObjectGuid(HIGHGUID_PLAYER, guidlo);

            // kick if player currently
            ObjectAccessor::KickPlayer(guid);
            Player::DeleteFromDB(guid, accountId, false);       // no need to update realm characters
        }
        while (result->NextRow());

        delete result;
    }

    // table realm specific but common for all characters of account for realm
    CharacterDatabase.PExecute("DELETE FROM character_tutorial WHERE account = '%u'", accountId);

    LoginDatabase.BeginTransaction();

    bool res =
        LoginDatabase.PExecute("DELETE FROM account WHERE id='%u'", accountId) &&
        LoginDatabase.PExecute("DELETE FROM realmcharacters WHERE acctid='%u'", accountId);

    LoginDatabase.CommitTransaction();

    // remove references to this account from our own memory
    std::lock_guard<std::mutex> guard(_mutex);
    _accountSecurity.erase(accountId);
    _accountBanned.erase(accountId);
    _instanceEnterTimes.erase(accountId);
    _accountPersistentData.erase(accountId);

    if (!res)
        return AOR_DB_INTERNAL_ERROR;                       // unexpected error;

    return AOR_OK;
}

AccountOpResult AccountMgr::ChangePassword(uint32 accountId, std::string new_passwd, std::string username) const
{
    if (username == "")
    {
        if (!GetName(accountId, username))
            return AOR_NAME_NOT_EXIST;
    }
    else
        normalizeString(username);                       // account doesn't exist

    if (utf8length(new_passwd) > MAX_ACCOUNT_STR)
        return AOR_PASS_TOO_LONG;

    normalizeString(new_passwd);

    // also reset s and v to force update at next realmd login
    if (!LoginDatabase.PExecute("UPDATE account SET v='0', s='0', sha_pass_hash='%s' WHERE id='%u'",
                                CalculateShaPassHash(username, new_passwd).c_str(), accountId))
        return AOR_DB_INTERNAL_ERROR;                       // unexpected error

    return AOR_OK;
}

uint32 AccountMgr::GetId(std::string username) const
{
    LoginDatabase.escape_string(username);
    QueryResult *result = LoginDatabase.PQuery("SELECT id FROM account WHERE username = '%s'", username.c_str());
    if (!result)
        return 0;
    else
    {
        uint32 id = (*result)[0].GetUInt32();
        delete result;
        return id;
    }
}

void AccountMgr::Load()
{
    LoadAccountSecurityList();
    LoadAccountBanList();
    LoadIPBanList();
}

AccountTypes AccountMgr::GetSecurity(uint32 accountId) const
{
    std::lock_guard<std::mutex> guard(_mutex);

    auto const it = _accountSecurity.find(accountId);

    return it == _accountSecurity.end() ? SEC_PLAYER : it->second;
}

bool AccountMgr::GetName(uint32 accountId, std::string &name) const
{
    QueryResult *result = LoginDatabase.PQuery("SELECT username FROM account WHERE id = '%u'", accountId);
    if (result)
    {
        name = (*result)[0].GetCppString();
        delete result;
        if (normalizeString(name))
            return true;
    }

    return false;
}

uint32 AccountMgr::GetFlags(uint32 accountId) const
{
    QueryResult *result = LoginDatabase.PQuery("SELECT flags FROM account WHERE id = '%u'", accountId);

    uint32 ret = 0;

    if (result)
        ret = (*result)[0].GetUInt32();

    delete result;
    return ret;
}

uint32 AccountMgr::GetCharactersCount(uint32 accountId) const
{
    // check character count
    QueryResult *result = CharacterDatabase.PQuery("SELECT COUNT(guid) FROM characters WHERE account = '%u'", accountId);
    if (result)
    {
        Field *fields = result->Fetch();
        uint32 charcount = fields[0].GetUInt32();
        delete result;
        return charcount;
    }
    else
        return 0;
}

bool AccountMgr::CheckPassword(uint32 accountId, std::string passwd, std::string username) const
{
    if (username == "")
    {
        if (!GetName(accountId, username))
            return false;
    }
    else
        normalizeString(username);

    normalizeString(passwd);

    QueryResult *result = LoginDatabase.PQuery("SELECT 1 FROM account WHERE id='%u' AND sha_pass_hash='%s'", accountId, CalculateShaPassHash(username, passwd).c_str());
    if (result)
    {
        delete result;
        return true;
    }

    return false;
}

bool AccountMgr::normalizeString(std::string& utf8str)
{
    wchar_t wstr_buf[MAX_ACCOUNT_STR + 1];

    size_t wstr_len = MAX_ACCOUNT_STR;
    if (!Utf8toWStr(utf8str, wstr_buf, wstr_len))
        return false;

    std::transform(&wstr_buf[0], wstr_buf + wstr_len, &wstr_buf[0], wcharToUpperOnlyLatin);

    return WStrToUtf8(wstr_buf, wstr_len, utf8str);
}

std::string AccountMgr::CalculateShaPassHash(std::string& name, std::string& password) const
{
    Sha1Hash sha;
    sha.Initialize();
    sha.UpdateData(name);
    sha.UpdateData(":");
    sha.UpdateData(password);
    sha.Finalize();

    std::string encoded;
    hexEncodeByteArray(sha.GetDigest(), sha.GetLength(), encoded);

    return encoded;
}

void AccountMgr::Update(uint32 diff)
{
    if (_banlistUpdateTimer < diff)
    {
        _banlistUpdateTimer = sWorld.getConfig(CONFIG_BANLIST_RELOAD_TIMER) * 1000;

        LoadIPBanList(true);
        LoadAccountBanList(true);
    }
    else
        _banlistUpdateTimer -= diff;
}

void AccountMgr::LoadIPBanList(bool silent)
{
    if (!silent)
        sLog.outString("Loading ip_banned ...");

    std::lock_guard<std::mutex> guard(_mutex);

    _ipBanned.clear();

    // order by ip so the map will be built in order, thereby allowing an unsorted map
    // order by unbandate to be sure that the longest ban is the one we use
    QueryResult *banresult = LoginDatabase.PQuery(
        "SELECT ip, unbandate, bandate FROM ip_banned WHERE (unbandate > UNIX_TIMESTAMP() OR bandate = unbandate) ORDER BY ip ASC, unbandate ASC"
    );

    if (banresult)
    {
        do
        {
            Field *fields = banresult->Fetch();
            uint32 unbandate = fields[1].GetUInt32();
            uint32 bandate = fields[2].GetUInt32();
            if (unbandate == bandate)
                unbandate = 0xFFFFFFFF;
            _ipBanned[fields[0].GetString()] = unbandate;
        }
        while (banresult->NextRow());
        delete banresult;
    }

    if (!silent)
        sLog.outString(">> Loaded %u account ban", _ipBanned.size());
}

void AccountMgr::LoadAccountSecurityList(bool silent)
{
    if (!silent)
        sLog.outString("Loading account_access ...");

    std::lock_guard<std::mutex> guard(_mutex);

    _accountSecurity.clear();

    // order by account so the map will be built in order, thereby allowing an unsorted map
    // order by gmlevel so that the highest rank available for this realm will be used
    QueryResult *result = LoginDatabase.PQuery(
        "SELECT id, gmlevel FROM account_access WHERE (RealmID = '%u' OR RealmID='-1') ORDER BY id ASC, gmlevel ASC", realmID);

    if (result)
    {
        Field *fields = NULL;
        do
        {
            fields = result->Fetch();
            uint32 accountId = fields[0].GetUInt32();
            AccountTypes secu = AccountTypes(fields[1].GetUInt32());
            switch (secu)
            {
                case SEC_MODERATOR:
                case SEC_MODERATOR_CONF:
                case SEC_GAMEMASTER:
                case SEC_BASIC_ADMIN:
                case SEC_DEVELOPPER:
                case SEC_ADMINISTRATOR:
                    _accountSecurity[accountId] = secu;
                default:
                    break;
            }
        } while (result->NextRow());
        delete result;
    }

    if (!silent)
        sLog.outString(">> %u GM ranks loaded for realm %u", _accountSecurity.size(), realmID);
}

void AccountMgr::LoadAccountBanList(bool silent)
{
    if (!silent)
        sLog.outString("Loading account_banned ...");

    std::lock_guard<std::mutex> guard(_mutex);

    _accountBanned.clear();

    // order by account so the map will be built in order, thereby allowing an unsorted map
    // order by unbandate to be sure that the longest ban is the one we use
    QueryResult *banresult = LoginDatabase.PQuery(
        "SELECT id, unbandate, bandate FROM account_banned WHERE active = 1 AND (unbandate > UNIX_TIMESTAMP() OR bandate = unbandate) ORDER BY id ASC, unbandate ASC"
    );

    if (banresult)
    {
        Field *fields = NULL;
        do
        {
            Field *fields = banresult->Fetch();

            auto const accountId = fields[0].GetUInt32();
            auto const bandate = fields[2].GetUInt32();
            auto unbandate = fields[1].GetUInt32();

            if (unbandate == bandate)
                unbandate = 0xFFFFFFFF;

            // if we already have information for this account, use
            // the unban date which is the farthest in the future
            auto const it = _accountBanned.find(accountId);

            if (it == _accountBanned.end() || it->second < unbandate)
                _accountBanned[fields[0].GetUInt32()] = unbandate;
        }
        while (banresult->NextRow());
        delete banresult;
    }

    if (!silent)
        sLog.outString(">> Loaded %u account ban(s)", _accountBanned.size());
}

void AccountMgr::BanIP(std::string const& ip, uint32 unbandate)
{
    std::lock_guard<std::mutex> guard(_mutex);

    // don't update if there is an active ip ban with a greater unban date
    auto const it = _ipBanned.find(ip);

    if (it == _ipBanned.end() || it->second < unbandate)
        _ipBanned[ip] = unbandate;
}

void AccountMgr::UnbanIP(std::string const& ip)
{
    std::lock_guard<std::mutex> guard(_mutex);
    _ipBanned.erase(ip);
}

void AccountMgr::BanAccount(uint32 accountId, uint32 unbandate)
{
    std::lock_guard<std::mutex> guard(_mutex);

    // don't update if there is an active ban with a greater unban date
    auto const it = _accountBanned.find(accountId);

    if (it == _accountBanned.end() || it->second < unbandate)
        _accountBanned[accountId] = unbandate;
}

void AccountMgr::UnbanAccount(uint32 accountId)
{
    std::lock_guard<std::mutex> guard(_mutex);
    _accountBanned.erase(accountId);
}

bool AccountMgr::IsIPBanned(std::string const& ip) const
{
    std::lock_guard<std::mutex> guard(_mutex);

    auto const it = _ipBanned.find(ip);

    return it != _ipBanned.end() && it->second < time(nullptr);
}

bool AccountMgr::IsAccountBanned(uint32 acc) const
{
    std::lock_guard<std::mutex> guard(_mutex);

    auto const it = _accountBanned.find(acc);

    return it != _accountBanned.end() && it->second < time(nullptr);
}

// returns true if they can enter an instance
bool AccountMgr::CheckInstanceCount(uint32 accountId, uint32 instanceId, uint32 maxCount)
{
    auto it = _instanceEnterTimes.find(accountId);

    // if we have no data for them, allow it
    if (it == _instanceEnterTimes.end())
        return true;

    auto& enterTimes = it->second;

    // if they have already entered this instance, dont count it as a new one, allow it
    if (enterTimes.find(instanceId) != enterTimes.end())
        return true;

    // if they have not entered too many instances, allow it
    if (enterTimes.size() < maxCount)
        return true;

    // they have entered too many instances.  remove any that have expired and re-check.
    auto const now = time(nullptr);

    for (auto i = enterTimes.begin(); i != enterTimes.end(); )
    {
        if (i->second + HOUR <= now)
            i = enterTimes.erase(i);
        else
            ++i;
    }

    return enterTimes.size() < maxCount;
}

void AccountMgr::AddInstanceEnterTime(uint32 accountId, uint32 instanceId, time_t enterTime)
{
    auto it = _instanceEnterTimes.find(accountId);

    if (it == _instanceEnterTimes.end())
    {
        InstanceEnterTimesMap resetTimes;
        resetTimes[instanceId] = enterTime;
        _instanceEnterTimes[accountId] = resetTimes;
        return;
    }

    it->second[instanceId] = enterTime;
}

// Anticheat
void AccountPersistentData::WhisperedBy(MasterPlayer* whisperer)
{
    WhispersMap::iterator it = _whisperTargets.find(whisperer->GetGUIDLow());
    if (it != _whisperTargets.end())
        it->second.score = 0;
}

uint32 AccountPersistentData::CountWhispersTo(MasterPlayer* from, MasterPlayer* player)
{
    sAccountMgr.GetAccountPersistentData(player->GetSession()->GetAccountId()).WhisperedBy(from);
    WhisperData& data = _whisperTargets[player->GetGUIDLow()];
    ++data.whispers_count;
    if (data.whispers_count == 1)
        data.score = GetWhisperScore(from, player);
    return data.whispers_count-1;
}

uint32 AccountPersistentData::GetWhisperScore(MasterPlayer* from, MasterPlayer* target) const
{
    uint32 score = 3;
    Player* playerFrom = from->GetSession()->GetPlayer();
    Player* playerTo = target->GetSession()->GetPlayer();
    if (playerFrom->GetGuildId() && playerFrom->GetGuildId() == playerTo->GetGuildId())
        score = 1;
    if (from->GetAreaId() == target->GetAreaId())
        score = 1;
    if (playerTo->GetGroup() && playerTo->GetGroup() == playerFrom->GetGroup())
        score = 1;
    return score;
}

void AccountPersistentData::JustMailed(uint32 toAccount)
{
    _mailsSent[toAccount] = time(NULL);
}

bool AccountPersistentData::CanMail(uint32 targetAccount)
{
    // Already sent a mail to this guy => OK
    if (_mailsSent.find(targetAccount) != _mailsSent.end())
        return true;

    uint32 totalScore = 0;
    time_t lastNonExpired = time(NULL) - sWorld.getConfig(CONFIG_UINT32_MAILSPAM_EXPIRE_SECS);
    for (auto it = _mailsSent.begin(); it != _mailsSent.end(); ++it)
        if (it->second >= lastNonExpired)
            totalScore++;
    uint32 allowedScore = sWorld.getConfig(CONFIG_UINT32_MAILSPAM_MAX_MAILS);
    return totalScore < allowedScore;
}
