#include "Host.hxx"

#include <bit>
#include <cmath>
#include <string>

namespace universelan::systemtest::host
{
#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
namespace
{
struct StatsRetrieveListener final : galaxy::api::IUserStatsAndAchievementsRetrieveListener
{
    explicit StatsRetrieveListener(const galaxy::api::GalaxyID& expectedUser) : expectedUser(expectedUser) {}
    galaxy::api::GalaxyID expectedUser;
    bool completed = false;
    bool succeeded = false;
    void OnUserStatsAndAchievementsRetrieveSuccess(galaxy::api::GalaxyID userId) override
    {
        completed = true;
        succeeded = userId == expectedUser;
    }
    void OnUserStatsAndAchievementsRetrieveFailure(galaxy::api::GalaxyID, FailureReason) override { completed = true; }
};

struct StatsStoreListener final : galaxy::api::IStatsAndAchievementsStoreListener
{
    bool completed = false;
    bool succeeded = false;
    void OnUserStatsAndAchievementsStoreSuccess() override { completed = true; succeeded = true; }
    void OnUserStatsAndAchievementsStoreFailure(FailureReason) override { completed = true; }
};

#if GALAXY_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE && GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
constexpr const char statName[] = "universelan-system-stats-achievement-user-data-stat-v1";
constexpr int32_t statValue = 41527;
constexpr const char achievementName[] = "universelan-system-stats-achievement-user-data-achievement-v1";
constexpr const char userDataKey[] = "universelan-system-stats-achievement-user-data-key-v1";
constexpr const char userDataValue[] = "universelan-system-stats-achievement-user-data-value-v1";
constexpr const char barrierKey[] = "universelan-system-stats-achievement-user-data-barrier-v1";
constexpr const char barrierValue[] = "stored";

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

struct RichPresenceBarrierListener final : galaxy::api::GlobalRichPresenceListener
{
    RichPresenceBarrierListener(galaxy::api::IFriends* friends, const galaxy::api::GalaxyID& expectedWriter)
        : friends(friends), expectedWriter(expectedWriter) {}
    galaxy::api::IFriends* friends;
    galaxy::api::GalaxyID expectedWriter;
    bool received = false;
    bool failed = false;
    void OnRichPresenceUpdated(galaxy::api::GalaxyID userId) override
    {
        if (userId != expectedWriter || received) { failed = true; return; }
        const char* value = friends->GetRichPresence(barrierKey, userId);
        if (value == nullptr || std::string(value) != barrierValue) { failed = true; return; }
        received = true;
    }
};

#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
struct UserDataRetrieveListener final : galaxy::api::ISpecificUserDataListener
{
    explicit UserDataRetrieveListener(const galaxy::api::GalaxyID& expectedUser) : expectedUser(expectedUser) {}
    galaxy::api::GalaxyID expectedUser;
    bool completed = false;
    bool succeeded = false;
    void OnSpecificUserDataUpdated(galaxy::api::GalaxyID userId) override
    {
        completed = true;
        succeeded = userId == expectedUser;
    }
};
#endif
#endif
}

#if GALAXY_BUILD_FEATURE_ISTATS_UPDATE_1_125
namespace
{
constexpr const char durableStatIntName[] = "universelan-system-stats-achievement-durable-persistence-int-v1";
constexpr int32_t durableStatIntValue = 52429;
constexpr const char durableStatFloatName[] = "universelan-system-stats-achievement-durable-persistence-float-v1";
constexpr float durableStatFloatValue = 123.75F;
constexpr const char durableAchievementName[] = "universelan-system-stats-achievement-durable-persistence-achievement-v1";
}

bool statsAchievementDurablePersistenceWriter(Api& api, const Arguments& arguments)
{
    galaxy::api::IStats* stats = api.stats();
    if (stats == nullptr) return false;

    const galaxy::api::GalaxyID userId = api.user->GetGalaxyID();
    StatsRetrieveListener retrieveListener(userId);
    stats->RequestUserStatsAndAchievements(userId, &retrieveListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&retrieveListener] { return retrieveListener.completed; }) || !retrieveListener.succeeded) return false;

    bool unlocked = true;
    uint32_t unlockTime = 1;
    stats->GetAchievement(durableAchievementName, unlocked, unlockTime, userId);
    if (stats->GetStatInt(durableStatIntName, userId) != 0 || stats->GetStatFloat(durableStatFloatName, userId) != 0.0F || unlocked || unlockTime != 0) return false;

    stats->SetStatInt(durableStatIntName, durableStatIntValue);
    stats->SetStatFloat(durableStatFloatName, durableStatFloatValue);
    stats->SetAchievement(durableAchievementName);
    StatsStoreListener storeListener;
    stats->StoreStatsAndAchievements(&storeListener);
    return pumpUntil(api, arguments.timeoutSeconds, [&storeListener] { return storeListener.completed; }) && storeListener.succeeded;
}

