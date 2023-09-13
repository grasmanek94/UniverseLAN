#pragma once

#include "Messages/EventConnect.hxx"
#include "Messages/EventDisconnect.hxx"

#include "Messages/ConnectionAcceptedMessage.hxx"
#include "Messages/CreateLobbyMessage.hxx"
#include "Messages/CreateLobbyResponseMessage.hxx"
#include "Messages/FileRequestMessage.hxx"
#include "Messages/FileShareMessage.hxx"
#include "Messages/FileShareResponseMessage.hxx"
#include "Messages/JoinLobbyMessage.hxx"
#include "Messages/KeyChallengeMessage.hxx"
#include "Messages/LeaveLobbyMessage.hxx"
#include "Messages/LobbyMemberStateChangeMessage.hxx"
#include "Messages/LobbyOwnerChangeMessage.hxx"
#include "Messages/OnlineStatusChangeMessage.hxx"
#include "Messages/P2PNetworkPacketMessage.hxx"
#include "Messages/RequestChatRoomMessagesMessage.hxx"
#include "Messages/RequestChatRoomWithUserMessage.hxx"
#include "Messages/RequestLobbyDataMessage.hxx"
#include "Messages/RequestLobbyListMessage.hxx"
#include "Messages/RequestSpecificUserDataMessage.hxx"
#include "Messages/RichPresenceChangeMessage.hxx"
#include "Messages/SendToChatRoomMessage.hxx"
#include "Messages/SendToLobbyMessage.hxx"
#include "Messages/SetLobbyDataMessage.hxx"
#include "Messages/SetLobbyJoinableMessage.hxx"
#include "Messages/SetLobbyMaxMembersMessage.hxx"
#include "Messages/SetLobbyMemberDataMessage.hxx"
#include "Messages/SetLobbyTypeMessage.hxx"
#include "Messages/SetUserDataMessage.hxx"
#include "Messages/UserHelloDataMessage.hxx"

namespace universelan {

#if GALAXY_BUILD_FEATURE_HAS_ICHAT 
#define SHARED_NETWORK_IMPLEMENT_ICHAT \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(RequestChatRoomMessagesMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(RequestChatRoomWithUserMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(SendToChatRoomMessage);
#else
#define SHARED_NETWORK_IMPLEMENT_ICHAT
#endif

#define SHARED_NETWORK_IMPLEMENT_ALL_CASES() \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(ConnectionAcceptedMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(CreateLobbyMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(CreateLobbyResponseMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(FileRequestMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(FileShareMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(FileShareResponseMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(JoinLobbyMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(KeyChallengeMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(LeaveLobbyMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(LobbyMemberStateChangeMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(LobbyOwnerChangeMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(OnlineStatusChangeMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(P2PNetworkPacketMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(RequestLobbyDataMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(RequestLobbyListMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(RequestSpecificUserDataMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(RichPresenceChangeMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(SendToLobbyMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(SetLobbyDataMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(SetLobbyJoinableMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(SetLobbyMaxMembersMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(SetLobbyMemberDataMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(SetLobbyTypeMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(SetUserDataMessage); \
	SHARED_NETWORK_IMPLEMENT_ICHAT \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(UserHelloDataMessage)

}