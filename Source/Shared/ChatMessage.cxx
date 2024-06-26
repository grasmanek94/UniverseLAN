#if GALAXY_BUILD_FEATURE_HAS_ICHAT

#include "ChatMessage.hxx"
#include "GlobalUniqueID.hxx"

namespace universelan {
	using namespace galaxy::api;

	ChatMessage::ChatMessage()
		: id{ 0 },
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
		type{ CHAT_MESSAGE_TYPE_UNKNOWN },
#endif
		room_id{ 0 }, sender_id{ 0 }, send_time{ 0 }, contents{}
	{}

	ChatMessage::ChatMessage(const ChatMessage& message)
		:id{ message.id },
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
		type{ message.type },
#endif
		room_id{ message.room_id }, sender_id{ message.sender_id },
		send_time{ message.send_time }, contents{ message.contents }

	{}

	ChatMessage::ChatMessage(
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
		ChatMessageType type,
#endif
		ChatRoomID room_id, GalaxyID sender_id, uint32_t send_time, const std::string& contents)
		: id{ GlobalUniqueID::get() },
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
		type{ type },
#endif
		room_id{ room_id }, sender_id{ sender_id }, send_time{ send_time }, contents{ contents }
	{}

	ChatMessageID ChatMessage::GetID() const
	{
		return id;
	}

#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
	ChatMessageType ChatMessage::GetType() const
	{
		return type;
	}
#endif

	ChatRoomID ChatMessage::GetRoom() const
	{
		return room_id;
	}

	GalaxyID ChatMessage::GetUser() const
	{
		return sender_id;
	}

	uint32_t ChatMessage::GetSendTime() const
	{
		return send_time;
	}

	const std::string& ChatMessage::GetContents() const
	{
		return contents;
	}
}
#endif
