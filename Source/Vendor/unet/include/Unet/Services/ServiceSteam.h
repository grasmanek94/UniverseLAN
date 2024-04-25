#pragma once

#include <Unet_common.h>
#include <Unet/Service.h>
#include <Unet/Context.h>

#include <steam/steam_api.h>

namespace Unet
{
	class ServiceSteam : public Service
	{
	private:
		std::vector<uint64_t> m_listDataFetch;
		std::vector<uint64_t> m_dataFetch;

		MultiCallback<CreateLobbyResult>::ServiceRequest* m_requestLobbyCreated = nullptr;
		CCallResult<ServiceSteam, LobbyCreated_t> m_callLobbyCreated;

		MultiCallback<LobbyListResult>::ServiceRequest* m_requestLobbyList = nullptr;
		CCallResult<ServiceSteam, LobbyMatchList_t> m_callLobbyList;

		MultiCallback<LobbyJoinResult>::ServiceRequest* m_requestLobbyJoin = nullptr;
		CCallResult<ServiceSteam, LobbyEnter_t> m_callLobbyJoin;

		CCallback<ServiceSteam, LobbyDataUpdate_t> m_callLobbyDataUpdate;
		CCallback<ServiceSteam, LobbyKicked_t> m_callLobbyKicked;
		CCallback<ServiceSteam, LobbyChatUpdate_t> m_callLobbyChatUpdate;

		CCallback<ServiceSteam, P2PSessionRequest_t> m_callP2PSessionRequest;

		CSteamID m_hostID;

	public:
		ServiceSteam(Internal::Context* ctx, int numChannels);
		virtual ~ServiceSteam();

		virtual void SimulateOutage() override;

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
		void OnLobbyCreated(LobbyCreated_t* result, bool bIOFailure);
		void OnLobbyList(LobbyMatchList_t* result, bool bIOFailure);
		void OnLobbyJoin(LobbyEnter_t* result, bool bIOFailure);

		void LobbyListDataUpdated();
		void OnLobbyDataUpdate(LobbyDataUpdate_t* result);
		void OnLobbyKicked(LobbyKicked_t* result);
		void OnLobbyChatUpdate(LobbyChatUpdate_t* result);

		void OnP2PSessionRequest(P2PSessionRequest_t* result);
	};
}
