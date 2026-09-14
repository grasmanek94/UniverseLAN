#include "Common/Trace.hxx"

#include <nlohmann/json.hpp>

#include <chrono>
#include <algorithm>
#include <array>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace universelan::behaviour::runner
{
namespace fs = std::filesystem;
using json = nlohmann::json;

namespace
{
struct Arguments
{
    fs::path manifest;
    fs::path universelanHost;
    fs::path gogHost;
    fs::path clientDll;
    fs::path server;
    fs::path gogRuntimeDirectory;
    bool characterizeGogServicesState = false;
    bool characterizeOfficialGogPublicLobbyOwnerCloseLifecycle = false;
    bool characterizeOfficialGogPublicLobbyOwnerOwnershipTransition = false;
    bool characterizeOfficialGogPublicLobbyNotJoinableBehavior = false;
    bool characterizeOfficialGogPublicLobbyFullJoinFailure = false;
    bool characterizePublicLobbyDataPropagation = false;
    bool characterizeMultipleLobbyMembershipAndMessageIsolation = false;
    bool characterizeChatRoomMessageDelivery = false;
    bool characterizeOfficialGogChatRoomMessageDelivery = false;
    bool characterizeOfficialGogFriendsPeerInformationRetrieval = false;
    bool characterizeOfficialGogReliableP2PListenerPeek = false;
};

struct Scenario
{
    const struct ScenarioContract* contract = nullptr;
    std::string laneMode;
    int timeoutSeconds = 0;
    bool acceptsGogServicesStatePair = false;
    bool acceptsFriendsPeerPersonaStatePair = false;
    bool acceptsReliableP2PDeliveryPair = false;
    bool characterization = false;
    std::string requiredTerminalOutcome;
};

struct ScenarioContract
{
    std::string_view name;
    std::string_view hostScenario;
    std::array<std::string_view, 20> records;
    std::size_t recordCount;
    bool observesGogServicesState;
    bool observesSessionIdRepeatability;
    bool observesPublicLobby;
    bool observesPublicLobbyDataPropagation;
    bool observesMultipleLobbyMembership;
    bool observesChatRoomMessageDelivery;
    bool observesFriendsPeerInformation;
    bool observesReliableP2PListenerPeek;
    bool observesPublicLobbyNotJoinableBehavior = false;
};

constexpr std::array scenarioContracts{
    ScenarioContract{"Simple/initialize-and-sign-in", "initialize-and-sign-in",
        {"initialize", "sign-in-callback", "sign-in-terminal", "self-state"}, 4, false, false, false, false, false, false},
    ScenarioContract{"Simple/session-id-repeatability", "session-id-repeatability",
        {"initialize", "sign-in-callback", "sign-in-terminal", "session-id-repeatability", "self-state"}, 5, false, true, false, false, false, false},
    ScenarioContract{"Simple/gog-services-state", "gog-services-state",
        {"initialize", "sign-in-callback", "sign-in-terminal", "self-state", "gog-services-state"}, 5, true, false, false, false, false, false},
    ScenarioContract{"Simple/gog-services-state characterization", "gog-services-state-characterization",
        {"initialize", "sign-in-callback", "sign-in-terminal", "self-state", "gog-services-state-characterization"}, 5, true, false, false, false, false, false},
    ScenarioContract{"Simple/public-lobby-create-list-join-leave", "public-lobby-create-list-join-leave",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "metadata", "list", "join",
            "creator-two-member-snapshot", "joiner-two-member-snapshot", "creator-sole-owner-snapshot", "creator-leave"}, 12, false, false, true, false, false, false},
    ScenarioContract{"Simple/public-lobby-not-joinable-behavior characterization", "public-lobby-not-joinable-behavior-characterization",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "nonjoinable-configuration", "creator-sole-owner-snapshot", "creator-leave",
            "list", "join", "joiner-access", "post-delete-list", "self-state"}, 13, false, false, true, false, false, false, false, false, true},
    ScenarioContract{"Simple/public-lobby-not-joinable-behavior", "public-lobby-not-joinable-behavior",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "nonjoinable-configuration", "creator-sole-owner-snapshot", "creator-leave",
            "list", "joiner-access", "post-delete-list", "self-state"}, 12, false, false, true, false, false, false, false, false, true},
    ScenarioContract{"Simple/public-lobby-full-join-failure characterization", "public-lobby-full-join-failure-characterization",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata", "creator-sole-owner-snapshot", "creator-leave",
            "list", "public-state", "join", "joiner-failure-state", "post-empty-list", "self-state"}, 15, false, false, true, false, false, false},
    ScenarioContract{"Simple/public-lobby-full-join-failure", "public-lobby-full-join-failure",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata", "creator-sole-owner-snapshot", "creator-leave",
            "list", "public-state", "join", "joiner-failure-state", "post-empty-list", "self-state"}, 15, false, false, true, false, false, false},
    ScenarioContract{"Simple/public-lobby-data-propagation characterization", "public-lobby-data-propagation-characterization",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "metadata", "owner-data-update", "list", "join",
            "joiner-two-member-snapshot", "joiner-lobby-data", "creator-sole-owner-snapshot"}, 12, false, false, true, true, false, false},
    ScenarioContract{"Simple/public-lobby-data-propagation", "public-lobby-data-propagation",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "metadata", "owner-data-update", "list", "join",
            "joiner-two-member-snapshot", "joiner-lobby-data", "creator-sole-owner-snapshot"}, 12, false, false, true, true, false, false},
    ScenarioContract{"Advanced/multiple-lobby-membership-and-message-isolation characterization", "multiple-lobby-membership-and-message-isolation-characterization",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create-pair", "explicit-configuration", "private-tags", "creator-messages", "discover-pair", "join-pair", "joiner-configuration", "joiner-messages", "self-state"}, 12, false, false, true, false, true, false},
    ScenarioContract{"Advanced/multiple-lobby-membership-and-message-isolation", "multiple-lobby-membership-and-message-isolation",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create-pair", "explicit-configuration", "private-tags", "creator-messages", "discover-pair", "join-pair", "joiner-configuration", "joiner-messages", "self-state"}, 12, false, false, true, false, true, false},
    ScenarioContract{"Simple/chat-room-message-delivery characterization", "chat-room-message-delivery-characterization",
        {"initialize", "sign-in-callback", "sign-in-terminal", "chat-listener-armed", "chat-message-received", "self-state",
            "chat-room-request-issued", "chat-room-retrieve", "chat-send-issued", "chat-send-terminal"}, 10, false, false, false, false, false, true},
    ScenarioContract{"Simple/chat-room-message-delivery", "chat-room-message-delivery",
        {"initialize", "sign-in-callback", "sign-in-terminal", "chat-listener-armed", "chat-message-received", "self-state",
            "chat-room-request-issued", "chat-room-retrieve", "chat-send-issued", "chat-send-terminal"}, 10, false, false, false, false, false, true, false},
    ScenarioContract{"Simple/friends-peer-information-retrieval characterization", "friends-peer-information-retrieval-characterization",
        {"initialize", "sign-in-callback", "sign-in-terminal", "persona-listener-armed", "user-information-request-issued", "user-information-terminal",
            "global-persona-data-changed", "self-state"}, 8, false, false, false, false, false, false, true},
    ScenarioContract{"Simple/friends-peer-information-retrieval", "friends-peer-information-retrieval",
        {"initialize", "sign-in-callback", "sign-in-terminal", "persona-listener-armed", "user-information-request-issued", "user-information-terminal",
            "global-persona-data-changed", "self-state"}, 8, false, false, false, false, false, false, true},
    ScenarioContract{"Simple/reliable-p2p-listener-peek characterization", "reliable-p2p-listener-peek-characterization",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata", "p2p-send", "creator-leave",
            "list", "join", "joiner-two-member-snapshot", "p2p-listener-armed", "p2p-listener-peek", "p2p-listener-destroyed", "joiner-leave"}, 16, false, false, true, false, false, false, false, true},
    ScenarioContract{"Simple/reliable-p2p-listener-peek", "reliable-p2p-listener-peek",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata", "p2p-send", "creator-leave",
            "list", "join", "joiner-two-member-snapshot", "p2p-listener-armed", "p2p-listener-peek", "p2p-listener-destroyed", "joiner-leave"}, 16, false, false, true, false, false, false, false, true},
    ScenarioContract{"Simple/public-lobby-owner-close-lifecycle characterization", "public-lobby-owner-close-lifecycle-characterization",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata", "creator-leave",
            "joiner-lifecycle-listeners-armed", "post-close-list", "owner-close-lifecycle", "self-state"}, 12, false, false, true, false, false, false},
    ScenarioContract{"Simple/public-lobby-owner-close-lifecycle", "public-lobby-owner-close-lifecycle",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata", "creator-leave",
            "joiner-lifecycle-listeners-armed", "post-close-list", "owner-close-lifecycle", "self-state"}, 12, false, false, true, false, false, false},
    ScenarioContract{"Simple/public-lobby-owner-ownership-transition characterization", "public-lobby-owner-ownership-transition-characterization",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata", "creator-leave",
            "joiner-lifecycle-listeners-armed", "owner-ownership-transition", "promoted-owner-data", "joiner-leave", "post-empty-list", "self-state"}, 14, false, false, true, false, false, false},
    ScenarioContract{"Simple/public-lobby-owner-ownership-transition", "public-lobby-owner-ownership-transition",
        {"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata", "creator-leave",
            "joiner-lifecycle-listeners-armed", "owner-ownership-transition", "promoted-owner-data", "joiner-leave", "post-empty-list", "self-state"}, 14, false, false, true, false, false, false}
};

struct Child
{
    fs::path log;
    std::string lane;
    std::string profile;
    bool started = false;
    bool exited = false;
    bool terminationRequested = false;
    int exitCode = -1;
#ifdef _WIN32
    HANDLE process = nullptr;
#else
    pid_t process = -1;
#endif
};

struct HostLaunch
{
    fs::path executable;
    fs::path workingDirectory;
    fs::path trace;
    fs::path control;
    std::string lane;
    std::string profile;
};

[[noreturn]] void invalidManifest() { throw std::runtime_error("Manifest validation failed"); }

bool fieldsExactly(const json& record, std::initializer_list<const char*> expected);

bool readArguments(const int argc, char* argv[], Arguments& arguments)
{
    for (int index = 1; index < argc; ++index)
    {
        const std::string option = argv[index];
        if (option == "--characterize-gog-services-state")
        {
            if (arguments.characterizeGogServicesState) return false;
            arguments.characterizeGogServicesState = true;
            continue;
        }
        if (option == "--characterize-official-gog-public-lobby-owner-close-lifecycle")
        {
            if (arguments.characterizeOfficialGogPublicLobbyOwnerCloseLifecycle) return false;
            arguments.characterizeOfficialGogPublicLobbyOwnerCloseLifecycle = true;
            continue;
        }
        if (option == "--characterize-official-gog-public-lobby-owner-ownership-transition")
        {
            if (arguments.characterizeOfficialGogPublicLobbyOwnerOwnershipTransition) return false;
            arguments.characterizeOfficialGogPublicLobbyOwnerOwnershipTransition = true;
            continue;
        }
        if (option == "--characterize-official-gog-public-lobby-not-joinable-behavior")
        {
            if (arguments.characterizeOfficialGogPublicLobbyNotJoinableBehavior) return false;
            arguments.characterizeOfficialGogPublicLobbyNotJoinableBehavior = true;
            continue;
        }
        if (option == "--characterize-official-gog-public-lobby-full-join-failure")
        {
            if (arguments.characterizeOfficialGogPublicLobbyFullJoinFailure) return false;
            arguments.characterizeOfficialGogPublicLobbyFullJoinFailure = true;
            continue;
        }
        if (option == "--characterize-public-lobby-data-propagation")
        {
            if (arguments.characterizePublicLobbyDataPropagation) return false;
            arguments.characterizePublicLobbyDataPropagation = true;
            continue;
        }
        if (option == "--characterize-multiple-lobby-membership-and-message-isolation")
        {
            if (arguments.characterizeMultipleLobbyMembershipAndMessageIsolation) return false;
            arguments.characterizeMultipleLobbyMembershipAndMessageIsolation = true;
            continue;
        }
        if (option == "--characterize-chat-room-message-delivery")
        {
            if (arguments.characterizeChatRoomMessageDelivery) return false;
            arguments.characterizeChatRoomMessageDelivery = true;
            continue;
        }
        if (option == "--characterize-official-gog-chat-room-message-delivery")
        {
            if (arguments.characterizeOfficialGogChatRoomMessageDelivery) return false;
            arguments.characterizeOfficialGogChatRoomMessageDelivery = true;
            continue;
        }
        if (option == "--characterize-official-gog-friends-peer-information-retrieval")
        {
            if (arguments.characterizeOfficialGogFriendsPeerInformationRetrieval) return false;
            arguments.characterizeOfficialGogFriendsPeerInformationRetrieval = true;
            continue;
        }
        if (option == "--characterize-official-gog-reliable-p2p-listener-peek")
        {
            if (arguments.characterizeOfficialGogReliableP2PListenerPeek) return false;
            arguments.characterizeOfficialGogReliableP2PListenerPeek = true;
            continue;
        }
        if (++index == argc) return false;
        const fs::path value = fs::u8path(argv[index]);
        if (option == "--manifest") arguments.manifest = value;
        else if (option == "--universelan-host") arguments.universelanHost = value;
        else if (option == "--gog-host") arguments.gogHost = value;
        else if (option == "--client-dll") arguments.clientDll = value;
        else if (option == "--server") arguments.server = value;
        else if (option == "--gog-runtime-dir") arguments.gogRuntimeDirectory = value;
        else return false;
    }
    return (static_cast<int>(arguments.characterizeGogServicesState) + static_cast<int>(arguments.characterizeOfficialGogPublicLobbyOwnerCloseLifecycle) + static_cast<int>(arguments.characterizeOfficialGogPublicLobbyOwnerOwnershipTransition) + static_cast<int>(arguments.characterizeOfficialGogPublicLobbyNotJoinableBehavior) + static_cast<int>(arguments.characterizeOfficialGogPublicLobbyFullJoinFailure) + static_cast<int>(arguments.characterizePublicLobbyDataPropagation) + static_cast<int>(arguments.characterizeMultipleLobbyMembershipAndMessageIsolation)
                 + static_cast<int>(arguments.characterizeChatRoomMessageDelivery) + static_cast<int>(arguments.characterizeOfficialGogChatRoomMessageDelivery)
                + static_cast<int>(arguments.characterizeOfficialGogFriendsPeerInformationRetrieval)
                + static_cast<int>(arguments.characterizeOfficialGogReliableP2PListenerPeek)
            == static_cast<int>(arguments.manifest.empty())) && !arguments.gogHost.empty() && !arguments.gogRuntimeDirectory.empty()
        && ((arguments.characterizeOfficialGogChatRoomMessageDelivery || arguments.characterizeOfficialGogFriendsPeerInformationRetrieval || arguments.characterizeOfficialGogPublicLobbyOwnerCloseLifecycle || arguments.characterizeOfficialGogPublicLobbyOwnerOwnershipTransition || arguments.characterizeOfficialGogPublicLobbyNotJoinableBehavior || arguments.characterizeOfficialGogPublicLobbyFullJoinFailure || arguments.characterizeOfficialGogReliableP2PListenerPeek)
            || (!arguments.universelanHost.empty() && !arguments.clientDll.empty() && !arguments.server.empty()));
}

void objectHasOnly(const json& value, std::initializer_list<const char*> allowed)
{
    if (!value.is_object()) invalidManifest();
    for (const auto& [key, ignored] : value.items())
    {
        bool known = false;
        for (const char* allowedKey : allowed) known = known || key == allowedKey;
        if (!known) invalidManifest();
    }
}

const json& required(const json& object, const char* name)
{
    if (!object.contains(name)) invalidManifest();
    return object.at(name);
}

const ScenarioContract* findScenarioContract(const std::string_view name)
{
    for (const ScenarioContract& contract : scenarioContracts)
        if (contract.name == name) return &contract;
    return nullptr;
}

bool observesPublicLobbyOwnerCloseLifecycle(const ScenarioContract& contract)
{
    return contract.hostScenario == "public-lobby-owner-close-lifecycle"
        || contract.hostScenario == "public-lobby-owner-close-lifecycle-characterization";
}

bool observesPublicLobbyFullJoinFailure(const ScenarioContract& contract)
{
    return contract.hostScenario == "public-lobby-full-join-failure"
        || contract.hostScenario == "public-lobby-full-join-failure-characterization";
}

bool observesPublicLobbyNotJoinableBehavior(const ScenarioContract& contract)
{
    return contract.observesPublicLobbyNotJoinableBehavior;
}

bool isStrictPublicLobbyNotJoinableBehavior(const ScenarioContract& contract)
{
    return contract.hostScenario == "public-lobby-not-joinable-behavior";
}

bool observesPublicLobbyOwnerOwnershipTransition(const ScenarioContract& contract)
{
    return contract.hostScenario == "public-lobby-owner-ownership-transition"
        || contract.hostScenario == "public-lobby-owner-ownership-transition-characterization";
}

bool observesSensitivePublicLobbyLifecycle(const ScenarioContract& contract)
{
    return observesPublicLobbyOwnerCloseLifecycle(contract) || observesPublicLobbyOwnerOwnershipTransition(contract);
}

bool observesReliableP2PListenerPeek(const ScenarioContract& contract)
{
    return contract.observesReliableP2PListenerPeek;
}

bool requiresSensitiveArtifactRedaction(const ScenarioContract& contract)
{
    return observesSensitivePublicLobbyLifecycle(contract) || observesPublicLobbyFullJoinFailure(contract)
        || observesPublicLobbyNotJoinableBehavior(contract) || observesReliableP2PListenerPeek(contract);
}

json requiredRecords(const ScenarioContract& contract)
{
    json records = json::array();
    for (std::size_t index = 0; index < contract.recordCount; ++index) records.push_back(contract.records[index]);
    return records;
}

