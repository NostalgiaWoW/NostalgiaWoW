#include <scriptPCH.h>
#include "project_social.h"


int randEmotes[] = { EMOTE_DIZZY, EMOTE_COUGH, EMOTE_SNEEZE };
int randNurseText[] = { -1999503, -1999504, -1999505 };

void infection_Message(Player* sender, int textID, const char* name)
{
    if (!sGameEventMgr.IsActiveEvent(EVENT_VIRUS))
        return;

    if (!name)
    {
        ChatHandler(sender->GetSession()).PSendSysMessage(textID);
        sender->GetSession()->SendNotification(textID);
    }
    else
    {
        ChatHandler(sender->GetSession()).PSendSysMessage(textID, name);
        sender->GetSession()->SendNotification(textID, name);
    }
}

uint32 getInfectChance(Unit* unit)
{
    uint32 chance = CHANCE_BASE_INFECT;

    if (unit->IsPlayer())
        if (Player* player = unit->ToPlayer())
            if (Item* headItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD))
                if (headItem->GetEntry() == ITEM_FACEMASK && !headItem->IsBroken())
                    chance -= CHANCE_FACEMASK_RESIST;

    if (unit->HasAura(SPELL_SANITIZE))
        chance -= CHANCE_SANITIZED_RESIST;

    return chance > 0 ? chance : 0;
}

void infection_CurePlayer(Player* player)
{
    if (!player || !player->IsInWorld())
        return;

    player->RemoveAuraHolderFromStack(SPELL_INFECTION);

    //log to db
    addToDBIfNotExist(player);
    std::ostringstream ss;
    ss << "UPDATE logs_virus_event SET cured='1' WHERE char_name='"
        << player->GetName() << "'"; //char_name
    CharacterDatabase.Execute(ss.str().c_str());
}

void infection_CurePlayerOrNPC(Player* player, Unit* target, bool self)
{
    if (!target)
        return;

    if (!target->HasAura(SPELL_INFECTION) && !target->HasAura(SPELL_INFECTION_NPC))
    {
        infection_Message(player, MESSAGE_ERROR_NOTINFECTED, nullptr);
        return;
    }

    if (!self)
    {
        //log to db
        addToDBIfNotExist(player);
        std::ostringstream ss;
        if (target->IsPlayer())
        {
            ss << "UPDATE logs_virus_event SET cured_player=cured_player+1 WHERE char_name='"
                << player->GetName() << "'"; //char_name

            if (Player* tPlayer = target->ToPlayer())
            {
                infection_CurePlayer(tPlayer);
                infection_Message(player, MESSAGE_YOU_CURED_BY, player->GetName());
            }
        }
        else
        {
            ss << "UPDATE logs_virus_event SET cured_npc=cured_npc+1 WHERE char_name='"
                << player->GetName() << "'"; //char_name

            target->RemoveAuraHolderFromStack(SPELL_INFECTION_NPC);
        }

        infection_Message(player, MESSAGE_CURED_OTHER, target->GetNameForLocaleIdx(player->GetSession()->GetSessionDbLocaleIndex()));

        CharacterDatabase.Execute(ss.str().c_str());
    }

    player->RemoveAuraHolderFromStack(SPELL_INFECTION);

    if (self)
    {
        infection_CurePlayer(player);
        infection_Message(player, MESSAGE_CURED, nullptr);
    }
}


void infection_InfectNpcOrGo(Player* infector, Creature* npc, GameObject* go)
{
    if (npc)
    {
        npc->AddAura(SPELL_INFECTION_NPC);
        //log to db
        addToDBIfNotExist(infector);
        std::ostringstream ss;
        ss << "UPDATE logs_virus_event SET infected_npc=infected_npc+1 WHERE char_name='"
            << infector->GetName() << "'"; //char_name
        CharacterDatabase.Execute(ss.str().c_str());
    }
    else if (go)
    {
        go->SummonCreature(NPC_INFECTION_CLOUD,
            go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), 0.0f,
            TEMPSUMMON_TIMED_DESPAWN, 3600 * IN_MILLISECONDS);
        //log to db
        addToDBIfNotExist(infector);
        std::ostringstream ss;
        ss << "UPDATE logs_virus_event SET infected_go=infected_go+1 WHERE char_name='"
            << infector->GetName() << "'"; //char_name
        CharacterDatabase.Execute(ss.str().c_str());
    }
}

