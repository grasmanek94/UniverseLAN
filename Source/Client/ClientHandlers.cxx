#include "Client.hxx"

#include <Networking/Networking.hxx>

#include <iostream>
#include <string>

namespace universelan::client {
	using namespace galaxy::api;

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<FileShareMessage>& data) {} // For server only, client uses FileShareResponseMessage
	void Client::Handle(ENetPeer* peer, const std::shared_ptr<UserHelloDataMessage>& data) {} // For server only
	void Client::Handle(ENetPeer* peer, const std::shared_ptr<CreateLobbyMessage>& data) {} // For server only, client uses CreateLobbyResponseMessage

	namespace {
		void client_log(const universelan::client::InterfaceInstances* const interfaces, tracer::Trace& trace, const std::string& what) {
			if (!interfaces->config->ShouldTraceToConsole()) {
				std::cout << what << '\n';
			}

			if (trace.has_flags(tracer::Trace::DETAILED)) {
				trace.write_all(what);
			}
		}
	}

	// Handlers:
	void Client::Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data)
	{
		tracer::Trace trace{ "::EventConnect", tracer::Trace::NETCLIENT };

		client_log(interfaces, trace, std::format("Peer connected: {:08x}:{}", peer->address.host, peer->address.port));

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
		interfaces->utils->ConnectionStateChangeReceived(true);
#endif
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data)
	{
		tracer::Trace trace{ "::EventDisconnect", tracer::Trace::NETCLIENT };

		client_log(interfaces, trace, std::format("Peer disconnected: {:08x}:{}", peer->address.host, peer->address.port));

#if GALAXY_BUILD_FEATURE_HAS_IUTILS
		interfaces->utils->ConnectionStateChangeReceived(false);
#endif

		connection.Reconnect();
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<KeyChallengeMessage>& data)
	{
		tracer::Trace trace{ "::KeyChallengeMessage", tracer::Trace::NETCLIENT };

		auto& config = interfaces->config;
		const uint64_t key = const_hash64(config->GetAuthenticationKey());

		KeyChallengeMessage message{ KeyChallengeMessage{ config->GetApiGalaxyID() }.response(key, data->encrypted) };

		client_log(interfaces, trace, std::format("Replying to challenge with ID {}", message.id.ToUint64()));

		connection.SendAsync(message);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAcceptedMessage>& data)
	{
		tracer::Trace trace{ "::ConnectionAcceptedMessage", tracer::Trace::NETCLIENT };

		client_log(interfaces, trace, "Connection accepted by server");

		connection.SendAsync(UserHelloDataMessage{
			interfaces->config->GetApiGalaxyID(),
			interfaces->config->GetLocalUserData()->stats,
			interfaces->config->GetCustomPersonaName()
			});
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestSpecificUserDataMessage>& data)
	{
		tracer::Trace trace{ "::RequestSpecificUserDataMessage", tracer::Trace::NETCLIENT | tracer::Trace::HIGH_FREQUENCY_CALLS };

		switch (data->type) {
		case RequestSpecificUserDataMessage::RequestTypeUserData:
			interfaces->user->SpecificUserDataRequestProcessed(data);
			break;

		case RequestSpecificUserDataMessage::RequestTypeAchievementsAndStats:
			interfaces->stats->SpecificUserStatsAndAchievementsRequestProcessed(data);
			break;

		case RequestSpecificUserDataMessage::RequestTypePlayTime:
			interfaces->stats->RequestUserTimePlayedProcessed(data);
			break;

		case RequestSpecificUserDataMessage::RequestTypeFriends:
			interfaces->friends->RequestUserInformationProcessed(data);
			break;

		case RequestSpecificUserDataMessage::RequestTypeRichPresence:
			interfaces->friends->RequestRichPresenceProcessed(data);
			break;
		}
	}

#if GALAXY_BUILD_FEATURE_HAS_ICHAT
	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestChatRoomWithUserMessage>& data) {
		tracer::Trace trace{ "::RequestChatRoomWithUserMessage", tracer::Trace::NETCLIENT };

		interfaces->chat->RequestChatRoomWithUserProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestChatRoomMessagesMessage>& data) {
		tracer::Trace trace{ "::RequestChatRoomMessagesMessage", tracer::Trace::NETCLIENT | tracer::Trace::HIGH_FREQUENCY_CALLS };

		interfaces->chat->RequestChatRoomMessagesProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SendToChatRoomMessage>& data) {
		tracer::Trace trace{ "::SendToChatRoomMessage", tracer::Trace::NETCLIENT };

		interfaces->chat->SendChatRoomMessageProcessed(data);
	}