Scenario parseScenario(const fs::path& manifest)
{
    std::ifstream input(manifest);
    json root;
    try { input >> root; }
    catch (...) { invalidManifest(); }
    objectHasOnly(root, {"name", "sdkVersion", "architecture", "laneMode", "timeoutSeconds", "profiles", "comparison"});
    if (!required(root, "name").is_string()) invalidManifest();
    const ScenarioContract* contract = findScenarioContract(root.at("name").get<std::string>());
    if (contract == nullptr) invalidManifest();
    if (!required(root, "sdkVersion").is_string() || root.at("sdkVersion") != UNIVERSELAN_BEHAVIOUR_TEST_VERSION) invalidManifest();
    if (!required(root, "architecture").is_string() || root.at("architecture") != UNIVERSELAN_BEHAVIOUR_TEST_ARCH) invalidManifest();
    if (!required(root, "laneMode").is_string()) invalidManifest();
    Scenario scenario;
    scenario.contract = contract;
    scenario.laneMode = root.at("laneMode").get<std::string>();
    if (scenario.laneMode != "concurrent" && scenario.laneMode != "sequential") invalidManifest();
    if ((contract->observesPublicLobby || contract->observesChatRoomMessageDelivery || contract->observesFriendsPeerInformation) && scenario.laneMode != "concurrent") invalidManifest();
    if (!required(root, "timeoutSeconds").is_number_integer()) invalidManifest();
    scenario.timeoutSeconds = root.at("timeoutSeconds").get<int>();
    if (scenario.timeoutSeconds < 1 || scenario.timeoutSeconds > 60) invalidManifest();
    const json& profiles = required(root, "profiles");
    if (!profiles.is_array() || profiles.size() != 2 || profiles[0] != "user1" || profiles[1] != "user2") invalidManifest();
    const json& comparison = required(root, "comparison");
    objectHasOnly(comparison, {"requiredRecords", "requiredTerminalOutcome", "unexpectedRecords", "opaqueIds", "acceptedStatePair", "acceptedPersonaStatePair", "acceptedP2PDeliveryPair"});
    const json& records = required(comparison, "requiredRecords");
    const bool validRecordDeclaration = observesReliableP2PListenerPeek(*contract)
        ? records.is_object() && records.size() == 2
            && records.value("user1", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter",
                "configuration", "metadata", "p2p-send", "creator-leave", "self-state"})
            && records.value("user2", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "list", "join",
                "joiner-two-member-snapshot", "p2p-listener-armed", "p2p-listener-peek", "p2p-listener-destroyed", "joiner-leave", "self-state"})
        : isStrictPublicLobbyNotJoinableBehavior(*contract)
        ? records.is_object() && records.size() == 2
            && records.value("user1", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter",
                "nonjoinable-configuration", "creator-sole-owner-snapshot", "creator-leave", "self-state"})
            && records.value("user2", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "list", "joiner-access",
                "post-delete-list", "self-state"})
        : observesPublicLobbyFullJoinFailure(*contract)
        ? records.is_object() && records.size() == 2
            && records.value("user1", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter",
                "configuration", "metadata", "creator-sole-owner-snapshot", "creator-leave", "self-state"})
            && records.value("user2", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "list", "public-state",
                "join", "joiner-failure-state", "post-empty-list", "self-state"})
        : observesPublicLobbyOwnerOwnershipTransition(*contract)
        ? records.is_object() && records.size() == 2
            && records.value("user1", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter",
                "configuration", "metadata", "creator-leave", "self-state"})
            && records.value("user2", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "list", "join",
                "joiner-two-member-snapshot", "joiner-lifecycle-listeners-armed", "owner-ownership-transition", "promoted-owner-data",
                "joiner-leave", "post-empty-list", "self-state"})
        : observesPublicLobbyOwnerCloseLifecycle(*contract)
        ? records.is_object() && records.size() == 2
            && records.value("user1", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter",
                "configuration", "metadata", "creator-leave", "self-state"})
            && records.value("user2", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "list", "join",
                "joiner-two-member-snapshot", "joiner-lifecycle-listeners-armed", "post-close-list", "owner-close-lifecycle", "self-state"})
        : contract->observesMultipleLobbyMembership
        ? records.is_object() && records.size() == 2
            && records.value("user1", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "create-pair", "explicit-configuration",
                "private-tags", "creator-messages", "creator-leave-L1", "creator-leave-L0", "self-state"})
            && records.value("user2", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "discover-pair", "join-pair",
                "joiner-configuration", "joiner-messages", "joiner-leave-L1", "joiner-leave-L0", "self-state"})
        : contract->observesChatRoomMessageDelivery
        ? records.is_object() && records.size() == 2
            && records.value("user1", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "chat-room-request-issued",
                "chat-room-retrieve", "chat-send-issued", "chat-send-terminal", "self-state"})
            && records.value("user2", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "chat-listener-armed",
                "chat-message-received", "self-state"})
        : contract->observesFriendsPeerInformation
        ? records.is_object() && records.size() == 2
            && records.value("user1", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "persona-listener-armed",
                "user-information-request-issued", "user-information-terminal", "global-persona-data-changed", "self-state"})
            && records.value("user2", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "persona-listener-armed",
                "user-information-request-issued", "user-information-terminal", "global-persona-data-changed", "self-state"})
        : contract->observesPublicLobbyDataPropagation
        ? records.is_object() && records.size() == 2
            && records.value("user1", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter",
                "configuration", "metadata", "owner-data-update", "creator-sole-owner-snapshot", "creator-leave", "self-state"})
            && records.value("user2", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "list", "join",
                "joiner-two-member-snapshot", "joiner-lobby-data", "joiner-leave", "self-state"})
        : contract->observesPublicLobby
        ? records.is_object() && records.size() == 2
            && records.value("user1", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter",
                "configuration", "metadata", "creator-two-member-snapshot", "creator-sole-owner-snapshot", "creator-leave", "self-state"})
            && records.value("user2", json()) == json::array({"initialize", "sign-in-callback", "sign-in-terminal", "list", "join",
                "joiner-two-member-snapshot", "joiner-leave", "self-state"})
        : records.is_array() && records == requiredRecords(*contract);
    if (!validRecordDeclaration
        || required(comparison, "requiredTerminalOutcome") != "success"
        || required(comparison, "unexpectedRecords") != "fail"
        || !required(comparison, "opaqueIds").is_string()) invalidManifest();
    if (contract->observesGogServicesState)
    {
        const json& acceptedStatePair = required(comparison, "acceptedStatePair");
        if (!fieldsExactly(acceptedStatePair, {"gog", "universelan"})
            || acceptedStatePair["gog"] != "undefined" || acceptedStatePair["universelan"] != "connected") invalidManifest();
        scenario.acceptsGogServicesStatePair = true;
    }
    else if (comparison.contains("acceptedStatePair")) invalidManifest();
    if (contract->observesFriendsPeerInformation)
    {
        const json& acceptedPersonaStatePair = required(comparison, "acceptedPersonaStatePair");
        if (!fieldsExactly(acceptedPersonaStatePair, {"gog", "universelan"})
            || acceptedPersonaStatePair["gog"] != "offline" || acceptedPersonaStatePair["universelan"] != "online") invalidManifest();
        scenario.acceptsFriendsPeerPersonaStatePair = true;
    }
    else if (comparison.contains("acceptedPersonaStatePair")) invalidManifest();
    if (contract->observesReliableP2PListenerPeek)
    {
        const json& acceptedP2PDeliveryPair = required(comparison, "acceptedP2PDeliveryPair");
        if (!fieldsExactly(acceptedP2PDeliveryPair, {"gog", "universelan"})
            || acceptedP2PDeliveryPair["gog"] != "scheduled-no-expected-channel-callback-or-peeks"
            || acceptedP2PDeliveryPair["universelan"] != "scheduled-delivery-and-two-peeks") invalidManifest();
        scenario.acceptsReliableP2PDeliveryPair = true;
    }
    else if (comparison.contains("acceptedP2PDeliveryPair")) invalidManifest();
    scenario.requiredTerminalOutcome = comparison.at("requiredTerminalOutcome").get<std::string>();
    return scenario;
}

Scenario characterizationScenario()
{
    Scenario scenario;
    scenario.contract = &scenarioContracts[3];
    scenario.laneMode = "concurrent";
    scenario.timeoutSeconds = 20;
    scenario.characterization = true;
    return scenario;
}

Scenario publicLobbyDataPropagationCharacterizationScenario()
{
    Scenario scenario;
    scenario.contract = &scenarioContracts[5];
    scenario.laneMode = "concurrent";
    scenario.timeoutSeconds = 30;
    scenario.characterization = true;
    return scenario;
}

Scenario publicLobbyOwnerCloseLifecycleCharacterizationScenario()
{
    Scenario scenario;
    scenario.contract = findScenarioContract("Simple/public-lobby-owner-close-lifecycle characterization");
    scenario.laneMode = "concurrent";
    scenario.timeoutSeconds = 45;
    scenario.characterization = true;
    return scenario;
}

Scenario publicLobbyOwnerOwnershipTransitionCharacterizationScenario()
{
    Scenario scenario;
    scenario.contract = findScenarioContract("Simple/public-lobby-owner-ownership-transition characterization");
    scenario.laneMode = "concurrent";
    scenario.timeoutSeconds = 45;
    scenario.characterization = true;
    return scenario;
}

Scenario publicLobbyFullJoinFailureCharacterizationScenario()
{
    Scenario scenario;
    scenario.contract = findScenarioContract("Simple/public-lobby-full-join-failure characterization");
    scenario.laneMode = "concurrent";
    scenario.timeoutSeconds = 45;
    scenario.characterization = true;
    return scenario;
}

Scenario publicLobbyNotJoinableBehaviorCharacterizationScenario()
{
    Scenario scenario;
    scenario.contract = findScenarioContract("Simple/public-lobby-not-joinable-behavior characterization");
    scenario.laneMode = "concurrent";
    scenario.timeoutSeconds = 45;
    scenario.characterization = true;
    return scenario;
}

Scenario multipleLobbyMembershipAndMessageIsolationCharacterizationScenario()
{
    Scenario scenario;
    scenario.contract = &scenarioContracts[7];
    scenario.laneMode = "concurrent";
    scenario.timeoutSeconds = 45;
    scenario.characterization = true;
    return scenario;
}

Scenario chatRoomMessageDeliveryCharacterizationScenario()
{
    Scenario scenario;
    scenario.contract = &scenarioContracts[9];
    scenario.laneMode = "concurrent";
    scenario.timeoutSeconds = 30;
    scenario.characterization = true;
    return scenario;
}

Scenario friendsPeerInformationRetrievalCharacterizationScenario()
{
    Scenario scenario;
    scenario.contract = &scenarioContracts[11];
    scenario.laneMode = "concurrent";
    scenario.timeoutSeconds = 30;
    scenario.characterization = true;
    scenario.requiredTerminalOutcome = "success";
    return scenario;
}

Scenario reliableP2PListenerPeekCharacterizationScenario()
{
    Scenario scenario;
    scenario.contract = findScenarioContract("Simple/reliable-p2p-listener-peek characterization");
    scenario.laneMode = "concurrent";
    scenario.timeoutSeconds = 45;
    scenario.characterization = true;
    return scenario;
}

void writeFile(const fs::path& path, const std::string& contents)
{
    fs::create_directories(path.parent_path());
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    if (!output) throw std::runtime_error("Unable to create isolated configuration");
    output << contents;
}

void writePrivateControl(const fs::path& path, const std::string& contents)
{
    const fs::path temporary = path.string() + ".tmp";
    writeFile(temporary, contents);
    std::error_code error;
    fs::rename(temporary, path, error);
    if (error)
    {
        fs::remove(path, error);
        fs::rename(temporary, path, error);
    }
    if (error) throw std::runtime_error("Unable to update private control");
}

std::string readControlValue(const fs::path& path, const char* const name)
{
    std::ifstream input(path, std::ios::binary);
    const std::string prefix = std::string(name) + "=";
    std::string line;
    while (std::getline(input, line)) if (line.rfind(prefix, 0) == 0) return line.substr(prefix.size());
    return {};
}

void setControlFlag(const fs::path& path, const char* const name)
{
    const std::string token = readControlValue(path, "token");
    const std::array<const char*, 18> flags{"creator-ready", "joiner-joined", "creator-two-member", "joiner-left",
        "joiner-lifecycle-armed", "creator-left", "post-empty-list-absent", "observer-armed", "creator-data-update-complete", "joiner-data-observed",
        "p2p-listener-armed", "p2p-sender-scheduled", "p2p-peek-complete", "joiner-failure-observed", "joiner-nonmember-complete", "joiner-list-complete", "post-delete-list-complete", "abort"};
    std::string contents = "token=" + token;
    for (const char* const flag : flags)
        contents += "\n" + std::string(flag) + "=" + (std::string(name) == flag || readControlValue(path, flag) == "1" ? "1" : "0");
    writePrivateControl(path, contents + "\n");
}

bool hasEvent(const fs::path& control, const char* const expected)
{
    std::ifstream input(control.parent_path() / "event", std::ios::binary);
    std::string event;
    while (std::getline(input, event)) if (event == expected) return true;
    return false;
}

void writeUniverselanConfiguration(const fs::path& directory, const std::string& profile, const std::uint16_t port)
{
    const std::string userId = profile == "user1" ? "41001" : "41002";
    const std::string persona = profile == "user1" ? "BehaviourTestUser1" : "BehaviourTestUser2";
    const fs::path data = directory / "UniverseLANData";
    fs::create_directories(data);
    writeFile(directory / "UniverseLAN.ini",
        "[Storage]\nGameDataPath=" + data.string() + "\nServerDataPath=UniverseLANServerData\n"
        "\n[Authentication]\nKey=UniverseLAN-BehaviourTests-NotASecret\n"
        "\n[Tracing]\nCallTracing=0\nUnhandledExceptionLogging=0\nMiniDumpOnUnhandledException=0\nAlwaysFlush=0\nTraceToConsole=0\n"
        "\n[Networking]\nTimeout=1000\n");
    writeFile(data / "Config.ini",
        "[Settings]\nEnableConsole=0\n\n[Client]\nServerAddress=127.0.0.1\nPort=" + std::to_string(port) + "\n"
        + "\n[User]\nPersonaNameType=@Custom\nCustomPersonaName=" + persona + "\nGalaxyIDType=@Custom\nCustomGalaxyID=" + userId
        + "\nGalaxyIDOffset=0\nSignedIn=1\n");
}

void writeServerConfiguration(const fs::path& directory, const std::uint16_t port)
{
    fs::create_directories(directory / "UniverseLANServerData");
    writeFile(directory / "UniverseLAN.ini",
        "[Storage]\nGameDataPath=" + (directory / "UniverseLANData").string() + "\nServerDataPath=UniverseLANServerData\n"
        "\n[Authentication]\nKey=UniverseLAN-BehaviourTests-NotASecret\n"
        "\n[Tracing]\nCallTracing=0\nUnhandledExceptionLogging=0\nMiniDumpOnUnhandledException=0\nAlwaysFlush=0\nTraceToConsole=0\n");
    writeFile(directory / "UniverseLANServerData" / "Config.ini",
        "[Server]\nBindAddress=127.0.0.1\nPort=" + std::to_string(port) + "\nMaxConnections=8\nMaxTickRate=200\n");
}

#ifdef _WIN32
std::string quoteWindows(const std::string& value)
{
    std::string result = "\"";
    for (const char character : value) result += character == '\"' ? "\\\"" : std::string(1, character);
    return result + "\"";
}
#endif

