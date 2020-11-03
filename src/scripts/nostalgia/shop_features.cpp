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
    if (pPlayer->getLevel() >= 10 && pPlayer->HasItemCount(51715, 1))
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

} 