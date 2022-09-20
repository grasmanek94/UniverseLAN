#include "Server.hxx"

#include "PeerData.hxx"

#include <Networking/Networking.hxx>

#define REQUIRES_AUTHENTICATION(peer) {if(KickUnauthenticated(peer)) { return; }}

namespace universelan::server {
	using namespace galaxy::api;

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAcceptedMessage>& data) { REQUIRES_AUTHENTICATION(peer); /* Not handled in server */ }
	void Server::Handle(ENetPeer* peer, const std::shared_ptr<FileShareResponseMessage>& data) { REQUIRES_AUTHENTICATION(peer); }

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

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<RequestChatRoomMessagesMessage>& data) {
		REQUIRES_AUTHENTICATION(peer);

		PeerData* pd = PeerData::get(peer);

		auto chat_room = chat_room_manager.GetChatRoom(data->id);

		ChatRoom::messages_t messages{};
		if (chat_room && chat_room->IsMember(pd->id)) {
			messages = chat_room->GetMessages(data->oldest_message);
		}
		RequestChatRoomMessagesMessage response{ data->request_id, data->id, data->oldest_message, messages };

		connection.Send(peer, response);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<SendToChatRoomMessage>& data) {
		REQUIRES_AUTHENTICATION(peer);

		PeerData* pd = PeerData::get(peer);

		auto chat_room = chat_room_manager.GetChatRoom(data->id);

		if (chat_room && chat_room->IsMember(pd->id) && data->message) {
			ChatMessageID oldest_message{ 0 };
			if (chat_room->GetMessageCount() > 0) {
				oldest_message = chat_room->GetMessages().back()->GetID();
			}

			auto message = chat_room->AddMessage(pd->id, CHAT_MESSAGE_TYPE_CHAT_MESSAGE, data->message->GetContents());

			connection.Send(peer, SendToChatRoomMessage{ data->request_id, data->id, nullptr });

			ChatRoom::messages_t messages{};
			messages.push_back(message);
			RequestChatRoomMessagesMessage notification{ data->request_id, data->id, oldest_message, messages };

			for (const auto& member : chat_room->GetMembers()) {
				PeerData* member_peer = PeerData::get(member, peer_map);
				connection.Send(member_peer->peer, notification);
			}
		}
		else {
			connection.Send(peer, SendToChatRoomMessage{ data->request_id, data->id, nullptr });
		}
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<P2PNetworkPacketMessage>& data) {
		REQUIRES_AUTHENTICATION(peer);

		PeerData* pd = PeerData::get(peer);
		PeerData* target_pd = PeerData::get(data->id, peer_map);

		if (target_pd) {
			data->id = pd->id;
			connection.Send(peer, *data);
		}
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<FileShareMessage>& data) {
		REQUIRES_AUTHENTICATION(peer);

		FileShareResponseMessage fsrm{ data->request_id, ++shared_file_counter, data->filename };
		sfu.OpenShared(shared_file_counter_file, std::ios::trunc) << fsrm.id;
		if (!sfu.InitSharedFileStorage(fsrm.filename, fsrm.id)) {
			std::cerr << "FileShareMessage::InitSharedFileStorage FAIL\n";
		}

		if (!sfu.WriteShared(fsrm.filename, data->data.data(), data->data.size())) {
			std::cerr << "FileShareMessage::WriteShared FAIL\n";
		}

		connection.Send(peer, fsrm);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<FileRequestMessage>& data) {
		REQUIRES_AUTHENTICATION(peer);

		if (data->id != 0) {
			data->data = sfu.ReadShared(data->id);
			data->filename = sfu.GetSharedFileName(data->id);
		} else if(data->filename.size() != 0) {
			data->data = sfu.ReadShared(data->filename);
			data->id = sfu.GetSharedFileID(data->filename);
		}

		if (data->data.size() == 0) {
			std::cerr << "FileShareMessage::ReadShared FAIL\n";
		}

		connection.Send(peer, data);
	}
}
