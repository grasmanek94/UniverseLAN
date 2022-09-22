#pragma once

#include "Messages/EventConnect.hxx"
#include "Messages/EventDisconnect.hxx"

#include "Messages/ConnectionAcceptedMessage.hxx"
#include "Messages/CreateLobbyMessage.hxx"
#include "Messages/CreateLobbyResponseMessage.hxx"
#include "Messages/FileRequestMessage.hxx"
#include "Messages/FileShareMessage.hxx"
#include "Messages/FileShareResponseMessage.hxx"
#include "Messages/KeyChallengeMessage.hxx"
#include "Messages/P2PNetworkPacketMessage.hxx"
#include "Messages/RequestChatRoomMessagesMessage.hxx"
#include "Messages/RequestChatRoomWithUserMessage.hxx"
#include "Messages/RequestLobbyListMessage.hxx"
#include "Messages/RequestSpecificUserDataMessage.hxx"
#include "Messages/SendToChatRoomMessage.hxx"
#include "Messages/UserHelloDataMessage.hxx"

namespace universelan {

#define SHARED_NETWORK_IMPLEMENT_ALL_CASES() \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(ConnectionAcceptedMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(CreateLobbyMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(CreateLobbyResponseMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(FileRequestMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(FileShareMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(FileShareResponseMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(KeyChallengeMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(P2PNetworkPacketMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(RequestChatRoomMessagesMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(RequestChatRoomWithUserMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(RequestLobbyListMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(RequestSpecificUserDataMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(SendToChatRoomMessage); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(UserHelloDataMessage)

}