bool statsAchievementDurablePersistenceReader(Api& api, const Arguments& arguments)
{
    galaxy::api::IStats* stats = api.stats();
    if (stats == nullptr) return false;

    const galaxy::api::GalaxyID userId = api.user->GetGalaxyID();
    StatsRetrieveListener retrieveListener(userId);
    stats->RequestUserStatsAndAchievements(userId, &retrieveListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&retrieveListener] { return retrieveListener.completed; }) || !retrieveListener.succeeded) return false;

    bool unlocked = false;
    uint32_t unlockTime = 0;
    stats->GetAchievement(durableAchievementName, unlocked, unlockTime, userId);
    const float floatValue = stats->GetStatFloat(durableStatFloatName, userId);
    return stats->GetStatInt(durableStatIntName, userId) == durableStatIntValue && unlocked && unlockTime != 0
        && std::isfinite(floatValue) && floatValue == durableStatFloatValue
        && std::bit_cast<std::uint32_t>(floatValue) == std::bit_cast<std::uint32_t>(durableStatFloatValue);
}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE && GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
bool statsAchievementUserDataPropagationWriter(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::IStats* stats = api.stats();
    galaxy::api::IFriends* friends = api.friends();
    if (stats == nullptr || friends == nullptr) return false;

    const galaxy::api::GalaxyID writerId = api.user->GetGalaxyID();
    StatsRetrieveListener retrieveListener(writerId);
    stats->RequestUserStatsAndAchievements(writerId, &retrieveListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&retrieveListener] { return retrieveListener.completed; }) || !retrieveListener.succeeded) return false;

    stats->SetStatInt(statName, statValue);
    stats->SetAchievement(achievementName);
    api.user->SetUserData(userDataKey, userDataValue);
    StatsStoreListener storeListener;
    stats->StoreStatsAndAchievements(&storeListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&storeListener] { return storeListener.completed; }) || !storeListener.succeeded) return false;

    RichPresenceChangeListener barrierListener;
    friends->SetRichPresence(barrierKey, barrierValue
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
        , &barrierListener
#endif
    );
    if (!pumpUntil(api, arguments.timeoutSeconds, [&barrierListener] { return barrierListener.completed; }) || !barrierListener.succeeded) return false;
    return emit(arguments, "writer-store-and-barrier-sent") && waitForCompletion(arguments);
}

bool statsAchievementUserDataPropagationReader(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1) return false;
    galaxy::api::IStats* stats = api.stats();
    galaxy::api::IFriends* friends = api.friends();
    if (stats == nullptr || friends == nullptr) return false;

    const galaxy::api::GalaxyID writerId = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, arguments.peerUserIds.front());
    RichPresenceBarrierListener barrierListener(friends, writerId);
    if (!emit(arguments, "reader-ready")
        || !pumpUntil(api, arguments.timeoutSeconds, [&barrierListener] { return barrierListener.received || barrierListener.failed; })
        || barrierListener.failed || !barrierListener.received) return false;

#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
    UserDataRetrieveListener userDataListener(writerId);
    api.user->RequestUserData(writerId, &userDataListener);
#else
    api.user->RequestUserData(writerId);
#endif
    StatsRetrieveListener statsListener(writerId);
    // The server replies in request order, so this stats callback also bounds the legacy user-data request.
    stats->RequestUserStatsAndAchievements(writerId, &statsListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&] {
        return statsListener.completed
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
            && userDataListener.completed
#endif
            ;
        }) || !statsListener.succeeded
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
        || !userDataListener.succeeded
#endif
    ) return false;

    bool unlocked = false;
    uint32_t unlockTime = 0;
    stats->GetAchievement(achievementName, unlocked, unlockTime, writerId);
    const char* value = api.user->GetUserData(userDataKey, writerId);
    return stats->GetStatInt(statName, writerId) == statValue && unlocked && unlockTime != 0
        && value != nullptr && std::string(value) == userDataValue
        && emit(arguments, "reader-values-validated");
}
#endif
#endif
}
