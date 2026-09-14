#include "Runner.hxx"

#include <chrono>
#include <fstream>
#include <stdexcept>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace universelan::systemtest::runner
{
namespace
{
void writeRootConfig(const fs::path& directory, const fs::path& gameDataPath)
{
    writeFile(directory / "UniverseLAN.ini",
        "[Storage]\nGameDataPath=" + gameDataPath.string() + "\nServerDataPath=UniverseLANServerData\n"
        "\n[Authentication]\nKey=UniverseLAN-SystemTests-NotASecret\n"
        "\n[Tracing]\nCallTracing=0\nUnhandledExceptionLogging=0\nMiniDumpOnUnhandledException=0\nAlwaysFlush=0\nTraceToConsole=0\n"
        "\n[Networking]\nTimeout=1000\n");
}

bool portAvailable(const unsigned short port, const int socketType)
{
#ifdef _WIN32
    WSADATA data{};
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) return false;
    const SOCKET socketHandle = socket(AF_INET, socketType, socketType == SOCK_DGRAM ? IPPROTO_UDP : IPPROTO_TCP);
    if (socketHandle == INVALID_SOCKET) { WSACleanup(); return false; }
#else
    const int socketHandle = socket(AF_INET, socketType, 0);
    if (socketHandle < 0) return false;
#endif
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    const bool available = bind(socketHandle, reinterpret_cast<const sockaddr*>(&address), sizeof(address)) == 0;
#ifdef _WIN32
    closesocket(socketHandle);
    WSACleanup();
#else
    close(socketHandle);
#endif
    return available;
}
}

void writeFile(const fs::path& path, const std::string& contents)
{
    std::ofstream output(path, std::ios::binary);
    if (!output) throw std::runtime_error("Unable to create isolated test configuration");
    output << contents;
}

void writeHostFiles(const fs::path& directory, const Host& host, const unsigned short port)
{
    const fs::path gameDataPath = host.persistenceGroup.empty()
        ? directory / "UniverseLANData" : directory.parent_path() / "persistence" / host.persistenceGroup;
    fs::create_directories(gameDataPath);
    writeRootConfig(directory, gameDataPath);
    std::string appsConfiguration;
    const bool saveUnknownDlcIds = host.hasAppsConfiguration ? host.appsSaveUnknownDlcIds : false;
    if (host.hasAppsConfiguration)
    {
        appsConfiguration = "Language=" + host.appsLanguage + "\nLanguageCode=" + host.appsLanguageCode
            + "\nEnableAllDLC=" + std::to_string(host.appsEnableAllDlc)
            + "\n";
        std::string dlcConfiguration = "[DLC]\n";
        for (const auto& [productId, installed] : host.appsDlc)
            dlcConfiguration += std::to_string(productId) + "=" + std::to_string(installed) + "\n";
        writeFile(gameDataPath / "DLC.ini", dlcConfiguration);
    }
    const std::string telemetryConfiguration = host.hasTelemetryConfiguration
        ? "\n[Telemetry]\nStore=" + std::to_string(host.telemetryStore) + "\n" : "";
    writeFile(gameDataPath / "Config.ini",
        "[Settings]\nEnableConsole=0\nSaveUnknownDLCIDs=" + std::to_string(saveUnknownDlcIds) + "\nSaveAchievementsAndStats=" + std::to_string(host.saveAchievementsAndStats) + "\n" + appsConfiguration + "\n[Client]\nServerAddress=127.0.0.1\n"
        "Port=" + std::to_string(port) + "\n\n[User]\nPersonaNameType=@Custom\n"
        "CustomPersonaName=" + host.personaName + "\nGalaxyIDType=@Custom\nCustomGalaxyID=" + std::to_string(host.userId)
         + "\nGalaxyIDOffset=0\nSignedIn=1\nAutoAcceptGameInvitations=1\n\n[Storage]\nAllowFileSharingDownload=1\nAllowFileSharingUpload=1\n" + telemetryConfiguration);
    if (host.scenario == "stats-achievement-user-data-propagation-writer")
    {
        writeFile(gameDataPath / "Achievements.ini",
            "[universelan-system-stats-achievement-user-data-achievement-v1]\nDescription=System test achievement\nUnlocked=0\nUnlockTime=0\nVisible=1\nVisibleWhileLocked=1\n");
    }
    if (host.scenario == "stats-achievement-durable-persistence-writer")
    {
        writeFile(gameDataPath / "Achievements.ini",
            "[universelan-system-stats-achievement-durable-persistence-achievement-v1]\nDescription=System test durable persistence achievement\nUnlocked=0\nUnlockTime=0\nVisible=1\nVisibleWhileLocked=1\n");
    }
    writeFile(directory / "role.json", "{\"role\":\"" + host.role + "\",\"scenario\":\"" + host.scenario + "\",\"userId\":" + std::to_string(host.userId) + "}");
}

