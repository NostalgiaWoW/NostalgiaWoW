#include "scriptPCH.h"
#include "Utilities/EventProcessor.h"

template <typename Functor>
void DoAfterTime(Player* player, uint32 p_time, Functor&& function)
{
    player->m_Events.AddEvent(new LambdaBasicEvent<Functor>(std::move(function)), player->m_Events.CalculateTime(p_time));
}

bool ItemUseSpell_shop_character_rename(Player* pPlayer, Item* pItem, const SpellCastTargets&)
{
    if (!pPlayer) return false;

    pPlayer->SetAtLoginFlag(AT_LOGIN_RENAME);
    pPlayer->GetSession()->SendNotification("Please choose a new name.\nYou will be disconnected in 5 seconds.");
    pPlayer->SaveToDB();
    DoAfterTime(pPlayer, 5 * IN_MILLISECONDS,[player = pPlayer]() { player->GetSession()->KickPlayer(); });
    return true;
}

bool ItemUseSpell_shop_mailbox(Player* pPlayer, Item* pItem, const SpellCastTargets&)
{
	if (!pPlayer) return false;

    GameObject* other_mailbox = pPlayer->FindNearestGameObject(144112, 50.0F);

    if (other_mailbox)
        other_mailbox->SetRespawnTime(1);

    float dis{ 2.0F };
    float x, y, z;
    pPlayer->GetSafePosition(x, y, z);
    x += dis * cos(pPlayer->GetOrientation());
    y += dis * sin(pPlayer->GetOrientation());

    pPlayer->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
    pPlayer->SummonGameObject(144112, x, y, z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30, true);
    return true;
}

bool ItemUseSpell_shop_brainwashing_device(Player* pPlayer, Item* pItem, const SpellCastTargets&)
{
    if (pPlayer->isInCombat() || pPlayer->IsBeingTeleported() || (pPlayer->getDeathState() == CORPSE) || pPlayer->IsMoving())
        ChatHandler(pPlayer).PSendSysMessage("Warning! Failsafe system shutting device down!");
    else
    {
        float dis{ 2.0F };
        float x, y, z;
        pPlayer->GetSafePosition(x, y, z);
        x += dis * cos(pPlayer->GetOrientation());
        y += dis * sin(pPlayer->GetOrientation());
        pPlayer->SummonGameObject(1000333, x, y, z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 120, true);
        return true;
    }
    return false;
}

bool GOHello_go_brainwashing_device(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->getLevel() >= 10 && pPlayer->HasItemCount(40005, 1))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Click here to reset your talents.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    pPlayer->SEND_GOSSIP_MENU(90350, pGo->GetGUID());
    return true;
}

bool GOSelect_go_brainwashing_device(Player* pPlayer, GameObject* pGo, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->resetTalents();
        pPlayer->AddAura(27880);
        pGo->Despawn();
        pGo->UpdateObjectVisibility();
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}

bool GossipHello_npc_barber(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->HasItemCount(40003, 1))
    {
        switch (pPlayer->getRace())
        {
        case RACE_TAUREN:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Horn Color Next", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Horn Color Previous", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Horn Style Next", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Horn Style Previous", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            break;
        default:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hair Color Next", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hair Color Previous", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hair Style Next", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hair Style Previous", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            break;      
        }
    }
    pPlayer->SEND_GOSSIP_MENU(90370, pCreature->GetGUID());
    return true;
}

class DemorphAfterTime : public BasicEvent 
{
public:
    explicit DemorphAfterTime(uint64 player_guid) : BasicEvent(), player_guid(player_guid) {}
    bool Execute(uint64 e_time, uint32 p_time) override 
    {
        Player* player = ObjectAccessor::FindPlayer(player_guid);
        if (player) 
            player->DeMorph();
        return false;
    }
private:
    uint64 player_guid;
};

