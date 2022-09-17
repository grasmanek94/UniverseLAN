#pragma once

#include "ChatRoom.hxx"
#include "GlobalUniqueID.hxx"

#include <chrono>
#include <memory>

namespace universelan {
	using namespace galaxy::api;

	ChatRoom::ChatRoom()
		: id{ GlobalUniqueID::get() }, messages{}, members{}, longest_message{ 0 }
	{}

	ChatRoom::ChatRoom(const ChatRoom & chat_room)
		: id{ chat_room.id }, messages{ chat_room.messages }, members{ chat_room.members }, longest_message{ chat_room.longest_message }
	{}

	ChatRoomID ChatRoom::GetID() const
	{
		return id;
	}

	const ChatRoom::messages_t& ChatRoom::GetMessages() const
	{
		return messages;
	}

	const ChatRoom::message_t& ChatRoom::GetMessageByIndex(size_t index) const
	{
		return messages.at(index);
	}

	const ChatRoom::members_t& ChatRoom::GetMembers() const
	{
		return members;
	}

	bool ChatRoom::AddMember(GalaxyID id)
	{
		return members.emplace(id).second;
	}

	bool ChatRoom::RemoveMember(GalaxyID id)
	{
		return members.erase(id) > 0;
	}

	bool ChatRoom::IsMember(GalaxyID id)
	{
		return members.find(id) != members.end();
	}

	ChatRoom::message_t ChatRoom::AddMessage(GalaxyID sender, ChatMessageType type, const std::string& contents)
	{
		uint32_t send_time = (uint32_t)(std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1));
		message_t message = std::make_shared<ChatMessage>(type, id, sender, send_time, contents);

		if (contents.size() > longest_message) {
			longest_message = contents.size();
		}

		messages.push_back(message);

		return message;
	}

	ChatRoom::message_t ChatRoom::AddMessage(const ChatMessage& message)
	{
		message_t message_ptr = std::make_shared<ChatMessage>(message);

		if (message.GetContents().size() > longest_message) {
			longest_message = message.GetContents().size();
		}

		messages.push_back(message_ptr);

		return message_ptr;
	}

	size_t ChatRoom::GetMemberCount() const
	{
		return members.size();
	}

	size_t ChatRoom::GetMessageCount() const
	{
		return messages.size();
	}

	size_t ChatRoom::GetLongestMessage() const
	{
		return longest_message;
	}
}
