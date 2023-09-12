#if GALAXY_BUILD_FEATURE_HAS_ICHAT

#include "ChatRoomManager.hxx"

#include <memory>

namespace universelan {
	using namespace galaxy::api;

	ChatRoomManager::ChatRoomManager() 
		: chatrooms{}
	{}

	bool ChatRoomManager::RemoveChatRoom(ChatRoomID id)
	{
		return chatrooms.erase(id) > 0;
	}

	ChatRoomManager::chatroom_t ChatRoomManager::GetChatRoom(ChatRoomID id)
	{
		auto it = chatrooms.find(id);
		if (it == chatrooms.end()) {
			return nullptr;
		}

		return it->second;
	}

	bool ChatRoomManager::AddChatRoom(const ChatRoom& chat_room)
	{
		chatroom_t chatroom = std::make_shared<ChatRoom>(chat_room);
		return chatrooms.emplace(chatroom->GetID(), chatroom).second;
	}

	ChatRoomManager::chatroom_t ChatRoomManager::CreateChatRoom()
	{
		chatroom_t chatroom = std::make_shared<ChatRoom>();
		chatrooms.emplace(chatroom->GetID(), chatroom);

		return chatroom;
	}
}
#endif