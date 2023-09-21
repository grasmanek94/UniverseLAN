#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICHAT 

#include "TestCaseClientDetails.hxx"

class ChatRoomMessagesListenerImplGlobal : public galaxy::api::GlobalChatRoomMessagesListener
{
public:
	using on_chat_room_messages_received_func_t = std::function<void(ChatRoomID, uint32_t messageCount, uint32_t longestMessageLenght)>;

private:
	on_chat_room_messages_received_func_t on_chat_room_messages_received;

public:
	ChatRoomMessagesListenerImplGlobal(
		on_chat_room_messages_received_func_t on_chat_room_messages_received = nullptr) :
		on_chat_room_messages_received{ on_chat_room_messages_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ChatRoomMessagesListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnChatRoomMessagesReceived(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} messageCount: {} longestMessageLenght: {}",
			chatRoomID, messageCount, longestMessageLenght
		).c_str());


		if (on_chat_room_messages_received != nullptr) {
			on_chat_room_messages_received(chatRoomID, messageCount, longestMessageLenght);
		}
	}
};

class ChatRoomMessagesListenerImplLocal : public galaxy::api::IChatRoomMessagesListener
{
public:
	using on_chat_room_messages_received_func_t = std::function<void(ChatRoomID, uint32_t messageCount, uint32_t longestMessageLenght)>;

private:
	on_chat_room_messages_received_func_t on_chat_room_messages_received;

public:
	ChatRoomMessagesListenerImplLocal(
		on_chat_room_messages_received_func_t on_chat_room_messages_received = nullptr) :
		on_chat_room_messages_received{ on_chat_room_messages_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ChatRoomMessagesListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnChatRoomMessagesReceived(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} messageCount: {} longestMessageLenght: {}",
			chatRoomID, messageCount, longestMessageLenght
		).c_str());


		if (on_chat_room_messages_received != nullptr) {
			on_chat_room_messages_received(chatRoomID, messageCount, longestMessageLenght);
		}
	}
};

#endif