void writeServerFiles(const fs::path& directory, const Scenario& scenario, const unsigned short port)
{
    fs::create_directories(directory / "UniverseLANServerData");
    writeRootConfig(directory, directory / "UniverseLANData");
    writeFile(directory / "UniverseLANServerData" / "Config.ini", "[Storage]\nAllowFileSharingDownload="
        + std::to_string(scenario.serverAllowFileSharingDownload) + "\nAllowFileSharingUpload="
        + std::to_string(scenario.serverAllowFileSharingUpload) + "\n\n[Server]\nBindAddress=127.0.0.1\nPort=" + std::to_string(port)
        + "\nMaxConnections=" + std::to_string(scenario.serverMaxConnections) + "\nMaxTickRate=" + std::to_string(scenario.serverMaxTickRate) + "\n");
}

unsigned short selectPort(const Scenario& scenario, const Arguments& arguments)
{
    std::uint32_t hash = 2166136261u;
    for (const unsigned char character : scenario.name + arguments.version) { hash ^= character; hash *= 16777619u; }
    const unsigned short first = static_cast<unsigned short>(37000 + (hash % 1000));
    for (unsigned int attempt = 0; attempt < 1000; ++attempt)
    {
        const unsigned short candidate = static_cast<unsigned short>(37000 + ((first - 37000 + attempt) % 1000));
        if (portAvailable(candidate, SOCK_DGRAM)) return candidate;
    }
    throw std::runtime_error("No available system-test UDP port");
}

unsigned short selectWebSocketPort(const Scenario& scenario, const Arguments& arguments, const unsigned short excludedPort)
{
    std::uint32_t hash = 2166136261u;
    for (const unsigned char character : scenario.name + arguments.version + "websocket") { hash ^= character; hash *= 16777619u; }
    const unsigned short first = static_cast<unsigned short>(39000 + (hash % 1000));
    for (unsigned int attempt = 0; attempt < 1000; ++attempt)
    {
        const unsigned short candidate = static_cast<unsigned short>(39000 + ((first - 39000 + attempt) % 1000));
        if (candidate != excludedPort && portAvailable(candidate, SOCK_STREAM)) return candidate;
    }
    throw std::runtime_error("No available system-test TCP port");
}

std::string lobbyToken(const Scenario& scenario)
{
    std::uint64_t hash = 1469598103934665603ULL;
    const std::string input = scenario.name + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    for (const unsigned char character : input) { hash ^= character; hash *= 1099511628211ULL; }
    return "systemtest-" + std::to_string(hash);
}

bool serverListening(const std::string& line) { return line.find("Listening...") != std::string::npos; }

fs::path stageHost(const fs::path& directory, const Arguments& arguments, const fs::path& runtime)
{
    const fs::path isolatedHost = directory / arguments.host.filename();
    const fs::path isolatedRuntime = directory / runtime.filename();
    std::error_code error;
    fs::copy_file(arguments.host, isolatedHost, fs::copy_options::overwrite_existing, error);
    if (error) throw std::runtime_error("Unable to stage isolated host executable");
    fs::copy_file(runtime, isolatedRuntime, fs::copy_options::overwrite_existing, error);
    if (error) throw std::runtime_error("Unable to stage selected runtime DLL");
    return isolatedHost;
}

fs::path gogRuntime(const Arguments& arguments)
{
    fs::path runtime = arguments.gogRuntimeDirectory / arguments.runtimeName;
    if (!fs::is_regular_file(runtime)) return {};
#ifdef _WIN32
    runtime.replace_extension(".lib");
    if (!fs::is_regular_file(runtime)) return {};
    runtime.replace_extension(".dll");
#endif
    return runtime;
}
}
