/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
 * Copyright (C) 2011-2016 Nostalrius <https://nostalrius.org>
 * Copyright (C) 2016-2017 Elysium Project <https://github.com/elysium-project>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Common.h"
#include "Database/DatabaseEnv.h"
#include "World.h"
#include "Player.h"
#include "Opcodes.h"
#include "Chat.h"
#include "ObjectAccessor.h"
#include "Language.h"
#include "AccountMgr.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "SystemConfig.h"
#include "revision.h"
#include "Util.h"
#include "Nostalgia/PvPArenaSystem.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"

bool registerPlayerToBg(WorldSession * sess, BattleGroundTypeId bgid)
{
    Player* pl = sess->GetPlayer();
	//if (bgid == BATTLEGROUND_TEST)
	//{
	//	sess->SendBattlegGroundList(pl->GetObjectGuid(), bgid);
	//	return true;
	//}

	if (!pl->GetBGAccessByLevel(bgid))
        return false;
    sess->SendBattlegGroundList(pl->GetObjectGuid(), bgid);
    return true;
}

bool ChatHandler::HandleGoWarsongCommand(char * args)
{
    Player * pPlayer = m_session->GetPlayer();

    if (!pPlayer)
        return false;

    if (pPlayer->isInCombat() || pPlayer->InBattleGround() || pPlayer->IsBeingTeleported() || pPlayer->HasSpellCooldown(20939) || pPlayer->HasSpellCooldown(26013) || (pPlayer->getDeathState() == CORPSE) || (pPlayer->getLevel() < 10))
    {
        PSendSysMessage("You can not queue yet!");
        return false;
    }

    return registerPlayerToBg(m_session, BattleGroundTypeId(BATTLEGROUND_WS));
}
bool ChatHandler::HandleGoArathiCommand(char *args)
{

    Player * pPlayer = m_session->GetPlayer();

    if (!pPlayer)
        return false;

    if (pPlayer->isInCombat() || pPlayer->InBattleGround() || pPlayer->IsBeingTeleported() || pPlayer->HasSpellCooldown(20939) || pPlayer->HasSpellCooldown(26013) || (pPlayer->getDeathState() == CORPSE) || (pPlayer->getLevel() < 10))
    {
        PSendSysMessage("You can not queue yet!");
        return false;
    }

    return registerPlayerToBg(m_session, BattleGroundTypeId(BATTLEGROUND_AB));
}

//bool ChatHandler::HandleGoTestBGCommand(char* args)
//{
//
//	Player* pPlayer = m_session->GetPlayer();
//
//	if (!pPlayer)
//		return false;
//
//	if (pPlayer->isInCombat() || pPlayer->InBattleGround() || pPlayer->IsBeingTeleported() || pPlayer->HasSpellCooldown(20939) || pPlayer->HasSpellCooldown(26013) || (pPlayer->getDeathState() == CORPSE) || (pPlayer->getLevel() < 10))
//	{
//		PSendSysMessage("You can not queue yet!");
//		return false;
//	}
//
//	return registerPlayerToBg(m_session, BATTLEGROUND_ARENA);
//}
bool ChatHandler::HandleGoAlteracCommand(char *args)
{

    Player * pPlayer = m_session->GetPlayer();

    if (!pPlayer)
        return false;

    if (pPlayer->isInCombat() || pPlayer->InBattleGround() || pPlayer->IsBeingTeleported() || pPlayer->HasSpellCooldown(20939) || pPlayer->HasSpellCooldown(26013) || (pPlayer->getDeathState() == CORPSE) || (pPlayer->getLevel() < 10))
    {
        PSendSysMessage("You can not queue yet!");
        return false;
    }

    return registerPlayerToBg(m_session, BattleGroundTypeId(BATTLEGROUND_AV));
}

bool ChatHandler::HandleXpCommand(char* args)
{
    if (!*args)
        return false;

    Player* pPlayer = m_session->GetPlayer();

    if (!pPlayer)
        return false;

    bool value;
    if (!ExtractOnOff(&args, value))
    {
        SendSysMessage(LANG_USE_BOL);
        SetSentErrorMessage(true);
        return false;
    }

    pPlayer->SetForced_X1_XpRate(!value);
    pPlayer->ShowCurrentXpRate();

    return true;
}

