#include "NetworkingListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::INETWORKING;
	}

	void NetworkingListener::OnP2PPacketAvailable(uint32_t msgSize, uint8_t channel)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("msgSize: {}", msgSize));
			trace.write_all(std::format("channel: {}", (int)channel));
		}
	}

#if GALAXY_BUILD_FEATURE_HAS_NAT_FUNCTIONALITY
	void NatTypeDetectionListener::OnNatTypeDetectionSuccess(NatType natType)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("natType: {}", magic_enum::enum_name(natType)));
		}
	}

	void NatTypeDetectionListener::OnNatTypeDetectionFailure()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };
	}
#endif
}
