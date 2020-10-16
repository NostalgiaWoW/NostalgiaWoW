#include <sstream>
#include <string>

#include <Chat.h>
#include <LoyaltyPoints/LoyaltyPointsMgr.h>

#include "Player.h"

using std::ostringstream;
using std::string;

bool ChatHandler::HandleLoyaltyPointsAddCommand(char* args) {
    const auto player = getSelectedPlayer();
    if (!player) {
        return false;
    }

    const uint32_t account_id = player->GetSession()->GetAccountId();
    const string source_id = "gm_command";
    const string source = "GM Command";

    int32_t amount;
    if (!ChatHandler::ExtractInt32(&args, amount)) {
        return false;
    }

    const auto& lpMgr = LoyaltyPointsMgr::instance();
    lpMgr->add_loyalty_points(account_id, amount, source_id, source, player->getLevel());
    lpMgr->commit_changes();

    const auto query_result = LoginDatabase.PQuery("SELECT username FROM account WHERE id = %u", account_id);
    const auto field = query_result->Fetch();
    if (field == nullptr) {
        // We're done at this point anyway, forget the message.
        return true;
    }

    const auto account_name = field[0].GetString();

    ostringstream ss;
    ss << "Added " << amount << " loyalty point(s) to account " << account_name << " (ID: " << account_id << ").";

    SendSysMessage(ss.str().c_str());
    return true;
}