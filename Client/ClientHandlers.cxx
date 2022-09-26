#include "Client.hxx"

#include <Networking/Networking.hxx>

namespace universelan::client {
	using namespace galaxy::api;

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<FileShareMessage>& data) {}
	void Client::Handle(ENetPeer* peer, const std::shared_ptr<UserHelloDataMessage>& data) {}
	void Client::Handle(ENetPeer* peer, const std::shared_ptr<CreateLobbyMessage>& data) {}

	// Handlers:
	void Client::Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data)
	{
		tracer::Trace trace{ __FUNCTION__"::EventConnect"};

		std::cout << "Peer connected: " << peer->address.host << ":" << peer->address.port << std::endl;
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data)
	{
		tracer::Trace trace{ __FUNCTION__"::EventDisconnect" };

		std::cout << "Peer disconnected: " << peer->address.host << ":" << peer->address.port << std::endl;

		connection.Reconnect();
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<KeyChallengeMessage>& data)
	{
		tracer::Trace trace{ __FUNCTION__"::KeyChallengeMessage" };

		auto& config = interfaces->config;
		const uint64_t key = const_hash64(config->GetAuthenticationKey());

		KeyChallengeMessage message{ KeyChallengeMessage{ config->GetApiGalaxyID() }.response(key, data->encrypted) };
		
		std::cout << "Replying to challenge with ID " << message.id.ToUint64() << "\n";

		connection.SendAsync(message);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAcceptedMessage>& data)
	{
		tracer::Trace trace{ __FUNCTION__"::ConnectionAcceptedMessage" };

		std::cout << "Connection accepted by server" << std::endl;

		connection.SendAsync(UserHelloDataMessage{ interfaces->config->GetASUC() });
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestSpecificUserDataMessage>& data)
	{
		tracer::Trace trace{ __FUNCTION__"::RequestSpecificUserDataMessage" };

		switch (data->type) {
		case RequestSpecificUserDataMessage::RequestTypeUserData:
			interfaces->user->SpecificUserDataRequestProcessed(data);
			break;

		case RequestSpecificUserDataMessage::RequestTypeAchievementsAndStats:
			interfaces->stats->SpecificUserStatsAndAchievementsRequestProcessed(data);
			break;
		}
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestChatRoomWithUserMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::RequestChatRoomWithUserMessage" };

		interfaces->chat->RequestChatRoomWithUserProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestChatRoomMessagesMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::RequestChatRoomMessagesMessage" };

		interfaces->chat->RequestChatRoomMessagesProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SendToChatRoomMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::SendToChatRoomMessage" };

		interfaces->chat->SendChatRoomMessageProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<P2PNetworkPacketMessage>& data) {

		interfaces->networking->AddPacket(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<FileShareResponseMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::FileShareResponseMessage" };

		interfaces->storage->FileUploaded(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<FileRequestMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::FileRequestMessage" };

		interfaces->storage->FileDownloaded(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<CreateLobbyResponseMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::CreateLobbyResponseMessage" };

		interfaces->matchmaking->CreateLobbyProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestLobbyListMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::RequestLobbyListMessage" };

		interfaces->matchmaking->RequestLobbyListProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<JoinLobbyMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::JoinLobbyMessage" };

		interfaces->matchmaking->JoinLobbyProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<LeaveLobbyMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::LeaveLobbyMessage" };

		interfaces->matchmaking->LeaveLobbyProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestLobbyDataMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::RequestLobbyDataMessage" };

		interfaces->matchmaking->RequestLobbyDataProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SendToLobbyMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::SendToLobbyMessage" };

		interfaces->matchmaking->SendLobbyMessageProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyDataMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::SetLobbyDataMessage" };

		interfaces->matchmaking->SetLobbyDataProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyJoinableMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::SetLobbyJoinableMessage" };

		interfaces->matchmaking->SetLobbyJoinableProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyMaxMembersMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::SetLobbyMaxMembersMessage" };

		interfaces->matchmaking->SetLobbyMaxMembersProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyMemberDataMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::SetLobbyMemberDataMessage" };

		interfaces->matchmaking->SetLobbyMemberDataProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyTypeMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::SetLobbyTypeMessage" };

		interfaces->matchmaking->SetLobbyTypeProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<LobbyMemberStateChangeMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::LobbyMemberStateChangeMessage" };

		interfaces->matchmaking->LobbyMemberStateChange(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<LobbyOwnerChangeMessage>& data) {
		tracer::Trace trace{ __FUNCTION__"::LobbyOwnerChangeMessage" };

		interfaces->matchmaking->LobbyOwnerChange(data);
	}
}
