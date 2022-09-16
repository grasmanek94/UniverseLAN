#include "Client.hxx"

#include <Networking/Networking.hxx>

#include "UniverseLAN.hxx"

// Handlers:
void Client::Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data)
{
	std::cout << "Peer connected: " << peer->address.host << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;
}

void Client::Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data)
{
	std::cout << "Peer disconnected: " << peer->address.host << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;

	//connection.Reconnect();
}

void Client::Handle(ENetPeer* peer, const std::shared_ptr<KeyChallengeMessage>& data)
{
	KeyChallengeMessage challenge = KeyChallengeMessage{}.response(const_hash64(galaxy::api::config->GetAuthenticationKey()), data->encrypted);

	connection.SendAsync(challenge);
}

void Client::Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAcceptedMessage>& data)
{
	std::cout << "Connection accepted by server" << std::endl;

	UserHelloDataMessage udm{ galaxy::api::config->GetApiGalaxyID() };
	udm.asuc = galaxy::api::config->GetASUC();

	connection.SendAsync(udm);
}

void Client::Handle(ENetPeer* peer, const std::shared_ptr<UserHelloDataMessage>& data)
{

}

void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestUserDataMessage>& data)
{

}

Client::Client(const std::string& address, uint16_t port)
	: running{ false }, tick_thread{}, connection{}
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

	if (!connection.Create() || !connection.Good())
	{
#ifdef _WIN32
		// TODO custom exception class
		throw std::exception("ENET host member creation failed");
#endif
	}

	connection.Connect(address, port);
}

void Client::Tick()
{
	while (running) {
		connection.RunNetworking(2);
	}

	connection.Disconnect();
}

Client::~Client()
{
	Stop();
}

void Client::Start()
{
	running = true;
	tick_thread = std::thread{ &Client::Tick, this };
}

void Client::Stop()
{
	running = false;
	if (tick_thread.joinable()) {
		tick_thread.join();
	}
}

void Client::ProcessEvents()
{
	connection.ProcessEvents(this);
}
