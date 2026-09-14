#include <windows.h>

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

namespace universelan::behaviour::game_server_p2p_1002
{
namespace
{
namespace fs = std::filesystem;

struct Arguments
{
    fs::path host;
    fs::path clientDll;
    fs::path server;
};

struct Child
{
    HANDLE process = nullptr;
    bool exited = false;
    int exitCode = -1;
};

bool readArguments(const int argc, char* argv[], Arguments& arguments)
{
    for (int index = 1; index < argc; ++index)
    {
        const std::string option = argv[index];
        if (++index == argc) return false;
        const fs::path value = fs::u8path(argv[index]);
        if (option == "--host") arguments.host = value;
        else if (option == "--client-dll") arguments.clientDll = value;
        else if (option == "--server") arguments.server = value;
        else return false;
    }
    return !arguments.host.empty() && !arguments.clientDll.empty() && !arguments.server.empty();
}

void writeFile(const fs::path& path, const std::string& value)
{
    fs::create_directories(path.parent_path());
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    if (!output) throw std::runtime_error("Unable to create isolated configuration");
    output << value;
}

void writeUniverseLANConfiguration(const fs::path& directory, const char* const profile, const std::uint16_t port)
{
    const bool host = std::string(profile) == "server-host";
    const fs::path data = directory / "UniverseLANData";
    const std::string id = host ? "41001" : "41002";
    const std::string persona = host ? "BehaviourTestServerHost" : "BehaviourTestClient";
    writeFile(directory / "UniverseLAN.ini", "[Storage]\nGameDataPath=" + data.string() + "\nServerDataPath=UniverseLANServerData\n"
        "\n[Authentication]\nKey=UniverseLAN-BehaviourTests-NotASecret\n"
        "\n[Tracing]\nCallTracing=0\nUnhandledExceptionLogging=0\nMiniDumpOnUnhandledException=0\nAlwaysFlush=0\nTraceToConsole=0\n"
        "\n[Networking]\nTimeout=1000\n");
    writeFile(data / "Config.ini", "[Settings]\nEnableConsole=0\n\n[Client]\nServerAddress=127.0.0.1\nPort=" + std::to_string(port)
        + "\n\n[User]\nPersonaNameType=@Custom\nCustomPersonaName=" + persona + "\nGalaxyIDType=@Custom\nCustomGalaxyID=" + id
        + "\nGalaxyIDOffset=0\nSignedIn=1\n");
}

void writeServerConfiguration(const fs::path& directory, const std::uint16_t port)
{
    writeFile(directory / "UniverseLAN.ini", "[Storage]\nGameDataPath=" + (directory / "UniverseLANData").string()
        + "\nServerDataPath=UniverseLANServerData\n\n[Authentication]\nKey=UniverseLAN-BehaviourTests-NotASecret\n"
        "\n[Tracing]\nCallTracing=0\nUnhandledExceptionLogging=0\nMiniDumpOnUnhandledException=0\nAlwaysFlush=0\n");
    writeFile(directory / "UniverseLANServerData" / "Config.ini", "[Server]\nBindAddress=127.0.0.1\nPort=" + std::to_string(port)
        + "\nMaxConnections=8\nMaxTickRate=200\n");
}

std::string quote(const std::string& value)
{
    std::string result = "\"";
    for (const char character : value) result += character == '\"' ? "\\\"" : std::string(1, character);
    return result + "\"";
}

bool startChild(Child& child, const fs::path& executable, const std::vector<std::string>& arguments, const fs::path& directory)
{
    std::string command = quote(executable.string());
    for (const std::string& argument : arguments) command += " " + quote(argument);
    const std::wstring wide = fs::u8path(command).wstring();
    std::vector<wchar_t> writable(wide.begin(), wide.end());
    writable.push_back(L'\0');
    STARTUPINFOW startup{};
    startup.cb = sizeof(startup);
    PROCESS_INFORMATION information{};
    if (!CreateProcessW(executable.c_str(), writable.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, directory.c_str(), &startup, &information)) return false;
    CloseHandle(information.hThread);
    child.process = information.hProcess;
    return true;
}

void update(Child& child)
{
    if (child.process == nullptr || child.exited) return;
    DWORD status = STILL_ACTIVE;
    if (GetExitCodeProcess(child.process, &status) && status != STILL_ACTIVE)
    {
        child.exited = true;
        child.exitCode = static_cast<int>(status);
    }
}

void stop(Child& child)
{
    if (child.process == nullptr) return;
    update(child);
    if (!child.exited)
    {
        TerminateProcess(child.process, 1);
        WaitForSingleObject(child.process, 5000);
        update(child);
    }
    CloseHandle(child.process);
    child.process = nullptr;
}

bool traceHasExactResult(const fs::path& trace)
{
    std::ifstream input(trace, std::ios::binary);
    std::string value((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    return value == "{\"record\":\"direct-game-server-reply\",\"delivery\":true,\"senderType\":\"unclassified-by-sdk-1.100.2\",\"senderEqualsLobbyOwner\":true,\"senderEqualsSelf\":false,\"payloadMatchesPrivateMarker\":true}\n";
}

int run(const Arguments& arguments)
{
    if (!fs::is_regular_file(arguments.host) || !fs::is_regular_file(arguments.clientDll) || !fs::is_regular_file(arguments.server))
    {
        std::cerr << "BEHAVIOUR_TEST UNIVERSELAN scenario=game-server-p2p-sender-identity sdk=1.100.2 "
            "classification=blocked-runtime-artifacts-missing" << std::endl;
        return 1;
    }
    std::mt19937_64 random(std::random_device{}());
    const fs::path root = fs::temp_directory_path() / "universelan-behaviour-tests"
        / ("game-server-p2p-sender-identity-1002-" + std::to_string(random()));
    const std::uint16_t port = static_cast<std::uint16_t>(40000 + random() % 1000);
    Child server;
    Child host;
    Child client;
    try
    {
        const fs::path serverDirectory = root / "server";
        const fs::path hostDirectory = root / "server-host";
        const fs::path clientDirectory = root / "client";
        const fs::path controlDirectory = root / "control";
        fs::create_directories(controlDirectory);
        writeFile(controlDirectory / "control", "token=private-game-server-p2p-marker-" + std::to_string(random()) + "\n");
        writeServerConfiguration(serverDirectory, port);
        writeUniverseLANConfiguration(hostDirectory, "server-host", port);
        writeUniverseLANConfiguration(clientDirectory, "client", port);
        fs::copy_file(arguments.host, hostDirectory / arguments.host.filename(), fs::copy_options::overwrite_existing);
        fs::copy_file(arguments.host, clientDirectory / arguments.host.filename(), fs::copy_options::overwrite_existing);
        fs::copy_file(arguments.clientDll, hostDirectory / arguments.clientDll.filename(), fs::copy_options::overwrite_existing);
        fs::copy_file(arguments.clientDll, clientDirectory / arguments.clientDll.filename(), fs::copy_options::overwrite_existing);
        if (!startChild(server, arguments.server, {}, serverDirectory)) throw std::runtime_error("Unable to start UniverseLAN server");
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        update(server);
        if (server.exited) throw std::runtime_error("UniverseLAN server exited");
        const fs::path stagedHost = hostDirectory / arguments.host.filename();
        const fs::path stagedClient = clientDirectory / arguments.host.filename();
        if (!startChild(host, stagedHost, {"--role", "server-host", "--control", controlDirectory.string(), "--trace",
                (hostDirectory / "trace.jsonl").string(), "--timeout-seconds", "35"}, hostDirectory)) throw std::runtime_error("Unable to start server host");
        if (!startChild(client, stagedClient, {"--role", "client", "--control", controlDirectory.string(), "--trace",
                (clientDirectory / "trace.jsonl").string(), "--timeout-seconds", "35"}, clientDirectory)) throw std::runtime_error("Unable to start client");
        const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(40);
        while (std::chrono::steady_clock::now() < deadline)
        {
            update(host);
            update(client);
            if (host.exited || client.exited) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        update(host);
        update(client);
        const bool success = host.exited && host.exitCode == 0 && client.exited && client.exitCode == 0
            && traceHasExactResult(clientDirectory / "trace.jsonl");
        stop(host);
        stop(client);
        stop(server);
        std::error_code error;
        fs::remove_all(root, error);
        if (!success || error) throw std::runtime_error("UniverseLAN sender relation was not characterized");
        std::cout << "BEHAVIOUR_TEST UNIVERSELAN scenario=game-server-p2p-sender-identity sdk=1.100.2 "
            "classification=characterized delivery=true senderType=unclassified-by-sdk-1.100.2 senderRelation=lobby-owner" << std::endl;
        return 0;
    }
    catch (...)
    {
        stop(host);
        stop(client);
        stop(server);
        std::error_code error;
        fs::remove_all(root, error);
        std::cerr << "BEHAVIOUR_TEST FAIL scenario=game-server-p2p-sender-identity sdk=1.100.2" << std::endl;
        return 1;
    }
}
}
}

int main(int argc, char* argv[])
{
    universelan::behaviour::game_server_p2p_1002::Arguments arguments;
    return universelan::behaviour::game_server_p2p_1002::readArguments(argc, argv, arguments)
        ? universelan::behaviour::game_server_p2p_1002::run(arguments) : 2;
}
