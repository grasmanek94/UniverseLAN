#include "Networking.hxx"

#include "UniverseLAN.hxx"

namespace universelan::client {
	using namespace galaxy::api;
	NetworkingImpl::NetworkingImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		buffer{}
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::INETWORKING };
	}

	NetworkingImpl::~NetworkingImpl()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::INETWORKING };
	}

	bool NetworkingImpl::SendP2PPacket(GalaxyID galaxyID, const void* data, uint32_t dataSize, P2PSendType sendType, uint8_t channel) {
		ENetPacketFlag flag{};

		switch (sendType) {
		case P2P_SEND_RELIABLE:
#if GALAXY_BUILD_FEATURE_HAS_P2P_SEND_IMMEDIATE
		case P2P_SEND_RELIABLE_IMMEDIATE:
#endif
			flag = ENET_PACKET_FLAG_RELIABLE;
			break;

		case P2P_SEND_UNRELIABLE:
#if GALAXY_BUILD_FEATURE_HAS_P2P_SEND_IMMEDIATE
		case P2P_SEND_UNRELIABLE_IMMEDIATE:
#endif
			// no unreliable flag?
			break;
		}

		intf->client->GetConnection().SendAsync(P2PNetworkPacketMessage{ galaxyID, channel, sendType, (const char*)data, dataSize }, flag);

		return true;
	}

	bool NetworkingImpl::GetP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel, bool pop) {
		auto channel_var = &buffer[channel];
		packet_t packet{ nullptr };
		{
			lock_t lock{ channel_var->mtx };
			if (channel_var->packets.empty()) {
				return false;
			}

			packet = channel_var->packets.front();
			if (pop) {
				channel_var->packets.pop();
			}
		}

		assert(packet != nullptr);

		outGalaxyID = packet->id;
		*outMsgSize = std::min((uint32_t)packet->data.size(), destSize);
		std::copy_n(packet->data.begin(), *outMsgSize, (char*)dest);

		return true;
	}

	bool NetworkingImpl::PeekP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel) {
		return GetP2PPacket(dest, destSize, outMsgSize, outGalaxyID, channel, false);
	}

	bool NetworkingImpl::ReadP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel) {
		return GetP2PPacket(dest, destSize, outMsgSize, outGalaxyID, channel, true);
	}

	bool NetworkingImpl::IsP2PPacketAvailable(uint32_t* outMsgSize, uint8_t channel) {
		auto channel_var = &buffer[channel];

		lock_t lock{ channel_var->mtx };
		if (channel_var->packets.empty()) {
			return false;
		}

		*outMsgSize = (int32_t)channel_var->packets.front()->data.size();
		return true;
	}

	void NetworkingImpl::PopP2PPacket(uint8_t channel) {
		auto channel_var = &buffer[channel];

		lock_t lock{ channel_var->mtx };
		channel_var->packets.pop();
	}

	int NetworkingImpl::GetPingWith(GalaxyID galaxyID) {
		return -1;
	}

#if GALAXY_BUILD_FEATURE_HAS_NAT_FUNCTIONALITY
	void NetworkingImpl::RequestNatTypeDetection() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::INETWORKING };

		listeners->NotifyAll(
			&INatTypeDetectionListener::OnNatTypeDetectionSuccess,
			NAT_TYPE_NONE);
	}

	NatType NetworkingImpl::GetNatType() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::INETWORKING };

		return NAT_TYPE_NONE;
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_TYPE
	ConnectionType NetworkingImpl::GetConnectionType(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::INETWORKING };

		return CONNECTION_TYPE_DIRECT;
	}
#endif

	void NetworkingImpl::AddPacket(const packet_t& packet) {
		if (!packet) {
			return;
		}

		// locked operation
		{
			auto channel_var = &buffer[packet->channel];

			lock_t lock{ channel_var->mtx };
			channel_var->packets.push(packet);
		}

		listeners->NotifyAllNow(&INetworkingListener::OnP2PPacketAvailable, (uint32_t)packet->data.size(), packet->channel);
	}
}
