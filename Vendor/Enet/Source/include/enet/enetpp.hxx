#ifndef ENETPP_HEADER
#define ENETPP_HEADER

#include <string>
#include <enet/enet.h>

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
	~NetworkBase();
public:
	void SetHost(std::string hostname, unsigned short port);
	const ENetAddress Address();
	const ENetEvent Event();
	int GetInitCode();
	bool Good();
	int Pull(enet_uint32 timeout = 0);
	int Send(ENetPeer* peer, const void* data, size_t bytes, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE);
	int Send(ENetPeer* peer, ENetPacket* packet);
};

class NetworkServer : public NetworkBase
{
public:
	NetworkServer();
	bool Create(size_t max_connections = 2);
	void Broadcast(const void* data, size_t bytes, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE);
	void Broadcast(ENetPacket* packet);
	void Broadcast(const void* data, size_t bytes, _ENetPacketFlag flags, ENetPeer* except);
	void Broadcast(ENetPacket* packet, ENetPeer* except);
};

class NetworkClient : public NetworkBase
{
private:
	ENetPeer * peer;
public:
	NetworkClient();
	~NetworkClient();
	ENetPeer * Connect(std::string hostname, unsigned short port);
	bool Create();
	int Send(const void* data, size_t bytes, _ENetPacketFlag flags = ENET_PACKET_FLAG_RELIABLE);
	int Send(ENetPacket* packet);
};

const size_t MAX_PACKET_SIZE = 32 * 1024;//k bytes
const size_t MAX_PACKETS_PER_PEER = 512;
#endif