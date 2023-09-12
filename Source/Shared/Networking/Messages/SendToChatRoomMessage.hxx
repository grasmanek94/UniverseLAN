#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICHAT

#include <ChatRoom.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyApi.h>

namespace universelan {
	class SendToChatRoomMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::ChatRoomID id;
		ChatRoom::message_t message;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, id, message);
		}

		UniqueClassId_Declare(SendToChatRoomMessage);

		SendToChatRoomMessage() : request_id{ 0 }, id{ 0 }, message{ nullptr } {}
		SendToChatRoomMessage(uint64_t request_id, galaxy::api::ChatRoomID id, const ChatRoom::message_t& message) : request_id{ request_id }, id{ id }, message { message } {}
	};
}
#endif
