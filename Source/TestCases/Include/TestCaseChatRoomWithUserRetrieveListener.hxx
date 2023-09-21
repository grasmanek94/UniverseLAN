#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICHAT 

#include "TestCaseClientDetails.hxx"

class ChatRoomWithUserRetrieveListenerImplGlobal : public galaxy::api::GlobalChatRoomWithUserRetrieveListener
{
public:
	using on_chat_room_with_user_retrieve_success_func_t = std::function<void(GalaxyID userID, ChatRoomID)>;
	using on_chat_room_with_user_retrieve_failure_func_t = std::function<void(GalaxyID userID, FailureReason)>;

private:
	on_chat_room_with_user_retrieve_success_func_t on_chat_room_with_user_retrieve_success;
	on_chat_room_with_user_retrieve_failure_func_t on_chat_room_with_user_retrieve_failure;

public:
	ChatRoomWithUserRetrieveListenerImplGlobal(
		on_chat_room_with_user_retrieve_success_func_t on_chat_room_with_user_retrieve_success = nullptr,
		on_chat_room_with_user_retrieve_failure_func_t on_chat_room_with_user_retrieve_failure = nullptr) :
		on_chat_room_with_user_retrieve_success{ on_chat_room_with_user_retrieve_success },
		on_chat_room_with_user_retrieve_failure{ on_chat_room_with_user_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ChatRoomWithUserRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnChatRoomWithUserRetrieveSuccess(GalaxyID userID, ChatRoomID chatRoomID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} chatRoomID: {}",
			userID, chatRoomID
		).c_str());


		if (on_chat_room_with_user_retrieve_success != nullptr) {
			on_chat_room_with_user_retrieve_success(userID, chatRoomID);
		}
	}

	virtual void OnChatRoomWithUserRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_chat_room_with_user_retrieve_failure != nullptr) {
			on_chat_room_with_user_retrieve_failure(userID, failureReason);
		}
	}
};

class ChatRoomWithUserRetrieveListenerImplLocal : public galaxy::api::IChatRoomWithUserRetrieveListener
{
public:
	using on_chat_room_with_user_retrieve_success_func_t = std::function<void(GalaxyID userID, ChatRoomID)>;
	using on_chat_room_with_user_retrieve_failure_func_t = std::function<void(GalaxyID userID, FailureReason)>;

private:
	on_chat_room_with_user_retrieve_success_func_t on_chat_room_with_user_retrieve_success;
	on_chat_room_with_user_retrieve_failure_func_t on_chat_room_with_user_retrieve_failure;

public:
	ChatRoomWithUserRetrieveListenerImplLocal(
		on_chat_room_with_user_retrieve_success_func_t on_chat_room_with_user_retrieve_success = nullptr,
		on_chat_room_with_user_retrieve_failure_func_t on_chat_room_with_user_retrieve_failure = nullptr) :
		on_chat_room_with_user_retrieve_success{ on_chat_room_with_user_retrieve_success },
		on_chat_room_with_user_retrieve_failure{ on_chat_room_with_user_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ChatRoomWithUserRetrieveListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnChatRoomWithUserRetrieveSuccess(GalaxyID userID, ChatRoomID chatRoomID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} chatRoomID: {}",
			userID, chatRoomID
		).c_str());


		if (on_chat_room_with_user_retrieve_success != nullptr) {
			on_chat_room_with_user_retrieve_success(userID, chatRoomID);
		}
	}

	virtual void OnChatRoomWithUserRetrieveFailure(GalaxyID userID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} failureReason: {}",
			userID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_chat_room_with_user_retrieve_failure != nullptr) {
			on_chat_room_with_user_retrieve_failure(userID, failureReason);
		}
	}
};

#endif