bool startChild(Child& child, const fs::path& executable, const std::vector<std::string>& arguments, const fs::path& workingDirectory)
{
#ifdef _WIN32
    const fs::path output = child.log.empty() ? fs::path("NUL") : child.log;
    HANDLE log = CreateFileW(output.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (log == INVALID_HANDLE_VALUE) return false;
    if (!SetHandleInformation(log, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT)) { CloseHandle(log); return false; }
    std::string command = quoteWindows(executable.string());
    for (const std::string& argument : arguments) command += " " + quoteWindows(argument);
    const std::wstring commandLine = fs::u8path(command).wstring();
    std::vector<wchar_t> writable(commandLine.begin(), commandLine.end());
    writable.push_back(L'\0');
    STARTUPINFOW startup{};
    startup.cb = sizeof(startup);
    startup.dwFlags = STARTF_USESTDHANDLES;
    startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startup.hStdOutput = log;
    startup.hStdError = log;
    PROCESS_INFORMATION information{};
    const BOOL started = CreateProcessW(executable.c_str(), writable.data(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW, nullptr, workingDirectory.c_str(), &startup, &information);
    CloseHandle(log);
    if (!started) return false;
    CloseHandle(information.hThread);
    child.process = information.hProcess;
    child.started = true;
    return true;
#else
    const int log = open((child.log.empty() ? "/dev/null" : child.log.string()).c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (log < 0) return false;
    child.process = fork();
    if (child.process == 0)
    {
        dup2(log, STDOUT_FILENO);
        dup2(log, STDERR_FILENO);
        close(log);
        if (chdir(workingDirectory.c_str()) != 0) _exit(127);
        std::vector<char*> command{const_cast<char*>(executable.c_str())};
        for (const std::string& argument : arguments) command.push_back(const_cast<char*>(argument.c_str()));
        command.push_back(nullptr);
        execv(executable.c_str(), command.data());
        _exit(127);
    }
    close(log);
    child.started = child.process > 0;
    return child.started;
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
    if (waitpid(child.process, &status, WNOHANG) == child.process)
    {
        child.exited = true;
        child.exitCode = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    }
#endif
}

void stopChild(Child& child)
{
#ifdef _WIN32
    if (child.process == nullptr) return;
#else
    if (child.process == -1) return;
#endif
    updateChild(child);
    if (!child.exited)
    {
        child.terminationRequested = true;
#ifdef _WIN32
        TerminateProcess(child.process, 1);
        WaitForSingleObject(child.process, 5000);
#else
        kill(child.process, SIGTERM);
        const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        while (std::chrono::steady_clock::now() < deadline)
        {
            updateChild(child);
            if (child.exited) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        if (!child.exited) kill(child.process, SIGKILL);
#endif
        updateChild(child);
    }
#ifdef _WIN32
    CloseHandle(child.process);
    child.process = nullptr;
#else
    child.process = -1;
#endif
}

bool logContains(const fs::path& path, const std::string& needle)
{
    std::ifstream input(path, std::ios::binary);
    std::string contents((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    return contents.find(needle) != std::string::npos;
}

fs::path stageHost(const fs::path& source, const fs::path& directory)
{
    const fs::path destination = directory / source.filename();
    std::error_code error;
    fs::copy_file(source, destination, fs::copy_options::overwrite_existing, error);
    if (error) throw std::runtime_error("Unable to stage host executable");
    return destination;
}

void stageUniverselanRuntime(const Arguments& arguments, const fs::path& directory)
{
    std::error_code error;
    fs::copy_file(arguments.clientDll, directory / arguments.clientDll.filename(), fs::copy_options::overwrite_existing, error);
    if (error) throw std::runtime_error("Unable to stage UniverseLAN runtime");
}

void stageGogRuntime(const Arguments& arguments, const fs::path& directory)
{
    bool copied = false;
    for (const fs::directory_entry& entry : fs::directory_iterator(arguments.gogRuntimeDirectory))
    {
        std::string extension = entry.path().extension().string();
        for (char& character : extension) character = static_cast<char>(std::tolower(static_cast<unsigned char>(character)));
        if (!entry.is_regular_file() || extension != ".dll") continue;
        std::error_code error;
        fs::copy_file(entry.path(), directory / entry.path().filename(), fs::copy_options::overwrite_existing, error);
        if (error) throw std::runtime_error("Unable to stage official-GOG runtime dependency");
        copied = true;
    }
    if (!copied) throw std::runtime_error("Official-GOG runtime dependencies are unavailable");
}

bool runHosts(const std::vector<HostLaunch>& launches, const ScenarioContract& contract, const int timeoutSeconds, std::vector<Child>& completed)
{
    std::vector<Child> children(launches.size());
    for (std::size_t index = 0; index < launches.size(); ++index)
    {
        children[index].log = requiresSensitiveArtifactRedaction(contract) ? fs::path() : launches[index].workingDirectory / "stdout.log";
        children[index].lane = launches[index].lane;
        children[index].profile = launches[index].profile;
        if (!startChild(children[index], launches[index].executable,
            {"--scenario", std::string(contract.hostScenario), "--profile", launches[index].profile,
                "--trace", launches[index].trace.string(), "--timeout-seconds", std::to_string(timeoutSeconds)},
            launches[index].workingDirectory))
        {
            for (Child& child : children) stopChild(child);
            completed = std::move(children);
            return false;
        }
    }

    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(timeoutSeconds + 5);
    bool passed = false;
    while (std::chrono::steady_clock::now() < deadline)
    {
        passed = true;
        for (Child& child : children)
        {
            updateChild(child);
            if (!child.exited) passed = false;
            else if (child.exitCode != 0) passed = false;
        }
        if (passed) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    for (Child& child : children) stopChild(child);
    completed = std::move(children);
    return passed;
}

bool runPublicLobbyHosts(const std::vector<HostLaunch>& launches, const ScenarioContract& contract, const int timeoutSeconds,
    std::vector<Child>& completed, bool& cleanupAcknowledged, std::vector<std::string>& callbackGateDiscoveryOrder)
{
    std::vector<Child> children(launches.size());
    for (std::size_t index = 0; index < launches.size(); ++index)
    {
        children[index].log = requiresSensitiveArtifactRedaction(contract) ? fs::path() : launches[index].workingDirectory / "stdout.log";
        children[index].lane = launches[index].lane;
        children[index].profile = launches[index].profile;
        if (!startChild(children[index], launches[index].executable,
            {"--scenario", std::string(contract.hostScenario), "--profile", launches[index].profile,
                "--trace", launches[index].trace.string(), "--control", launches[index].control.string(),
                "--timeout-seconds", std::to_string(timeoutSeconds)}, launches[index].workingDirectory))
        {
            for (const HostLaunch& launch : launches) setControlFlag(launch.control, "abort");
            for (Child& child : children) stopChild(child);
            completed = std::move(children);
            cleanupAcknowledged = false;
            return false;
        }
    }

    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(timeoutSeconds + 5);
    std::vector<bool> creatorCallbackObserved(launches.size());
    std::vector<bool> joinerCallbackObserved(launches.size());
    bool passed = false;
    while (std::chrono::steady_clock::now() < deadline)
    {
        for (std::size_t creator = 0; creator + 1 < launches.size(); creator += 2)
        {
            const std::size_t joiner = creator + 1;
            if (hasEvent(launches[creator].control, "creator-ready")) setControlFlag(launches[joiner].control, "creator-ready");
            if (hasEvent(launches[joiner].control, "joiner-joined")) setControlFlag(launches[creator].control, "joiner-joined");
            if (observesPublicLobbyNotJoinableBehavior(contract))
            {
                if (hasEvent(launches[joiner].control, "joiner-list-complete")) setControlFlag(launches[creator].control, "joiner-list-complete");
                if (hasEvent(launches[creator].control, "creator-left")) setControlFlag(launches[joiner].control, "creator-left");
                if (hasEvent(launches[joiner].control, "post-delete-list-complete")) setControlFlag(launches[creator].control, "post-delete-list-complete");
            }
            else if (observesPublicLobbyFullJoinFailure(contract))
            {
                if (hasEvent(launches[joiner].control, "joiner-failure-observed")) setControlFlag(launches[creator].control, "joiner-failure-observed");
                if (hasEvent(launches[creator].control, "creator-left")) setControlFlag(launches[joiner].control, "creator-left");
                if (hasEvent(launches[joiner].control, "post-empty-list-absent")) setControlFlag(launches[creator].control, "post-empty-list-absent");
            }
            else if (observesReliableP2PListenerPeek(contract))
            {
                if (hasEvent(launches[joiner].control, "p2p-listener-armed")) setControlFlag(launches[creator].control, "p2p-listener-armed");
                if (hasEvent(launches[creator].control, "p2p-sender-scheduled")) setControlFlag(launches[joiner].control, "p2p-sender-scheduled");
                if (hasEvent(launches[joiner].control, "p2p-peek-complete")) setControlFlag(launches[creator].control, "p2p-peek-complete");
                if (hasEvent(launches[joiner].control, "joiner-left")) setControlFlag(launches[creator].control, "joiner-left");
            }
            else if (observesSensitivePublicLobbyLifecycle(contract))
            {
                if (hasEvent(launches[joiner].control, "joiner-lifecycle-armed")) setControlFlag(launches[creator].control, "joiner-lifecycle-armed");
                if (hasEvent(launches[creator].control, "creator-left")) setControlFlag(launches[joiner].control, "creator-left");
                if (observesPublicLobbyOwnerOwnershipTransition(contract)
                    && hasEvent(launches[joiner].control, "post-empty-list-absent"))
                    setControlFlag(launches[creator].control, "post-empty-list-absent");
            }
            else if (contract.observesPublicLobbyDataPropagation || contract.observesMultipleLobbyMembership)
            {
                if (contract.observesPublicLobbyDataPropagation && !creatorCallbackObserved[creator] && hasEvent(launches[creator].control, "creator-data-update-callback"))
                {
                    creatorCallbackObserved[creator] = true;
                    callbackGateDiscoveryOrder.push_back(launches[creator].lane + ":creator-update-callback");
                }
                if (contract.observesPublicLobbyDataPropagation && !joinerCallbackObserved[joiner] && hasEvent(launches[joiner].control, "joiner-lobby-data-callback"))
                {
                    joinerCallbackObserved[joiner] = true;
                    callbackGateDiscoveryOrder.push_back(launches[joiner].lane + ":joiner-data-callback");
                }
                if (hasEvent(launches[joiner].control, "observer-armed")) setControlFlag(launches[creator].control, "observer-armed");
                if (hasEvent(launches[creator].control, "creator-data-update-complete")) setControlFlag(launches[joiner].control, "creator-data-update-complete");
                if (hasEvent(launches[joiner].control, "joiner-data-observed")) setControlFlag(launches[creator].control, "joiner-data-observed");
            }
            else if (hasEvent(launches[creator].control, "creator-two-member")) setControlFlag(launches[joiner].control, "creator-two-member");
            if (hasEvent(launches[joiner].control, "joiner-left")) setControlFlag(launches[creator].control, "joiner-left");
        }

        passed = true;
        for (Child& child : children)
        {
            updateChild(child);
            passed = passed && child.exited && child.exitCode == 0;
        }
        cleanupAcknowledged = true;
        if (observesPublicLobbyFullJoinFailure(contract))
            for (std::size_t creator = 0; creator + 1 < launches.size(); creator += 2)
                cleanupAcknowledged = cleanupAcknowledged && hasEvent(launches[creator].control, "cleanup-ack")
                    && hasEvent(launches[creator + 1].control, "joiner-nonmember-complete");
        if (!observesPublicLobbyFullJoinFailure(contract))
            for (const HostLaunch& launch : launches) cleanupAcknowledged = cleanupAcknowledged && hasEvent(launch.control, "cleanup-ack");
        if (passed && cleanupAcknowledged) break;
        if (std::any_of(children.begin(), children.end(), [](const Child& child) { return child.exited && child.exitCode != 0; })) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    if (!(passed && cleanupAcknowledged))
    {
        for (const HostLaunch& launch : launches) setControlFlag(launch.control, "abort");
        const auto cleanupDeadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        while (std::chrono::steady_clock::now() < cleanupDeadline)
        {
            cleanupAcknowledged = true;
            if (observesPublicLobbyFullJoinFailure(contract))
                for (std::size_t creator = 0; creator + 1 < launches.size(); creator += 2)
                    cleanupAcknowledged = cleanupAcknowledged && hasEvent(launches[creator].control, "cleanup-ack")
                        && hasEvent(launches[creator + 1].control, "joiner-nonmember-complete");
            if (!observesPublicLobbyFullJoinFailure(contract))
                for (const HostLaunch& launch : launches) cleanupAcknowledged = cleanupAcknowledged && hasEvent(launch.control, "cleanup-ack");
            if (cleanupAcknowledged) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
    for (Child& child : children) stopChild(child);
    completed = std::move(children);
    return passed && cleanupAcknowledged;
}

void setChatControlFlag(const fs::path& path, const char* const name)
{
    writePrivateControl(path, std::string("receiver-armed=") + (std::string(name) == "receiver-armed" ? "1" : "0")
        + "\nabort=" + (std::string(name) == "abort" ? "1" : "0") + "\n");
}

bool consumeOneTimeRelay(const fs::path& path, std::string& value)
{
    std::error_code error;
    const bool exists = fs::exists(path, error);
    if (error) return false;
    if (!exists) { value.clear(); return true; }
    std::ifstream input(path, std::ios::binary);
    if (!input) return false;
    value.assign(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
    if (input.bad()) return false;
    input.close();
    fs::remove(path, error);
    return !error;
}

bool isRawGalaxyIDRelay(const std::string& value)
{
    return !value.empty() && value.size() <= 20 && std::all_of(value.begin(), value.end(), [](const char character) {
        return character >= '0' && character <= '9';
    });
}

bool redactSensitiveFailureArtifacts(const fs::path& root)
{
    std::error_code error;
    fs::recursive_directory_iterator iterator(root, error);
    if (error) return false;
    const fs::recursive_directory_iterator end;
    std::vector<fs::path> sensitive;
    while (iterator != end)
    {
        const fs::path path = iterator->path();
        const bool directory = iterator->is_directory(error);
        if (error) return false;
        if (!directory)
        {
            const std::string name = path.filename().string();
            std::string extension = path.extension().string();
            std::transform(extension.begin(), extension.end(), extension.begin(), [](const unsigned char character) { return static_cast<char>(std::tolower(character)); });
            const bool stagedBinary = extension == ".exe" || extension == ".dll" || extension == ".pdb";
            if (name != "trace.jsonl" && name != "normalized-comparison.json" && !stagedBinary)
                sensitive.push_back(path);
        }
        iterator.increment(error);
        if (error) return false;
    }
    for (const fs::path& path : sensitive)
    {
        fs::remove(path, error);
        if (error) return false;
    }
    return true;
}

bool runChatRoomMessageDeliveryHosts(const std::vector<HostLaunch>& launches, const ScenarioContract& contract, const int timeoutSeconds,
    std::vector<Child>& completed, bool& receiverArmedBeforeSenderRelease, bool& allHostsExited)
{
    std::vector<Child> children(launches.size());
    for (std::size_t index = 0; index < launches.size(); ++index)
    {
        // The Galaxy runtime can print raw account IDs; chat diagnostics retain only symbolic traces.
        children[index].log.clear();
        children[index].lane = launches[index].lane;
        children[index].profile = launches[index].profile;
        if (!startChild(children[index], launches[index].executable,
            {"--scenario", std::string(contract.hostScenario), "--profile", launches[index].profile,
                "--trace", launches[index].trace.string(), "--control", launches[index].control.string(),
                "--timeout-seconds", std::to_string(timeoutSeconds)}, launches[index].workingDirectory))
        {
            for (const HostLaunch& launch : launches) setChatControlFlag(launch.control, "abort");
            for (Child& child : children) stopChild(child);
            completed = std::move(children);
            allHostsExited = std::all_of(completed.begin(), completed.end(), [](const Child& child) { return child.exited; });
            return false;
        }
    }

    std::vector<std::string> identities(launches.size());
    std::vector<bool> relayed(launches.size() / 2);
    bool relayError = false;
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(timeoutSeconds + 5);
    bool passed = false;
    while (std::chrono::steady_clock::now() < deadline)
    {
        for (std::size_t index = 0; index < launches.size(); ++index)
        {
            if (!identities[index].empty()) continue;
            std::string candidate;
            if (!consumeOneTimeRelay(launches[index].workingDirectory / "self-id-relay", candidate)) { relayError = true; break; }
            if (!candidate.empty() && isRawGalaxyIDRelay(candidate)) identities[index] = candidate;
        }
        if (relayError) break;
        for (std::size_t sender = 0; sender + 1 < launches.size(); sender += 2)
        {
            const std::size_t receiver = sender + 1;
            const std::size_t lane = sender / 2;
            if (!relayed[lane] && !identities[sender].empty() && !identities[receiver].empty()
                && hasEvent(launches[receiver].control, "receiver-listener-registered"))
            {
                writePrivateControl(launches[sender].workingDirectory / "peer-id-relay", identities[receiver]);
                writePrivateControl(launches[receiver].workingDirectory / "peer-id-relay", identities[sender]);
                relayed[lane] = true;
            }
            if (relayed[lane] && hasEvent(launches[receiver].control, "receiver-armed"))
            {
                receiverArmedBeforeSenderRelease = true;
                setChatControlFlag(launches[sender].control, "receiver-armed");
            }
        }
        passed = true;
        for (Child& child : children)
        {
            updateChild(child);
            passed = passed && child.exited && child.exitCode == 0;
        }
        if (passed) break;
        if (std::any_of(children.begin(), children.end(), [](const Child& child) { return child.exited && child.exitCode != 0; })) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    if (!passed)
    {
        for (const HostLaunch& launch : launches) setChatControlFlag(launch.control, "abort");
    }
    for (Child& child : children) stopChild(child);
    allHostsExited = std::all_of(children.begin(), children.end(), [](const Child& child) { return child.exited; });
    completed = std::move(children);
    return passed && !relayError && receiverArmedBeforeSenderRelease && allHostsExited;
}

bool runFriendsPeerInformationRetrievalHosts(const std::vector<HostLaunch>& launches, const ScenarioContract& contract, const int timeoutSeconds,
    std::vector<Child>& completed, bool& personaListenersReadyBeforePeerRelay, bool& allHostsExited)
{
    std::vector<Child> children(launches.size());
    for (std::size_t index = 0; index < launches.size(); ++index)
    {
        // The Galaxy runtime can print account identifiers; friend diagnostics retain symbolic traces only.
        children[index].log.clear();
        children[index].lane = launches[index].lane;
        children[index].profile = launches[index].profile;
        if (!startChild(children[index], launches[index].executable,
            {"--scenario", std::string(contract.hostScenario), "--profile", launches[index].profile,
                "--trace", launches[index].trace.string(), "--control", launches[index].control.string(),
                "--timeout-seconds", std::to_string(timeoutSeconds)}, launches[index].workingDirectory))
        {
            for (const HostLaunch& launch : launches) setChatControlFlag(launch.control, "abort");
            for (Child& child : children) stopChild(child);
            completed = std::move(children);
            allHostsExited = std::all_of(completed.begin(), completed.end(), [](const Child& child) { return child.exited; });
            return false;
        }
    }

    std::vector<std::string> identities(launches.size());
    std::vector<bool> relayed(launches.size() / 2);
    bool relayError = false;
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(timeoutSeconds + 5);
    bool passed = false;
    while (std::chrono::steady_clock::now() < deadline)
    {
        for (std::size_t first = 0; first + 1 < launches.size(); first += 2)
        {
            const std::size_t second = first + 1;
            const std::size_t lane = first / 2;
            if (!relayed[lane] && hasEvent(launches[first].control, "persona-listener-registered")
                && hasEvent(launches[second].control, "persona-listener-registered"))
            {
                personaListenersReadyBeforePeerRelay = true;
                if (identities[first].empty())
                {
                    std::string candidate;
                    if (!consumeOneTimeRelay(launches[first].workingDirectory / "self-id-relay", candidate)) { relayError = true; break; }
                    if (!candidate.empty() && isRawGalaxyIDRelay(candidate)) identities[first] = candidate;
                }
                if (identities[second].empty())
                {
                    std::string candidate;
                    if (!consumeOneTimeRelay(launches[second].workingDirectory / "self-id-relay", candidate)) { relayError = true; break; }
                    if (!candidate.empty() && isRawGalaxyIDRelay(candidate)) identities[second] = candidate;
                }
                if (!identities[first].empty() && !identities[second].empty())
                {
                    writePrivateControl(launches[first].workingDirectory / "peer-id-relay", identities[second]);
                    writePrivateControl(launches[second].workingDirectory / "peer-id-relay", identities[first]);
                    relayed[lane] = true;
                }
            }
        }
        if (relayError) break;
        passed = true;
        for (Child& child : children)
        {
            updateChild(child);
            passed = passed && child.exited && child.exitCode == 0;
        }
        if (passed) break;
        if (std::any_of(children.begin(), children.end(), [](const Child& child) { return child.exited && child.exitCode != 0; })) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    if (!passed)
        for (const HostLaunch& launch : launches) setChatControlFlag(launch.control, "abort");
    for (Child& child : children) stopChild(child);
    allHostsExited = std::all_of(children.begin(), children.end(), [](const Child& child) { return child.exited; });
    completed = std::move(children);
    return passed && !relayError && personaListenersReadyBeforePeerRelay && allHostsExited
        && std::all_of(relayed.begin(), relayed.end(), [](const bool value) { return value; });
}

void addProcessFailures(json& report, const std::vector<Child>& children)
{
    for (const Child& child : children)
    {
        if (child.started && child.exited && child.exitCode == 0) continue;
        report["processFailures"].push_back({
            {"lane", child.lane},
            {"profile", child.profile},
            {"exitStatus", child.exited ? json(child.exitCode) : json("unavailable")},
            {"logPath", child.log.string()},
            {"terminationRequested", child.terminationRequested}
        });
    }
}

bool fieldsExactly(const json& record, std::initializer_list<const char*> expected)
{
    if (!record.is_object() || record.size() != expected.size()) return false;
    for (const char* key : expected) if (!record.contains(key)) return false;
    return true;
}

bool normalizeReliableP2PListenerPeekTrace(const fs::path& trace, const std::string& profile, json& normalized)
{
    try
    {
        std::vector<json> records;
        for (const std::string& line : common::readTrace(trace)) records.push_back(json::parse(line));
        const std::vector<std::string> expected = profile == "user1"
            ? std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata", "p2p-send", "creator-leave", "self-state"}
            : std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "list", "join", "joiner-two-member-snapshot", "p2p-listener-armed", "p2p-listener-peek", "p2p-listener-destroyed", "joiner-leave", "self-state"};
        if (records.size() != expected.size()) return false;
        for (std::size_t index = 0; index < expected.size(); ++index)
            if (!records[index].is_object() || records[index].value("record", "") != expected[index]) return false;
        const auto validSelf = [](const json& record) {
            return fieldsExactly(record, {"record", "signedIn", "loggedOn", "idValid", "idType", "selfIdRepeatEqual", "personaAvailable"})
                && record["signedIn"] == true && record["loggedOn"] == true && record["idValid"] == true && record["idType"] == "user"
                && record["selfIdRepeatEqual"] == true && record["personaAvailable"].is_boolean();
        };
        const auto validLeave = [](const json& record) {
            return fieldsExactly(record, {"record", "result", "reason", "sameLobby"}) && record["result"] == "callback"
                && record["reason"] == "user-left" && record["sameLobby"] == true;
        };
        const auto validSnapshot = [](const json& record) {
            return fieldsExactly(record, {"record", "lobbyValid", "public", "joinable", "capacity", "memberCount", "selfPresent", "otherPresent", "membersValid", "membersDistinct", "ownerIsSelf", "ownerValid"})
                && record["lobbyValid"] == true && record["public"] == true && record["joinable"] == true && record["capacity"] == 2
                && record["memberCount"] == 2 && record["selfPresent"] == true && record["otherPresent"] == true && record["membersValid"] == true
                && record["membersDistinct"] == true && record["ownerIsSelf"] == false && record["ownerValid"] == true;
        };
        if (!fieldsExactly(records[0], {"record", "result"}) || records[0]["result"] != "returned"
            || !fieldsExactly(records[1], {"record", "result"}) || records[1]["result"] != "success"
            || !fieldsExactly(records[2], {"record", "result"}) || records[2]["result"] != "success" || !validSelf(records.back())) return false;
        if (profile == "user1")
        {
            if (!fieldsExactly(records[3], {"record", "result", "lobbyValid", "lobbyType"}) || records[3]["result"] != "success" || records[3]["lobbyValid"] != true || records[3]["lobbyType"] != "lobby"
                || !fieldsExactly(records[4], {"record", "result", "sameCreatedLobby"}) || records[4]["result"] != "success" || records[4]["sameCreatedLobby"] != true
                || !fieldsExactly(records[5], {"record", "joinableUpdateSuccess", "capacityUpdateSuccess", "joinableVisible", "capacityVisible"})
                || records[5]["joinableUpdateSuccess"] != true || records[5]["capacityUpdateSuccess"] != true || records[5]["joinableVisible"] != true || records[5]["capacityVisible"] != true
                || !fieldsExactly(records[6], {"record", "result", "sameCreatedLobby"}) || records[6]["result"] != "success" || records[6]["sameCreatedLobby"] != true
                || !fieldsExactly(records[7], {"record", "recipientValidNonSelf", "recipientCurrentLobbyMember", "recipientType", "channelExpected", "postArmSettled", "privatePayloadNonemptyBounded", "scheduled"})
                || records[7]["recipientValidNonSelf"] != true || records[7]["recipientCurrentLobbyMember"] != true || records[7]["recipientType"] != "user"
                || records[7]["channelExpected"] != true || records[7]["postArmSettled"] != true || records[7]["privatePayloadNonemptyBounded"] != true || records[7]["scheduled"] != true || !validLeave(records[8])) return false;
        }
        else
        {
            if (!fieldsExactly(records[3], {"record", "result", "attempts", "retryUsed", "selectedCount", "selectedValid"}) || records[3]["result"] != "success"
                || !records[3]["attempts"].is_number_integer() || records[3]["attempts"] < 1 || records[3]["attempts"] > 6 || !records[3]["retryUsed"].is_boolean()
                || records[3]["selectedCount"] != 1 || records[3]["selectedValid"] != true
                || !fieldsExactly(records[4], {"record", "result", "sameListedLobby"}) || records[4]["result"] != "success" || records[4]["sameListedLobby"] != true
                || !validSnapshot(records[5]) || !fieldsExactly(records[6], {"record", "listenerRegistered", "creatorValidNonSelf"})
                || records[6]["listenerRegistered"] != true || records[6]["creatorValidNonSelf"] != true
                || !fieldsExactly(records[7], {"record", "callbackObserved", "expectedChannelCallbackObserved", "nonTargetCallbackObserved", "callbackCount", "expectedChannelCallbackCount", "nonTargetCallbackCount", "callbackContexts", "callbackSizeMatchesPrivatePayload",
                    "firstPeekSucceeded", "firstPeekSenderValidNonSelf", "firstPeekSenderMatchesCreator", "firstPeekLengthMatchesPrivatePayload", "firstPeekPayloadMatchesPrivatePayload",
                    "secondPeekSucceeded", "secondPeekSenderValidNonSelf", "secondPeekSenderMatchesCreator", "secondPeekLengthMatchesPrivatePayload", "secondPeekPayloadMatchesPrivatePayload", "peekResultsEquivalent"})
                || !records[7]["callbackObserved"].is_boolean() || !records[7]["expectedChannelCallbackObserved"].is_boolean() || !records[7]["nonTargetCallbackObserved"].is_boolean()
                || !records[7]["callbackCount"].is_number_integer() || records[7]["callbackCount"] < 0 || !records[7]["expectedChannelCallbackCount"].is_number_integer() || records[7]["expectedChannelCallbackCount"] < 0
                || !records[7]["nonTargetCallbackCount"].is_number_integer() || records[7]["nonTargetCallbackCount"] < 0 || !records[7]["callbackContexts"].is_array()
                || !fieldsExactly(records[8], {"record", "destroyedBeforeShutdown"}) || records[8]["destroyedBeforeShutdown"] != true || !validLeave(records[9])) return false;
        }
        normalized = records;
        return true;
    }
    catch (...) { return false; }
}

bool normalizePublicLobbyTrace(const fs::path& trace, const std::string& profile, json& normalized)
{
    try
    {
        const std::vector<std::string> raw = common::readTrace(trace);
        std::vector<json> records;
        for (const std::string& line : raw) records.push_back(json::parse(line));
        const std::vector<std::string> expected = profile == "user1"
            ? std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata",
                "creator-two-member-snapshot", "creator-sole-owner-snapshot", "creator-leave", "self-state"}
            : std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "list", "join", "joiner-two-member-snapshot", "joiner-leave", "self-state"};
        if (records.size() != expected.size()) return false;
        for (std::size_t index = 0; index < expected.size(); ++index)
            if (!records[index].is_object() || records[index].value("record", "") != expected[index]) return false;
        if (!fieldsExactly(records[0], {"record", "result"}) || records[0]["result"] != "returned"
            || !fieldsExactly(records[1], {"record", "result"}) || records[1]["result"] != "success"
            || !fieldsExactly(records[2], {"record", "result"}) || records[2]["result"] != "success") return false;
        const auto validSnapshot = [](const json& record, const int members, const bool other, const bool owner) {
            return fieldsExactly(record, {"record", "lobbyValid", "public", "joinable", "capacity", "memberCount", "selfPresent",
                    "otherPresent", "membersValid", "membersDistinct", "ownerIsSelf", "ownerValid"})
                && record["lobbyValid"] == true && record["public"] == true && record["joinable"] == true && record["capacity"] == 2
                && record["memberCount"] == members && record["selfPresent"] == true && record["otherPresent"] == other
                && record["membersValid"] == true && record["membersDistinct"] == true && record["ownerIsSelf"] == owner && record["ownerValid"] == true;
        };
        const auto validLeave = [](const json& record) {
            return fieldsExactly(record, {"record", "result", "reason", "sameLobby"}) && record["result"] == "callback"
                && record["reason"] == "user-left" && record["sameLobby"] == true;
        };
        if (profile == "user1")
        {
            if (!fieldsExactly(records[3], {"record", "result", "lobbyValid", "lobbyType"}) || records[3]["result"] != "success"
                || records[3]["lobbyValid"] != true || records[3]["lobbyType"] != "lobby"
                || !fieldsExactly(records[4], {"record", "result", "sameCreatedLobby"}) || records[4]["result"] != "success"
                || records[4]["sameCreatedLobby"] != true || !fieldsExactly(records[5], {"record", "joinableUpdateSuccess", "capacityUpdateSuccess", "joinableVisible", "capacityVisible"})
                || records[5]["joinableUpdateSuccess"] != true || records[5]["capacityUpdateSuccess"] != true || records[5]["joinableVisible"] != true || records[5]["capacityVisible"] != true
                || !fieldsExactly(records[6], {"record", "result", "sameCreatedLobby"}) || records[6]["result"] != "success" || records[6]["sameCreatedLobby"] != true
                || !validSnapshot(records[7], 2, true, true) || !validSnapshot(records[8], 1, false, true) || !validLeave(records[9])) return false;
        }
        else
        {
            if (!fieldsExactly(records[3], {"record", "result", "attempts", "retryUsed", "selectedCount", "selectedValid"})
                || records[3]["result"] != "success" || !records[3]["attempts"].is_number_integer() || records[3]["attempts"] < 1
                || records[3]["attempts"] > 6 || !records[3]["retryUsed"].is_boolean() || records[3]["selectedCount"] != 1
                || records[3]["selectedValid"] != true || !fieldsExactly(records[4], {"record", "result", "sameListedLobby"})
                || records[4]["result"] != "success" || records[4]["sameListedLobby"] != true
                || !validSnapshot(records[5], 2, true, false) || !validLeave(records[6])) return false;
        }
        if (!fieldsExactly(records.back(), {"record", "signedIn", "loggedOn", "idValid", "idType", "selfIdRepeatEqual", "personaAvailable"})
            || records.back()["signedIn"] != true || records.back()["loggedOn"] != true || records.back()["idValid"] != true
            || records.back()["idType"] != "user" || records.back()["selfIdRepeatEqual"] != true || !records.back()["personaAvailable"].is_boolean()) return false;
        normalized = records;
        return true;
    }
    catch (...) { return false; }
}

bool normalizePublicLobbyNotJoinableBehaviorTrace(const fs::path& trace, const std::string& profile, json& normalized)
{
    try
    {
        std::vector<json> records;
        for (const std::string& line : common::readTrace(trace)) records.push_back(json::parse(line));
        const std::vector<std::string> expected = profile == "user1"
            ? std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "nonjoinable-configuration", "creator-sole-owner-snapshot", "creator-leave", "self-state"}
            : std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "list", "joiner-access", "post-delete-list", "self-state"};
        if (records.size() != expected.size()) return false;
        for (std::size_t index = 0; index < expected.size(); ++index)
            if (!records[index].is_object() || records[index].value("record", "") != expected[index]) return false;
        const auto validSelf = [](const json& record) {
            return fieldsExactly(record, {"record", "signedIn", "loggedOn", "idValid", "idType", "selfIdRepeatEqual", "personaAvailable"})
                && record["signedIn"] == true && record["loggedOn"] == true && record["idValid"] == true && record["idType"] == "user"
                && record["selfIdRepeatEqual"] == true && record["personaAvailable"].is_boolean();
        };
        const auto validLeave = [](const json& record) {
            return fieldsExactly(record, {"record", "result", "reason", "sameLobby"}) && record["result"] == "callback"
                && record["reason"] == "user-left" && record["sameLobby"] == true;
        };
        if (!fieldsExactly(records[0], {"record", "result"}) || records[0]["result"] != "returned"
            || !fieldsExactly(records[1], {"record", "result"}) || records[1]["result"] != "success"
            || !fieldsExactly(records[2], {"record", "result"}) || records[2]["result"] != "success" || !validSelf(records.back())) return false;
        if (profile == "user1")
        {
            if (!fieldsExactly(records[3], {"record", "result", "lobbyValid", "lobbyType"}) || records[3]["result"] != "success" || records[3]["lobbyValid"] != true || records[3]["lobbyType"] != "lobby"
                || !fieldsExactly(records[4], {"record", "result", "sameCreatedLobby"}) || records[4]["result"] != "success" || records[4]["sameCreatedLobby"] != true
                || !fieldsExactly(records[5], {"record", "capacityUpdateSuccess", "setLobbyJoinableFalseSuccess", "publicVisible", "capacityVisible", "nonjoinableVisible", "tagVisible"})
                || records[5]["capacityUpdateSuccess"] != true || records[5]["setLobbyJoinableFalseSuccess"] != true || records[5]["publicVisible"] != true
                || records[5]["capacityVisible"] != true || records[5]["nonjoinableVisible"] != true || records[5]["tagVisible"] != true
                || !fieldsExactly(records[6], {"record", "lobbyValid", "public", "joinable", "capacity", "memberCount", "selfPresent", "otherPresent", "membersValid", "membersDistinct", "ownerIsSelf", "ownerValid"})
                || records[6]["lobbyValid"] != true || records[6]["public"] != true || records[6]["joinable"] != false || records[6]["capacity"] != 2
                || records[6]["memberCount"] != 1 || records[6]["selfPresent"] != true || records[6]["otherPresent"] != false || records[6]["membersValid"] != true
                || records[6]["membersDistinct"] != true || records[6]["ownerIsSelf"] != true || records[6]["ownerValid"] != true || !validLeave(records[7])) return false;
        }
        else if (!fieldsExactly(records[3], {"record", "result", "candidateCount", "selectedFromFilteredList", "selectedValid"}) || records[3]["result"] != "success"
            || records[3]["candidateCount"] != 0 || records[3]["selectedFromFilteredList"] != false || records[3]["selectedValid"] != false
            || !fieldsExactly(records[4], {"record", "joinIssuedOnlyForFilteredSelection", "directIdJoinAttempted", "memberOnlyCallsAttempted", "memberDataCallsAttempted", "sendLobbyMessageAttempted", "joined"})
            || records[4]["joinIssuedOnlyForFilteredSelection"] != true || records[4]["directIdJoinAttempted"] != false || records[4]["memberOnlyCallsAttempted"] != false
            || records[4]["memberDataCallsAttempted"] != false || records[4]["sendLobbyMessageAttempted"] != false || records[4]["joined"] != false
            || !fieldsExactly(records[5], {"record", "result", "targetAbsent"}) || records[5]["result"] != "success" || records[5]["targetAbsent"] != true) return false;
        normalized = records;
        return true;
    }
    catch (...) { return false; }
}

bool normalizePublicLobbyFullJoinFailureTrace(const fs::path& trace, const std::string& profile, json& normalized)
{
    try
    {
        std::vector<json> records;
        for (const std::string& line : common::readTrace(trace)) records.push_back(json::parse(line));
        const std::vector<std::string> expected = profile == "user1"
            ? std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata", "creator-sole-owner-snapshot", "creator-leave", "self-state"}
            : std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "list", "public-state", "join", "joiner-failure-state", "post-empty-list", "self-state"};
        if (records.size() != expected.size()) return false;
        for (std::size_t index = 0; index < expected.size(); ++index)
            if (!records[index].is_object() || records[index].value("record", "") != expected[index]) return false;
        const auto validSelf = [](const json& record) {
            return fieldsExactly(record, {"record", "signedIn", "loggedOn", "idValid", "idType", "selfIdRepeatEqual", "personaAvailable"})
                && record["signedIn"] == true && record["loggedOn"] == true && record["idValid"] == true && record["idType"] == "user"
                && record["selfIdRepeatEqual"] == true && record["personaAvailable"].is_boolean();
        };
        const auto validLeave = [](const json& record) {
            return fieldsExactly(record, {"record", "result", "reason", "sameLobby"}) && record["result"] == "callback"
                && record["reason"] == "user-left" && record["sameLobby"] == true;
        };
        if (!fieldsExactly(records[0], {"record", "result"}) || records[0]["result"] != "returned"
            || !fieldsExactly(records[1], {"record", "result"}) || records[1]["result"] != "success"
            || !fieldsExactly(records[2], {"record", "result"}) || records[2]["result"] != "success" || !validSelf(records.back())) return false;
        if (profile == "user1")
        {
            if (!fieldsExactly(records[3], {"record", "result", "lobbyValid", "lobbyType"}) || records[3]["result"] != "success"
                || records[3]["lobbyValid"] != true || records[3]["lobbyType"] != "lobby"
                || !fieldsExactly(records[4], {"record", "result", "sameCreatedLobby"}) || records[4]["result"] != "success" || records[4]["sameCreatedLobby"] != true
                || !fieldsExactly(records[5], {"record", "capacityUpdateSuccess", "joinableUpdateSuccess", "publicVisible", "configuredLimitVisible", "joinableVisible"})
                || records[5]["capacityUpdateSuccess"] != true || records[5]["joinableUpdateSuccess"] != true || records[5]["publicVisible"] != true
                || records[5]["configuredLimitVisible"] != true || records[5]["joinableVisible"] != true
                || !fieldsExactly(records[6], {"record", "result", "sameCreatedLobby"}) || records[6]["result"] != "success" || records[6]["sameCreatedLobby"] != true
                || !fieldsExactly(records[7], {"record", "lobbyValid", "ownerIsSelf", "soleMemberIsSelf", "configuredLimitObserved", "joinableObserved"})
                || records[7]["lobbyValid"] != true || records[7]["ownerIsSelf"] != true || records[7]["soleMemberIsSelf"] != true
                || records[7]["configuredLimitObserved"] != true || records[7]["joinableObserved"] != true || !validLeave(records[8])) return false;
        }
        else
        {
            if (!fieldsExactly(records[3], {"record", "result", "fullLobbiesRequested", "exactlyOneCandidate", "selectedValid"}) || records[3]["result"] != "success"
                || records[3]["fullLobbiesRequested"] != true || records[3]["exactlyOneCandidate"] != true || records[3]["selectedValid"] != true
                || !fieldsExactly(records[4], {"record", "retrieveResult", "sameListedLobby", "publicVisible", "configuredLimitVisible", "joinableVisible"})
                || records[4]["retrieveResult"] != "success" || records[4]["sameListedLobby"] != true || records[4]["publicVisible"] != true
                || records[4]["configuredLimitVisible"] != true || records[4]["joinableVisible"] != true
                || !fieldsExactly(records[5], {"record", "exactlyOneTerminal", "terminalResult", "sameListedLobby", "entered"})
                || records[5]["exactlyOneTerminal"] != true || records[5]["terminalResult"] != "full"
                || records[5]["sameListedLobby"] != true || records[5]["entered"] != false
                || !fieldsExactly(records[6], {"record", "failedWithoutEntry", "memberOnlyCallsAttempted", "memberDataCallsAttempted", "sendLobbyMessageAttempted", "publicStateOnly"})
                || records[6]["failedWithoutEntry"] != true || records[6]["memberOnlyCallsAttempted"] != false || records[6]["memberDataCallsAttempted"] != false
                || records[6]["sendLobbyMessageAttempted"] != false || records[6]["publicStateOnly"] != true
                || !fieldsExactly(records[7], {"record", "result", "targetAbsent"}) || records[7]["result"] != "success" || records[7]["targetAbsent"] != true) return false;
        }
        normalized = records;
        return true;
    }
    catch (...) { return false; }
}

bool normalizePublicLobbyOwnerCloseLifecycleTrace(const fs::path& trace, const std::string& profile, json& normalized)
{
    try
    {
        std::vector<json> records;
        for (const std::string& line : common::readTrace(trace)) records.push_back(json::parse(line));
        const std::vector<std::string> expected = profile == "user1"
            ? std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata", "creator-leave", "self-state"}
            : std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "list", "join", "joiner-two-member-snapshot", "joiner-lifecycle-listeners-armed", "post-close-list", "owner-close-lifecycle", "self-state"};
        if (records.size() != expected.size()) return false;
        for (std::size_t index = 0; index < expected.size(); ++index)
            if (!records[index].is_object() || records[index].value("record", "") != expected[index]) return false;
        if (!fieldsExactly(records[0], {"record", "result"}) || records[0]["result"] != "returned"
            || !fieldsExactly(records[1], {"record", "result"}) || records[1]["result"] != "success"
            || !fieldsExactly(records[2], {"record", "result"}) || records[2]["result"] != "success") return false;
        const auto validSnapshot = [](const json& record, const bool owner) {
            return fieldsExactly(record, {"record", "lobbyValid", "public", "joinable", "capacity", "memberCount", "selfPresent",
                    "otherPresent", "membersValid", "membersDistinct", "ownerIsSelf", "ownerValid"})
                && record["lobbyValid"] == true && record["public"] == true && record["joinable"] == true && record["capacity"] == 2
                && record["memberCount"] == 2 && record["selfPresent"] == true && record["otherPresent"] == true
                && record["membersValid"] == true && record["membersDistinct"] == true && record["ownerIsSelf"] == owner && record["ownerValid"] == true;
        };
        const auto validLeave = [](const json& record) {
            return fieldsExactly(record, {"record", "result", "reason", "sameLobby"}) && record["result"] == "callback"
                && record["reason"] == "user-left" && record["sameLobby"] == true;
        };
        if (profile == "user1")
        {
            if (!fieldsExactly(records[3], {"record", "result", "lobbyValid", "lobbyType"}) || records[3]["result"] != "success"
                || records[3]["lobbyValid"] != true || records[3]["lobbyType"] != "lobby"
                || !fieldsExactly(records[4], {"record", "result", "sameCreatedLobby"}) || records[4]["result"] != "success"
                || records[4]["sameCreatedLobby"] != true
                || !fieldsExactly(records[5], {"record", "joinableUpdateSuccess", "capacityUpdateSuccess", "joinableVisible", "capacityVisible"})
                || records[5]["joinableUpdateSuccess"] != true || records[5]["capacityUpdateSuccess"] != true
                || records[5]["joinableVisible"] != true || records[5]["capacityVisible"] != true
                || !fieldsExactly(records[6], {"record", "result", "sameCreatedLobby"}) || records[6]["result"] != "success"
                || records[6]["sameCreatedLobby"] != true || !validLeave(records[7])) return false;
        }
        else
        {
            if (!fieldsExactly(records[3], {"record", "result", "attempts", "retryUsed", "selectedCount", "selectedValid"})
                || records[3]["result"] != "success" || !records[3]["attempts"].is_number_integer() || records[3]["attempts"] < 1 || records[3]["attempts"] > 6
                || !records[3]["retryUsed"].is_boolean() || records[3]["selectedCount"] != 1 || records[3]["selectedValid"] != true
                || !fieldsExactly(records[4], {"record", "result", "sameListedLobby"}) || records[4]["result"] != "success" || records[4]["sameListedLobby"] != true
                || !validSnapshot(records[5], false)
                || !fieldsExactly(records[6], {"record", "memberStateListenerRegistered", "globalLobbyLeftListenerRegistered", "priorOwnerValidNonSelf"})
                || records[6]["memberStateListenerRegistered"] != true || records[6]["globalLobbyLeftListenerRegistered"] != true || records[6]["priorOwnerValidNonSelf"] != true
                || !fieldsExactly(records[7], {"record", "result", "attempts", "targetAbsent"}) || records[7]["result"] != "success"
                || !records[7]["attempts"].is_number_integer() || records[7]["attempts"] < 1 || records[7]["attempts"] > 6 || records[7]["targetAbsent"] != true
                || !fieldsExactly(records[8], {"record", "priorOwnerMemberCallbackObserved", "priorOwnerMemberStateSequence", "priorOwnerLeftObserved",
                    "globalLobbyLeftCallbackObserved", "globalLobbyLeaveReasonSequence", "globalLobbyClosedObserved", "unexpectedGlobalLobbyLeaveReasonObserved", "targetLobbySequence"})
                || !records[8]["priorOwnerMemberCallbackObserved"].is_boolean() || !records[8]["priorOwnerLeftObserved"].is_boolean()
                || !records[8]["globalLobbyLeftCallbackObserved"].is_boolean() || !records[8]["globalLobbyClosedObserved"].is_boolean()
                || records[8]["unexpectedGlobalLobbyLeaveReasonObserved"] != false
                || !records[8]["priorOwnerMemberStateSequence"].is_array() || !records[8]["globalLobbyLeaveReasonSequence"].is_array() || !records[8]["targetLobbySequence"].is_array()) return false;
        }
        if (!fieldsExactly(records.back(), {"record", "signedIn", "loggedOn", "idValid", "idType", "selfIdRepeatEqual", "personaAvailable"})
            || records.back()["signedIn"] != true || records.back()["loggedOn"] != true || records.back()["idValid"] != true
            || records.back()["idType"] != "user" || records.back()["selfIdRepeatEqual"] != true || !records.back()["personaAvailable"].is_boolean()) return false;
        normalized = records;
        return true;
    }
    catch (...) { return false; }
}

bool normalizePublicLobbyOwnerOwnershipTransitionTrace(const fs::path& trace, const std::string& profile, json& normalized)
{
    try
    {
        std::vector<json> records;
        for (const std::string& line : common::readTrace(trace)) records.push_back(json::parse(line));
        const std::vector<std::string> expected = profile == "user1"
            ? std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata", "creator-leave", "self-state"}
            : std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "list", "join", "joiner-two-member-snapshot", "joiner-lifecycle-listeners-armed", "owner-ownership-transition", "promoted-owner-data", "joiner-leave", "post-empty-list", "self-state"};
        if (records.size() != expected.size()) return false;
        for (std::size_t index = 0; index < expected.size(); ++index)
            if (!records[index].is_object() || records[index].value("record", "") != expected[index]) return false;
        if (!fieldsExactly(records[0], {"record", "result"}) || records[0]["result"] != "returned"
            || !fieldsExactly(records[1], {"record", "result"}) || records[1]["result"] != "success"
            || !fieldsExactly(records[2], {"record", "result"}) || records[2]["result"] != "success") return false;
        const auto validSnapshot = [](const json& record, const bool owner) {
            return fieldsExactly(record, {"record", "lobbyValid", "public", "joinable", "capacity", "memberCount", "selfPresent",
                    "otherPresent", "membersValid", "membersDistinct", "ownerIsSelf", "ownerValid"})
                && record["lobbyValid"] == true && record["public"] == true && record["joinable"] == true && record["capacity"] == 2
                && record["memberCount"] == 2 && record["selfPresent"] == true && record["otherPresent"] == true
                && record["membersValid"] == true && record["membersDistinct"] == true && record["ownerIsSelf"] == owner && record["ownerValid"] == true;
        };
        const auto validLeave = [](const json& record) {
            return fieldsExactly(record, {"record", "result", "reason", "sameLobby"}) && record["result"] == "callback"
                && record["reason"] == "user-left" && record["sameLobby"] == true;
        };
        if (profile == "user1")
        {
            if (!fieldsExactly(records[3], {"record", "result", "lobbyValid", "lobbyType"}) || records[3]["result"] != "success"
                || records[3]["lobbyValid"] != true || records[3]["lobbyType"] != "lobby"
                || !fieldsExactly(records[4], {"record", "result", "sameCreatedLobby"}) || records[4]["result"] != "success"
                || records[4]["sameCreatedLobby"] != true
                || !fieldsExactly(records[5], {"record", "joinableUpdateSuccess", "capacityUpdateSuccess", "joinableVisible", "capacityVisible"})
                || records[5]["joinableUpdateSuccess"] != true || records[5]["capacityUpdateSuccess"] != true
                || records[5]["joinableVisible"] != true || records[5]["capacityVisible"] != true
                || !fieldsExactly(records[6], {"record", "result", "sameCreatedLobby"}) || records[6]["result"] != "success"
                || records[6]["sameCreatedLobby"] != true || !validLeave(records[7])) return false;
        }
        else
        {
            if (!fieldsExactly(records[3], {"record", "result", "attempts", "retryUsed", "selectedCount", "selectedValid"})
                || records[3]["result"] != "success" || !records[3]["attempts"].is_number_integer() || records[3]["attempts"] < 1 || records[3]["attempts"] > 6
                || !records[3]["retryUsed"].is_boolean() || records[3]["selectedCount"] != 1 || records[3]["selectedValid"] != true
                || !fieldsExactly(records[4], {"record", "result", "sameListedLobby"}) || records[4]["result"] != "success" || records[4]["sameListedLobby"] != true
                || !validSnapshot(records[5], false)
                || !fieldsExactly(records[6], {"record", "memberStateListenerRegistered", "globalOwnerChangeListenerRegistered", "priorOwnerValidNonSelf"})
                || records[6]["memberStateListenerRegistered"] != true || records[6]["globalOwnerChangeListenerRegistered"] != true || records[6]["priorOwnerValidNonSelf"] != true
                || !fieldsExactly(records[7], {"record", "priorOwnerLeftObserved", "ownerChangedToSelfObserved", "ownerNowSelf", "membersOnlySelf", "priorOwnerMemberStateSequence", "ownerChangeSequence", "targetLobbySequence"})
                || records[7]["priorOwnerLeftObserved"] != true || records[7]["ownerChangedToSelfObserved"] != true || records[7]["ownerNowSelf"] != true || records[7]["membersOnlySelf"] != true
                || !records[7]["priorOwnerMemberStateSequence"].is_array() || !records[7]["ownerChangeSequence"].is_array() || !records[7]["targetLobbySequence"].is_array()
                || !fieldsExactly(records[8], {"record", "setLobbyDataSuccess", "copiedValueVisible"}) || records[8]["setLobbyDataSuccess"] != true || records[8]["copiedValueVisible"] != true
                || !validLeave(records[9])
                || !fieldsExactly(records[10], {"record", "result", "attempts", "targetAbsent"}) || records[10]["result"] != "success"
                || !records[10]["attempts"].is_number_integer() || records[10]["attempts"] < 1 || records[10]["attempts"] > 6 || records[10]["targetAbsent"] != true) return false;
        }
        if (!fieldsExactly(records.back(), {"record", "signedIn", "loggedOn", "idValid", "idType", "selfIdRepeatEqual", "personaAvailable"})
            || records.back()["signedIn"] != true || records.back()["loggedOn"] != true || records.back()["idValid"] != true
            || records.back()["idType"] != "user" || records.back()["selfIdRepeatEqual"] != true || !records.back()["personaAvailable"].is_boolean()) return false;
        normalized = records;
        return true;
    }
    catch (...) { return false; }
}

bool normalizePublicLobbyDataPropagationTrace(const fs::path& trace, const std::string& profile, json& normalized)
{
    try
    {
        const std::vector<std::string> raw = common::readTrace(trace);
        std::vector<json> records;
        for (const std::string& line : raw) records.push_back(json::parse(line));
        const std::vector<std::string> expected = profile == "user1"
            ? std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "create", "creator-enter", "configuration", "metadata",
                "owner-data-update", "creator-sole-owner-snapshot", "creator-leave", "self-state"}
            : std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "list", "join", "joiner-two-member-snapshot",
                "joiner-lobby-data", "joiner-leave", "self-state"};
        if (records.size() != expected.size()) return false;
        for (std::size_t index = 0; index < expected.size(); ++index)
            if (!records[index].is_object() || records[index].value("record", "") != expected[index]) return false;
        if (!fieldsExactly(records[0], {"record", "result"}) || records[0]["result"] != "returned"
            || !fieldsExactly(records[1], {"record", "result"}) || records[1]["result"] != "success"
            || !fieldsExactly(records[2], {"record", "result"}) || records[2]["result"] != "success") return false;
        const auto validSnapshot = [](const json& record, const int members, const bool other, const bool owner) {
            return fieldsExactly(record, {"record", "lobbyValid", "public", "joinable", "capacity", "memberCount", "selfPresent",
                    "otherPresent", "membersValid", "membersDistinct", "ownerIsSelf", "ownerValid"})
                && record["lobbyValid"] == true && record["public"] == true && record["joinable"] == true && record["capacity"] == 2
                && record["memberCount"] == members && record["selfPresent"] == true && record["otherPresent"] == other
                && record["membersValid"] == true && record["membersDistinct"] == true && record["ownerIsSelf"] == owner && record["ownerValid"] == true;
        };
        const auto validLeave = [](const json& record) {
            return fieldsExactly(record, {"record", "result", "reason", "sameLobby"}) && record["result"] == "callback"
                && record["reason"] == "user-left" && record["sameLobby"] == true;
        };
        if (profile == "user1")
        {
            if (!fieldsExactly(records[3], {"record", "result", "lobbyValid", "lobbyType"}) || records[3]["result"] != "success"
                || records[3]["lobbyValid"] != true || records[3]["lobbyType"] != "lobby"
                || !fieldsExactly(records[4], {"record", "result", "sameCreatedLobby"}) || records[4]["result"] != "success"
                || records[4]["sameCreatedLobby"] != true || !fieldsExactly(records[5], {"record", "joinableUpdateSuccess", "capacityUpdateSuccess", "joinableVisible", "capacityVisible"})
                || records[5]["joinableUpdateSuccess"] != true || records[5]["capacityUpdateSuccess"] != true || records[5]["joinableVisible"] != true || records[5]["capacityVisible"] != true
                || !fieldsExactly(records[6], {"record", "result", "sameCreatedLobby"}) || records[6]["result"] != "success" || records[6]["sameCreatedLobby"] != true
                || !fieldsExactly(records[7], {"record", "result", "sameCreatedLobby"}) || records[7]["result"] != "success"
                || records[7]["sameCreatedLobby"] != true || !validSnapshot(records[8], 1, false, true) || !validLeave(records[9])) return false;
        }
        else
        {
            if (!fieldsExactly(records[3], {"record", "result", "attempts", "retryUsed", "selectedCount", "selectedValid"})
                || records[3]["result"] != "success" || !records[3]["attempts"].is_number_integer() || records[3]["attempts"] < 1
                || records[3]["attempts"] > 6 || !records[3]["retryUsed"].is_boolean() || records[3]["selectedCount"] != 1
                || records[3]["selectedValid"] != true || !fieldsExactly(records[4], {"record", "result", "sameListedLobby"})
                || records[4]["result"] != "success" || records[4]["sameListedLobby"] != true || !validSnapshot(records[5], 2, true, false)
                || !fieldsExactly(records[6], {"record", "callbackAvailable", "callbackCount", "duplicateNotifications", "memberIdValid",
                    "sameCallbackCopyVisible", "eventualCopyVisible"}) || records[6]["callbackAvailable"] != true
                || !records[6]["callbackCount"].is_number_integer() || records[6]["callbackCount"] < 1
                || !records[6]["duplicateNotifications"].is_boolean() || records[6]["memberIdValid"] != false
                || records[6]["sameCallbackCopyVisible"] != true || records[6]["eventualCopyVisible"] != true || !validLeave(records[7])) return false;
        }
        if (!fieldsExactly(records.back(), {"record", "signedIn", "loggedOn", "idValid", "idType", "selfIdRepeatEqual", "personaAvailable"})
            || records.back()["signedIn"] != true || records.back()["loggedOn"] != true || records.back()["idValid"] != true
            || records.back()["idType"] != "user" || records.back()["selfIdRepeatEqual"] != true || !records.back()["personaAvailable"].is_boolean()) return false;
        normalized = records;
        return true;
    }
    catch (...) { return false; }
}

bool normalizeChatRoomMessageDeliveryTrace(const fs::path& trace, const std::string& profile, json& normalized)
{
    try
    {
        std::vector<json> records;
        for (const std::string& line : common::readTrace(trace)) records.push_back(json::parse(line));
        const std::vector<std::string> expected = profile == "user1"
            ? std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "chat-room-request-issued", "chat-room-retrieve",
                "chat-send-issued", "chat-send-terminal", "self-state"}
            : std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "chat-listener-armed", "chat-message-received", "self-state"};
        if (records.size() != expected.size()) return false;
        for (std::size_t index = 0; index < expected.size(); ++index)
            if (!records[index].is_object() || records[index].value("record", "") != expected[index]) return false;
        if (!fieldsExactly(records[0], {"record", "result"}) || records[0]["result"] != "returned"
            || !fieldsExactly(records[1], {"record", "result"}) || records[1]["result"] != "success"
            || !fieldsExactly(records[2], {"record", "result"}) || records[2]["result"] != "success") return false;
        if (profile == "user1")
        {
            if (!fieldsExactly(records[3], {"record", "receiverArmed", "peerRelayConsumed", "tokenRelayConsumed"})
                || records[3]["receiverArmed"] != true || records[3]["peerRelayConsumed"] != true || records[3]["tokenRelayConsumed"] != true
                || !fieldsExactly(records[4], {"record", "terminalCount", "successCount", "failureCount", "callbackPeerMatchesRequested", "roomValid"})
                || records[4]["terminalCount"] != 1 || records[4]["successCount"] != 1 || records[4]["failureCount"] != 0
                || records[4]["callbackPeerMatchesRequested"] != true || records[4]["roomValid"] != true
                || !fieldsExactly(records[5], {"record", "sendIndexReturned"}) || records[5]["sendIndexReturned"] != true
                || !fieldsExactly(records[6], {"record", "terminalCount", "successCount", "failureCount", "sameRoom", "sameSendIndex"})
                || records[6]["terminalCount"] != 1 || records[6]["successCount"] != 1 || records[6]["failureCount"] != 0
                || records[6]["sameRoom"] != true || records[6]["sameSendIndex"] != true) return false;
        }
        else if (!fieldsExactly(records[3], {"record", "listenerRegistered", "peerRelayConsumed", "tokenRelayConsumed"})
            || records[3]["listenerRegistered"] != true || records[3]["peerRelayConsumed"] != true || records[3]["tokenRelayConsumed"] != true
            || !fieldsExactly(records[4], {"record", "callbackCount", "messageCountOne", "readInsideCallback", "callbackRoomValid", "senderMatchesExpectedPeer", "messageTypeChat", "payloadMatchesExpectedToken"})
            || records[4]["callbackCount"] != 1 || records[4]["messageCountOne"] != true || records[4]["readInsideCallback"] != true
            || records[4]["callbackRoomValid"] != true || records[4]["senderMatchesExpectedPeer"] != true || records[4]["messageTypeChat"] != true
            || records[4]["payloadMatchesExpectedToken"] != true) return false;
        if (!fieldsExactly(records.back(), {"record", "signedIn", "loggedOn", "idValid", "idType", "selfIdRepeatEqual", "personaAvailable"})
            || records.back()["signedIn"] != true || records.back()["loggedOn"] != true || records.back()["idValid"] != true
            || records.back()["idType"] != "user" || records.back()["selfIdRepeatEqual"] != true || !records.back()["personaAvailable"].is_boolean()) return false;
        normalized = records;
        return true;
    }
    catch (...) { return false; }
}

bool normalizeFriendsPeerInformationRetrievalTrace(const fs::path& trace, json& normalized)
{
    try
    {
        std::vector<json> records;
        for (const std::string& line : common::readTrace(trace)) records.push_back(json::parse(line));
        const std::vector<std::string> expected{"initialize", "sign-in-callback", "sign-in-terminal", "persona-listener-armed",
            "user-information-request-issued", "user-information-terminal", "global-persona-data-changed", "self-state"};
        if (records.size() != expected.size()) return false;
        for (std::size_t index = 0; index < expected.size(); ++index)
            if (!records[index].is_object() || records[index].value("record", "") != expected[index]) return false;
        if (!fieldsExactly(records[0], {"record", "result"}) || records[0]["result"] != "returned"
            || !fieldsExactly(records[1], {"record", "result"}) || records[1]["result"] != "success"
            || !fieldsExactly(records[2], {"record", "result"}) || records[2]["result"] != "success"
            || !fieldsExactly(records[3], {"record", "listenerRegistered", "peerRelayConsumed"})
            || records[3]["listenerRegistered"] != true || records[3]["peerRelayConsumed"] != true
            || !fieldsExactly(records[4], {"record", "avatarCriteria"}) || records[4]["avatarCriteria"] != "none"
            || !fieldsExactly(records[5], {"record", "outcome", "callbackPeerEqualsRequested", "callbackPeerValidNonSelf",
                "informationAvailableAfterTerminal", "personaNameNonempty", "personaState"})
            || !records[5]["outcome"].is_string() || (records[5]["outcome"] != "success" && records[5]["outcome"] != "failure" && records[5]["outcome"] != "timeout")
            || records[5]["callbackPeerEqualsRequested"] != true || records[5]["callbackPeerValidNonSelf"] != true
            || records[5]["informationAvailableAfterTerminal"] != true || records[5]["personaNameNonempty"] != true
            || !records[5]["personaState"].is_string() || (records[5]["personaState"] != "online" && records[5]["personaState"] != "offline"
                && records[5]["personaState"] != "unavailable")
            || !fieldsExactly(records[6], {"record", "events"}) || !records[6]["events"].is_array()) return false;
        for (const json& event : records[6]["events"])
        {
            if (!fieldsExactly(event, {"change"}) || !event["change"].is_string()) return false;
        }
        if (!fieldsExactly(records[7], {"record", "signedIn", "loggedOn", "idValid", "idType", "selfIdRepeatEqual", "personaAvailable"})
            || records[7]["signedIn"] != true || records[7]["loggedOn"] != true || records[7]["idValid"] != true
            || records[7]["idType"] != "user" || records[7]["selfIdRepeatEqual"] != true || !records[7]["personaAvailable"].is_boolean()) return false;
        normalized = records;
        return true;
    }
    catch (...) { return false; }
}

bool normalizeMultipleLobbyMembershipTrace(const fs::path& trace, const std::string& profile, json& normalized)
{
    try
    {
        std::vector<json> records;
        for (const std::string& line : common::readTrace(trace)) records.push_back(json::parse(line));
        const std::vector<std::string> expected = profile == "user1"
            ? std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "create-pair", "explicit-configuration", "private-tags",
                "creator-messages", "creator-leave-L1", "creator-leave-L0", "self-state"}
            : std::vector<std::string>{"initialize", "sign-in-callback", "sign-in-terminal", "discover-pair", "join-pair", "joiner-configuration",
                "joiner-messages", "joiner-leave-L1", "joiner-leave-L0", "self-state"};
        if (records.size() != expected.size()) return false;
        for (std::size_t index = 0; index < expected.size(); ++index)
            if (!records[index].is_object() || records[index].value("record", "") != expected[index]) return false;
        if (!fieldsExactly(records[0], {"record", "result"}) || records[0]["result"] != "returned"
            || !fieldsExactly(records[1], {"record", "result"}) || records[1]["result"] != "success"
            || !fieldsExactly(records[2], {"record", "result"}) || records[2]["result"] != "success") return false;
        const auto validLeave = [](const json& record) {
            return fieldsExactly(record, {"record", "result", "reason", "sameLobby"}) && record["result"] == "callback"
                && record["reason"] == "user-left" && record["sameLobby"] == true;
        };
        const auto validMessages = [](const json& record, const bool armed) {
            return fieldsExactly(record, armed
                    ? std::initializer_list<const char*>{"record", "listenerArmedBeforeSends", "callbackOrder", "L0Delivered", "L1Delivered", "senderMatches", "payloadMatches", "onlyKnownLobbies", "publicMessageTypeAvailable"}
                    : std::initializer_list<const char*>{"record", "issuedBackToBack", "L0Scheduled", "L1Scheduled", "callbackOrder", "L0Delivered", "L1Delivered", "senderMatches", "payloadMatches", "onlyKnownLobbies", "publicMessageTypeAvailable"})
                && (!armed || record["listenerArmedBeforeSends"] == true) && (!armed || !record["callbackOrder"].empty())
                && (armed || (record["issuedBackToBack"] == true && record["L0Scheduled"] == true && record["L1Scheduled"] == true))
                && record["L0Delivered"] == true && record["L1Delivered"] == true && record["senderMatches"] == true
                && record["payloadMatches"] == true && record["onlyKnownLobbies"] == true && record["publicMessageTypeAvailable"] == false
                && record["callbackOrder"].is_array() && record["callbackOrder"].size() == 2;
        };
        if (profile == "user1")
        {
            if (!fieldsExactly(records[3], {"record", "issuedBackToBack", "createdCallbackOrder", "enteredCallbackOrder", "L0Success", "L1Success", "createdEnteredIdentity", "distinctLobbies"})
                || records[3]["issuedBackToBack"] != true || records[3]["L0Success"] != true || records[3]["L1Success"] != true || records[3]["createdEnteredIdentity"] != true || records[3]["distinctLobbies"] != true
                || !records[3]["createdCallbackOrder"].is_array() || !records[3]["enteredCallbackOrder"].is_array() || records[3]["createdCallbackOrder"].size() != 2 || records[3]["enteredCallbackOrder"].size() != 2
                || !fieldsExactly(records[4], {"record", "callbackOrder", "allSetOperationsSucceeded", "publicVisible", "joinableVisible", "capacityVisible"})
                || records[4]["allSetOperationsSucceeded"] != true || records[4]["publicVisible"] != true || records[4]["joinableVisible"] != true || records[4]["capacityVisible"] != true
                || !records[4]["callbackOrder"].is_array() || records[4]["callbackOrder"].size() != 6
                || !fieldsExactly(records[5], {"record", "L0Success", "L1Success"}) || records[5]["L0Success"] != true || records[5]["L1Success"] != true
                || !validMessages(records[6], false) || !validLeave(records[7]) || !validLeave(records[8])) return false;
        }
        else if (!fieldsExactly(records[3], {"record", "L0Found", "L1Found", "distinctLobbies", "L0AttemptsBounded", "L1AttemptsBounded"})
            || records[3]["L0Found"] != true || records[3]["L1Found"] != true || records[3]["distinctLobbies"] != true || records[3]["L0AttemptsBounded"] != true || records[3]["L1AttemptsBounded"] != true
            || !fieldsExactly(records[4], {"record", "issuedBackToBack", "enteredCallbackOrder", "L0Success", "L1Success"}) || records[4]["issuedBackToBack"] != true || records[4]["L0Success"] != true || records[4]["L1Success"] != true
            || !records[4]["enteredCallbackOrder"].is_array() || records[4]["enteredCallbackOrder"].size() != 2
            || !fieldsExactly(records[5], {"record", "publicJoinableCapacityVisible"}) || records[5]["publicJoinableCapacityVisible"] != true
            || !validMessages(records[6], true) || !validLeave(records[7]) || !validLeave(records[8])) return false;
        if (!fieldsExactly(records.back(), {"record", "signedIn", "loggedOn", "idValid", "idType", "selfIdRepeatEqual", "personaAvailable"})
            || records.back()["signedIn"] != true || records.back()["loggedOn"] != true || records.back()["idValid"] != true
            || records.back()["idType"] != "user" || records.back()["selfIdRepeatEqual"] != true || !records.back()["personaAvailable"].is_boolean()) return false;
        normalized = records;
        return true;
    }
    catch (...) { return false; }
}

