#include <enet6/enetpp.hxx>

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
	address.port = port;
	if ((hostname == "localhost") || (hostname == "LOCALHOST")) {
		address.type = ENET_ADDRESS_TYPE_ANY;
		return 0;
	}

	return enet_address_set_host(&address, address.type, hostname.c_str());
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
	return enet_host_service(member, &event, timeout);
}

int NetworkBase::Send(ENetPeer* peer, const void* data, size_t bytes, _ENetPacketFlag flags)
{
	return enet_peer_send(peer, 0, enet_packet_create(data, bytes, flags));
}

int NetworkBase::Send(ENetPeer* peer, ENetPacket* packet)
{
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
		if (address.type == ENET_ADDRESS_TYPE_ANY) {
			ENetAddress any_address;
			enet_address_build_any(&any_address, ENET_ADDRESS_TYPE_IPV6);
			any_address.port = address.port;

			member = enet_host_create(
				ENET_ADDRESS_TYPE_ANY           /* Dual stack IPv4+IPv6 support                                     */,
				&any_address	                /* the address to bind the server host to							*/,
				max_connections					/* allow up to max_connections clients and/or outgoing connections	*/,
				1								/* allow up to 1 channels to be used, 0								*/,
				0								/* assume any amount of incoming bandwidth							*/,
				0								/* assume any amount of outgoing bandwidth							*/);
		}
		else {
			member = enet_host_create(
				address.type,
				&address	                    /* the address to bind the server host to							*/,
				max_connections					/* allow up to max_connections clients and/or outgoing connections	*/,
				1								/* allow up to 1 channels to be used, 0								*/,
				0								/* assume any amount of incoming bandwidth							*/,
				0								/* assume any amount of outgoing bandwidth							*/);
		}

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
	}
}

ENetPeer* NetworkClient::Connect(std::string hostname, unsigned short port)
{
	if (peer != nullptr)
	{
		enet_peer_reset(peer);
	}

	int set_host_code = SetHost(hostname, port);
	if (set_host_code < 0) {
		return nullptr;
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
	if (member == nullptr)
	{
		member = enet_host_create(
			ENET_ADDRESS_TYPE_ANY           /* dual IPv4 and IPv6                                               */,
			nullptr,
			1								/* allow up to max_connections clients and/or outgoing connections	*/,
			1								/* allow up to 1 channels to be used, 0								*/,
			0								/* assume any amount of incoming bandwidth							*/,
			0								/* assume any amount of outgoing bandwidth							*/);

		return member != nullptr;
	}
	return false;
}

int NetworkClient::Send(const void* data, size_t bytes, _ENetPacketFlag flags)
{
	return NetworkBase::Send(peer, data, bytes, flags);
}

int NetworkClient::Send(ENetPacket* packet)
{
	return NetworkBase::Send(peer, packet);
}

extern "C" {

	/** Queues a packet to be sent to all peers associated with the host.
	@param host host on which to broadcast the packet
	@param channelID channel on which to broadcast
	@param packet packet to broadcast
	*/
	void
		enet_host_broadcast_except(ENetHost* host, enet_uint8 channelID, ENetPacket* packet, ENetPeer* except)
	{
		ENetPeer* currentPeer;

		for (currentPeer = host->peers;
			currentPeer < &host->peers[host->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED || currentPeer == except)
				continue;

			enet_peer_send(currentPeer, channelID, packet);
		}

		if (packet->referenceCount == 0)
			enet_packet_destroy(packet);
	}
}
