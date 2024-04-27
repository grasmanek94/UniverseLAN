#pragma once

#include <Unet_common.h>
#include <Unet/Service.h>
#include <Unet/Context.h>

#include <GalaxyApi.h>

namespace Unet
{
	class GalaxyListener
	{
	protected:
		class ServiceGalaxy* m_self;
	};

	class LobbyListListener : public GalaxyListener
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, public galaxy::api::ILobbyListListener, public galaxy::api::ILobbyDataRetrieveListener
#else
		, public galaxy::api::GlobalLobbyListListener, public galaxy::api::GlobalLobbyDataRetrieveListener
#endif
	{
	private:
		std::vector<galaxy::api::GalaxyID> m_listDataFetch;

	public:
		LobbyListListener(ServiceGalaxy* self) { m_self = self; }
		virtual void OnLobbyList(uint32_t lobbyCount
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
			, galaxy::api::LobbyListResult result
#else
			, bool ioFailure
#endif
		) override;
		void LobbyDataUpdated();
		virtual void OnLobbyDataRetrieveSuccess(const galaxy::api::GalaxyID& lobbyID) override;
		virtual void OnLobbyDataRetrieveFailure(const galaxy::api::GalaxyID& lobbyID, FailureReason failureReason) override;
	};

	class ServiceGalaxy : public Service,
		galaxy::api::ILobbyCreatedListener,
		galaxy::api::ILobbyEnteredListener,
		galaxy::api::ILobbyLeftListener,
		galaxy::api::ILobbyMemberStateListener,
		galaxy::api::ILobbyDataRetrieveListener
	{
	private:
		LobbyListListener m_lobbyListListener;
		std::vector<galaxy::api::GalaxyID> m_dataFetch;

	public:
		MultiCallback<CreateLobbyResult>::ServiceRequest* m_requestLobbyCreated = nullptr;
		MultiCallback<LobbyListResult>::ServiceRequest* m_requestLobbyList = nullptr;
		MultiCallback<LobbyJoinResult>::ServiceRequest* m_requestLobbyJoin = nullptr;
		MultiCallback<LobbyLeftResult>::ServiceRequest* m_requestLobbyLeft = nullptr;

	public:
		ServiceGalaxy(Internal::Context* ctx, int numChannels);
		virtual ~ServiceGalaxy();

		virtual void SimulateOutage() override;

		virtual ServiceType GetType() override;

		virtual ServiceID GetUserID() override;
		virtual std::string GetUserName() override;

		virtual void SetRichPresence(const char* key, const char* value) override;

		virtual void CreateLobby(LobbyPrivacy privacy, int maxPlayers) override;
		virtual void SetLobbyPrivacy(const ServiceID& lobbyId, LobbyPrivacy privacy) override;
		virtual void SetLobbyJoinable(const ServiceID& lobbyId, bool joinable) override;

		virtual void GetLobbyList() override;
		virtual bool FetchLobbyInfo(const ServiceID& id) override;
		virtual void JoinLobby(const ServiceID& id) override;
		virtual void LeaveLobby() override;

		virtual int GetLobbyPlayerCount(const ServiceID& lobbyId) override;
		virtual void SetLobbyMaxPlayers(const ServiceID& lobbyId, int amount) override;
		virtual int GetLobbyMaxPlayers(const ServiceID& lobbyId) override;

		virtual std::string GetLobbyData(const ServiceID& lobbyId, const char* name) override;
		virtual int GetLobbyDataCount(const ServiceID& lobbyId) override;
		virtual LobbyData GetLobbyData(const ServiceID& lobbyId, int index) override;

		virtual ServiceID GetLobbyHost(const ServiceID& lobbyId) override;

		virtual void SetLobbyData(const ServiceID& lobbyId, const char* name, const char* value) override;
		virtual void RemoveLobbyData(const ServiceID& lobbyId, const char* name) override;

		virtual size_t ReliablePacketLimit() override;

		virtual void SendPacket(const ServiceID& peerId, const void* data, size_t size, PacketType type, uint8_t channel) override;
		virtual size_t ReadPacket(void* data, size_t maxSize, ServiceID* peerId, uint8_t channel) override;
		virtual bool IsPacketAvailable(size_t* outPacketSize, uint8_t channel) override;

	private:
		virtual void OnLobbyCreated(const galaxy::api::GalaxyID& lobbyID, galaxy::api::LobbyCreateResult result) override;
		virtual void OnLobbyEntered(const galaxy::api::GalaxyID& lobbyID, galaxy::api::LobbyEnterResult result) override;
		virtual void OnLobbyLeft(const galaxy::api::GalaxyID& lobbyID
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
			, galaxy::api::LobbyLeaveReason leaveReason
#else
			, bool ioFailure
#endif
		) override;

		virtual void OnLobbyMemberStateChanged(const galaxy::api::GalaxyID& lobbyID, const galaxy::api::GalaxyID& memberID, galaxy::api::LobbyMemberStateChange memberStateChange) override;
		virtual void OnLobbyDataRetrieveSuccess(const galaxy::api::GalaxyID& lobbyID) override;
		virtual void OnLobbyDataRetrieveFailure(const galaxy::api::GalaxyID& lobbyID, FailureReason failureReason) override;
	};
}