bool normalizeTrace(const fs::path& trace, const ScenarioContract& contract, json& normalized)
{
    try
    {
        const std::vector<std::string> raw = common::readTrace(trace);
        if (raw.size() != contract.recordCount) return false;
        std::vector<json> records;
        for (const std::string& line : raw) records.push_back(json::parse(line));
        if (!fieldsExactly(records[0], {"record", "result"}) || records[0]["record"] != "initialize" || records[0]["result"] != "returned") return false;
        if (!records[1].contains("record") || !records[1].contains("result") || records[1]["record"] != "sign-in-callback") return false;
        const std::string callback = records[1]["result"].is_string() ? records[1]["result"].get<std::string>() : "";
        if (callback == "success")
        {
            if (!fieldsExactly(records[1], {"record", "result"})) return false;
        }
        else if (callback == "failure")
        {
            if (!fieldsExactly(records[1], {"record", "result", "reason"}) || !records[1]["reason"].is_number_integer()) return false;
        }
        else return false;
        if (!fieldsExactly(records[2], {"record", "result"}) || records[2]["record"] != "sign-in-terminal"
            || !records[2]["result"].is_string() || records[2]["result"] != callback) return false;
        const std::size_t selfStateIndex = contract.observesSessionIdRepeatability ? 4 : 3;
        if (contract.observesSessionIdRepeatability
            && (!fieldsExactly(records[3], {"record", "equal"}) || records[3]["record"] != "session-id-repeatability"
                || !records[3]["equal"].is_boolean())) return false;
        if (!fieldsExactly(records[selfStateIndex], {"record", "signedIn", "loggedOn", "idValid", "idType", "selfIdRepeatEqual", "personaAvailable"})
            || records[selfStateIndex]["record"] != "self-state" || !records[selfStateIndex]["signedIn"].is_boolean() || !records[selfStateIndex]["loggedOn"].is_boolean()
            || !records[selfStateIndex]["idValid"].is_boolean() || !records[selfStateIndex]["idType"].is_string() || !records[selfStateIndex]["selfIdRepeatEqual"].is_boolean()
            || !records[selfStateIndex]["personaAvailable"].is_boolean()) return false;
        if (contract.observesGogServicesState
            && (!fieldsExactly(records[4], {"record", "state"}) || records[4]["record"] != "gog-services-state"
                || !records[4]["state"].is_string()
                || (records[4]["state"] != "undefined" && records[4]["state"] != "connected"
                    && records[4]["state"] != "disconnected" && records[4]["state"] != "auth-lost"))) return false;
        normalized = records;
        return true;
    }
    catch (...) { return false; }
}

