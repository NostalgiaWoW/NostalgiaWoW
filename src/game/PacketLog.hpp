#pragma once

#include <vector>
#include <queue>
#include <mutex>

class WorldSession;

class MANGOS_DLL_SPEC PacketLog
{
    private:
        mutable std::mutex _mutex;

        struct Entry
        {
            time_t Time;
            std::vector<uint8> Data;
            Entry(time_t time, std::vector<uint8> &&data) : Time(time), Data(std::move(data)) {}
        };

        const WorldSession *_session;

        std::queue<Entry> _data;

        void Save();

    public:
        PacketLog(const WorldSession *session);
        ~PacketLog();
        
        void Push(uint16 opCode, const uint8 *data, int32 length);
};