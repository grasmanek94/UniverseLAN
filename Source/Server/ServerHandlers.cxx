#include "Server.hxx"

#include "Peer.hxx"

#include <Networking/Networking.hxx>
#include <Tracer.hxx>

#include <format>
#include <string>

#define REQUIRES_AUTHENTICATION(peer) {if(!KickUnauthenticated(peer)) { return; }}

namespace universelan::server {
	using namespace galaxy::api;

	namespace {
		std::string bytes_to_hex(const void* data, uint32_t dataSize) {
			std::string hex;
			for (uint32_t i = 0; i < dataSize; ++i) {
				hex += std::format("{:02x}", ((const unsigned char*)data)[i]);
			}
			return hex;
		}
	}

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
			HandleMemberAllLobbiesLeave(peer, true);
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
		tracer::Trace trace{ "::KeyChallengeMessage" };

		peer::ptr pd = peer_mapper.Get(peer);
		if (pd->challenge.completed) { return; }

		if (pd->challenge.Validate(*data) && data->id.IsValid()) {
			auto entry = user_data.emplace(data->id, std::make_shared<GalaxyUserData>(data->id));
			if (entry.second && pd->link(data->id)) {
				tracer::Trace validated{ "::challenge.Validate" };

				pd->user_data = entry.first->second;

				unauthenticated_peers.erase(peer);
				connection.Send(peer, ConnectionAcceptedMessage{});
				connection.Broadcast(OnlineStatusChangeMessage{ pd->id, true }, peer);

				for (auto& online_peer : peer_mapper.connected_peers) {
					if (peer != online_peer) {
						peer::ptr online_member = peer_mapper.Get(online_peer);
						if (online_member->id.IsValid()) {
							connection.Send(peer, OnlineStatusChangeMessage{ online_member->id, true });
						}
					}
				}

				std::cout << "Peer(" << peer->address.host << ":" << peer->address.port << ") KeyChallengeMessage ACCEPT" << std::endl;
				return;
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

			auto message = chat_room->AddMessage(pd->id,
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
				data->message->GetType(),
#endif
				data->message->GetContents());

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

	// Message *from* a *server host*
	void Server::Handle(ENetPeer* peer, const std::shared_ptr<P2PServerNetworkPacketMessage>& server_data) {
		REQUIRES_AUTHENTICATION(peer);

		tracer::Trace trace{ "::P2PServerNetworkPacketMessage", __FUNCTION__, tracer::Trace::INETWORKING | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto& data = server_data->packet;

		if (!data) {
			return;
		}

		if (trace.has_flags(tracer::Trace::NETWORK_P2P_CONTENTS)) {
			trace.write_all(std::format("data_contents: {}", bytes_to_hex(data->data.data(), (uint32_t)data->data.size())));
		}

		ENetPacketFlag flag{};

		switch (data->send_type) {
		case P2P_SEND_RELIABLE:
#if GALAXY_BUILD_FEATURE_HAS_P2P_SEND_IMMEDIATE
		case P2P_SEND_RELIABLE_IMMEDIATE:
#endif
			flag = ENET_PACKET_FLAG_RELIABLE;
			break;

		case P2P_SEND_UNRELIABLE:
#if GALAXY_BUILD_FEATURE_HAS_P2P_SEND_IMMEDIATE
		case P2P_SEND_UNRELIABLE_IMMEDIATE:
#endif
			// no unreliable flag?
			break;
		}

		peer::ptr pd = peer_mapper.Get(peer);
		P2PNetworkPacketMessage data_to_send{ *data };

		for (auto& lobby_iter : pd->lobbies) {
			auto& lobby = lobby_iter.second;
			if (lobby && lobby->GetOwner() == pd->id && lobby->GetMemberCount() >= 2) {
				if (galaxy::api::GetIDType(data->id) == galaxy::api::IDType::ID_TYPE_LOBBY) {
					if (data->id == lobby->GetID()) {
						// send to all lobby members "as lobby" (id is already lobby so just send as-is)
						for (const auto& member : lobby->GetMembers()) {
							peer::ptr target_pd = peer_mapper.Get(member);
							if (target_pd) {
								connection.Send(target_pd->peer, data_to_send, flag);
							}
						}
					}
				}
				else if (lobby->IsMember(data->id)) {
					peer::ptr target_pd = peer_mapper.Get(data->id);
					if (target_pd != nullptr) {
						// send "as lobby" (modify id to lobby)
						data_to_send.id = lobby->GetID();
						connection.Send(target_pd->peer, data_to_send, flag);
					}
					else if (trace.has_flags(tracer::Trace::DETAILED)) {
						trace.write_all("target_pd is nullptr?!");
					}
				}
			}
		}
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<P2PNetworkPacketMessage>& data) {
		REQUIRES_AUTHENTICATION(peer);

		tracer::Trace trace{ "::P2PNetworkPacketMessage", __FUNCTION__, tracer::Trace::INETWORKING | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::NETWORK_P2P_CONTENTS)) {
			trace.write_all(std::format("data_contents: {}", bytes_to_hex(data->data.data(), (uint32_t)data->data.size())));
		}

		ENetPacketFlag flag{};

		switch (data->send_type) {
		case P2P_SEND_RELIABLE:
#if GALAXY_BUILD_FEATURE_HAS_P2P_SEND_IMMEDIATE
		case P2P_SEND_RELIABLE_IMMEDIATE:
#endif
			flag = ENET_PACKET_FLAG_RELIABLE;
			break;

		case P2P_SEND_UNRELIABLE:
#if GALAXY_BUILD_FEATURE_HAS_P2P_SEND_IMMEDIATE
		case P2P_SEND_UNRELIABLE_IMMEDIATE:
#endif
			// no unreliable flag?
			break;
		}

		peer::ptr pd = peer_mapper.Get(peer);
		peer::ptr target_pd{ nullptr };

		// Send message TO lobby
		if (galaxy::api::GetIDType(data->id) == galaxy::api::IDType::ID_TYPE_LOBBY) {
			auto lobby = lobby_manager.GetLobby(data->id);
			if (lobby) {
				target_pd = peer_mapper.Get(lobby->GetOwner());

				if (target_pd) {
					if (target_pd->id == pd->id) {
						// broadcast to all members, lobby owner sent to own lobby
						// now question, should we use the lobby id or the member id?
						// Uncomment for host member id instead of lobby id:
						// data->id = pd->id;

						for (const auto& member : lobby->GetMembers()) {
							peer::ptr target_pd = peer_mapper.Get(member);
							if (target_pd) {
								connection.Send(target_pd->peer, *data, flag);
							}
						}
					}
					else {
#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
						// some member sent a message to the lobby host
						data->id = pd->id;
						connection.Send(target_pd->peer, P2PServerNetworkPacketMessage{ *data }, flag);
#endif
					}
				}
			}
			return;
		}

		target_pd = peer_mapper.Get(data->id);

		if (!target_pd) {
			return;
		}

		// send normal packet from peer to peer
		data->id = pd->id;
		connection.Send(target_pd->peer, *data, flag);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<FileShareMessage>& data) {
		tracer::Trace trace{ "::FileShareMessage" };

		REQUIRES_AUTHENTICATION(peer);

		FileShareResponseMessage fsrm{ data->request_id, ++shared_file_counter, data->filename };
		auto var = sfu.Open(sfu.shared, shared_file_counter_file.c_str(), std::ios::out | std::ios::trunc);
		var << shared_file_counter;

		auto entry = sfu.shared->create_shared(fsrm.filename, fsrm.id);
		if (!entry) {
			std::cerr << "FileShareMessage::create_shared FAIL\n";
		}
		else if (!entry->write(data->data)) {
			std::cerr << "FileShareMessage::write FAIL\n";
		}

		connection.Send(peer, fsrm);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<FileRequestMessage>& data) {
		tracer::Trace trace{ "::FileRequestMessage" };

		REQUIRES_AUTHENTICATION(peer);

		bool read = false;
		if (data->id != 0) {
			auto entry = sfu.shared->get(data->id);
			if (entry) {
				data->data = entry->read();
				data->filename = entry->get_path().string();
				read = true;
			}
		}
		if (!read && data->filename.size() != 0) {
			auto entry = sfu.shared->get(data->filename);
			if (entry) {
				data->data = entry->read();
				data->filename = entry->get_path().string();
				read = true;
			}
		}

		if (!read) {
			std::cerr << "FileShareMessage::Read FAIL\n";
		}

		connection.Send(peer, data);
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<CreateLobbyMessage>& data) {
		tracer::Trace trace{ "::CreateLobbyMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);
		LobbyManager::lobby_t lobby{ nullptr };

		lobby = lobby_manager.CreateLobby(pd->id, data->type, data->max_members, data->joinable, data->topology_type);

		if (pd->AddLobby(lobby)) {
			connection.Send(peer, CreateLobbyResponseMessage{ data->request_id, lobby });
		}
		else {
			connection.Send(peer, CreateLobbyResponseMessage{ data->request_id, nullptr });
		}
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

		// !Apparently it's OK to be in multiple lobbies
		//if (pd->lobby) {
		//	// already in a lobby
		//	data->result = LOBBY_ENTER_RESULT_ERROR;
		//	connection.Send(peer, data);
		//	return;
		//}

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

		if (!pd->AddLobby(lobby)) {
			data->result = LOBBY_ENTER_RESULT_ERROR;
			connection.Send(peer, data);
			return;
		}

		data->result = LOBBY_ENTER_RESULT_SUCCESS;
		connection.Send(peer, data);

		LobbyMemberStateChangeMessage enter_notification{ lobby->GetID(), pd->id, LOBBY_MEMBER_STATE_CHANGED_ENTERED };

		// hmm should we include the user itself?
		auto members = lobby->GetMembers();
		for (auto& member : members) {
			if (member != pd->id) {
				auto member_peer = peer_mapper.Get(member);

				connection.Send(member_peer->peer, enter_notification);
			}
		}
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<LeaveLobbyMessage>& data) {
		tracer::Trace trace{ "::LeaveLobbyMessage" };

		REQUIRES_AUTHENTICATION(peer);

		peer::ptr pd = peer_mapper.Get(peer);

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		data->reason = ILobbyLeftListener::LOBBY_LEAVE_REASON_USER_LEFT;
#else
		data->reason = false;
#endif

		HandleMemberLobbyLeave(peer, data->lobby_id, false);

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
		if (!lobby || !lobby->IsMember(pd->id)) {
			return;
		}

		data->message.sender = pd->id;
		data->message.message_id = lobby->SendMsg(data->message.sender, data->message.data);

		if (data->message.message_id != 0) {
			auto members = lobby->GetMembers();
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
		auto members = lobby->GetMembers();
		for (auto& member : members) {
			auto member_peer = peer_mapper.Get(member);
			if (member_peer && (member_peer->peer != peer)) {
				connection.Send(member_peer->peer, notification);
			}
		}
	}

	template<typename T, typename U> bool BoilerplateHandleLobbyDataUpdate(peer::Mapper& peer_mapper, LobbyManager& lobby_manager, GalaxyNetworkServer& connection, ENetPeer* peer, const T& data, const U& notification, std::function<bool(peer::ptr pd, LobbyManager::lobby_t& lobby)> func) {
		tracer::Trace trace{ nullptr, __FUNCTION__ };

		peer::ptr pd = peer_mapper.Get(peer);

#if (GALAXY_VERSION) > 11240
		data->fail_reason = ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED;
#endif

		data->success = false;
		auto lobby = lobby_manager.GetLobby(data->lobby_id);

		if (!lobby || !lobby->IsMember(pd->id) || (lobby->GetOwner() != pd->id)) {
			connection.Send(peer, data);
			return false;
		}

		if (!func(pd, lobby)) {
			connection.Send(peer, data);
			return false;
		}

		data->success = true;
		connection.Send(peer, data);

		auto members = lobby->GetMembers();
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

		BoilerplateHandleLobbyDataUpdate(peer_mapper, lobby_manager, connection, peer, data, notification, [&](peer::ptr pd, LobbyManager::lobby_t& lobby) -> bool {
			lobby->SetJoinable(data->joinable);
			return true;
			});
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyMaxMembersMessage>& data) {
		tracer::Trace trace{ "::SetLobbyMaxMembersMessage" };

		REQUIRES_AUTHENTICATION(peer);

		SetLobbyMaxMembersMessage notification{ 0, data->lobby_id, data->max_members };
		BoilerplateHandleLobbyDataUpdate(peer_mapper, lobby_manager, connection, peer, data, notification, [&](peer::ptr pd, LobbyManager::lobby_t& lobby) -> bool {
			lobby->SetMaxMembers(data->max_members);
			return true;
			});
	}

	void Server::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyTypeMessage>& data) {
		tracer::Trace trace{ "::SetLobbyTypeMessage" };

		REQUIRES_AUTHENTICATION(peer);

		SetLobbyTypeMessage notification{ 0, data->lobby_id, data->type };
		BoilerplateHandleLobbyDataUpdate(peer_mapper, lobby_manager, connection, peer, data, notification, [&](peer::ptr pd, LobbyManager::lobby_t& lobby) -> bool {
			lobby->SetType(data->type);
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
		auto members = lobby->GetMembers();
		for (auto& member : members) {
			auto member_peer = peer_mapper.Get(member);
			if (member_peer && (member_peer->peer != peer)) {
				connection.Send(member_peer->peer, notification);
			}
		}
	}

	bool Server::HandleMemberLobbyLeave(ENetPeer* peer, const GalaxyID& lobby_id, bool disconnected) {
		tracer::Trace trace{ nullptr, __FUNCTION__ };

		peer::ptr pd = peer_mapper.Get(peer);

		auto lobby = pd->GetLobby(lobby_id);
		if (!lobby) {
			return false;
		}

		pd->RemoveLobby(lobby_id);
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
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
			, ILobbyLeftListener::LOBBY_LEAVE_REASON_LOBBY_CLOSED
#else
			, false
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
				member_peer->RemoveLobby(lobby);
				connection.Send(member_peer->peer, leave_notification);
				connection.Send(member_peer->peer, close_message);
			}
		}

		if (close) {
			lobby_manager.RemoveLobby(lobby->GetID());
		}

		return true;
	}

	bool Server::HandleMemberAllLobbiesLeave(ENetPeer* peer, bool disconnected) {
		tracer::Trace trace{ nullptr, __FUNCTION__ };

		peer::ptr pd = peer_mapper.Get(peer);

		bool left_some = false;
		while (pd->lobbies.size()) {
			if (HandleMemberLobbyLeave(peer, pd->lobbies.begin()->first, disconnected)) {
				left_some = true;
			}
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
		tracer::Trace trace{ "1" };

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
		tracer::Trace trace{ "2" };

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
