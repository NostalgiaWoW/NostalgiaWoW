#include "LoyaltyPointsMgr.h"
#include "Database/DatabaseEnv.h"

using std::make_unique;
using std::move;
using std::mutex;
using std::lock_guard;
using std::string;
using std::unique_ptr;
using std::vector;

unique_ptr<LoyaltyPointsMgr> LoyaltyPointsMgr::s_instance = nullptr;

LoyaltyPointsMgr* LoyaltyPointsMgr::instance() {
    if (s_instance == nullptr) {
        s_instance = make_unique<LoyaltyPointsMgr>();
    }

    return s_instance.get();
}

void LoyaltyPointsMgr::commit_changes() {
    m_mutex.lock();
    vector<unique_ptr<ModifyLoyaltyPointsOperation>> operations;
    operations.reserve(m_operations.size());
    for (auto& operation : m_operations) {
        operations.push_back(move(operation));
    }
    m_operations.clear();
    m_mutex.unlock();

    for (auto& operation : operations) {
        const auto data = string(operation->to_json());
        LoginDatabase.PExecute("INSERT INTO `agent_queue` (`opcode`, `data`) VALUES ('loyalty_points', '%s')",
                               data.c_str());
    }
}

void LoyaltyPointsMgr::add_loyalty_points(uint32_t account_id, int amount, string source_id, string source,
                                          uint8_t character_level) {
    lock_guard<mutex> lock(m_mutex);

    m_operations.push_back(
            make_unique<ModifyLoyaltyPointsOperation>(account_id, amount, source_id, source, character_level)
    );
}

LoyaltyPointsMgr::LoyaltyPointsMgr() : m_operations(), m_mutex() {}
