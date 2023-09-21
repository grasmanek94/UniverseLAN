#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICHAT 

#include "TestCaseClientDetails.hxx"

class ChatRoomMessageSendListenerImplGlobal : public galaxy::api::GlobalChatRoomMessageSendListener
{
public:
	using on_chat_room_message_send_success_func_t = std::function<void(ChatRoomID, uint32_t sentMessageIndex, ChatMessageID, uint32_t sendTime)>;
	using on_chat_room_message_send_failure_func_t = std::function<void(ChatRoomID, uint32_t sentMessageIndex, FailureReason)>;

private:
	on_chat_room_message_send_success_func_t on_chat_room_message_send_success;
	on_chat_room_message_send_failure_func_t on_chat_room_message_send_failure;

public:
	ChatRoomMessageSendListenerImplGlobal(
		on_chat_room_message_send_success_func_t on_chat_room_message_send_success = nullptr,
		on_chat_room_message_send_failure_func_t on_chat_room_message_send_failure = nullptr) :
		on_chat_room_message_send_success{ on_chat_room_message_send_success },
		on_chat_room_message_send_failure{ on_chat_room_message_send_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ChatRoomMessageSendListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnChatRoomMessageSendSuccess(ChatRoomID chatRoomID, uint32_t sentMessageIndex, ChatMessageID messageID, uint32_t sendTime) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} sentMessageIndex: {} messageID:{} sendTime: {}",
			chatRoomID, sentMessageIndex, messageID, sendTime
		).c_str());

		if (on_chat_room_message_send_success != nullptr) {
			on_chat_room_message_send_success(chatRoomID, sentMessageIndex, messageID, sendTime);
		}
	}

	virtual void OnChatRoomMessageSendFailure(ChatRoomID chatRoomID, uint32_t sentMessageIndex, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} sentMessageIndex: {} failureReason: {}",
			chatRoomID, sentMessageIndex, magic_enum::enum_name(failureReason)
		).c_str());

		if (on_chat_room_message_send_failure != nullptr) {
			on_chat_room_message_send_failure(chatRoomID, sentMessageIndex, failureReason);
		}
	}
};

class ChatRoomMessageSendListenerImplLocal : public galaxy::api::IChatRoomMessageSendListener
{
public:
	using on_chat_room_message_send_success_func_t = std::function<void(ChatRoomID, uint32_t sentMessageIndex, ChatMessageID, uint32_t sendTime)>;
	using on_chat_room_message_send_failure_func_t = std::function<void(ChatRoomID, uint32_t sentMessageIndex, FailureReason)>;

private:
	on_chat_room_message_send_success_func_t on_chat_room_message_send_success;
	on_chat_room_message_send_failure_func_t on_chat_room_message_send_failure;

public:
	ChatRoomMessageSendListenerImplLocal(
		on_chat_room_message_send_success_func_t on_chat_room_message_send_success = nullptr,
		on_chat_room_message_send_failure_func_t on_chat_room_message_send_failure = nullptr) :
		on_chat_room_message_send_success{ on_chat_room_message_send_success },
		on_chat_room_message_send_failure{ on_chat_room_message_send_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ChatRoomMessageSendListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnChatRoomMessageSendSuccess(ChatRoomID chatRoomID, uint32_t sentMessageIndex, ChatMessageID messageID, uint32_t sendTime) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} sentMessageIndex: {} messageID:{} sendTime: {}",
			chatRoomID, sentMessageIndex, messageID, sendTime
		).c_str());

		if (on_chat_room_message_send_success != nullptr) {
			on_chat_room_message_send_success(chatRoomID, sentMessageIndex, messageID, sendTime);
		}
	}

	virtual void OnChatRoomMessageSendFailure(ChatRoomID chatRoomID, uint32_t sentMessageIndex, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"chatRoomID: {} sentMessageIndex: {} failureReason: {}",
			chatRoomID, sentMessageIndex, magic_enum::enum_name(failureReason)
		).c_str());

		if (on_chat_room_message_send_failure != nullptr) {
			on_chat_room_message_send_failure(chatRoomID, sentMessageIndex, failureReason);
		}
	}
};

#endif
