#pragma once

#include "ChatRoom.hxx"

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyApi.h>

namespace universelan {
	using namespace galaxy::api;

	class RequestChatRoomWithUserMessage
	{
	public:
		uint64_t request_id;
		GalaxyID id;
		std::shared_ptr<ChatRoom> chat_room;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, id, chat_room);
		}

		UniqueClassId_Declare(RequestChatRoomWithUserMessage);

		RequestChatRoomWithUserMessage() : request_id{}, id{}, chat_room{} {}
		RequestChatRoomWithUserMessage(const GalaxyID& id) : request_id{}, id{id}, chat_room{} {}
		RequestChatRoomWithUserMessage(uint64_t request_id, const GalaxyID& id) : request_id{ request_id }, id{ id }, chat_room{} {}
	};
}
