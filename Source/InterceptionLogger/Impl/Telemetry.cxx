#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY

#include "Telemetry.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	TelemetryImpl::TelemetryImpl(FuncT::F intf) : intf{ intf }
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

	TelemetryImpl::~TelemetryImpl()
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

	void TelemetryImpl::AddStringParam(const char* name, const char* value) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

	void TelemetryImpl::AddIntParam(const char* name, int32_t value) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

	void TelemetryImpl::AddFloatParam(const char* name, double value) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

	void TelemetryImpl::AddBoolParam(const char* name, bool value) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

	void TelemetryImpl::AddObjectParam(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

	void TelemetryImpl::AddArrayParam(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

	void TelemetryImpl::CloseParam() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

	void TelemetryImpl::ClearParams() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY_SAMPLING_CLASS
	void TelemetryImpl::SetSamplingClass(const char* name) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}
#endif

	uint32_t TelemetryImpl::SendTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

#if GALAXY_BUILD_FEATURE_ITELEMETRY_1_139_6_UPDATE
	uint32_t TelemetryImpl::SendAnonymousTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}
#endif

#if GALAXY_BUILD_FEATURE_ITELEMETRY_1_139_7_UPDATE
	const char* TelemetryImpl::GetVisitID() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

	void TelemetryImpl::GetVisitIDCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}

	void TelemetryImpl::ResetVisitID() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ITELEMETRY };

	}
#endif

}

#endif
