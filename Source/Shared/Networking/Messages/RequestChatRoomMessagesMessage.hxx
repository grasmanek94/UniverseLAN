#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICHAT

#include <ChatRoom.hxx>
#include <Networking/SendableEventMessage.hxx>

#include <GalaxyApi.h>

#include <memory>

namespace universelan {
	class RequestChatRoomMessagesMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::ChatRoomID id;
		galaxy::api::ChatMessageID oldest_message;
		ChatRoom::messages_t messages;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, id, messages);
		}

		UniqueClassId_Declare(RequestChatRoomMessagesMessage);

		RequestChatRoomMessagesMessage() : request_id{ 0 }, id{ 0 }, oldest_message{ 0 }, messages { nullptr } {}
		RequestChatRoomMessagesMessage(uint64_t request_id, galaxy::api::ChatRoomID id, galaxy::api::ChatMessageID oldest_message) : request_id{ request_id }, id{ id }, oldest_message{ oldest_message }, messages { nullptr } {}
		RequestChatRoomMessagesMessage(uint64_t request_id, galaxy::api::ChatRoomID id, const ChatRoom::messages_t& messages) : request_id{ request_id }, id{ id }, oldest_message{ 0 }, messages{ messages } {}
		RequestChatRoomMessagesMessage(uint64_t request_id, galaxy::api::ChatRoomID id, galaxy::api::ChatMessageID oldest_message, const ChatRoom::messages_t& messages) : request_id{ request_id }, id{ id }, oldest_message{ oldest_message }, messages{ messages } {}
	};
}
#endif