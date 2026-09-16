#include "BehaviourTestCredentials.hxx"
#include "Common/Trace.hxx"

#include <galaxy/GalaxyApi.h>

#include <array>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

#if GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED
namespace universelan::behaviour::lobby_member_persona
{
namespace
{
namespace credentials = universelan::behaviour::host::credentials;
struct Arguments
{
    std::string profile;
    std::filesystem::path trace;
    std::filesystem::path control;
    int timeoutSeconds = 0;
};

bool readArguments(const int argc, char* argv[], Arguments& arguments)
{
    for (int index = 1; index < argc; ++index)
    {
        const std::string option = argv[index];
        if (++index == argc) return false;
        const std::string value = argv[index];
        if (option == "--scenario" && value != "automatic-lobby-member-persona") return false;
        if (option == "--profile") arguments.profile = value;
        else if (option == "--trace") arguments.trace = std::filesystem::u8path(value);
        else if (option == "--control") arguments.control = std::filesystem::u8path(value);
        else if (option == "--timeout-seconds")
        {
            try { arguments.timeoutSeconds = std::stoi(value); }
            catch (...) { return false; }
        }
        else if (option != "--scenario") return false;
    }
    return (arguments.profile == "user1" || arguments.profile == "user2") && !arguments.trace.empty() && !arguments.control.empty()
        && arguments.timeoutSeconds > 0 && arguments.timeoutSeconds <= 60;
}

std::string boolean(const bool value) { return value ? "true" : "false"; }

std::string controlValue(const Arguments& arguments, const char* const name)
{
    std::ifstream input(arguments.control, std::ios::binary);
    const std::string prefix = std::string(name) + "=";
    std::string line;
    while (std::getline(input, line)) if (line.rfind(prefix, 0) == 0) return line.substr(prefix.size());
    return {};
}

bool controlIsSet(const Arguments& arguments, const char* const name) { return controlValue(arguments, name) == "1"; }

void writeEvent(const Arguments& arguments, const char* const event)
{
    std::ofstream output(arguments.control.parent_path() / "event", std::ios::binary | std::ios::app);
    if (output) output << event << '\n';
}

template <typename Predicate>
bool pumpUntil(const Arguments& arguments, const std::chrono::steady_clock::time_point deadline, Predicate&& predicate)
{
    while (std::chrono::steady_clock::now() < deadline)
    {
        if (controlIsSet(arguments, "abort")) return false;
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
        galaxy::api::GalaxyFactory::GetInstance()->ProcessData();
#else
        galaxy::api::ProcessData();
#endif
        if (predicate()) return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return predicate();
}

bool validUser(const galaxy::api::GalaxyID& id)
{
    if (!id.IsValid()) return false;
#if GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
    return id.GetIDType() == galaxy::api::GalaxyID::ID_TYPE_USER;
#else
    return true;
#endif
}

bool validLobby(const galaxy::api::GalaxyID& id)
{
    if (!id.IsValid()) return false;
#if GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
    return id.GetIDType() == galaxy::api::GalaxyID::ID_TYPE_LOBBY;
#else
    return true;
#endif
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
    bool called = false;
    galaxy::api::GalaxyID lobby;
    galaxy::api::LobbyCreateResult result = galaxy::api::LOBBY_CREATE_RESULT_ERROR;
    void OnLobbyCreated(const galaxy::api::GalaxyID& id, const galaxy::api::LobbyCreateResult value) override
    {
        called = true;
        lobby = id;
        result = value;
    }
};

struct LobbyEnteredListener final : galaxy::api::GlobalLobbyEnteredListener
{
    bool called = false;
    galaxy::api::GalaxyID lobby;
    galaxy::api::LobbyEnterResult result = galaxy::api::LOBBY_ENTER_RESULT_ERROR;
    void OnLobbyEntered(const galaxy::api::GalaxyID& id, const galaxy::api::LobbyEnterResult value) override
    {
        called = true;
        lobby = id;
        result = value;
    }
};

struct LobbyListListener final : galaxy::api::GlobalLobbyListListener
{
    galaxy::api::IMatchmaking* matchmaking = nullptr;
    bool called = false;
    bool failed = true;
    galaxy::api::GalaxyID selected;

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
    void OnLobbyList(const std::uint32_t count, const galaxy::api::LobbyListResult result) override
    {
        called = true;
        failed = result != galaxy::api::LOBBY_LIST_RESULT_SUCCESS;
        if (!failed && count == 1) selected = matchmaking->GetLobbyByIndex(0);
    }
#else
    void OnLobbyList(const std::uint32_t count, const bool ioFailure) override
    {
        called = true;
        failed = ioFailure;
        if (!failed && count == 1) selected = matchmaking->GetLobbyByIndex(0);
    }
#endif
};

struct LobbyLeftListener final : galaxy::api::GlobalLobbyLeftListener
{
    galaxy::api::GalaxyID expected;
    bool called = false;
    bool matchingLobby = false;

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
    void OnLobbyLeft(const galaxy::api::GalaxyID& lobby, const LobbyLeaveReason) override
#else
    void OnLobbyLeft(const galaxy::api::GalaxyID& lobby, const bool) override
#endif
    {
        called = true;
        matchingLobby = matchingLobby || lobby == expected;
    }
};

struct MemberAndPersonaListener final : galaxy::api::GlobalLobbyMemberStateListener, galaxy::api::GlobalPersonaDataChangedListener
{
    galaxy::api::GalaxyID lobby;
    galaxy::api::GalaxyID self;
    galaxy::api::GalaxyID enteredRemote;
    bool enteredRemoteObserved = false;
    bool matchingPersonaObserved = false;

    void OnLobbyMemberStateChanged(const galaxy::api::GalaxyID& callbackLobby, const galaxy::api::GalaxyID& member,
        const galaxy::api::LobbyMemberStateChange state) override
    {
        if (callbackLobby != lobby || member == self || !validUser(member)) return;
        if (state == galaxy::api::LOBBY_MEMBER_STATE_CHANGED_ENTERED)
        {
            enteredRemote = member;
            enteredRemoteObserved = true;
        }
    }

    void OnPersonaDataChanged(const galaxy::api::GalaxyID user, const std::uint32_t) override
    {
        if (enteredRemoteObserved && user == enteredRemote) matchingPersonaObserved = true;
    }

    bool personaForEnteredRemote() const
    {
        return matchingPersonaObserved;
    }
};

bool leaveLobby(const Arguments& arguments, galaxy::api::IMatchmaking* const matchmaking, const galaxy::api::GalaxyID& lobby,
    const std::chrono::steady_clock::time_point deadline)
{
    LobbyLeftListener left;
    left.expected = lobby;
    matchmaking->LeaveLobby(lobby);
    return pumpUntil(arguments, deadline, [&] { return left.called && left.matchingLobby; });
}

bool run(const Arguments& arguments)
{
    std::vector<std::string> records;
    if constexpr (!credentials::available)
    {
        records.push_back("{\"record\":\"initialize\",\"result\":\"credentials-unavailable\"}");
        common::writeTrace(arguments.trace, records);
        return false;
    }

    bool initialized = false;
    try
    {
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
        galaxy::api::IGalaxy* const galaxy = galaxy::api::GalaxyFactory::CreateInstance();
        galaxy->InitLocal(credentials::clientId, credentials::clientSecret, ".");
        galaxy::api::IUser* const user = galaxy->GetUser();
        galaxy::api::IMatchmaking* const matchmaking = galaxy->GetMatchmaking();
        galaxy::api::IFriends* const friends = galaxy->GetFriends();
#else
        galaxy::api::Init(galaxy::api::InitOptions{credentials::clientId, credentials::clientSecret, "."});
        galaxy::api::IUser* const user = galaxy::api::User();
        galaxy::api::IMatchmaking* const matchmaking = galaxy::api::Matchmaking();
        galaxy::api::IFriends* const friends = galaxy::api::Friends();
#endif
        initialized = true;
        records.push_back("{\"record\":\"initialize\",\"result\":\"returned\"}");
        if (user == nullptr || matchmaking == nullptr || friends == nullptr) throw std::runtime_error("Missing public interface");

        AuthListener auth;
        const char* const login = arguments.profile == "user1" ? credentials::user1Name : credentials::user2Name;
        const char* const password = arguments.profile == "user1" ? credentials::user1Password : credentials::user2Password;
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
        user->SignInCredentials(login, password, &auth);
#else
        user->SignIn(login, password);
#endif
        const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(arguments.timeoutSeconds);
        const bool signedIn = pumpUntil(arguments, deadline, [&] { return auth.completed; }) && auth.success;
        records.push_back("{\"record\":\"sign-in\",\"result\":" + common::jsonString(signedIn ? "success" : "failure") + "}");
        if (!signedIn) throw std::runtime_error("Sign-in failed");

        const galaxy::api::GalaxyID self = user->GetGalaxyID();
        MemberAndPersonaListener callbacks;
        callbacks.self = self;
        records.push_back("{\"record\":\"listeners-armed\",\"memberListenerRegistered\":true,\"personaListenerRegistered\":true,\"selfValid\":"
            + boolean(validUser(self)) + "}");
        if (!validUser(self)) throw std::runtime_error("Invalid self");

        const bool creator = arguments.profile == "user1";
        galaxy::api::GalaxyID lobby;
        bool joined = false;
        auto cleanup = [&]
        {
            const bool left = !joined || leaveLobby(arguments, matchmaking, lobby, std::chrono::steady_clock::now() + std::chrono::seconds(5));
            if (left) writeEvent(arguments, "cleanup-ack");
            return left;
        };

        if (creator)
        {
            LobbyCreatedListener created;
            LobbyEnteredListener entered;
            matchmaking->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 2, false, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM);
            const bool createdAndEntered = pumpUntil(arguments, deadline, [&] { return created.called && entered.called; });
            lobby = entered.lobby;
            joined = createdAndEntered && created.result == galaxy::api::LOBBY_CREATE_RESULT_SUCCESS
                && entered.result == galaxy::api::LOBBY_ENTER_RESULT_SUCCESS && created.lobby == lobby && validLobby(lobby);
            callbacks.lobby = lobby;
            records.push_back("{\"record\":\"create\",\"createdAndEntered\":" + boolean(joined) + ",\"publicLobbyValid\":" + boolean(validLobby(lobby)) + "}");
            if (!joined) { cleanup(); throw std::runtime_error("Create failed"); }

            const std::string token = controlValue(arguments, "token");
#if GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
            matchmaking->SetLobbyData(lobby, "universelan-behaviour-token", token.c_str());
            matchmaking->SetLobbyJoinable(lobby, true);
            const bool markerScheduled = true;
            const bool joinableScheduled = true;
#else
            const bool markerScheduled = matchmaking->SetLobbyData(lobby, "universelan-behaviour-token", token.c_str());
            const bool joinableScheduled = matchmaking->SetLobbyJoinable(lobby, true);
#endif
            const bool configured = pumpUntil(arguments, deadline, [&] { return matchmaking->IsLobbyJoinable(lobby); });
            records.push_back("{\"record\":\"configuration\",\"tokenNonempty\":" + boolean(!token.empty()) + ",\"markerScheduled\":"
                + boolean(markerScheduled) + ",\"joinableScheduled\":" + boolean(joinableScheduled) + ",\"joinableVisible\":" + boolean(configured) + "}");
            if (token.empty() || !markerScheduled || !joinableScheduled || !configured) { cleanup(); throw std::runtime_error("Configuration failed"); }
            writeEvent(arguments, "creator-ready");
            if (!pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "joiner-joined"); })) { cleanup(); throw std::runtime_error("Joiner timeout"); }
            const bool matchingPersona = pumpUntil(arguments, deadline, [&] { return callbacks.personaForEnteredRemote(); });
            std::array<char, 256> name{};
            if (matchingPersona && friends != nullptr) friends->GetFriendPersonaNameCopy(callbacks.enteredRemote, name.data(), static_cast<std::uint32_t>(name.size()));
            records.push_back("{\"record\":\"remote-persona-observation\",\"remoteEnteredObserved\":" + boolean(callbacks.enteredRemoteObserved)
                + ",\"enteredRemoteValidNonSelf\":" + boolean(validUser(callbacks.enteredRemote) && callbacks.enteredRemote != self)
                + ",\"matchingPersonaCallbackObserved\":" + boolean(matchingPersona) + ",\"personaNameNonempty\":" + boolean(name[0] != '\0') + "}");
            if (!pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "joiner-left"); })) { cleanup(); throw std::runtime_error("Joiner cleanup timeout"); }
            const bool left = cleanup();
            records.push_back("{\"record\":\"creator-leave\",\"completed\":" + boolean(left) + "}");
            common::writeTrace(arguments.trace, records);
            return left && callbacks.enteredRemoteObserved && matchingPersona && name[0] != '\0';
        }

        if (!pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "creator-ready"); })) throw std::runtime_error("Creator timeout");
        const std::string token = controlValue(arguments, "token");
        LobbyListListener listed;
        bool listedOne = false;
        for (int attempt = 0; attempt < 6 && !listedOne && std::chrono::steady_clock::now() < deadline; ++attempt)
        {
            listed = LobbyListListener{};
            listed.matchmaking = matchmaking;
            matchmaking->AddRequestLobbyListStringFilter("universelan-behaviour-token", token.c_str(), galaxy::api::LOBBY_COMPARISON_TYPE_EQUAL);
            matchmaking->RequestLobbyList(false);
            listedOne = pumpUntil(arguments, std::min(deadline, std::chrono::steady_clock::now() + std::chrono::seconds(3)), [&] { return listed.called; })
                && !listed.failed && validLobby(listed.selected);
            if (!listedOne) std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        records.push_back("{\"record\":\"list\",\"selectedOnePublicLobby\":" + boolean(listedOne) + "}");
        if (!listedOne) throw std::runtime_error("List failed");
        LobbyEnteredListener entered;
        matchmaking->JoinLobby(listed.selected);
        const bool joinedLobby = pumpUntil(arguments, deadline, [&] { return entered.called; })
            && entered.result == galaxy::api::LOBBY_ENTER_RESULT_SUCCESS && entered.lobby == listed.selected;
        lobby = entered.lobby;
        joined = joinedLobby;
        callbacks.lobby = lobby;
        records.push_back("{\"record\":\"join\",\"enteredSelectedLobby\":" + boolean(joinedLobby) + "}");
        if (!joinedLobby) { cleanup(); throw std::runtime_error("Join failed"); }
        writeEvent(arguments, "joiner-joined");
        galaxy::api::GalaxyID owner = matchmaking->GetLobbyOwner(lobby);
        records.push_back("{\"record\":\"joined-persona-observation\",\"ownerValidNonSelf\":" + boolean(validUser(owner) && owner != self) + "}");
        const bool left = cleanup();
        records.push_back("{\"record\":\"joiner-leave\",\"completed\":" + boolean(left) + "}");
        if (left) writeEvent(arguments, "joiner-left");
        common::writeTrace(arguments.trace, records);
        return validUser(owner) && owner != self && left;
    }
    catch (...)
    {
        if (records.empty()) records.push_back("{\"record\":\"initialize\",\"result\":\"exception\"}");
        common::writeTrace(arguments.trace, records);
        if (initialized)
        {
#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
            galaxy::api::GalaxyFactory::GetInstance()->Shutdown();
            galaxy::api::GalaxyFactory::ResetInstance();
#else
            galaxy::api::Shutdown();
#endif
        }
        return false;
    }
}
}
}

int main(int argc, char* argv[])
{
    using namespace universelan::behaviour::lobby_member_persona;
    Arguments arguments;
    return readArguments(argc, argv, arguments) && run(arguments) ? 0 : 1;
}
#else
int main()
{
    return 0;
}
#endif
