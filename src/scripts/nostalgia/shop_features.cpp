#include "scriptPCH.h"

bool ItemUseSpell_shop_character_rename(Player* pPlayer, Item* pItem, const SpellCastTargets&)
{
    if (!pPlayer) return false;

    ChatHandler(pPlayer).PSendSysMessage("Please logout and choose a new name.");
    pPlayer->SetAtLoginFlag(AT_LOGIN_RENAME);
    return true;
}

bool ItemUseSpell_shop_mailbox(Player* pPlayer, Item* pItem, const SpellCastTargets&)
{
	if (!pPlayer) return false;

    float dis{ 2.0F };
    float x, y, z;
    pPlayer->GetSafePosition(x, y, z);
    x += dis * cos(pPlayer->GetOrientation());
    y += dis * sin(pPlayer->GetOrientation());

    pPlayer->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
    pPlayer->SummonGameObject(144112, x, y, z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 180, true);
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
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "New hair color", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "New hair style", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
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
        }
        pPlayer->SetByteValue(PLAYER_BYTES, 3, color);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        uint16 bytelimit_human  = (pPlayer->getGender() == GENDER_FEMALE) ? 18 : 11;
        uint16 bytelimit_elf    = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 6;
        uint16 bytelimit_gnome  = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 6;
        uint16 bytelimit_dwarf  = (pPlayer->getGender() == GENDER_FEMALE) ? 13 : 10;
        uint16 bytelimit_troll  = (pPlayer->getGender() == GENDER_FEMALE) ? 4 : 5;
        uint16 bytelimit_orc    = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 6;
        uint16 bytelimit_undead = (pPlayer->getGender() == GENDER_FEMALE) ? 9 : 9;

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
        }
        pPlayer->SetByteValue(PLAYER_BYTES, 2, style);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }
    pCreature->HandleEmote(25);
    pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

bool GossipHello_npc_surgeon(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->HasItemCount(40004, 1))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "New skin tone", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "New facial feature", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
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
        }
        pPlayer->SetByteValue(PLAYER_BYTES, 0, skintone);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        uint16 bytelimit_human  = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 8;
        uint16 bytelimit_elf    = (pPlayer->getGender() == GENDER_FEMALE) ? 9 : 5;
        uint16 bytelimit_gnome  = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 7;
        uint16 bytelimit_dwarf  = (pPlayer->getGender() == GENDER_FEMALE) ? 8 : 10;
        uint16 bytelimit_troll  = (pPlayer->getGender() == GENDER_FEMALE) ? 5 : 10;
        uint16 bytelimit_orc    = (pPlayer->getGender() == GENDER_FEMALE) ? 6 : 10;
        uint16 bytelimit_undead = (pPlayer->getGender() == GENDER_FEMALE) ? 7 : 16;

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
        }
        pPlayer->SetByteValue(PLAYER_BYTES_2, 0, feature);
        pPlayer->SetDisplayId(15435);
        pPlayer->m_Events.AddEvent(new DemorphAfterTime(pPlayer->GetGUID()), pPlayer->m_Events.CalculateTime(150));
    }
    pCreature->HandleEmote(EMOTE_ONESHOT_POINT);
    pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

void AddSC_shop_features()
{
    Script *newscript;

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