#pragma once
#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY

#include <ITelemetry.h>

namespace universelan::client {
	using namespace galaxy::api;

	class TelemetryEventSendListener : public ITelemetryEventSendListener
	{
	public:
		virtual void OnTelemetryEventSendSuccess(const char* eventType, uint32_t sentEventIndex);
		virtual void OnTelemetryEventSendFailure(const char* eventType, uint32_t sentEventIndex, FailureReason failureReason);
	};
}

#endif