void infection_OnsetPlayer(Player* player, Player* infector)
{
    if (getInfectChance(player) == 0 || !roll_chance_i(getInfectChance(player))
        || player->HasAura(SPELL_ONSET))
        return;

    player->AddAura(SPELL_ONSET);
    infection_Message(player, MESSAGE_WARN_TICKLE, nullptr);

    //log to db
    if (infector)
    {
        addToDBIfNotExist(infector);
        std::ostringstream ss;
        ss << "UPDATE logs_virus_event SET infected_player=infected_player+1 WHERE char_name='"
            << infector->GetName() << "'"; //char_name
        CharacterDatabase.Execute(ss.str().c_str());
    }
}

void infection_InfectPlayer(Player* player)
{
    if (!player || !player->IsInWorld())
        return;

    player->MonsterTextEmote(randEmotes[urand(0, 2)]);
    infection_Message(player, MESSAGE_WARN_INFECTED, nullptr);
    //log to db
    addToDBIfNotExist(player);
    std::ostringstream ss;
    ss << "UPDATE logs_virus_event SET cured='0' WHERE char_name='"
        << player->GetName() << "'"; //char_name
    CharacterDatabase.Execute(ss.str().c_str());
}

void addToDBIfNotExist(Player* player)
{
    QueryResult* result = CharacterDatabase.PQuery(
        "SELECT char_name FROM logs_virus_event WHERE char_name = '%s';", player->GetName());
    
    if (!result)
    {
        std::ostringstream ss;
        ss << "REPLACE INTO logs_virus_event (char_name, infected_player, infected_npc, infected_go,"
            "sanitized_player, sanitized_npc, sanitized_go, cured, cured_npc, cured_player) VALUES ('"
            << player->GetName() << "', " //char_name
            << 0 << ", "                 //infected_player
            << 0 << ", "                 //infected_npc
            << 0 << ", "                 //infected_go
            << 0 << ", "                 //sanitized_player
            << 0 << ", "                 //sanitized_npc
            << 0 << ", "                 //sanitized_go
            << 0 << ", "                 //cured
            << 0 << ", "                 //cured_npc
            << 0 << ");";                //cured_player
        CharacterDatabase.Execute(ss.str().c_str());
    }
}

void infection_SanitizePlayerOrNPC(Player* player, Unit* target, bool self)
{
    if (!target)
        return;

    if (!target->HasAura(SPELL_SANITIZE) && !self)
    {
        //log to db
        addToDBIfNotExist(player);
        std::ostringstream ss;
        if (target->IsPlayer())
            ss << "UPDATE logs_virus_event SET sanitized_player=sanitized_player+1 WHERE char_name='"
            << player->GetName() << "'"; //char_name
        else
            ss << "UPDATE logs_virus_event SET sanitized_npc=sanitized_npc+1 WHERE char_name='"
            << player->GetName() << "'"; //char_name

        CharacterDatabase.Execute(ss.str().c_str());
    }

    target->AddAura(SPELL_SANITIZE);

    if (self)
    {
        // self
        infection_Message(player, MESSAGE_SANITIZED_SELF, nullptr);

        if (player->GetQuestStatus(QUEST_SANITIZE_OWN_A) == QUEST_STATUS_INCOMPLETE)
            player->AreaExploredOrEventHappens(QUEST_SANITIZE_OWN_A);
        if (player->GetQuestStatus(QUEST_SANITIZE_OWN_H) == QUEST_STATUS_INCOMPLETE)
            player->AreaExploredOrEventHappens(QUEST_SANITIZE_OWN_H);
    }
    else
    {
        //another npc
        infection_Message(player, MESSAGE_SANITIZED_OTHER, target->GetNameForLocaleIdx(player->GetSession()->GetSessionDbLocaleIndex()));

        if (player->GetQuestStatus(QUEST_SANITIZE_SOMEONE_A) == QUEST_STATUS_INCOMPLETE)
            player->AreaExploredOrEventHappens(QUEST_SANITIZE_SOMEONE_A);
        if (player->GetQuestStatus(QUEST_SANITIZE_SOMEONE_H) == QUEST_STATUS_INCOMPLETE)
            player->AreaExploredOrEventHappens(QUEST_SANITIZE_SOMEONE_H);
    }
}

