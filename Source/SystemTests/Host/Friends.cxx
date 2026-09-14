#include "Host.hxx"

#include <string>

namespace universelan::systemtest::host
{
#if GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED && GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS && GALAXY_BUILD_FEATURE_HAS_FRIENDADDLISTENER && GALAXY_BUILD_FEATURE_HAS_IGAMEINVITATIONRECEIVEDLISTENER && GALAXY_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER && GALAXY_BUILD_FEATURE_HAS_ISENDINVITATIONLISTENER && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
namespace
{
constexpr const char onlinePersonaGameInvitationConnectionString[] = "universelan-system-online-persona-game-invitation-v1";
constexpr const char onlinePersonaGameInvitationReceiverName[] = "OnlinePersonaReceiver";

struct OnlinePeerAddedListener final : galaxy::api::GlobalFriendAddListener
{
    explicit OnlinePeerAddedListener(const galaxy::api::GalaxyID& expectedPeer) : expectedPeer(expectedPeer) {}
    galaxy::api::GalaxyID expectedPeer;
    bool received = false;
    bool failed = false;
    void OnFriendAdded(galaxy::api::GalaxyID userId, InvitationDirection) override
    {
        if (userId != expectedPeer || received) { failed = true; return; }
        received = true;
    }
};

struct PersonaDataChangedListener final : galaxy::api::GlobalPersonaDataChangedListener
{
    explicit PersonaDataChangedListener(const galaxy::api::GalaxyID& expectedPeer) : expectedPeer(expectedPeer) {}
    galaxy::api::GalaxyID expectedPeer;
    bool received = false;
    bool failed = false;
    void OnPersonaDataChanged(galaxy::api::GalaxyID userId, uint32_t change) override
    {
        if (userId != expectedPeer) return;
        if (change == (galaxy::api::IPersonaDataChangedListener::PERSONA_CHANGE_NAME
            | galaxy::api::IPersonaDataChangedListener::PERSONA_CHANGE_AVATAR))
        {
            received = true;
            return;
        }
        if (change != galaxy::api::IPersonaDataChangedListener::PERSONA_CHANGE_NONE) failed = true;
    }
};

struct UserInformationRetrieveListener final : galaxy::api::IUserInformationRetrieveListener
{
    explicit UserInformationRetrieveListener(const galaxy::api::GalaxyID& expectedPeer) : expectedPeer(expectedPeer) {}
    galaxy::api::GalaxyID expectedPeer;
    bool completed = false;
    bool succeeded = false;
    void OnUserInformationRetrieveSuccess(galaxy::api::GalaxyID userId) override { completed = true; succeeded = userId == expectedPeer; }
    void OnUserInformationRetrieveFailure(galaxy::api::GalaxyID, FailureReason) override { completed = true; }
};

struct GameInvitationReceivedListener final : galaxy::api::GlobalGameInvitationReceivedListener
{
    explicit GameInvitationReceivedListener(const galaxy::api::GalaxyID& expectedSender) : expectedSender(expectedSender) {}
    galaxy::api::GalaxyID expectedSender;
    bool received = false;
    bool failed = false;
    void OnGameInvitationReceived(galaxy::api::GalaxyID userId, const char* connectionString) override
    {
        if (userId != expectedSender || connectionString == nullptr || received || std::string(connectionString) != onlinePersonaGameInvitationConnectionString) { failed = true; return; }
        received = true;
    }
};

struct GameJoinRequestedListener final : galaxy::api::GlobalGameJoinRequestedListener
{
    explicit GameJoinRequestedListener(const galaxy::api::GalaxyID& expectedSender) : expectedSender(expectedSender) {}
    galaxy::api::GalaxyID expectedSender;
    bool received = false;
    bool failed = false;
    void OnGameJoinRequested(galaxy::api::GalaxyID userId, const char* connectionString) override
    {
        if (userId != expectedSender || connectionString == nullptr || received || std::string(connectionString) != onlinePersonaGameInvitationConnectionString) { failed = true; return; }
        received = true;
    }
};

struct GameInvitationSendListener final : galaxy::api::ISendInvitationListener
{
    explicit GameInvitationSendListener(const galaxy::api::GalaxyID& expectedReceiver) : expectedReceiver(expectedReceiver) {}
    galaxy::api::GalaxyID expectedReceiver;
    bool completed = false;
    bool succeeded = false;
    void OnInvitationSendSuccess(galaxy::api::GalaxyID userId, const char* connectionString) override
    {
        completed = true;
        succeeded = userId == expectedReceiver && connectionString != nullptr && std::string(connectionString) == onlinePersonaGameInvitationConnectionString;
    }
    void OnInvitationSendFailure(galaxy::api::GalaxyID, const char*, FailureReason) override { completed = true; }
};
}

bool onlinePersonaGameInvitationSender(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::IFriends* friends = api.friends();
    if (friends == nullptr) return false;
    const galaxy::api::GalaxyID receiverId = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, arguments.peerUserIds.front());
    PersonaDataChangedListener personaListener(receiverId);
    UserInformationRetrieveListener informationListener(receiverId);
    friends->RequestUserInformation(receiverId, galaxy::api::AVATAR_TYPE_NONE, &informationListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&] { return informationListener.completed && (personaListener.received || personaListener.failed); })
        || !informationListener.succeeded || personaListener.failed || !personaListener.received
        || std::string(friends->GetFriendPersonaName(receiverId)) != onlinePersonaGameInvitationReceiverName
        || friends->GetFriendPersonaState(receiverId) != galaxy::api::PERSONA_STATE_ONLINE
        || !emit(arguments, "sender-online-peer-validated")) return false;
    GameInvitationSendListener sendListener(receiverId);
    friends->SendInvitation(receiverId, onlinePersonaGameInvitationConnectionString, &sendListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&sendListener] { return sendListener.completed; }) || !sendListener.succeeded) return false;
    return emit(arguments, "sender-invitation-sent") && waitForCompletion(arguments);
}

