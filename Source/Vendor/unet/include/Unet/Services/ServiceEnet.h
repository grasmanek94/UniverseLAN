#pragma once

#include <Unet_common.h>
#include <Unet/Service.h>
#include <Unet/Context.h>

#include <enet/enet.h>

// Windows sucks
#if defined(GetUserName)
#undef GetUserName
#endif

namespace Unet
{
	struct EnetPacket
	{
		ENetPacket* Packet;
		ENetPeer* Peer;
	};

	class ServiceEnet : public Service
	{
	private:
		ENetHost* m_host = nullptr;

		ENetPeer* m_peerHost = nullptr;
		std::vector<ENetPeer*> m_peers;

		std::vector<std::queue<EnetPacket>> m_channels;

		MultiCallback<LobbyJoinResult>::ServiceRequest* m_requestLobbyJoin = nullptr;
		MultiCallback<LobbyLeftResult>::ServiceRequest* m_requestLobbyLeft = nullptr;

		bool m_waitingForPeers = false;

	public:
		static Unet::ServiceID AddressToID(const ENetAddress &addr);

	public:
		ServiceEnet(Internal::Context* ctx, int numChannels);
		virtual ~ServiceEnet();

		virtual void SimulateOutage() override;

		virtual void RunCallbacks() override;

		virtual ServiceType GetType() override;

		virtual ServiceID GetUserID() override;
		virtual std::string GetUserName() override;

		virtual void SetRichPresence(const char* key, const char* value) override;

		virtual void CreateLobby(LobbyPrivacy privacy, int maxPlayers) override;
		virtual void SetLobbyPrivacy(const ServiceID &lobbyId, LobbyPrivacy privacy) override;
		virtual void SetLobbyJoinable(const ServiceID &lobbyId, bool joinable) override;

		virtual void GetLobbyList() override;
		virtual bool FetchLobbyInfo(const ServiceID &id) override;
		virtual void JoinLobby(const ServiceID &id) override;
		virtual void LeaveLobby() override;

		virtual int GetLobbyPlayerCount(const ServiceID &lobbyId) override;
		virtual void SetLobbyMaxPlayers(const ServiceID &lobbyId, int amount) override;
		virtual int GetLobbyMaxPlayers(const ServiceID &lobbyId) override;

		virtual std::string GetLobbyData(const ServiceID &lobbyId, const char* name) override;
		virtual int GetLobbyDataCount(const ServiceID &lobbyId) override;
		virtual LobbyData GetLobbyData(const ServiceID &lobbyId, int index) override;

		virtual ServiceID GetLobbyHost(const ServiceID &lobbyId) override;

		virtual void SetLobbyData(const ServiceID &lobbyId, const char* name, const char* value) override;
		virtual void RemoveLobbyData(const ServiceID &lobbyId, const char* name) override;

		virtual size_t ReliablePacketLimit() override;

		virtual void SendPacket(const ServiceID &peerId, const void* data, size_t size, PacketType type, uint8_t channel) override;
		virtual size_t ReadPacket(void* data, size_t maxSize, ServiceID* peerId, uint8_t channel) override;
		virtual bool IsPacketAvailable(size_t* outPacketSize, uint8_t channel) override;

	private:
		ENetPeer* GetPeer(const ServiceID &id);
		void Clear(size_t numChannels);
	};
}