bool compareTraces(const fs::path& root, const Scenario& scenario, json& report)
{
    const ScenarioContract& contract = *scenario.contract;
    report = json::object();
    report["scenario"] = contract.name;
    report["opaqueIdPolicy"] = observesPublicLobbyOwnerOwnershipTransition(contract)
        ? "raw Galaxy IDs, public collision-marker values, and promoted data are never recorded; only symbolic ownership, member, authorization, and list-absence relations are compared"
        : isStrictPublicLobbyNotJoinableBehavior(contract)
        ? "raw Galaxy IDs, public collision-marker values, configuration values, and timestamps are never recorded; only public nonjoinable configuration, filtered-list absence, no direct join/member/send access, creator sole ownership, and delete-probe relations are compared"
        : observesPublicLobbyFullJoinFailure(contract)
        ? "raw Galaxy IDs, public collision-marker values, configuration values, and timestamps are never recorded; only public terminal result, non-entry, owner/sole-member, and list-absence relations are compared"
        : observesPublicLobbyOwnerCloseLifecycle(contract)
        ? "raw Galaxy IDs, public collision-marker values, and timestamps are never recorded; only symbolic prior-owner, leave-reason, and list-absence relations are compared"
        : contract.observesMultipleLobbyMembership
        ? "raw Galaxy IDs, lobby IDs, message IDs, public collision-marker values, and message payloads are never recorded; only L0/L1-local public relations are compared"
        : contract.observesChatRoomMessageDelivery
        ? "raw Galaxy IDs, room IDs, message IDs, and private message token are never recorded; only symbolic peer, room, send-index, and payload relations are compared"
        : contract.observesFriendsPeerInformation
        ? "raw Galaxy IDs, persona names, avatar data, counts, status text, timestamps, and credentials are never recorded; only symbolic peer relations, terminal outcome, availability, name nonemptiness, persona state, and ordered persona-change diagnostics are retained"
        : observesReliableP2PListenerPeek(contract)
        ? "raw Galaxy IDs, lobby IDs, collision-marker-derived payload bytes, and message lengths are never recorded; only symbolic lobby membership, sender, channel, callback, and non-consuming peek relations are compared"
        : contract.observesPublicLobby
        ? "raw Galaxy IDs and public collision-marker values are never recorded; only validity and creator/joiner/owner/member relations are compared"
        : "raw IDs are never recorded; validity, type, and repeat-equality are lane-local observations";
    bool valid = true;
    for (const char* profile : {"user1", "user2"})
    {
        json universelan;
        json gog;
        const bool universelanValid = isStrictPublicLobbyNotJoinableBehavior(contract)
            ? normalizePublicLobbyNotJoinableBehaviorTrace(root / "universelan" / profile / "trace.jsonl", profile, universelan)
            : observesPublicLobbyFullJoinFailure(contract)
            ? normalizePublicLobbyFullJoinFailureTrace(root / "universelan" / profile / "trace.jsonl", profile, universelan)
            : observesPublicLobbyOwnerOwnershipTransition(contract)
            ? normalizePublicLobbyOwnerOwnershipTransitionTrace(root / "universelan" / profile / "trace.jsonl", profile, universelan)
            : observesPublicLobbyOwnerCloseLifecycle(contract)
            ? normalizePublicLobbyOwnerCloseLifecycleTrace(root / "universelan" / profile / "trace.jsonl", profile, universelan)
            : contract.observesMultipleLobbyMembership
            ? normalizeMultipleLobbyMembershipTrace(root / "universelan" / profile / "trace.jsonl", profile, universelan)
            : contract.observesChatRoomMessageDelivery
            ? normalizeChatRoomMessageDeliveryTrace(root / "universelan" / profile / "trace.jsonl", profile, universelan)
            : contract.observesFriendsPeerInformation
            ? normalizeFriendsPeerInformationRetrievalTrace(root / "universelan" / profile / "trace.jsonl", universelan)
            : observesReliableP2PListenerPeek(contract)
            ? normalizeReliableP2PListenerPeekTrace(root / "universelan" / profile / "trace.jsonl", profile, universelan)
            : contract.observesPublicLobbyDataPropagation
            ? normalizePublicLobbyDataPropagationTrace(root / "universelan" / profile / "trace.jsonl", profile, universelan)
            : contract.observesPublicLobby
            ? normalizePublicLobbyTrace(root / "universelan" / profile / "trace.jsonl", profile, universelan)
            : normalizeTrace(root / "universelan" / profile / "trace.jsonl", contract, universelan);
        const bool gogValid = isStrictPublicLobbyNotJoinableBehavior(contract)
            ? normalizePublicLobbyNotJoinableBehaviorTrace(root / "gog" / profile / "trace.jsonl", profile, gog)
            : observesPublicLobbyFullJoinFailure(contract)
            ? normalizePublicLobbyFullJoinFailureTrace(root / "gog" / profile / "trace.jsonl", profile, gog)
            : observesPublicLobbyOwnerOwnershipTransition(contract)
            ? normalizePublicLobbyOwnerOwnershipTransitionTrace(root / "gog" / profile / "trace.jsonl", profile, gog)
            : observesPublicLobbyOwnerCloseLifecycle(contract)
            ? normalizePublicLobbyOwnerCloseLifecycleTrace(root / "gog" / profile / "trace.jsonl", profile, gog)
            : contract.observesMultipleLobbyMembership
            ? normalizeMultipleLobbyMembershipTrace(root / "gog" / profile / "trace.jsonl", profile, gog)
            : contract.observesChatRoomMessageDelivery
            ? normalizeChatRoomMessageDeliveryTrace(root / "gog" / profile / "trace.jsonl", profile, gog)
            : contract.observesFriendsPeerInformation
            ? normalizeFriendsPeerInformationRetrievalTrace(root / "gog" / profile / "trace.jsonl", gog)
            : observesReliableP2PListenerPeek(contract)
            ? normalizeReliableP2PListenerPeekTrace(root / "gog" / profile / "trace.jsonl", profile, gog)
            : contract.observesPublicLobbyDataPropagation
            ? normalizePublicLobbyDataPropagationTrace(root / "gog" / profile / "trace.jsonl", profile, gog)
            : contract.observesPublicLobby
            ? normalizePublicLobbyTrace(root / "gog" / profile / "trace.jsonl", profile, gog)
            : normalizeTrace(root / "gog" / profile / "trace.jsonl", contract, gog);
        report["lanes"][profile]["universelan"] = universelanValid ? universelan : json("invalid-trace");
        report["lanes"][profile]["gog"] = gogValid ? gog : json("invalid-trace");
        const bool officialOwnerCloseFacts = !observesPublicLobbyOwnerCloseLifecycle(contract) || profile != std::string_view("user2")
            || (gogValid && gog[8]["priorOwnerMemberCallbackObserved"] == false && gog[8]["priorOwnerLeftObserved"] == false
                && gog[8]["globalLobbyLeftCallbackObserved"] == true && gog[8]["globalLobbyClosedObserved"] == true
                && gog[8]["unexpectedGlobalLobbyLeaveReasonObserved"] == false && gog[7]["targetAbsent"] == true);
        const bool terminalSuccess = universelanValid && gogValid && officialOwnerCloseFacts && universelan[2]["result"] == "success" && gog[2]["result"] == "success"
            && (!contract.observesFriendsPeerInformation || (universelan[5]["outcome"] == scenario.requiredTerminalOutcome
                && gog[5]["outcome"] == scenario.requiredTerminalOutcome));
        const bool sessionIdRepeatabilityEqual = !contract.observesSessionIdRepeatability
            || (terminalSuccess && universelan[3]["equal"] == gog[3]["equal"]);
        json comparableUniverselan = universelan;
        json comparableGog = gog;
        if (contract.observesPublicLobby && !observesPublicLobbyFullJoinFailure(contract) && profile == std::string_view("user2") && universelanValid && gogValid)
        {
            // Public-list indexing is eventually consistent; both lanes must satisfy the bounded retry contract,
            // but their successful attempt number is not an identity or callback-behavior relation.
            comparableUniverselan[3].erase("attempts");
            comparableUniverselan[3].erase("retryUsed");
            comparableGog[3].erase("attempts");
            comparableGog[3].erase("retryUsed");
            report["lanes"][profile]["retryConvergenceEquivalent"] = true;
            if (universelan[3]["attempts"] != gog[3]["attempts"] || universelan[3]["retryUsed"] != gog[3]["retryUsed"])
            {
                const bool fasterUniverselanConvergence = universelan[3]["attempts"] < gog[3]["attempts"];
                report["lanes"][profile]["retryConvergenceComparison"] = fasterUniverselanConvergence
                    ? "accepted-difference" : "diagnostic-context-excluded";
            }
        }
        if (observesPublicLobbyOwnerCloseLifecycle(contract) && profile == std::string_view("user2") && universelanValid && gogValid)
        {
            // Callback order and multiplicity between the global listeners are diagnostic, not an SDK ordering contract.
            comparableUniverselan[8].erase("priorOwnerMemberStateSequence");
            comparableUniverselan[8].erase("globalLobbyLeaveReasonSequence");
            comparableUniverselan[8].erase("targetLobbySequence");
            comparableUniverselan[7].erase("attempts");
            comparableGog[8].erase("priorOwnerMemberStateSequence");
            comparableGog[8].erase("globalLobbyLeaveReasonSequence");
            comparableGog[8].erase("targetLobbySequence");
            comparableGog[7].erase("attempts");
            report["lanes"][profile]["ownerCloseListenerSequenceComparison"] = "official-characterized-diagnostic-context-excluded";
            report["lanes"][profile]["postCloseListConvergenceComparison"] = "diagnostic-context-excluded";
        }
        if (observesPublicLobbyOwnerOwnershipTransition(contract) && profile == std::string_view("user2") && universelanValid && gogValid)
        {
            // Global member and owner listener classes have no cross-class callback-order guarantee.
            comparableUniverselan[7].erase("priorOwnerMemberStateSequence");
            comparableUniverselan[7].erase("ownerChangeSequence");
            comparableUniverselan[7].erase("targetLobbySequence");
            comparableUniverselan[10].erase("attempts");
            comparableGog[7].erase("priorOwnerMemberStateSequence");
            comparableGog[7].erase("ownerChangeSequence");
            comparableGog[7].erase("targetLobbySequence");
            comparableGog[10].erase("attempts");
            report["lanes"][profile]["ownershipTransitionListenerSequenceComparison"] = "official-characterized-diagnostic-context-excluded";
            report["lanes"][profile]["postEmptyListConvergenceComparison"] = "diagnostic-context-excluded";
        }
        if (contract.observesPublicLobbyDataPropagation && profile == std::string_view("user2") && universelanValid && gogValid)
        {
            // The SDK requires notification delivery, not a duplicate-count or cross-host timing contract.
            comparableUniverselan[6].erase("callbackCount");
            comparableUniverselan[6].erase("duplicateNotifications");
            comparableGog[6].erase("callbackCount");
            comparableGog[6].erase("duplicateNotifications");
            report["lanes"][profile]["callbackMultiplicityComparison"] = "diagnostic-context-excluded";
        }
        if (contract.observesMultipleLobbyMembership && profile == std::string_view("user2") && universelanValid && gogValid)
        {
            // Official characterization observed both L0,L1 and L1,L0 delivery across independent lobbies.
            // Retain the callback order in the lane traces, but do not turn an unstable cross-lobby order into a compatibility requirement.
            comparableUniverselan[6].erase("callbackOrder");
            comparableGog[6].erase("callbackOrder");
            report["lanes"][profile]["messageCallbackOrderComparison"] = "official-characterized-not-stable;diagnostic-context-excluded";
        }
        if (contract.observesFriendsPeerInformation && universelanValid && gogValid)
        {
            // A later clean full comparison observed terminal none without the semantic event in one official lane.
            comparableUniverselan[6].erase("events");
            comparableGog[6].erase("events");
            report["lanes"][profile]["personaDataChangedComparison"] = "requested-peer-only;official-variation-observed;diagnostic-context-excluded";
        }
        const bool exactEquality = universelanValid && gogValid && universelan == gog && sessionIdRepeatabilityEqual;
        bool acceptedGogServicesStateDifference = false;
        if (scenario.acceptsGogServicesStatePair && universelanValid && gogValid && sessionIdRepeatabilityEqual
            && gog[4]["state"] == "undefined" && universelan[4]["state"] == "connected")
        {
            json stateNeutralUniverselan = universelan;
            json stateNeutralGog = gog;
            stateNeutralUniverselan[4].erase("state");
            stateNeutralGog[4].erase("state");
            acceptedGogServicesStateDifference = stateNeutralUniverselan == stateNeutralGog;
        }
        bool acceptedFriendsPeerPersonaStateDifference = false;
        if (scenario.acceptsFriendsPeerPersonaStatePair && universelanValid && gogValid
            && gog[5]["personaState"] == "offline" && universelan[5]["personaState"] == "online")
        {
            json personaStateNeutralUniverselan = comparableUniverselan;
            json personaStateNeutralGog = comparableGog;
            personaStateNeutralUniverselan[5].erase("personaState");
            personaStateNeutralGog[5].erase("personaState");
            acceptedFriendsPeerPersonaStateDifference = personaStateNeutralUniverselan == personaStateNeutralGog;
        }
        bool acceptedReliableP2PDeliveryDifference = false;
        if (scenario.acceptsReliableP2PDeliveryPair && profile == std::string_view("user2") && universelanValid && gogValid)
        {
            const json& official = gog[7];
            const json& universelanDelivery = universelan[7];
            const bool officialNoDelivery = official["callbackObserved"] == true && official["expectedChannelCallbackObserved"] == false
                && official["nonTargetCallbackObserved"] == true && official["callbackCount"] == 1 && official["expectedChannelCallbackCount"] == 0
                && official["nonTargetCallbackCount"] == 1 && official["callbackContexts"] == json::array({"non-target-channel"})
                && official["callbackSizeMatchesPrivatePayload"] == false && official["firstPeekSucceeded"] == false
                && official["firstPeekSenderValidNonSelf"] == false && official["firstPeekSenderMatchesCreator"] == false
                && official["firstPeekLengthMatchesPrivatePayload"] == false && official["firstPeekPayloadMatchesPrivatePayload"] == false
                && official["secondPeekSucceeded"] == false && official["secondPeekSenderValidNonSelf"] == false
                && official["secondPeekSenderMatchesCreator"] == false && official["secondPeekLengthMatchesPrivatePayload"] == false
                && official["secondPeekPayloadMatchesPrivatePayload"] == false && official["peekResultsEquivalent"] == false;
            const bool universelanDeliveryObserved = universelanDelivery["callbackObserved"] == true && universelanDelivery["expectedChannelCallbackObserved"] == true
                && universelanDelivery["nonTargetCallbackObserved"] == false && universelanDelivery["callbackCount"] == 1
                && universelanDelivery["expectedChannelCallbackCount"] == 1 && universelanDelivery["nonTargetCallbackCount"] == 0
                && universelanDelivery["callbackContexts"] == json::array({"expected-channel-size-matches-private-payload"})
                && universelanDelivery["callbackSizeMatchesPrivatePayload"] == true && universelanDelivery["firstPeekSucceeded"] == true
                && universelanDelivery["firstPeekSenderValidNonSelf"] == true && universelanDelivery["firstPeekSenderMatchesCreator"] == true
                && universelanDelivery["firstPeekLengthMatchesPrivatePayload"] == true && universelanDelivery["firstPeekPayloadMatchesPrivatePayload"] == true
                && universelanDelivery["secondPeekSucceeded"] == true && universelanDelivery["secondPeekSenderValidNonSelf"] == true
                && universelanDelivery["secondPeekSenderMatchesCreator"] == true && universelanDelivery["secondPeekLengthMatchesPrivatePayload"] == true
                && universelanDelivery["secondPeekPayloadMatchesPrivatePayload"] == true && universelanDelivery["peekResultsEquivalent"] == true;
            json neutralUniverselan = universelan;
            json neutralGog = gog;
            neutralUniverselan[7].erase("callbackObserved");
            neutralUniverselan[7].erase("expectedChannelCallbackObserved");
            neutralUniverselan[7].erase("nonTargetCallbackObserved");
            neutralUniverselan[7].erase("callbackCount");
            neutralUniverselan[7].erase("expectedChannelCallbackCount");
            neutralUniverselan[7].erase("nonTargetCallbackCount");
            neutralUniverselan[7].erase("callbackContexts");
            neutralUniverselan[7].erase("callbackSizeMatchesPrivatePayload");
            neutralUniverselan[7].erase("firstPeekSucceeded");
            neutralUniverselan[7].erase("firstPeekSenderValidNonSelf");
            neutralUniverselan[7].erase("firstPeekSenderMatchesCreator");
            neutralUniverselan[7].erase("firstPeekLengthMatchesPrivatePayload");
            neutralUniverselan[7].erase("firstPeekPayloadMatchesPrivatePayload");
            neutralUniverselan[7].erase("secondPeekSucceeded");
            neutralUniverselan[7].erase("secondPeekSenderValidNonSelf");
            neutralUniverselan[7].erase("secondPeekSenderMatchesCreator");
            neutralUniverselan[7].erase("secondPeekLengthMatchesPrivatePayload");
            neutralUniverselan[7].erase("secondPeekPayloadMatchesPrivatePayload");
            neutralUniverselan[7].erase("peekResultsEquivalent");
            neutralGog[7] = neutralUniverselan[7];
            acceptedReliableP2PDeliveryDifference = officialNoDelivery && universelanDeliveryObserved && neutralUniverselan == neutralGog;
        }
        const bool equal = universelanValid && gogValid && (comparableUniverselan == comparableGog || acceptedGogServicesStateDifference
                || acceptedFriendsPeerPersonaStateDifference || acceptedReliableP2PDeliveryDifference)
            && sessionIdRepeatabilityEqual;
        report["lanes"][profile]["equal"] = equal;
        report["lanes"][profile]["comparison"] = exactEquality ? "exact-equality"
            : ((acceptedGogServicesStateDifference || acceptedFriendsPeerPersonaStateDifference || acceptedReliableP2PDeliveryDifference) ? "accepted-difference"
                : (equal ? "diagnostic-context-excluded" : "mismatch"));
        report["lanes"][profile]["terminalSuccess"] = terminalSuccess;
        if (contract.observesSessionIdRepeatability)
            report["lanes"][profile]["sessionIdRepeatabilityEqual"] = sessionIdRepeatabilityEqual;
        valid = valid && terminalSuccess && equal;
    }
    report["status"] = valid ? "match" : "mismatch";
    report["comparisonResult"] = valid ? "matched" : "mismatched";
    return valid;
}

