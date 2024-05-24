#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY

#include "TestCaseClientDetails.hxx"

class TelemetryEventSendListenerImplGlobal : public galaxy::api::GlobalTelemetryEventSendListener
{
public:
	using on_telemetry_event_send_success_func_t = std::function<void(const char*, uint32_t)>;
	using on_telemetry_event_send_failure_func_t = std::function<void(const char*, uint32_t, FailureReason)>;

private:
	on_telemetry_event_send_success_func_t on_telemetry_event_send_success;
	on_telemetry_event_send_failure_func_t on_telemetry_event_send_failure;

public:
	TelemetryEventSendListenerImplGlobal(
		on_telemetry_event_send_success_func_t on_telemetry_event_send_success = nullptr,
		on_telemetry_event_send_failure_func_t on_telemetry_event_send_failure = nullptr) :
		on_telemetry_event_send_success{ on_telemetry_event_send_success },
		on_telemetry_event_send_failure{ on_telemetry_event_send_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~TelemetryEventSendListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnTelemetryEventSendSuccess(const char* eventType, uint32_t sentEventIndex) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"eventType: {} sentEventIndex: {}",
			eventType, sentEventIndex
		).c_str());


		if (on_telemetry_event_send_success != nullptr) {
			on_telemetry_event_send_success(eventType, sentEventIndex);
		}
	}

	virtual void OnTelemetryEventSendFailure(const char* eventType, uint32_t sentEventIndex, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"eventType: {} sentEventIndex: {} failureReason: {}",
			eventType, sentEventIndex, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_telemetry_event_send_failure != nullptr) {
			on_telemetry_event_send_failure(eventType, sentEventIndex, failureReason);
		}
	}
};

class TelemetryEventSendListenerImplLocal : public galaxy::api::ITelemetryEventSendListener
{
public:
	using on_telemetry_event_send_success_func_t = std::function<void(const char*, uint32_t)>;
	using on_telemetry_event_send_failure_func_t = std::function<void(const char*, uint32_t, FailureReason)>;

private:
	on_telemetry_event_send_success_func_t on_telemetry_event_send_success;
	on_telemetry_event_send_failure_func_t on_telemetry_event_send_failure;

public:
	TelemetryEventSendListenerImplLocal(
		on_telemetry_event_send_success_func_t on_telemetry_event_send_success = nullptr,
		on_telemetry_event_send_failure_func_t on_telemetry_event_send_failure = nullptr) :
		on_telemetry_event_send_success{ on_telemetry_event_send_success },
		on_telemetry_event_send_failure{ on_telemetry_event_send_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~TelemetryEventSendListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnTelemetryEventSendSuccess(const char* eventType, uint32_t sentEventIndex) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"eventType: {} sentEventIndex: {}",
			eventType, sentEventIndex
		).c_str());


		if (on_telemetry_event_send_success != nullptr) {
			on_telemetry_event_send_success(eventType, sentEventIndex);
		}
	}

	virtual void OnTelemetryEventSendFailure(const char* eventType, uint32_t sentEventIndex, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"eventType: {} sentEventIndex: {} failureReason: {}",
			eventType, sentEventIndex, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_telemetry_event_send_failure != nullptr) {
			on_telemetry_event_send_failure(eventType, sentEventIndex, failureReason);
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API
#if GALAXY_BUILD_FEATURE_HAS_GAMESERVERTELEMETRY
class GameServerTelemetryEventSendListenerImplGlobal : public galaxy::api::GameServerGlobalTelemetryEventSendListener
{
public:
	using on_telemetry_event_send_success_func_t = std::function<void(const char*, uint32_t)>;
	using on_telemetry_event_send_failure_func_t = std::function<void(const char*, uint32_t, FailureReason)>;

private:
	on_telemetry_event_send_success_func_t on_telemetry_event_send_success;
	on_telemetry_event_send_failure_func_t on_telemetry_event_send_failure;

public:
	GameServerTelemetryEventSendListenerImplGlobal(
		on_telemetry_event_send_success_func_t on_telemetry_event_send_success = nullptr,
		on_telemetry_event_send_failure_func_t on_telemetry_event_send_failure = nullptr) :
		on_telemetry_event_send_success{ on_telemetry_event_send_success },
		on_telemetry_event_send_failure{ on_telemetry_event_send_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerTelemetryEventSendListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnTelemetryEventSendSuccess(const char* eventType, uint32_t sentEventIndex) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"eventType: {} sentEventIndex: {}",
			eventType, sentEventIndex
		).c_str());


		if (on_telemetry_event_send_success != nullptr) {
			on_telemetry_event_send_success(eventType, sentEventIndex);
		}
	}

	virtual void OnTelemetryEventSendFailure(const char* eventType, uint32_t sentEventIndex, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"eventType: {} sentEventIndex: {} failureReason: {}",
			eventType, sentEventIndex, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_telemetry_event_send_failure != nullptr) {
			on_telemetry_event_send_failure(eventType, sentEventIndex, failureReason);
		}
	}
};
#endif
#endif

#endif
