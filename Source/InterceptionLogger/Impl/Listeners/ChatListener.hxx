#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICHAT 

#include <IChat.h>

namespace universelan::client {
	using namespace galaxy::api;

	class ChatRoomWithUserRetrieveListener : public IChatRoomWithUserRetrieveListener
	{
	public:
		virtual void OnChatRoomWithUserRetrieveSuccess(GalaxyID userID, ChatRoomID chatRoomID);
		virtual void OnChatRoomWithUserRetrieveFailure(GalaxyID userID, FailureReason failureReason);
	};

	class ChatRoomMessageSendListener : public IChatRoomMessageSendListener
	{
	public:
		virtual void OnChatRoomMessageSendSuccess(ChatRoomID chatRoomID, uint32_t sentMessageIndex, ChatMessageID messageID, uint32_t sendTime);
		virtual void OnChatRoomMessageSendFailure(ChatRoomID chatRoomID, uint32_t sentMessageIndex, FailureReason failureReason);
	};

	class ChatRoomMessagesListener : public IChatRoomMessagesListener
	{
	public:
		virtual void OnChatRoomMessagesReceived(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght);
	};

#if GALAXY_BUILD_FEATURE_HAS_ICHATROOMMESSAGERETRIEVELISTENER
	class ChatRoomMessagesRetrieveListener : public IChatRoomMessagesRetrieveListener
	{
	public:
		virtual void OnChatRoomMessagesRetrieveSuccess(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght);
		virtual void OnChatRoomMessagesRetrieveFailure(ChatRoomID chatRoomID, FailureReason failureReason);
	};
#endif
}

#endif