void characterizeTraces(const fs::path& root, json& report)
{
    report = json::object();
    report["scenario"] = "Simple/gog-services-state";
    report["classification"] = "characterization";
    report["comparison"] = "none";
    report["status"] = "characterized";
    report["opaqueIdPolicy"] = "raw IDs and credentials are never recorded; traces contain public symbolic observations only";
    for (const char* profile : {"user1", "user2"})
    {
        for (const char* lane : {"universelan", "gog"})
        {
            const fs::path trace = root / lane / profile / "trace.jsonl";
            json laneReport = json::object();
            try
            {
                const std::vector<std::string> raw = common::readTrace(trace);
                laneReport["raw"] = raw;
                json normalized = json::array();
                for (const std::string& record : raw) normalized.push_back(json::parse(record));
                laneReport["normalized"] = normalized;
            }
            catch (...)
            {
                laneReport["normalized"] = "unavailable";
            }
            report["lanes"][profile][lane] = laneReport;
        }
    }
}

void characterizePublicLobbyDataPropagationTraces(const fs::path& root, json& report)
{
    report = json::object();
    report["scenario"] = "Simple/public-lobby-data-propagation";
    report["classification"] = "characterization";
    report["comparison"] = "none";
    report["status"] = "characterized";
    report["opaqueIdPolicy"] = "raw Galaxy IDs, private token, private key, and private value are never recorded";
    report["crossHostCallbackOrder"] = "not a contract; only observer-armed-before-owner-update and joiner-observed-before-cleanup causal gates are retained";
    for (const char* profile : {"user1", "user2"})
    {
        for (const char* lane : {"universelan", "gog"})
        {
            json laneReport = json::object();
            try
            {
                json records = json::array();
                for (const std::string& line : common::readTrace(root / lane / profile / "trace.jsonl")) records.push_back(json::parse(line));
                laneReport["normalized"] = records;
                if (profile == std::string_view("user2"))
                {
                    for (const json& record : records)
                    {
                        if (record.value("record", "") != "joiner-lobby-data") continue;
                        laneReport["callbackAvailability"] = record.value("callbackAvailable", false);
                        laneReport["memberIdValid"] = record.value("memberIdValid", true);
                        laneReport["sameCallbackCopyVisible"] = record.value("sameCallbackCopyVisible", false);
                        laneReport["eventualCopyVisible"] = record.value("eventualCopyVisible", false);
                        laneReport["duplicateNotifications"] = record.value("duplicateNotifications", false);
                        break;
                    }
                }
            }
            catch (...) { laneReport["normalized"] = "unavailable"; }
            report["lanes"][profile][lane] = laneReport;
        }
    }
}

