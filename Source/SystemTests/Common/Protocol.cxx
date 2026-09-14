#include "Protocol.hxx"

#include <algorithm>
#include <cctype>

namespace universelan::systemtest::common
{
bool token(const std::string_view value)
{
    if (value.empty()) return false;
    return std::all_of(value.begin(), value.end(), [](const unsigned char character)
    {
        return std::isalnum(character) || character == '-' || character == '_' || character == '.';
    });
}

bool appendToken(std::vector<std::string>& values, const std::string& value)
{
    if (!token(value) || std::find(values.begin(), values.end(), value) != values.end()) return false;
    values.push_back(value);
    return true;
}

bool galaxyRealId(const std::string_view value, std::uint64_t& result)
{
    if (value.empty() || !std::all_of(value.begin(), value.end(), [](const unsigned char character) { return std::isdigit(character); })) return false;
    try { result = std::stoull(std::string(value)); }
    catch (...) { return false; }
    return galaxyRealId(result);
}

bool galaxyRealId(const std::uint64_t value)
{
    return value > 0 && value <= 0x00FFFFFFFFFFFFFFULL;
}
}
