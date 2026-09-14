#include "Common/Trace.hxx"

#include <fstream>
#include <stdexcept>

namespace universelan::behaviour::common
{
std::string jsonString(const std::string& value)
{
    std::string result;
    result.reserve(value.size() + 2);
    result += '"';
    for (const unsigned char character : value)
    {
        if (character == '"' || character == '\\') { result += '\\'; result += static_cast<char>(character); }
        else if (character == '\n') result += "\\n";
        else if (character == '\r') result += "\\r";
        else if (character == '\t') result += "\\t";
        else if (character < 0x20) result += "?";
        else result += static_cast<char>(character);
    }
    result += '"';
    return result;
}

void writeTrace(const std::filesystem::path& path, const std::vector<std::string>& records)
{
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    if (!output) throw std::runtime_error("Unable to create behaviour trace");
    for (const std::string& record : records) output << record << '\n';
}

std::vector<std::string> readTrace(const std::filesystem::path& path)
{
    std::ifstream input(path, std::ios::binary);
    std::vector<std::string> result;
    std::string line;
    while (std::getline(input, line)) if (!line.empty()) result.push_back(line);
    return result;
}
}