bool ChatHandler::HandleHelpCommand(char* args)
{
    if (!*args)
    {
        ShowHelpForCommand(getCommandTable(), "help");
        ShowHelpForCommand(getCommandTable(), "");
    }
    else
    {
        if (!ShowHelpForCommand(getCommandTable(), args))
            SendSysMessage(LANG_NO_CMD);
    }

    return true;
}

bool ChatHandler::HandleCommandsCommand(char* /*args*/)
{
    ShowHelpForCommand(getCommandTable(), "");
    return true;
}

bool ChatHandler::HandleAccountCommand(char* args)
{
    // let show subcommands at unexpected data in args
    if (*args)
        return false;

    AccountTypes gmlevel = GetAccessLevel();
    PSendSysMessage(LANG_ACCOUNT_LEVEL, uint32(gmlevel));
    return true;
}

bool ChatHandler::HandleStartCommand(char* /*args*/)
{
    Player *chr = m_session->GetPlayer();

    if (chr->IsTaxiFlying())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    if (chr->isInCombat())
    {
        SendSysMessage(LANG_YOU_IN_COMBAT);
        SetSentErrorMessage(true);
        return false;
    }

    // cast spell Stuck
    chr->CastSpell(chr, 7355, false);
    return true;
}

bool ChatHandler::HandleUnstuckCommand(char* /*args*/)
{
    Player * pPlayer = m_session->GetPlayer();

    if (!pPlayer)
        return false;

    if (pPlayer->isInCombat() || pPlayer->InBattleGround() || pPlayer->IsTaxiFlying() || pPlayer->HasSpellCooldown(20939) || (pPlayer->getDeathState() == CORPSE) || (pPlayer->getLevel() < 10))
    {
        SendSysMessage(LANG_UNSTUCK_UNAVAILABLE);
        return false;
    }

    if (pPlayer->isAlive())
    {
        pPlayer->CastSpell(pPlayer, 20939, false);
        SendSysMessage(LANG_UNSTUCK_ALIVE);
    }
    else
    {
        pPlayer->AddAura(15007); // Add Resurrection Sickness
        pPlayer->AddSpellCooldown(20939, 0, time(nullptr) + 3600000); // Trigger 1 Hour Cooldown
        // Get nearest graveyard.
        WorldSafeLocsEntry const *ClosestGrave = sObjectMgr.GetClosestGraveYard(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetMapId(), pPlayer->GetTeam());
        if (!ClosestGrave) //No nearby graveyards (stuck in void?). Send ally to Westfall, Horde to Barrens.
            ClosestGrave = pPlayer->GetTeamId() ? sWorldSafeLocsStore.LookupEntry(10) : sWorldSafeLocsStore.LookupEntry(4);
        if (ClosestGrave)
            pPlayer->TeleportTo(ClosestGrave->map_id, ClosestGrave->x, ClosestGrave->y, ClosestGrave->z, 0, 0);
        SendSysMessage(LANG_UNSTUCK_DEAD);
    }

    sLog.outInfo("Player %s (guid %u) used unstuck command at map %u (%f, %f, %f).", pPlayer->GetName(), pPlayer->GetGUIDLow(), pPlayer->GetMapId(), pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ());
    return true;
}

bool ChatHandler::HandleServerInfoCommand(char* /*args*/)
{
    uint32 activeClientsNum = sWorld.GetActiveSessionCount();
    uint32 queuedClientsNum = sWorld.GetQueuedSessionCount();
    uint32 maxActiveClientsNum = sWorld.GetMaxActiveSessionCount();
    uint32 maxQueuedClientsNum = sWorld.GetMaxQueuedSessionCount();
    std::string str = secsToTimeString(sWorld.GetUptime());

    SendSysMessage("Core revision: " _FULLVERSION);
    PSendSysMessage(LANG_UPTIME, str.c_str());

    return true;
}

