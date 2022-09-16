#include "Server.hxx"

#include "PeerData.hxx"

#include <Networking/Networking.hxx>

#include <chrono>
#include <exception>
#include <iostream>

bool Server::KickUnauthenticated(ENetPeer* peer) {
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

Server::Server()
	: config{}, connection{}, id_generator{}, max_connections{ 1024 },
	connected_peers{}, authentication_key{ 0 }, random{}, ticks{ 0 }, minimum_tick_wait_time{ 0 }, user_data {}
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

	std::cout << "Binding address: " << config.GetBindAddress() << ":" << config.GetPort() << std::endl;

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

void Server::Tick()
{
	while (connection.Pull())
	{
		ProcessEvent(connection.Event());
	}

	if (++ticks > 50) {
		ticks = 0;
		auto now = std::chrono::system_clock::now();
		for (auto& peer : unauthenticated_peers) {
			PeerData* pd = PeerData::get(peer);
			if (pd == nullptr) {
				connection.Disconnect(peer);
			}
			else {
				auto time = ((now - pd->connected_time) / std::chrono::milliseconds(1));
				if (time > 2500) {
					connection.Disconnect(peer);
				}
			}
		}
	}
}

uint32_t Server::GetMaxTickRate() const {
	return config.GetMaxTickRate();
}

Server::~Server()
{

}
