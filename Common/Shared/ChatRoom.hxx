#pragma once

#include "ChatMessage.hxx"

#include <IChat.h>

#include <memory>
#include <set>
#include <string>
#include <vector>

namespace universelan {
	using namespace galaxy::api;

	class ChatRoom {
	public:
		using message_t = std::shared_ptr<ChatMessage>;
		using messages_t = std::vector<message_t>;
		using members_t = std::set<GalaxyID>;

	private:
		ChatRoomID id;
		messages_t messages;
		members_t members;
		size_t longest_message;

	public:
		ChatRoom();
		ChatRoom(const ChatRoom& chat_room);

		ChatRoomID GetID() const;

		const members_t& GetMembers() const;
		bool AddMember(GalaxyID id);
		bool RemoveMember(GalaxyID id);
		bool IsMember(GalaxyID id);
		size_t GetMemberCount() const;

		const messages_t& GetMessages() const;
		const message_t& GetMessageByIndex(size_t index) const;
		message_t AddMessage(GalaxyID sender, ChatMessageType type, const std::string& contents);
		message_t AddMessage(const ChatMessage& message);
		size_t GetMessageCount() const;
		size_t GetLongestMessage() const;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(id, messages, members, longest_message);
		}
	};
}
