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

#ifndef _ACCMGR_H
#define _ACCMGR_H

#include "Common.h"
#include "Policies/Singleton.h"

#include <string>
#include <map>
#include <unordered_map>
#include <mutex>

enum AccountOpResult
{
    AOR_OK,
    AOR_NAME_TOO_LONG,
    AOR_PASS_TOO_LONG,
    AOR_NAME_ALREDY_EXIST,
    AOR_NAME_NOT_EXIST,
    AOR_DB_INTERNAL_ERROR
};


class WorldSession;
class ChatHandler;
class MasterPlayer;

#define MAX_ACCOUNT_STR 16

class AccountPersistentData
{
/// WHISP FLOOD
public:
    struct WhisperData
    {
        WhisperData() : first_whisp(time(NULL)), score(0), whispers_count(0) {}
        time_t first_whisp;
        uint32 score;
        uint32 whispers_count;
    };
    void WhisperedBy(MasterPlayer* whisperer);
    uint32 CountWhispersTo(MasterPlayer* from, MasterPlayer* player);
    uint32 GetWhisperScore(MasterPlayer* from, MasterPlayer* player) const;
    uint32 CountDifferentWhispTargets() const { return _whisperTargets.size(); }

    typedef std::map<uint32 /*lowguid*/, WhisperData> WhispersMap;
    WhispersMap _whisperTargets;

/// MAIL FLOOD
public:
    void JustMailed(uint32 toAccount);
    bool CanMail(uint32 targetAccount);
protected:
    typedef std::map<uint32, time_t> MailsSentMap;
    MailsSentMap _mailsSent;
};

class AccountMgr
{
    public:
        AccountMgr();

        AccountOpResult CreateAccount(std::string username, std::string password) const;
        AccountOpResult DeleteAccount(uint32 accountId);
        AccountOpResult ChangePassword(uint32 accountId, std::string new_passwd, std::string username = "") const;
        bool CheckPassword(uint32 accountId, std::string passwd, std::string username = "") const;

        uint32 GetId(std::string username) const;

        void Load();
        AccountTypes GetSecurity(uint32 accountId) const;

        bool GetName(uint32 accountId, std::string &name) const;
        uint32 GetFlags(uint32 accountId) const;
        uint32 GetCharactersCount(uint32 accountId) const;
        std::string CalculateShaPassHash(std::string& name, std::string& password) const;

        static bool normalizeString(std::string& utf8str);

        // Nostalrius
        void Update(uint32 diff);

        void LoadAccountSecurityList(bool silence = false);
        void LoadIPBanList(bool silent = false);
        void LoadAccountBanList(bool silent = false);

        void BanIP(std::string const& ip, uint32 unbandate);
        void UnbanIP(std::string const& ip);
        void BanAccount(uint32 accountId, uint32 unbandate);
        void UnbanAccount(uint32 accountId);

        bool IsIPBanned(std::string const& ip) const;
        bool IsAccountBanned(uint32 acc) const;

        // Max instance reset per account per hour
        bool CheckInstanceCount(uint32 accountId, uint32 instanceId, uint32 maxCount);
        void AddInstanceEnterTime(uint32 accountId, uint32 instanceId, time_t enterTime);

        AccountPersistentData& GetAccountPersistentData(uint32 accountId) { return _accountPersistentData[accountId]; }

    private:
        mutable std::mutex _mutex;

        std::unordered_map<uint32, AccountTypes> _accountSecurity;

        uint32 _banlistUpdateTimer;
        std::unordered_map<std::string, uint32> _ipBanned;
        std::unordered_map<uint32, uint32> _accountBanned;

        std::unordered_map<uint32, AccountPersistentData> _accountPersistentData;

        using InstanceEnterTimesMap = std::unordered_map<uint32 /* instanceId */, time_t /* enter time */>;
        using AccountInstanceEnterTimesMap = std::unordered_map<uint32 /* accountId */, InstanceEnterTimesMap>;

        AccountInstanceEnterTimesMap _instanceEnterTimes;
};

#define sAccountMgr MaNGOS::Singleton<AccountMgr>::Instance()
#endif
