#include "Client.hxx"

#include <Networking/Networking.hxx>

namespace universelan::client {
	using namespace galaxy::api;

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<FileShareMessage>& data) {}
	void Client::Handle(ENetPeer* peer, const std::shared_ptr<UserHelloDataMessage>& data){}

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
		challenge.id = interfaces->config->GetApiGalaxyID();

		connection.SendAsync(challenge);
	}

	void Client::Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAcceptedMessage>& data)
	{
		std::cout << "Connection accepted by server" << std::endl;

		UserHelloDataMessage udm{ };

		udm.asuc = interfaces->config->GetASUC();

		connection.SendAsync(udm);
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
}