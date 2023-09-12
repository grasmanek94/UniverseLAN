#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICHAT

#include "ChatMessage.hxx"

#include <IChat.h>

#include <memory>
#include <set>
#include <string>
#include <vector>

namespace universelan {
	class ChatRoom {
	public:
		using message_t = std::shared_ptr<ChatMessage>;
		using messages_t = std::vector<message_t>;
		using members_t = std::set<galaxy::api::GalaxyID>;

	private:
		galaxy::api::ChatRoomID id;
		messages_t messages;
		members_t members;
		uint32_t longest_message;
		uint32_t read_messages;

	public:
		ChatRoom();
		ChatRoom(const ChatRoom& chat_room);

		galaxy::api::ChatRoomID GetID() const;

		const members_t& GetMembers() const;
		bool AddMember(galaxy::api::GalaxyID id);
		bool RemoveMember(galaxy::api::GalaxyID id);
		bool IsMember(galaxy::api::GalaxyID id);
		uint32_t GetMemberCount() const;

		const messages_t& GetMessages() const;
		messages_t GetMessages(galaxy::api::ChatMessageID exclusive_from) const;
		const message_t& GetMessageByIndex(uint32_t index) const;
		message_t AddMessage(galaxy::api::GalaxyID sender, galaxy::api::ChatMessageType type, const std::string& contents);
		message_t AddMessage(const ChatMessage& message);
		uint32_t GetMessageCount() const;
		uint32_t GetLongestMessage() const;

		void MarkAsRead();
		void MarkAsUnread();
		bool IsRead() const;
		uint32_t GetUnreadCount() const;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(id, messages, members, longest_message, read_messages);
		}
	};
}
#endif