void infection_SanitizeSurface(Player* player, Creature* target)
{
    if (!target)
        return;

    if (!target->HasAura(SPELL_SANITIZE) && target->GetEntry() != NPC_INFECTION_CLOUD_QUEST)
    {
        //log to db
        addToDBIfNotExist(player);
        std::ostringstream ss;
        ss << "UPDATE logs_virus_event SET sanitized_go=sanitized_go+1 WHERE char_name='"
            << player->GetName() << "'"; //char_name
        CharacterDatabase.Execute(ss.str().c_str());
    }

    target->AddAura(SPELL_SANITIZE);
    if (target->HasAura(SPELL_CLOUDAURA))
        target->RemoveAuraHolderFromStack(SPELL_CLOUDAURA);

    if (target->HasAura(SPELL_INFECTION_NPC))
        target->RemoveAuraHolderFromStack(SPELL_INFECTION_NPC);
    // game object
    infection_Message(player, MESSAGE_SANITIZED_OBJECT, nullptr);

    if (player->GetQuestStatus(QUEST_SANITIZE_SURFACE_A) == QUEST_STATUS_INCOMPLETE)
        player->AreaExploredOrEventHappens(QUEST_SANITIZE_SURFACE_A);
    if (player->GetQuestStatus(QUEST_SANITIZE_SURFACE_H) == QUEST_STATUS_INCOMPLETE)
        player->AreaExploredOrEventHappens(QUEST_SANITIZE_SURFACE_H);

    if (target->GetEntry() == NPC_INFECTION_CLOUD_QUEST)
    {
        switch (target->GetSubtype())
        {
        case CREATURE_SUBTYPE_GENERIC:
        {
            target->CombatStop();
            if (CreatureData const* data = sObjectMgr.GetCreatureData(target->GetGUIDLow()))
            {
                Creature::AddToRemoveListInMaps(target->GetGUIDLow(), data);
                Creature::DeleteFromDB(target->GetGUIDLow(), data);
            }
            else
                target->AddObjectToRemoveList();
            break;
        }
        case CREATURE_SUBTYPE_TEMPORARY_SUMMON:
            ((TemporarySummon*)target)->UnSummon();
            break;
        default:
            target->ForcedDespawn();
            break;
        }
    }
}

void infection_CleanHandsPlayer(Player* player)
{
    if (player->HasAura(SPELL_ONSET))
        player->RemoveAuraHolderFromStack(SPELL_ONSET);

    player->AddAura(SPELL_CLEAN_HANDS);

    infection_Message(player, MESSAGE_HANDS_WASHED, nullptr);

    if (player->GetQuestStatus(QUEST_WASH_HANDS_A) == QUEST_STATUS_INCOMPLETE)
        player->AreaExploredOrEventHappens(QUEST_WASH_HANDS_A);
    if (player->GetQuestStatus(QUEST_WASH_HANDS_H) == QUEST_STATUS_INCOMPLETE)
        player->AreaExploredOrEventHappens(QUEST_WASH_HANDS_H);
}

void infection_PlayerTouchInfected(Player* player)
{
    if (player->HasAura(SPELL_CLEAN_HANDS))
        player->RemoveAuraHolderFromStack(SPELL_CLEAN_HANDS);
}

