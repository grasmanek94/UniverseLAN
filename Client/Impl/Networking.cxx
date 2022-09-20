#include "Networking.hxx"

#include "UniverseLAN.hxx"

namespace universelan::client {
	using namespace galaxy::api;
	NetworkingImpl::NetworkingImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		buffer{}
	{}

	NetworkingImpl::~NetworkingImpl()
	{}

	bool NetworkingImpl::SendP2PPacket(GalaxyID galaxyID, const void* data, uint32_t dataSize, P2PSendType sendType, uint8_t channel) {
		ENetPacketFlag flag{};

		switch (sendType) {
		case P2P_SEND_RELIABLE:
		case P2P_SEND_RELIABLE_IMMEDIATE:
			flag = ENET_PACKET_FLAG_RELIABLE;
			break;

		case P2P_SEND_UNRELIABLE:
		case P2P_SEND_UNRELIABLE_IMMEDIATE:
			// no unreliable flag?
			break;
		}

		intf->client->GetConnection().SendAsync(P2PNetworkPacketMessage{ galaxyID, channel, sendType, (const char*)data, dataSize }, flag);

		return true;
	}

	bool NetworkingImpl::GetP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel, bool pop) {
		channels_array::value_type& channel_var = buffer[channel];
		packet_t packet{ nullptr };
		{
			lock_t lock{ channel_var.mtx };
			if (channel_var.packets.empty()) {
				return false;
			}

			packet = channel_var.packets.front();
			if (pop) {
				channel_var.packets.pop();
			}
		}

		assert(packet);

		outGalaxyID = packet->id;
		*outMsgSize = std::min((uint32_t)packet->data.size(), destSize);
		std::copy_n(packet->data.begin(), *outMsgSize, (char*)dest);

		return true;
	}

	bool NetworkingImpl::PeekP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel) {
		return GetP2PPacket(dest, destSize, outMsgSize, outGalaxyID, channel, false);
	}

	bool NetworkingImpl::IsP2PPacketAvailable(uint32_t* outMsgSize, uint8_t channel) {
		return buffer[channel].count.load() > 0;
	}

	bool NetworkingImpl::ReadP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel) {
		return GetP2PPacket(dest, destSize, outMsgSize, outGalaxyID, channel, true);
	}

	void NetworkingImpl::PopP2PPacket(uint8_t channel) {
		channels_array::value_type& channel_var = buffer[channel];

		lock_t lock{ channel_var.mtx };
		channel_var.count.fetch_sub(1);
		channel_var.packets.pop();
	}

	int NetworkingImpl::GetPingWith(GalaxyID galaxyID) {
		return -1;
	}

	void NetworkingImpl::RequestNatTypeDetection() {
		listeners->NotifyAll<INatTypeDetectionListener>(
			&INatTypeDetectionListener::OnNatTypeDetectionSuccess,
			NAT_TYPE_NONE);
	}

	NatType NetworkingImpl::GetNatType() {
		return NAT_TYPE_NONE;
	}

	ConnectionType NetworkingImpl::GetConnectionType(GalaxyID userID) {
		return CONNECTION_TYPE_DIRECT;
	}

	void NetworkingImpl::AddPacket(const NetworkingImpl::packet_t& packet) {
		if (!packet) {
			return;
		}

		channels_array::value_type& channel_var = buffer[packet->channel];

		lock_t lock{ channel_var.mtx };
		channel_var.count.fetch_add(1);
		channel_var.packets.push(packet);
	}
}
