#include "Server.hxx"

#include "PeerData.hxx"

#include <Networking/Networking.hxx>

#define REQUIRES_AUTHENTICATION(peer) {if(KickUnauthenticated(peer)) { return; }}

namespace universelan::server {
	using namespace galaxy::api;

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

		PeerData::destruct(peer, peer_map);
		unauthenticated_peers.erase(peer);
		connected_peers.erase(peer);

		std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") EventDisconnect" << std::endl;
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<KeyChallengeMessage>& data)
	{
		PeerData* pd = PeerData::get(peer);
		if (pd->challenge.completed) { return; }

		if (pd->challenge.Validate(*data)) {
			auto entry = user_data.emplace(pd->id, std::make_shared<GalaxyUserData>(pd->id));
			if (entry.second) {
				if (PeerData::link(peer, data->id, peer_map)) {
					pd->user_data = entry.first->second;

					unauthenticated_peers.erase(peer);
					connection.Send(peer, ConnectionAcceptedMessage{});
					
					std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") KeyChallengeMessage ACCEPT" << std::endl;
					return;
				}
			}
		}

		std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") KeyChallengeMessage FAIL" << std::endl;
		connection.Disconnect(peer);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<UserHelloDataMessage>& data) {
		REQUIRES_AUTHENTICATION(peer);

		PeerData* pd = PeerData::get(peer);
		pd->user_data->stats = data->asuc;
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		REQUIRES_AUTHENTICATION(peer);

		PeerData* pd = PeerData::get(peer);
		PeerData* target = PeerData::get(data->id, peer_map);

		RequestSpecificUserDataMessage response{ data->type, data->id };

		if (target) {
			response.found = true;
			response.asuc = target->user_data->stats;
		}
		else {
			response.found = false;
		}

		connection.Send(peer, response);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<RequestChatRoomWithUserMessage>& data) {
		REQUIRES_AUTHENTICATION(peer);

		PeerData* pd = PeerData::get(peer);
		PeerData* target = PeerData::get(data->id, peer_map);

		RequestChatRoomWithUserMessage response{ data->request_id, data->id };

		if (target) {
			response.chat_room = chat_room_manager.CreateChatRoom();
			response.chat_room->AddMember(pd->id);
			response.chat_room->AddMember(data->id);

			connection.Send(target->peer, response);
		}
		else {
			response.chat_room = nullptr;
		}

		connection.Send(peer, response);
	}
}