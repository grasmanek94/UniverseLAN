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

#define REQUIRES_AUTHENTICATION(peer) {if(KickUnauthenticated(peer)) { return; }}

void Server::Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAcceptedMessage>& data) { REQUIRES_AUTHENTICATION(peer); /* Not handled in server */ }

void Server::Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data)
{
	PeerData* pd = PeerData::construct(peer);
	connected_peers.insert(peer);

	std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") EventConnect" << std::endl;

	connection.Send(peer, pd->challenge.Prepare(authentication_key, random()));
}

void Server::Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data)
{
	PeerData::destruct(peer);
	connected_peers.erase(peer);

	std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") EventDisconnect" << std::endl;
}

void Server::Handle(ENetPeer* peer, const std::shared_ptr<KeyChallengeMessage>& data)
{
	PeerData* pd = PeerData::get(peer);

	if (!pd->challenge.Validate(*data)) {
		std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") KeyChallengeMessage FAIL" << std::endl;
		connection.Disconnect(peer);
	}
	else {
		std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") KeyChallengeMessage ACCEPT" << std::endl;
		connection.Send(peer, ConnectionAcceptedMessage{});
	}
}

void Server::Handle(ENetPeer* peer, const std::shared_ptr<UserHelloDataMessage>& data) {
	REQUIRES_AUTHENTICATION(peer);

	PeerData* pd = PeerData::get(peer);

	//connection.Broadcast(message);
}

void Server::Handle(ENetPeer* peer, const std::shared_ptr<RequestUserDataMessage>& data) {
	REQUIRES_AUTHENTICATION(peer);

	PeerData* pd = PeerData::get(peer);

	//connection.Broadcast(message);
}

Server::Server()
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
	if (connection.Pull())
	{
		ProcessEvent(connection.Event());
	}
}

uint32_t Server::GetMaxTickRate() const {
	return config.GetMaxTickRate();
}

Server::~Server()
{

}
