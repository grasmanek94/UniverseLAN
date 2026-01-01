#ifndef ENETPP_HEADER
#define ENETPP_HEADER

#include <enet6/enet.h>

#include <format>
#include <ostream>
#include <string>

class NetworkBase;
class NetworkServer;
class NetworkClient;

class NetworkBase
{
	friend class NetworkServer;
	friend class NetworkClient;
private:
	ENetAddress address;
	ENetHost* member;
	ENetEvent event;

	int initialisation_code;

	NetworkBase();

public:
	int SetHost(std::string hostname, unsigned short port);
	const ENetAddress Address();
	const ENetEvent Event();
	int GetInitCode();
	bool Good();
	int Pull(enet_uint32 timeout = 0);
	int Send(ENetPeer* peer, const void* data, size_t bytes, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE);
	int Send(ENetPeer* peer, ENetPacket* packet);

	virtual ~NetworkBase();
};

class NetworkServer : public NetworkBase
{
public:
	NetworkServer();
	virtual ~NetworkServer() {}

	bool Create(size_t max_connections = 2);
	void Broadcast(const void* data, size_t bytes, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE);
	void Broadcast(ENetPacket* packet);
	void Broadcast(const void* data, size_t bytes, _ENetPacketFlag flags, ENetPeer* except);
	void Broadcast(ENetPacket* packet, ENetPeer* except);
	void Disconnect(ENetPeer* peer);
};

class NetworkClient : public NetworkBase
{
private:
	ENetPeer* peer;
public:
	NetworkClient();
	virtual ~NetworkClient();

	ENetPeer* Connect(std::string hostname, unsigned short port);
	ENetPeer* Reconnect();
	void Disconnect();

	bool Create();
	int Send(const void* data, size_t bytes, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE);
	int Send(ENetPacket* packet);
};

const size_t MAX_PACKET_SIZE = 32 * 1024;//k bytes
const size_t MAX_PACKETS_PER_PEER = 512;

extern "C" {
	ENET_API void       enet_host_broadcast_except(ENetHost*, enet_uint8, ENetPacket*, ENetPeer*);
}

template <>
struct std::formatter<ENetAddress> : std::formatter<std::string> {
	auto format(const ENetAddress& p, format_context& ctx) const {
		switch (p.type) {
		case ENET_ADDRESS_TYPE_IPV4:
			return formatter<string>::format(
				std::format("{:d}.{:d}.{:d}.{:d}:{:d}",
					p.host.v4[0], p.host.v4[1], p.host.v4[2], p.host.v4[3], p.port),
				ctx);
		case ENET_ADDRESS_TYPE_IPV6:
			return formatter<string>::format(
				std::format("[{:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}]:{:d}",
					p.host.v6[0], p.host.v6[1], p.host.v6[2], p.host.v6[3], p.host.v6[4], p.host.v6[5], p.host.v6[6], p.host.v6[7], p.port),
				ctx);
		case ENET_ADDRESS_TYPE_ANY:
			return formatter<string>::format(
				std::format("[{:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}]:{:d} | {:d}.{:d}.{:d}.{:d}:{:d}",
					p.host.v6[0], p.host.v6[1], p.host.v6[2], p.host.v6[3], p.host.v6[4], p.host.v6[5], p.host.v6[6], p.host.v6[7], p.port,
					p.host.v4[0], p.host.v4[1], p.host.v4[2], p.host.v4[3], p.port),
				ctx);
		default:
			throw std::format_error("Unkown ENET_ADDRESS_TYPE");
		}
	}
};

inline std::ostream& operator << (std::ostream& os, const ENetAddress& p)
{
	os << std::format("{}", p);

	return os;
}

#endif