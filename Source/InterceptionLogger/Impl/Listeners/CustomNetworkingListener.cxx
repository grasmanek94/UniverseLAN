#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING

#include "CustomNetworkingListener.hxx"
#include "ProxifySingleShotListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::ICUSTOMNETWORKING;
	}

	void ConnectionOpenListener::OnConnectionOpenSuccess(const char* connectionString, ConnectionID connectionID)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
			trace.write_all(std::format("connectionID: {}", connectionID));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnConnectionOpenSuccess(connectionString, connectionID));
	}

	void ConnectionOpenListener::OnConnectionOpenFailure(const char* connectionString, FailureReason failureReason) 
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
			trace.write_all(std::format("failureReason: {}", magic_enum::enum_name(failureReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnConnectionOpenFailure(connectionString, failureReason));
	}

	void ConnectionCloseListener::OnConnectionClosed(ConnectionID connectionID, CloseReason closeReason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
			trace.write_all(std::format("closeReason: {}", magic_enum::enum_name(closeReason)));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnConnectionClosed(connectionID, closeReason));
	}

	void ConnectionDataListener::OnConnectionDataReceived(ConnectionID connectionID, uint32_t dataSize) 
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
			trace.write_all(std::format("dataSize: {}", dataSize));
		}

		IMPLEMENT_PROXY_CALL_ORIGINAL_LISTENER_FUNC(OnConnectionDataReceived(connectionID, dataSize));
	}
}

#endif
