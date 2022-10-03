#pragma once

#include <ChatRoom.hxx>
#include <Networking/SendableEventMessage.hxx>

#include <GalaxyApi.h>

namespace universelan {
	class RequestChatRoomWithUserMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::GalaxyID id;
		std::shared_ptr<ChatRoom> chat_room;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, id, chat_room);
		}

		UniqueClassId_Declare(RequestChatRoomWithUserMessage);

		RequestChatRoomWithUserMessage() : request_id{}, id{}, chat_room{} {}
		RequestChatRoomWithUserMessage(const galaxy::api::GalaxyID& id) : request_id{}, id{id}, chat_room{} {}
		RequestChatRoomWithUserMessage(uint64_t request_id, const galaxy::api::GalaxyID& id) : request_id{ request_id }, id{ id }, chat_room{} {}
	};
}