bool ChatHandler::HandleDismountCommand(char* /*args*/)
{
    //If player is not mounted, so go out :)
    if (!m_session->GetPlayer()->IsMounted())
    {
        SendSysMessage(LANG_CHAR_NON_MOUNTED);
        SetSentErrorMessage(true);
        return false;
    }

    if (m_session->GetPlayer()->IsTaxiFlying())
    {
        SendSysMessage(LANG_YOU_IN_FLIGHT);
        SetSentErrorMessage(true);
        return false;
    }

    m_session->GetPlayer()->Unmount();
    m_session->GetPlayer()->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
    return true;
}

bool ChatHandler::HandleSaveCommand(char* /*args*/)
{
    Player *player = m_session->GetPlayer();

    // save GM account without delay and output message (testing, etc)
    if (GetAccessLevel() > SEC_PLAYER)
    {
        player->SaveToDB();
        SendSysMessage(LANG_PLAYER_SAVED);
        return true;
    }

    // save or plan save after 20 sec (logout delay) if current next save time more this value and _not_ output any messages to prevent cheat planning
    uint32 save_interval = sWorld.getConfig(CONFIG_UINT32_INTERVAL_SAVE);
    if (save_interval == 0 || (save_interval > 20 * IN_MILLISECONDS && player->GetSaveTimer() <= save_interval - 20 * IN_MILLISECONDS))
        player->SaveToDB();
    SendSysMessage(LANG_PLAYER_SAVED);
    return true;
}

bool ChatHandler::HandleGMListIngameCommand(char* /*args*/)
{
    std::list< std::pair<std::string, bool> > names;

    {
        HashMapHolder<Player>::ReadGuard g(HashMapHolder<Player>::GetLock());
        HashMapHolder<Player>::MapType &m = sObjectAccessor.GetPlayers();
        for (HashMapHolder<Player>::MapType::const_iterator itr = m.begin(); itr != m.end(); ++itr)
        {
            AccountTypes itr_sec = itr->second->GetSession()->GetSecurity();
            if ((itr->second->isGameMaster() || (itr_sec > SEC_PLAYER && itr_sec <= (AccountTypes)sWorld.getConfig(CONFIG_UINT32_GM_LEVEL_IN_GM_LIST))) &&
                    (!m_session || itr->second->IsVisibleGloballyFor(m_session->GetPlayer())))
                names.push_back(std::make_pair<std::string, bool>(GetNameLink(itr->second), itr->second->IsAcceptWhispers()));
        }
    }

    if (!names.empty())
    {
        SendSysMessage(LANG_GMS_ON_SRV);

        char const* accepts = GetMangosString(LANG_GM_ACCEPTS_WHISPER);
        char const* not_accept = GetMangosString(LANG_GM_NO_WHISPER);
        for (std::list<std::pair< std::string, bool> >::const_iterator iter = names.begin(); iter != names.end(); ++iter)
            PSendSysMessage("%s - %s", iter->first.c_str(), iter->second ? accepts : not_accept);
    }
    else
        SendSysMessage(LANG_GMS_NOT_LOGGED);

    return true;
}

bool ChatHandler::HandleAccountPasswordCommand(char* args)
{
    // allow use from RA, but not from console (not have associated account id)
    if (!GetAccountId())
    {
        SendSysMessage(LANG_RA_ONLY_COMMAND);
        SetSentErrorMessage(true);
        return false;
    }

    // allow or quoted string with possible spaces or literal without spaces
    char *old_pass = ExtractQuotedOrLiteralArg(&args);
    char *new_pass = ExtractQuotedOrLiteralArg(&args);
    char *new_pass_c = ExtractQuotedOrLiteralArg(&args);

    if (!old_pass || !new_pass || !new_pass_c)
        return false;

    std::string password_old = old_pass;
    std::string password_new = new_pass;
    std::string password_new_c = new_pass_c;

    if (password_new != password_new_c)
    {
        SendSysMessage(LANG_NEW_PASSWORDS_NOT_MATCH);
        SetSentErrorMessage(true);
        return false;
    }

    if (!sAccountMgr.CheckPassword(GetAccountId(), password_old, m_session->GetUsername()))
    {
        SendSysMessage(LANG_COMMAND_WRONGOLDPASSWORD);
        SetSentErrorMessage(true);
        return false;
    }

    AccountOpResult result = sAccountMgr.ChangePassword(GetAccountId(), password_new, m_session->GetUsername());

    switch (result)
    {
        case AOR_OK:
            SendSysMessage(LANG_COMMAND_PASSWORD);
            break;
        case AOR_PASS_TOO_LONG:
            SendSysMessage(LANG_PASSWORD_TOO_LONG);
            SetSentErrorMessage(true);
            return false;
        case AOR_NAME_NOT_EXIST:                            // not possible case, don't want get account name for output
        default:
            SendSysMessage(LANG_COMMAND_NOTCHANGEPASSWORD);
            SetSentErrorMessage(true);
            return false;
    }
    SetSentErrorMessage(true);
    // Pas de log du nouveau mdp dans les logs GM par exemple.
    return false;
}

