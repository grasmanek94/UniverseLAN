#include "BehaviourTestCredentials.hxx"

#include <galaxy/GalaxyApi.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <thread>

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY && GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING && GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
namespace universelan::behaviour::game_server_p2p
{
namespace
{
struct Arguments
{
    std::string role;
    std::filesystem::path control;
    std::filesystem::path trace;
    int timeoutSeconds = 0;
};

bool readArguments(const int argc, char* argv[], Arguments& arguments)
{
    for (int index = 1; index < argc; ++index)
    {
        const std::string option = argv[index];
        if (++index == argc) return false;
        const std::string value = argv[index];
        if (option == "--role") arguments.role = value;
        else if (option == "--control") arguments.control = std::filesystem::u8path(value);
        else if (option == "--trace") arguments.trace = std::filesystem::u8path(value);
        else if (option == "--timeout-seconds")
        {
            try { arguments.timeoutSeconds = std::stoi(value); }
            catch (...) { return false; }
        }
        else return false;
    }
    return (arguments.role == "server-host" || arguments.role == "client") && !arguments.control.empty()
        && !arguments.trace.empty() && arguments.timeoutSeconds > 0 && arguments.timeoutSeconds <= 60;
}

void writeTrace(const std::filesystem::path& path, const std::string& record)
{
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    if (output) output << record << '\n';
}

void writeEvent(const Arguments& arguments, const char* const event)
{
    std::ofstream output(arguments.control / "event", std::ios::binary | std::ios::app);
    if (output) output << event << '\n';
}

bool hasEvent(const Arguments& arguments, const char* const expected)
{
    std::ifstream input(arguments.control / "event", std::ios::binary);
    std::string event;
    while (std::getline(input, event)) if (event == expected) return true;
    return false;
}

std::string controlValue(const Arguments& arguments, const char* const name)
{
    std::ifstream input(arguments.control / "control", std::ios::binary);
    const std::string prefix = std::string(name) + "=";
    std::string line;
    while (std::getline(input, line)) if (line.rfind(prefix, 0) == 0) return line.substr(prefix.size());
    return {};
}

template <typename Predicate>
bool pumpUntil(galaxy::api::IGalaxy* const galaxy, const std::chrono::steady_clock::time_point deadline, Predicate&& predicate)
{
    while (std::chrono::steady_clock::now() < deadline)
    {
        galaxy->ProcessData();
        if (predicate()) return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return predicate();
}

struct AuthListener final : galaxy::api::GlobalAuthListener
{
    bool completed = false;
    bool success = false;

    void OnAuthSuccess() override { completed = true; success = true; }
    void OnAuthFailure(const FailureReason) override { completed = true; }
    void OnAuthLost() override {}
};

struct LobbyCreatedListener final : galaxy::api::GlobalLobbyCreatedListener
{
    bool completed = false;
    bool success = false;
    galaxy::api::GalaxyID lobby;

    void OnLobbyCreated(const galaxy::api::GalaxyID& id, const galaxy::api::LobbyCreateResult result) override
    {
        completed = true;
        success = result == galaxy::api::LOBBY_CREATE_RESULT_SUCCESS;
        lobby = id;
    }
};

struct LobbyEnteredListener final : galaxy::api::GlobalLobbyEnteredListener
{
    bool completed = false;
    bool success = false;
    galaxy::api::GalaxyID lobby;

    void OnLobbyEntered(const galaxy::api::GalaxyID& id, const galaxy::api::LobbyEnterResult result) override
    {
        completed = true;
        success = result == galaxy::api::LOBBY_ENTER_RESULT_SUCCESS;
        lobby = id;
    }
};

struct LobbyListListener final : galaxy::api::GlobalLobbyListListener
{
    galaxy::api::IMatchmaking* matchmaking = nullptr;
    bool completed = false;
    bool ioFailure = true;
    galaxy::api::GalaxyID selected;

    void OnLobbyList(const std::uint32_t count, const bool failed) override
    {
        completed = true;
        ioFailure = failed;
        if (!failed && count == 1) selected = matchmaking->GetLobbyByIndex(0);
    }
};

struct LobbyLeftListener final : galaxy::api::GlobalLobbyLeftListener
{
    galaxy::api::GalaxyID expected;
    bool completed = false;
    bool ioFailure = true;

    void OnLobbyLeft(const galaxy::api::GalaxyID& lobby, const bool failed) override
    {
        if (lobby == expected)
        {
            completed = true;
            ioFailure = failed;
        }
    }
};

bool leaveLobby(galaxy::api::IGalaxy* const galaxy, galaxy::api::IMatchmaking* const matchmaking,
    const galaxy::api::GalaxyID& lobby, const std::chrono::steady_clock::time_point deadline)
{
    LobbyLeftListener left;
    left.expected = lobby;
    matchmaking->LeaveLobby(lobby);
    return pumpUntil(galaxy, deadline, [&] { return left.completed; }) && !left.ioFailure;
}

int runServerHost(const Arguments& arguments, galaxy::api::IGalaxy* const galaxy, const std::chrono::steady_clock::time_point deadline)
{
    galaxy::api::IMatchmaking* const matchmaking = galaxy->GetMatchmaking();
    galaxy::api::INetworking* const serverNetworking = galaxy->GetServerNetworking();
    const std::string token = controlValue(arguments, "token");
    LobbyCreatedListener created;
    LobbyEnteredListener entered;
    if (matchmaking == nullptr || serverNetworking == nullptr || token.empty()) return 1;

#if GALAXY_BUILD_FEATURE_HAS_LOBBYTOPOLOGYTYPE_ENUM
    matchmaking->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 2, false, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM);
#else
    matchmaking->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 2);
#endif
    if (!pumpUntil(galaxy, deadline, [&] { return created.completed && entered.completed; }) || !created.success || !entered.success
        || !created.lobby.IsValid() || created.lobby != entered.lobby) return 1;

