#include "Telemetry.hxx"

namespace galaxy
{
	namespace api
	{
		Telemetry::~Telemetry()
		{
		}

		void Telemetry::AddStringParam(const char* name, const char* value) {

		}

		void Telemetry::AddIntParam(const char* name, int32_t value) {

		}

		void Telemetry::AddFloatParam(const char* name, double value) {

		}

		void Telemetry::AddBoolParam(const char* name, bool value) {

		}

		void Telemetry::AddObjectParam(const char* name) {

		}

		void Telemetry::AddArrayParam(const char* name) {

		}

		void Telemetry::CloseParam() {

		}

		void Telemetry::ClearParams() {

		}

		void Telemetry::SetSamplingClass(const char* name) {

		}

		uint32_t Telemetry::SendTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener) {
			return 0;
		}

		uint32_t Telemetry::SendAnonymousTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener) {
			return 0;
		}

		const char* Telemetry::GetVisitID() {
			return "0";
		}

		void Telemetry::GetVisitIDCopy(char* buffer, uint32_t bufferLength) {

		}

		void Telemetry::ResetVisitID() {

		}
	}
}


