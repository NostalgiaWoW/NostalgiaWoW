#include "Database/DatabaseEnv.h"
#include "World.h"
#include "Log.h"
#include "ProgressBar.h"
#include "Policies/SingletonImp.h"
#include "Util.h"

#include "AutoBroadCastMgr.h"

INSTANTIATE_SINGLETON_1(AutoBroadCastMgr);

AutoBroadCastMgr::AutoBroadCastMgr()
{
    _constInterval = sWorld.getConfig(CONFIG_BOOL_AUTOBROADCAST_USE_CONST_TIMER) ? sWorld.getConfig(CONFIG_UINT32_AUTOBROADCAST_INTERVAL) : 0;
    _current = 0;
}

AutoBroadCastMgr::~AutoBroadCastMgr()
{
    entries.clear();
}

void AutoBroadCastMgr::load()
{
    entries.clear();
    QueryResult* result = WorldDatabase.Query("SELECT delay, stringId FROM autobroadcast");

    if (!result)
    {
        sLog.outString();
        sLog.outString(">> Loaded 0 AutoBroadCast message");
        return;
    }

    uint32 count = 0;

    Field *fields;
    do
    {
        AutoBroadCastEntry e;
        fields = result->Fetch();

        e.delay = fields[0].GetUInt32();
        e.stringId = fields[1].GetInt32();
        e.lastAnnounce = time(NULL);

        entries.push_back(e);
        ++count;
    }
    while (result->NextRow());

    sLog.outString();
    sLog.outString(">> Loaded %u AutoBroadCast messages", count);

}

void AutoBroadCastMgr::update(uint32 diff)
{
    if (entries.empty())
        return;

    if (sWorld.getConfig(CONFIG_BOOL_AUTOBROADCAST_USE_CONST_TIMER))
    {
        _current += diff;
        if (_current >= _constInterval)
        {
            AutoBroadCastEntry entry = SelectRandomContainerElement(entries);
            uint32 abcenter = sWorld.getConfig(CONFIG_UINT32_AUTOBROADCAST_CENTER);

            if (abcenter == 0)
                sWorld.SendWorldText(entry.stringId);
            else if (abcenter == 1)
                sWorld.SendWorldNotification(entry.stringId);
            else if (abcenter == 2)
            {
                sWorld.SendWorldText(entry.stringId);
                sWorld.SendWorldNotification(entry.stringId);
            }

            _current = 0;
        }
    }
    else
    {
        time_t now = time(nullptr);
        std::vector<AutoBroadCastEntry>::iterator iter;
        for (iter = entries.begin(); iter != entries.end(); ++iter)
        {
            if ((now - iter->lastAnnounce) > iter->delay)
            {
                sWorld.SendWorldText(iter->stringId);
                iter->lastAnnounce = now;
            }
        }
    }
}
