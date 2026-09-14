#include "BehaviourTestCredentials.hxx"
#include "Common/Trace.hxx"

#include <galaxy/GalaxyApi.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace universelan::behaviour::host
{
namespace
{
struct Arguments
{
    std::string scenario;
    std::string profile;
    std::filesystem::path trace;
    std::filesystem::path control;
    int timeoutSeconds = 0;
};

    enum class Scenario { initializeAndSignIn, sessionIdRepeatability, gogServicesState, gogServicesStateCharacterization, publicLobbyCreateListJoinLeave, publicLobbyDataPropagationCharacterization, publicLobbyDataPropagation, multipleLobbyMembershipAndMessageIsolationCharacterization, multipleLobbyMembershipAndMessageIsolation, chatRoomMessageDeliveryCharacterization, chatRoomMessageDelivery, friendsPeerInformationRetrievalCharacterization, friendsPeerInformationRetrieval };

bool isSupportedScenario(const std::string& scenario)
{
    return scenario == "initialize-and-sign-in" || scenario == "session-id-repeatability" || scenario == "gog-services-state"
        || scenario == "gog-services-state-characterization" || scenario == "public-lobby-create-list-join-leave"
            || scenario == "public-lobby-data-propagation-characterization" || scenario == "public-lobby-data-propagation"
            || scenario == "multiple-lobby-membership-and-message-isolation-characterization" || scenario == "multiple-lobby-membership-and-message-isolation"
        || scenario == "chat-room-message-delivery-characterization" || scenario == "chat-room-message-delivery"
        || scenario == "friends-peer-information-retrieval-characterization" || scenario == "friends-peer-information-retrieval";
}

Scenario selectedScenario(const Arguments& arguments)
{
    if (arguments.scenario == "session-id-repeatability") return Scenario::sessionIdRepeatability;
    if (arguments.scenario == "gog-services-state") return Scenario::gogServicesState;
    if (arguments.scenario == "gog-services-state-characterization") return Scenario::gogServicesStateCharacterization;
    if (arguments.scenario == "public-lobby-create-list-join-leave") return Scenario::publicLobbyCreateListJoinLeave;
    if (arguments.scenario == "public-lobby-data-propagation-characterization") return Scenario::publicLobbyDataPropagationCharacterization;
    if (arguments.scenario == "public-lobby-data-propagation") return Scenario::publicLobbyDataPropagation;
    if (arguments.scenario == "multiple-lobby-membership-and-message-isolation-characterization") return Scenario::multipleLobbyMembershipAndMessageIsolationCharacterization;
    if (arguments.scenario == "multiple-lobby-membership-and-message-isolation") return Scenario::multipleLobbyMembershipAndMessageIsolation;
    if (arguments.scenario == "chat-room-message-delivery-characterization") return Scenario::chatRoomMessageDeliveryCharacterization;
    if (arguments.scenario == "chat-room-message-delivery") return Scenario::chatRoomMessageDelivery;
    if (arguments.scenario == "friends-peer-information-retrieval-characterization") return Scenario::friendsPeerInformationRetrievalCharacterization;
    if (arguments.scenario == "friends-peer-information-retrieval") return Scenario::friendsPeerInformationRetrieval;
    return Scenario::initializeAndSignIn;
}

bool readArguments(const int argc, char* argv[], Arguments& arguments)
{
    for (int index = 1; index < argc; ++index)
    {
        const std::string option = argv[index];
        if (++index == argc) return false;
        const std::string value = argv[index];
        if (option == "--scenario") arguments.scenario = value;
        else if (option == "--profile") arguments.profile = value;
        else if (option == "--trace") arguments.trace = std::filesystem::u8path(value);
        else if (option == "--control") arguments.control = std::filesystem::u8path(value);
        else if (option == "--timeout-seconds")
        {
            try { arguments.timeoutSeconds = std::stoi(value); }
            catch (...) { return false; }
        }
        else return false;
    }
    return isSupportedScenario(arguments.scenario) && (arguments.profile == "user1" || arguments.profile == "user2")
        && !arguments.trace.empty() && ((arguments.scenario != "public-lobby-create-list-join-leave"
            && arguments.scenario != "public-lobby-data-propagation-characterization" && arguments.scenario != "public-lobby-data-propagation"
            && arguments.scenario != "multiple-lobby-membership-and-message-isolation-characterization" && arguments.scenario != "multiple-lobby-membership-and-message-isolation"
             && arguments.scenario != "chat-room-message-delivery-characterization" && arguments.scenario != "chat-room-message-delivery"
             && arguments.scenario != "friends-peer-information-retrieval-characterization" && arguments.scenario != "friends-peer-information-retrieval") || !arguments.control.empty())
        && arguments.timeoutSeconds > 0 && arguments.timeoutSeconds <= 60;
}

const char* idType(const galaxy::api::GalaxyID::IDType type)
{
    switch (type)
    {
    case galaxy::api::GalaxyID::ID_TYPE_UNASSIGNED: return "unassigned";
    case galaxy::api::GalaxyID::ID_TYPE_LOBBY: return "lobby";
    case galaxy::api::GalaxyID::ID_TYPE_USER: return "user";
    }
    return "unknown";
}

struct AuthListener final : galaxy::api::IAuthListener
{
    enum class Outcome { pending, success, failure };

    Outcome outcome = Outcome::pending;
    int failureReason = -1;

    void OnAuthSuccess() override { outcome = Outcome::success; }
    void OnAuthFailure(const FailureReason reason) override
    {
        outcome = Outcome::failure;
        failureReason = static_cast<int>(reason);
    }
    void OnAuthLost() override {}
};

struct GogServicesStateEvent
{
    const char* phase;
    const char* state;
};

std::string boolean(const bool value) { return value ? "true" : "false"; }

const char* gogServicesState(const galaxy::api::GogServicesConnectionState state)
{
    switch (state)
    {
    case galaxy::api::GOG_SERVICES_CONNECTION_STATE_UNDEFINED: return "undefined";
    case galaxy::api::GOG_SERVICES_CONNECTION_STATE_CONNECTED: return "connected";
    case galaxy::api::GOG_SERVICES_CONNECTION_STATE_DISCONNECTED: return "disconnected";
    case galaxy::api::GOG_SERVICES_CONNECTION_STATE_AUTH_LOST: return "auth-lost";
    }
    return "invalid";
}

struct GogServicesStateListener final : galaxy::api::GlobalGogServicesConnectionStateListener
{
    const AuthListener& auth;
    bool settled = false;
    std::vector<GogServicesStateEvent> events;

    explicit GogServicesStateListener(const AuthListener& authListener) : auth(authListener) {}

    void OnConnectionStateChange(const galaxy::api::GogServicesConnectionState state) override
    {
        const char* phase = auth.outcome == AuthListener::Outcome::pending ? "before" : (settled ? "settled" : "immediate");
        events.push_back({phase, gogServicesState(state)});
    }
};

const char* elapsedBucket(const std::chrono::milliseconds elapsed)
{
    if (elapsed < std::chrono::milliseconds(100)) return "under-100ms";
    if (elapsed < std::chrono::milliseconds(250)) return "100-249ms";
    return "250ms-or-more";
}

std::string gogServicesStateEvents(const std::vector<GogServicesStateEvent>& events)
{
    std::string result = "[";
    for (std::size_t index = 0; index < events.size(); ++index)
    {
        if (index != 0) result += ',';
        result += "{\"phase\":" + common::jsonString(events[index].phase)
            + ",\"state\":" + common::jsonString(events[index].state) + "}";
    }
    return result + "]";
}

std::string selfStateRecord(galaxy::api::IUser* const user)
{
    const bool signedIn = user != nullptr && user->SignedIn();
    const bool loggedOn = user != nullptr && user->IsLoggedOn();
    galaxy::api::GalaxyID first;
    galaxy::api::GalaxyID second;
    if (user != nullptr)
    {
        first = user->GetGalaxyID();
        second = user->GetGalaxyID();
    }

    std::array<char, 256> persona{};
    bool personaAvailable = false;
    if (signedIn && galaxy::api::Friends() != nullptr)
    {
        galaxy::api::Friends()->GetPersonaNameCopy(persona.data(), static_cast<std::uint32_t>(persona.size()));
        personaAvailable = persona[0] != '\0';
    }
    return "{\"record\":\"self-state\",\"signedIn\":" + boolean(signedIn)
        + ",\"loggedOn\":" + boolean(loggedOn)
        + ",\"idValid\":" + boolean(first.IsValid())
        + ",\"idType\":" + common::jsonString(idType(first.GetIDType()))
        + ",\"selfIdRepeatEqual\":" + boolean(first == second)
        + ",\"personaAvailable\":" + boolean(personaAvailable) + "}";
}

std::string controlValue(const std::filesystem::path& control, const std::string& name)
{
    std::ifstream input(control, std::ios::binary);
    std::string line;
    const std::string prefix = name + "=";
    while (std::getline(input, line)) if (line.rfind(prefix, 0) == 0) return line.substr(prefix.size());
    return {};
}

bool controlIsSet(const Arguments& arguments, const char* const name)
{
    return controlValue(arguments.control, name) == "1";
}

void writeEvent(const Arguments& arguments, const char* const event)
{
    const std::filesystem::path target = arguments.control.parent_path() / "event";
    std::ofstream output(target, std::ios::binary | std::ios::app);
    if (output) output << event << '\n';
}

bool writeOneTimeRelay(const Arguments& arguments, const char* const name, const std::string& value)
{
    const std::filesystem::path target = arguments.control.parent_path() / name;
    const std::filesystem::path temporary = target.string() + ".tmp";
    std::ofstream output(temporary, std::ios::binary | std::ios::trunc);
    if (!output) return false;
    output << value;
    output.close();
    if (!output) return false;
    std::error_code error;
    std::filesystem::rename(temporary, target, error);
    if (error)
    {
        std::filesystem::remove(target, error);
        if (error) return false;
        std::filesystem::rename(temporary, target, error);
    }
    return !error;
}

bool consumeOneTimeRelay(const Arguments& arguments, const char* const name, std::string& value)
{
    const std::filesystem::path target = arguments.control.parent_path() / name;
    std::error_code error;
    const bool exists = std::filesystem::exists(target, error);
    if (error) return false;
    if (!exists) { value.clear(); return true; }
    std::ifstream input(target, std::ios::binary);
    if (!input) return false;
    value.assign(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
    if (input.bad()) return false;
    input.close();
    std::filesystem::remove(target, error);
    return !error;
}

bool galaxyIDFromRelay(const std::string& value, galaxy::api::GalaxyID& id)
{
    if (value.empty() || value.size() > 20) return false;
    std::uint64_t raw = 0;
    for (const char character : value)
    {
        if (character < '0' || character > '9') return false;
        const std::uint64_t digit = static_cast<std::uint64_t>(character - '0');
        if (raw > (UINT64_MAX - digit) / 10) return false;
        raw = raw * 10 + digit;
    }
    id = galaxy::api::GalaxyID(raw);
    return id.IsValid() && id.GetIDType() == galaxy::api::GalaxyID::ID_TYPE_USER;
}

template <typename Predicate>
bool pumpUntil(const Arguments& arguments, const std::chrono::steady_clock::time_point deadline, Predicate&& predicate)
{
    while (std::chrono::steady_clock::now() < deadline)
    {
        if (controlIsSet(arguments, "abort")) return false;
        galaxy::api::ProcessData();
        if (predicate()) return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return predicate();
}

const char* createResult(const galaxy::api::LobbyCreateResult result)
{
    switch (result)
    {
    case galaxy::api::LOBBY_CREATE_RESULT_SUCCESS: return "success";
    case galaxy::api::LOBBY_CREATE_RESULT_ERROR: return "error";
    case galaxy::api::LOBBY_CREATE_RESULT_CONNECTION_FAILURE: return "connection-failure";
    }
    return "unknown";
}

const char* enterResult(const galaxy::api::LobbyEnterResult result)
{
    switch (result)
    {
    case galaxy::api::LOBBY_ENTER_RESULT_SUCCESS: return "success";
    case galaxy::api::LOBBY_ENTER_RESULT_LOBBY_DOES_NOT_EXIST: return "does-not-exist";
    case galaxy::api::LOBBY_ENTER_RESULT_LOBBY_IS_FULL: return "full";
    case galaxy::api::LOBBY_ENTER_RESULT_ERROR: return "error";
    case galaxy::api::LOBBY_ENTER_RESULT_CONNECTION_FAILURE: return "connection-failure";
    }
    return "unknown";
}

const char* listResult(const galaxy::api::LobbyListResult result)
{
    switch (result)
    {
    case galaxy::api::LOBBY_LIST_RESULT_SUCCESS: return "success";
    case galaxy::api::LOBBY_LIST_RESULT_ERROR: return "error";
    case galaxy::api::LOBBY_LIST_RESULT_CONNECTION_FAILURE: return "connection-failure";
    }
    return "unknown";
}

const char* leaveReason(const galaxy::api::ILobbyLeftListener::LobbyLeaveReason reason)
{
    switch (reason)
    {
    case galaxy::api::ILobbyLeftListener::LOBBY_LEAVE_REASON_UNDEFINED: return "undefined";
    case galaxy::api::ILobbyLeftListener::LOBBY_LEAVE_REASON_USER_LEFT: return "user-left";
    case galaxy::api::ILobbyLeftListener::LOBBY_LEAVE_REASON_LOBBY_CLOSED: return "lobby-closed";
    case galaxy::api::ILobbyLeftListener::LOBBY_LEAVE_REASON_CONNECTION_LOST: return "connection-lost";
    }
    return "unknown";
}

struct LobbyCreatedListener final : galaxy::api::ILobbyCreatedListener
{
    bool called = false;
    galaxy::api::GalaxyID lobby;
    galaxy::api::LobbyCreateResult result = galaxy::api::LOBBY_CREATE_RESULT_ERROR;
    void OnLobbyCreated(const galaxy::api::GalaxyID& id, const galaxy::api::LobbyCreateResult callbackResult) override
    {
        called = true; lobby = id; result = callbackResult;
    }
};

struct LobbyEnteredListener final : galaxy::api::ILobbyEnteredListener
{
    bool called = false;
    galaxy::api::GalaxyID lobby;
    galaxy::api::LobbyEnterResult result = galaxy::api::LOBBY_ENTER_RESULT_ERROR;
    void OnLobbyEntered(const galaxy::api::GalaxyID& id, const galaxy::api::LobbyEnterResult callbackResult) override
    {
        called = true; lobby = id; result = callbackResult;
    }
};

struct LobbyDataUpdateListener final : galaxy::api::ILobbyDataUpdateListener
{
    bool called = false;
    bool success = false;
    galaxy::api::GalaxyID lobby;
    FailureReason reason = FAILURE_REASON_UNDEFINED;
    void OnLobbyDataUpdateSuccess(const galaxy::api::GalaxyID& id) override { called = true; success = true; lobby = id; }
    void OnLobbyDataUpdateFailure(const galaxy::api::GalaxyID& id, const FailureReason failureReason) override
    {
        called = true; lobby = id; reason = failureReason;
    }
};

struct LobbyDataPropagationListener final : galaxy::api::GlobalLobbyDataListener
{
    const Arguments* arguments = nullptr;
    galaxy::api::IMatchmaking* matchmaking = nullptr;
    galaxy::api::GalaxyID expectedLobby;
    const char* key = nullptr;
    const char* expectedValue = nullptr;
    int targetCallbackCount = 0;
    bool memberIdValid = true;
    bool copyVisibleInCallback = false;

    void OnLobbyDataUpdated(const galaxy::api::GalaxyID& lobby, const galaxy::api::GalaxyID& member) override
    {
        if (lobby != expectedLobby) return;
        ++targetCallbackCount;
        memberIdValid = memberIdValid && member.IsValid();
        std::array<char, 256> value{};
        matchmaking->GetLobbyDataCopy(lobby, key, value.data(), static_cast<std::uint32_t>(value.size()));
        copyVisibleInCallback = copyVisibleInCallback || std::string(value.data()) == expectedValue;
        writeEvent(*arguments, "joiner-lobby-data-callback");
    }
};

struct LobbyLeftListener final : galaxy::api::ILobbyLeftListener
{
    bool called = false;
    galaxy::api::GalaxyID lobby;
    LobbyLeaveReason reason = LOBBY_LEAVE_REASON_UNDEFINED;
    void OnLobbyLeft(const galaxy::api::GalaxyID& id, const LobbyLeaveReason leaveReasonValue) override
    {
        called = true; lobby = id; reason = leaveReasonValue;
    }
};

struct LobbyListListener final : galaxy::api::ILobbyListListener
{
    galaxy::api::IMatchmaking* matchmaking = nullptr;
    bool called = false;
    std::uint32_t count = 0;
    galaxy::api::LobbyListResult result = galaxy::api::LOBBY_LIST_RESULT_ERROR;
    std::vector<galaxy::api::GalaxyID> candidates;
    void OnLobbyList(const std::uint32_t lobbyCount, const galaxy::api::LobbyListResult callbackResult) override
    {
        called = true; count = lobbyCount; result = callbackResult;
        if (callbackResult == galaxy::api::LOBBY_LIST_RESULT_SUCCESS)
            for (std::uint32_t index = 0; index < lobbyCount; ++index) candidates.push_back(matchmaking->GetLobbyByIndex(index));
    }
};

std::string snapshotRecord(const char* const record, galaxy::api::IMatchmaking* const matchmaking,
    const galaxy::api::GalaxyID& lobby, const galaxy::api::GalaxyID& self, const std::uint32_t expectedMembers)
{
    const std::uint32_t count = matchmaking->GetNumLobbyMembers(lobby);
    const galaxy::api::GalaxyID owner = matchmaking->GetLobbyOwner(lobby);
    bool selfPresent = false;
    bool otherPresent = false;
    bool membersValid = true;
    bool distinctMembers = count == expectedMembers;
    for (std::uint32_t index = 0; index < count; ++index)
    {
        const galaxy::api::GalaxyID member = matchmaking->GetLobbyMemberByIndex(lobby, index);
        membersValid = membersValid && member.IsValid() && member.GetIDType() == galaxy::api::GalaxyID::ID_TYPE_USER;
        selfPresent = selfPresent || member == self;
        otherPresent = otherPresent || member != self;
        for (std::uint32_t previous = 0; previous < index; ++previous)
            distinctMembers = distinctMembers && member != matchmaking->GetLobbyMemberByIndex(lobby, previous);
    }
    return "{\"record\":" + common::jsonString(record) + ",\"lobbyValid\":" + boolean(lobby.IsValid())
        + ",\"public\":" + boolean(matchmaking->GetLobbyType(lobby) == galaxy::api::LOBBY_TYPE_PUBLIC)
        + ",\"joinable\":" + boolean(matchmaking->IsLobbyJoinable(lobby))
        + ",\"capacity\":" + std::to_string(matchmaking->GetMaxNumLobbyMembers(lobby))
        + ",\"memberCount\":" + std::to_string(count) + ",\"selfPresent\":" + boolean(selfPresent)
        + ",\"otherPresent\":" + boolean(otherPresent) + ",\"membersValid\":" + boolean(membersValid)
        + ",\"membersDistinct\":" + boolean(distinctMembers) + ",\"ownerIsSelf\":" + boolean(owner == self)
        + ",\"ownerValid\":" + boolean(owner.IsValid() && owner.GetIDType() == galaxy::api::GalaxyID::ID_TYPE_USER) + "}";
}

bool leaveLobby(const Arguments& arguments, galaxy::api::IMatchmaking* const matchmaking, const galaxy::api::GalaxyID& lobby,
    std::vector<std::string>& records, const char* const record, const std::chrono::steady_clock::time_point deadline)
{
    LobbyLeftListener listener;
    matchmaking->LeaveLobby(lobby, &listener);
    const bool completed = pumpUntil(arguments, deadline, [&] { return listener.called; });
    records.push_back("{\"record\":" + common::jsonString(record) + ",\"result\":"
        + common::jsonString(completed ? "callback" : "timeout") + ",\"reason\":"
        + common::jsonString(completed ? leaveReason(listener.reason) : "unavailable") + ",\"sameLobby\":"
        + boolean(completed && listener.lobby == lobby) + "}");
    return completed && listener.reason == galaxy::api::ILobbyLeftListener::LOBBY_LEAVE_REASON_USER_LEFT && listener.lobby == lobby;
}

bool runPublicLobby(const Arguments& arguments, galaxy::api::IUser* const user, std::vector<std::string>& records)
{
    galaxy::api::IMatchmaking* const matchmaking = galaxy::api::Matchmaking();
    const std::string token = controlValue(arguments.control, "token");
    const Scenario scenario = selectedScenario(arguments);
    const bool dataPropagation = scenario == Scenario::publicLobbyDataPropagationCharacterization || scenario == Scenario::publicLobbyDataPropagation;
    static constexpr const char* propagationKey = "universelan-behaviour-data-propagation";
    const std::string propagationValue = token + "-data";
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(arguments.timeoutSeconds);
    if (matchmaking == nullptr || token.empty()) { writeEvent(arguments, "cleanup-ack"); return false; }
    const galaxy::api::GalaxyID self = user->GetGalaxyID();
    galaxy::api::GalaxyID lobby;
    bool joined = false;
    bool completed = false;
    const bool creator = arguments.profile == "user1";
    auto cleanup = [&]
    {
        if (joined) leaveLobby(arguments, matchmaking, lobby, records, "cleanup-leave", deadline);
        writeEvent(arguments, "cleanup-ack");
    };
    if (creator)
    {
        LobbyCreatedListener created;
        LobbyEnteredListener entered;
        matchmaking->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 2, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM, &created, &entered);
        const bool callbacks = pumpUntil(arguments, deadline, [&] { return created.called && entered.called; });
        records.push_back("{\"record\":\"create\",\"result\":" + common::jsonString(callbacks ? createResult(created.result) : "timeout")
            + ",\"lobbyValid\":" + boolean(callbacks && created.lobby.IsValid()) + ",\"lobbyType\":"
            + common::jsonString(callbacks ? idType(created.lobby.GetIDType()) : "unavailable") + "}");
        records.push_back("{\"record\":\"creator-enter\",\"result\":" + common::jsonString(callbacks ? enterResult(entered.result) : "timeout")
            + ",\"sameCreatedLobby\":" + boolean(callbacks && created.lobby == entered.lobby) + "}");
        if (!callbacks || created.result != galaxy::api::LOBBY_CREATE_RESULT_SUCCESS || entered.result != galaxy::api::LOBBY_ENTER_RESULT_SUCCESS
            || created.lobby != entered.lobby || !created.lobby.IsValid()) { cleanup(); return false; }
        lobby = created.lobby; joined = true;
        LobbyDataUpdateListener joinable;
        LobbyDataUpdateListener capacity;
        matchmaking->SetLobbyJoinable(lobby, true, &joinable);
        matchmaking->SetMaxNumLobbyMembers(lobby, 2, &capacity);
        const bool configurationCompleted = pumpUntil(arguments, deadline, [&] { return joinable.called && capacity.called; });
        const bool configurationVisible = matchmaking->IsLobbyJoinable(lobby) && matchmaking->GetMaxNumLobbyMembers(lobby) == 2;
        records.push_back("{\"record\":\"configuration\",\"joinableUpdateSuccess\":"
            + boolean(configurationCompleted && joinable.success && joinable.lobby == lobby) + ",\"capacityUpdateSuccess\":"
            + boolean(configurationCompleted && capacity.success && capacity.lobby == lobby) + ",\"joinableVisible\":"
            + boolean(configurationVisible && matchmaking->IsLobbyJoinable(lobby)) + ",\"capacityVisible\":"
            + boolean(configurationVisible && matchmaking->GetMaxNumLobbyMembers(lobby) == 2) + "}");
        if (!configurationCompleted || !joinable.success || !capacity.success || joinable.lobby != lobby || capacity.lobby != lobby || !configurationVisible) { cleanup(); return false; }
        LobbyDataUpdateListener metadata;
        matchmaking->SetLobbyData(lobby, "universelan-behaviour-token", token.c_str(), &metadata);
        const bool metadataCompleted = pumpUntil(arguments, deadline, [&] { return metadata.called; });
        records.push_back("{\"record\":\"metadata\",\"result\":" + common::jsonString(metadataCompleted && metadata.success ? "success" : "failure")
            + ",\"sameCreatedLobby\":" + boolean(metadataCompleted && metadata.lobby == lobby) + "}");
        if (!metadataCompleted || !metadata.success || metadata.lobby != lobby) { cleanup(); return false; }
        writeEvent(arguments, "creator-ready");
        if (!pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "joiner-joined"); })) { cleanup(); return false; }
        if (dataPropagation)
        {
            if (!pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "observer-armed"); })) { cleanup(); return false; }
            LobbyDataUpdateListener update;
            matchmaking->SetLobbyData(lobby, propagationKey, propagationValue.c_str(), &update);
            const bool updateCompleted = pumpUntil(arguments, deadline, [&] { return update.called; });
            records.push_back("{\"record\":\"owner-data-update\",\"result\":"
                + common::jsonString(updateCompleted && update.success ? "success" : "failure")
                + ",\"sameCreatedLobby\":" + boolean(updateCompleted && update.lobby == lobby) + "}");
            writeEvent(arguments, "creator-data-update-callback");
            writeEvent(arguments, "creator-data-update-complete");
            if (!updateCompleted || !update.success || update.lobby != lobby
                || !pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "joiner-data-observed"); })) { cleanup(); return false; }
            if (!pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "joiner-left"); })) { cleanup(); return false; }
            records.push_back(snapshotRecord("creator-sole-owner-snapshot", matchmaking, lobby, self, 1));
            if (matchmaking->GetNumLobbyMembers(lobby) != 1 || matchmaking->GetLobbyOwner(lobby) != self) { cleanup(); return false; }
            completed = leaveLobby(arguments, matchmaking, lobby, records, "creator-leave", deadline);
            joined = false;
            writeEvent(arguments, "cleanup-ack");
            return completed;
        }
        records.push_back(snapshotRecord("creator-two-member-snapshot", matchmaking, lobby, self, 2));
        if (matchmaking->GetNumLobbyMembers(lobby) != 2) { cleanup(); return false; }
        writeEvent(arguments, "creator-two-member");
        if (!pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "joiner-left"); })) { cleanup(); return false; }
        records.push_back(snapshotRecord("creator-sole-owner-snapshot", matchmaking, lobby, self, 1));
        if (matchmaking->GetNumLobbyMembers(lobby) != 1 || matchmaking->GetLobbyOwner(lobby) != self) { cleanup(); return false; }
        completed = leaveLobby(arguments, matchmaking, lobby, records, "creator-leave", deadline);
        joined = false;
    }
    else
    {
        if (!pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "creator-ready"); })) { cleanup(); return false; }
        galaxy::api::GalaxyID selected;
        int attempts = 0;
        LobbyListListener listed;
        while (std::chrono::steady_clock::now() < deadline && attempts < 6 && !controlIsSet(arguments, "abort"))
        {
            ++attempts;
            listed = LobbyListListener{};
            listed.matchmaking = matchmaking;
            matchmaking->AddRequestLobbyListStringFilter("universelan-behaviour-token", token.c_str(), galaxy::api::LOBBY_COMPARISON_TYPE_EQUAL);
            matchmaking->AddRequestLobbyListResultCountFilter(2);
            matchmaking->RequestLobbyList(false, &listed);
            if (!pumpUntil(arguments, std::min(deadline, std::chrono::steady_clock::now() + std::chrono::seconds(3)), [&] { return listed.called; })) break;
            if (listed.result == galaxy::api::LOBBY_LIST_RESULT_SUCCESS && listed.candidates.size() == 1) { selected = listed.candidates.front(); break; }
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        records.push_back("{\"record\":\"list\",\"result\":" + common::jsonString(listed.called ? listResult(listed.result) : "timeout")
            + ",\"attempts\":" + std::to_string(attempts) + ",\"retryUsed\":" + boolean(attempts > 1)
            + ",\"selectedCount\":" + std::to_string(listed.candidates.size()) + ",\"selectedValid\":" + boolean(selected.IsValid()) + "}");
        if (!selected.IsValid() || listed.candidates.size() != 1) { cleanup(); return false; }
        LobbyEnteredListener entered;
        matchmaking->JoinLobby(selected, &entered);
        const bool enterCompleted = pumpUntil(arguments, deadline, [&] { return entered.called; });
        records.push_back("{\"record\":\"join\",\"result\":" + common::jsonString(enterCompleted ? enterResult(entered.result) : "timeout")
            + ",\"sameListedLobby\":" + boolean(enterCompleted && entered.lobby == selected) + "}");
        if (!enterCompleted || entered.result != galaxy::api::LOBBY_ENTER_RESULT_SUCCESS || entered.lobby != selected) { cleanup(); return false; }
        lobby = entered.lobby; joined = true;
        records.push_back(snapshotRecord("joiner-two-member-snapshot", matchmaking, lobby, self, 2));
        writeEvent(arguments, "joiner-joined");
        if (dataPropagation)
        {
            LobbyDataPropagationListener observer;
            observer.arguments = &arguments;
            observer.matchmaking = matchmaking;
            observer.expectedLobby = lobby;
            observer.key = propagationKey;
            observer.expectedValue = propagationValue.c_str();
            writeEvent(arguments, "observer-armed");
            const bool callbackObserved = pumpUntil(arguments, deadline, [&] { return observer.targetCallbackCount > 0; });
            for (int pump = 0; pump < 10 && std::chrono::steady_clock::now() < deadline; ++pump)
            {
                galaxy::api::ProcessData();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            std::array<char, 256> copied{};
            matchmaking->GetLobbyDataCopy(lobby, propagationKey, copied.data(), static_cast<std::uint32_t>(copied.size()));
            const bool eventualCopyVisible = copied.data() == propagationValue;
            records.push_back("{\"record\":\"joiner-lobby-data\",\"callbackAvailable\":" + boolean(callbackObserved)
                + ",\"callbackCount\":" + std::to_string(observer.targetCallbackCount)
                + ",\"duplicateNotifications\":" + boolean(observer.targetCallbackCount > 1)
                + ",\"memberIdValid\":" + boolean(observer.memberIdValid)
                + ",\"sameCallbackCopyVisible\":" + boolean(observer.copyVisibleInCallback)
                + ",\"eventualCopyVisible\":" + boolean(eventualCopyVisible) + "}");
            writeEvent(arguments, "joiner-data-observed");
            if (!callbackObserved || !eventualCopyVisible
                || !pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "creator-data-update-complete"); })) { cleanup(); return false; }
            completed = leaveLobby(arguments, matchmaking, lobby, records, "joiner-leave", deadline);
            joined = false;
            writeEvent(arguments, "joiner-left");
            writeEvent(arguments, "cleanup-ack");
            return completed;
        }
        if (!pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "creator-two-member"); })) { cleanup(); return false; }
        completed = leaveLobby(arguments, matchmaking, lobby, records, "joiner-leave", deadline);
        joined = false;
        writeEvent(arguments, "joiner-left");
    }
    writeEvent(arguments, "cleanup-ack");
    return completed;
}

