#pragma once

#include <Unet_common.h>
#include <Unet/LobbyInfo.h>
#include <Unet/LobbyMember.h>
#include <Unet/LobbyData.h>

namespace Unet
{
	class Lobby : public LobbyDataContainer
	{
		friend class Internal::Context;

	private:
		Internal::Context* m_ctx;
		LobbyInfo m_info;

		std::vector<LobbyMember*> m_members;
		std::vector<OutgoingFileTransfer> m_outgoingFileTransfers;

	private:
		Lobby(Internal::Context* ctx, const LobbyInfo &lobbyInfo);
		~Lobby();

	public:
		const LobbyInfo &GetInfo();
		bool IsConnected();

		ServiceID GetPrimaryEntryPoint();

		const std::vector<LobbyMember*> &GetMembers();
		LobbyMember* GetMember(const xg::Guid &guid);
		LobbyMember* GetMember(int peer);
		LobbyMember* GetMember(const ServiceID &serviceId);
		LobbyMember* GetHostMember();

		void HandleMessage(const ServiceID &peer, uint8_t* data, size_t size);
		LobbyMember* DeserializeMember(const json &member);

		void AddEntryPoint(const ServiceID &id);
		void ServiceDisconnected(ServiceType service);

		LobbyMember* AddMemberService(const xg::Guid &guid, const ServiceID &id);
		void RemoveMemberService(const ServiceID &id);
		void RemoveMember(LobbyMember* member);

		void SetName(const std::string &name);
		void SetMaxPlayers(int amount);
		void SetPrivacy(LobbyPrivacy privacy);
		void SetJoinable(bool joinable);

		void SetRichPresence();

		virtual void SetData(const std::string &name, const std::string &value) override;
		virtual std::string GetData(const std::string &name) const override;
		virtual void RemoveData(const std::string &name) override;

	private:
		int GetNextAvailablePeer();

		void HandleOutgoingFileTransfers();
	};
}
