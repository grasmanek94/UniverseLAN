#pragma once

#include "ChatRoom.hxx"

#include <IChat.h>

#include <memory>
#include <unordered_map>

namespace universelan {
	class ChatRoomManager {
	public:
		using chatroom_t = std::shared_ptr<ChatRoom>;
		using chatrooms_t = std::unordered_map<galaxy::api::ChatRoomID, chatroom_t>;
		//using linkage_t = std::unordered_map<GalaxyID, std::set<ChatRoomID>>;

	private:
		chatrooms_t chatrooms;

	public:
		ChatRoomManager();

		// Server func
		chatroom_t CreateChatRoom();
		bool RemoveChatRoom(galaxy::api::ChatRoomID id);
		chatroom_t GetChatRoom(galaxy::api::ChatRoomID id);

		// Client func
		bool AddChatRoom(const ChatRoom& chat_room); 
	};
}