struct TaggedLobbyCreatedListener final : galaxy::api::ILobbyCreatedListener
{
    const char* symbol = nullptr;
    std::vector<std::string>* order = nullptr;
    bool called = false;
    galaxy::api::GalaxyID lobby;
    galaxy::api::LobbyCreateResult result = galaxy::api::LOBBY_CREATE_RESULT_ERROR;
    void OnLobbyCreated(const galaxy::api::GalaxyID& id, const galaxy::api::LobbyCreateResult callbackResult) override
    {
        called = true; lobby = id; result = callbackResult; order->push_back(symbol);
    }
};

struct TaggedLobbyEnteredListener final : galaxy::api::ILobbyEnteredListener
{
    const char* symbol = nullptr;
    std::vector<std::string>* order = nullptr;
    bool called = false;
    galaxy::api::GalaxyID lobby;
    galaxy::api::LobbyEnterResult result = galaxy::api::LOBBY_ENTER_RESULT_ERROR;
    void OnLobbyEntered(const galaxy::api::GalaxyID& id, const galaxy::api::LobbyEnterResult callbackResult) override
    {
        called = true; lobby = id; result = callbackResult; order->push_back(symbol);
    }
};

struct TaggedLobbyDataUpdateListener final : galaxy::api::ILobbyDataUpdateListener
{
    const char* symbol = nullptr;
    std::vector<std::string>* order = nullptr;
    bool called = false;
    bool success = false;
    galaxy::api::GalaxyID lobby;
    void OnLobbyDataUpdateSuccess(const galaxy::api::GalaxyID& id) override
    {
        called = true; success = true; lobby = id; order->push_back(symbol);
    }
    void OnLobbyDataUpdateFailure(const galaxy::api::GalaxyID& id, const FailureReason) override
    {
        called = true; lobby = id; order->push_back(symbol);
    }
};