    const galaxy::api::GalaxyID lobby = created.lobby;
    const bool configured = matchmaking->SetLobbyData(lobby, "universelan-behaviour-token", token.c_str())
        && matchmaking->SetLobbyJoinable(lobby, true);
    if (!configured) return 1;
    writeEvent(arguments, "server-host-ready");
    if (!pumpUntil(galaxy, deadline, [&] { return hasEvent(arguments, "client-joined"); })) return 1;

    const galaxy::api::GalaxyID owner = matchmaking->GetLobbyOwner(lobby);
    galaxy::api::GalaxyID client;
    const std::uint32_t members = matchmaking->GetNumLobbyMembers(lobby);
    for (std::uint32_t index = 0; index < members; ++index)
    {
        const galaxy::api::GalaxyID member = matchmaking->GetLobbyMemberByIndex(lobby, index);
        if (member != owner) client = member;
    }
    constexpr std::array<std::uint8_t, 4> payload{{0x47, 0x53, 0x31, 0x02}};
    constexpr std::uint8_t channel = 61;
    const bool scheduled = client.IsValid() && serverNetworking->SendP2PPacket(client, payload.data(), static_cast<std::uint32_t>(payload.size()),
        galaxy::api::P2P_SEND_RELIABLE, channel);
    writeEvent(arguments, "server-host-reply-scheduled");
    if (!scheduled || !pumpUntil(galaxy, deadline, [&] { return hasEvent(arguments, "client-observed-reply"); })) return 1;
    const bool left = leaveLobby(galaxy, matchmaking, lobby, deadline);
    writeEvent(arguments, "server-host-finished");
    return left ? 0 : 1;
}

int runClient(const Arguments& arguments, galaxy::api::IGalaxy* const galaxy, const std::chrono::steady_clock::time_point deadline)
{
    galaxy::api::IMatchmaking* const matchmaking = galaxy->GetMatchmaking();
    galaxy::api::INetworking* const networking = galaxy->GetNetworking();
    const std::string token = controlValue(arguments, "token");
    if (matchmaking == nullptr || networking == nullptr || token.empty()) return 1;
    if (!pumpUntil(galaxy, deadline, [&] { return hasEvent(arguments, "server-host-ready"); })) return 1;

    LobbyListListener listed;
    listed.matchmaking = matchmaking;
    matchmaking->AddRequestLobbyListStringFilter("universelan-behaviour-token", token.c_str(), galaxy::api::LOBBY_COMPARISON_TYPE_EQUAL);
#if GALAXY_BUILD_FEATURE_HAS_REQUESTLOBBYLIST_ARGS_ALLOWFULL
    matchmaking->RequestLobbyList(false);
#else
    matchmaking->RequestLobbyList();
#endif
    if (!pumpUntil(galaxy, deadline, [&] { return listed.completed; }) || listed.ioFailure || !listed.selected.IsValid()) return 1;

    LobbyEnteredListener entered;
    matchmaking->JoinLobby(listed.selected);
    if (!pumpUntil(galaxy, deadline, [&] { return entered.completed; }) || !entered.success || entered.lobby != listed.selected) return 1;

    const galaxy::api::GalaxyID lobby = entered.lobby;
    const galaxy::api::GalaxyID owner = matchmaking->GetLobbyOwner(lobby);
    writeEvent(arguments, "client-joined");
    if (!pumpUntil(galaxy, deadline, [&] { return hasEvent(arguments, "server-host-reply-scheduled"); })) return 1;

    constexpr std::array<std::uint8_t, 4> expectedPayload{{0x47, 0x53, 0x31, 0x02}};
    constexpr std::uint8_t channel = 61;
    std::array<std::uint8_t, 64> buffer{};
    std::uint32_t size = 0;
    galaxy::api::GalaxyID sender;
    bool read = false;
    while (std::chrono::steady_clock::now() < deadline && !read)
    {
        galaxy->ProcessData();
        if (networking->IsP2PPacketAvailable(&size, channel))
            read = networking->ReadP2PPacket(buffer.data(), static_cast<std::uint32_t>(buffer.size()), &size, sender, channel);
        if (!read) std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    const bool payloadMatches = read && size == expectedPayload.size()
        && std::equal(expectedPayload.begin(), expectedPayload.end(), buffer.begin());
    const bool senderEqualsOwner = read && sender == owner;
    const bool senderEqualsSelf = read && sender == galaxy->GetUser()->GetGalaxyID();
    writeTrace(arguments.trace, std::string("{\"record\":\"direct-game-server-reply\",\"delivery\":")
        + (read ? "true" : "false") + ",\"senderType\":\"unclassified-by-public-sdk\",\"senderEqualsLobbyOwner\":"
        + (senderEqualsOwner ? "true" : "false") + ",\"senderEqualsSelf\":" + (senderEqualsSelf ? "true" : "false")
        + ",\"payloadMatchesPrivateMarker\":" + (payloadMatches ? "true" : "false") + "}");
    writeEvent(arguments, "client-observed-reply");
    const bool left = leaveLobby(galaxy, matchmaking, lobby, deadline);
    writeEvent(arguments, "client-finished");
    return read && payloadMatches && senderEqualsOwner && !senderEqualsSelf && left ? 0 : 1;
}

int run(const Arguments& arguments)
{
    if constexpr (!universelan::behaviour::host::credentials::available) return 4;
    galaxy::api::IGalaxy* const galaxy = galaxy::api::GalaxyFactory::CreateInstance();
    if (galaxy == nullptr) return 1;
    int result = 1;
    try
    {
        galaxy->InitLocal(universelan::behaviour::host::credentials::clientId,
            universelan::behaviour::host::credentials::clientSecret, ".", false);
        {
            AuthListener auth;
            const char* const login = arguments.role == "server-host" ? universelan::behaviour::host::credentials::user1Name
                : universelan::behaviour::host::credentials::user2Name;
            const char* const password = arguments.role == "server-host" ? universelan::behaviour::host::credentials::user1Password
                : universelan::behaviour::host::credentials::user2Password;
            galaxy::api::IUser* const user = galaxy->GetUser();
            if (user == nullptr) throw std::runtime_error("User interface unavailable");
            user->SignIn(login, password);
            const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(arguments.timeoutSeconds);
            if (pumpUntil(galaxy, deadline, [&] { return auth.completed; }) && auth.success)
                result = arguments.role == "server-host" ? runServerHost(arguments, galaxy, deadline) : runClient(arguments, galaxy, deadline);
        }
        galaxy->Shutdown();
    }
    catch (...)
    {
        galaxy->Shutdown();
        result = 1;
    }
    galaxy::api::GalaxyFactory::ResetInstance();
    return result;
}
}
}

int main(int argc, char* argv[])
{
    universelan::behaviour::game_server_p2p::Arguments arguments;
    return universelan::behaviour::game_server_p2p::readArguments(argc, argv, arguments)
        ? universelan::behaviour::game_server_p2p::run(arguments) : 2;
}
#else
int main()
{
    return 0;
}
#endif
