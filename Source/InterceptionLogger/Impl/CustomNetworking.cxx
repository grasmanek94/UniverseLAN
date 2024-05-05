#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING

#include "CustomNetworking.hxx"

#include "Listeners/CustomNetworkingListener.hxx"

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

	CustomNetworkingImpl::CustomNetworkingImpl(FuncT::F intf, IListenerRegistrar* notifications) :
		intf{ intf },
		notifications{ notifications },
		listeners{ notifications } {
		listeners.AddListener<ConnectionOpenListener>();
		listeners.AddListener<ConnectionCloseListener>();
		listeners.AddListener<ConnectionDataListener>();
	}

	CustomNetworkingImpl::~CustomNetworkingImpl() { 
		listeners.UnregisterAllListeners();
	}

	void CustomNetworkingImpl::OpenConnection(const char* connectionString
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
		, IConnectionOpenListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->OpenConnection(connectionString
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
			, listener
#endif
		);
	}

	void CustomNetworkingImpl::CloseConnection(ConnectionID connectionID
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
		, IConnectionCloseListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->CloseConnection(connectionID
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
			, listener
#endif
		);
	}

	void CustomNetworkingImpl::SendData(ConnectionID connectionID, const void* data, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
			trace.write_all(std::format("data: {}", (void*)data));
			trace.write_all(std::format("dataSize: {}", dataSize));
		}

		intf()->SendData(connectionID, data, dataSize);
	}

	uint32_t CustomNetworkingImpl::GetAvailableDataSize(ConnectionID connectionID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
		}

		auto result = intf()->GetAvailableDataSize(connectionID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void CustomNetworkingImpl::PeekData(ConnectionID connectionID, void* dest, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
			trace.write_all(std::format("dest: {}", dest));
			trace.write_all(std::format("dataSize: {}", dataSize));
		}

		intf()->PeekData(connectionID, dest, dataSize);
	}

	void CustomNetworkingImpl::ReadData(ConnectionID connectionID, void* dest, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
			trace.write_all(std::format("dest: {}", dest));
			trace.write_all(std::format("dataSize: {}", dataSize));
		}

		intf()->ReadData(connectionID, dest, dataSize);
	}

	void CustomNetworkingImpl::PopData(ConnectionID connectionID, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
			trace.write_all(std::format("dataSize: {}", dataSize));
		}

		intf()->PopData(connectionID, dataSize);
	}
}

#endif