std::string symbolicOrder(const std::vector<std::string>& order)
{
    std::string result = "[";
    for (std::size_t index = 0; index < order.size(); ++index)
    {
        if (index != 0) result += ',';
        result += common::jsonString(order[index]);
    }
    return result + "]";
}

struct MultipleLobbyMessageListener final : galaxy::api::GlobalLobbyMessageListener
{
    galaxy::api::IMatchmaking* matchmaking = nullptr;
    std::array<galaxy::api::GalaxyID, 2> lobbies;
    std::array<std::string, 2> expectedMessages;
    std::array<galaxy::api::GalaxyID, 2> expectedSenders;
    std::vector<std::string> callbackOrder;
    std::array<int, 2> callbackCount{};
    bool allReadsInsideCallbacks = true;
    bool allSendersMatch = true;
    bool allPayloadsMatch = true;
    bool onlyKnownLobbies = true;

    void OnLobbyMessageReceived(const galaxy::api::GalaxyID& lobby, const galaxy::api::GalaxyID& sender,
        const std::uint32_t messageID, const std::uint32_t messageLength) override
    {
        int index = -1;
        for (int candidate = 0; candidate < 2; ++candidate)
            if (lobbies[candidate] == lobby) { index = candidate; break; }
        if (index < 0) { onlyKnownLobbies = false; return; }
        callbackOrder.push_back(index == 0 ? "L0" : "L1");
        ++callbackCount[index];
        if (messageLength > 4096) { allPayloadsMatch = false; return; }
        std::array<char, 4097> message{};
        galaxy::api::GalaxyID receivedSender;
        const std::uint32_t read = matchmaking->GetLobbyMessage(lobby, messageID, receivedSender, message.data(), static_cast<std::uint32_t>(message.size()));
        allSendersMatch = allSendersMatch && sender == expectedSenders[index] && receivedSender == expectedSenders[index];
        allPayloadsMatch = allPayloadsMatch && read == expectedMessages[index].size()
            && std::string(message.data(), read) == expectedMessages[index];
    }
};

