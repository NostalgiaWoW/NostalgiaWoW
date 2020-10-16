//Giperion February 2018
//[EUREKA] 3.6
#include "ChatHookMgr.h"
#include <Policies/SingletonImp.h>
#include "ObjectMgr.h"
#include "Chat.h"

INSTANTIATE_SINGLETON_1(ChatHookMgr);

void ChatHookMgr::HookMessage(Group* group, WorldPacket& data)
{
    auto ListenersPairs = groupHooks.equal_range(group->GetId());

    for (auto StartIter = ListenersPairs.first; StartIter != ListenersPairs.second; StartIter++)
    {
        ObjectGuid Listener = StartIter->second;

        if (Player* pl = sObjectAccessor.FindPlayer(Listener))
        {
            pl->GetSession()->SendPacket(&data);
        }
    }
}

void ChatHookMgr::HookMessage(Guild* guild, WorldPacket& data)
{
    auto ListenersPairs = guildsHooks.equal_range(guild->GetId());

    for (auto StartIter = ListenersPairs.first; StartIter != ListenersPairs.second; ++StartIter)
    {
        ObjectGuid Listener = StartIter->second;

        if (Player* pl = sObjectAccessor.FindPlayer(Listener))
        {
            pl->GetSession()->SendPacket(&data);
        }
    }
}

void ChatHookMgr::HookMessage(MasterPlayer* sender, MasterPlayer* receiver, std::string& textMessage)
{
    if (sender == nullptr || receiver == nullptr) return;
    //we intercept both income and outcome whisper messages

    auto SendMessageToListenersFunc = [sender, receiver, textMessage](auto& ListenersPairs)
    {
        std::stringstream ss;
        ss << sender->GetName() << "->" << receiver->GetName() << ": " << textMessage;
        std::string Message = ss.str();
        for (auto StartIter = ListenersPairs.first; StartIter != ListenersPairs.second; StartIter++)
        {
            ObjectGuid Listener = StartIter->second;

            if (Player* pl = sObjectAccessor.FindPlayer(Listener))
            {
                ChatHandler ch(pl);
                ch.PSendSysMessage("%s", Message.c_str());
            }
        }
    };

    auto ListenersPairs = whisperHooks.equal_range(sender->GetObjectGuid());
    if (ListenersPairs.first != whisperHooks.end())
    {
        SendMessageToListenersFunc(ListenersPairs);
    }

    ListenersPairs = whisperHooks.equal_range(receiver->GetObjectGuid());
    if (ListenersPairs.first != whisperHooks.end())
    {
        SendMessageToListenersFunc(ListenersPairs);
    }
}

void ChatHookMgr::HookMessage(Player* player, ChatMsg MessageType, std::string& textMessage)
{
    if (player == nullptr) return;

    auto ListenersPairs = MiscChannelsHooks.equal_range(player->GetObjectGuid());
    if (ListenersPairs.first != MiscChannelsHooks.end())
    {
        std::stringstream ss;
        ss << player->GetName() << " ";
        switch (MessageType)
        {
        case CHAT_MSG_SAY:
            ss << "say: ";
            break;
        case CHAT_MSG_YELL:
            ss << "yell: ";
            break;
        case CHAT_MSG_EMOTE:
            ss << "emote: ";
            break;
        default:
            return;
        }
        ss << textMessage;

        for (auto StartIter = ListenersPairs.first; StartIter != ListenersPairs.second; StartIter++)
        {
            ObjectGuid Listener = StartIter->second;

            if (Player* pl = sObjectAccessor.FindPlayer(Listener))
            {
                ChatHandler ch(pl);
                ch.PSendSysMessage("%s", ss.str().c_str());
            }
        }
    }
}

void ChatHookMgr::HookChannelMessage(Player* player, std::string& Channel, std::string& textMessage)
{
    if (player == nullptr) return;

    auto ListenersPairs = MiscChannelsHooks.equal_range(player->GetObjectGuid());
    if (ListenersPairs.first != MiscChannelsHooks.end())
    {
        std::stringstream ss;
        ss << player->GetName() << " send to channel " << Channel << " :" << textMessage;
        for (auto StartIter = ListenersPairs.first; StartIter != ListenersPairs.second; StartIter++)
        {
            ObjectGuid Listener = StartIter->second;

            if (Player* pl = sObjectAccessor.FindPlayer(Listener))
            {
                ChatHandler ch(pl);
                ch.PSendSysMessage("%s", ss.str().c_str());
            }
        }
    }
}

