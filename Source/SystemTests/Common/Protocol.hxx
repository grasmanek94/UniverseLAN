#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace universelan::systemtest::common
{
inline constexpr std::string_view eventPrefix = "SYSTEM_TEST EVENT name=";
inline constexpr std::string_view passPrefix = "SYSTEM_TEST PASS role=";
inline constexpr std::string_view failPrefix = "SYSTEM_TEST FAIL role=";

bool token(std::string_view value);
bool appendToken(std::vector<std::string>& values, const std::string& value);
bool galaxyRealId(std::string_view value, std::uint64_t& result);
bool galaxyRealId(std::uint64_t value);
}
