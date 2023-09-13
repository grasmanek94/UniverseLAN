#if (GALAXY_VERSION) > 112400

#include "Telemetry.hxx"
#include "UniverseLAN.hxx"

#include <SafeStringCopy.hxx>

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>

namespace universelan::client {
	using namespace galaxy::api;

	TelemetryImpl::TelemetryImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		mtx{}, telemetry_file{}, counter{ 1 }, visit_id{ "1337" }
	{
		tracer::Trace trace{ __FUNCTION__ };

		if (!intf->config->GetTelemetryStore()) {
			return;
		}

		auto t = std::time(nullptr);

#pragma warning( push )
#pragma warning( disable : 4996 )
		auto tm = *std::localtime(&t);
#pragma warning( pop )

		std::ostringstream path;

		path << (std::filesystem::path(intf->config->GetGameDataPath()) / "Telemetry" / "T")
			<< std::put_time(&tm, "%Y-%m-%d_%H-%M-%S")
			<< "-" << std::this_thread::get_id() << ".log";

		telemetry_file = std::ofstream{ path.str() };
		if (!telemetry_file) {
			std::cerr << "Error opening for write: " << path.str() << std::endl;
		}
	}

	TelemetryImpl::~TelemetryImpl()
	{
		tracer::Trace trace{ __FUNCTION__ };

		if (telemetry_file) {
			lock_t lock(mtx);
			telemetry_file.flush();
		}
	}

	void TelemetryImpl::AddStringParam(const char* name, const char* value) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!telemetry_file) {
			return;
		}

		lock_t lock{ mtx };
		telemetry_file << name << " = (str)" << value << "\n";
	}

	void TelemetryImpl::AddIntParam(const char* name, int32_t value) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!telemetry_file) {
			return;
		}

		lock_t lock{ mtx };
		telemetry_file << name << " = (int32_t)" << value << "\n";
	}

	void TelemetryImpl::AddFloatParam(const char* name, double value) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!telemetry_file) {
			return;
		}

		lock_t lock{ mtx };
		telemetry_file << name << " = (double)" << value << "\n";
	}

	void TelemetryImpl::AddBoolParam(const char* name, bool value) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!telemetry_file) {
			return;
		}

		lock_t lock{ mtx };
		telemetry_file << name << " = (bool)" << value << "\n";
	}

	void TelemetryImpl::AddObjectParam(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!telemetry_file) {
			return;
		}

		lock_t lock{ mtx };
		telemetry_file << "(object) " << name << "\n";
	}

	void TelemetryImpl::AddArrayParam(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!telemetry_file) {
			return;
		}

		lock_t lock{ mtx };
		telemetry_file << "(array) " << name << "\n";
	}

	void TelemetryImpl::CloseParam() {
		tracer::Trace trace{ __FUNCTION__ };

		if (!telemetry_file) {
			return;
		}

		lock_t lock{ mtx };
		telemetry_file << "(CloseParam) " << "\n";
	}

	void TelemetryImpl::ClearParams() {
		tracer::Trace trace{ __FUNCTION__ };

		if (!telemetry_file) {
			return;
		}

		lock_t lock{ mtx };
		telemetry_file << "(ClearParams) " << "\n";
	}

	void TelemetryImpl::SetSamplingClass(const char* name) {
		tracer::Trace trace{ __FUNCTION__ };

		if (!telemetry_file) {
			return;
		}

		lock_t lock{ mtx };
		telemetry_file << "(SetSamplingClass) " << name << "\n";
	}

	uint32_t TelemetryImpl::SendTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		uint32_t id = counter.fetch_add(1);
		std::string event_type{ eventType };

		if (!telemetry_file) {
			listeners->NotifyAll(listener, &ITelemetryEventSendListener::OnTelemetryEventSendFailure, event_type.c_str(), id, ITelemetryEventSendListener::FAILURE_REASON_UNDEFINED);
			return id;
		}

		lock_t lock{ mtx };
		telemetry_file << "(SendTelemetryEvent) " << eventType << "\n";

		listeners->NotifyAll(listener, &ITelemetryEventSendListener::OnTelemetryEventSendSuccess, event_type.c_str(), id);

		return id;
	}

	uint32_t TelemetryImpl::SendAnonymousTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		return SendTelemetryEvent(eventType, listener);
	}

	const char* TelemetryImpl::GetVisitID() {
		tracer::Trace trace{ __FUNCTION__ };

		lock_t lock{ mtx };
		return visit_id.c_str();
	}

	void TelemetryImpl::GetVisitIDCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		lock_t lock{ mtx };
		universelan::util::safe_copy_str_n(visit_id, buffer, bufferLength);
	}

	void TelemetryImpl::ResetVisitID() {
		tracer::Trace trace{ __FUNCTION__ };

		lock_t lock{ mtx };
		visit_id = std::to_string((uint32_t)((uint64_t)this) + counter.fetch_add(1));
	}
}

#endif