bool ChatHandler::HandleAccountLockCommand(char* args)
{
    // allow use from RA, but not from console (not have associated account id)
    if (!GetAccountId())
    {
        SendSysMessage(LANG_RA_ONLY_COMMAND);
        SetSentErrorMessage(true);
        return false;
    }

    bool value;
    if (!ExtractOnOff(&args, value))
    {
        SendSysMessage(LANG_USE_BOL);
        SetSentErrorMessage(true);
        return false;
    }

    if (value)
    {
        LoginDatabase.PExecute("UPDATE account SET locked = '1' WHERE id = '%u'", GetAccountId());
        PSendSysMessage(LANG_COMMAND_ACCLOCKLOCKED);
    }
    else
    {
        LoginDatabase.PExecute("UPDATE account SET locked = '0' WHERE id = '%u'", GetAccountId());
        PSendSysMessage(LANG_COMMAND_ACCLOCKUNLOCKED);
    }

    return true;
}

/// Display the 'Message of the day' for the realm
bool ChatHandler::HandleServerMotdCommand(char* /*args*/)
{
    PSendSysMessage(LANG_MOTD_CURRENT, sWorld.GetMotd());
    return true;
}

bool ChatHandler::HandleWhisperRestrictionCommand(char* args)
{
    if (!*args)
    {
        PSendSysMessage("Whisper restriction is %s", GetSession()->GetPlayer()->isEnabledWhisperRestriction() ? "ON" : "OFF");
        return true;
    }

    bool value;
    if (!ExtractOnOff(&args, value))
    {
        SendSysMessage(LANG_USE_BOL);
        SetSentErrorMessage(true);
        return false;
    }

    GetSession()->GetPlayer()->setWhisperRestriction(value);
    PSendSysMessage("Whisper restriction is %s", value ? "ON" : "OFF");
    return false;
}

bool ChatHandler::HandleVIPListAuras(char* /*args*/)
{
    PSendSysMessage("Visual auras:");
    for (uint32 aura : sWorld.GetVIPVisuals())
    {
        if (SpellEntry const* entry = sSpellMgr.GetSpellEntry(aura))
            PSendSysMessage("-- %s - %u", entry->SpellName[sWorld.GetDefaultDbcLocale()], aura);
    }

    return true;
}

bool ChatHandler::HandleVIPAura(char * args)
{
    Player* player = m_session->GetPlayer();
    if (!player)
        return false;

    if (!player->HasPremiumAccount() || sWorld.GetVIPVisuals().empty())
        return true;

    for (uint32 aura : sWorld.GetVIPVisuals())
        player->RemoveAurasDueToSpell(aura);

    uint32 aura = SelectRandomContainerElement(sWorld.GetVIPVisuals());
    player->CastSpell(player, aura, true);
    return true;
}

bool ChatHandler::HandleVIPUnAura(char * args)
{
    Player* player = m_session->GetPlayer();
    if (!player)
        return false;

    for (uint32 aura : sWorld.GetVIPVisuals())
        player->RemoveAurasDueToSpell(aura);
    return true;
}

bool ChatHandler::HandleDuelModCommand(char* args)
{
    if (!*args)
        return false;

    bool value;
    if (!ExtractOnOff(&args, value))
    {
        SendSysMessage(LANG_USE_BOL);
        SetSentErrorMessage(true);
        return false;
    }

    GetSession()->GetPlayer()->SetDuelReplenishState(value);
    PSendSysMessage("Duel replenishment is %s.", value ? "enabled" : "disabled");

    return true;
}

