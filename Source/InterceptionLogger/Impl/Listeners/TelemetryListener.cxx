#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY

#include "TelemetryListener.hxx"
#include "ProxifySingleShotListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::ITELEMETRY;
	}

	void TelemetryEventSendListener::OnTelemetryEventSendSuccess(const char* eventType, uint32_t sentEventIndex)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("eventType: {}", util::safe_fix_null_char_ptr_annotate_ret(eventType)));
			trace.write_all(std::format("sentEventIndex: {}", sentEventIndex));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnTelemetryEventSendSuccess(eventType, sentEventIndex));
	}

	void TelemetryEventSendListener::OnTelemetryEventSendFailure(const char* eventType, uint32_t sentEventIndex, FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("eventType: {}", util::safe_fix_null_char_ptr_annotate_ret(eventType)));
			trace.write_all(std::format("sentEventIndex: {}", sentEventIndex));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnTelemetryEventSendFailure(eventType, sentEventIndex, failureReason));
	}
}

#endif
