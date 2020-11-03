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
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hair color | Back", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hair color | Next", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hair style | Back", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Hair style | Next", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    }

    pPlayer->SEND_GOSSIP_MENU(90370, pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_barber(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    uint16 bytelimit_human  = 9;
    uint16 bytelimit_elf    = 7;
    uint16 bytelimit_gnome  = 8;
    uint16 bytelimit_dwarf  = 8;
    uint16 bytelimit_troll  = 9;
    uint16 bytelimit_orc    = 7;
    uint16 bytelimit_undead = 9;

    uint16 color = 0;
    uint16 curr_color = pPlayer->GetByteValue(PLAYER_BYTES, 3);

    if (!curr_color)
        return false;

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        switch (pPlayer->getRace())
        {
        case RACE_HUMAN:
            if (curr_color = bytelimit_human)
                color = 0;
            else
            color += curr_color;
            break;
        default:
            break;
        }

        pPlayer->SetByteValue(PLAYER_BYTES, 3, color);
        pPlayer->SetDisplayId(4); 
    }

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
} 