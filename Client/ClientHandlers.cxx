#include "Client.hxx"

#include <Networking/Networking.hxx>

// Handlers:
void Client::Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data)
{
	std::cout << "Peer connected: " << peer->address.host << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;
}

void Client::Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data)
{
	std::cout << "Peer disconnected: " << peer->address.host << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;

	connection.Reconnect();
}

void Client::Handle(ENetPeer* peer, const std::shared_ptr<KeyChallengeMessage>& data)
{
	KeyChallengeMessage challenge = KeyChallengeMessage{}.response(const_hash64(interfaces->config->GetAuthenticationKey()), data->encrypted);

	connection.SendAsync(challenge);
}

void Client::Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAcceptedMessage>& data)
{
	std::cout << "Connection accepted by server" << std::endl;

	UserHelloDataMessage udm{ interfaces->config->GetApiGalaxyID() };

	udm.asuc = interfaces->config->GetASUC();

	connection.SendAsync(udm);
}

void Client::Handle(ENetPeer* peer, const std::shared_ptr<UserHelloDataMessage>& data)
{

}

void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestSpecificUserDataMessage>& data)
{
	interfaces->user->SpecificUserDataRequestProcessed(data);
}
