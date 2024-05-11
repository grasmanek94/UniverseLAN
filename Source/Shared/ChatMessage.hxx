#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICHAT

#include <IChat.h>

#include <string>
#include <vector>

namespace universelan {
	class ChatMessage {
	private:
		galaxy::api::ChatMessageID id;
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
		galaxy::api::ChatMessageType type;
#endif
		galaxy::api::ChatRoomID room_id;
		galaxy::api::GalaxyID sender_id;
		uint32_t send_time;
		std::string contents;

	public:
		ChatMessage();
		ChatMessage(const ChatMessage& message);
		ChatMessage(
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
			galaxy::api::ChatMessageType type,
#endif
			galaxy::api::ChatRoomID room_id, galaxy::api::GalaxyID sender_id, uint32_t send_time, const std::string& contents);

		galaxy::api::ChatMessageID GetID() const;
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
		galaxy::api::ChatMessageType GetType() const;
#endif
		galaxy::api::ChatRoomID GetRoom() const;
		galaxy::api::GalaxyID GetUser() const;
		uint32_t GetSendTime() const;
		const std::string& GetContents() const;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(id,
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
				type,
#endif
				room_id, sender_id, send_time, contents);
		}
	};
}
#endif