#if 0
void ChatHookMgr::HookMessage(Player* player, WorldPacket& data)
{
    auto ListenersPairs = whisperHooks.equal_range(player->GetObjectGuid());

    for (auto StartIter = ListenersPairs.first; StartIter != ListenersPairs.second; StartIter++)
    {
        ObjectGuid Listener = StartIter->second;

        if (Player* pl = sObjectAccessor.FindPlayer(Listener))
        {
            pl->GetSession()->SendPacket(&data);
        }
    }
}
#endif

bool ChatHookMgr::InstallHook(Player* receiver, Group* target)
{
    if (target == nullptr) return false;

    groupHooks.insert(std::pair<uint32, ObjectGuid>(target->GetId(), receiver->GetObjectGuid()));
    return true;
}

bool ChatHookMgr::InstallHook(Player* receiver, Guild* target)
{
    if (target == nullptr) return false;

    guildsHooks.insert(std::pair<uint32, ObjectGuid>(target->GetId(), receiver->GetObjectGuid()));
    return true;
}

bool ChatHookMgr::InstallHook(Player* receiver, Player* target)
{
    if (target == nullptr) return false;

    whisperHooks.insert(std::pair<ObjectGuid, ObjectGuid>(target->GetObjectGuid(), receiver->GetObjectGuid()));
    return true;
}

bool ChatHookMgr::InstallHookOnMiscChannels(Player* receiver, Player* target)
{
    if (target == nullptr) return false;

    MiscChannelsHooks.insert(std::pair<ObjectGuid, ObjectGuid>(target->GetObjectGuid(), receiver->GetObjectGuid()));
    return true;
}

bool ChatHookMgr::RemoveHook(Player* receiver, Group* target)
{
    if (target == nullptr) return false;

    auto ListenersPairs = groupHooks.equal_range(target->GetId());

    ObjectGuid guid = receiver->GetObjectGuid();

    for (auto Iter = ListenersPairs.first; Iter != ListenersPairs.second; Iter++)
    {
        auto PairElem = *Iter;
        if (PairElem.first == target->GetId() && PairElem.second == guid)
        {
            Iter = groupHooks.erase(Iter);
            if (Iter == groupHooks.end()) return true;
        }
    }

    return true;
}

bool ChatHookMgr::RemoveHook(Player* receiver, Guild* target)
{
    if (target == nullptr) return false;

    auto ListenersPairs = guildsHooks.equal_range(target->GetId());

    ObjectGuid guid = receiver->GetObjectGuid();

    for (auto guildHookIter = ListenersPairs.first; guildHookIter != ListenersPairs.second; guildHookIter++)
    {
        auto PairElem = *guildHookIter;
        if (PairElem.first == target->GetId() && PairElem.second == guid)
        {
            guildHookIter = guildsHooks.erase(guildHookIter);
            if (guildHookIter == guildsHooks.end()) return true;
        }
    }

    return true;
}

bool ChatHookMgr::RemoveHook(Player* receiver, Player* target)
{
    if (target == nullptr) return false;

    ObjectGuid guid = receiver->GetObjectGuid();
    ObjectGuid guidTarget = target->GetObjectGuid();

    auto ListenersPairs = whisperHooks.equal_range(guidTarget);

    for (auto whisperHookIter = ListenersPairs.first; whisperHookIter != ListenersPairs.second; whisperHookIter++)
    {
        auto PairElem = *whisperHookIter;
        if (PairElem.first == guidTarget && PairElem.second == guid)
        {
            whisperHookIter = whisperHooks.erase(whisperHookIter);
            if (whisperHookIter == whisperHooks.end()) return true;
        }
    }

    return true;
}

bool ChatHookMgr::ClearAllHooksRelatedToListener(ObjectGuid PlayerGuid)
{
    auto EraseEverythingThatHaveValue = [this](auto& containerRef, ObjectGuid value)
    {
        for (auto containerRefIter = containerRef.begin(); containerRefIter != containerRef.end(); containerRefIter++)
        {
            if (containerRefIter->second == value)
            {
                containerRefIter = containerRef.erase(containerRefIter);
                if (containerRefIter == containerRef.end()) return;
            }
        }
    };

    EraseEverythingThatHaveValue(groupHooks, PlayerGuid);
    EraseEverythingThatHaveValue(guildsHooks, PlayerGuid);
    EraseEverythingThatHaveValue(whisperHooks, PlayerGuid);
    EraseEverythingThatHaveValue(MiscChannelsHooks, PlayerGuid);

    return true;
}