void infection_InfectNearestObjects(Unit* infector)
{
    if (!sGameEventMgr.IsActiveEvent(EVENT_VIRUS))
        return;

    if (!infector || (!infector->HasAura(SPELL_INFECTION)
        && !infector->HasAura(SPELL_INFECTION_NPC)))
        return;

    if (infector->IsPlayer())
    {
        Player* player = infector->ToPlayer();
        if (!player || !player->IsInWorld() || !player->isAlive())
            return;

        if (player->InBattleGround() ||
            player->GetMap()->IsDungeon() ||
            player->GetMap()->IsRaid())
            return;
    }

    if (!roll_chance_i(getInfectChance(infector)))
        return;

    infection_OnsetNearestPlayers(infector);

    if (!infector->IsPlayer() || infector->FindNearestCreature(NPC_INFECTION_PROTECT, RADIUS_INFECTION_PROTECT))
        return;

    if (Player* player = infector->ToPlayer())
    {
        std::list<Creature*> creatures;
        infector->GetCreatureListInGrid(creatures, RADIUS_INFECT);

        std::vector<uint32> immuneNPC = { NPC_NURSE , NPC_SUPPLIES_MULE , NPC_MEDICAL_HEALER ,
            NPC_MEDICAL_DISPENSER , NPC_MEDICAL_GUARD1 , NPC_MEDICAL_GUARD2 , NPC_MEDICAL_GUARD3 , NPC_ALERT_BOT ,
            1100014 , 1100015 , 1100016 , 1100017 , 1100018 , 1100019 , 1100020 , NPC_INFECTION_CLOUD_QUEST , NPC_INFECTION_PROTECT };

        for (Creature* creature : creatures)
        {
            if (creature->GetCreatureInfo() && 
                (creature->GetCreatureInfo()->flags_extra & CREATURE_FLAG_EXTRA_INVISIBLE))
                continue;

            if (std::find(immuneNPC.begin(), immuneNPC.end(), creature->GetEntry()) != immuneNPC.end())
                continue;

            if (!roll_chance_i(getInfectChance(creature)) || creature->HasAura(SPELL_INFECTION_NPC))
                continue;

            if (!creature->IsHostileTo(infector))
                infection_InfectNpcOrGo(player, creature, nullptr);
        }

        std::list<GameObject*> gameobjects;
        infector->GetGameObjectListInGrid(gameobjects, RADIUS_INFECT);

        for (GameObject* gameobject : gameobjects)
        {
            if (gameobject->GetEntry() == GO_HANDWASH_STATION)
                continue;

            if (!roll_chance_i(CHANCE_OBJECT_INFECT) || !infector->IsPlayer() ||
                gameobject->FindNearestCreature(NPC_INFECTION_CLOUD, RADIUS_INFECT))
                continue;

            infection_InfectNpcOrGo(player, nullptr, gameobject);
            return;
        }
    }
}

void infection_OnsetNearestPlayers(Unit* infector)
{
    std::list<Player*> targets;
    MaNGOS::AnyPlayerInObjectRangeCheck check(infector, RADIUS_INFECT);
    MaNGOS::PlayerListSearcher<MaNGOS::AnyPlayerInObjectRangeCheck> searcher(targets, check);
    Cell::VisitWorldObjects(infector, searcher, RADIUS_INFECT);
    for (Player* player : targets)
    {
        if (!player->isAlive())
            continue;

        if (player->getLevel() < 11)
            continue;

        if (player->InBattleGround() || player->GetMap()->IsDungeon() || player->GetMap()->IsRaid())
            continue;

        if (infector->IsCreature() && ((Creature*)infector)->GetEntry() == NPC_INFECTION_CLOUD)
            infection_PlayerTouchInfected(player);

        if (player->HasAura(SPELL_INFECTION) || player->HasAura(SPELL_ONSET))
            continue;

        Player* infectorPlayer = infector->IsPlayer() ? infector->ToPlayer() : nullptr;

        infection_OnsetPlayer(player, infectorPlayer);
    }
}