void characterizePublicLobbyFullJoinFailureTraces(const fs::path& root, json& report)
{
    report = json::object();
    report["scenario"] = "Simple/public-lobby-full-join-failure";
    report["classification"] = "official-gog-only-characterization";
    report["comparison"] = "none";
    report["status"] = "characterized";
    report["opaqueIdPolicy"] = "raw Galaxy IDs, public collision-marker values, configuration values, timestamps, controls, and runtime output are never retained";
    report["headerFacts"] = "RequestLobbyList consumes its filters and supports an explicit full-lobby request. JoinLobby reports its terminal result asynchronously. Member queries and lobby messaging require membership, so the rejected joiner uses only list, lobby-data retrieval, and public state calls.";
    report["ordering"] = "IMatchmaking records are ordered within each host. Creator-ready, rejected-join terminal, creator leave, and post-empty absence are causal gates only; no cross-host total order is asserted.";
    for (const char* profile : {"user1", "user2"})
    {
        json laneReport = json::object();
        try
        {
            json records = json::array();
            for (const std::string& line : common::readTrace(root / "gog" / profile / "trace.jsonl")) records.push_back(json::parse(line));
            laneReport["orderedIMatchmakingRecords"] = records;
            if (profile == std::string_view("user2") && records.size() > 7)
            {
                laneReport["joinTerminalResult"] = records[5].value("terminalResult", "unavailable");
                laneReport["failedWithoutEntry"] = records[6].value("failedWithoutEntry", false);
                laneReport["postEmptyListAbsentObserved"] = records[7].value("targetAbsent", false);
            }
        }
        catch (...) { laneReport["orderedIMatchmakingRecords"] = "unavailable"; }
        report["lanes"][profile]["gog"] = laneReport;
    }
}

void characterizePublicLobbyNotJoinableBehaviorTraces(const fs::path& root, json& report)
{
    report = json::object();
    report["scenario"] = "Simple/public-lobby-not-joinable-behavior";
    report["classification"] = "official-gog-only-characterization";
    report["comparison"] = "none";
    report["status"] = "characterized";
    report["opaqueIdPolicy"] = "raw Galaxy IDs, public collision-marker values, configuration values, timestamps, controls, and runtime output are never retained";
    report["headerFacts"] = "SetLobbyJoinable updates public lobby joinability asynchronously. RequestLobbyList consumes its filters. JoinLobby reports its terminal result asynchronously. The public headers do not state whether a nonjoinable tagged public lobby appears in a filtered list or which terminal result follows a listed join attempt.";
    report["ordering"] = "IMatchmaking records are ordered within each host. Creator-ready, joiner list completion, creator terminal leave, and post-delete list completion are causal gates only; no cross-host callback order is asserted.";
    for (const char* profile : {"user1", "user2"})
    {
        json laneReport = json::object();
        try
        {
            json records = json::array();
            for (const std::string& line : common::readTrace(root / "gog" / profile / "trace.jsonl")) records.push_back(json::parse(line));
            laneReport["orderedIMatchmakingRecords"] = records;
            if (profile == std::string_view("user2"))
            {
                for (const json& record : records)
                {
                    if (record.value("record", "") == "list")
                    {
                        laneReport["listResult"] = record.value("result", "unavailable");
                        laneReport["selectedFromFilteredList"] = record.value("selectedFromFilteredList", false);
                    }
                    else if (record.value("record", "") == "join")
                    {
                        laneReport["joinIssued"] = true;
                        laneReport["joinTerminalResult"] = record.value("terminalResult", "unavailable");
                        laneReport["joinEntered"] = record.value("entered", false);
                    }
                    else if (record.value("record", "") == "joiner-access")
                    {
                        laneReport["noDirectIdJoin"] = !record.value("directIdJoinAttempted", true);
                        laneReport["noMemberOnlyCalls"] = !record.value("memberOnlyCallsAttempted", true)
                            && !record.value("memberDataCallsAttempted", true);
                        laneReport["noLobbySend"] = !record.value("sendLobbyMessageAttempted", true);
                    }
                    else if (record.value("record", "") == "post-delete-list")
                    {
                        laneReport["postDeleteListResult"] = record.value("result", "unavailable");
                        laneReport["postDeleteTargetAbsent"] = record.value("targetAbsent", false);
                    }
                }
                if (!laneReport.contains("joinIssued")) laneReport["joinIssued"] = false;
            }
        }
        catch (...) { laneReport["orderedIMatchmakingRecords"] = "unavailable"; }
        report["lanes"][profile]["gog"] = laneReport;
    }
}

void characterizePublicLobbyOwnerCloseLifecycleTraces(const fs::path& root, json& report)
{
    report = json::object();
    report["scenario"] = "Simple/public-lobby-owner-close-lifecycle";
    report["classification"] = "official-gog-only-characterization";
    report["comparison"] = "none";
    report["status"] = "characterized";
    report["opaqueIdPolicy"] = "raw Galaxy IDs, private tokens, tag values, data, timestamps, credentials, controls, and runtime output are never retained";
    report["headerGuarantee"] = "LeaveLobby generically documents other-member notifications and a local user-left callback; the FCM topology documents owner disconnection closing a lobby. The observed normal-FCM-close prior-owner callback absence is empirical, not a header guarantee.";
    report["listenerOrdering"] = "target-lobby sequences retain local diagnostic order only; global member-state and global lobby-left listener order and multiplicity are not contracts";
    for (const char* profile : {"user1", "user2"})
    {
        json laneReport = json::object();
        try
        {
            json records = json::array();
            for (const std::string& line : common::readTrace(root / "gog" / profile / "trace.jsonl")) records.push_back(json::parse(line));
            laneReport["orderedIMatchmakingRecords"] = records;
            if (profile == std::string_view("user2") && records.size() > 8)
            {
                laneReport["priorOwnerMemberCallbackObserved"] = records[8].value("priorOwnerMemberCallbackObserved", false);
                laneReport["priorOwnerLeftObserved"] = records[8].value("priorOwnerLeftObserved", false);
                laneReport["globalLobbyLeftCallbackObserved"] = records[8].value("globalLobbyLeftCallbackObserved", false);
                laneReport["globalLobbyClosedObserved"] = records[8].value("globalLobbyClosedObserved", false);
                laneReport["unexpectedGlobalLobbyLeaveReasonObserved"] = records[8].value("unexpectedGlobalLobbyLeaveReasonObserved", true);
                laneReport["postCloseListAbsentObserved"] = records[7].value("targetAbsent", false);
            }
        }
        catch (...) { laneReport["orderedIMatchmakingRecords"] = "unavailable"; }
        report["lanes"][profile]["gog"] = laneReport;
    }
}

void characterizePublicLobbyOwnerOwnershipTransitionTraces(const fs::path& root, json& report)
{
    report = json::object();
    report["scenario"] = "Simple/public-lobby-owner-ownership-transition";
    report["classification"] = "official-gog-only-characterization";
    report["comparison"] = "none";
    report["status"] = "characterized";
    report["opaqueIdPolicy"] = "raw Galaxy IDs, private tokens, tag values, promoted data, timestamps, credentials, controls, and runtime output are never retained";
    report["listenerOrdering"] = "member-state and owner-change target-lobby sequences retain local diagnostic order only; cross-listener order and multiplicity are not contracts";
    for (const char* profile : {"user1", "user2"})
    {
        json laneReport = json::object();
        try
        {
            json records = json::array();
            for (const std::string& line : common::readTrace(root / "gog" / profile / "trace.jsonl")) records.push_back(json::parse(line));
            laneReport["orderedIMatchmakingRecords"] = records;
            if (profile == std::string_view("user2") && records.size() > 10)
            {
                laneReport["priorOwnerLeftObserved"] = records[7].value("priorOwnerLeftObserved", false);
                laneReport["ownerChangedToSelfObserved"] = records[7].value("ownerChangedToSelfObserved", false);
                laneReport["ownerNowSelf"] = records[7].value("ownerNowSelf", false);
                laneReport["membersOnlySelf"] = records[7].value("membersOnlySelf", false);
                laneReport["promotedOwnerDataAuthorized"] = records[8].value("setLobbyDataSuccess", false)
                    && records[8].value("copiedValueVisible", false);
                laneReport["postEmptyListAbsentObserved"] = records[10].value("targetAbsent", false);
            }
        }
        catch (...) { laneReport["orderedIMatchmakingRecords"] = "unavailable"; }
        report["lanes"][profile]["gog"] = laneReport;
    }
}

void characterizeMultipleLobbyMembershipTraces(const fs::path& root, json& report)
{
    report = json::object();
    report["scenario"] = "Advanced/multiple-lobby-membership-and-message-isolation";
    report["classification"] = "official-gog-only-characterization";
    report["comparison"] = "none";
    report["status"] = "characterized";
    report["opaqueIdPolicy"] = "raw Galaxy IDs, lobby IDs, message IDs, private tags, and message payloads are never recorded";
    report["publicMessageType"] = "unavailable: ILobbyMessageListener and IMatchmaking::GetLobbyMessage expose no message-type field";
    for (const char* profile : {"user1", "user2"})
    {
        json laneReport = json::object();
        try
        {
            json records = json::array();
            for (const std::string& line : common::readTrace(root / "gog" / profile / "trace.jsonl")) records.push_back(json::parse(line));
            laneReport["orderedIMatchmakingRecords"] = records;
        }
        catch (...) { laneReport["orderedIMatchmakingRecords"] = "unavailable"; }
        report["lanes"][profile]["gog"] = laneReport;
    }
}

void characterizeChatRoomMessageDeliveryTraces(const fs::path& root, const bool officialGogOnly, json& report)
{
    report = json::object();
    report["scenario"] = "Simple/chat-room-message-delivery";
    report["classification"] = officialGogOnly ? "official-gog-only-characterization" : "characterization";
    report["comparison"] = "none";
    report["status"] = "characterized";
    report["opaqueIdPolicy"] = "raw Galaxy IDs, room IDs, message IDs, and private message token are never recorded";
    report["crossHostCallbackOrder"] = "not a contract; receiver arming precedes sender release, while sender terminal and receiver message callbacks have no required cross-host order";
    for (const char* profile : {"user1", "user2"})
    {
        const std::vector<const char*> lanes = officialGogOnly ? std::vector<const char*>{"gog"} : std::vector<const char*>{"universelan", "gog"};
        for (const char* lane : lanes)
        {
            json laneReport = json::object();
            try
            {
                json records = json::array();
                for (const std::string& line : common::readTrace(root / lane / profile / "trace.jsonl")) records.push_back(json::parse(line));
                laneReport["orderedIChatRecords"] = records;
            }
            catch (...) { laneReport["orderedIChatRecords"] = "unavailable"; }
            report["lanes"][profile][lane] = laneReport;
        }
    }
}

void characterizeFriendsPeerInformationRetrievalTraces(const fs::path& root, json& report)
{
    report = json::object();
    report["scenario"] = "Simple/friends-peer-information-retrieval";
    report["classification"] = "official-gog-only-characterization";
    report["comparison"] = "none";
    report["status"] = "characterized";
    report["opaqueIdPolicy"] = "raw Galaxy IDs, persona names, avatar data, counts, status text, timestamps, and credentials are never recorded";
    report["globalPersonaDataChanged"] = "requested-peer symbolic callback events are retained without sorting; a later official variation keeps them diagnostic";
    for (const char* profile : {"user1", "user2"})
    {
        json laneReport = json::object();
        try
        {
            json records = json::array();
            for (const std::string& line : common::readTrace(root / "gog" / profile / "trace.jsonl")) records.push_back(json::parse(line));
            laneReport["orderedIFriendsRecords"] = records;
        }
        catch (...) { laneReport["orderedIFriendsRecords"] = "unavailable"; }
        report["lanes"][profile]["gog"] = laneReport;
    }
}

void characterizeReliableP2PListenerPeekTraces(const fs::path& root, json& report)
{
    report = json::object();
    report["scenario"] = "Simple/reliable-p2p-listener-peek";
    report["classification"] = "official-gog-only-characterization";
    report["comparison"] = "none";
    report["status"] = "characterized";
    report["opaqueIdPolicy"] = "raw Galaxy IDs, lobby IDs, collision-marker-derived payload bytes, and message lengths are never retained";
    report["headerFacts"] = "SendP2PPacket returns whether sending was scheduled; P2P_SEND_RELIABLE does not prove delivery. PeekP2PPacket is non-consuming, and the listener-mode header directs callers to peek during notification rather than poll, read, or pop.";
    report["diagnosticFacts"] = "listener callback multiplicity, callback order, and cross-host send-to-callback timing are retained as diagnostics only";
    for (const char* profile : {"user1", "user2"})
    {
        json laneReport = json::object();
        try
        {
            json records = json::array();
            for (const std::string& line : common::readTrace(root / "gog" / profile / "trace.jsonl")) records.push_back(json::parse(line));
            laneReport["orderedINetworkingRecords"] = records;
            if (profile == std::string_view("user2") && records.size() > 8)
            {
                laneReport["callbackObserved"] = records[7].value("callbackObserved", false);
                laneReport["expectedChannelCallbackObserved"] = records[7].value("expectedChannelCallbackObserved", false);
                laneReport["nonTargetCallbackObserved"] = records[7].value("nonTargetCallbackObserved", false);
                laneReport["twoSuccessfulPeekRelationsObserved"] = records[7].value("firstPeekSucceeded", false)
                    && records[7].value("secondPeekSucceeded", false) && records[7].value("peekResultsEquivalent", false);
                laneReport["listenerDestroyedBeforeShutdown"] = records[8].value("destroyedBeforeShutdown", false);
            }
        }
        catch (...) { laneReport["orderedINetworkingRecords"] = "unavailable"; }
        report["lanes"][profile]["gog"] = laneReport;
    }
}

void printFriendsPeerInformationCharacterizationResult(const json& report)
{
    std::cout << "BEHAVIOUR_TEST CHARACTERIZATION scenario=Simple/friends-peer-information-retrieval comparison=none";
    for (const char* profile : {"user1", "user2"})
    {
        const json& records = report["lanes"][profile]["gog"]["orderedIFriendsRecords"];
        const bool terminalSuccess = records.is_array() && records.size() == 8 && records[5].value("outcome", "") == "success";
        const std::string state = terminalSuccess ? records[5].value("personaState", "unavailable") : "unavailable";
        const bool listenerEventObserved = records.is_array() && records.size() == 8 && records[6]["events"].is_array() && !records[6]["events"].empty();
        std::cout << ' ' << profile << "=terminal-" << (terminalSuccess ? "success" : "not-success")
            << ",persona-state-" << state << ",persona-event-observed-" << (listenerEventObserved ? "true" : "false")
            << ",ordered-persona-events-" << (records.is_array() && records.size() == 8 ? records[6]["events"].dump() : "unavailable");
    }
    std::cout << std::endl;
}

void writeReport(const fs::path& root, const json& report)
{
    writeFile(root / "normalized-comparison.json", report.dump(2) + "\n");
}

void printComparisonResult(const json& report, const ScenarioContract& contract)
{
    std::cout << "BEHAVIOUR_TEST RESULT scenario=" << contract.name
        << " comparison=" << report.value("comparisonResult", "mismatched");
    if (contract.observesPublicLobby || contract.observesChatRoomMessageDelivery)
        std::cout << " exitCleanup=" << report.value("exitCleanup", "unavailable");
    if (contract.observesGogServicesState)
    {
        std::cout << " officialGogServicesState=";
        for (const char* profile : {"user1", "user2"})
        {
            if (profile != std::string_view("user1")) std::cout << ',';
            const json& lane = report["lanes"][profile]["gog"];
            const std::string state = lane.is_array() && lane.size() == contract.recordCount
                && lane[4].is_object() && lane[4].contains("state") && lane[4]["state"].is_string()
                ? lane[4]["state"].get<std::string>() : "unavailable";
            std::cout << profile << ':' << state;
        }
        std::cout << " universelanGogServicesState=";
        for (const char* profile : {"user1", "user2"})
        {
            if (profile != std::string_view("user1")) std::cout << ',';
            const json& lane = report["lanes"][profile]["universelan"];
            const std::string state = lane.is_array() && lane.size() == contract.recordCount
                && lane[4].is_object() && lane[4].contains("state") && lane[4]["state"].is_string()
                ? lane[4]["state"].get<std::string>() : "unavailable";
            std::cout << profile << ':' << state;
        }
        std::cout << " stateComparison=";
        for (const char* profile : {"user1", "user2"})
        {
            if (profile != std::string_view("user1")) std::cout << ',';
            std::cout << profile << ':' << report["lanes"][profile].value("comparison", "mismatch");
        }
    }
    if (contract.observesSessionIdRepeatability)
    {
        std::cout << " officialSessionIdRepeatEqual=";
        for (const char* profile : {"user1", "user2"})
        {
            if (profile != std::string_view("user1")) std::cout << ',';
            const json& lane = report["lanes"][profile]["gog"];
            const std::string equal = lane.is_array() && lane.size() == contract.recordCount
                && lane[3].is_object() && lane[3].contains("equal") && lane[3]["equal"].is_boolean()
                ? (lane[3]["equal"].get<bool>() ? "true" : "false") : "unavailable";
            std::cout << profile << ':' << equal;
        }
    }
    std::cout << std::endl;
}

void printCharacterizationResult(const fs::path& root)
{
    std::cout << "BEHAVIOUR_TEST CHARACTERIZATION comparison=none runDirectory="
        << root.string() << std::endl;
}

void printPublicLobbyFullJoinFailureCharacterizationResult(const json& report)
{
    std::cout << "BEHAVIOUR_TEST CHARACTERIZATION scenario=Simple/public-lobby-full-join-failure comparison=none";
    const json& joiner = report["lanes"]["user2"]["gog"];
    std::cout << " join-terminal=" << joiner.value("joinTerminalResult", "unavailable")
        << ",non-entry=" << (joiner.value("failedWithoutEntry", false) ? "true" : "false")
        << ",post-empty-absence=" << (joiner.value("postEmptyListAbsentObserved", false) ? "true" : "false") << std::endl;
}

void printPublicLobbyNotJoinableBehaviorCharacterizationResult(const json& report)
{
    const json& joiner = report["lanes"]["user2"]["gog"];
    std::cout << "BEHAVIOUR_TEST CHARACTERIZATION scenario=Simple/public-lobby-not-joinable-behavior comparison=none"
        << " list-result=" << joiner.value("listResult", "unavailable")
        << ",selected=" << (joiner.value("selectedFromFilteredList", false) ? "true" : "false")
        << ",join-issued=" << (joiner.value("joinIssued", false) ? "true" : "false");
    if (joiner.value("joinIssued", false))
        std::cout << ",join-terminal=" << joiner.value("joinTerminalResult", "unavailable")
            << ",entered=" << (joiner.value("joinEntered", false) ? "true" : "false");
    std::cout << ",post-delete-absence=" << (joiner.value("postDeleteTargetAbsent", false) ? "true" : "false") << std::endl;
}
}