#endif

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<P2PNetworkPacketMessage>& data) {
		// This is too high frequency in my opinion to trace

		interfaces->networking->AddPacket(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<FileShareResponseMessage>& data) {
		tracer::Trace trace{ "::FileShareResponseMessage", tracer::Trace::NETCLIENT };

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
		interfaces->storage->FileUploaded(data);
#endif
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<FileRequestMessage>& data) {
		tracer::Trace trace{ "::FileRequestMessage", tracer::Trace::NETCLIENT };

#if GALAXY_BUILD_FEATURE_HAS_ISTORAGE
		interfaces->storage->FileDownloaded(data);
#endif
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<CreateLobbyResponseMessage>& data) {
		tracer::Trace trace{ "::CreateLobbyResponseMessage", tracer::Trace::NETCLIENT };

		interfaces->matchmaking->CreateLobbyProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestLobbyListMessage>& data) {
		tracer::Trace trace{ "::RequestLobbyListMessage", tracer::Trace::NETCLIENT };

		interfaces->matchmaking->RequestLobbyListProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<JoinLobbyMessage>& data) {
		tracer::Trace trace{ "::JoinLobbyMessage", tracer::Trace::NETCLIENT };

		interfaces->matchmaking->JoinLobbyProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<LeaveLobbyMessage>& data) {
		tracer::Trace trace{ "::LeaveLobbyMessage", tracer::Trace::NETCLIENT };

		interfaces->matchmaking->LeaveLobbyProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestLobbyDataMessage>& data) {
		tracer::Trace trace{ "::RequestLobbyDataMessage", tracer::Trace::NETCLIENT | tracer::Trace::HIGH_FREQUENCY_CALLS };

		interfaces->matchmaking->RequestLobbyDataProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SendToLobbyMessage>& data) {
		tracer::Trace trace{ "::SendToLobbyMessage", tracer::Trace::NETCLIENT | tracer::Trace::HIGH_FREQUENCY_CALLS };

		interfaces->matchmaking->SendLobbyMessageProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyDataMessage>& data) {
		tracer::Trace trace{ "::SetLobbyDataMessage", tracer::Trace::NETCLIENT | tracer::Trace::HIGH_FREQUENCY_CALLS };

		interfaces->matchmaking->SetLobbyDataProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyJoinableMessage>& data) {
		tracer::Trace trace{ "::SetLobbyJoinableMessage", tracer::Trace::NETCLIENT };

		interfaces->matchmaking->SetLobbyJoinableProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyMaxMembersMessage>& data) {
		tracer::Trace trace{ "::SetLobbyMaxMembersMessage", tracer::Trace::NETCLIENT | tracer::Trace::HIGH_FREQUENCY_CALLS };

		interfaces->matchmaking->SetLobbyMaxMembersProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyMemberDataMessage>& data) {
		tracer::Trace trace{ "::SetLobbyMemberDataMessage", tracer::Trace::NETCLIENT | tracer::Trace::HIGH_FREQUENCY_CALLS };

		interfaces->matchmaking->SetLobbyMemberDataProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyTypeMessage>& data) {
		tracer::Trace trace{ "::SetLobbyTypeMessage", tracer::Trace::NETCLIENT };

		interfaces->matchmaking->SetLobbyTypeProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<LobbyMemberStateChangeMessage>& data) {
		tracer::Trace trace{ "::LobbyMemberStateChangeMessage", tracer::Trace::NETCLIENT };

		interfaces->matchmaking->LobbyMemberStateChange(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<LobbyOwnerChangeMessage>& data) {
		tracer::Trace trace{ "::LobbyOwnerChangeMessage", tracer::Trace::NETCLIENT };

		interfaces->matchmaking->LobbyOwnerChange(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<OnlineStatusChangeMessage>& data)
	{
		tracer::Trace trace{ "::OnlineStatusChangeMessage", tracer::Trace::NETCLIENT };

		interfaces->user->OnlineUserStateChange(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetUserDataMessage>& data)
	{
		tracer::Trace trace{ "::SetUserDataMessage", tracer::Trace::NETCLIENT | tracer::Trace::HIGH_FREQUENCY_CALLS };

		interfaces->user->SetUserDataMessageReceived(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RichPresenceChangeMessage>& data)
	{
		tracer::Trace trace{ "::RichPresenceChangeMessage", tracer::Trace::NETCLIENT };

		interfaces->friends->RichPresenceChangeMessageProcessed(data);
	}
}
