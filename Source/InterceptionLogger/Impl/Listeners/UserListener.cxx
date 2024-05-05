#include "UserListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::IUSER;
	}

	void AuthListener::OnAuthSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}

	void AuthListener::OnAuthFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

	void AuthListener::OnAuthLost()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}

	void OtherSessionStartListener::OnOtherSessionStarted()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}

	void OperationalStateChangeListener::OnOperationalStateChanged(uint32_t operationalState)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("operationalState: {}", operationalState));
		}
	}

	void UserDataListener::OnUserDataUpdated()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}

	void SpecificUserDataListener::OnSpecificUserDataUpdated(GalaxyID userID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}
	}

	void EncryptedAppTicketListener::OnEncryptedAppTicketRetrieveSuccess()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}

	void EncryptedAppTicketListener::OnEncryptedAppTicketRetrieveFailure(FailureReason failureReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}
	}

	void AccessTokenListener::OnAccessTokenChanged()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}
}
