#pragma once

#include <IChat.h>

#include <string>
#include <vector>

namespace universelan {
	class ChatMessage {
	private:
		galaxy::api::ChatMessageID id;
		galaxy::api::ChatMessageType type;
		galaxy::api::ChatRoomID room_id;
		galaxy::api::GalaxyID sender_id;
		uint32_t send_time;
		std::string contents;

	public:
		ChatMessage();
		ChatMessage(const ChatMessage& message);
		ChatMessage(galaxy::api::ChatMessageType type, galaxy::api::ChatRoomID room_id, galaxy::api::GalaxyID sender_id, uint32_t send_time, const std::string& contents);

		galaxy::api::ChatMessageID GetID() const;
		galaxy::api::ChatMessageType GetType() const;
		galaxy::api::ChatRoomID GetRoom() const;
		galaxy::api::GalaxyID GetUser() const;
		uint32_t GetSendTime() const;
		const std::string& GetContents() const;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(id, type, room_id, sender_id, send_time, contents);
		}
	};
}
