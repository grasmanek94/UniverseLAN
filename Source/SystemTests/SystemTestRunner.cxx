#include <nlohmann/json.hpp>

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocketServer.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace
{
struct Host
{
    std::string role;
    std::string scenario;
    std::uint64_t userId = 0;
    std::string personaName;
    std::string credentialProfile;
    std::vector<std::string> waitFor;
    std::vector<std::string> signals;
    std::vector<std::string> actionAfter;
    std::vector<std::string> finishAfter;
    std::vector<std::uint64_t> peerUserIds;
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
    bool exited = false;
    int exitCode = 0;
#ifdef _WIN32
    HANDLE process = nullptr;
#else
    pid_t process = -1;
#endif
};

[[noreturn]] void invalidManifest()
{
    throw std::runtime_error("Manifest validation failed");
}

bool token(const std::string& value)
{
    if (value.empty()) return false;
    for (const unsigned char character : value)
        if (!(std::isalnum(character) || character == '-' || character == '_' || character == '.')) return false;
    return true;
}

bool galaxyRealId(std::uint64_t value)
{
    return value > 0 && value <= 0x00FFFFFFFFFFFFFFULL;
}

void objectHasOnly(const json& value, std::initializer_list<const char*> allowed)
{
    if (!value.is_object()) invalidManifest();
    for (const auto& [key, ignored] : value.items())
    {
        bool known = false;
        for (const char* name : allowed) known = known || key == name;
        if (!known) invalidManifest();
    }
}

const json& required(const json& value, const char* name)
{
    if (!value.contains(name)) invalidManifest();
    return value.at(name);
}

std::string requiredToken(const json& value, const char* name)
{
    const json& field = required(value, name);
    if (!field.is_string() || !token(field.get<std::string>())) invalidManifest();
    return field.get<std::string>();
}

int requiredTimeout(const json& value, const char* name)
{
    const json& field = required(value, name);
    if (!field.is_number_integer()) invalidManifest();
    const int timeout = field.get<int>();
    if (timeout < 1 || timeout > 600) invalidManifest();
    return timeout;
}

std::vector<std::string> tokenArray(const json& value)
{
    if (!value.is_array()) invalidManifest();
    std::vector<std::string> result;
    for (const json& item : value)
    {
        if (!item.is_string() || !token(item.get<std::string>())) invalidManifest();
        result.push_back(item.get<std::string>());
    }
    return result;
}

Scenario parseScenario(const fs::path& manifest)
{
    std::ifstream input(manifest);
    if (!input) invalidManifest();
    json root;
    try { input >> root; }
    catch (...) { invalidManifest(); }

    objectHasOnly(root, {"name", "runtimeProvider", "timeoutSeconds", "server", "websocket", "hosts"});
    Scenario result;
    result.name = requiredToken(root, "name");
    result.provider = requiredToken(root, "runtimeProvider");
    if (result.provider != "universelan" && result.provider != "gog") invalidManifest();
    result.timeoutSeconds = requiredTimeout(root, "timeoutSeconds");

    if (root.contains("server"))
    {
        const json& server = root.at("server");
        objectHasOnly(server, {"enabled", "readyEvent", "configuration"});
        if (!required(server, "enabled").is_boolean()) invalidManifest();
        result.serverEnabled = server.at("enabled").get<bool>();
        if (result.serverEnabled) result.serverReadyEvent = requiredToken(server, "readyEvent");
        if (server.contains("configuration"))
        {
            const json& configuration = server.at("configuration");
            objectHasOnly(configuration, {"maxConnections", "tickRate"});
            for (const auto& [key, setting] : configuration.items())
            {
                if (!setting.is_number_integer() || setting.get<int>() < 1) invalidManifest();
                if (key == "maxConnections") result.serverMaxConnections = setting.get<int>();
                if (key == "tickRate") result.serverMaxTickRate = setting.get<int>();
            }
        }
    }
    if (result.provider == "gog" && result.serverEnabled) invalidManifest();
    if (root.contains("websocket"))
    {
        const json& webSocket = root.at("websocket");
        objectHasOnly(webSocket, {"enabled", "readyEvent"});
        if (!required(webSocket, "enabled").is_boolean()) invalidManifest();
        result.webSocketEnabled = webSocket.at("enabled").get<bool>();
        if (result.webSocketEnabled) result.webSocketReadyEvent = requiredToken(webSocket, "readyEvent");
    }

    const json& hosts = required(root, "hosts");
    if (!hosts.is_array() || hosts.empty()) invalidManifest();
    std::set<std::string> roles;
    std::set<std::uint64_t> identities;
    std::set<std::string> declaredEvents;
    if (result.serverEnabled) declaredEvents.insert(result.serverReadyEvent);
    if (result.webSocketEnabled && !declaredEvents.insert(result.webSocketReadyEvent).second) invalidManifest();
    for (const json& entry : hosts)
    {
        objectHasOnly(entry, {"role", "scenario", "identity", "waitFor", "signals", "actionAfter", "finishAfter", "peerUserIds", "timeoutSeconds"});
        Host host;
        host.role = requiredToken(entry, "role");
        host.scenario = requiredToken(entry, "scenario");
        host.timeoutSeconds = requiredTimeout(entry, "timeoutSeconds");
        if (!roles.insert(host.role).second) invalidManifest();
        const json& identity = required(entry, "identity");
        objectHasOnly(identity, {"userId", "personaName", "credentialProfile"});
        const json& userId = required(identity, "userId");
        if (!userId.is_number_unsigned() || !galaxyRealId(userId.get<std::uint64_t>())) invalidManifest();
        host.userId = userId.get<std::uint64_t>();
        if (!identities.insert(host.userId).second) invalidManifest();
        if (identity.contains("personaName")) host.personaName = requiredToken(identity, "personaName");
        if (identity.contains("credentialProfile"))
        {
            host.credentialProfile = requiredToken(identity, "credentialProfile");
            if (host.credentialProfile != "user1" && host.credentialProfile != "user2") invalidManifest();
        }
        if (entry.contains("waitFor")) host.waitFor = tokenArray(entry.at("waitFor"));
        if (entry.contains("signals")) host.signals = tokenArray(entry.at("signals"));
        if (entry.contains("actionAfter")) host.actionAfter = tokenArray(entry.at("actionAfter"));
        if (entry.contains("finishAfter")) host.finishAfter = tokenArray(entry.at("finishAfter"));
        if (entry.contains("peerUserIds"))
        {
            const json& peerUserIds = entry.at("peerUserIds");
            if (!peerUserIds.is_array()) invalidManifest();
            std::set<std::uint64_t> uniquePeerIds;
            for (const json& peerUserId : peerUserIds)
            {
                if (!peerUserId.is_number_unsigned() || !galaxyRealId(peerUserId.get<std::uint64_t>())) invalidManifest();
                const std::uint64_t value = peerUserId.get<std::uint64_t>();
                if (!uniquePeerIds.insert(value).second || value == host.userId) invalidManifest();
                host.peerUserIds.push_back(value);
            }
        }
        for (const std::string& signal : host.signals)
            if (!declaredEvents.insert(signal).second) invalidManifest();
        result.hosts.push_back(std::move(host));
    }
    for (const Host& host : result.hosts)
    {
        std::set<std::string> uniqueDependencies;
        for (const std::string& dependency : host.waitFor)
            if (!declaredEvents.contains(dependency) || !uniqueDependencies.insert(dependency).second) invalidManifest();
        uniqueDependencies.clear();
        for (const std::string& dependency : host.actionAfter)
            if (!declaredEvents.contains(dependency) || !uniqueDependencies.insert(dependency).second) invalidManifest();
        uniqueDependencies.clear();
        for (const std::string& dependency : host.finishAfter)
            if (!declaredEvents.contains(dependency) || !uniqueDependencies.insert(dependency).second) invalidManifest();
        for (const std::uint64_t peerUserId : host.peerUserIds)
            if (!identities.contains(peerUserId)) invalidManifest();
    }
    return result;
}

bool readArguments(int argc, char* argv[], Arguments& arguments)
{
    for (int index = 1; index < argc; ++index)
    {
        const std::string option = argv[index];
        if (++index == argc) return false;
        const std::string value = argv[index];
        if (option == "--manifest") arguments.manifest = fs::u8path(value);
        else if (option == "--host") arguments.host = fs::u8path(value);
        else if (option == "--client-dll") arguments.clientDll = fs::u8path(value);
        else if (option == "--server") arguments.server = fs::u8path(value);
        else if (option == "--gog-runtime-dir") arguments.gogRuntimeDirectory = fs::u8path(value);
        else if (option == "--runtime-name") arguments.runtimeName = value;
        else if (option == "--version") arguments.version = value;
        else if (option == "--arch") arguments.arch = value;
        else return false;
    }
    return !arguments.manifest.empty() && !arguments.host.empty() && !arguments.clientDll.empty()
        && !arguments.server.empty() && !arguments.gogRuntimeDirectory.empty() && token(arguments.runtimeName)
        && token(arguments.version) && (arguments.arch == "x86" || arguments.arch == "x64");
}

void writeFile(const fs::path& path, const std::string& contents)
{
    std::ofstream output(path, std::ios::binary);
    if (!output) throw std::runtime_error("Unable to create isolated test configuration");
    output << contents;
}

void writeRootConfig(const fs::path& directory)
{
    writeFile(directory / "UniverseLAN.ini",
        "[Storage]\n"
        "GameDataPath=UniverseLANData\n"
        "ServerDataPath=UniverseLANServerData\n"
        "\n[Authentication]\n"
        "Key=UniverseLAN-SystemTests-NotASecret\n"
        "\n[Tracing]\n"
        "CallTracing=0\n"
        "UnhandledExceptionLogging=0\n"
        "MiniDumpOnUnhandledException=0\n"
        "AlwaysFlush=0\n"
        "TraceToConsole=0\n"
        "\n[Networking]\n"
        "Timeout=1000\n");
}

void writeHostFiles(const fs::path& directory, const Host& host, unsigned short port)
{
    fs::create_directories(directory / "UniverseLANData");
    writeRootConfig(directory);
    writeFile(directory / "UniverseLANData" / "Config.ini",
        "[Settings]\n"
        "EnableConsole=0\n"
        "SaveUnknownDLCIDs=0\n"
        "SaveAchievementsAndStats=0\n"
        "\n"
        "[Client]\n"
        "ServerAddress=127.0.0.1\n"
        "Port=" + std::to_string(port) + "\n"
        "\n[User]\n"
        "PersonaNameType=@Custom\n"
        "CustomPersonaName=" + host.personaName + "\n"
        "GalaxyIDType=@Custom\n"
        "CustomGalaxyID=" + std::to_string(host.userId) + "\n"
        "GalaxyIDOffset=0\n"
        "SignedIn=1\n");
    writeFile(directory / "role.json", "{\"role\":\"" + host.role + "\",\"scenario\":\"" + host.scenario
        + "\",\"userId\":" + std::to_string(host.userId) + "}");
}

void writeServerFiles(const fs::path& directory, const Scenario& scenario, unsigned short port)
{
    fs::create_directories(directory / "UniverseLANServerData");
    writeRootConfig(directory);
    writeFile(directory / "UniverseLANServerData" / "Config.ini",
        "[Server]\n"
        "BindAddress=127.0.0.1\n"
        "Port=" + std::to_string(port) + "\n"
        "MaxConnections=" + std::to_string(scenario.serverMaxConnections) + "\n"
        "MaxTickRate=" + std::to_string(scenario.serverMaxTickRate) + "\n");
}

std::string quoteWindows(const std::string& value)
{
    std::string result = "\"";
    for (const char character : value)
    {
        if (character == '\"') result += "\\\"";
        else result += character;
    }
    return result + "\"";
}

bool startChild(Child& child, const fs::path& executable, const std::vector<std::string>& arguments, const fs::path& workingDirectory)
{
#ifdef _WIN32
    HANDLE log = CreateFileW(child.log.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (log == INVALID_HANDLE_VALUE) return false;
    if (!SetHandleInformation(log, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT))
    {
        CloseHandle(log);
        return false;
    }
    std::string command = quoteWindows(executable.string());
    for (const std::string& argument : arguments) command += " " + quoteWindows(argument);
    std::wstring commandLine = fs::u8path(command).wstring();
    std::vector<wchar_t> writable(commandLine.begin(), commandLine.end());
    writable.push_back(L'\0');
    STARTUPINFOW startup{};
    startup.cb = sizeof(startup);
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startup.hStdOutput = log;
    startup.hStdError = log;
    PROCESS_INFORMATION information{};
    const BOOL started = CreateProcessW(executable.c_str(), writable.data(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW, nullptr,
        workingDirectory.c_str(), &startup, &information);
    CloseHandle(log);
    if (!started) return false;
    CloseHandle(information.hThread);
    child.process = information.hProcess;
    return true;
#else
    const int log = open(child.log.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (log < 0) return false;
    child.process = fork();
    if (child.process == 0)
    {
        dup2(log, STDOUT_FILENO);
        dup2(log, STDERR_FILENO);
        close(log);
        if (chdir(workingDirectory.c_str()) != 0) _exit(127);
        std::vector<char*> command;
        command.push_back(const_cast<char*>(executable.c_str()));
        for (const std::string& argument : arguments) command.push_back(const_cast<char*>(argument.c_str()));
        command.push_back(nullptr);
        execv(executable.c_str(), command.data());
        _exit(127);
    }
    close(log);
    return child.process > 0;
#endif
}

void updateChild(Child& child)
{
    if (child.exited) return;
#ifdef _WIN32
    DWORD status = STILL_ACTIVE;
    if (GetExitCodeProcess(child.process, &status) && status != STILL_ACTIVE)
    {
        child.exited = true;
        child.exitCode = static_cast<int>(status);
    }
#else
    int status = 0;
    const pid_t result = waitpid(child.process, &status, WNOHANG);
    if (result == child.process)
    {
        child.exited = true;
        child.exitCode = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    }
#endif
}

void stopChild(Child& child)
{
    if (child.process ==
#ifdef _WIN32
        nullptr
#else
        -1
#endif
    ) return;
    updateChild(child);
    if (!child.exited)
    {
#ifdef _WIN32
        TerminateProcess(child.process, 1);
        WaitForSingleObject(child.process, 5000);
        updateChild(child);
#else
        kill(child.process, SIGTERM);
        const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        while (std::chrono::steady_clock::now() < deadline)
        {
            updateChild(child);
            if (child.exited) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        if (!child.exited)
        {
            kill(child.process, SIGKILL);
            const auto forceDeadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
            while (std::chrono::steady_clock::now() < forceDeadline)
            {
                updateChild(child);
                if (child.exited) break;
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
        }
#endif
    }
#ifdef _WIN32
    CloseHandle(child.process);
    child.process = nullptr;
#else
    child.process = -1;
#endif
}

std::vector<std::string> readLines(Child& child)
{
    std::error_code error;
    const std::uintmax_t size = fs::file_size(child.log, error);
    if (error || size <= child.logOffset) return {};
    std::ifstream input(child.log, std::ios::binary);
    if (!input) return {};
    input.seekg(static_cast<std::streamoff>(child.logOffset));
    std::string bytes(static_cast<std::size_t>(size - child.logOffset), '\0');
    input.read(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    bytes.resize(static_cast<std::size_t>(input.gcount()));
    child.logOffset += bytes.size();
    child.pendingLog += bytes;
    std::vector<std::string> lines;
    std::size_t newline = 0;
    while ((newline = child.pendingLog.find('\n')) != std::string::npos)
    {
        std::string line = child.pendingLog.substr(0, newline);
        child.pendingLog.erase(0, newline + 1);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(line);
    }
    return lines;
}

bool eventsReady(const std::vector<std::string>& dependencies, const std::set<std::string>& events)
{
    for (const std::string& dependency : dependencies)
        if (!events.contains(dependency)) return false;
    return true;
}

bool dependenciesReady(const Host& host, const std::set<std::string>& events)
{
    return eventsReady(host.waitFor, events);
}

bool portAvailable(unsigned short port, int socketType)
{
#ifdef _WIN32
    WSADATA data{};
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) return false;
    const SOCKET socketHandle = socket(AF_INET, socketType, socketType == SOCK_DGRAM ? IPPROTO_UDP : IPPROTO_TCP);
    if (socketHandle == INVALID_SOCKET)
    {
        WSACleanup();
        return false;
    }
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

unsigned short selectPort(const Scenario& scenario, const Arguments& arguments)
{
    std::uint32_t hash = 2166136261u;
    for (const unsigned char character : scenario.name + arguments.version)
    {
        hash ^= character;
        hash *= 16777619u;
    }
    const unsigned short first = static_cast<unsigned short>(37000 + (hash % 1000));
    for (unsigned int attempt = 0; attempt < 1000; ++attempt)
    {
        const unsigned short candidate = static_cast<unsigned short>(37000 + ((first - 37000 + attempt) % 1000));
        if (portAvailable(candidate, SOCK_DGRAM)) return candidate;
    }
    throw std::runtime_error("No available system-test UDP port");
}

unsigned short selectWebSocketPort(const Scenario& scenario, const Arguments& arguments, unsigned short excludedPort)
{
    std::uint32_t hash = 2166136261u;
    for (const unsigned char character : scenario.name + arguments.version + "websocket")
    {
        hash ^= character;
        hash *= 16777619u;
    }
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
    for (const unsigned char character : input)
    {
        hash ^= character;
        hash *= 1099511628211ULL;
    }
    return "systemtest-" + std::to_string(hash);
}

bool serverListening(const std::string& line)
{
    return line.find("Listening...") != std::string::npos;
}

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

bool handleLine(const std::string& line, const Host& host, Child& child, std::set<std::string>& events)
{
    const std::string eventPrefix = "SYSTEM_TEST EVENT name=";
    const std::string passPrefix = "SYSTEM_TEST PASS role=";
    const std::string failPrefix = "SYSTEM_TEST FAIL role=";
    if (line.rfind("SYSTEM_TEST ", 0) != 0) return true;
    if (line.rfind(eventPrefix, 0) == 0)
    {
        const std::string event = line.substr(eventPrefix.size());
        if (!token(event) || !std::count(host.signals.begin(), host.signals.end(), event)) return false;
        return events.insert(event).second;
    }
    if (line == passPrefix + host.role && !child.sawPass)
    {
        child.sawPass = true;
        return true;
    }
    if (line.rfind(failPrefix, 0) == 0) return false;
    return false;
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

int run(const Arguments& arguments, const Scenario& scenario)
{
    if (arguments.version != UNIVERSELAN_SYSTEM_TEST_VERSION || arguments.arch != UNIVERSELAN_SYSTEM_TEST_ARCH)
        throw std::runtime_error("Selected version does not match this runner target");
    fs::path runtime = arguments.clientDll;
    if (scenario.provider == "gog")
    {
        runtime = gogRuntime(arguments);
        if (runtime.empty())
        {
            std::cout << "SYSTEM_TEST SKIP reason=GogRuntimeMissing" << std::endl;
            return 0;
        }
    }
    if (!fs::is_regular_file(arguments.host) || !fs::is_regular_file(runtime)
        || (scenario.serverEnabled && !fs::is_regular_file(arguments.server)))
        throw std::runtime_error("Selected version target path is unavailable");

    const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
    const fs::path root = fs::temp_directory_path() / "universelan-system-tests" / (scenario.name + "-" + std::to_string(stamp));
    fs::create_directories(root / "control");
    const unsigned short port = selectPort(scenario, arguments);
    const unsigned short webSocketPort = scenario.webSocketEnabled ? selectWebSocketPort(scenario, arguments, port) : 0;
    const std::string uniqueLobbyToken = lobbyToken(scenario);
    std::set<std::string> events;
    Child server;
    std::vector<Child> children;
    bool webSocketNetSystemInitialized = false;
    std::unique_ptr<ix::WebSocketServer> webSocket;
    bool success = false;
    try
    {
        if (scenario.serverEnabled)
        {
            const fs::path directory = root / "server";
            writeServerFiles(directory, scenario, port);
            server.role = "server";
            server.log = directory / "stdout.log";
            if (!startChild(server, arguments.server, {}, directory)) throw std::runtime_error("Unable to start selected server target");
        }
        if (scenario.webSocketEnabled)
        {
            if (!ix::initNetSystem()) throw std::runtime_error("Unable to initialize WebSocket networking");
            webSocketNetSystemInitialized = true;
            webSocket = std::make_unique<ix::WebSocketServer>(webSocketPort, "127.0.0.1");
            webSocket->disablePerMessageDeflate();
            webSocket->setOnClientMessageCallback([](std::shared_ptr<ix::ConnectionState>, ix::WebSocket& client,
                const ix::WebSocketMessagePtr& message)
            {
                if (message->type == ix::WebSocketMessageType::Message && message->binary) client.sendBinary(message->str);
            });
            const auto [listening, error] = webSocket->listen();
            if (!listening) throw std::runtime_error("Unable to listen on system-test WebSocket port: " + error);
            webSocket->start();
            events.insert(scenario.webSocketReadyEvent);
        }
        for (const Host& host : scenario.hosts)
        {
            const fs::path directory = root / host.role;
            fs::create_directories(directory);
            writeHostFiles(directory, host, port);
            const fs::path isolatedHost = stageHost(directory, arguments, runtime);
            Child child;
            child.role = host.role;
            child.log = directory / "stdout.log";
            std::vector<std::string> childArguments = {"--role", host.role, "--scenario", host.scenario,
                "--control-dir", (root / "control").string(), "--timeout-seconds", std::to_string(host.timeoutSeconds), "--version", arguments.version,
                "--arch", arguments.arch, "--runtime-provider", scenario.provider, "--lobby-token", uniqueLobbyToken};
            if (scenario.webSocketEnabled)
            {
                childArguments.push_back("--websocket-url");
                childArguments.push_back("ws://127.0.0.1:" + std::to_string(webSocketPort) + "/echo");
            }
            for (const std::uint64_t peerUserId : host.peerUserIds)
            {
                childArguments.push_back("--peer-user-id");
                childArguments.push_back(std::to_string(peerUserId));
            }
            if (!host.credentialProfile.empty())
            {
                childArguments.push_back("--credential-profile");
                childArguments.push_back(host.credentialProfile);
            }
            for (const std::string& signal : host.signals)
            {
                childArguments.push_back("--signal");
                childArguments.push_back(signal);
            }
            for (const std::string& event : host.finishAfter)
            {
                childArguments.push_back("--finish-after");
                childArguments.push_back(event);
            }
            if (!startChild(child, isolatedHost, childArguments, directory)) throw std::runtime_error("Unable to start selected host target");
            children.push_back(std::move(child));
        }

        const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(scenario.timeoutSeconds);
        while (std::chrono::steady_clock::now() < deadline)
        {
            if (scenario.serverEnabled)
            {
                for (const std::string& line : readLines(server))
                    if (serverListening(line)) events.insert(scenario.serverReadyEvent);
                updateChild(server);
                if (server.exited) throw std::runtime_error("Server exited before scenario completion");
            }
            for (std::size_t index = 0; index < children.size(); ++index)
            {
                const Host& host = scenario.hosts[index];
                Child& child = children[index];
                if (dependenciesReady(host, events)) writeFile(root / "control" / (host.role + ".release"), "release\n");
                for (const std::string& line : readLines(child))
                    if (!handleLine(line, host, child, events)) throw std::runtime_error("Invalid child protocol");
                updateChild(child);
                if (child.exited && (!child.sawPass || child.exitCode != 0))
                    throw std::runtime_error("Host exited without a successful protocol result (exit " + std::to_string(child.exitCode) + ")");
            }
            for (const Host& host : scenario.hosts)
                if (!host.finishAfter.empty() && eventsReady(host.finishAfter, events)
                    && !fs::exists(root / "control" / (host.role + ".complete")))
                    writeFile(root / "control" / (host.role + ".complete"), "complete\n");
            for (const Host& host : scenario.hosts)
                if (!host.actionAfter.empty() && eventsReady(host.actionAfter, events)
                    && !fs::exists(root / "control" / (host.role + ".action")))
                    writeFile(root / "control" / (host.role + ".action"), "action\n");
            bool complete = true;
            for (std::size_t index = 0; index < children.size(); ++index)
            {
                complete = complete && children[index].sawPass;
                for (const std::string& signal : scenario.hosts[index].signals)
                    complete = complete && events.contains(signal);
            }
            if (complete)
            {
                success = true;
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        if (!success) throw std::runtime_error("Scenario deadline expired");
    }
    catch (const std::exception& error)
    {
        for (Child& child : children) stopChild(child);
        stopChild(server);
        if (webSocket) webSocket->stop();
        if (webSocketNetSystemInitialized) ix::uninitNetSystem();
        std::cerr << "SYSTEM_TEST FAIL reason=RunnerFailure detail=" << error.what()
            << " runDirectory=" << root.string() << std::endl;
        return 1;
    }
    for (Child& child : children) stopChild(child);
    stopChild(server);
    if (webSocket) webSocket->stop();
    if (webSocketNetSystemInitialized) ix::uninitNetSystem();
    std::error_code cleanupError;
    for (int attempt = 0; attempt < 500; ++attempt)
    {
        cleanupError.clear();
        fs::remove_all(root, cleanupError);
        if (!cleanupError) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    if (cleanupError)
    {
        std::cerr << "SYSTEM_TEST FAIL reason=CleanupFailure detail=" << cleanupError.message()
            << " runDirectory=" << root.string() << std::endl;
        return 1;
    }
    std::cout << "SYSTEM_TEST PASS scenario=" << scenario.name << std::endl;
    return 0;
}
}

int main(int argc, char* argv[])
{
    Arguments arguments;
    if (!readArguments(argc, argv, arguments))
    {
        std::cerr << "SYSTEM_TEST FAIL reason=InvalidArguments" << std::endl;
        return 2;
    }
    try
    {
        const Scenario scenario = parseScenario(arguments.manifest);
        return run(arguments, scenario);
    }
    catch (...)
    {
        std::cerr << "SYSTEM_TEST FAIL reason=ManifestOrSetupFailure" << std::endl;
        return 1;
    }
}
