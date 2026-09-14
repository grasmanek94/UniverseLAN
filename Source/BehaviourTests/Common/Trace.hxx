#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace universelan::behaviour::common
{
std::string jsonString(const std::string& value);
void writeTrace(const std::filesystem::path& path, const std::vector<std::string>& records);
std::vector<std::string> readTrace(const std::filesystem::path& path);
}
