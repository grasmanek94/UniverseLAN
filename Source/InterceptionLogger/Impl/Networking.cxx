#include "Networking.hxx"

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

	NetworkingImpl::NetworkingImpl(FuncT::F intf, IListenerRegistrar* notifications) : intf{ intf }, notifications{ notifications } {}
	NetworkingImpl::~NetworkingImpl() {}

	bool NetworkingImpl::SendP2PPacket(GalaxyID galaxyID, const void* data, uint32_t dataSize, P2PSendType sendType, uint8_t channel) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("galaxyID: {}", galaxyID));
			trace.write_all(std::format("data: {}", data));
			trace.write_all(std::format("dataSize: {}", dataSize));
			trace.write_all(std::format("sendType: {}", magic_enum::enum_name(sendType)));
			trace.write_all(std::format("channel: {}", channel));
		}

		auto result = intf()->SendP2PPacket(galaxyID, data, dataSize, sendType, channel);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	bool NetworkingImpl::PeekP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("dest: {}", dest));
			trace.write_all(std::format("destSize: {}", destSize));
			trace.write_all(std::format("outMsgSize(addr): {}", (void*)outMsgSize));
			trace.write_all(std::format("channel: {}", channel));
		}

		auto result = intf()->PeekP2PPacket(dest, destSize, outMsgSize, outGalaxyID, channel);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
			if (outMsgSize) {
				trace.write_all(std::format("outMsgSize: {}", *outMsgSize));
			}
			trace.write_all(std::format("outGalaxyID: {}", outGalaxyID));
		}

		return result;
	}

	bool NetworkingImpl::ReadP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("dest: {}", dest));
			trace.write_all(std::format("destSize: {}", destSize));
			trace.write_all(std::format("outMsgSize(addr): {}", (void*)outMsgSize));
			trace.write_all(std::format("channel: {}", channel));
		}

		auto result = intf()->ReadP2PPacket(dest, destSize, outMsgSize, outGalaxyID, channel);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
			if (outMsgSize) {
				trace.write_all(std::format("outMsgSize: {}", *outMsgSize));
			}
			trace.write_all(std::format("outGalaxyID: {}", outGalaxyID));
		}

		return result;
	}

	bool NetworkingImpl::IsP2PPacketAvailable(uint32_t* outMsgSize, uint8_t channel) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("outMsgSize(addr): {}", (void*)outMsgSize));
			trace.write_all(std::format("channel: {}", channel));
		}

		auto result = intf()->IsP2PPacketAvailable(outMsgSize, channel);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
			if (outMsgSize) {
				trace.write_all(std::format("outMsgSize: {}", *outMsgSize));
			}
		}

		return result;
	}

	void NetworkingImpl::PopP2PPacket(uint8_t channel) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("channel: {}", channel));
		}

		intf()->PopP2PPacket(channel);
	}

	int NetworkingImpl::GetPingWith(GalaxyID galaxyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("galaxyID: {}", galaxyID));
		}

		auto result = intf()->GetPingWith(galaxyID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_HAS_NAT_FUNCTIONALITY
	void NetworkingImpl::RequestNatTypeDetection() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		intf()->RequestNatTypeDetection();
	}

	NatType NetworkingImpl::GetNatType() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = intf()->GetNatType();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_TYPE
	ConnectionType NetworkingImpl::GetConnectionType(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = intf()->GetConnectionType(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;
	}
#endif
}
