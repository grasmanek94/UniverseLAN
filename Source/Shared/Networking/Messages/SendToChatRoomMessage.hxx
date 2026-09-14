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
		galaxy::api::IChatRoomMessageSendListener::FailureReason fail_reason;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, id, message, fail_reason);
		}

		UniqueClassId_Declare(SendToChatRoomMessage);

		SendToChatRoomMessage() : request_id{ 0 }, id{ 0 }, message{ nullptr }, fail_reason{ galaxy::api::IChatRoomMessageSendListener::FAILURE_REASON_UNDEFINED } {}
		SendToChatRoomMessage(uint64_t request_id, galaxy::api::ChatRoomID id, const ChatRoom::message_t& message) : request_id{ request_id }, id{ id }, message { message }, fail_reason{ galaxy::api::IChatRoomMessageSendListener::FAILURE_REASON_UNDEFINED } {}
		SendToChatRoomMessage(uint64_t request_id, galaxy::api::ChatRoomID id, galaxy::api::IChatRoomMessageSendListener::FailureReason fail_reason) : request_id{ request_id }, id{ id }, message{ nullptr }, fail_reason{ fail_reason } {}
	};
}
#endif