int run(const Arguments& arguments, const Scenario& scenario)
{
    const bool officialGogOnlyChatCharacterization = arguments.characterizeOfficialGogChatRoomMessageDelivery;
    const bool officialGogOnlyFriendsCharacterization = arguments.characterizeOfficialGogFriendsPeerInformationRetrieval;
    const bool officialGogOnlyOwnerCloseCharacterization = arguments.characterizeOfficialGogPublicLobbyOwnerCloseLifecycle;
    const bool officialGogOnlyOwnershipTransitionCharacterization = arguments.characterizeOfficialGogPublicLobbyOwnerOwnershipTransition;
    const bool officialGogOnlyNotJoinableBehaviorCharacterization = arguments.characterizeOfficialGogPublicLobbyNotJoinableBehavior;
    const bool officialGogOnlyFullJoinFailureCharacterization = arguments.characterizeOfficialGogPublicLobbyFullJoinFailure;
    const bool officialGogOnlyReliableP2PListenerPeekCharacterization = arguments.characterizeOfficialGogReliableP2PListenerPeek;
    if (!fs::is_regular_file(arguments.gogHost) || !fs::is_directory(arguments.gogRuntimeDirectory)
        || (!(officialGogOnlyChatCharacterization || officialGogOnlyFriendsCharacterization || officialGogOnlyOwnerCloseCharacterization || officialGogOnlyOwnershipTransitionCharacterization || officialGogOnlyNotJoinableBehaviorCharacterization || officialGogOnlyFullJoinFailureCharacterization || officialGogOnlyReliableP2PListenerPeekCharacterization) && (!fs::is_regular_file(arguments.universelanHost)
            || !fs::is_regular_file(arguments.clientDll) || !fs::is_regular_file(arguments.server)))) throw std::runtime_error("Preflight failed");

    std::mt19937_64 random(std::random_device{}());
    fs::path root;
    for (int attempt = 0; attempt < 16; ++attempt)
    {
        root = fs::temp_directory_path() / "universelan-behaviour-tests"
            / (std::string(scenario.contract->hostScenario) + "-" + std::to_string(random()));
        std::error_code rootError;
        if (fs::create_directories(root, rootError) && !rootError) break;
        root.clear();
    }
    if (root.empty()) throw std::runtime_error("Unable to create private run root");
    const std::string privateToken = "bt-" + std::to_string(random()) + std::to_string(random());
    const std::uint16_t privatePort = static_cast<std::uint16_t>(38000 + random() % 2000);
    Child server;
    json report;
    bool success = false;
    bool cleanupAcknowledged = !scenario.contract->observesPublicLobby;
    bool receiverArmedBeforeSenderRelease = false;
    bool chatHostsExited = false;
    bool personaListenersReadyBeforePeerRelay = false;
    bool friendsHostsExited = false;
    try
    {
        if (!(officialGogOnlyChatCharacterization || officialGogOnlyFriendsCharacterization || officialGogOnlyOwnerCloseCharacterization || officialGogOnlyOwnershipTransitionCharacterization || officialGogOnlyNotJoinableBehaviorCharacterization || officialGogOnlyFullJoinFailureCharacterization || officialGogOnlyReliableP2PListenerPeekCharacterization))
        {
            const fs::path serverDirectory = root / "universelan" / "server";
            writeServerConfiguration(serverDirectory, privatePort);
            if (!scenario.contract->observesChatRoomMessageDelivery && !scenario.contract->observesFriendsPeerInformation) server.log = serverDirectory / "stdout.log";
            if (!startChild(server, arguments.server, {}, serverDirectory)) throw std::runtime_error("Unable to start server");
            if (!scenario.contract->observesChatRoomMessageDelivery && !scenario.contract->observesFriendsPeerInformation)
            {
                const auto serverDeadline = std::chrono::steady_clock::now() + std::chrono::seconds(10);
                while (std::chrono::steady_clock::now() < serverDeadline)
                {
                    updateChild(server);
                    if (server.exited) throw std::runtime_error("Server exited");
                    if (logContains(server.log, "Listening...")) break;
                    std::this_thread::sleep_for(std::chrono::milliseconds(20));
                }
                if (!logContains(server.log, "Listening...")) throw std::runtime_error("Server readiness timeout");
            }
            else
            {
                updateChild(server);
                if (server.exited) throw std::runtime_error("Server exited");
            }
        }

        const bool officialGogOnlyCharacterization = (scenario.characterization && scenario.contract->observesMultipleLobbyMembership)
            || officialGogOnlyOwnerCloseCharacterization || officialGogOnlyOwnershipTransitionCharacterization || officialGogOnlyNotJoinableBehaviorCharacterization || officialGogOnlyFullJoinFailureCharacterization || officialGogOnlyReliableP2PListenerPeekCharacterization;
        std::vector<HostLaunch> universelanLaunches;
        std::vector<HostLaunch> gogLaunches;
        for (const char* profile : {"user1", "user2"})
        {
            const fs::path gogDirectory = root / "gog" / profile;
            fs::create_directories(gogDirectory);
            const fs::path gogControl = gogDirectory / "control";
            if (!(officialGogOnlyChatCharacterization || officialGogOnlyFriendsCharacterization || officialGogOnlyOwnerCloseCharacterization || officialGogOnlyOwnershipTransitionCharacterization || officialGogOnlyNotJoinableBehaviorCharacterization || officialGogOnlyFullJoinFailureCharacterization || officialGogOnlyReliableP2PListenerPeekCharacterization))
            {
                const fs::path universelanDirectory = root / "universelan" / profile;
                fs::create_directories(universelanDirectory);
                writeUniverselanConfiguration(universelanDirectory, profile, privatePort);
                const fs::path universelanControl = universelanDirectory / "control";
                if (scenario.contract->observesPublicLobby)
                    writePrivateControl(universelanControl, "token=" + privateToken + "-universelan\ncreator-ready=0\njoiner-joined=0\ncreator-two-member=0\njoiner-left=0\njoiner-lifecycle-armed=0\ncreator-left=0\npost-empty-list-absent=0\nobserver-armed=0\ncreator-data-update-complete=0\njoiner-data-observed=0\np2p-listener-armed=0\np2p-sender-scheduled=0\np2p-peek-complete=0\njoiner-failure-observed=0\njoiner-nonmember-complete=0\nabort=0\n");
                else if (scenario.contract->observesChatRoomMessageDelivery)
                {
                    writePrivateControl(universelanControl, "receiver-armed=0\nabort=0\n");
                    writePrivateControl(universelanDirectory / "expected-token-relay", privateToken);
                }
                else if (scenario.contract->observesFriendsPeerInformation)
                    writePrivateControl(universelanControl, "abort=0\n");
                universelanLaunches.push_back({stageHost(arguments.universelanHost, universelanDirectory), universelanDirectory,
                    universelanDirectory / "trace.jsonl", universelanControl, "universelan", profile});
                stageUniverselanRuntime(arguments, universelanDirectory);
            }
            if (scenario.contract->observesPublicLobby)
            {
                writePrivateControl(gogControl, "token=" + privateToken + "-gog\ncreator-ready=0\njoiner-joined=0\ncreator-two-member=0\njoiner-left=0\njoiner-lifecycle-armed=0\ncreator-left=0\npost-empty-list-absent=0\nobserver-armed=0\ncreator-data-update-complete=0\njoiner-data-observed=0\np2p-listener-armed=0\np2p-sender-scheduled=0\np2p-peek-complete=0\njoiner-failure-observed=0\njoiner-nonmember-complete=0\nabort=0\n");
            }
            else if (scenario.contract->observesChatRoomMessageDelivery)
            {
                writePrivateControl(gogControl, "receiver-armed=0\nabort=0\n");
                writePrivateControl(gogDirectory / "expected-token-relay", privateToken);
            }
            else if (scenario.contract->observesFriendsPeerInformation)
                writePrivateControl(gogControl, "abort=0\n");
            gogLaunches.push_back({stageHost(arguments.gogHost, gogDirectory), gogDirectory, gogDirectory / "trace.jsonl", gogControl, "gog", profile});
            stageGogRuntime(arguments, gogDirectory);
        }

        bool processesSucceeded = false;
        std::vector<Child> completedHosts;
        std::vector<std::string> callbackGateDiscoveryOrder;
        if (scenario.contract->observesPublicLobby)
        {
            if (officialGogOnlyCharacterization) universelanLaunches = gogLaunches;
            else universelanLaunches.insert(universelanLaunches.end(), gogLaunches.begin(), gogLaunches.end());
            processesSucceeded = runPublicLobbyHosts(universelanLaunches, *scenario.contract, scenario.timeoutSeconds, completedHosts, cleanupAcknowledged, callbackGateDiscoveryOrder);
            report["exitCleanup"] = cleanupAcknowledged ? "acknowledged" : "not-acknowledged";
        }
        else if (scenario.contract->observesChatRoomMessageDelivery)
        {
            if (officialGogOnlyChatCharacterization) universelanLaunches = gogLaunches;
            else universelanLaunches.insert(universelanLaunches.end(), gogLaunches.begin(), gogLaunches.end());
            processesSucceeded = runChatRoomMessageDeliveryHosts(universelanLaunches, *scenario.contract, scenario.timeoutSeconds, completedHosts,
                receiverArmedBeforeSenderRelease, chatHostsExited);
            report["exitCleanup"] = chatHostsExited ? "all-hosts-exited" : "host-exit-incomplete";
            report["causalGates"] = {{"receiverArmedBeforeSenderRelease", receiverArmedBeforeSenderRelease}};
        }
        else if (scenario.contract->observesFriendsPeerInformation)
        {
            if (officialGogOnlyFriendsCharacterization) universelanLaunches = gogLaunches;
            else universelanLaunches.insert(universelanLaunches.end(), gogLaunches.begin(), gogLaunches.end());
            processesSucceeded = runFriendsPeerInformationRetrievalHosts(universelanLaunches, *scenario.contract, scenario.timeoutSeconds,
                completedHosts, personaListenersReadyBeforePeerRelay, friendsHostsExited);
            report["exitCleanup"] = friendsHostsExited ? "all-hosts-exited" : "host-exit-incomplete";
            report["causalGates"] = {{"personaListenersReadyBeforePeerRelay", personaListenersReadyBeforePeerRelay}};
        }
        else if (scenario.laneMode == "concurrent")
        {
            universelanLaunches.insert(universelanLaunches.end(), gogLaunches.begin(), gogLaunches.end());
            processesSucceeded = runHosts(universelanLaunches, *scenario.contract, scenario.timeoutSeconds, completedHosts);
        }
        else
        {
            processesSucceeded = runHosts(universelanLaunches, *scenario.contract, scenario.timeoutSeconds, completedHosts);
            if (processesSucceeded)
            {
                std::vector<Child> completedGogHosts;
                processesSucceeded = runHosts(gogLaunches, *scenario.contract, scenario.timeoutSeconds, completedGogHosts);
                completedHosts.insert(completedHosts.end(), std::make_move_iterator(completedGogHosts.begin()), std::make_move_iterator(completedGogHosts.end()));
            }
        }
        if (!processesSucceeded)
        {
            if (scenario.characterization && scenario.contract->observesChatRoomMessageDelivery)
            {
                characterizeChatRoomMessageDeliveryTraces(root, officialGogOnlyChatCharacterization, report);
            }
            else if (scenario.characterization && scenario.contract->observesFriendsPeerInformation)
            {
                characterizeFriendsPeerInformationRetrievalTraces(root, report);
            }
            else if (scenario.characterization && scenario.contract->observesMultipleLobbyMembership)
            {
                characterizeMultipleLobbyMembershipTraces(root, report);
            }
            else if (scenario.characterization && scenario.contract->observesPublicLobbyDataPropagation)
            {
                characterizePublicLobbyDataPropagationTraces(root, report);
                report["callbackGateDiscoveryOrder"] = callbackGateDiscoveryOrder;
            }
            else if (scenario.characterization && observesReliableP2PListenerPeek(*scenario.contract))
                characterizeReliableP2PListenerPeekTraces(root, report);
            else if (scenario.characterization && observesPublicLobbyNotJoinableBehavior(*scenario.contract))
                characterizePublicLobbyNotJoinableBehaviorTraces(root, report);
            else if (scenario.characterization && observesPublicLobbyFullJoinFailure(*scenario.contract))
                characterizePublicLobbyFullJoinFailureTraces(root, report);
            else if (scenario.characterization && observesPublicLobbyOwnerCloseLifecycle(*scenario.contract))
                characterizePublicLobbyOwnerCloseLifecycleTraces(root, report);
            else if (scenario.characterization && observesPublicLobbyOwnerOwnershipTransition(*scenario.contract))
                characterizePublicLobbyOwnerOwnershipTransitionTraces(root, report);
            else if (scenario.characterization) characterizeTraces(root, report);
            else compareTraces(root, scenario, report);
            if (scenario.contract->observesPublicLobby) report["exitCleanup"] = cleanupAcknowledged ? "acknowledged" : "not-acknowledged";
            addProcessFailures(report, completedHosts);
            report["status"] = "process-failure";
            throw std::runtime_error("Host process failed");
        }
        if (scenario.characterization)
        {
            if (scenario.contract->observesChatRoomMessageDelivery)
            {
                characterizeChatRoomMessageDeliveryTraces(root, officialGogOnlyChatCharacterization, report);
            }
            else if (scenario.contract->observesFriendsPeerInformation)
            {
                characterizeFriendsPeerInformationRetrievalTraces(root, report);
            }
            else if (scenario.contract->observesMultipleLobbyMembership)
            {
                characterizeMultipleLobbyMembershipTraces(root, report);
            }
            else if (scenario.contract->observesPublicLobbyDataPropagation)
            {
                characterizePublicLobbyDataPropagationTraces(root, report);
                report["callbackGateDiscoveryOrder"] = callbackGateDiscoveryOrder;
            }
            else if (observesReliableP2PListenerPeek(*scenario.contract))
                characterizeReliableP2PListenerPeekTraces(root, report);
            else if (observesPublicLobbyNotJoinableBehavior(*scenario.contract))
                characterizePublicLobbyNotJoinableBehaviorTraces(root, report);
            else if (observesPublicLobbyFullJoinFailure(*scenario.contract))
                characterizePublicLobbyFullJoinFailureTraces(root, report);
            else if (observesPublicLobbyOwnerCloseLifecycle(*scenario.contract))
                characterizePublicLobbyOwnerCloseLifecycleTraces(root, report);
            else if (observesPublicLobbyOwnerOwnershipTransition(*scenario.contract))
                characterizePublicLobbyOwnerOwnershipTransitionTraces(root, report);
            else characterizeTraces(root, report);
            success = true;
            if (scenario.contract->observesFriendsPeerInformation)
            {
                for (const char* profile : {"user1", "user2"})
                {
                    const json& records = report["lanes"][profile]["gog"]["orderedIFriendsRecords"];
                    success = success && records.is_array() && records.size() == 8
                        && records[5].value("outcome", "") == scenario.requiredTerminalOutcome;
                    if (!success) break;
                }
            }
        }
        else success = compareTraces(root, scenario, report);
        if (scenario.contract->observesPublicLobby) report["exitCleanup"] = cleanupAcknowledged ? "acknowledged" : "not-acknowledged";
        if (scenario.contract->observesChatRoomMessageDelivery)
        {
            report["exitCleanup"] = chatHostsExited ? "all-hosts-exited" : "host-exit-incomplete";
            report["causalGates"] = {{"receiverArmedBeforeSenderRelease", receiverArmedBeforeSenderRelease}};
        }
        if (scenario.contract->observesFriendsPeerInformation)
        {
            report["exitCleanup"] = friendsHostsExited ? "all-hosts-exited" : "host-exit-incomplete";
            report["causalGates"] = {{"personaListenersReadyBeforePeerRelay", personaListenersReadyBeforePeerRelay}};
        }
        writeReport(root, report);
        if (scenario.characterization && scenario.contract->observesFriendsPeerInformation)
            printFriendsPeerInformationCharacterizationResult(report);
        else if (scenario.characterization && observesPublicLobbyNotJoinableBehavior(*scenario.contract))
            printPublicLobbyNotJoinableBehaviorCharacterizationResult(report);
        else if (scenario.characterization && observesPublicLobbyFullJoinFailure(*scenario.contract))
            printPublicLobbyFullJoinFailureCharacterizationResult(report);
        else if (scenario.characterization) printCharacterizationResult(root);
        else printComparisonResult(report, *scenario.contract);
        if (!success) throw std::runtime_error("Trace mismatch");
    }
    catch (...)
    {
        stopChild(server);
        if (report.empty())
        {
            report["scenario"] = scenario.contract->name;
            report["status"] = "process-failure";
        }
        if (scenario.contract->observesPublicLobby)
            report["exitCleanup"] = cleanupAcknowledged ? "acknowledged" : "not-acknowledged";
        if (scenario.contract->observesChatRoomMessageDelivery)
        {
            report["exitCleanup"] = chatHostsExited ? "all-hosts-exited" : "host-exit-incomplete";
            report["causalGates"] = {{"receiverArmedBeforeSenderRelease", receiverArmedBeforeSenderRelease}};
        }
        if (scenario.contract->observesFriendsPeerInformation)
        {
            report["exitCleanup"] = friendsHostsExited ? "all-hosts-exited" : "host-exit-incomplete";
            report["causalGates"] = {{"personaListenersReadyBeforePeerRelay", personaListenersReadyBeforePeerRelay}};
        }
        if ((scenario.contract->observesChatRoomMessageDelivery || scenario.contract->observesFriendsPeerInformation || requiresSensitiveArtifactRedaction(*scenario.contract))
            && !redactSensitiveFailureArtifacts(root))
        {
            std::error_code cleanupError;
            fs::remove_all(root, cleanupError);
            std::cerr << "BEHAVIOUR_TEST FAIL reason=SensitiveArtifactHandlingFailure" << std::endl;
            return 1;
        }
        report["serverExitStatus"] = server.started && server.exited ? json(server.exitCode) : json("unavailable");
        try { writeReport(root, report); }
        catch (...) {}
        std::cerr << "BEHAVIOUR_TEST FAIL reason=ComparisonOrProcessFailure runDirectory=" << root.string() << std::endl;
        return 1;
    }
    stopChild(server);
    if (scenario.characterization)
    {
        if (requiresSensitiveArtifactRedaction(*scenario.contract))
        {
            if (!redactSensitiveFailureArtifacts(root))
            {
                std::error_code cleanupError;
                fs::remove_all(root, cleanupError);
                std::cerr << "BEHAVIOUR_TEST FAIL reason=SensitiveArtifactHandlingFailure" << std::endl;
                return 1;
            }
            std::cout << "BEHAVIOUR_TEST CHARACTERIZATION COMPLETE scenario=" << scenario.contract->name << " artifacts=sanitized" << std::endl;
            return 0;
        }
        if (scenario.contract->observesFriendsPeerInformation)
        {
            std::error_code cleanupError;
            fs::remove_all(root, cleanupError);
            if (cleanupError)
            {
                std::cerr << "BEHAVIOUR_TEST FAIL reason=CleanupFailure" << std::endl;
                return 1;
            }
            std::cout << "BEHAVIOUR_TEST CHARACTERIZATION COMPLETE scenario=" << scenario.contract->name << " artifacts=removed" << std::endl;
            return 0;
        }
        std::cout << "BEHAVIOUR_TEST CHARACTERIZATION COMPLETE scenario=" << scenario.contract->name << " artifacts=retained" << std::endl;
        return 0;
    }
    std::error_code cleanupError;
    fs::remove_all(root, cleanupError);
    if (cleanupError)
    {
        std::cerr << "BEHAVIOUR_TEST FAIL reason=CleanupFailure runDirectory=" << root.string() << std::endl;
        return 1;
    }
    std::cout << "BEHAVIOUR_TEST PASS scenario=" << scenario.contract->name << std::endl;
    return 0;
}
}

int main(int argc, char* argv[])
{
    using namespace universelan::behaviour::runner;
    Arguments arguments;
    if (!readArguments(argc, argv, arguments))
    {
        std::cerr << "BEHAVIOUR_TEST FAIL reason=InvalidArguments" << std::endl;
        return 2;
    }
    try
    {
        Scenario scenario;
        if (arguments.characterizeGogServicesState) scenario = characterizationScenario();
        else if (arguments.characterizeOfficialGogPublicLobbyOwnerCloseLifecycle) scenario = publicLobbyOwnerCloseLifecycleCharacterizationScenario();
        else if (arguments.characterizeOfficialGogPublicLobbyOwnerOwnershipTransition) scenario = publicLobbyOwnerOwnershipTransitionCharacterizationScenario();
        else if (arguments.characterizeOfficialGogPublicLobbyNotJoinableBehavior) scenario = publicLobbyNotJoinableBehaviorCharacterizationScenario();
        else if (arguments.characterizeOfficialGogPublicLobbyFullJoinFailure) scenario = publicLobbyFullJoinFailureCharacterizationScenario();
        else if (arguments.characterizePublicLobbyDataPropagation) scenario = publicLobbyDataPropagationCharacterizationScenario();
        else if (arguments.characterizeMultipleLobbyMembershipAndMessageIsolation) scenario = multipleLobbyMembershipAndMessageIsolationCharacterizationScenario();
        else if (arguments.characterizeChatRoomMessageDelivery || arguments.characterizeOfficialGogChatRoomMessageDelivery) scenario = chatRoomMessageDeliveryCharacterizationScenario();
        else if (arguments.characterizeOfficialGogFriendsPeerInformationRetrieval) scenario = friendsPeerInformationRetrievalCharacterizationScenario();
        else if (arguments.characterizeOfficialGogReliableP2PListenerPeek) scenario = reliableP2PListenerPeekCharacterizationScenario();
        else scenario = parseScenario(arguments.manifest);
        return run(arguments, scenario);
    }
    catch (...)
    {
        std::cerr << "BEHAVIOUR_TEST FAIL reason=ManifestOrPreflightFailure" << std::endl;
        return 1;
    }
}
