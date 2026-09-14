#pragma once

#include <cstdint>
#include <filesystem>
#include <utility>
#include <set>
#include <string>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <sys/types.h>
#endif

namespace universelan::systemtest::runner
{
namespace fs = std::filesystem;

struct Host
{
    std::string role;
    std::string scenario;
    std::uint64_t userId = 0;
    std::string personaName;
    std::string credentialProfile;
    std::string persistenceGroup;
    bool saveAchievementsAndStats = false;
    std::vector<std::string> waitFor;
    std::vector<std::string> signals;
    std::vector<std::string> actionAfter;
    std::vector<std::string> finishAfter;
    std::vector<std::uint64_t> peerUserIds;
    bool hasAppsConfiguration = false;
    std::string appsLanguage;
    std::string appsLanguageCode;
    bool appsEnableAllDlc = true;
    bool appsSaveUnknownDlcIds = true;
    std::vector<std::pair<std::uint64_t, bool>> appsDlc;
    bool hasTelemetryConfiguration = false;
    bool telemetryStore = false;
    int timeoutSeconds = 0;
};

struct Scenario
{
    std::string name;
    std::string provider;
    int timeoutSeconds = 0;
    bool serverEnabled = false;
    std::string serverReadyEvent;
    int serverMaxConnections = 8;
    int serverMaxTickRate = 200;
    bool serverAllowFileSharingDownload = true;
    bool serverAllowFileSharingUpload = true;
    bool webSocketEnabled = false;
    std::string webSocketReadyEvent;
    std::vector<Host> hosts;
};

struct Arguments
{
    fs::path manifest;
    fs::path host;
    fs::path clientDll;
    fs::path server;
    fs::path gogRuntimeDirectory;
    std::string runtimeName;
    std::string version;
    std::string arch;
};

struct Child
{
    std::string role;
    fs::path log;
    std::uintmax_t logOffset = 0;
    std::string pendingLog;
    bool sawPass = false;
    bool started = false;
    bool exited = false;
    int exitCode = 0;
#ifdef _WIN32
    HANDLE process = nullptr;
#else
    pid_t process = -1;
#endif
};

Scenario parseScenario(const fs::path& manifest);
bool readArguments(int argc, char* argv[], Arguments& arguments);

void writeFile(const fs::path& path, const std::string& contents);
void writeHostFiles(const fs::path& directory, const Host& host, unsigned short port);
void writeServerFiles(const fs::path& directory, const Scenario& scenario, unsigned short port);
unsigned short selectPort(const Scenario& scenario, const Arguments& arguments);
unsigned short selectWebSocketPort(const Scenario& scenario, const Arguments& arguments, unsigned short excludedPort);
std::string lobbyToken(const Scenario& scenario);
bool serverListening(const std::string& line);
fs::path stageHost(const fs::path& directory, const Arguments& arguments, const fs::path& runtime);
fs::path gogRuntime(const Arguments& arguments);

bool startChild(Child& child, const fs::path& executable, const std::vector<std::string>& arguments, const fs::path& workingDirectory);
void updateChild(Child& child);
void stopChild(Child& child);
std::vector<std::string> readLines(Child& child);
bool handleLine(const std::string& line, const Host& host, Child& child, std::set<std::string>& events);

bool eventsReady(const std::vector<std::string>& dependencies, const std::set<std::string>& events);
bool dependenciesReady(const Host& host, const std::set<std::string>& events);
int run(const Arguments& arguments, const Scenario& scenario);
}
