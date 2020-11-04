#pragma once

#include "Player.h"

class InspectSystem
{
public:
    static const int SenderId = 4407;

    static InspectSystem* Instance()
    {
        static InspectSystem instance;
        return &instance;
    }


    void BlockInspect(Player* target, Player* source);

private:
    void SendModifiedPackets(Player* target, Player* source);
    void FillItemPacket(Item* item, WorldPacket& packet);
};

#define sInspectSystem InspectSystem::Instance()