bool leaveMultipleLobbies(const Arguments& arguments, galaxy::api::IMatchmaking* const matchmaking,
    const std::array<galaxy::api::GalaxyID, 2>& lobbies, const std::array<bool, 2>& joined,
    std::vector<std::string>& records, const char* const role, const std::chrono::steady_clock::time_point deadline)
{
    bool complete = true;
    for (int index = 1; index >= 0; --index)
    {
        if (!joined[index]) continue;
        const std::string record = std::string(role) + "-leave-" + (index == 0 ? "L0" : "L1");
        complete = leaveLobby(arguments, matchmaking, lobbies[index], records, record.c_str(), deadline) && complete;
    }
    return complete;
}

bool runMultipleLobbyMembershipAndMessageIsolation(const Arguments& arguments, galaxy::api::IUser* const user, std::vector<std::string>& records)
{
    galaxy::api::IMatchmaking* const matchmaking = galaxy::api::Matchmaking();
    const std::string token = controlValue(arguments.control, "token");
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(arguments.timeoutSeconds);
    if (matchmaking == nullptr || token.empty()) { writeEvent(arguments, "cleanup-ack"); return false; }
    const bool creator = arguments.profile == "user1";
    const galaxy::api::GalaxyID self = user->GetGalaxyID();
    std::array<galaxy::api::GalaxyID, 2> lobbies;
    std::array<bool, 2> joined{};
    auto cleanup = [&]
    {
        leaveMultipleLobbies(arguments, matchmaking, lobbies, joined, records, creator ? "creator" : "joiner", deadline);
        writeEvent(arguments, "cleanup-ack");
    };
    const std::array<std::string, 2> tagValues{token + "-L0", token + "-L1"};
    const std::array<std::string, 2> messages{token + "-message-L0", token + "-message-L1"};
    if (creator)
    {
        std::vector<std::string> createdOrder;
        std::vector<std::string> enteredOrder;
        std::array<TaggedLobbyCreatedListener, 2> created{};
        std::array<TaggedLobbyEnteredListener, 2> entered{};
        for (int index = 0; index < 2; ++index)
        {
            created[index].symbol = index == 0 ? "L0" : "L1"; created[index].order = &createdOrder;
            entered[index].symbol = index == 0 ? "L0" : "L1"; entered[index].order = &enteredOrder;
        }
        // These two requests are intentionally adjacent: no ProcessData call may serialize them.
        matchmaking->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 2, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM, &created[0], &entered[0]);
        matchmaking->CreateLobby(galaxy::api::LOBBY_TYPE_PUBLIC, 2, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM, &created[1], &entered[1]);
        const bool callbacks = pumpUntil(arguments, deadline, [&] { return created[0].called && created[1].called && entered[0].called && entered[1].called; });
        records.push_back("{\"record\":\"create-pair\",\"issuedBackToBack\":true,\"createdCallbackOrder\":" + symbolicOrder(createdOrder)
            + ",\"enteredCallbackOrder\":" + symbolicOrder(enteredOrder) + ",\"L0Success\":"
            + boolean(callbacks && created[0].result == galaxy::api::LOBBY_CREATE_RESULT_SUCCESS && entered[0].result == galaxy::api::LOBBY_ENTER_RESULT_SUCCESS)
            + ",\"L1Success\":" + boolean(callbacks && created[1].result == galaxy::api::LOBBY_CREATE_RESULT_SUCCESS && entered[1].result == galaxy::api::LOBBY_ENTER_RESULT_SUCCESS)
            + ",\"createdEnteredIdentity\":" + boolean(callbacks && created[0].lobby == entered[0].lobby && created[1].lobby == entered[1].lobby)
            + ",\"distinctLobbies\":" + boolean(callbacks && created[0].lobby != created[1].lobby) + "}");
        if (!callbacks || created[0].result != galaxy::api::LOBBY_CREATE_RESULT_SUCCESS || created[1].result != galaxy::api::LOBBY_CREATE_RESULT_SUCCESS
            || entered[0].result != galaxy::api::LOBBY_ENTER_RESULT_SUCCESS || entered[1].result != galaxy::api::LOBBY_ENTER_RESULT_SUCCESS
            || created[0].lobby != entered[0].lobby || created[1].lobby != entered[1].lobby || created[0].lobby == created[1].lobby) { cleanup(); return false; }
        for (int index = 0; index < 2; ++index) { lobbies[index] = entered[index].lobby; joined[index] = true; }

        std::vector<std::string> setupOrder;
        std::array<TaggedLobbyDataUpdateListener, 6> setup{};
        for (int index = 0; index < 6; ++index) { setup[index].symbol = index < 3 ? "L0" : "L1"; setup[index].order = &setupOrder; }
        for (int index = 0; index < 2; ++index)
        {
            const int offset = index * 3;
            matchmaking->SetLobbyType(lobbies[index], galaxy::api::LOBBY_TYPE_PUBLIC, &setup[offset]);
            matchmaking->SetLobbyJoinable(lobbies[index], true, &setup[offset + 1]);
            matchmaking->SetMaxNumLobbyMembers(lobbies[index], 2, &setup[offset + 2]);
        }
        const bool setupComplete = pumpUntil(arguments, deadline, [&] {
            return std::all_of(setup.begin(), setup.end(), [](const TaggedLobbyDataUpdateListener& listener) { return listener.called; });
        });
        bool setupSuccess = setupComplete;
        for (int index = 0; index < 6; ++index) setupSuccess = setupSuccess && setup[index].success && setup[index].lobby == lobbies[index / 3];
        const bool publicVisible = matchmaking->GetLobbyType(lobbies[0]) == galaxy::api::LOBBY_TYPE_PUBLIC && matchmaking->GetLobbyType(lobbies[1]) == galaxy::api::LOBBY_TYPE_PUBLIC;
        const bool joinableVisible = matchmaking->IsLobbyJoinable(lobbies[0]) && matchmaking->IsLobbyJoinable(lobbies[1]);
        const bool capacityVisible = matchmaking->GetMaxNumLobbyMembers(lobbies[0]) == 2 && matchmaking->GetMaxNumLobbyMembers(lobbies[1]) == 2;
        records.push_back("{\"record\":\"explicit-configuration\",\"callbackOrder\":" + symbolicOrder(setupOrder)
            + ",\"allSetOperationsSucceeded\":" + boolean(setupSuccess) + ",\"publicVisible\":" + boolean(publicVisible)
            + ",\"joinableVisible\":" + boolean(joinableVisible) + ",\"capacityVisible\":" + boolean(capacityVisible) + "}");
        if (!setupSuccess || !publicVisible || !joinableVisible || !capacityVisible) { cleanup(); return false; }

        std::array<LobbyDataUpdateListener, 2> tags;
        matchmaking->SetLobbyData(lobbies[0], "universelan-behaviour-multi-lobby-token", tagValues[0].c_str(), &tags[0]);
        matchmaking->SetLobbyData(lobbies[1], "universelan-behaviour-multi-lobby-token", tagValues[1].c_str(), &tags[1]);
        const bool tagsComplete = pumpUntil(arguments, deadline, [&] { return tags[0].called && tags[1].called; });
        records.push_back("{\"record\":\"private-tags\",\"L0Success\":" + boolean(tagsComplete && tags[0].success && tags[0].lobby == lobbies[0])
            + ",\"L1Success\":" + boolean(tagsComplete && tags[1].success && tags[1].lobby == lobbies[1]) + "}");
        if (!tagsComplete || !tags[0].success || !tags[1].success || tags[0].lobby != lobbies[0] || tags[1].lobby != lobbies[1]) { cleanup(); return false; }
        MultipleLobbyMessageListener listener;
        listener.matchmaking = matchmaking; listener.lobbies = lobbies; listener.expectedMessages = messages; listener.expectedSenders = {self, self};
        writeEvent(arguments, "creator-ready");
        if (!pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "observer-armed"); })) { cleanup(); return false; }
        const bool sentL0 = matchmaking->SendLobbyMessage(lobbies[0], messages[0].data(), static_cast<std::uint32_t>(messages[0].size()));
        const bool sentL1 = matchmaking->SendLobbyMessage(lobbies[1], messages[1].data(), static_cast<std::uint32_t>(messages[1].size()));
        const bool received = pumpUntil(arguments, deadline, [&] { return listener.callbackCount[0] >= 1 && listener.callbackCount[1] >= 1; });
        records.push_back("{\"record\":\"creator-messages\",\"issuedBackToBack\":true,\"L0Scheduled\":" + boolean(sentL0)
            + ",\"L1Scheduled\":" + boolean(sentL1) + ",\"callbackOrder\":" + symbolicOrder(listener.callbackOrder)
            + ",\"L0Delivered\":" + boolean(listener.callbackCount[0] == 1) + ",\"L1Delivered\":" + boolean(listener.callbackCount[1] == 1)
            + ",\"senderMatches\":" + boolean(listener.allSendersMatch) + ",\"payloadMatches\":" + boolean(listener.allPayloadsMatch)
            + ",\"onlyKnownLobbies\":" + boolean(listener.onlyKnownLobbies) + ",\"publicMessageTypeAvailable\":false}");
        writeEvent(arguments, "creator-data-update-complete");
        if (!sentL0 || !sentL1 || !received || listener.callbackCount[0] != 1 || listener.callbackCount[1] != 1 || !listener.allSendersMatch || !listener.allPayloadsMatch || !listener.onlyKnownLobbies
            || !pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "joiner-data-observed"); })) { cleanup(); return false; }
        const bool left = leaveMultipleLobbies(arguments, matchmaking, lobbies, joined, records, "creator", deadline);
        joined = {};
        writeEvent(arguments, "cleanup-ack");
        return left;
    }

    if (!pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "creator-ready"); })) { cleanup(); return false; }
    std::array<galaxy::api::GalaxyID, 2> selected;
    std::array<int, 2> attempts{};
    for (int target = 0; target < 2; ++target)
    {
        LobbyListListener listed;
        while (std::chrono::steady_clock::now() < deadline && attempts[target] < 6 && !controlIsSet(arguments, "abort"))
        {
            ++attempts[target]; listed = LobbyListListener{}; listed.matchmaking = matchmaking;
            matchmaking->AddRequestLobbyListStringFilter("universelan-behaviour-multi-lobby-token", tagValues[target].c_str(), galaxy::api::LOBBY_COMPARISON_TYPE_EQUAL);
            matchmaking->AddRequestLobbyListResultCountFilter(2);
            matchmaking->RequestLobbyList(false, &listed);
            if (!pumpUntil(arguments, std::min(deadline, std::chrono::steady_clock::now() + std::chrono::seconds(3)), [&] { return listed.called; })) break;
            if (listed.result == galaxy::api::LOBBY_LIST_RESULT_SUCCESS && listed.candidates.size() == 1) { selected[target] = listed.candidates.front(); break; }
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }
    records.push_back("{\"record\":\"discover-pair\",\"L0Found\":" + boolean(selected[0].IsValid()) + ",\"L1Found\":" + boolean(selected[1].IsValid())
        + ",\"distinctLobbies\":" + boolean(selected[0].IsValid() && selected[1].IsValid() && selected[0] != selected[1])
        + ",\"L0AttemptsBounded\":" + boolean(attempts[0] >= 1 && attempts[0] <= 6) + ",\"L1AttemptsBounded\":" + boolean(attempts[1] >= 1 && attempts[1] <= 6) + "}");
    if (!selected[0].IsValid() || !selected[1].IsValid() || selected[0] == selected[1]) { cleanup(); return false; }
    std::vector<std::string> enteredOrder;
    std::array<TaggedLobbyEnteredListener, 2> entered{};
    for (int index = 0; index < 2; ++index) { entered[index].symbol = index == 0 ? "L0" : "L1"; entered[index].order = &enteredOrder; }
    // The requested parallel join operation is intentionally issued without a ProcessData call between requests.
    matchmaking->JoinLobby(selected[0], &entered[0]);
    matchmaking->JoinLobby(selected[1], &entered[1]);
    const bool joinedCallbacks = pumpUntil(arguments, deadline, [&] { return entered[0].called && entered[1].called; });
    records.push_back("{\"record\":\"join-pair\",\"issuedBackToBack\":true,\"enteredCallbackOrder\":" + symbolicOrder(enteredOrder)
        + ",\"L0Success\":" + boolean(joinedCallbacks && entered[0].result == galaxy::api::LOBBY_ENTER_RESULT_SUCCESS && entered[0].lobby == selected[0])
        + ",\"L1Success\":" + boolean(joinedCallbacks && entered[1].result == galaxy::api::LOBBY_ENTER_RESULT_SUCCESS && entered[1].lobby == selected[1]) + "}");
    if (!joinedCallbacks || entered[0].result != galaxy::api::LOBBY_ENTER_RESULT_SUCCESS || entered[1].result != galaxy::api::LOBBY_ENTER_RESULT_SUCCESS
        || entered[0].lobby != selected[0] || entered[1].lobby != selected[1]) { cleanup(); return false; }
    for (int index = 0; index < 2; ++index) { lobbies[index] = entered[index].lobby; joined[index] = true; }
    const bool configurationVisible = matchmaking->GetLobbyType(lobbies[0]) == galaxy::api::LOBBY_TYPE_PUBLIC && matchmaking->GetLobbyType(lobbies[1]) == galaxy::api::LOBBY_TYPE_PUBLIC
        && matchmaking->IsLobbyJoinable(lobbies[0]) && matchmaking->IsLobbyJoinable(lobbies[1])
        && matchmaking->GetMaxNumLobbyMembers(lobbies[0]) == 2 && matchmaking->GetMaxNumLobbyMembers(lobbies[1]) == 2;
    records.push_back("{\"record\":\"joiner-configuration\",\"publicJoinableCapacityVisible\":" + boolean(configurationVisible) + "}");
    if (!configurationVisible) { cleanup(); return false; }
    MultipleLobbyMessageListener listener;
    listener.matchmaking = matchmaking; listener.lobbies = lobbies; listener.expectedMessages = messages;
    listener.expectedSenders = {matchmaking->GetLobbyOwner(lobbies[0]), matchmaking->GetLobbyOwner(lobbies[1])};
    writeEvent(arguments, "observer-armed");
    const bool received = pumpUntil(arguments, deadline, [&] { return listener.callbackCount[0] >= 1 && listener.callbackCount[1] >= 1; });
    records.push_back("{\"record\":\"joiner-messages\",\"listenerArmedBeforeSends\":true,\"callbackOrder\":" + symbolicOrder(listener.callbackOrder)
        + ",\"L0Delivered\":" + boolean(listener.callbackCount[0] == 1) + ",\"L1Delivered\":" + boolean(listener.callbackCount[1] == 1)
        + ",\"senderMatches\":" + boolean(listener.allSendersMatch) + ",\"payloadMatches\":" + boolean(listener.allPayloadsMatch)
        + ",\"onlyKnownLobbies\":" + boolean(listener.onlyKnownLobbies) + ",\"publicMessageTypeAvailable\":false}");
    writeEvent(arguments, "joiner-data-observed");
    if (!received || listener.callbackCount[0] != 1 || listener.callbackCount[1] != 1 || !listener.allSendersMatch || !listener.allPayloadsMatch || !listener.onlyKnownLobbies
        || !pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "creator-data-update-complete"); })) { cleanup(); return false; }
    const bool left = leaveMultipleLobbies(arguments, matchmaking, lobbies, joined, records, "joiner", deadline);
    joined = {};
    writeEvent(arguments, "joiner-left");
    writeEvent(arguments, "cleanup-ack");
    return left;
}

