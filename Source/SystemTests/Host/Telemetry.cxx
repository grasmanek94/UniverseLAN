#include "Host.hxx"

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY

#include <string>

namespace universelan::systemtest::host
{
namespace
{
constexpr const char eventType[] = "universelan-systemtest-telemetry-local-event-v1";

struct TelemetryEventSendListener final : galaxy::api::ITelemetryEventSendListener
{
    unsigned int successes = 0;
    unsigned int failures = 0;
    std::string returnedEventType;
    std::uint32_t returnedEventIndex = 0;

    void OnTelemetryEventSendSuccess(const char* value, const std::uint32_t index) override
    {
        ++successes;
        returnedEventType = value == nullptr ? "" : value;
        returnedEventIndex = index;
    }

    void OnTelemetryEventSendFailure(const char*, const std::uint32_t, FailureReason) override { ++failures; }
};
}

bool telemetryLocalEventResult(Api& api, const Arguments& arguments)
{
    galaxy::api::ITelemetry* telemetry = api.telemetry();
    if (telemetry == nullptr) return false;

    TelemetryEventSendListener listener;
    const std::uint32_t eventIndex = telemetry->SendTelemetryEvent(eventType, &listener);
    const bool completed = pumpUntil(api, arguments.timeoutSeconds, [&listener]
    {
        return listener.successes != 0 || listener.failures != 0;
    });
    return completed && listener.successes == 1 && listener.failures == 0
        && listener.returnedEventType == eventType && eventIndex != 0 && listener.returnedEventIndex == eventIndex;
}
}

#endif
