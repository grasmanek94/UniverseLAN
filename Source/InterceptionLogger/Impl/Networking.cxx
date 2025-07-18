#include "Networking.hxx"

#include "Listeners/NetworkingListener.hxx"

#include <ConstHash.hxx>
#include <filesystem_container/filesystem_container_utils.hxx>
#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;
	using namespace universelan::util;

	namespace {
		const auto TraceContext = tracer::Trace::INETWORKING;
	}

	NetworkingImpl::NetworkingImpl(FuncT::F intf, IListenerRegistrar* notifications, char networking_type_letter) :
		intf{ intf },
		notifications{ notifications },
		listeners{ notifications },
		networking_type{ '[', networking_type_letter, ']', 0 } {
		tracer::Trace trace{ "::WARNING: NetworkingListener disabled due to introducing bugs with PeekPacket", __FUNCTION__, TraceContext };

		//listeners.AddListener<NetworkingListener>();
#if GALAXY_BUILD_FEATURE_HAS_NAT_FUNCTIONALITY
		listeners.AddListener<NatTypeDetectionListener>();
#endif
	}

	NetworkingImpl::~NetworkingImpl() {
		listeners.UnregisterAllListeners();
	}

	bool NetworkingImpl::SendP2PPacket(GalaxyID galaxyID, const void* data, uint32_t dataSize, P2PSendType sendType, uint8_t channel) {
		tracer::Trace trace{ networking_type, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("galaxyID: {}", galaxyID));
			trace.write_all(std::format("data: {}", data));
			trace.write_all(std::format("dataSize: {}", dataSize));
			trace.write_all(std::format("sendType: {}", magic_enum::enum_name(sendType)));
			trace.write_all(std::format("channel: {}", channel));
			trace.write_all(std::format("data_hash: {:x}", const_hash64_data_loop((const char*)data, dataSize)));

			if (trace.has_flags(tracer::Trace::NETWORK_P2P_CONTENTS)) {
				trace.write_all(std::format("data_contents_hex: {}", bytes_to_hex(data, dataSize)));
				trace.write_all(std::format("data_contents_enc: {}", filesystem_container::filename_encode(std::string((char*)data, (size_t)dataSize))));
			}
		}

		auto result = intf()->SendP2PPacket(galaxyID, data, dataSize, sendType, channel);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	bool NetworkingImpl::PeekP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel) {
		tracer::Trace trace{ networking_type, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("dest: {}", dest));
			trace.write_all(std::format("destSize: {}", destSize));
			trace.write_all(std::format("outMsgSize(addr): {}", (void*)outMsgSize));
			trace.write_all(std::format("channel: {}", channel));
		}

		auto result = intf()->PeekP2PPacket(dest, destSize, outMsgSize, outGalaxyID, channel);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
			if (result) {
				if (outMsgSize) {
					trace.write_all(std::format("outMsgSize: {}", *outMsgSize));
				}

				trace.write_all(std::format("outGalaxyID: {}", outGalaxyID));
				if (outMsgSize) {
					trace.write_all(std::format("data_hash: {:x}", const_hash64_data_loop((const char*)dest, *outMsgSize)));

					if (trace.has_flags(tracer::Trace::NETWORK_P2P_CONTENTS)) {
						trace.write_all(std::format("data_contents_hex: {}", bytes_to_hex(dest, *outMsgSize)));
						trace.write_all(std::format("data_contents_enc: {}", filesystem_container::filename_encode(std::string((char*)dest, (size_t)*outMsgSize))));
					}
				}
			}
		}

		return result;
	}
	
	bool NetworkingImpl::ReadP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel) {
		tracer::Trace trace{ networking_type, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("dest: {}", dest));
			trace.write_all(std::format("destSize: {}", destSize));
			trace.write_all(std::format("outMsgSize(addr): {}", (void*)outMsgSize));
			trace.write_all(std::format("channel: {}", channel));
		}

		auto result = intf()->ReadP2PPacket(dest, destSize, outMsgSize, outGalaxyID, channel);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
			if (result) {
				if (outMsgSize) {
					trace.write_all(std::format("outMsgSize: {}", *outMsgSize));
				}

				trace.write_all(std::format("outGalaxyID: {}", outGalaxyID));
				if (outMsgSize) {
					trace.write_all(std::format("data_hash: {:x}", const_hash64_data_loop((const char*)dest, *outMsgSize)));
					if (trace.has_flags(tracer::Trace::NETWORK_P2P_CONTENTS)) {
						trace.write_all(std::format("data_contents_hex: {}", bytes_to_hex(dest, *outMsgSize)));
						trace.write_all(std::format("data_contents_enc: {}", filesystem_container::filename_encode(std::string((char*)dest, (size_t)*outMsgSize))));
					}
				}
			}
		}

		return result;
	}

	bool NetworkingImpl::IsP2PPacketAvailable(uint32_t* outMsgSize, uint8_t channel) {
		tracer::Trace trace{ networking_type, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS | tracer::Trace::DETAILED };

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
		tracer::Trace trace{ networking_type, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("channel: {}", channel));
		}

		intf()->PopP2PPacket(channel);
	}

	int NetworkingImpl::GetPingWith(GalaxyID galaxyID) {
		tracer::Trace trace{ networking_type, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

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
		tracer::Trace trace{ networking_type, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		intf()->RequestNatTypeDetection();
	}

	NatType NetworkingImpl::GetNatType() {
		tracer::Trace trace{ networking_type, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = intf()->GetNatType();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_TYPE
	ConnectionType NetworkingImpl::GetConnectionType(GalaxyID userID) {
		tracer::Trace trace{ networking_type, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

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
