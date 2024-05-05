#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY

#include "Telemetry.hxx"

#include "Listeners/TelemetryListener.hxx"

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

	TelemetryImpl::TelemetryImpl(FuncT::F intf, IListenerRegistrar* notifications) :
		intf{ intf },
		notifications{ notifications },
		listeners{ notifications } {
		listeners.AddListener<TelemetryEventSendListener>();
	}

	TelemetryImpl::~TelemetryImpl() {
		listeners.UnregisterAllListeners();
	}

	void TelemetryImpl::AddStringParam(const char* name, const char* value) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("value: {}", util::safe_fix_null_char_ptr_annotate_ret(value)));
		}

		intf()->AddStringParam(name, value);
	}

	void TelemetryImpl::AddIntParam(const char* name, int32_t value) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("value: {}", value));
		}

		intf()->AddIntParam(name, value);
	}

	void TelemetryImpl::AddFloatParam(const char* name, double value) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("value: {}", value));
		}

		intf()->AddFloatParam(name, value);
	}

	void TelemetryImpl::AddBoolParam(const char* name, bool value) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
			trace.write_all(std::format("value: {}", value));
		}

		intf()->AddBoolParam(name, value);
	}

	void TelemetryImpl::AddObjectParam(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		intf()->AddObjectParam(name);
	}

	void TelemetryImpl::AddArrayParam(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		intf()->AddArrayParam(name);
	}

	void TelemetryImpl::CloseParam() {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		intf()->CloseParam();
	}

	void TelemetryImpl::ClearParams() {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		intf()->ClearParams();
	}

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY_SAMPLING_CLASS
	void TelemetryImpl::SetSamplingClass(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("name: {}", util::safe_fix_null_char_ptr_annotate_ret(name)));
		}

		intf()->SetSamplingClass(name);
	}
#endif

	uint32_t TelemetryImpl::SendTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("eventType: {}", util::safe_fix_null_char_ptr_annotate_ret(eventType)));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		auto result = intf()->SendTelemetryEvent(eventType, listener);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_ITELEMETRY_1_139_6_UPDATE
	uint32_t TelemetryImpl::SendAnonymousTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("eventType: {}", util::safe_fix_null_char_ptr_annotate_ret(eventType)));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		auto result = intf()->SendAnonymousTelemetryEvent(eventType, listener);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif

#if GALAXY_BUILD_FEATURE_ITELEMETRY_1_139_7_UPDATE
	const char* TelemetryImpl::GetVisitID() {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->GetVisitID();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	void TelemetryImpl::GetVisitIDCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		intf()->GetVisitIDCopy(buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}

	void TelemetryImpl::ResetVisitID() {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		intf()->ResetVisitID();
	}
#endif

}

#endif
