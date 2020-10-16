#include "Common.h"
#include "PacketLog.hpp"
#include "WorldSession.h"
#include "Config/Config.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <mutex>

#define PACKETLOG_BUFFER_SIZE   10

PacketLog::PacketLog(const WorldSession *session) : _session(session) {}

PacketLog::~PacketLog()
{
    std::lock_guard<std::mutex> guard(_mutex);

    Save();
}

void PacketLog::Save()
{
    std::stringstream ss;

    auto const dir = sConfig.GetStringDefault("LogsDir", "");

    if (!dir.empty())
        ss << dir << "/";

    ss << std::dec << _session->GetAccountId() << "_packetlog.txt";

    std::ofstream outfile(ss.str().c_str(), std::ofstream::out | std::ios_base::app);

    std::ios_base::fmtflags flags(outfile.flags());

    while (!_data.empty())
    {
        const uint32 time = _data.front().Time;
        const std::vector<uint8> &data = _data.front().Data;

        outfile << "> " << time;

        for (auto i = 0; i < data.size(); ++i)
            outfile << " 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)data[i];

        outfile << std::endl;

        outfile.flags(flags);

        _data.pop();
    }

    outfile.close();
}

void PacketLog::Push(uint16 opCode, const uint8 *data, int32 length)
{
    std::vector<uint8> entryData(length+sizeof(opCode));

    memcpy(&entryData[0], (void *)&opCode, sizeof(opCode));

    if (length)
        memcpy(&entryData[sizeof(opCode)], data, length);

    std::lock_guard<std::mutex> guard(_mutex);

    _data.emplace(time(nullptr), std::move(entryData));

    if (_data.size() >= PACKETLOG_BUFFER_SIZE)
        Save();
}
