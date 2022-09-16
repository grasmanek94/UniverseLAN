#include <Common.hxx>
#include <IdCounter.hxx>
#include <IniData.hxx>
#include <Networking/Networking.hxx>
#include <Version.hxx>

#include <GalaxyApi.h>

#include <algorithm>
#include <chrono>
#include <exception>
#include <iostream>
#include <random>
#include <set>
#include <thread>

class PeerData {
private:
	PeerData() : peer{}, id{ 0ULL }, challenge{}, connected_time{ std::chrono::system_clock::now() }
	{}

public:
	struct Challenge {
		bool completed;
		uint64_t data;
		KeyChallenge for_client;
		KeyChallenge expected_response;

		Challenge() : completed{ false }, data{ 0ULL }, for_client{}, expected_response{} {}

		void Prepare(uint64_t key, uint64_t rnd) {
			data = rnd;
			for_client = KeyChallenge{}.challenge(key, data);
			expected_response = KeyChallenge{}.response(key, for_client.encrypted);
		}

		bool Validate(const KeyChallenge& response) {
			completed = (response.encrypted == expected_response.encrypted);
			return completed;
		}
	};

	ENetPeer* peer;
	galaxy::api::GalaxyID id;
	Challenge challenge;
	std::chrono::system_clock::time_point connected_time;

	virtual ~PeerData() {}

	static PeerData* get(ENetPeer* peer) {
		assert(peer != nullptr);
		assert(peer->data != nullptr);

		return (PeerData*)peer->data;
	}

	static PeerData* construct(ENetPeer* peer) {
		if (peer == nullptr) {
			return nullptr;
		}

		PeerData* peer_data = new PeerData();
		peer_data->peer = peer;
		peer->data = (void*)peer_data;

		return peer_data;
	}

	static void destruct(ENetPeer* peer) {
		if (peer == nullptr) {
			return;
		}

		PeerData* peer_data = (PeerData*)peer->data;
		if (peer_data) {
			peer->data = nullptr;
			delete peer_data;
		}
	}
};

class Server : public MessageReceiver
{
private:
	ServerIniData config;
	GalaxyNetworkServer connection;
	IdCounter id_generator;
	size_t max_connections;
	std::set<ENetPeer*> connected_peers;
	uint64_t authentication_key;
	std::mt19937_64 random;

	bool KickUnauthenticated(ENetPeer* peer) {
		PeerData* pd = PeerData::get(peer);

		if (pd == nullptr) {
			return false;
		}

		if (pd->challenge.completed) {
			return true;
		}

		connection.Disconnect(peer);

		return false;
	}

#define REQUIRES_AUTHENTICATION(peer) {if(KickUnauthenticated(peer)) { return; }}

	// Handlers:
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAccepted>& data) override {}

	void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) override
	{
		PeerData* pd = PeerData::construct(peer);
		connected_peers.insert(peer);

		std::cout << "Peer connected: " << peer->address.host << ":" << peer->address.port << std::endl;

		pd->challenge.Prepare(authentication_key, random());

		connection.Send(peer, pd->challenge.for_client);
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<KeyChallenge>& data) override
	{
		PeerData* pd = PeerData::get(peer);

		if (!pd->challenge.Validate(*data)) {
			connection.Disconnect(peer);
		} else {
			connection.Send(peer, ConnectionAccepted{});
		}
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) override
	{
		PeerData::destruct(peer);

		//PlayerQuit player_quit;
		//player_quit.SetSender(player->id);

		//connection.Broadcast(player_quit, peer);

		std::cout << "Peer disconnected: " << peer->address.host << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;

		connected_peers.erase(peer);
		//id_generator.FreeId(player->id);
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<ChatMessage>& message) override
	{
		REQUIRES_AUTHENTICATION(peer);

		PeerData* pd = PeerData::get(peer);

		//message->SetSender(player->id);

		//std::wcout << "[" << message->GetSender() << "]: " << message->GetContents() << std::endl;

		//connection.Broadcast(message);
	}

public:
	Server()
		: id_generator()
	{
		int init_code = connection.GetInitCode();

		if (init_code)
		{
			// TODO custom exception class
			throw std::exception(
#ifdef _WIN32
			("Cannot initialize ENET, error code: " + std::to_string(init_code)).c_str()
#endif
			);
		}

		connection.SetHost(config.GetBindAddress(), config.GetPort());

		std::cout << "Binding addr: " << config.GetBindAddress() << ":" << config.GetPort() << std::endl;

		max_connections = config.GetMaxConnections();

		std::cout << "Max Connections: " << max_connections << std::endl;
		if (!connection.Create(max_connections) || !connection.Good())
		{
#ifdef _WIN32
			// TODO custom exception class
			throw std::exception("ENET host member creation failed");
#endif
		}

		authentication_key = const_hash64(config.GetAuthenticationKey());
		uint64_t milliseconds_since_epoch =
			std::chrono::system_clock::now().time_since_epoch() /
			std::chrono::milliseconds(1);

		random.seed(authentication_key ^ milliseconds_since_epoch);

		std::cout << "Using key: " << authentication_key << std::endl;
		std::cout << "Listening..." << std::endl;
		//ready
	}

	void Tick()
	{
		if (connection.Pull())
		{
			ProcessEvent(connection.Event());
		}
	}

	uint32_t GetMaxTickRate() const {
		return config.GetMaxTickRate();
	}

	~Server()
	{

	}
};

std::unique_ptr<Server> server;
int main()
{
	std::cout << "Version: " << Version_Number << std::endl;

	server = std::make_unique<Server>();
	std::chrono::milliseconds wait_time = std::chrono::milliseconds(1000 / server->GetMaxTickRate());

	while (true)
	{
		server->Tick();
		std::this_thread::sleep_for(wait_time);
	}
	return 0;
}
