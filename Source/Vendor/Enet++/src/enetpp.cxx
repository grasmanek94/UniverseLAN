#include <enet6/enetpp.hxx>

#include <enet6/enetpp_helpers.hxx>

#include <cstddef>
#include <string>

namespace enetpp {

	NetworkBase::NetworkBase()
		: address{}, member{ nullptr }, event{}
	{
		initialisation_code = enet_initialize();
		atexit(enet_deinitialize);

		address.port = 0xBEEF;
	}

	NetworkBase::~NetworkBase()
	{
		if (member != nullptr)
		{
			enet_host_destroy(member);
		}
	}

	int NetworkBase::SetHost(const std::string& hostname, unsigned short port)
	{
		int code = enet_address_set_host(&address, ENET_ADDRESS_TYPE_ANY, hostname.c_str());
		address.port = port;
		return code;
	}

	const ENetAddress NetworkBase::Address()
	{
		return address;
	}

	const ENetEvent NetworkBase::Event()
	{
		return event;
	}

	int NetworkBase::GetInitCode()
	{
		return initialisation_code;
	}

	bool NetworkBase::Good()
	{
		return member != nullptr;
	}

	int NetworkBase::Pull(enet_uint32 timeout)
	{
		if (member == nullptr) {
			return -1;
		}

		return enet_host_service(member, &event, timeout);
	}

	int NetworkBase::Send(ENetPeer* peer, const void* data, size_t bytes, _ENetPacketFlag flags)
	{
		if ((peer == nullptr) || (data == nullptr)) {
			return -1;
		}

		return enet_peer_send(peer, 0, enet_packet_create(data, bytes, flags));
	}

	int NetworkBase::Send(ENetPeer* peer, ENetPacket* packet)
	{
		if ((peer == nullptr) || (packet == nullptr)) {
			return -1;
		}

		return enet_peer_send(peer, 0, packet);
	}

	NetworkServer::NetworkServer()
	{
		enet_address_build_any(&address, ENET_ADDRESS_TYPE_IPV6);
	}

	bool NetworkServer::Create(size_t max_connections)
	{
		if (member == nullptr)
		{
			member = enet_host_create(
				address.type,
				&address	                    /* the address to bind the server host to							*/,
				max_connections					/* allow up to max_connections clients and/or outgoing connections	*/,
				1								/* allow up to 1 channels to be used, 0								*/,
				0								/* assume any amount of incoming bandwidth							*/,
				0								/* assume any amount of outgoing bandwidth							*/);

			if (member == nullptr)
			{
				return false;
			}

			// TODO: make this into something more configurable
			member->maximumPacketSize = MAX_PACKET_SIZE;
			member->maximumWaitingData = MAX_PACKETS_PER_PEER * MAX_PACKET_SIZE;

			return member != nullptr;
		}
		return false;
	}

	void NetworkServer::Broadcast(const void* data, size_t bytes, _ENetPacketFlag flags)
	{
		enet_host_broadcast(member, 0, enet_packet_create(data, bytes, flags));
	}

	void NetworkServer::Broadcast(ENetPacket* packet)
	{
		enet_host_broadcast(member, 0, packet);
	}

	void NetworkServer::Broadcast(const void* data, size_t bytes, _ENetPacketFlag flags, ENetPeer* except)
	{
		enet_host_broadcast_except(member, 0, enet_packet_create(data, bytes, flags), except);
	}

	void NetworkServer::Broadcast(ENetPacket* packet, ENetPeer* except)
	{
		enet_host_broadcast_except(member, 0, packet, except);
	}

	void NetworkServer::Disconnect(ENetPeer* peer) {
		enet_peer_disconnect_now(peer, 0);
		enet_peer_reset(peer);
	}

	int NetworkServer::SetHost(const std::string& hostname, unsigned short port)
	{
		if ((hostname == "localhost") || (hostname == "LOCALHOST") || (hostname == "*")) {
			enet_address_build_any(&address, ENET_ADDRESS_TYPE_ANY);
			address.type = ENET_ADDRESS_TYPE_ANY;
			address.port = port;
			return 0;
		}

		return NetworkBase::SetHost(hostname, port);
	}

	NetworkClient::NetworkClient()
		: peer{ nullptr }
	{
		enet_address_set_host(&address, ENET_ADDRESS_TYPE_ANY, "localhost");
	}

	NetworkClient::~NetworkClient()
	{
		if (peer != nullptr)
		{
			enet_peer_disconnect_now(peer, 0);
			enet_peer_reset(peer);
			enet_host_destroy(member);
		}
	}

	ENetPeer* NetworkClient::Connect(std::string hostname, unsigned short port)
	{
		int set_host_code = SetHost(hostname, port);
		if (set_host_code < 0) {
			return nullptr;
		}

		if (member != nullptr)
		{
			enet_host_destroy(member);
			member = nullptr;
		}

		member = enet_host_create(
			address.type,
			nullptr,
			1								/* allow up to max_connections clients and/or outgoing connections	*/,
			1								/* allow up to 1 channels to be used, 0								*/,
			0								/* assume any amount of incoming bandwidth							*/,
			0								/* assume any amount of outgoing bandwidth							*/);

		if (member == nullptr)
		{
			return nullptr;
		}

		if (peer != nullptr)
		{
			enet_peer_reset(peer);
		}

		peer = enet_host_connect(member, &address, 1, 0);
		return peer;
	}

	ENetPeer* NetworkClient::Reconnect()
	{
		if (peer != nullptr)
		{
			enet_peer_reset(peer);
		}

		peer = enet_host_connect(member, &address, 1, 0);
		return peer;
	}

	void NetworkClient::Disconnect()
	{
		if (peer != nullptr)
		{
			enet_peer_disconnect_now(peer, 0);
		}
	}

	bool NetworkClient::Create()
	{
		return true;
	}

	int NetworkClient::Send(const void* data, size_t bytes, _ENetPacketFlag flags)
	{
		if ((peer == nullptr) || (data == nullptr)) {
			return -1;
		}

		return NetworkBase::Send(peer, data, bytes, flags);
	}

	int NetworkClient::Send(ENetPacket* packet)
	{
		if ((peer == nullptr) || (packet == nullptr)) {
			return -1;
		}

		return NetworkBase::Send(peer, packet);
	}
} /* namespace enetpp */