#pragma once

#include <IChat.h>

#include <string>
#include <vector>

namespace universelan {
	using namespace galaxy::api;

	class ChatMessage {
	private:
		ChatMessageID id;
		ChatMessageType type;
		ChatRoomID room_id;
		GalaxyID sender_id;
		uint32_t send_time;
		std::string contents;

	public:
		ChatMessage();
		ChatMessage(const ChatMessage& message);
		ChatMessage(ChatMessageType type, ChatRoomID room_id, GalaxyID sender_id, uint32_t send_time, const std::string& contents);

		ChatMessageID GetID() const;
		ChatMessageType GetType() const;
		ChatRoomID GetRoom() const;
		GalaxyID GetUser() const;
		uint32_t GetSendTime() const;
		const std::string& GetContents() const;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(id, type, room_id, sender_id, send_time, contents);
		}
	};
}