bool onlinePersonaGameInvitationReceiver(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    const galaxy::api::GalaxyID senderId = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, arguments.peerUserIds.front());
    OnlinePeerAddedListener onlinePeerListener(senderId);
    GameInvitationReceivedListener invitationListener(senderId);
    GameJoinRequestedListener gameJoinListener(senderId);
    if (!emit(arguments, "receiver-ready") || !pumpUntil(api, arguments.timeoutSeconds, [&] { return onlinePeerListener.received || onlinePeerListener.failed; })
        || onlinePeerListener.failed || !onlinePeerListener.received || !emit(arguments, "receiver-observed-sender") || !waitForAction(arguments)) return false;
    return pumpUntil(api, arguments.timeoutSeconds, [&] { return (invitationListener.received && gameJoinListener.received) || invitationListener.failed || gameJoinListener.failed; })
        && !invitationListener.failed && !gameJoinListener.failed && invitationListener.received && gameJoinListener.received
        && emit(arguments, "receiver-invitation-validated") && emit(arguments, "receiver-game-join-requested");
}
#endif
}

namespace universelan::systemtest::host
{
#if GALAXY_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE && GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
namespace
{
constexpr const char richPresenceLivePropagationKey[] = "universelan-system-rich-presence-key-v1";
constexpr const char richPresenceLivePropagationValue[] = "universelan-system-rich-presence-value-v1";

struct RichPresenceUpdatedListener final : galaxy::api::GlobalRichPresenceListener
{
    RichPresenceUpdatedListener(galaxy::api::IFriends* friends, const galaxy::api::GalaxyID& expectedWriter)
        : friends(friends), expectedWriter(expectedWriter) {}
    galaxy::api::IFriends* friends;
    galaxy::api::GalaxyID expectedWriter;
    bool received = false;
    bool failed = false;
    void OnRichPresenceUpdated(galaxy::api::GalaxyID userId) override
    {
        if (userId != expectedWriter || received) { failed = true; return; }
        const char* value = friends->GetRichPresence(richPresenceLivePropagationKey, userId);
        if (value == nullptr || std::string(value) != richPresenceLivePropagationValue
            || friends->GetRichPresenceCount(userId) == 0)
        {
            failed = true;
            return;
        }
        received = true;
    }
};

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
struct RichPresenceChangeListener final : galaxy::api::IRichPresenceChangeListener
#else
struct RichPresenceChangeListener final : galaxy::api::GlobalRichPresenceChangeListener
#endif
{
    bool completed = false;
    bool succeeded = false;
    void OnRichPresenceChangeSuccess() override { completed = true; succeeded = true; }
    void OnRichPresenceChangeFailure(FailureReason) override { completed = true; }
};
}

bool richPresenceLivePropagationWriter(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::IFriends* friends = api.friends();
    if (friends == nullptr) return false;
    RichPresenceChangeListener listener;
    friends->SetRichPresence(richPresenceLivePropagationKey, richPresenceLivePropagationValue
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
        , &listener
#endif
    );
    if (!pumpUntil(api, arguments.timeoutSeconds, [&listener] { return listener.completed; }) || !listener.succeeded) return false;
    return emit(arguments, "writer-set-succeeded") && waitForCompletion(arguments);
}

bool richPresenceLivePropagationReceiver(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::IFriends* friends = api.friends();
    if (friends == nullptr) return false;
    const galaxy::api::GalaxyID writerId = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, arguments.peerUserIds.front());
    RichPresenceUpdatedListener listener(friends, writerId);
    if (!emit(arguments, "receiver-ready")) return false;
    return pumpUntil(api, arguments.timeoutSeconds, [&listener] { return listener.received || listener.failed; })
        && listener.received && !listener.failed && emit(arguments, "receiver-presence-validated");
}
#endif
}
