#pragma once

#include <Unet_common.h>
#include <Unet/ICallbacks.h>
#include <Unet/ServiceType.h>
#include <Unet/Lobby.h>
#include <Unet/Service.h>
#include <Unet/MultiCallback.h>
#include <Unet/NetworkMessage.h>
#include <Unet/Reassembly.h>
#include <Unet/IContext.h>

namespace Unet
{
	namespace Internal
	{
		class Context : public IContext
		{
			friend class ::Unet::Lobby;
			friend class ::Unet::LobbyMember;
			friend struct ::Unet::LobbyListResult;

		public:
			Context(int numChannels = 1);
			virtual ~Context();

			virtual ContextStatus GetStatus() override;

			virtual void SetCallbacks(ICallbacks* callbacks) override;
			virtual ICallbacks* GetCallbacks() override;

			virtual void RunCallbacks() override;

			virtual void SetPrimaryService(ServiceType service) override;
			virtual ServiceType GetPrimaryService() override;

			virtual void EnableService(ServiceType service) override;
			virtual int ServiceCount() override;
			virtual void SimulateServiceOutage(ServiceType service) override;

			virtual void CreateLobby(LobbyPrivacy privacy, int maxPlayers, const char* name = nullptr) override;

			virtual void GetLobbyList(const LobbyListFilter &filter) override;
			virtual bool FetchLobbyInfo(const ServiceID &id) override;
			virtual void JoinLobby(const LobbyInfo &lobbyInfo) override;
			virtual void JoinLobby(const ServiceID &id) override;
			virtual void LeaveLobby(LeaveReason reason = LeaveReason::UserLeave) override;

			virtual void KickMember(LobbyMember* member) override;

			virtual bool IsHosting() override;
			virtual Lobby* CurrentLobby() override;
			virtual int GetLocalPeer() override;
			virtual xg::Guid GetLocalGuid() override;

			virtual void SetPersonaName(const char* str) override;
			virtual const char* GetPersonaName() override;

			virtual void AddFile(const char* filename, const char* filenameOnDisk) override;
			virtual void AddFile(const char* filename, uint8_t* buffer, size_t size) override;
			virtual void RemoveFile(const char* filename) override;

			virtual void RequestFile(LobbyMember* member, const char* filename) override;
			virtual void RequestFile(LobbyMember* member, LobbyFile* file) override;

			virtual void SendChat(const char* message) override;

			virtual bool IsMessageAvailable(int channel) override;
			virtual NetworkMessageRef ReadMessage(int channel) override;

			void SendTo_Impl(LobbyMember* member, uint8_t* data, size_t size, PacketType type = PacketType::Reliable, uint8_t channel = 0);
			virtual void SendTo(LobbyMember* member, uint8_t* data, size_t size, PacketType type = PacketType::Reliable, uint8_t channel = 0) override;
			virtual void SendToAll(uint8_t* data, size_t size, PacketType type = PacketType::Reliable, uint8_t channel = 0) override;
			virtual void SendToAllExcept(LobbyMember* exceptMember, uint8_t* data, size_t size, PacketType type = PacketType::Reliable, uint8_t channel = 0) override;
			virtual void SendToHost(uint8_t* data, size_t size, PacketType type = PacketType::Reliable, uint8_t channel = 0) override;

		private:
			Service* PrimaryService();
			Service* GetService(ServiceType type);

		public:
			void InternalSendTo(LobbyMember* member, const json &js, uint8_t* binaryData = nullptr, size_t binarySize = 0);
			void InternalSendTo(const ServiceID &id, const json &js, uint8_t* binaryData = nullptr, size_t binarySize = 0);
			void InternalSendToAll(const json &js, uint8_t* binaryData = nullptr, size_t binarySize = 0);
			void InternalSendToAllExcept(LobbyMember* exceptMember, const json &js, uint8_t* binaryData = nullptr, size_t binarySize = 0);
			void InternalSendToHost(const json &js, uint8_t* binaryData = nullptr, size_t binarySize = 0);

		private:
			void OnLobbyCreated(const CreateLobbyResult &result);
			void OnLobbyList(const LobbyListResult &result);
			void OnLobbyJoined(const LobbyJoinResult &result);
			void OnLobbyLeft(const LobbyLeftResult &result);

			void OnLobbyPlayerLeft(LobbyMember* member);

			void PrepareReceiveBuffer(size_t size);
			void PrepareSendBuffer(size_t size);

		private:
			std::string m_personaName;

			int m_numChannels;

			ContextStatus m_status;
			ServiceType m_primaryService;

			ICallbacks* m_callbacks;

			Lobby* m_currentLobby;
			xg::Guid m_localGuid;
			int m_localPeer;

			std::vector<Service*> m_services;

			std::vector<std::queue<NetworkMessage*>> m_queuedMessages;
			Reassembly m_reassembly;

			std::vector<uint8_t> m_receiveBuffer;
			std::vector<uint8_t> m_sendBuffer;

		public:
			MultiCallback<CreateLobbyResult> m_callbackCreateLobby;
			MultiCallback<LobbyListResult> m_callbackLobbyList;
			MultiCallback<LobbyJoinResult> m_callbackLobbyJoin;
			MultiCallback<LobbyLeftResult> m_callbackLobbyLeft;
		};
	}
}
