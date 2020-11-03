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

void AddSC_shop_features()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "shop_character_rename";
    newscript->pItemUseSpell = &ItemUseSpell_shop_character_rename;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "shop_mailbox";
    newscript->pItemUseSpell = &ItemUseSpell_shop_mailbox;
    newscript->RegisterSelf();
} 