struct ChatRoomRetrieveListener final : galaxy::api::IChatRoomWithUserRetrieveListener
{
    int terminalCount = 0;
    int successCount = 0;
    int failureCount = 0;
    galaxy::api::GalaxyID expectedPeer;
    bool callbackPeerMatchesRequested = false;
    galaxy::api::ChatRoomID room = 0;

    void OnChatRoomWithUserRetrieveSuccess(const galaxy::api::GalaxyID user, const galaxy::api::ChatRoomID chatRoom) override
    {
        ++terminalCount;
        ++successCount;
        callbackPeerMatchesRequested = callbackPeerMatchesRequested || user == expectedPeer;
        room = chatRoom;
    }
    void OnChatRoomWithUserRetrieveFailure(const galaxy::api::GalaxyID, const FailureReason) override
    {
        ++terminalCount;
        ++failureCount;
    }
};

struct ChatSendListener final : galaxy::api::IChatRoomMessageSendListener
{
    int terminalCount = 0;
    int successCount = 0;
    int failureCount = 0;
    galaxy::api::ChatRoomID expectedRoom = 0;
    std::uint32_t expectedIndex = 0;
    bool sameRoom = false;
    bool sameSendIndex = false;

    void OnChatRoomMessageSendSuccess(const galaxy::api::ChatRoomID room, const std::uint32_t index, const galaxy::api::ChatMessageID, const std::uint32_t) override
    {
        ++terminalCount;
        ++successCount;
        sameRoom = sameRoom || room == expectedRoom;
        sameSendIndex = sameSendIndex || index == expectedIndex;
    }
    void OnChatRoomMessageSendFailure(const galaxy::api::ChatRoomID room, const std::uint32_t index, const FailureReason) override
    {
        ++terminalCount;
        ++failureCount;
        sameRoom = sameRoom || room == expectedRoom;
        sameSendIndex = sameSendIndex || index == expectedIndex;
    }
};

