#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICHAT 

#include "TestCaseClientDetails.hxx"

class ChatRoomMessagesRetrieveListenerImplGlobal : public galaxy::api::GlobalChatRoomMessagesRetrieveListener
{
public:
	using on_chat_room_messages_retrieve_success_func_t = std::function<void(ChatRoomID, uint32_t messageCount, uint32_t longestMessageLenght)>;
	using on_chat_room_messages_retrieve_failure_func_t = std::function<void(ChatRoomID, FailureReason)>;

private:
	on_chat_room_messages_retrieve_success_func_t on_chat_room_messages_retrieve_success;
	on_chat_room_messages_retrieve_failure_func_t on_chat_room_messages_retrieve_failure;

public:
	ChatRoomMessagesRetrieveListenerImplGlobal(
		on_chat_room_messages_retrieve_success_func_t on_chat_room_messages_retrieve_success = nullptr,
		on_chat_room_messages_retrieve_failure_func_t on_chat_room_messages_retrieve_failure = nullptr) :
		on_chat_room_messages_retrieve_success{ on_chat_room_messages_retrieve_success },
		on_chat_room_messages_retrieve_failure{ on_chat_room_messages_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ChatRoomMessagesRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnChatRoomMessagesRetrieveSuccess(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} messageCount: {} longestMessageLenght: {}",
			chatRoomID, messageCount, longestMessageLenght
		).c_str());


		if (on_chat_room_messages_retrieve_success != nullptr) {
			on_chat_room_messages_retrieve_success(chatRoomID, messageCount, longestMessageLenght);
		}
	}

	virtual void OnChatRoomMessagesRetrieveFailure(ChatRoomID chatRoomID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} failureReason: {}",
			chatRoomID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_chat_room_messages_retrieve_failure != nullptr) {
			on_chat_room_messages_retrieve_failure(chatRoomID, failureReason);
		}
	}
};

class ChatRoomMessagesRetrieveListenerImplLocal : public galaxy::api::IChatRoomMessagesRetrieveListener
{
public:
	using on_chat_room_messages_retrieve_success_func_t = std::function<void(ChatRoomID, uint32_t messageCount, uint32_t longestMessageLenght)>;
	using on_chat_room_messages_retrieve_failure_func_t = std::function<void(ChatRoomID, FailureReason)>;

private:
	on_chat_room_messages_retrieve_success_func_t on_chat_room_messages_retrieve_success;
	on_chat_room_messages_retrieve_failure_func_t on_chat_room_messages_retrieve_failure;

public:
	ChatRoomMessagesRetrieveListenerImplLocal(
		on_chat_room_messages_retrieve_success_func_t on_chat_room_messages_retrieve_success = nullptr,
		on_chat_room_messages_retrieve_failure_func_t on_chat_room_messages_retrieve_failure = nullptr) :
		on_chat_room_messages_retrieve_success{ on_chat_room_messages_retrieve_success },
		on_chat_room_messages_retrieve_failure{ on_chat_room_messages_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ChatRoomMessagesRetrieveListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnChatRoomMessagesRetrieveSuccess(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} messageCount: {} longestMessageLenght: {}",
			chatRoomID, messageCount, longestMessageLenght
		).c_str());


		if (on_chat_room_messages_retrieve_success != nullptr) {
			on_chat_room_messages_retrieve_success(chatRoomID, messageCount, longestMessageLenght);
		}
	}

	virtual void OnChatRoomMessagesRetrieveFailure(ChatRoomID chatRoomID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} failureReason: {}",
			chatRoomID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_chat_room_messages_retrieve_failure != nullptr) {
			on_chat_room_messages_retrieve_failure(chatRoomID, failureReason);
		}
	}
};

#endif