bool GossipSelect_npc_barber(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        uint16 bytelimit_human = 9;
        uint16 bytelimit_elf = 7;
        uint16 bytelimit_gnome = 8;
        uint16 bytelimit_dwarf = 8;
        uint16 bytelimit_troll = 9;
        uint16 bytelimit_orc = 7;
        uint16 bytelimit_undead = 9;
        uint16 bytelimit_tauren = 9;

        uint16 color = 0;
        uint16 curr_color = pPlayer->GetByteValue(PLAYER_BYTES, 3);

        switch (pPlayer->getRace())
        {
        case RACE_HUMAN:    color = (curr_color == bytelimit_human) ? 0 : ++curr_color; break;
        case RACE_NIGHTELF: color = (curr_color == bytelimit_elf) ? 0 : ++curr_color; break;
        case RACE_GNOME:    color = (curr_color == bytelimit_gnome) ? 0 : ++curr_color; break;
        case RACE_DWARF:    color = (curr_color == bytelimit_dwarf) ? 0 : ++curr_color; break;
        case RACE_TROLL:    color = (curr_color == bytelimit_troll) ? 0 : ++curr_color; break;
        case RACE_ORC:      color = (curr_color == bytelimit_orc) ? 0 : ++curr_color; break;
        case RACE_UNDEAD:   color = (curr_color == bytelimit_undead) ? 0 : ++curr_color; break;
        case RACE_TAUREN:   color = (curr_color == bytelimit_tauren) ? 0 : ++curr_color; break;
        }
        pPlayer->SetByteValue(PLAYER_BYTES, 3, color);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        uint16 bytelimit_human = 9;
        uint16 bytelimit_elf = 7;
        uint16 bytelimit_gnome = 8;
        uint16 bytelimit_dwarf = 8;
        uint16 bytelimit_troll = 9;
        uint16 bytelimit_orc = 7;
        uint16 bytelimit_undead = 9;
        uint16 bytelimit_tauren = 9;

        uint16 color = 0;
        uint16 curr_color = pPlayer->GetByteValue(PLAYER_BYTES, 3);

        switch (pPlayer->getRace())
        {
        case RACE_HUMAN:    color = (curr_color == 0) ? bytelimit_human : --curr_color; break;
        case RACE_NIGHTELF: color = (curr_color == 0) ? bytelimit_elf : --curr_color; break;
        case RACE_GNOME:    color = (curr_color == 0) ? bytelimit_gnome : --curr_color; break;
        case RACE_DWARF:    color = (curr_color == 0) ? bytelimit_dwarf : --curr_color; break;
        case RACE_TROLL:    color = (curr_color == 0) ? bytelimit_troll : --curr_color; break;
        case RACE_ORC:      color = (curr_color == 0) ? bytelimit_orc : --curr_color; break;
        case RACE_UNDEAD:   color = (curr_color == 0) ? bytelimit_undead : --curr_color; break;
        case RACE_TAUREN:   color = (curr_color == 0) ? bytelimit_tauren : --curr_color; break;
        }
        pPlayer->SetByteValue(PLAYER_BYTES, 3, color);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 3)
    {
        uint16 bytelimit_human  = (pPlayer->getGender() == GENDER_FEMALE) ? 18 : 11;
        uint16 bytelimit_elf    = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 6;
        uint16 bytelimit_gnome  = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 6;
        uint16 bytelimit_dwarf  = (pPlayer->getGender() == GENDER_FEMALE) ? 13 : 10;
        uint16 bytelimit_troll  = (pPlayer->getGender() == GENDER_FEMALE) ? 4 : 5;
        uint16 bytelimit_orc    = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 6;
        uint16 bytelimit_undead = (pPlayer->getGender() == GENDER_FEMALE) ? 9 : 9;
        uint16 bytelimit_tauren = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 7;

        uint16 style = 0;
        uint16 curr_style = pPlayer->GetByteValue(PLAYER_BYTES, 2);

        switch (pPlayer->getRace())
        {
        case RACE_HUMAN:    style = (curr_style == bytelimit_human) ? 0 : ++curr_style; break;
        case RACE_NIGHTELF: style = (curr_style == bytelimit_elf) ? 0 : ++curr_style; break;
        case RACE_GNOME:    style = (curr_style == bytelimit_gnome) ? 0 : ++curr_style; break;
        case RACE_DWARF:    style = (curr_style == bytelimit_dwarf) ? 0 : ++curr_style; break;
        case RACE_TROLL:    style = (curr_style == bytelimit_troll) ? 0 : ++curr_style; break;
        case RACE_ORC:      style = (curr_style == bytelimit_orc) ? 0 : ++curr_style; break;
        case RACE_UNDEAD:   style = (curr_style == bytelimit_undead) ? 0 : ++curr_style; break;
        case RACE_TAUREN:   style = (curr_style == bytelimit_tauren) ? 0 : ++curr_style; break;
        }
        pPlayer->SetByteValue(PLAYER_BYTES, 2, style);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 4)
    {
        uint16 bytelimit_human = (pPlayer->getGender() == GENDER_FEMALE) ? 18 : 11;
        uint16 bytelimit_elf = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 6;
        uint16 bytelimit_gnome = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 6;
        uint16 bytelimit_dwarf = (pPlayer->getGender() == GENDER_FEMALE) ? 13 : 10;
        uint16 bytelimit_troll = (pPlayer->getGender() == GENDER_FEMALE) ? 4 : 5;
        uint16 bytelimit_orc = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 6;
        uint16 bytelimit_undead = (pPlayer->getGender() == GENDER_FEMALE) ? 9 : 9;
        uint16 bytelimit_tauren = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 7;

        uint16 style = 0;
        uint16 curr_style = pPlayer->GetByteValue(PLAYER_BYTES, 2);

        switch (pPlayer->getRace())
        {
        case RACE_HUMAN:    style = (curr_style == 0) ? bytelimit_human : --curr_style; break;
        case RACE_NIGHTELF: style = (curr_style == 0) ? bytelimit_elf : --curr_style; break;
        case RACE_GNOME:    style = (curr_style == 0) ? bytelimit_gnome : --curr_style; break;
        case RACE_DWARF:    style = (curr_style == 0) ? bytelimit_dwarf : --curr_style; break;
        case RACE_TROLL:    style = (curr_style == 0) ? bytelimit_troll : --curr_style; break;
        case RACE_ORC:      style = (curr_style == 0) ? bytelimit_orc : --curr_style; break;
        case RACE_UNDEAD:   style = (curr_style == 0) ? bytelimit_undead : --curr_style; break;
        case RACE_TAUREN:   style = (curr_style == 0) ? bytelimit_tauren : --curr_style; break;
        }
        pPlayer->SetByteValue(PLAYER_BYTES, 2, style);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }
    pPlayer->SaveToDB();
    pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

