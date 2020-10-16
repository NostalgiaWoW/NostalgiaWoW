#ifndef __XPLOG_H
#define __XPLOG_H

#include "Common.h"
#include <unordered_map>
#include <mutex>
#include "Timer.h"
#include "ObjectGuid.h"

enum XPLogType : uint8
{
    FromKill = 0,
    FromQuest = 1,
    FromExploration = 2,

    Max,
};

class XPLog
{
private:
    struct CharacterXPData
    {
        uint64 XP = 0LL;
        bool Changed = false;
    };

    struct TotalNPCKills
    {
        uint64 XP = 0LL;
        uint32 Kills = 0;

        bool Changed = false;
    };

public:
    static XPLog* Instance();    

    void FromNpcKill(ObjectGuid player, uint32 npcId, uint32 xp);
    void FromExploration(ObjectGuid player, uint32 xp);
    void FromQuest(ObjectGuid player, uint32 xp);

    void Update(uint32 diff);
    void SaveToDB();
    void LoadFromDB();

private:
    std::unordered_map<ObjectGuid, CharacterXPData> _xpFrom[XPLogType::Max];
    std::unordered_map<uint32, TotalNPCKills> _xpFromNPCTotal;

    IntervalTimer _saveTimer;
    bool _enabled = false;

    using LockType = std::mutex;
    using RWGuard = std::lock_guard<LockType>;

    LockType _lock;
};

#define sXPLogMgr XPLog::Instance()

#endif