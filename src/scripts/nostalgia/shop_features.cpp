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

bool ItemUseSpell_shop_character_haircolor(Player* pPlayer, Item* pItem, const SpellCastTargets&)
{
    uint8 color = 0;
    switch (pItem->GetEntry())
    {
    // Night Elves
    case 50107: color = 0; break; // Grass Green
    case 50108: color = 1; break; // Green
    case 50109: color = 2; break; // Dark Green
    case 50110: color = 3; break; // Aquamarine
    case 50111: color = 4; break; // White
    case 50112: color = 5; break; // Blue
    case 50113: color = 6; break; // Dark Blue
    case 50114: color = 7; break; // Purple
    // Humans
    case 50115: color = 0; break; // Black
    case 50116: color = 1; break; // Crushed Garnet
    case 50117: color = 2; break; // Havana Brown
    case 50118: color = 3; break; // Copper Shimmer
    case 50119: color = 4; break; // Reddish Blonde
    case 50120: color = 5; break; // Sunflower Blonde
    case 50121: color = 6; break; // Beeline Honey
    case 50122: color = 7; break; // Pure Diamond
    case 50123: color = 8; break; // Dark Ash Grey
    case 50124: color = 9; break; // Light Ash Grey
    // Gnomes
    case 50125: color = 0; break; // Black
    case 50126: color = 1; break; // Chocolate Brown
    case 50127: color = 2; break; // Ash Blonde
    case 50128: color = 3; break; // Diamond Blonde
    case 50129: color = 4; break; // Dream Purple
    case 50130: color = 5; break; // Ruby Fusion
    case 50131: color = 6; break; // Steel Blue
    case 50132: color = 7; break; // Pure Green
    case 50133: color = 8; break; // Shining Pink
    // Dwarves
    case 50134: color = 0; break; // Copper Shimmer
    case 50135: color = 1; break; // Reddish Blonde
    case 50136: color = 2; break; // Dark Orange
    case 50137: color = 3; break; // Ash Blonde
    case 50138: color = 4; break; // Light Auburn
    case 50139: color = 5; break; // Black
    case 50140: color = 6; break; // Caramel
    case 50141: color = 7; break; // Light Ash Grey
    case 50142: color = 8; break; // Dark Ash Grey
    // Trolls
    case 50143: color = 0; break; // Purple
    case 50144: color = 1; break; // Red
    case 50145: color = 2; break; // Orange
    case 50146: color = 3; break; // Yellow
    case 50147: color = 4; break; // Grass Green
    case 50148: color = 5; break; // Mint Blue
    case 50149: color = 6; break; // Light Blue
    case 50150: color = 7; break; // Dark Blue
    case 50151: color = 8; break; // Ash Grey
    case 50152: color = 9; break; // Snow White
    // Orcs
    case 50153: color = 0; break; // Blue Black
    case 50154: color = 1; break; // Oak Brown
    case 50155: color = 2; break; // Dark Purple
    case 50156: color = 3; break; // Lilac Violet
    case 50157: color = 4; break; // Rich Purple
    case 50158: color = 5; break; // Black
    case 50159: color = 6; break; // Dark Ash Grey
    case 50160: color = 7; break; // Light Ash Grey
    // Undeads
    case 50161: color = 0; break; // Lime Green
    case 50162: color = 1; break; // Ash Rose
    case 50163: color = 2; break; // Mud Brown
    case 50164: color = 3; break; // Green Blonde
    case 50165: color = 4; break; // Ash Blonde
    case 50167: color = 5; break; // Mint Blue
    case 50168: color = 6; break; // Mud Green
    case 50169: color = 7; break; // Light Teal 
    case 50170: color = 8; break; // Dirty Purple
    case 50171: color = 9; break; // Ash Black
    }

    pPlayer->SetByteValue(PLAYER_BYTES, 3, color);
    pPlayer->SetDisplayId(4); // This is the first id in the dbc and exists in all clients.
    return false;
}

void AddSC_shop_features()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "shop_character_haircolor";
    newscript->pItemUseSpell = &ItemUseSpell_shop_character_haircolor;
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

} 