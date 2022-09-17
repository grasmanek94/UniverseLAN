#include "Server.hxx"

#include "PeerData.hxx"

#include <Networking/Networking.hxx>

#define REQUIRES_AUTHENTICATION(peer) {if(KickUnauthenticated(peer)) { return; }}

void Server::Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAcceptedMessage>& data) { REQUIRES_AUTHENTICATION(peer); /* Not handled in server */ }

void Server::Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data)
{
	PeerData* pd = PeerData::construct(peer);
	connected_peers.insert(peer);
	unauthenticated_peers.insert(peer);

	std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") EventConnect" << std::endl;

	connection.Send(peer, pd->challenge.Prepare(authentication_key, random()));
}

void Server::Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data)
{
	PeerData* pd = PeerData::get(peer);
	user_data.erase(pd->id);
		
	PeerData::destruct(peer);
	unauthenticated_peers.erase(peer);
	connected_peers.erase(peer);

	std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") EventDisconnect" << std::endl;
}

void Server::Handle(ENetPeer* peer, const std::shared_ptr<KeyChallengeMessage>& data)
{
	PeerData* pd = PeerData::get(peer);
	if (pd->challenge.completed) { return; }

	if (!pd->challenge.Validate(*data)) {
		std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") KeyChallengeMessage FAIL" << std::endl;
		connection.Disconnect(peer);
	}
	else {
		std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") KeyChallengeMessage ACCEPT" << std::endl;
		unauthenticated_peers.erase(peer);
		connection.Send(peer, ConnectionAcceptedMessage{});
	}
}

void Server::Handle(ENetPeer* peer, const std::shared_ptr<UserHelloDataMessage>& data) {
	REQUIRES_AUTHENTICATION(peer);

	PeerData* pd = PeerData::get(peer);

	pd->id = data->id;

	auto entry = user_data.emplace(pd->id, std::make_shared<GalaxyUserData>(pd->id));
	if (!entry.second) { // id already exists
		connection.Disconnect(peer);
	}
	else {
		entry.first->second->stats = data->asuc;
	}
}

void Server::Handle(ENetPeer* peer, const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
	REQUIRES_AUTHENTICATION(peer);

	PeerData* pd = PeerData::get(peer);

	auto found = user_data.find(data->id);
	RequestSpecificUserDataMessage response{ data->id };

	if (found == user_data.end()) {
		response.found = false;
	}
	else {
		response.found = true;
		response.asuc = found->second->stats;
	}

	connection.Send(peer, response);
}
