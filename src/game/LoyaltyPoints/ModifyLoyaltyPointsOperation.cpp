#include <cstdint>
#include <sstream>

#include "ModifyLoyaltyPointsOperation.h"

using std::string;
using std::ostringstream;

string ModifyLoyaltyPointsOperation::to_json() const {
    ostringstream ss;
    ss << "{"
       << "\"account_id\": " << m_account_id << ", "
       << "\"loyalty_points\": " << m_loyalty_points << ", "
       << "\"source_id\": \"" << sanitise(m_source_id) << "\", "
       << "\"source_description\": " << "\"" << sanitise(m_source_description) << "\", "
       << "\"character_level\": " << uint32_t(m_character_level)
       << "}";
    const auto json = ss.str();
    return json;
}

string ModifyLoyaltyPointsOperation::sanitise(string source) const {
    auto copy = string(source);
    const string search = "\"";
    const string replacement = "\\\"";

    for (size_t idx = 0; true; idx += replacement.length()) {
        idx = copy.find(search, idx);
        if (idx == string::npos) {
            break;
        }

        copy.erase(idx, search.length());
        copy.insert(idx, replacement);
    }

    return copy;
}

ModifyLoyaltyPointsOperation::ModifyLoyaltyPointsOperation(uint32_t m_account_id, int32_t m_loyalty_points,
                                                           const std::string& m_source_id,
                                                           const std::string& m_source_description,
                                                           uint8_t m_character_level)
        : m_account_id(m_account_id),
          m_loyalty_points(m_loyalty_points),
          m_character_level(m_character_level),
          m_source_id(m_source_id),
          m_source_description(m_source_description) {}
