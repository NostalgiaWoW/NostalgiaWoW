#pragma once

#include <cstdint>
#include <string>

class ModifyLoyaltyPointsOperation {
    uint32_t m_account_id;
    int32_t m_loyalty_points;
    std::string m_source_id;
    std::string m_source_description;
    uint8_t m_character_level;

    std::string sanitise(std::string source) const;

public:
    ModifyLoyaltyPointsOperation(uint32_t m_account_id, int32_t m_loyalty_points, const std::string& m_source_id,
                                 const std::string& m_source_description, uint8_t m_character_level);

    std::string to_json() const;
};