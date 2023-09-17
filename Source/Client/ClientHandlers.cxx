#include "Client.hxx"

#include <Networking/Networking.hxx>

#include <iostream>

namespace universelan::client {
	using namespace galaxy::api;

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<FileShareMessage>& data) {}
	void Client::Handle(ENetPeer* peer, const std::shared_ptr<UserHelloDataMessage>& data) {}
	void Client::Handle(ENetPeer* peer, const std::shared_ptr<CreateLobbyMessage>& data) {}

	// Handlers:
	void Client::Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data)
	{
		tracer::Trace trace{ "::EventConnect"};

		std::cout << "Peer connected: " 
			<< std::hex <<peer->address.host << ":" << std::dec << peer->address.port << std::endl;

		interfaces->utils->ConnectionStateChangeReceived(true);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data)
	{
		tracer::Trace trace{ "::EventDisconnect" };

		std::cout << "Peer disconnected: " 
			<< std::hex << peer->address.host << ":" << std::dec << peer->address.port << std::endl;

		interfaces->utils->ConnectionStateChangeReceived(false);

		connection.Reconnect();
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<KeyChallengeMessage>& data)
	{
		tracer::Trace trace{ "::KeyChallengeMessage" };

		auto& config = interfaces->config;
		const uint64_t key = const_hash64(config->GetAuthenticationKey());

		KeyChallengeMessage message{ KeyChallengeMessage{ config->GetApiGalaxyID() }.response(key, data->encrypted) };
		
		std::cout << "Replying to challenge with ID " << message.id.ToUint64() << "\n";

		connection.SendAsync(message);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAcceptedMessage>& data)
	{
		tracer::Trace trace{ "::ConnectionAcceptedMessage" };

		std::cout << "Connection accepted by server" << std::endl;

		connection.SendAsync(UserHelloDataMessage { 
			interfaces->config->GetApiGalaxyID(), 
			interfaces->config->GetLocalUserData()->stats,
			interfaces->config->GetCustomPersonaName()
		});
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestSpecificUserDataMessage>& data)
	{
		tracer::Trace trace{ "::RequestSpecificUserDataMessage" };

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
		tracer::Trace trace{ "::RequestChatRoomWithUserMessage" };

		interfaces->chat->RequestChatRoomWithUserProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestChatRoomMessagesMessage>& data) {
		tracer::Trace trace{ "::RequestChatRoomMessagesMessage" };

		interfaces->chat->RequestChatRoomMessagesProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SendToChatRoomMessage>& data) {
		tracer::Trace trace{ "::SendToChatRoomMessage" };

		interfaces->chat->SendChatRoomMessageProcessed(data);
	}
#endif

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<P2PNetworkPacketMessage>& data) {

		interfaces->networking->AddPacket(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<FileShareResponseMessage>& data) {
		tracer::Trace trace{ "::FileShareResponseMessage" };

		interfaces->storage->FileUploaded(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<FileRequestMessage>& data) {
		tracer::Trace trace{ "::FileRequestMessage" };

		interfaces->storage->FileDownloaded(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<CreateLobbyResponseMessage>& data) {
		tracer::Trace trace{ "::CreateLobbyResponseMessage" };

		interfaces->matchmaking->CreateLobbyProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestLobbyListMessage>& data) {
		tracer::Trace trace{ "::RequestLobbyListMessage" };

		interfaces->matchmaking->RequestLobbyListProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<JoinLobbyMessage>& data) {
		tracer::Trace trace{ "::JoinLobbyMessage" };

		interfaces->matchmaking->JoinLobbyProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<LeaveLobbyMessage>& data) {
		tracer::Trace trace{ "::LeaveLobbyMessage" };

		interfaces->matchmaking->LeaveLobbyProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestLobbyDataMessage>& data) {
		tracer::Trace trace{ "::RequestLobbyDataMessage" };

		interfaces->matchmaking->RequestLobbyDataProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SendToLobbyMessage>& data) {
		tracer::Trace trace{ "::SendToLobbyMessage" };

		interfaces->matchmaking->SendLobbyMessageProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyDataMessage>& data) {
		tracer::Trace trace{ "::SetLobbyDataMessage" };

		interfaces->matchmaking->SetLobbyDataProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyJoinableMessage>& data) {
		tracer::Trace trace{ "::SetLobbyJoinableMessage" };

		interfaces->matchmaking->SetLobbyJoinableProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyMaxMembersMessage>& data) {
		tracer::Trace trace{ "::SetLobbyMaxMembersMessage" };

		interfaces->matchmaking->SetLobbyMaxMembersProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyMemberDataMessage>& data) {
		tracer::Trace trace{ "::SetLobbyMemberDataMessage" };

		interfaces->matchmaking->SetLobbyMemberDataProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyTypeMessage>& data) {
		tracer::Trace trace{ "::SetLobbyTypeMessage" };

		interfaces->matchmaking->SetLobbyTypeProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<LobbyMemberStateChangeMessage>& data) {
		tracer::Trace trace{ "::LobbyMemberStateChangeMessage" };

		interfaces->matchmaking->LobbyMemberStateChange(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<LobbyOwnerChangeMessage>& data) {
		tracer::Trace trace{ "::LobbyOwnerChangeMessage" };

		interfaces->matchmaking->LobbyOwnerChange(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<OnlineStatusChangeMessage>& data)
	{
		tracer::Trace trace{ "::OnlineStatusChangeMessage" };

		interfaces->user->OnlineUserStateChange(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetUserDataMessage>& data)
	{
		tracer::Trace trace{ "::SetUserDataMessage" };

		interfaces->user->SetUserDataMessageReceived(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RichPresenceChangeMessage>& data)
	{
		tracer::Trace trace{ "::RichPresenceChangeMessage" };

		interfaces->friends->RichPresenceChangeMessageProcessed(data);
	}
}