void infection_InfoPlayerOrNPC(Player* player, Unit* target)
{
    if (!target || !target->isAlive() 
        || !player || !player->isAlive())
        return;

    player->PlayerTalkClass->ClearMenus();

    std::string color_red = "|cff620000 ";
    std::string color_green = "|cff005100 ";

    std::string strText = sObjectMgr.GetMangosString(GOSSIP_E_TARGET, player->GetSession()->GetSessionDbLocaleIndex());
    std::string beepText = sObjectMgr.GetMangosString(GOSSIP_E_BEEP, player->GetSession()->GetSessionDbLocaleIndex());
    strText = strText + target->GetNameForLocaleIdx(player->GetSession()->GetSessionDbLocaleIndex()) + "\n " + beepText;;
    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, strText.c_str(), GOSSIP_SENDER_MAIN, 0);

    if (!target->HasAura(SPELL_INFECTION) && !target->HasAura(SPELL_INFECTION_NPC))
    {
        std::string strText = sObjectMgr.GetMangosString(GOSSIP_E_NOT_INFECTED, player->GetSession()->GetSessionDbLocaleIndex());
        strText = color_green + strText + " |r  \n " + beepText;
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, strText.c_str(), GOSSIP_SENDER_MAIN, 0);
    }
    else
    {
        std::string strText = sObjectMgr.GetMangosString(GOSSIP_E_INFECTION_DETECTED, player->GetSession()->GetSessionDbLocaleIndex());
        strText = color_red + strText + " |r  \n " + beepText;
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, strText.c_str(), GOSSIP_SENDER_MAIN, 0);
    }

    if (target->HasAura(SPELL_ONSET))
    {
        std::string strText = sObjectMgr.GetMangosString(GOSSIP_E_BAC_DETECTED, player->GetSession()->GetSessionDbLocaleIndex());
        strText = color_red + strText + " |r  \n " + beepText;
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, strText.c_str(), GOSSIP_SENDER_MAIN, 0);
    }

    if (target->HasAura(SPELL_CLEAN_HANDS))
    {
        std::string strText = sObjectMgr.GetMangosString(GOSSIP_E_CLEAN_HANDS, player->GetSession()->GetSessionDbLocaleIndex());
        strText = color_green + strText + " |r  \n " + beepText;
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, strText.c_str(), GOSSIP_SENDER_MAIN, 0);
    }

    if (target->HasAura(SPELL_SANITIZE))
    {
        std::string strText = sObjectMgr.GetMangosString(GOSSIP_E_SANITIZED, player->GetSession()->GetSessionDbLocaleIndex());
        strText = color_green + strText + " |r  \n " + beepText;
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, strText.c_str(), GOSSIP_SENDER_MAIN, 0);
    }

    if (target->IsPlayer())
        if (Player* player = target->ToPlayer())
            if (Item* headItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD))
                if (headItem->GetEntry() == ITEM_FACEMASK && !headItem->IsBroken())
                {
                    std::string strText = sObjectMgr.GetMangosString(GOSSIP_E_MASK, player->GetSession()->GetSessionDbLocaleIndex());
                    strText = color_green + strText + " |r  \n " + beepText;
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_DOT, strText.c_str(), GOSSIP_SENDER_MAIN, 0);
                }

    player->SEND_GOSSIP_MENU(GOSSIP_TEXT_MAIN, player->GetGUID());

    if (player->GetQuestStatus(QUEST_VIRUS_TESTER_A) == QUEST_STATUS_INCOMPLETE)
        player->AreaExploredOrEventHappens(QUEST_VIRUS_TESTER_A);
    if (player->GetQuestStatus(QUEST_VIRUS_TESTER_H) == QUEST_STATUS_INCOMPLETE)
        player->AreaExploredOrEventHappens(QUEST_VIRUS_TESTER_H);
}

void custom_AuraUpdate(Aura* aura)
{
    if (Unit* target = aura->GetTarget())
    {
        if (target->GetMap()->IsDungeon() ||
            target->GetMap()->IsRaid())
            return;
    }

    switch (aura->GetId())
    {
    case SPELL_INFECTION:
    case SPELL_INFECTION_NPC:
    {
        if (aura->GetTarget() && aura->GetTarget()->isAlive())
        {
            if (!sGameEventMgr.IsActiveEvent(EVENT_VIRUS))
            {
                aura->GetTarget()->RemoveAuraHolderFromStack(aura->GetId());
                return;
            }

            infection_InfectNearestObjects(aura->GetTarget());
        }

        if (roll_chance_i(CHANCE_EMOTE))
            if (aura->GetTarget()->IsCreature() && 
                ((Creature*)aura->GetTarget())->GetEntry() != NPC_INFECTION_CLOUD && 
                ((Creature*)aura->GetTarget())->GetEntry() != NPC_INFECTION_CLOUD_QUEST)
                aura->GetTarget()->MonsterTextEmote(randEmotes[urand(0, 2)]);
            else if (aura->GetTarget()->IsPlayer())
                aura->GetTarget()->MonsterTextEmote(randEmotes[urand(0, 2)]);
        return;
    }
    break;
    }
}

void custom_HandleAuraDummy(Aura* aura, Unit* target, bool apply, AuraRemoveMode m_removeMode)
{
    if (!sGameEventMgr.IsActiveEvent(EVENT_VIRUS))
        return;

    if (!target)
        return;

    if (apply)
    {
        if (aura->GetId() == SPELL_INFECTION)
        {
            if (target->IsPlayer())
                infection_InfectPlayer(((Player*)target));

            return;
        }
    }
    else
    {
        switch (aura->GetId())
        {
        case SPELL_ONSET:
        {
            if (target->IsPlayer() && m_removeMode == AURA_REMOVE_BY_EXPIRE)
                ((Player*)target)->AddAura(SPELL_INFECTION);
            return;
        }
        case SPELL_CLEAN_HANDS:
        {
            if (target->IsPlayer())
                infection_Message(target->ToPlayer(), MESSAGE_HANDS_TIMETOWASH, nullptr);

            return;
        }
        break;
        }
    }
}

