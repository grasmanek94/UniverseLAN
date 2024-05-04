#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING

#include "CustomNetworking.hxx"

#include <Tracer.hxx>
#include <GalaxyDLL.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;
	
	CustomNetworkingImpl::CustomNetworkingImpl(InterfaceInstances* intf) : intf{intf}
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };
	}

	CustomNetworkingImpl::~CustomNetworkingImpl()
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };
	}

	void CustomNetworkingImpl::OpenConnection(const char* connectionString
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
		, IConnectionOpenListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_CustomNetworking()->OpenConnection(connectionString
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
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_CustomNetworking()->CloseConnection(connectionID
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
			, listener
#endif
		);
	}

	uint32_t CustomNetworkingImpl::GetAvailableDataSize(ConnectionID connectionID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
		}

		auto result = RealGalaxyDLL_CustomNetworking()->GetAvailableDataSize(connectionID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void CustomNetworkingImpl::PeekData(ConnectionID connectionID, void* dest, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
			trace.write_all(std::format("dest: {}", dest));
			trace.write_all(std::format("dataSize: {}", dataSize));
		}

		RealGalaxyDLL_CustomNetworking()->PeekData(connectionID, dest, dataSize);
	}

	void CustomNetworkingImpl::ReadData(ConnectionID connectionID, void* dest, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
			trace.write_all(std::format("dest: {}", dest));
			trace.write_all(std::format("dataSize: {}", dataSize));
		}

		RealGalaxyDLL_CustomNetworking()->ReadData(connectionID, dest, dataSize);
	}

	void CustomNetworkingImpl::PopData(ConnectionID connectionID, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionID: {}", connectionID));
			trace.write_all(std::format("dataSize: {}", dataSize));
		}

		RealGalaxyDLL_CustomNetworking()->PopData(connectionID, dataSize);
	}
}

#endif
