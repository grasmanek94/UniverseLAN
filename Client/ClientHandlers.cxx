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
		std::cout << "Peer connected: " << peer->address.host << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data)
	{
		std::cout << "Peer disconnected: " << peer->address.host << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;

		connection.Reconnect();
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<KeyChallengeMessage>& data)
	{
		auto& config = interfaces->config;
		const uint64_t key = const_hash64(config->GetAuthenticationKey());

		connection.SendAsync(
			KeyChallengeMessage{ config->GetApiGalaxyID() }.response(key, data->encrypted)
		);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAcceptedMessage>& data)
	{
		std::cout << "Connection accepted by server" << std::endl;

		connection.SendAsync(UserHelloDataMessage{ interfaces->config->GetASUC() });
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestSpecificUserDataMessage>& data)
	{
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
		interfaces->chat->RequestChatRoomWithUserProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestChatRoomMessagesMessage>& data) {
		interfaces->chat->RequestChatRoomMessagesProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SendToChatRoomMessage>& data) {
		interfaces->chat->SendChatRoomMessageProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<P2PNetworkPacketMessage>& data) {
		interfaces->networking->AddPacket(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<FileShareResponseMessage>& data) {
		interfaces->storage->FileUploaded(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<FileRequestMessage>& data) {
		interfaces->storage->FileDownloaded(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<CreateLobbyResponseMessage>& data) {
		interfaces->matchmaking->CreateLobbyProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestLobbyListMessage>& data) {
		interfaces->matchmaking->RequestLobbyListProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<JoinLobbyMessage>& data) {
		interfaces->matchmaking->JoinLobbyProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<LeaveLobbyMessage>& data) {
		interfaces->matchmaking->LeaveLobbyProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<RequestLobbyDataMessage>& data) {
		interfaces->matchmaking->RequestLobbyDataProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SendToLobbyMessage>& data) {
		interfaces->matchmaking->SendLobbyMessageProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyDataMessage>& data) {
		interfaces->matchmaking->SetLobbyDataProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyJoinableMessage>& data) {
		interfaces->matchmaking->SetLobbyJoinableProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyMaxMembersMessage>& data) {
		interfaces->matchmaking->SetLobbyMaxMembersProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyMemberDataMessage>& data) {
		interfaces->matchmaking->SetLobbyMemberDataProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<SetLobbyTypeMessage>& data) {
		interfaces->matchmaking->SetLobbyTypeProcessed(data);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<LobbyMemberStateChangeMessage>& data) {

	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<LobbyOwnerChangeMessage>& data) {

	}

}