struct ChatMessagesListener final : galaxy::api::GlobalChatRoomMessagesListener
{
    galaxy::api::IChat* chat = nullptr;
    galaxy::api::GalaxyID expectedSender;
    std::string expectedToken;
    int callbackCount = 0;
    bool messageCountOne = false;
    bool readInsideCallback = false;
    bool callbackRoomValid = false;
    bool senderMatchesExpectedPeer = false;
    bool messageTypeChat = false;
    bool payloadMatchesExpectedToken = false;

    void OnChatRoomMessagesReceived(const galaxy::api::ChatRoomID room, const std::uint32_t count, const std::uint32_t longest) override
    {
        ++callbackCount;
        messageCountOne = messageCountOne || count == 1;
        callbackRoomValid = callbackRoomValid || room != 0;
        if (chat == nullptr || count != 1 || longest > 4096) return;
        std::vector<char> buffer(std::max<std::size_t>(longest, expectedToken.size()) + 1, '\0');
        galaxy::api::ChatMessageID messageID = 0;
        galaxy::api::ChatMessageType type = galaxy::api::CHAT_MESSAGE_TYPE_UNKNOWN;
        galaxy::api::GalaxyID sender;
        std::uint32_t sendTime = 0;
        const std::uint32_t length = chat->GetChatRoomMessageByIndex(0, messageID, type, sender, sendTime, buffer.data(), static_cast<std::uint32_t>(buffer.size()));
        readInsideCallback = true;
        senderMatchesExpectedPeer = senderMatchesExpectedPeer || sender == expectedSender;
        messageTypeChat = messageTypeChat || type == galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE;
        payloadMatchesExpectedToken = payloadMatchesExpectedToken
            || (length == expectedToken.size() && std::string(buffer.data(), length) == expectedToken);
    }
};

