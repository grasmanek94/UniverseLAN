#include "Server.hxx"

#include "Peer.hxx"

#include <Networking/Networking.hxx>
#include <Tracer.hxx>

#define REQUIRES_AUTHENTICATION(peer) {if(!KickUnauthenticated(peer)) { return; }}

namespace universelan::server {
	using namespace galaxy::api;

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAcceptedMessage>& data) { tracer::Trace trace{ "::ConnectionAcceptedMessage" }; REQUIRES_AUTHENTICATION(peer); /* Not handled in server */ }
	void Server::Handle(ENetPeer* peer, const std::shared_ptr<FileShareResponseMessage>& data) { tracer::Trace trace{ "::FileShareResponseMessage" }; REQUIRES_AUTHENTICATION(peer); }
	void Server::Handle(ENetPeer* peer, const std::shared_ptr<CreateLobbyResponseMessage>& data) { tracer::Trace trace{ "::CreateLobbyResponseMessage" }; REQUIRES_AUTHENTICATION(peer); }
	void Server::Handle(ENetPeer* peer, const std::shared_ptr<LobbyMemberStateChangeMessage>& data) { tracer::Trace trace{ "::LobbyMemberStateChangeMessage" }; REQUIRES_AUTHENTICATION(peer); }
	void Server::Handle(ENetPeer* peer, const std::shared_ptr<LobbyOwnerChangeMessage>& data) { tracer::Trace trace{ "::LobbyOwnerChangeMessage" }; REQUIRES_AUTHENTICATION(peer); }
	void Server::Handle(ENetPeer* peer, const std::shared_ptr<OnlineStatusChangeMessage>& data) { tracer::Trace trace{ "::OnlineStatusChangeMessage" }; REQUIRES_AUTHENTICATION(peer); }

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data)
	{
		tracer::Trace trace{ "::EventConnect" };

		peer->data = nullptr;
		std::cout << "Peer(" 
			<< std::hex << peer->address.host << ":" << std::dec << peer->address.port
			<< ") EventConnect" << std::endl;

		peer::ptr pd = peer_mapper.Connect(peer);
		unauthenticated_peers.insert(peer);

		connection.Send(peer, pd->challenge.Prepare(authentication_key, random()));
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data)
	{
		tracer::Trace trace{ "::EventDisconnect" };

		std::cout << "Peer(" 
			<< std::hex << peer->address.host << ":" << std::dec << peer->address.port
			<< ") EventDisconnect" << std::endl;

		unauthenticated_peers.erase(peer);

		peer::ptr pd = peer_mapper.Get(peer);
		if (pd) {
			HandleMemberLobbyLeave(peer, true);
#if GALAXY_BUILD_FEATURE_HAS_ICHAT
			HandleMemberChatLeave(peer);
#endif

			user_data.erase(pd->id);

			if (pd->id.IsValid()) {
				connection.Broadcast(OnlineStatusChangeMessage{ pd->id, false }, peer);
			}
			pd = nullptr;
		}

		peer_mapper.Disconnect(peer);
		peer->data = nullptr;
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<KeyChallengeMessage>& data)
	{
		tracer::Trace trace{ "::KeyChallengeMessage"};

		peer::ptr pd = peer_mapper.Get(peer);
		if (pd->challenge.completed) { return; }

		if (pd->challenge.Validate(*data)) {
			auto entry = user_data.emplace(data->id, std::make_shared<GalaxyUserData>(data->id));
			if (entry.second) {
				pd->id = data->id;
				if (pd->link(data->id)) {
					tracer::Trace validated{ "::challenge.Validate" };

					pd->user_data = entry.first->second;

					unauthenticated_peers.erase(peer);
					connection.Send(peer, ConnectionAcceptedMessage{});
					connection.Broadcast(OnlineStatusChangeMessage{ pd->id, true }, peer);

					std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") KeyChallengeMessage ACCEPT" << std::endl;
					return;
				}
			}
		}

		std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") KeyChallengeMessage FAIL" << std::endl;
		connection.Disconnect(peer);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<UserHelloDataMessage>& data) {
		tracer::Trace trace{ "::UserHelloDataMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);
		pd->user_data->stats = data->asuc;
		if (!data->nickname.empty() && pd->user_data->nickname.empty()) {
			pd->user_data->nickname = data->nickname;
		}
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{ "::RequestSpecificUserDataMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);
		peer::ptr target = peer_mapper.Get(data->id);

		RequestSpecificUserDataMessage response{ data->type, data->request_id, data->id };

		if (target) {
			response.found = true;
			response.asuc = target->user_data->stats;
			response.nickname = target->user_data->nickname;
		}
		else {
			response.found = false;
		}

		connection.Send(peer, response);
	}


	void Server::Handle(ENetPeer* peer, const std::shared_ptr<SetUserDataMessage>& data)
	{
		tracer::Trace trace{ "::SetUserDataMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);

		pd->user_data->stats.SetUserData(data->key, data->value);

		data->id = pd->id;
		connection.Broadcast(data, peer);
	}

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
	void Server::Handle(ENetPeer* peer, const std::shared_ptr<RequestChatRoomWithUserMessage>& data) {
		tracer::Trace trace{ "::RequestChatRoomWithUserMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);
		peer::ptr target = peer_mapper.Get(data->id);

		RequestChatRoomWithUserMessage response{ data->request_id, data->id };

		if (!target) {
			response.chat_room = nullptr;
			connection.Send(peer, response);
			return;
		}

		response.chat_room = chat_room_manager.CreateChatRoom();

		for (auto& i : { pd, target }) {
			response.chat_room->AddMember(i->id);
			i->chat_rooms.emplace(response.chat_room->GetID(), response.chat_room);
			connection.Send(i->peer, response);
		}
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<RequestChatRoomMessagesMessage>& data) {
		tracer::Trace trace{ "::RequestChatRoomMessagesMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);

		auto chat_room = chat_room_manager.GetChatRoom(data->id);

		ChatRoom::messages_t messages{};
		if (chat_room && chat_room->IsMember(pd->id)) {
			messages = chat_room->GetMessages(data->oldest_message);
		}
		RequestChatRoomMessagesMessage response{ data->request_id, data->id, data->oldest_message, messages };

		connection.Send(peer, response);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<SendToChatRoomMessage>& data) {
		tracer::Trace trace{ "::SendToChatRoomMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);

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

			auto& members = chat_room->GetMembers();
			for (const auto& member : members) {
				peer::ptr member_peer = peer_mapper.Get(member);
				connection.Send(member_peer->peer, notification);
			}
		}
		else {
			connection.Send(peer, SendToChatRoomMessage{ data->request_id, data->id, nullptr });
		}
	}
#endif

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<P2PNetworkPacketMessage>& data) {
		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);
		peer::ptr target_pd{ nullptr };

		if (galaxy::api::GetIDType(data->id) == galaxy::api::IDType::ID_TYPE_LOBBY) {
			auto lobby = lobby_manager.GetLobby(data->id);
			if (lobby) {
				target_pd = peer_mapper.Get(lobby->GetOwner());
			}
		}
		else {
			target_pd = peer_mapper.Get(data->id);
		}

		if (target_pd) {
			data->id = pd->id;
			connection.Send(target_pd->peer, *data);
		}
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<FileShareMessage>& data) {
		tracer::Trace trace{ "::FileShareMessage" };

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
		tracer::Trace trace{ "::FileRequestMessage" };

		REQUIRES_AUTHENTICATION(peer);

		if (data->id != 0) {
			data->data = sfu.ReadShared(data->id);
			data->filename = sfu.GetSharedFileName(data->id).string();
		}
		else if (data->filename.size() != 0) {
			data->data = sfu.ReadShared(data->filename);
			data->id = sfu.GetSharedFileID(data->filename);
		}

		if (data->data.size() == 0) {
			std::cerr << "FileShareMessage::ReadShared FAIL\n";
		}

		connection.Send(peer, data);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<CreateLobbyMessage>& data) {
		tracer::Trace trace{ "::CreateLobbyMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);
		LobbyManager::lobby_t lobby{ nullptr };

		if (pd->lobby == nullptr) {
			lobby = lobby_manager.CreateLobby(pd->id, data->type, data->max_members, data->joinable, data->topology_type);
			pd->lobby = lobby;
		}

		connection.Send(peer, CreateLobbyResponseMessage{ data->request_id, lobby });
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<RequestLobbyListMessage>& data) {
		tracer::Trace trace{ "::RequestLobbyListMessage" };

		REQUIRES_AUTHENTICATION(peer);

		data->lobby_list = lobby_manager.GetLobbies();
		data->error = false;

		connection.Send(peer, data);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<JoinLobbyMessage>& data) {
		tracer::Trace trace{ "::JoinLobbyMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);

		if (pd->lobby) {
			// already in a lobby
			data->result = LOBBY_ENTER_RESULT_ERROR;
			connection.Send(peer, data);
			return;
		}

		auto lobby = lobby_manager.GetLobby(data->lobby_id);
		if (!lobby) {
			data->result = LOBBY_ENTER_RESULT_LOBBY_DOES_NOT_EXIST;
			connection.Send(peer, data);
			return;
		}

		if (lobby->IsFull()) {
			data->result = LOBBY_ENTER_RESULT_LOBBY_IS_FULL;
			connection.Send(peer, data);
			return;
		}

		if (!lobby->AddMember(pd->id)) {
			data->result = LOBBY_ENTER_RESULT_ERROR;
			connection.Send(peer, data);
			return;
		}

		pd->lobby = lobby;
		data->result = LOBBY_ENTER_RESULT_SUCCESS;
		connection.Send(peer, data);

		LobbyMemberStateChangeMessage enter_notification{ lobby->GetID(), pd->id, LOBBY_MEMBER_STATE_CHANGED_ENTERED };

		// hmm should we include the user itself?
		auto members = lobby->GetMembers();
		for (auto& member : members) {
			//if (member != pd->id) {
				auto member_peer = peer_mapper.Get(member);

				connection.Send(member_peer->peer, enter_notification);
			//}
		}
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<LeaveLobbyMessage>& data) {
		tracer::Trace trace{ "::LeaveLobbyMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);

#if (GALAXY_VERSION) > 11240
		data->reason = ILobbyLeftListener::LOBBY_LEAVE_REASON_USER_LEFT;
#endif

		HandleMemberLobbyLeave(peer, false);

		connection.Send(peer, data);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<RequestLobbyDataMessage>& data) {
		tracer::Trace trace{ "::RequestLobbyDataMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);

		auto lobby = lobby_manager.GetLobby(data->lobby_id);
		if (!lobby) {
			data->data = nullptr;
			data->fail_reason = ILobbyDataRetrieveListener::FAILURE_REASON_LOBBY_DOES_NOT_EXIST;
			connection.Send(peer, data);
			return;
		}

		data->data = lobby;

		connection.Send(peer, data);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<SendToLobbyMessage>& data) {
		tracer::Trace trace{ "::SendToLobbyMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);

		auto lobby = lobby_manager.GetLobby(data->lobby_id);
		if (!lobby) {
			return;
		}

		data->message.sender = pd->id;
		data->message.message_id = lobby->SendMsg(data->message.sender, data->message.data);

		if (data->message.message_id != 0) {
			auto members = pd->lobby->GetMembers();
			for (auto& member : members) {
				auto member_peer = peer_mapper.Get(member);
				if (member_peer) {
					connection.Send(member_peer->peer, data);
				}
			}
		}
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyDataMessage>& data) {
		tracer::Trace trace{ "::SetLobbyDataMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);

		auto lobby = lobby_manager.GetLobby(data->lobby_id);
		if (!lobby) {
			data->success = false;
#if (GALAXY_VERSION) > 11240
			data->fail_reason = ILobbyDataUpdateListener::FAILURE_REASON_LOBBY_DOES_NOT_EXIST;
#endif
			connection.Send(peer, data);
			return;
		}

		if (lobby->GetOwner() != pd->id) {
			data->success = false;
#if (GALAXY_VERSION) > 11240
			data->fail_reason = ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED;
#endif
			connection.Send(peer, data);
			return;
		}

		lobby->SetData(data->key.c_str(), data->value.c_str());
		data->success = true;
		connection.Send(peer, data);

		SetLobbyDataMessage notification{ 0, data->lobby_id, data->key, data->value };
		auto members = pd->lobby->GetMembers();
		for (auto& member : members) {
			auto member_peer = peer_mapper.Get(member);
			if (member_peer && (member_peer->peer != peer)) {
				connection.Send(member_peer->peer, notification);
			}
		}
	}

	template<typename T, typename U> bool BoilerplateHandleLobbyDataUpdate(peer::Mapper& peer_mapper, GalaxyNetworkServer& connection, ENetPeer* peer, const T& data, const U& notification, std::function<bool(peer::ptr pd)> func) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		peer::ptr pd = peer_mapper.Get(peer);

#if (GALAXY_VERSION) > 11240
		data->fail_reason = ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED;
#endif

		data->success = false;

		if ((!pd->lobby) ||
			(pd->lobby->GetID() != data->lobby_id) ||
			(pd->lobby->GetOwner() != pd->id)) {
			connection.Send(peer, data);
			return false;
		}

		if (!func(pd)) {
			connection.Send(peer, data);
			return false;
		}

		data->success = true;
		connection.Send(peer, data);

		auto members = pd->lobby->GetMembers();
		for (auto& member : members) {
			auto member_peer = peer_mapper.Get(member);
			if (member_peer && (member_peer->peer != peer)) {
				connection.Send(member_peer->peer, notification);
			}
		}

		return true;
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyJoinableMessage>& data) {
		tracer::Trace trace{ "::SetLobbyJoinableMessage" };

		REQUIRES_AUTHENTICATION(peer);

		SetLobbyJoinableMessage notification{ 0, data->lobby_id, data->joinable };

		BoilerplateHandleLobbyDataUpdate(peer_mapper, connection, peer, data, notification, [&](peer::ptr pd) -> bool {
			pd->lobby->SetJoinable(data->joinable);
			return true;
			});
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyMaxMembersMessage>& data) {
		tracer::Trace trace{ "::SetLobbyMaxMembersMessage" };

		REQUIRES_AUTHENTICATION(peer);

		SetLobbyMaxMembersMessage notification{ 0, data->lobby_id, data->max_members };
		BoilerplateHandleLobbyDataUpdate(peer_mapper, connection, peer, data, notification, [&](peer::ptr pd) -> bool {
			pd->lobby->SetMaxMembers(data->max_members);
			return true;
			});
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyTypeMessage>& data) {
		tracer::Trace trace{ "::SetLobbyTypeMessage" };

		REQUIRES_AUTHENTICATION(peer);

		SetLobbyTypeMessage notification{ 0, data->lobby_id, data->type };
		BoilerplateHandleLobbyDataUpdate(peer_mapper, connection, peer, data, notification, [&](peer::ptr pd) -> bool {
			pd->lobby->SetType(data->type);
			return true;
			});
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyMemberDataMessage>& data) {
		tracer::Trace trace{ "::SetLobbyMemberDataMessage" };

		REQUIRES_AUTHENTICATION(peer);
		peer::ptr pd = peer_mapper.Get(peer);

		auto lobby = lobby_manager.GetLobby(data->lobby_id);
		if (!lobby) {
			data->success = false;
#if (GALAXY_VERSION) > 11240
			data->fail_reason = ILobbyMemberDataUpdateListener::FAILURE_REASON_LOBBY_DOES_NOT_EXIST;
#endif
			connection.Send(peer, data);
			return;
		}

		data->member_id = pd->id;

		if (!lobby->SetMemberData(data->member_id, data->key.c_str(), data->value.c_str())) {
			data->success = false;
#if (GALAXY_VERSION) > 11240
			data->fail_reason = ILobbyMemberDataUpdateListener::FAILURE_REASON_UNDEFINED;
#endif
			connection.Send(peer, data);
			return;
		}

		data->success = true;
		connection.Send(peer, data);

		SetLobbyMemberDataMessage notification{ 0, data->lobby_id, data->member_id, data->key, data->value };
		auto members = pd->lobby->GetMembers();
		for (auto& member : members) {
			auto member_peer = peer_mapper.Get(member);
			if (member_peer && (member_peer->peer != peer)) {
				connection.Send(member_peer->peer, notification);
			}
		}
	}

	bool Server::HandleMemberLobbyLeave(ENetPeer* peer, bool disconnected) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		peer::ptr pd = peer_mapper.Get(peer);

		LobbyManager::lobby_t lobby{ pd->lobby };
		if (!lobby) {
			return false;
		}

		pd->lobby = nullptr;
		lobby->RemoveMember(pd->id);

		if (lobby->GetMemberCount() == 0) {
			lobby_manager.RemoveLobby(lobby->GetID());
			return true;
		}

		bool close{
			(lobby->GetTopology() == LOBBY_TOPOLOGY_TYPE_FCM) ||
			(lobby->GetTopology() == LOBBY_TOPOLOGY_TYPE_STAR)
		};

		LobbyMemberStateChangeMessage leave_notification{ lobby->GetID(), pd->id, (disconnected ? LOBBY_MEMBER_STATE_CHANGED_DISCONNECTED : LOBBY_MEMBER_STATE_CHANGED_LEFT) };
		LeaveLobbyMessage close_message{ 0, lobby->GetID()
#if (GALAXY_VERSION) > 11240
			, ILobbyLeftListener::LOBBY_LEAVE_REASON_LOBBY_CLOSED
#endif
		};

		bool new_owner{ false };
		GalaxyID new_owner_id{ 0 };

		if (lobby->GetOwner() == pd->id) {
			new_owner = true;
			new_owner_id = lobby->ChooseNewOwner();
		}

		LobbyOwnerChangeMessage owner_change_message{ lobby->GetID(), new_owner_id };

		auto members = lobby->GetMembers();
		for (auto& member : members) {
			auto member_peer = peer_mapper.Get(member);

			if (!close && new_owner) {
				connection.Send(member_peer->peer, owner_change_message);
				connection.Send(member_peer->peer, leave_notification);
			}
			else if (close) {
				member_peer->lobby = nullptr;
				connection.Send(member_peer->peer, leave_notification);
				connection.Send(member_peer->peer, close_message);
			}
		}

		if (close) {
			lobby_manager.RemoveLobby(lobby->GetID());
		}

		return true;
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<RichPresenceChangeMessage>& data)
	{
		tracer::Trace trace{ "::RichPresenceChangeMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);

		data->id = pd->id;
		auto& entry = pd->user_data->stats;
		switch (data->action) {
		case RichPresenceChangeMessage::ACTION_SET:
			entry.SetRichPresence(data->key, data->value);
			data->success = true;
			break;

		case RichPresenceChangeMessage::ACTION_DELETE:
			entry.EraseRichPresence(data->key);
			data->success = true;
			break;

		case RichPresenceChangeMessage::ACTION_CLEAR:
			entry.ClearRichPresence();
			data->success = true;
			break;

		case RichPresenceChangeMessage::ACTION_NONE:
			data->success = false;
			break;
		}

		connection.Broadcast(data);
	}
#if GALAXY_BUILD_FEATURE_HAS_ICHAT
	bool Server::HandleMemberChatLeave(ENetPeer* peer) {
		tracer::Trace trace{ "1"};

		peer::ptr pd = peer_mapper.Get(peer);

		bool success = true;

		ChatRoomManager::chatrooms_t chat_rooms_copy = pd->chat_rooms;

		for (auto& entry : chat_rooms_copy) {
			if (!HandleMemberChatLeave(peer, entry.first)) {
				success = false;
			}
		}

		return success;
	}

	bool Server::HandleMemberChatLeave(ENetPeer* peer, galaxy::api::ChatRoomID chat_room_id) {
		tracer::Trace trace{ "2"};

		peer::ptr pd = peer_mapper.Get(peer);

		auto& chat_rooms = pd->chat_rooms;

		auto chat_room_it = chat_rooms.find(chat_room_id);
		if (chat_room_it == chat_rooms.end()) {
			return false;
		}

		auto chat_room = chat_room_it->second;
		chat_rooms.erase(chat_room_id);

		chat_room->RemoveMember(pd->id);

		if (chat_room->GetMemberCount() == 0) {
			chat_room_manager.RemoveChatRoom(chat_room_id);
			return true;
		}

		/*if (chat_room->GetMemberCount() == 1) {
			auto member_peer = peer_mapper.Get(*chat_room->GetMembers().begin());

			// TODO: let member know chatroom is closing
			// A: No mechanism for that? Perhaps because chats are kept saved on the server
			// ^ but we don't care about that
		}
		else {
			auto members = chat_room->GetMembers();
			for (auto& member : members) {
				auto member_peer = peer_mapper.Get(member);

				// TODO: let member know participant has left
				// A: No mechanism for that? Perhaps because chats are kept saved on the server
				// ^ but we don't care about that
			}
		}*/

		return true;
	}
#endif

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<InvitationMessage>& data) {
		tracer::Trace trace{ "::InvitationMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);
		peer::ptr target = peer_mapper.Get(data->user_id);

		if (!target) {
			return;
		}

		data->user_id = pd->id;
		connection.Send(target->peer, data);
	}
}
