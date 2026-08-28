#include <enet6/enetpp.hxx>

#include <enet6/enetpp_helpers.hxx>

#include <cstddef>
#include <string>

namespace enetpp {

	NetworkBase::NetworkBase()
		: address{}, member{ nullptr }, event{}
	{
		// REVIEW: Every NetworkBase instance initializes ENet and registers a
		// separate atexit callback. This library creates multiple base objects
		// (client/server and per-version builds), so global initialization and
		// cleanup are not paired safely. Centralize initialization with
		// one-time/ref-counted ownership and only deinitialize after all hosts die.
		initialisation_code = enet_initialize();
		atexit(enet_deinitialize);

		address.port = 0xBEEF;
	}

	NetworkBase::~NetworkBase()
	{
		if (member != nullptr)
		{
			// REVIEW: `member` is owned here, but NetworkClient::~NetworkClient
			// also destroys it without clearing the pointer. That derived
			// destructor is followed by this base destructor, so the same ENet
			// host can be destroyed twice.
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

		// REVIEW: enet_packet_create may return nullptr. enet_peer_send
		// dereferences the packet before checking it, so pass only an allocated
		// packet and return failure without leaking it.
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
			member->maximumWaitingData = MAX_WAITING_DATA;

			return member != nullptr;
		}
		return false;
	}

	void NetworkServer::Broadcast(const void* data, size_t bytes, _ENetPacketFlag flags)
	{
		// REVIEW: This forwards member, data, and the allocation result without
		// validation. ENet's broadcast path dereferences the host and packet;
		// surface a failed/uninitialized server or packet allocation safely.
		enet_host_broadcast(member, 0, enet_packet_create(data, bytes, flags));
	}

	void NetworkServer::Broadcast(ENetPacket* packet)
	{
		// REVIEW: No host or packet check is performed before ENet dereferences
		// both. Make the initialized-server and ownership preconditions explicit.
		enet_host_broadcast(member, 0, packet);
	}

	void NetworkServer::Broadcast(const void* data, size_t bytes, _ENetPacketFlag flags, ENetPeer* except)
	{
		// REVIEW: The custom except-broadcast has the same unchecked host/data/
		// allocation inputs as the normal broadcast path.
		enet_host_broadcast_except(member, 0, enet_packet_create(data, bytes, flags), except);
	}

	void NetworkServer::Broadcast(ENetPacket* packet, ENetPeer* except)
	{
		// REVIEW: The custom helper dereferences both host and packet; reject
		// calls made before Create() or with a null packet.
		enet_host_broadcast_except(member, 0, packet, except);
	}

	void NetworkServer::Disconnect(ENetPeer* peer) {
		// REVIEW: ENet's disconnect/reset functions require a valid peer. A stale
		// mapper entry or failed connection can pass nullptr and crash here.
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
			// REVIEW: NetworkBase owns `member` and destroys it immediately after
			// this body. Destroying it here as well leaves a dangling non-null
			// pointer for the base destructor, causing a double destroy.
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
			// REVIEW: `peer` points into this host. Replacing member without
			// resetting/clearing peer leaves a pointer into freed storage; the
			// subsequent Reconnect() calls enet_peer_reset(peer) on that storage.
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

		return Reconnect();
	}

	ENetPeer* NetworkClient::Reconnect()
	{
		if (peer != nullptr)
		{
			// REVIEW: This peer may belong to a host already destroyed by
			// Connect(). Reset it only while its owning member is alive, then
			// clear the handle before creating a replacement.
			enet_peer_reset(peer);
		}

		// REVIEW: Reconnect does not validate member. After host creation fails,
		// enet_host_connect receives nullptr and dereferences it.
		peer = enet_host_connect(member, &address, 1, 0);
		return peer;
	}

	void NetworkClient::Disconnect()
	{
		if (peer != nullptr)
		{
			// REVIEW: Disconnect leaves peer non-null. A later Connect() destroys
			// member while this handle still points into the old host, and a later
			// Send() can also use a disconnected peer. Clear or replace the handle
			// as part of the lifecycle transition.
			enet_peer_disconnect_now(peer, 0);
		}
	}

	bool NetworkClient::Create()
	{
		// REVIEW: The public Create() operation reports success without creating
		// a host. Callers relying on Good() or Pull() then observe an uninitialized
		// client; either implement creation or make the unsupported operation clear.
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