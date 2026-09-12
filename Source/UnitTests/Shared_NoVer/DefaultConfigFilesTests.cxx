#include <DefaultConfigFiles.hxx>

#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace {

std::string read_file(const std::filesystem::path& path)
{
    std::ifstream stream(path);
    return { std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>() };
}

TEST(DefaultConfigFiles, CreatesConfigurationFilesInMissingParentDirectories)
{
    const std::filesystem::path root = std::filesystem::temp_directory_path() / ("UniverseLANConfigTests_" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    const std::filesystem::path boot = root / "nested" / "UniverseLAN.ini";
    const std::filesystem::path client = root / "nested" / "client.ini";
    const std::filesystem::path server = root / "nested" / "server.ini";

    universelan::defaults::create_boot_file(boot);
    universelan::defaults::create_client_config_file(client);
    universelan::defaults::create_server_config_file(server);

    EXPECT_NE(read_file(boot).find("GameDataPath = UniverseLANData"), std::string::npos);
    EXPECT_NE(read_file(client).find("ServerAddress = 127.0.0.1"), std::string::npos);
    EXPECT_NE(read_file(server).find("MaxConnections = 1024"), std::string::npos);

    std::error_code error;
    std::filesystem::remove_all(root, error);
}

} // namespace