bool runChatRoomMessageDelivery(const Arguments& arguments, galaxy::api::IUser* const user, std::vector<std::string>& records)
{
    galaxy::api::IChat* const chat = galaxy::api::Chat();
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(arguments.timeoutSeconds);
    const galaxy::api::GalaxyID self = user->GetGalaxyID();
    if (chat == nullptr || !self.IsValid() || self.GetIDType() != galaxy::api::GalaxyID::ID_TYPE_USER) return false;

    if (!writeOneTimeRelay(arguments, "self-id-relay", std::to_string(self.ToUint64()))) return false;
    if (arguments.profile == "user2")
    {
        ChatMessagesListener listener;
        listener.chat = chat;
        writeEvent(arguments, "receiver-listener-registered");
        bool relayError = false;
        const std::string peerRelay = pumpUntil(arguments, deadline, [&] {
            std::string candidate;
            if (!consumeOneTimeRelay(arguments, "peer-id-relay", candidate)) { relayError = true; return true; }
            if (candidate.empty()) return false;
            return galaxyIDFromRelay(candidate, listener.expectedSender);
        }) && !relayError ? "consumed" : "unavailable";
        if (!consumeOneTimeRelay(arguments, "expected-token-relay", listener.expectedToken)) return false;
        const bool listenerArmed = peerRelay == "consumed" && !listener.expectedToken.empty();
        records.push_back("{\"record\":\"chat-listener-armed\",\"listenerRegistered\":" + boolean(true)
            + ",\"peerRelayConsumed\":" + boolean(peerRelay == "consumed") + ",\"tokenRelayConsumed\":" + boolean(!listener.expectedToken.empty()) + "}");
        if (!listenerArmed) return false;
        writeEvent(arguments, "receiver-armed");
        const bool received = pumpUntil(arguments, deadline, [&] { return listener.callbackCount > 0; });
        records.push_back("{\"record\":\"chat-message-received\",\"callbackCount\":" + std::to_string(listener.callbackCount)
            + ",\"messageCountOne\":" + boolean(listener.messageCountOne) + ",\"readInsideCallback\":" + boolean(listener.readInsideCallback)
            + ",\"callbackRoomValid\":" + boolean(listener.callbackRoomValid) + ",\"senderMatchesExpectedPeer\":" + boolean(listener.senderMatchesExpectedPeer)
            + ",\"messageTypeChat\":" + boolean(listener.messageTypeChat) + ",\"payloadMatchesExpectedToken\":" + boolean(listener.payloadMatchesExpectedToken) + "}");
        return received && listener.callbackCount == 1 && listener.messageCountOne && listener.readInsideCallback && listener.callbackRoomValid
            && listener.senderMatchesExpectedPeer && listener.messageTypeChat && listener.payloadMatchesExpectedToken;
    }

    if (!pumpUntil(arguments, deadline, [&] { return controlIsSet(arguments, "receiver-armed"); })) return false;
    galaxy::api::GalaxyID peer;
    bool relayError = false;
    const bool peerAvailable = pumpUntil(arguments, deadline, [&] {
        std::string candidate;
        if (!consumeOneTimeRelay(arguments, "peer-id-relay", candidate)) { relayError = true; return true; }
        return !candidate.empty() && galaxyIDFromRelay(candidate, peer);
    }) && !relayError;
    std::string token;
    if (!consumeOneTimeRelay(arguments, "expected-token-relay", token)) return false;
    records.push_back("{\"record\":\"chat-room-request-issued\",\"receiverArmed\":true,\"peerRelayConsumed\":"
        + boolean(peerAvailable) + ",\"tokenRelayConsumed\":" + boolean(!token.empty()) + "}");
    if (!peerAvailable || token.empty()) return false;
    ChatRoomRetrieveListener retrieve;
    retrieve.expectedPeer = peer;
    chat->RequestChatRoomWithUser(peer, &retrieve);
    const bool roomTerminal = pumpUntil(arguments, deadline, [&] { return retrieve.terminalCount > 0; });
    records.push_back("{\"record\":\"chat-room-retrieve\",\"terminalCount\":" + std::to_string(retrieve.terminalCount)
        + ",\"successCount\":" + std::to_string(retrieve.successCount) + ",\"failureCount\":" + std::to_string(retrieve.failureCount)
        + ",\"callbackPeerMatchesRequested\":" + boolean(retrieve.callbackPeerMatchesRequested) + ",\"roomValid\":" + boolean(retrieve.room != 0) + "}");
    if (!roomTerminal || retrieve.terminalCount != 1 || retrieve.successCount != 1 || retrieve.failureCount != 0
        || !retrieve.callbackPeerMatchesRequested || retrieve.room == 0) return false;
    ChatSendListener sent;
    sent.expectedRoom = retrieve.room;
    sent.expectedIndex = chat->SendChatRoomMessage(retrieve.room, token.c_str(), &sent);
    records.push_back("{\"record\":\"chat-send-issued\",\"sendIndexReturned\":true}");
    const bool sendTerminal = pumpUntil(arguments, deadline, [&] { return sent.terminalCount > 0; });
    records.push_back("{\"record\":\"chat-send-terminal\",\"terminalCount\":" + std::to_string(sent.terminalCount)
        + ",\"successCount\":" + std::to_string(sent.successCount) + ",\"failureCount\":" + std::to_string(sent.failureCount)
        + ",\"sameRoom\":" + boolean(sent.sameRoom) + ",\"sameSendIndex\":" + boolean(sent.sameSendIndex) + "}");
    return sendTerminal && sent.terminalCount == 1 && sent.successCount == 1 && sent.failureCount == 0 && sent.sameRoom && sent.sameSendIndex;
}

const char* personaState(const galaxy::api::PersonaState state)
{
    switch (state)
    {
    case galaxy::api::PERSONA_STATE_OFFLINE: return "offline";
    case galaxy::api::PERSONA_STATE_ONLINE: return "online";
    }
    return "unknown";
}

std::string personaChange(const std::uint32_t change)
{
    const bool name = (change & galaxy::api::IPersonaDataChangedListener::PERSONA_CHANGE_NAME) != 0;
    const bool avatar = (change & galaxy::api::IPersonaDataChangedListener::PERSONA_CHANGE_AVATAR) != 0;
    const bool avatarImage = (change & galaxy::api::IPersonaDataChangedListener::PERSONA_CHANGE_AVATAR_DOWNLOADED_IMAGE_ANY) != 0;
    if (name && avatar && avatarImage) return "name-avatar-avatar-image";
    if (name && avatar) return "name-avatar";
    if (name && avatarImage) return "name-avatar-image";
    if (avatar && avatarImage) return "avatar-avatar-image";
    if (name) return "name";
    if (avatar) return "avatar";
    if (avatarImage) return "avatar-image";
    return change == galaxy::api::IPersonaDataChangedListener::PERSONA_CHANGE_NONE ? "none" : "other";
}

struct FriendPersonaDataListener final : galaxy::api::GlobalPersonaDataChangedListener
{
    galaxy::api::GalaxyID peer;
    bool observing = false;
    std::vector<std::string> events;

    void OnPersonaDataChanged(const galaxy::api::GalaxyID user, const std::uint32_t change) override
    {
        if (!observing || user != peer) return;
        events.push_back(std::string("{") + "\"change\":" + common::jsonString(personaChange(change)) + "}");
    }
};

struct FriendInformationListener final : galaxy::api::IUserInformationRetrieveListener
{
    int terminalCount = 0;
    bool success = false;
    bool failure = false;
    galaxy::api::GalaxyID expectedPeer;
    galaxy::api::GalaxyID self;
    bool callbackPeerEqualsRequested = false;
    bool callbackPeerValidNonSelf = false;

    void OnUserInformationRetrieveSuccess(const galaxy::api::GalaxyID user) override
    {
        ++terminalCount;
        success = true;
        callbackPeerEqualsRequested = callbackPeerEqualsRequested || user == expectedPeer;
        callbackPeerValidNonSelf = callbackPeerValidNonSelf || (user.IsValid()
            && user.GetIDType() == galaxy::api::GalaxyID::ID_TYPE_USER && user != self);
    }
    void OnUserInformationRetrieveFailure(const galaxy::api::GalaxyID user, const FailureReason) override
    {
        ++terminalCount;
        failure = true;
        callbackPeerEqualsRequested = callbackPeerEqualsRequested || user == expectedPeer;
        callbackPeerValidNonSelf = callbackPeerValidNonSelf || (user.IsValid()
            && user.GetIDType() == galaxy::api::GalaxyID::ID_TYPE_USER && user != self);
    }
};

std::string orderedPersonaEvents(const std::vector<std::string>& events)
{
    std::string result = "[";
    for (std::size_t index = 0; index < events.size(); ++index)
    {
        if (index != 0) result += ',';
        result += events[index];
    }
    return result + "]";
}