struct npc_infection_cloudAI : public ScriptedAI
{
    npc_infection_cloudAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiTimer;

    void Reset()
    {
        m_uiTimer = urand((TIMER_INFECT /2), TIMER_INFECT);
        if (!m_creature->HasAura(SPELL_SANITIZE))
        {
            m_creature->AddAura(SPELL_CLOUDAURA);
            if (m_creature->GetEntry() != NPC_INFECTION_CLOUD_QUEST)
                m_creature->AddAura(SPELL_INFECTION_NPC);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiTimer <= uiDiff)
        {
            if (!m_creature->HasAura(SPELL_SANITIZE))
            {
                if (!m_creature->HasAura(SPELL_CLOUDAURA))
                    m_creature->AddAura(SPELL_CLOUDAURA);

                if (m_creature->GetEntry() != NPC_INFECTION_CLOUD_QUEST
                    && !m_creature->HasAura(SPELL_INFECTION_NPC))
                    m_creature->AddAura(SPELL_INFECTION_NPC);
            }
            else
            {
                if (m_creature->HasAura(SPELL_CLOUDAURA))
                    m_creature->RemoveAuraHolderFromStack(SPELL_CLOUDAURA);

                if (m_creature->HasAura(SPELL_INFECTION_NPC))
                    m_creature->RemoveAuraHolderFromStack(SPELL_INFECTION_NPC);
            }

            m_uiTimer = urand((TIMER_INFECT / 2), TIMER_INFECT);
        }
        else 
            m_uiTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_infection_cloud(Creature* pCreature)
{
    return new npc_infection_cloudAI(pCreature);
}

bool GOHello_handwash_station(Player* player, GameObject* go)
{
    if (!sGameEventMgr.IsActiveEvent(EVENT_VIRUS))
        return true;

    if (Creature* nurse = player->FindNearestCreature(NPC_NURSE, 40, true))
        nurse->MonsterSay(randNurseText[urand(0, 2)]);

    if (player->HasItemCount(ITEM_SOAP, 1))
    {
        infection_CleanHandsPlayer(player);
        return true;
    }
    else
    {
        infection_Message(player, MESSAGE_HANDS_WASHWITHSOAP, nullptr);
        return true;
    }
    return true;
}

bool ITEMUseSpell_hand_sanitizer(Player* player, Item* item, const SpellCastTargets& sct)
{
    if (!sGameEventMgr.IsActiveEvent(EVENT_VIRUS))
        return true;

    if (Unit* target = player->GetMap()->GetUnit(player->GetTargetGuid()))
    {
        if (target->isAlive())
        {
            if (target == player->ToUnit())
                infection_SanitizePlayerOrNPC(player, target, true);
            else if (player->GetDistance2d(target) <= RADIUS_INFECT)
                infection_SanitizePlayerOrNPC(player, target, false);
            else
                player->GetSession()->SendNotification(MESSAGE_TARGET_FAR_AWAY);
        }
    }
    else if (player->isAlive())
       infection_SanitizePlayerOrNPC(player, player, true);

    return true;
}

bool ITEMUseSpell_surface_sanitizer(Player* player, Item* item, const SpellCastTargets& sct)
{
    if (!sGameEventMgr.IsActiveEvent(EVENT_VIRUS))
        return true;

    if (Creature* cloud = player->FindNearestCreature(NPC_INFECTION_CLOUD, RADIUS_INFECT))
    {
        if (!cloud->HasAura(SPELL_SANITIZE))
            infection_SanitizeSurface(player, cloud);
        else
            player->GetSession()->SendNotification(MESSAGE_TARGET_NOT_FOUND);
    }
    else if (Creature* cloud_quest = player->FindNearestCreature(NPC_INFECTION_CLOUD_QUEST, RADIUS_INFECT))
    {
        if (!cloud_quest->HasAura(SPELL_SANITIZE))
            infection_SanitizeSurface(player, cloud_quest);
        else
            player->GetSession()->SendNotification(MESSAGE_TARGET_NOT_FOUND);
    }
    else
        player->GetSession()->SendNotification(MESSAGE_TARGET_NOT_FOUND);

    return true;
}

bool ITEMUse_health_status_checker(Player* player, Item* item, const SpellCastTargets& sct)
{
    if (!sGameEventMgr.IsActiveEvent(EVENT_VIRUS))
        return true;

    if (Unit* target = player->GetMap()->GetUnit(player->GetTargetGuid()))
    {
        if (target->isAlive())
            if (target == player->ToUnit())
                infection_InfoPlayerOrNPC(player, target);
            else if (player->GetDistance2d(target) <= RADIUS_INFECT)
                infection_InfoPlayerOrNPC(player, target);
            else
                player->GetSession()->SendNotification(MESSAGE_TARGET_FAR_AWAY);
    }
    else if (player->isAlive())
        infection_InfoPlayerOrNPC(player, player);

    return true;
}

bool ITEMUse_infection_antivirus(Player* player, Item* item, const SpellCastTargets& sct)
{
    if (!sGameEventMgr.IsActiveEvent(EVENT_VIRUS))
        return true;

    if (Unit* target = player->GetMap()->GetUnit(player->GetTargetGuid()))
    {
        if (target->isAlive())
        {
            if (target == player->ToUnit())
                infection_CurePlayerOrNPC(player, target, true);
            else if (player->GetDistance2d(target) <= RADIUS_INFECT)
                infection_CurePlayerOrNPC(player, target, false);
            else
                player->GetSession()->SendNotification(MESSAGE_TARGET_FAR_AWAY);
        }
    }
    else if (player->isAlive())
        infection_CurePlayerOrNPC(player, player, true);

    return true;
}

bool QuestAccept_virus_event_sanitize(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (!sGameEventMgr.IsActiveEvent(EVENT_VIRUS))
        return true;

    if (pQuest->GetQuestId() == QUEST_SANITIZE_SURFACE_A || 
        pQuest->GetQuestId() == QUEST_SANITIZE_SURFACE_H)
    {
        std::list<Creature*> creatures;
        pPlayer->GetCreatureListWithEntryInGrid(creatures, NPC_INFECTION_CLOUD_QUEST, 30);
        if (creatures.size() < 20)
            if (GameObject* go = pPlayer->FindNearestGameObject(GO_INFECTED_OBJECT, 30))
                go->SummonCreature(NPC_INFECTION_CLOUD_QUEST,
                    go->GetPositionX(), go->GetPositionY(), go->GetPositionZ(), 0.0f,
                    TEMPSUMMON_TIMED_DESPAWN, 60 * IN_MILLISECONDS);
    }
    return true;
}

struct npc_minivirus_petAI : public ScriptedPetAI
{
    npc_minivirus_petAI(Creature* pCreature) : ScriptedPetAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiTimer;

    void Reset() override
    {
        m_uiTimer = urand((TIMER_INFECT / 2), TIMER_INFECT);
    }

    void ResetCreature() override
    {
        m_uiTimer = urand((TIMER_INFECT / 2), TIMER_INFECT);
    }

    void UpdatePetOOCAI(const uint32 uiDiff) override
    {
        if (m_uiTimer <= uiDiff)
        {
            if (roll_chance_i(25))
                m_creature->MonsterTextEmote(EMOTE_SNEEZE);

            m_uiTimer = urand((TIMER_INFECT / 2), TIMER_INFECT);
        }
        else
            m_uiTimer -= uiDiff;
    }
};

CreatureAI* GetAI_minivirus_pet(Creature* pCreature)
{
    return new npc_minivirus_petAI(pCreature);
}

void AddSC_project_social()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "custom_infection_cloud";
    newscript->GetAI = &GetAI_npc_infection_cloud;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_handwash_station";
    newscript->pGOGossipHello = &GOHello_handwash_station;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "item_hand_sanitizer";
    newscript->pItemUseSpell = &ITEMUseSpell_hand_sanitizer;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "item_surface_sanitizer";
    newscript->pItemUseSpell = &ITEMUseSpell_surface_sanitizer;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "item_health_status_checker";
    newscript->pItemUse = &ITEMUse_health_status_checker;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "item_infection_antivirus";
    newscript->pItemUse = &ITEMUse_infection_antivirus;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "custom_minivirus_pet";
    newscript->GetAI = &GetAI_minivirus_pet;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "virus_event_sanitize_quest";
    newscript->pQuestAcceptNPC = &QuestAccept_virus_event_sanitize;
    newscript->RegisterSelf();
}
