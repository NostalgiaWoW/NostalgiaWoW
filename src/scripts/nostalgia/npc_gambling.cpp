#include "scriptPCH.h"
#include <unordered_map>

#define GAMBLING_TEXT 120000
#define OPT1 "125 gold coins."
#define OPT2 "250 gold coins."
#define OPT3 "500 gold coins."
#define OPT4 "1000 gold coins."

#define COIN_SOUND 1204

#define SPELL_FIREWORK 11543

#define FIVE_MINUTES 5 * 60

struct GamblerInfo
{
    uint32 betCount;
    uint32 lastBet;
    time_t timestamp;
};

std::unordered_map<uint64, GamblerInfo> gamblingRecords;

uint32 handleRecords(Player* pPlayer, uint32 amount, int result)
{
    GamblerInfo currentInfo{};
    uint32 newAmount = 0;
    time_t currentTime = time(nullptr);

    if (!gamblingRecords.count(pPlayer->GetGUID()))
    {
        currentInfo =
        {
            0,
            amount,
            currentTime
        };
    }
    else
        currentInfo = gamblingRecords[pPlayer->GetGUID()];

    // Reset count if amount is different or last bet is older than 5 minutes.
    if (currentInfo.lastBet != amount || currentInfo.timestamp < currentTime - FIVE_MINUTES)
        currentInfo.betCount = 0;
    currentInfo.betCount++;

	if (currentInfo.betCount == 3 && currentInfo.lastBet == amount)
	{
		if (result > 75)
			newAmount = amount * 3;
		else if (result <= 75)
			newAmount = 0;

		currentInfo.betCount = 0;
	}
	else if (result > 55)
		newAmount = amount * 2;
	else if (result <= 55) {
		newAmount = 0;
		currentInfo.betCount = 0;
	}

    currentInfo.lastBet = amount;
    currentInfo.timestamp = currentTime;
    gamblingRecords[pPlayer->GetGUID()] = currentInfo;

    return newAmount;
}

bool GossipHello_npc_gambling(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, OPT1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, OPT2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, OPT3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, OPT4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);

    pPlayer->SEND_GOSSIP_MENU(GAMBLING_TEXT, pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_gambling(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    uint32 amount;

    switch (uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            amount = 1250000;
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            amount = 2500000;
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            amount = 5000000;
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:
            amount = 10000000;
            break;
        default:
            return true;
    }

    if (pPlayer->GetMoney() < amount)
    {
        pPlayer->GetSession()->SendNotification("You don't have enough money!");
        pPlayer->PlayerTalkClass->CloseGossip();
        return true;
    }

    pPlayer->ModifyMoney(amount * -1);

    pCreature->HandleEmote(EMOTE_ONESHOT_ATTACK1H);
    pCreature->PlayDirectSound(COIN_SOUND, pPlayer); // Coin sound

    int result = irand(1, 100);
    pCreature->PMonsterEmote("Gazrik Goldenspark rolls a dice for %s... %i!", nullptr, false,
                             pPlayer->GetName(),
                             result);

    uint32 amountToAward = handleRecords(pPlayer, amount, result);
    if (amountToAward > 0)
    {
        pPlayer->ModifyMoney(amountToAward);
		pCreature->MonsterSay("Winner!");

        if (amountToAward >= amount * 3)
        {
			pCreature->MonsterSay("You're on a streak!");
            pPlayer->SendSpellGo(pPlayer, SPELL_FIREWORK);
        }
        else
            pPlayer->HandleEmote(EMOTE_ONESHOT_CHEER);
    }
	else
	{
		pPlayer->HandleEmote(EMOTE_ONESHOT_CRY);
		CharacterDatabase.PExecute("UPDATE gambling_bank SET bank = bank+%u", amount);
	}
    pPlayer->PlayerTalkClass->CloseGossip();
    return true;
}

void AddSC_npc_gambling()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_gambling";
    newscript->pGossipHello = &GossipHello_npc_gambling;
    newscript->pGossipSelect = &GossipSelect_npc_gambling;
    newscript->RegisterSelf();
}