#include "Telemetry.hxx"

namespace galaxy
{
	namespace api
	{
		TelemetryImpl::~TelemetryImpl()
		{
		}

		void TelemetryImpl::AddStringParam(const char* name, const char* value) {

		}

		void TelemetryImpl::AddIntParam(const char* name, int32_t value) {

		}

		void TelemetryImpl::AddFloatParam(const char* name, double value) {

		}

		void TelemetryImpl::AddBoolParam(const char* name, bool value) {

		}

		void TelemetryImpl::AddObjectParam(const char* name) {

		}

		void TelemetryImpl::AddArrayParam(const char* name) {

		}

		void TelemetryImpl::CloseParam() {

		}

		void TelemetryImpl::ClearParams() {

		}

		void TelemetryImpl::SetSamplingClass(const char* name) {

		}

		uint32_t TelemetryImpl::SendTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener) {
			return 0;
		}

		uint32_t TelemetryImpl::SendAnonymousTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener) {
			return 0;
		}

		const char* TelemetryImpl::GetVisitID() {
			return "0";
		}

		void TelemetryImpl::GetVisitIDCopy(char* buffer, uint32_t bufferLength) {

		}

		void TelemetryImpl::ResetVisitID() {

		}
	}
}


