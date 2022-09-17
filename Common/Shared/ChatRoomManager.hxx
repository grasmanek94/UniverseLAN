#pragma once

#include "ChatRoom.hxx"

#include <IChat.h>

#include <memory>
#include <unordered_map>

namespace universelan {
	using namespace galaxy::api;

	class ChatRoomManager {
	public:
		using chatroom_t = std::shared_ptr<ChatRoom>;
		using chatrooms_t = std::unordered_map<ChatRoomID, chatroom_t>;

	private:
		chatrooms_t chatrooms;

	public:
		ChatRoomManager();

		// Server func
		chatroom_t CreateChatRoom();
		bool RemoveChatRoom(ChatRoomID id);
		chatroom_t GetChatRoom(ChatRoomID id);

		// Client func
		bool AddChatRoom(const ChatRoom& chat_room); 
	};
}
