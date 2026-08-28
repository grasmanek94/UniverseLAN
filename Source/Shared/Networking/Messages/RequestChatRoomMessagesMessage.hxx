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
			// REVIEW: oldest_message is part of the request state but is omitted from
			// the wire format. Incremental requests deserialize as zero and cannot select
			// the requested starting point; serialize it with the other fields.
			ar(request_id, id, messages);
		}

		UniqueClassId_Declare(RequestChatRoomMessagesMessage);

		// REVIEW: `{ nullptr }` constructs a one-element vector containing a null
		// shared_ptr, not an empty vector. Default/request messages therefore carry a
		// bogus entry; use `{}` for an empty response payload.
		RequestChatRoomMessagesMessage() : request_id{ 0 }, id{ 0 }, oldest_message{ 0 }, messages { nullptr } {}
		RequestChatRoomMessagesMessage(uint64_t request_id, galaxy::api::ChatRoomID id, galaxy::api::ChatMessageID oldest_message) : request_id{ request_id }, id{ id }, oldest_message{ oldest_message }, messages { nullptr } {}
		RequestChatRoomMessagesMessage(uint64_t request_id, galaxy::api::ChatRoomID id, const ChatRoom::messages_t& messages) : request_id{ request_id }, id{ id }, oldest_message{ 0 }, messages{ messages } {}
		RequestChatRoomMessagesMessage(uint64_t request_id, galaxy::api::ChatRoomID id, galaxy::api::ChatMessageID oldest_message, const ChatRoom::messages_t& messages) : request_id{ request_id }, id{ id }, oldest_message{ oldest_message }, messages{ messages } {}
	};
}
#endif