#include "Host.hxx"

#include <string>

namespace universelan::systemtest::host
{
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER && GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
namespace
{
constexpr const char userDataLivePropagationKey[] = "universelan-system-user-data-live-propagation-key-v1";
constexpr const char userDataLivePropagationValue[] = "universelan-system-user-data-live-propagation-value-v1";

#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
using UserDataSetListenerBase = galaxy::api::ISpecificUserDataListener;
#else
using UserDataSetListenerBase = galaxy::api::GlobalSpecificUserDataListener;
#endif

struct UserDataSetListener final : UserDataSetListenerBase
{
    explicit UserDataSetListener(const galaxy::api::GalaxyID& expectedUser) : expectedUser(expectedUser) {}

    galaxy::api::GalaxyID expectedUser;
    bool completed = false;
    bool succeeded = false;

    void OnSpecificUserDataUpdated(galaxy::api::GalaxyID userId) override
    {
        completed = true;
        succeeded = userId == expectedUser;
    }
};

struct UserDataUpdatedListener final : galaxy::api::ISpecificUserDataListener
{
    explicit UserDataUpdatedListener(const galaxy::api::GalaxyID& expectedUser) : expectedUser(expectedUser) {}

    galaxy::api::GalaxyID expectedUser;
    bool received = false;
    bool failed = false;

    void OnSpecificUserDataUpdated(galaxy::api::GalaxyID userId) override
    {
        if (userId != expectedUser) { failed = true; return; }
        received = true;
    }
};
}

bool userDataLivePropagationWriter(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1 || api.user == nullptr) return false;

    UserDataSetListener listener(api.user->GetGalaxyID());
    api.user->SetUserData(userDataLivePropagationKey, userDataLivePropagationValue
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
        , &listener
#endif
    );
    return pumpUntil(api, arguments.timeoutSeconds, [&listener] { return listener.completed; }) && listener.succeeded
        && emit(arguments, "writer-local-update") && waitForCompletion(arguments);
}

bool userDataLivePropagationReceiver(Api& api, const Arguments& arguments)
{
    if (arguments.peerUserIds.size() != 1 || api.user == nullptr) return false;

    const galaxy::api::GalaxyID writerId = galaxy::api::GalaxyID::FromRealID(galaxy::api::GalaxyID::ID_TYPE_USER, arguments.peerUserIds.front());
    UserDataUpdatedListener listener(writerId);
    galaxy::api::IListenerRegistrar* registrar = galaxy::api::ListenerRegistrar();
    if (registrar == nullptr) return false;
    registrar->Register(galaxy::api::ISpecificUserDataListener::GetListenerType(), &listener);
    if (!emit(arguments, "receiver-ready")) { registrar->Unregister(galaxy::api::ISpecificUserDataListener::GetListenerType(), &listener); return false; }
    const bool callbackReceived = pumpUntil(api, arguments.timeoutSeconds, [&listener] { return listener.received || listener.failed; });
    const char* value = api.user->GetUserData(userDataLivePropagationKey, writerId);
    registrar->Unregister(galaxy::api::ISpecificUserDataListener::GetListenerType(), &listener);
    return callbackReceived && !listener.failed && listener.received
        && value != nullptr && std::string(value) == userDataLivePropagationValue
        && emit(arguments, "receiver-cache-validated");
}
#endif
}
