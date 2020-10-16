#include "XPLog.h"
#include "Database/DatabaseEnv.h"
#include "World.h"

XPLog* XPLog::Instance()
{
    static XPLog instance;
    return &instance;
}

void XPLog::FromNpcKill(ObjectGuid player, uint32 npcId, uint32 xp)
{
    ASSERT(player.IsPlayer());

    RWGuard guard(_lock);

    CharacterXPData& data = _xpFrom[XPLogType::FromKill][player];
    data.XP += xp;
    data.Changed = true;

    TotalNPCKills& npcData = _xpFromNPCTotal[npcId];
    npcData.XP += xp;
    npcData.Kills++;
    npcData.Changed = true;
}

void XPLog::FromExploration(ObjectGuid player, uint32 xp)
{
    ASSERT(player.IsPlayer());

    RWGuard guard(_lock);

    CharacterXPData& data = _xpFrom[XPLogType::FromExploration][player];
    data.XP += xp;
    data.Changed = true;
}

void XPLog::FromQuest(ObjectGuid player, uint32 xp)
{
    ASSERT(player.IsPlayer());

    RWGuard guard(_lock);

    CharacterXPData& data = _xpFrom[XPLogType::FromQuest][player];
    data.XP += xp;
    data.Changed = true;
}

void XPLog::Update(uint32 diff)
{
    if (!_enabled)
        return;

    if (_saveTimer.GetCurrent() >= 0)
        _saveTimer.Update(diff);
    else
        _saveTimer.SetCurrent(0);

    if (_saveTimer.Passed())
    {
        SaveToDB();
        _saveTimer.Reset();
    }
}

void XPLog::SaveToDB()
{
    if (!_enabled)
        return;

    static SqlStatementID perCharDelStats;
    static SqlStatementID perCharInsertStats;

    static SqlStatementID totalDelStats;
    static SqlStatementID totalInsertStats;

    RWGuard guard(_lock);

    for (uint8 type = 0; type < XPLogType::Max; ++type)
    {
        for (auto& pair : _xpFrom[type])
        {
            CharacterXPData const& xp = pair.second;
            if (!xp.Changed)
                continue;

            SqlStatement stmt = CharacterDatabase.CreateStatement(perCharDelStats, "DELETE FROM character_xp_from_log WHERE guid = ? AND type = ?");
            stmt.PExecute(pair.first.GetCounter(), type);

            stmt = CharacterDatabase.CreateStatement(perCharInsertStats, "INSERT INTO character_xp_from_log (guid, type, xp) VALUES (?, ?, ?)");
            stmt.addUInt32(pair.first.GetCounter());
            stmt.addUInt8(type);
            stmt.addUInt64(xp.XP);
            stmt.Execute();

            pair.second.Changed = false;
        }
    }

    for (auto& pair : _xpFromNPCTotal)
    {
        TotalNPCKills const& xp = pair.second;
        if (!xp.Changed)
            continue;

        SqlStatement stmt = CharacterDatabase.CreateStatement(totalDelStats, "DELETE FROM npc_kill_xp_log_total WHERE npcId = ?");
        stmt.PExecute(pair.first);

        stmt = CharacterDatabase.CreateStatement(totalInsertStats, "INSERT INTO npc_kill_xp_log_total (npcId, kills, xp) VALUES (?, ?, ?)");
        stmt.addUInt32(pair.first);
        stmt.addUInt32(xp.Kills);
        stmt.addUInt64(xp.XP);
        stmt.Execute();

        pair.second.Changed = false;
    }
}

void XPLog::LoadFromDB()
{
    int32 savePeriod = sWorld.getConfig(CONFIG_INT32_XP_LOG_SAVE_PERIOD);
    if (savePeriod <= 0)
        return;

    QueryResult* result = CharacterDatabase.PQuery("SELECT guid, type, xp FROM character_xp_from_log");
    if (result)
    {
        do
        {
            Field* fields = result->Fetch();
            
            uint32 guid = fields[0].GetUInt32();
            XPLogType type = static_cast<XPLogType>(fields[1].GetUInt8());
            uint64 xp = fields[2].GetUInt64();

            switch (type)
            {
                case XPLogType::FromKill:
                case XPLogType::FromQuest:
                case XPLogType::FromExploration:
                    _xpFrom[type][guid].XP += xp;
                    break;
            }

        } while (result->NextRow());
    }

    result = CharacterDatabase.Query("SELECT npcId, kills, xp FROM npc_kill_xp_log_total");
    if (result)
    {
        do
        {
            Field* fields = result->Fetch();

            uint32 npcId = fields[0].GetUInt32();
            uint32 kills = fields[1].GetUInt32();
            uint64 xp = fields[2].GetUInt64();

            TotalNPCKills& npcData = _xpFromNPCTotal[npcId];
            npcData.XP += xp;
            npcData.Kills = kills;

        } while (result->NextRow());
    }

    _enabled = true;
    _saveTimer.SetInterval(savePeriod * IN_MILLISECONDS);
}
