#pragma once

#include "ProxifySingleShotListener.hxx"

#include <IMatchmaking.h>

#include <GalaxyVersionedTypes.hxx>

namespace universelan::client {
	using namespace galaxy::api;

	class LobbyListListener : public ILobbyListListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LobbyListListener, ILobbyListListener);

	public:
		virtual void OnLobbyList(uint32_t lobbyCount, LobbyListResult result);
		virtual void OnLobbyList(uint32_t lobbyCount, bool ioFailure);
	};

	class LobbyCreatedListener : public ILobbyCreatedListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LobbyCreatedListener, ILobbyCreatedListener);

	public:
		virtual void OnLobbyCreated(const GalaxyID& lobbyID, LobbyCreateResult result);
	};

	class LobbyEnteredListener : public ILobbyEnteredListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LobbyEnteredListener, ILobbyEnteredListener);

	public:
		virtual void OnLobbyEntered(const GalaxyID& lobbyID, LobbyEnterResult result);
	};

	class LobbyLeftListener : public ILobbyLeftListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LobbyLeftListener, ILobbyLeftListener);

	public:
		virtual void OnLobbyLeft(const GalaxyID& lobbyID, LobbyLeaveReason leaveReason);
		virtual void OnLobbyLeft(const GalaxyID& lobbyID, bool ioFailure);
	};

	class LobbyDataListener : public ILobbyDataListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LobbyDataListener, ILobbyDataListener);

	public:
		virtual void OnLobbyDataUpdated(const GalaxyID& lobbyID, const GalaxyID& memberID);
	};

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
	class LobbyDataUpdateListener : public ILobbyDataUpdateListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LobbyDataUpdateListener, ILobbyDataUpdateListener);

	public:
		virtual void OnLobbyDataUpdateSuccess(const GalaxyID& lobbyID);
		virtual void OnLobbyDataUpdateFailure(const GalaxyID& lobbyID, FailureReason failureReason);
	};

	class LobbyMemberDataUpdateListener : public ILobbyMemberDataUpdateListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LobbyMemberDataUpdateListener, ILobbyMemberDataUpdateListener);

	public:
		virtual void OnLobbyMemberDataUpdateSuccess(const GalaxyID& lobbyID, const GalaxyID& memberID);
		virtual void OnLobbyMemberDataUpdateFailure(const GalaxyID& lobbyID, const GalaxyID& memberID, FailureReason failureReason);
	};
#endif

#if GALAXY_BUILD_FEATURE_HAS_ILOBBYDATARETRIEVELISTENER
	class LobbyDataRetrieveListener : public ILobbyDataRetrieveListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LobbyDataRetrieveListener, ILobbyDataRetrieveListener);

	public:
		virtual void OnLobbyDataRetrieveSuccess(const GalaxyID& lobbyID);
		virtual void OnLobbyDataRetrieveFailure(const GalaxyID& lobbyID, FailureReason failureReason);
	};
#endif

	class LobbyMemberStateListener : public ILobbyMemberStateListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LobbyMemberStateListener, ILobbyMemberStateListener);

	public:
		virtual void OnLobbyMemberStateChanged(const GalaxyID& lobbyID, const GalaxyID& memberID, LobbyMemberStateChange memberStateChange);
	};

	class LobbyOwnerChangeListener : public ILobbyOwnerChangeListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LobbyOwnerChangeListener, ILobbyOwnerChangeListener);

	public:
		virtual void OnLobbyOwnerChanged(const GalaxyID& lobbyID, const GalaxyID& newOwnerID);
	};

	class LobbyMessageListener : public ILobbyMessageListener
	{
		IMPLEMENT_PROXY_ENCAPSULATE_FUNC_FOR(LobbyMessageListener, ILobbyMessageListener);

	public:
		virtual void OnLobbyMessageReceived(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength);
	};
}