bool GossipHello_npc_surgeon(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->HasItemCount(40004, 1))
    {
        if (pPlayer->getRace() == RACE_TAUREN)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Fur Color Next ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Fur Color Previous", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Features Next ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Features Previous", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Face Next ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Face Previous", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
        }
        else
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Skin Color Next ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Skin Color Previous", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Features Next ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Features Previous", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Face Next ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Face Previous", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
        }
    }

    pPlayer->SEND_GOSSIP_MENU(90371, pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_surgeon(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        uint16 bytelimit_human  = (pPlayer->getGender() == GENDER_FEMALE) ? 9 : 9;
        uint16 bytelimit_elf    = (pPlayer->getGender() == GENDER_FEMALE) ? 8 : 8;
        uint16 bytelimit_gnome  = (pPlayer->getGender() == GENDER_FEMALE) ? 4 : 3;
        uint16 bytelimit_dwarf  = (pPlayer->getGender() == GENDER_FEMALE) ? 8 : 8;
        uint16 bytelimit_troll  = (pPlayer->getGender() == GENDER_FEMALE) ? 5 : 5;
        uint16 bytelimit_orc    = (pPlayer->getGender() == GENDER_FEMALE) ? 8 : 8;
        uint16 bytelimit_undead = (pPlayer->getGender() == GENDER_FEMALE) ? 5 : 7;
        uint16 bytelimit_tauren = (pPlayer->getGender() == GENDER_FEMALE) ? 10 : 18;

        uint16 skintone = 0;
        uint16 curr_skintone = pPlayer->GetByteValue(PLAYER_BYTES, 0);

        switch (pPlayer->getRace())
        {
        case RACE_HUMAN:    skintone = (curr_skintone == bytelimit_human) ? 0 : ++curr_skintone; break;
        case RACE_NIGHTELF: skintone = (curr_skintone == bytelimit_elf) ? 0 : ++curr_skintone; break;
        case RACE_GNOME:    skintone = (curr_skintone == bytelimit_gnome) ? 0 : ++curr_skintone; break;
        case RACE_DWARF:    skintone = (curr_skintone == bytelimit_dwarf) ? 0 : ++curr_skintone; break;
        case RACE_TROLL:    skintone = (curr_skintone == bytelimit_troll) ? 0 : ++curr_skintone; break;
        case RACE_ORC:      skintone = (curr_skintone == bytelimit_orc) ? 0 : ++curr_skintone; break;
        case RACE_UNDEAD:   skintone = (curr_skintone == bytelimit_undead) ? 0 : ++curr_skintone; break;
        case RACE_TAUREN:   skintone = (curr_skintone == bytelimit_tauren) ? 0 : ++curr_skintone; break;
        }
        pPlayer->SetByteValue(PLAYER_BYTES, 0, skintone);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        uint16 bytelimit_human = (pPlayer->getGender() == GENDER_FEMALE) ? 9 : 9;
        uint16 bytelimit_elf = (pPlayer->getGender() == GENDER_FEMALE) ? 8 : 8;
        uint16 bytelimit_gnome = (pPlayer->getGender() == GENDER_FEMALE) ? 4 : 3;
        uint16 bytelimit_dwarf = (pPlayer->getGender() == GENDER_FEMALE) ? 8 : 8;
        uint16 bytelimit_troll = (pPlayer->getGender() == GENDER_FEMALE) ? 5 : 5;
        uint16 bytelimit_orc = (pPlayer->getGender() == GENDER_FEMALE) ? 8 : 8;
        uint16 bytelimit_undead = (pPlayer->getGender() == GENDER_FEMALE) ? 5 : 7;
        uint16 bytelimit_tauren = (pPlayer->getGender() == GENDER_FEMALE) ? 10 : 18;

        uint16 skintone = 0;
        uint16 curr_skintone = pPlayer->GetByteValue(PLAYER_BYTES, 0);

        switch (pPlayer->getRace())
        {
        case RACE_HUMAN:    skintone = (curr_skintone == 0) ? bytelimit_human : --curr_skintone; break;
        case RACE_NIGHTELF: skintone = (curr_skintone == 0) ? bytelimit_elf : --curr_skintone; break;
        case RACE_GNOME:    skintone = (curr_skintone == 0) ? bytelimit_gnome : --curr_skintone; break;
        case RACE_DWARF:    skintone = (curr_skintone == 0) ? bytelimit_dwarf : --curr_skintone; break;
        case RACE_TROLL:    skintone = (curr_skintone == 0) ? bytelimit_troll : --curr_skintone; break;
        case RACE_ORC:      skintone = (curr_skintone == 0) ? bytelimit_orc : --curr_skintone; break;
        case RACE_UNDEAD:   skintone = (curr_skintone == 0) ? bytelimit_undead : --curr_skintone; break;
        case RACE_TAUREN:   skintone = (curr_skintone == 0) ? bytelimit_tauren : --curr_skintone; break;
        }
        pPlayer->SetByteValue(PLAYER_BYTES, 0, skintone);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 3)
    {
        uint16 bytelimit_human  = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 8;
        uint16 bytelimit_elf    = (pPlayer->getGender() == GENDER_FEMALE) ? 9 : 5;
        uint16 bytelimit_gnome  = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 7;
        uint16 bytelimit_dwarf  = (pPlayer->getGender() == GENDER_FEMALE) ? 8 : 10;
        uint16 bytelimit_troll  = (pPlayer->getGender() == GENDER_FEMALE) ? 5 : 10;
        uint16 bytelimit_orc    = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 10;
        uint16 bytelimit_undead = (pPlayer->getGender() == GENDER_FEMALE) ? 7 : 16;
        uint16 bytelimit_tauren = (pPlayer->getGender() == GENDER_FEMALE) ? 4 : 6;

        uint16 feature = 0;
        uint16 curr_feature = pPlayer->GetByteValue(PLAYER_BYTES_2, 0);

        switch (pPlayer->getRace())
        {
        case RACE_HUMAN:    feature = (curr_feature == bytelimit_human) ? 0 : ++curr_feature; break;
        case RACE_NIGHTELF: feature = (curr_feature == bytelimit_elf) ? 0 : ++curr_feature; break;
        case RACE_GNOME:    feature = (curr_feature == bytelimit_gnome) ? 0 : ++curr_feature; break;
        case RACE_DWARF:    feature = (curr_feature == bytelimit_dwarf) ? 0 : ++curr_feature; break;
        case RACE_TROLL:    feature = (curr_feature == bytelimit_troll) ? 0 : ++curr_feature; break;
        case RACE_ORC:      feature = (curr_feature == bytelimit_orc) ? 0 : ++curr_feature; break;
        case RACE_UNDEAD:   feature = (curr_feature == bytelimit_undead) ? 0 : ++curr_feature; break;
        case RACE_TAUREN:   feature = (curr_feature == bytelimit_tauren) ? 0 : ++curr_feature; break;
        }
        pPlayer->SetByteValue(PLAYER_BYTES_2, 0, feature);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 4)
    {
        uint16 bytelimit_human = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 8;
        uint16 bytelimit_elf = (pPlayer->getGender() == GENDER_FEMALE) ? 9 : 5;
        uint16 bytelimit_gnome = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 7;
        uint16 bytelimit_dwarf = (pPlayer->getGender() == GENDER_FEMALE) ? 8 : 10;
        uint16 bytelimit_troll = (pPlayer->getGender() == GENDER_FEMALE) ? 5 : 10;
        uint16 bytelimit_orc = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 10;
        uint16 bytelimit_undead = (pPlayer->getGender() == GENDER_FEMALE) ? 7 : 16;
        uint16 bytelimit_tauren = (pPlayer->getGender() == GENDER_FEMALE) ? 4 : 6;

        uint16 feature = 0;
        uint16 curr_feature = pPlayer->GetByteValue(PLAYER_BYTES_2, 0);

        switch (pPlayer->getRace())
        {
        case RACE_HUMAN:    feature = (curr_feature == 0) ? bytelimit_human : --curr_feature; break;
        case RACE_NIGHTELF: feature = (curr_feature == 0) ? bytelimit_elf : --curr_feature; break;
        case RACE_GNOME:    feature = (curr_feature == 0) ? bytelimit_gnome : --curr_feature; break;
        case RACE_DWARF:    feature = (curr_feature == 0) ? bytelimit_dwarf : --curr_feature; break;
        case RACE_TROLL:    feature = (curr_feature == 0) ? bytelimit_troll : --curr_feature; break;
        case RACE_ORC:      feature = (curr_feature == 0) ? bytelimit_orc : --curr_feature; break;
        case RACE_UNDEAD:   feature = (curr_feature == 0) ? bytelimit_undead : --curr_feature; break;
        case RACE_TAUREN:   feature = (curr_feature == 0) ? bytelimit_tauren : --curr_feature; break;
        }
        pPlayer->SetByteValue(PLAYER_BYTES_2, 0, feature);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 5)
    {
        uint16 bytelimit_human  = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 8;
        uint16 bytelimit_elf    = (pPlayer->getGender() == GENDER_FEMALE) ? 9 : 5;
        uint16 bytelimit_gnome  = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 7;
        uint16 bytelimit_dwarf  = (pPlayer->getGender() == GENDER_FEMALE) ? 8 : 10;
        uint16 bytelimit_troll  = (pPlayer->getGender() == GENDER_FEMALE) ? 5 : 10;
        uint16 bytelimit_orc    = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 10;
        uint16 bytelimit_undead = (pPlayer->getGender() == GENDER_FEMALE) ? 7 : 16;
        uint16 bytelimit_tauren = (pPlayer->getGender() == GENDER_FEMALE) ? 7 : 16;

        uint16 face = 0;
        uint16 curr_face = pPlayer->GetByteValue(PLAYER_BYTES, 1);

        switch (pPlayer->getRace())
        {
        case RACE_HUMAN:    face = (curr_face == bytelimit_human) ? 0 : ++curr_face; break;
        case RACE_NIGHTELF: face = (curr_face == bytelimit_elf) ? 0 : ++curr_face; break;
        case RACE_GNOME:    face = (curr_face == bytelimit_gnome) ? 0 : ++curr_face; break;
        case RACE_DWARF:    face = (curr_face == bytelimit_dwarf) ? 0 : ++curr_face; break;
        case RACE_TROLL:    face = (curr_face == bytelimit_troll) ? 0 : ++curr_face; break;
        case RACE_ORC:      face = (curr_face == bytelimit_orc) ? 0 : ++curr_face; break;
        case RACE_UNDEAD:   face = (curr_face == bytelimit_undead) ? 0 : ++curr_face; break;
        case RACE_TAUREN:   face = (curr_face == bytelimit_tauren) ? 0 : ++curr_face; break;
        }
        pPlayer->SetByteValue(PLAYER_BYTES, 1, face);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 6)
    {
        uint16 bytelimit_human = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 8;
        uint16 bytelimit_elf = (pPlayer->getGender() == GENDER_FEMALE) ? 9 : 5;
        uint16 bytelimit_gnome = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 7;
        uint16 bytelimit_dwarf = (pPlayer->getGender() == GENDER_FEMALE) ? 8 : 10;
        uint16 bytelimit_troll = (pPlayer->getGender() == GENDER_FEMALE) ? 5 : 10;
        uint16 bytelimit_orc = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 10;
        uint16 bytelimit_undead = (pPlayer->getGender() == GENDER_FEMALE) ? 7 : 16;
        uint16 bytelimit_tauren = (pPlayer->getGender() == GENDER_FEMALE) ? 7 : 16;

        uint16 face = 0;
        uint16 curr_face = pPlayer->GetByteValue(PLAYER_BYTES, 1);

        switch (pPlayer->getRace())
        {
        case RACE_HUMAN:    face = (curr_face == 0) ? bytelimit_human : --curr_face; break;
        case RACE_NIGHTELF: face = (curr_face == 0) ? bytelimit_elf : --curr_face; break;
        case RACE_GNOME:    face = (curr_face == 0) ? bytelimit_gnome : --curr_face; break;
        case RACE_DWARF:    face = (curr_face == 0) ? bytelimit_dwarf : --curr_face; break;
        case RACE_TROLL:    face = (curr_face == 0) ? bytelimit_troll : --curr_face; break;
        case RACE_ORC:      face = (curr_face == 0) ? bytelimit_orc : --curr_face; break;
        case RACE_UNDEAD:   face = (curr_face == 0) ? bytelimit_undead : --curr_face; break;
        case RACE_TAUREN:   face = (curr_face == 0) ? bytelimit_tauren : --curr_face; break;
        }
        pPlayer->SetByteValue(PLAYER_BYTES, 1, face);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }
    pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

bool ItemUseSpell_shop_racechange(Player* pPlayer, Item* pItem, const SpellCastTargets&)
{
    if (pPlayer->isInCombat() || pPlayer->IsBeingTeleported() || (pPlayer->getDeathState() == CORPSE) || pPlayer->IsMoving())
    {
        pPlayer->GetSession()->SendNotification("Can't change race at this moment!");
        return false;
    }

    uint32 race = pPlayer->getRace();
    uint32 bytes  = pPlayer->GetUInt32Value(PLAYER_BYTES);
    uint32 bytes2 = pPlayer->GetUInt32Value(PLAYER_BYTES_2);
    uint8 player_class = pPlayer->getClass();
    uint8 player_gender  = pPlayer->getGender();

    switch (pItem->GetEntry())
    {
    case 40013: // Human
        if (pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_SHAMAN)
        {
            pPlayer->GetSession()->SendNotification("This race does not support your class.");
            return false;
        }
        bytes = pPlayer->getGender() == GENDER_MALE ? 101058307 : 100730885;
        race = RACE_HUMAN;
        break;
    case 40014: // Gnome
        if (pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_PRIEST || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_SHAMAN)
        {
            pPlayer->GetSession()->SendNotification("This race does not support your class.");
            return false;
        }
        bytes = pPlayer->getGender() == GENDER_MALE ? 67372546 : 131076;
        race = RACE_GNOME;
        break;
    case 40015: // Dwarf
        if (pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_MAGE || pPlayer->getClass() == CLASS_WARLOCK || pPlayer->getClass() == CLASS_SHAMAN)
        {
            pPlayer->GetSession()->SendNotification("This race does not support your class.");
            return false;
        }
        bytes = pPlayer->getGender() == GENDER_MALE ? 50528773 : 34406912;
        race = RACE_DWARF;
        break;
    case 40016: // Night Elf
        if (pPlayer->getClass() == CLASS_MAGE || pPlayer->getClass() == CLASS_WARLOCK || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_SHAMAN)
        {
            pPlayer->GetSession()->SendNotification("This race does not support your class.");
            return false;
        }
        bytes = pPlayer->getGender() == GENDER_MALE ? 132615 : 67503620;
        race = RACE_NIGHTELF;
        break;
    case 40017: // Orc
        if (pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_PRIEST || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_MAGE)
        {
            pPlayer->GetSession()->SendNotification("This race does not support your class.");
            return false;
        }
        bytes = pPlayer->getGender() == GENDER_MALE ? 84214788 : 84214788;
        race = RACE_ORC;
        break;
    case 40018: // Troll
        if (pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_WARLOCK || pPlayer->getClass() == CLASS_PALADIN)
        {
            pPlayer->GetSession()->SendNotification("This race does not support your class.");
            return false;
        }
        bytes = pPlayer->getGender() == GENDER_MALE ? 33751041 : 131587;
        race = RACE_TROLL;
        break;
    case 40019: // Tauren
        if (pPlayer->getClass() == CLASS_PRIEST || pPlayer->getClass() == CLASS_MAGE || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_PALADIN)
        {
            pPlayer->GetSession()->SendNotification("This race does not support your class.");
            return false;
        }
        bytes = pPlayer->getGender() == GENDER_MALE ? 17105153 : 393736;
        race = RACE_TAUREN;
        break;
    case 40020: // Undead
        if (pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_HUNTER)
        {
            pPlayer->GetSession()->SendNotification("This race does not support your class.");
            return false;
        }
        bytes = pPlayer->getGender() == GENDER_MALE ? 117703426 : 151126786;
        race = RACE_UNDEAD;
        break;
    }

    bytes2 |= (pPlayer->GetUInt32Value(PLAYER_BYTES_2) & 0xFFFFFF00);
    pPlayer->SetUInt32Value(PLAYER_BYTES, bytes);
    pPlayer->SetUInt32Value(PLAYER_BYTES_2, bytes2);
    pPlayer->SetByteValue(UNIT_FIELD_BYTES_0, 2, player_gender);
    pPlayer->ChangeRace(race, player_gender, bytes, bytes2);
    return true;
}

bool ItemUseSpell_shop_changegender(Player* pPlayer, Item* pItem, const SpellCastTargets&)
{
    if (!pPlayer) return false;

    uint8 player_gender = (pPlayer->getGender() == GENDER_MALE) ? GENDER_FEMALE : GENDER_MALE;
    pPlayer->SetByteValue(UNIT_FIELD_BYTES_0, 2, player_gender);
    pPlayer->InitPlayerDisplayIds();
    pPlayer->SaveToDB();
    return true;
}

void AddSC_shop_features()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "shop_changegender";
    newscript->pItemUseSpell = &ItemUseSpell_shop_changegender;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "shop_racechange";
    newscript->pItemUseSpell = &ItemUseSpell_shop_racechange;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "shop_brainwashing_device";
    newscript->pItemUseSpell = &ItemUseSpell_shop_brainwashing_device;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "shop_character_rename";
    newscript->pItemUseSpell = &ItemUseSpell_shop_character_rename;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "shop_mailbox";
    newscript->pItemUseSpell = &ItemUseSpell_shop_mailbox;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_brainwashing_device";
    newscript->pGOHello = &GOHello_go_brainwashing_device;
    newscript->pGOGossipSelect = &GOSelect_go_brainwashing_device;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_barber";
    newscript->pGossipHello = &GossipHello_npc_barber;
    newscript->pGossipSelect = &GossipSelect_npc_barber;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_surgeon";
    newscript->pGossipHello = &GossipHello_npc_surgeon;
    newscript->pGossipSelect = &GossipSelect_npc_surgeon;
    newscript->RegisterSelf();
} 