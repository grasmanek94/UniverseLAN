#pragma once

#include <IMatchmaking.h>

namespace universelan::client {
	using namespace galaxy::api;

	class LobbyListListener : public ILobbyListListener
	{
	public:
		virtual void OnLobbyList(uint32_t lobbyCount, LobbyListResult result);
	};

	class LobbyCreatedListener : public ILobbyCreatedListener
	{
	public:
		virtual void OnLobbyCreated(const GalaxyID& lobbyID, LobbyCreateResult result);
	};

	class LobbyEnteredListener : public ILobbyEnteredListener
	{
	public:
		virtual void OnLobbyEntered(const GalaxyID& lobbyID, LobbyEnterResult result);
	};

	class LobbyLeftListener : public ILobbyLeftListener
	{
	public:
		virtual void OnLobbyLeft(const GalaxyID& lobbyID, LobbyLeaveReason leaveReason);
	};

	class LobbyDataListener : public ILobbyDataListener
	{
	public:
		virtual void OnLobbyDataUpdated(const GalaxyID& lobbyID, const GalaxyID& memberID);
	};

	class LobbyDataUpdateListener : public ILobbyDataUpdateListener
	{
	public:
		virtual void OnLobbyDataUpdateSuccess(const GalaxyID& lobbyID);
		virtual void OnLobbyDataUpdateFailure(const GalaxyID& lobbyID, FailureReason failureReason);
	};

	class LobbyMemberDataUpdateListener : public ILobbyMemberDataUpdateListener
	{
	public:
		virtual void OnLobbyMemberDataUpdateSuccess(const GalaxyID& lobbyID, const GalaxyID& memberID);
		virtual void OnLobbyMemberDataUpdateFailure(const GalaxyID& lobbyID, const GalaxyID& memberID, FailureReason failureReason);
	};

	class LobbyDataRetrieveListener : public ILobbyDataRetrieveListener
	{
	public:
		virtual void OnLobbyDataRetrieveSuccess(const GalaxyID& lobbyID);
		virtual void OnLobbyDataRetrieveFailure(const GalaxyID& lobbyID, FailureReason failureReason);
	};

	class LobbyMemberStateListener : public ILobbyMemberStateListener
	{
	public:
		virtual void OnLobbyMemberStateChanged(const GalaxyID& lobbyID, const GalaxyID& memberID, LobbyMemberStateChange memberStateChange);
	};

	class LobbyOwnerChangeListener : public ILobbyOwnerChangeListener
	{
	public:
		virtual void OnLobbyOwnerChanged(const GalaxyID& lobbyID, const GalaxyID& newOwnerID);
	};

	class LobbyMessageListener : public ILobbyMessageListener
	{
	public:
		virtual void OnLobbyMessageReceived(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength);
	};
}
