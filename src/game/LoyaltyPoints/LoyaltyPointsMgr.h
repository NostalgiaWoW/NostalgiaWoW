#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include <LoyaltyPoints/ModifyLoyaltyPointsOperation.h>

class LoyaltyPointsMgr {
    static std::unique_ptr<LoyaltyPointsMgr> s_instance;
public:
    static LoyaltyPointsMgr* instance();

private:
    std::vector<std::unique_ptr<ModifyLoyaltyPointsOperation>> m_operations;
    std::mutex m_mutex;
public:
    LoyaltyPointsMgr();

    void commit_changes();

    void add_loyalty_points(uint32_t account_id, int amount, std::string source_id, std::string source, uint8_t character_level);
};
