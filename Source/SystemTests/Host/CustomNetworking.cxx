#include "Host.hxx"

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
#include <ixwebsocket/IXNetSystem.h>
#endif

namespace universelan::systemtest::host
{
#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
namespace
{
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
using ConnectionOpenListenerBase = galaxy::api::IConnectionOpenListener;
using ConnectionCloseListenerBase = galaxy::api::IConnectionCloseListener;
#else
using ConnectionOpenListenerBase = galaxy::api::GlobalConnectionOpenListener;
using ConnectionCloseListenerBase = galaxy::api::GlobalConnectionCloseListener;
#endif

struct ConnectionOpenListener final : ConnectionOpenListenerBase
{
    bool completed = false;
    bool succeeded = false;
    unsigned int successes = 0;
    unsigned int failures = 0;
    galaxy::api::ConnectionID connectionId = 0;
    std::string connectionString;

    void OnConnectionOpenSuccess(const char* value, galaxy::api::ConnectionID id) override
    {
        completed = true;
        succeeded = id != 0;
        ++successes;
        connectionId = id;
        connectionString = value == nullptr ? "" : value;
    }
    void OnConnectionOpenFailure(const char*, FailureReason) override
    {
        completed = true;
        ++failures;
    }
};

struct ConnectionCloseListener final : ConnectionCloseListenerBase
{
    unsigned int closes = 0;
    galaxy::api::ConnectionID connectionId = 0;
    CloseReason reason = CLOSE_REASON_UNDEFINED;

    void OnConnectionClosed(const galaxy::api::ConnectionID id, const CloseReason value) override
    {
        ++closes;
        connectionId = id;
        reason = value;
    }
};
}

#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
bool customNetworkingEcho(Api& api, const Arguments& arguments)
{
    galaxy::api::ICustomNetworking* networking = api.customNetworking();
    if (networking == nullptr || arguments.webSocketUrl.empty()) return false;
    if (!ix::initNetSystem()) return false;
    ConnectionOpenListener openListener;
    networking->OpenConnection(arguments.webSocketUrl.c_str(), &openListener);
    if (!pumpUntil(api, arguments.timeoutSeconds, [&openListener] { return openListener.completed; }) || !openListener.succeeded)
    {
        ix::uninitNetSystem();
        return false;
    }
    const std::vector<std::uint8_t> payload{'e', 'c', 'h', 'o', 0, 'b', 'i', 'n', 'a', 'r', 'y'};
    networking->SendData(openListener.connectionId, payload.data(), static_cast<uint32_t>(payload.size()));
    const bool echoed = pumpUntil(api, arguments.timeoutSeconds, [&]
    {
        const uint32_t available = networking->GetAvailableDataSize(openListener.connectionId);
        if (available == 0) return false;
        if (available != payload.size()) return false;
        std::vector<std::uint8_t> echoed(available);
        networking->ReadData(openListener.connectionId, echoed.data(), available);
        return echoed == payload;
    });
    ix::uninitNetSystem();
    return echoed;
}
#endif

bool customNetworkingClose(Api& api, const Arguments& arguments)
{
    galaxy::api::ICustomNetworking* networking = api.customNetworking();
    if (networking == nullptr || arguments.webSocketUrl.empty() || !ix::initNetSystem()) return false;

    ConnectionOpenListener openListener;
    ConnectionCloseListener closeListener;
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
    networking->OpenConnection(arguments.webSocketUrl.c_str(), &openListener);
#else
    networking->OpenConnection(arguments.webSocketUrl.c_str());
#endif
    const bool opened = pumpUntil(api, arguments.timeoutSeconds, [&openListener]
    {
        return openListener.completed;
    });
    if (!opened || !openListener.succeeded || openListener.successes != 1 || openListener.failures != 0
        || openListener.connectionId == 0 || openListener.connectionString != arguments.webSocketUrl)
    {
        ix::uninitNetSystem();
        return false;
    }

#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
    networking->CloseConnection(openListener.connectionId, &closeListener);
#else
    networking->CloseConnection(openListener.connectionId);
#endif
    const bool closed = pumpUntil(api, arguments.timeoutSeconds, [&closeListener]
    {
        return closeListener.closes != 0;
    });
    pumpUntil(api, 1, [] { return false; });
    const bool succeeded = closed && openListener.successes == 1 && openListener.failures == 0 && closeListener.closes == 1
        && closeListener.connectionId == openListener.connectionId
        && closeListener.reason == galaxy::api::IConnectionCloseListener::CLOSE_REASON_UNDEFINED;
    ix::uninitNetSystem();
    return succeeded;
}
#endif
}