bool ChatHandler::HandleInspectModCommand(char* args)
{
    if (!*args)
        return false;

    bool value;
    if (!ExtractOnOff(&args, value))
    {
        SendSysMessage(LANG_USE_BOL);
        SetSentErrorMessage(true);
        return false;
    }

    GetSession()->GetPlayer()->SetInspectState(!value);
    PSendSysMessage("Inspect is currently being %s.", value ? "allowed" : "blocked");

    return true;
}

bool ChatHandler::HandleArenaCommand(char* args)
{
	auto player = GetSession()->GetPlayer();

	player->PlayerTalkClass->ClearMenus();

	if (sPvPArenaSystem->IsInQueue(player))
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Leave Queue", PvPArenaSystem::SenderId, 10);
	}
	else {
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "Queue Arena", PvPArenaSystem::CommandSenderId, 4);
	}

	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Spectate Arena", PvPArenaSystem::CommandSenderId, 5);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "Your PvP Stats", PvPArenaSystem::CommandSenderId, 6);
	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, "View Top Arena Players", PvPArenaSystem::CommandSenderId, 7);

	player->SEND_GOSSIP_MENU(877, player->GetObjectGuid());
	return true;
}


bool ChatHandler::HandleBountyCommand(char* args)
{

	// Syntax: .bounty $TARGETPLAYER $PRICE
	Player* target;
	ObjectGuid target_guid;
	std::string target_name;

	auto player = GetSession()->GetPlayer();

	if (!ExtractPlayerTarget(&args, &target, &target_guid, &target_name))
		return false;

	uint32 price = atoi(args);

	if (!player || !price || !target)
		return false;

	if (!*args)
	{
		PSendSysMessage("Incorrect usage of the bounty command. Please try again using .bounty PLAYERNAME BOUNTYPRICE.");
		return false;
	}

	QueryResult *result = CharacterDatabase.PQuery("SELECT posterGuid FROM bounty WHERE posterGuid = %u", player->GetGUIDLow());

	if (result)
	{
		PSendSysMessage("You cannot post multiple bounties. Please wait until the bounty is concluded or cancelled.");
		return false;
	}

	if (price < 1000)
	{
		PSendSysMessage("You must pay a minimum of 1000g to post a bounty!");
		return false;
	}

	if (player->GetMoney() < (price * 10000))
	{
		PSendSysMessage("You don't have enough money for this bounty!");
		return false;
	}

	if (!player->FindNearestGameObject(3100147, 3))
	{
		PSendSysMessage("You must be at a Bounty Board to post a bounty!");
		return false;
	}

	// If all checks are successful
	else {

		uint32 targetZone = target->GetZoneId();
		uint32 targetArea = target->GetAreaId();

		const auto* zoneEntry = AreaEntry::GetById(targetZone);
		const auto* areaEntry = AreaEntry::GetById(targetArea);

		std::string zoneName = "<unknown>";
		std::string areaName = "<unknown>";

		if (zoneEntry)
		{
			zoneName = zoneEntry->Name;
			sObjectMgr.GetAreaLocaleString(zoneEntry->Id, GetSessionDbLocaleIndex(), &zoneName);
		}

		if (areaEntry)
		{
			areaName = areaEntry->Name;
			sObjectMgr.GetAreaLocaleString(areaEntry->Id, GetSessionDbLocaleIndex(), &areaName);
		}
		

		CharacterDatabase.PQuery("INSERT INTO bounty (`posterGuid`, `posterName`, `targetGuid`, `targetName`, `bountyPrice`, `timePosted`) VALUES (%u, '%s', %u, '%s', %u, CURRENT_TIMESTAMP)", player->GetGUIDLow(), player->GetName(), target->GetGUIDLow(), target->GetName(), price);
		PSendSysMessage("Bounty issued. '%s' will be hunted down by Azeroth's most capable bounty hunters. %ug has been taken as payment.", target->GetName(), price);

		player->ModifyMoney(price * -10000);
		sWorld.SendWorldText(LANG_BOUNTY_POSTED, player->GetName(), price, target->GetName(), areaName.c_str(), zoneName.c_str());

	}
	return true;

}