bool runFriendsPeerInformationRetrieval(const Arguments& arguments, galaxy::api::IUser* const user, std::vector<std::string>& records)
{
    galaxy::api::IFriends* const friends = galaxy::api::Friends();
    const galaxy::api::GalaxyID self = user->GetGalaxyID();
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(arguments.timeoutSeconds);
    if (friends == nullptr || !self.IsValid() || self.GetIDType() != galaxy::api::GalaxyID::ID_TYPE_USER) return false;

    FriendPersonaDataListener personaListener;
    writeEvent(arguments, "persona-listener-registered");
    if (!writeOneTimeRelay(arguments, "self-id-relay", std::to_string(self.ToUint64()))) return false;
    galaxy::api::GalaxyID peer;
    bool relayError = false;
    const bool peerRelayConsumed = pumpUntil(arguments, deadline, [&] {
        std::string candidate;
        if (!consumeOneTimeRelay(arguments, "peer-id-relay", candidate)) { relayError = true; return true; }
        return !candidate.empty() && galaxyIDFromRelay(candidate, peer);
    }) && !relayError;
    records.push_back("{\"record\":\"persona-listener-armed\",\"listenerRegistered\":true,\"peerRelayConsumed\":"
        + boolean(peerRelayConsumed) + "}");
    if (!peerRelayConsumed || peer == self) return false;

    personaListener.peer = peer;
    personaListener.observing = true;
    FriendInformationListener retrieve;
    retrieve.expectedPeer = peer;
    retrieve.self = self;
    friends->RequestUserInformation(peer, galaxy::api::AVATAR_TYPE_NONE, &retrieve);
    records.push_back("{\"record\":\"user-information-request-issued\",\"avatarCriteria\":\"none\"}");
    const bool terminal = pumpUntil(arguments, deadline, [&] { return retrieve.terminalCount > 0; });
    std::array<char, 256> name{};
    if (terminal) friends->GetFriendPersonaNameCopy(peer, name.data(), static_cast<std::uint32_t>(name.size()));
    const bool available = terminal && friends->IsUserInformationAvailable(peer);
    const char* const state = terminal ? personaState(friends->GetFriendPersonaState(peer)) : "unavailable";
    records.push_back("{\"record\":\"user-information-terminal\",\"outcome\":"
        + common::jsonString(!terminal ? "timeout" : (retrieve.success && !retrieve.failure ? "success" : "failure"))
        + ",\"callbackPeerEqualsRequested\":" + boolean(retrieve.callbackPeerEqualsRequested)
        + ",\"callbackPeerValidNonSelf\":" + boolean(retrieve.callbackPeerValidNonSelf)
        + ",\"informationAvailableAfterTerminal\":" + boolean(available)
        + ",\"personaNameNonempty\":" + boolean(terminal && name[0] != '\0')
        + ",\"personaState\":" + common::jsonString(state) + "}");
    for (int pump = 0; pump < 10 && std::chrono::steady_clock::now() < deadline && !controlIsSet(arguments, "abort"); ++pump)
    {
        galaxy::api::ProcessData();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    records.push_back("{\"record\":\"global-persona-data-changed\",\"events\":" + orderedPersonaEvents(personaListener.events) + "}");
    // Emit the complete public terminal observation in both lanes; the strict runner normalizer decides compatibility.
    return terminal && retrieve.terminalCount == 1 && retrieve.success && !retrieve.failure;
}
}

int run(const Arguments& arguments)
{
    const Scenario scenario = selectedScenario(arguments);
    std::vector<std::string> records;
    const char* login = nullptr;
    const char* password = nullptr;
    if constexpr (credentials::available)
    {
        login = arguments.profile == "user1" ? credentials::user1Name : credentials::user2Name;
        password = arguments.profile == "user1" ? credentials::user1Password : credentials::user2Password;
    }
    else
    {
        records.push_back("{\"record\":\"initialize\",\"result\":\"credentials-unavailable\"}");
        common::writeTrace(arguments.trace, records);
        return 4;
    }

    bool initialized = false;
    try
    {
        galaxy::api::Init(galaxy::api::InitOptions{credentials::clientId, credentials::clientSecret, "."});
        initialized = true;
        records.push_back("{\"record\":\"initialize\",\"result\":\"returned\"}");
        galaxy::api::IUser* const user = galaxy::api::User();
        if (user == nullptr)
        {
            records.push_back("{\"record\":\"sign-in-callback\",\"result\":\"unavailable\"}");
            records.push_back("{\"record\":\"sign-in-terminal\",\"result\":\"unavailable\"}");
            records.push_back(selfStateRecord(nullptr));
            common::writeTrace(arguments.trace, records);
            galaxy::api::Shutdown();
            return 1;
        }

        AuthListener listener;
        std::unique_ptr<GogServicesStateListener> servicesStateListener;
        if (scenario == Scenario::gogServicesStateCharacterization)
            servicesStateListener = std::make_unique<GogServicesStateListener>(listener);
        user->SignInCredentials(login, password, &listener);
        const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(arguments.timeoutSeconds);
        while (listener.outcome == AuthListener::Outcome::pending && std::chrono::steady_clock::now() < deadline)
        {
            galaxy::api::ProcessData();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::string servicesState;
        if (listener.outcome == AuthListener::Outcome::success)
        {
            records.push_back("{\"record\":\"sign-in-callback\",\"result\":\"success\"}");
            records.push_back("{\"record\":\"sign-in-terminal\",\"result\":\"success\"}");
            if (scenario == Scenario::publicLobbyCreateListJoinLeave || scenario == Scenario::publicLobbyDataPropagationCharacterization
                || scenario == Scenario::publicLobbyDataPropagation)
            {
                const bool lobbySucceeded = runPublicLobby(arguments, user, records);
                records.push_back(selfStateRecord(user));
                common::writeTrace(arguments.trace, records);
                galaxy::api::Shutdown();
                return lobbySucceeded ? 0 : 1;
            }
            if (scenario == Scenario::multipleLobbyMembershipAndMessageIsolationCharacterization
                || scenario == Scenario::multipleLobbyMembershipAndMessageIsolation)
            {
                const bool lobbySucceeded = runMultipleLobbyMembershipAndMessageIsolation(arguments, user, records);
                records.push_back(selfStateRecord(user));
                common::writeTrace(arguments.trace, records);
                galaxy::api::Shutdown();
                return lobbySucceeded ? 0 : 1;
            }
            if (scenario == Scenario::chatRoomMessageDeliveryCharacterization || scenario == Scenario::chatRoomMessageDelivery)
            {
                const bool chatSucceeded = runChatRoomMessageDelivery(arguments, user, records);
                records.push_back(selfStateRecord(user));
                common::writeTrace(arguments.trace, records);
                galaxy::api::Shutdown();
                return chatSucceeded ? 0 : 1;
            }
            if (scenario == Scenario::friendsPeerInformationRetrievalCharacterization || scenario == Scenario::friendsPeerInformationRetrieval)
            {
                const bool friendsSucceeded = runFriendsPeerInformationRetrieval(arguments, user, records);
                records.push_back(selfStateRecord(user));
                common::writeTrace(arguments.trace, records);
                galaxy::api::Shutdown();
                return friendsSucceeded ? 0 : 1;
            }
            if (scenario == Scenario::sessionIdRepeatability)
            {
                // Keep the public session-ID calls adjacent and retain only their equality relation.
                const galaxy::api::SessionID first = user->GetSessionID();
                const galaxy::api::SessionID second = user->GetSessionID();
                records.push_back("{\"record\":\"session-id-repeatability\",\"equal\":" + boolean(first == second) + "}");
            }
            // This public query is intentionally made before any further ProcessData call.
            if (scenario == Scenario::gogServicesState)
                servicesState = gogServicesState(galaxy::api::Utils()->GetGogServicesConnectionState());
            else if (scenario == Scenario::gogServicesStateCharacterization)
            {
                const char* const immediateState = gogServicesState(galaxy::api::Utils()->GetGogServicesConnectionState());
                galaxy::api::ProcessData();
                const char* const afterOneProcessDataState = gogServicesState(galaxy::api::Utils()->GetGogServicesConnectionState());

                constexpr int settledPumpCount = 10;
                servicesStateListener->settled = true;
                const auto settledStart = std::chrono::steady_clock::now();
                for (int pump = 0; pump < settledPumpCount; ++pump)
                {
                    galaxy::api::ProcessData();
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
                const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - settledStart);
                const char* const settledState = gogServicesState(galaxy::api::Utils()->GetGogServicesConnectionState());
                servicesState = "{\"record\":\"gog-services-state-characterization\",\"immediateState\":"
                    + common::jsonString(immediateState) + ",\"afterOneProcessDataState\":" + common::jsonString(afterOneProcessDataState)
                    + ",\"settledState\":" + common::jsonString(settledState) + ",\"settledPumps\":"
                    + std::to_string(settledPumpCount) + ",\"settledElapsedBucket\":" + common::jsonString(elapsedBucket(elapsed))
                    + ",\"events\":" + gogServicesStateEvents(servicesStateListener->events) + "}";
            }
        }
        else if (listener.outcome == AuthListener::Outcome::failure)
        {
            records.push_back("{\"record\":\"sign-in-callback\",\"result\":\"failure\",\"reason\":" + std::to_string(listener.failureReason) + "}");
            records.push_back("{\"record\":\"sign-in-terminal\",\"result\":\"failure\"}");
        }
        else
        {
            records.push_back("{\"record\":\"sign-in-callback\",\"result\":\"timeout\"}");
            records.push_back("{\"record\":\"sign-in-terminal\",\"result\":\"timeout\"}");
        }
        records.push_back(selfStateRecord(user));
        if (scenario == Scenario::gogServicesState && listener.outcome == AuthListener::Outcome::success)
            records.push_back("{\"record\":\"gog-services-state\",\"state\":" + common::jsonString(servicesState) + "}");
        else if (scenario == Scenario::gogServicesStateCharacterization && listener.outcome == AuthListener::Outcome::success)
            records.push_back(servicesState);
        common::writeTrace(arguments.trace, records);
        const bool successful = listener.outcome == AuthListener::Outcome::success;
        servicesStateListener.reset();
        galaxy::api::Shutdown();
        return successful ? 0 : 1;
    }
    catch (...)
    {
        if (records.empty()) records.push_back("{\"record\":\"initialize\",\"result\":\"exception\"}");
        common::writeTrace(arguments.trace, records);
        if (initialized) galaxy::api::Shutdown();
        return 1;
    }
}
}

int main(int argc, char* argv[])
{
    using namespace universelan::behaviour::host;
    Arguments arguments;
    if (!readArguments(argc, argv, arguments))
    {
        std::cerr << "BEHAVIOUR_TEST FAIL reason=InvalidArguments" << std::endl;
        return 2;
    }
    return run(arguments);
}
