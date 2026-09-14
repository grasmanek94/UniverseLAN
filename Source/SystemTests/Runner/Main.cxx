#include "Runner.hxx"

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocketServer.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>

namespace universelan::systemtest::runner
{
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

namespace
{
bool persistenceReady(const Scenario& scenario, const std::size_t index, const std::vector<Child>& children)
{
    const std::string& group = scenario.hosts[index].persistenceGroup;
    if (group.empty()) return true;
    for (std::size_t previous = 0; previous < index; ++previous)
    {
        if (scenario.hosts[previous].persistenceGroup != group) continue;
        const Child& child = children[previous];
        if (!child.started || !child.sawPass || !child.exited || child.exitCode != 0) return false;
    }
    return true;
}
}

int run(const Arguments& arguments, const Scenario& scenario)
{
    if (arguments.version != UNIVERSELAN_SYSTEM_TEST_VERSION || arguments.arch != UNIVERSELAN_SYSTEM_TEST_ARCH)
        throw std::runtime_error("Selected version does not match this runner target");
    fs::path runtime = arguments.clientDll;
    if (scenario.provider == "gog")
    {
        runtime = gogRuntime(arguments);
        if (runtime.empty()) { std::cout << "SYSTEM_TEST SKIP reason=GogRuntimeMissing" << std::endl; return 0; }
    }
    if (!fs::is_regular_file(arguments.host) || !fs::is_regular_file(runtime) || (scenario.serverEnabled && !fs::is_regular_file(arguments.server)))
        throw std::runtime_error("Selected version target path is unavailable");

    const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
    const fs::path root = fs::temp_directory_path() / "universelan-system-tests" / (scenario.name + "-" + std::to_string(stamp));
    fs::create_directories(root / "control");
    const unsigned short port = selectPort(scenario, arguments);
    const unsigned short webSocketPort = scenario.webSocketEnabled ? selectWebSocketPort(scenario, arguments, port) : 0;
    const std::string uniqueLobbyToken = lobbyToken(scenario);
    std::set<std::string> events;
    Child server;
    std::vector<Child> children(scenario.hosts.size());
    std::vector<fs::path> hostExecutables(scenario.hosts.size());
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
            webSocket->setOnClientMessageCallback([](std::shared_ptr<ix::ConnectionState>, ix::WebSocket& client, const ix::WebSocketMessagePtr& message)
            {
                if (message->type == ix::WebSocketMessageType::Message && message->binary) client.sendBinary(message->str);
            });
            const auto [listening, error] = webSocket->listen();
            if (!listening) throw std::runtime_error("Unable to listen on system-test WebSocket port: " + error);
            webSocket->start();
            events.insert(scenario.webSocketReadyEvent);
        }
        for (std::size_t index = 0; index < scenario.hosts.size(); ++index)
        {
            const Host& host = scenario.hosts[index];
            const fs::path directory = root / host.role;
            fs::create_directories(directory);
            writeHostFiles(directory, host, port);
            hostExecutables[index] = stageHost(directory, arguments, runtime);
            children[index].role = host.role;
            children[index].log = directory / "stdout.log";
        }
        const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(scenario.timeoutSeconds);
        while (std::chrono::steady_clock::now() < deadline)
        {
            if (scenario.serverEnabled)
            {
                for (const std::string& line : readLines(server)) if (serverListening(line)) events.insert(scenario.serverReadyEvent);
                updateChild(server);
                if (server.exited) throw std::runtime_error("Server exited before scenario completion");
            }
            for (std::size_t index = 0; index < children.size(); ++index)
            {
                const Host& host = scenario.hosts[index];
                Child& child = children[index];
                const fs::path directory = root / host.role;
                if (!child.started && dependenciesReady(host, events) && persistenceReady(scenario, index, children))
                {
                    std::vector<std::string> childArguments = {"--role", host.role, "--scenario", host.scenario, "--control-dir", (root / "control").string(),
                        "--timeout-seconds", std::to_string(host.timeoutSeconds), "--version", arguments.version, "--arch", arguments.arch, "--runtime-provider", scenario.provider,
                        "--lobby-token", uniqueLobbyToken};
                    if (scenario.webSocketEnabled)
                    {
                        childArguments.push_back("--websocket-url");
                        childArguments.push_back("ws://127.0.0.1:" + std::to_string(webSocketPort) + "/echo");
                    }
                    for (const std::uint64_t peerUserId : host.peerUserIds) { childArguments.push_back("--peer-user-id"); childArguments.push_back(std::to_string(peerUserId)); }
                    if (!host.credentialProfile.empty()) { childArguments.push_back("--credential-profile"); childArguments.push_back(host.credentialProfile); }
                    for (const std::string& signal : host.signals) { childArguments.push_back("--signal"); childArguments.push_back(signal); }
                    for (const std::string& event : host.finishAfter) { childArguments.push_back("--finish-after"); childArguments.push_back(event); }
                    if (!startChild(child, hostExecutables[index], childArguments, directory)) throw std::runtime_error("Unable to start selected host target");
                    child.started = true;
                }
                if (!child.started) continue;
                if (dependenciesReady(host, events)) writeFile(root / "control" / (host.role + ".release"), "release\n");
                for (const std::string& line : readLines(child)) if (!handleLine(line, host, child, events)) throw std::runtime_error("Invalid child protocol");
                updateChild(child);
                if (child.exited && (!child.sawPass || child.exitCode != 0)) throw std::runtime_error("Host exited without a successful protocol result (exit " + std::to_string(child.exitCode) + ")");
            }
            for (const Host& host : scenario.hosts)
                if (!host.finishAfter.empty() && eventsReady(host.finishAfter, events) && !fs::exists(root / "control" / (host.role + ".complete")))
                    writeFile(root / "control" / (host.role + ".complete"), "complete\n");
            for (const Host& host : scenario.hosts)
                if (!host.actionAfter.empty() && eventsReady(host.actionAfter, events) && !fs::exists(root / "control" / (host.role + ".action")))
                    writeFile(root / "control" / (host.role + ".action"), "action\n");
            bool complete = true;
            for (std::size_t index = 0; index < children.size(); ++index)
            {
                complete = complete && children[index].started && children[index].sawPass && children[index].exited && children[index].exitCode == 0;
                for (const std::string& signal : scenario.hosts[index].signals) complete = complete && events.contains(signal);
            }
            if (complete) { success = true; break; }
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
        std::cerr << "SYSTEM_TEST FAIL reason=RunnerFailure detail=" << error.what() << " runDirectory=" << root.string() << std::endl;
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
        std::cerr << "SYSTEM_TEST FAIL reason=CleanupFailure detail=" << cleanupError.message() << " runDirectory=" << root.string() << std::endl;
        return 1;
    }
    std::cout << "SYSTEM_TEST PASS scenario=" << scenario.name << std::endl;
    return 0;
}
}

int main(int argc, char* argv[])
{
    using namespace universelan::systemtest::runner;

    Arguments arguments;
    if (!readArguments(argc, argv, arguments))
    {
        std::cerr << "SYSTEM_TEST FAIL reason=InvalidArguments" << std::endl;
        return 2;
    }
    try { return run(arguments, parseScenario(arguments.manifest)); }
    catch (...) { std::cerr << "SYSTEM_TEST FAIL reason=ManifestOrSetupFailure" << std::endl; return 1; }
}
