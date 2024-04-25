#pragma once

#include <Unet_common.h>
#include <Unet/Lobby.h>
#include <Unet/ServiceType.h>
#include <Unet/NetworkMessage.h>

namespace Unet
{
	class Service
	{
	public:
		Internal::Context* m_ctx = nullptr;
		int m_numChannels = 0;

	public:
		Service(Internal::Context* ctx, int numChannels);
		virtual ~Service() {}

		virtual void RunCallbacks() {}

		virtual void SimulateOutage() = 0;

		virtual ServiceType GetType() = 0;

		virtual ServiceID GetUserID() = 0;
		virtual std::string GetUserName() = 0;

		virtual void SetRichPresence(const char* key, const char* value) = 0;

		virtual void CreateLobby(LobbyPrivacy privacy, int maxPlayers) = 0;
		virtual void SetLobbyPrivacy(const ServiceID &lobbyId, LobbyPrivacy privacy) = 0;
		virtual void SetLobbyJoinable(const ServiceID &lobbyId, bool joinable) = 0;

		virtual void GetLobbyList() = 0;
		virtual bool FetchLobbyInfo(const ServiceID &id) = 0;
		virtual void JoinLobby(const ServiceID &id) = 0;
		virtual void LeaveLobby() = 0;

		virtual int GetLobbyPlayerCount(const ServiceID &lobbyId) = 0;
		virtual void SetLobbyMaxPlayers(const ServiceID &lobbyId, int amount) = 0;
		virtual int GetLobbyMaxPlayers(const ServiceID &lobbyId) = 0;

		virtual std::string GetLobbyData(const ServiceID &lobbyId, const char* name) = 0;
		virtual int GetLobbyDataCount(const ServiceID &lobbyId) = 0;
		virtual LobbyData GetLobbyData(const ServiceID &lobbyId, int index) = 0;

		virtual ServiceID GetLobbyHost(const ServiceID &lobbyId) = 0;

		virtual void SetLobbyData(const ServiceID &lobbyId, const char* name, const char* value) = 0;
		virtual void RemoveLobbyData(const ServiceID &lobbyId, const char* name) = 0;

		virtual size_t ReliablePacketLimit() = 0;

		virtual void SendPacket(const ServiceID &peerId, const void* data, size_t size, PacketType type, uint8_t channel) = 0;
		virtual size_t ReadPacket(void* data, size_t maxSize, ServiceID* peerId, uint8_t channel) = 0;
		virtual bool IsPacketAvailable(size_t* outPacketSize, uint8_t channel) = 0;
	};
}
