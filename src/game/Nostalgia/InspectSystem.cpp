#include "InspectSystem.h"



void InspectSystem::BlockInspect(Player* target, Player* source)
{
    SendModifiedPackets(target, source);
}

void InspectSystem::SendModifiedPackets(Player* target, Player* source)
{
    for (uint32 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
    {
        WorldPacket packet(SMSG_ITEM_QUERY_SINGLE_RESPONSE, 1000);
        Item* item = target->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (item)
        {
            FillItemPacket(item, packet);
            source->GetSession()->SendPacket(&packet);
        }
    }
}

void InspectSystem::FillItemPacket(Item* item, WorldPacket& packet)
{
    auto pProto = sObjectMgr.GetItemPrototype(926);//item->GetProto();
    auto& data = packet;

    std::string Name = pProto->Name1;
    std::string Description = pProto->Description;

    data << item->GetProto()->ItemId;
    data << pProto->Class;
    // client known only 0 subclass (and 1-2 obsolute subclasses)
    data << (pProto->Class == ITEM_CLASS_CONSUMABLE ? uint32(0) : pProto->SubClass);
    data << Name;                                       // max length of any of 4 names: 256 bytes
    data << uint8(0x00);                                //pProto->Name2; // blizz not send name there, just uint8(0x00); <-- \0 = empty string = empty name...
    data << uint8(0x00);                                //pProto->Name3; // blizz not send name there, just uint8(0x00);
    data << uint8(0x00);                                //pProto->Name4; // blizz not send name there, just uint8(0x00);
    data << pProto->DisplayInfoID;
    data << pProto->Quality;
    data << pProto->Flags;
    data << pProto->BuyPrice;
    data << pProto->SellPrice;
    data << pProto->InventoryType;
    data << pProto->AllowableClass;
    data << pProto->AllowableRace;
    data << pProto->ItemLevel;
    data << pProto->RequiredLevel;
    data << pProto->RequiredSkill;
    data << pProto->RequiredSkillRank;
    data << pProto->RequiredSpell;
    // Item de style insigne
    if (pProto->Spells[0].SpellId != 0)
        data << uint32(0);
    else
        data << pProto->RequiredHonorRank;

    data << pProto->RequiredCityRank;
    data << pProto->RequiredReputationFaction;
    data << (pProto->RequiredReputationFaction > 0 ? pProto->RequiredReputationRank : 0);   // send value only if reputation faction id setted ( needed for some items)
    data << pProto->MaxCount;
    data << pProto->Stackable;
    data << pProto->ContainerSlots;
    for (int i = 0; i < MAX_ITEM_PROTO_STATS; ++i)
    {
        data << pProto->ItemStat[i].ItemStatType;
        data << pProto->ItemStat[i].ItemStatValue;
    }
    for (int i = 0; i < MAX_ITEM_PROTO_DAMAGES; ++i)
    {
        data << pProto->Damage[i].DamageMin;
        data << pProto->Damage[i].DamageMax;
        data << pProto->Damage[i].DamageType;
    }

    // resistances (7)
    data << pProto->Armor;
    data << pProto->HolyRes;
    data << pProto->FireRes;
    data << pProto->NatureRes;
    data << pProto->FrostRes;
    data << pProto->ShadowRes;
    data << pProto->ArcaneRes;

    data << pProto->Delay;
    data << pProto->AmmoType;
    data << (float)pProto->RangedModRange;

    for (int s = 0; s < MAX_ITEM_PROTO_SPELLS; ++s)
    {
        // send DBC data for cooldowns in same way as it used in Spell::SendSpellCooldown
        // use `item_template` or if not set then only use spell cooldowns
        SpellEntry const* spell = sSpellMgr.GetSpellEntry(pProto->Spells[s].SpellId);
        if (spell)
        {
            bool db_data = pProto->Spells[s].SpellCooldown >= 0 || pProto->Spells[s].SpellCategoryCooldown >= 0;

            data << pProto->Spells[s].SpellId;
            data << pProto->Spells[s].SpellTrigger;

            // let the database control the sign here.  negative means that the item should be consumed once the charges are consumed.
            data << pProto->Spells[s].SpellCharges;

            if (db_data)
            {
                data << uint32(pProto->Spells[s].SpellCooldown);
                data << uint32(pProto->Spells[s].SpellCategory);
                data << uint32(pProto->Spells[s].SpellCategoryCooldown);
            }
            else
            {
                data << uint32(spell->RecoveryTime);
                data << uint32(spell->Category);
                data << uint32(spell->CategoryRecoveryTime);
            }
        }
        else
        {
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(-1);
            data << uint32(0);
            data << uint32(-1);
        }
    }
    data << pProto->Bonding;
    data << Description;
    data << pProto->PageText;
    data << pProto->LanguageID;
    data << pProto->PageMaterial;
    data << pProto->StartQuest;
    data << pProto->LockID;
    data << pProto->Material;
    data << pProto->Sheath;
    data << pProto->RandomProperty;
    data << pProto->Block;
    data << pProto->ItemSet;
    data << pProto->MaxDurability;
    data << pProto->Area;
    data << pProto->Map;                                // Added in 1.12.x & 2.0.1 client branch
    data << pProto->BagFamily;
}