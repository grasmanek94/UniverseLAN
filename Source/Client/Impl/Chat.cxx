#if GALAXY_BUILD_FEATURE_HAS_ICHAT 

#include "Chat.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>
#include <SafeStringCopy.hxx>

#include <boost/preprocessor/control/if.hpp>

namespace universelan::client {
	using namespace galaxy::api;
	ChatImpl::ChatImpl(InterfaceInstances* intf)
		: intf{ intf }, listeners{ intf->notification.get() },
		chatroom_manager{}, incomming_messages_buffer{ nullptr },
		request_chat_room_with_user_requests{},
		request_chat_room_messages_requests{},
		send_to_chat_room_requests{},
		mtx{} {}

	ChatImpl::~ChatImpl() {}

	void ChatImpl::RequestChatRoomWithUser(GalaxyID userID
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
		, IChatRoomWithUserRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICHAT };

		uint64_t request_id = MessageUniqueID::get();

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format(
				"userID: {} listener: {}",
				userID,
				(void*)BOOST_PP_IF(GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER, listener, nullptr)
			));
		}

#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
		request_chat_room_with_user_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RequestChatRoomWithUserMessage{ request_id, userID });
	}

	void ChatImpl::RequestChatRoomWithUserProcessed(const std::shared_ptr<RequestChatRoomWithUserMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICHAT };

		IChatRoomWithUserRetrieveListener* listener = request_chat_room_with_user_requests.pop(data->request_id);

		bool success{ false };
		{
			lock_t lock{ mtx };
			success = data->chat_room && chatroom_manager.AddChatRoom(*data->chat_room);
		}

		if (success) {
			if (trace.has_flags(tracer::Trace::DETAILED)) {
				trace.write_all(std::format(
					"OnChatRoomWithUserRetrieveSuccess userID: {} chat_room: {}",
					data->id, data->chat_room->GetID()
				));
			}

			listeners->NotifyAll(listener,
				&IChatRoomWithUserRetrieveListener::OnChatRoomWithUserRetrieveSuccess,
				data->id, data->chat_room->GetID());
		}
		else {
			if (trace.has_flags(tracer::Trace::DETAILED)) {
				trace.write_all(std::format("OnChatRoomWithUserRetrieveFailure userID: {}", data->id));
			}

			listeners->NotifyAll(listener,
				&IChatRoomWithUserRetrieveListener::OnChatRoomWithUserRetrieveFailure,
				data->id, IChatRoomWithUserRetrieveListener::FAILURE_REASON_UNDEFINED);
		}
	}

	void ChatImpl::RequestChatRoomMessages(ChatRoomID chatRoomID, uint32_t limit, ChatMessageID referenceMessageID
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
		, IChatRoomMessagesRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICHAT };

		if (trace.has_flags(tracer::Trace::ARGUMENTS | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
			trace.write_all(std::format(
				"chatRoomID: {} limit: {} referenceMessageID: {} listener: {}",
				chatRoomID, limit, referenceMessageID,
				(void*)BOOST_PP_IF(GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER, listener, nullptr)
			));
		}

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
		request_chat_room_messages_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RequestChatRoomMessagesMessage{ request_id, chatRoomID, referenceMessageID });
	}

	void ChatImpl::RequestChatRoomMessagesProcessed(const std::shared_ptr<RequestChatRoomMessagesMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICHAT };

		IChatRoomMessagesRetrieveListener* listener = request_chat_room_messages_requests.pop(data->request_id);

		lock_t lock{ mtx };
		auto chat_room = chatroom_manager.GetChatRoom(data->id);
		if (chat_room != nullptr) {
			uint32_t longest_message = 0;
			for (auto message : data->messages) {
				if (message->GetContents().length() > longest_message) {
					longest_message = (uint32_t)message->GetContents().length();
				}
				chat_room->AddMessage(*message);
			}

			if (trace.has_flags(tracer::Trace::DETAILED)) {
				trace.write_all(std::format(
					"OnChatRoomMessagesRetrieveSuccess ChatRoomID: {} MessageCount: {} LongestMessage: {}",
					data->id, (uint32_t)data->messages.size(), longest_message
				));
			}

			incomming_messages_buffer = &data->messages;

			listeners->NotifyAll(listener,
				&IChatRoomMessagesRetrieveListener::OnChatRoomMessagesRetrieveSuccess,
				data->id, (uint32_t)data->messages.size(), longest_message);

			listeners->NotifyAll(
				&IChatRoomMessagesListener::OnChatRoomMessagesReceived,
				data->id, (uint32_t)data->messages.size(), longest_message);

			incomming_messages_buffer = nullptr;
		}
		else {
			if (trace.has_flags(tracer::Trace::DETAILED)) {
				trace.write_all(std::format(
					"OnChatRoomMessagesRetrieveFailure ChatRoomID: {} OldestMessageID: {}",
					data->id, data->oldest_message
				));
			}

			listeners->NotifyAll(listener,
				&IChatRoomMessagesRetrieveListener::OnChatRoomMessagesRetrieveFailure,
				data->id, IChatRoomMessagesRetrieveListener::FAILURE_REASON_UNDEFINED);
		}
	}

	uint32_t ChatImpl::SendChatRoomMessage(ChatRoomID chatRoomID, const char* msg
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
		, IChatRoomMessageSendListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICHAT };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format(
				"chatRoomID: {} msg: {} listener: {}",
				chatRoomID, msg,
				(void*)BOOST_PP_IF(GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER, listener, nullptr)
			));
		}

		uint64_t request_id = MessageUniqueID::get();

		SendToChatRoomMessage message{ request_id, chatRoomID, std::make_shared<ChatMessage>(CHAT_MESSAGE_TYPE_CHAT_MESSAGE, chatRoomID, intf->config->GetApiGalaxyID(), 0UL, msg) };

#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
		send_to_chat_room_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(message);

		// would be quite the feat to submit over 4B requests, ~45days @ 1K/s
		return (uint32_t)request_id;
	}

	void ChatImpl::SendChatRoomMessageProcessed(const std::shared_ptr<SendToChatRoomMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICHAT };

		IChatRoomMessageSendListener* listener = send_to_chat_room_requests.pop(data->request_id);

		if (data->message) {
			{
				lock_t lock{ mtx };
				auto chat_room = chatroom_manager.GetChatRoom(data->id);
				if (chat_room) {
					chat_room->AddMessage(*data->message);
				}
			}

			if (trace.has_flags(tracer::Trace::DETAILED)) {
				trace.write_all(std::format(
					"OnChatRoomMessageSendSuccess ChatRoomID: {} sentMessageIndex: {} ChatMessageID: {} SendTime: {}",
					data->id, (uint32_t)data->request_id, data->message->GetID(), data->message->GetSendTime()
				));
			}

			listeners->NotifyAll(listener,
				&IChatRoomMessageSendListener::OnChatRoomMessageSendSuccess,
				data->id, (uint32_t)data->request_id, data->message->GetID(), data->message->GetSendTime());
		}
		else {

			if (trace.has_flags(tracer::Trace::DETAILED)) {
				trace.write_all(std::format(
					"OnChatRoomMessageSendFailure ChatRoomID: {} sentMessageIndex: {}",
					data->id, (uint32_t)data->request_id
				));
			}

			listeners->NotifyAll(listener,
				&IChatRoomMessageSendListener::OnChatRoomMessageSendFailure,
				data->id, (uint32_t)data->request_id, IChatRoomMessageSendListener::FAILURE_REASON_UNDEFINED);
		}
	}

	uint32_t ChatImpl::GetChatRoomMessageByIndex(uint32_t index, ChatMessageID& messageID, ChatMessageType& messageType, GalaxyID& senderID, uint32_t& sendTime, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICHAT };

		if (trace.has_flags(tracer::Trace::ARGUMENTS | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
			trace.write_all(std::format("index: {}", index));
		}

		lock_t lock{ mtx };
		if (incomming_messages_buffer == nullptr) {
			return 0;
		}

		const auto& message = incomming_messages_buffer->at(index);
		messageID = message->GetID();
		messageType = message->GetType();
		senderID = message->GetUser();
		sendTime = message->GetSendTime();

		const auto& contents = message->GetContents();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
			trace.write_all(std::format(
				"messageID: {} messageType: {} senderID: {} sendTime: {} buffer: {}",
				messageID, magic_enum::enum_name(messageType), senderID, sendTime, contents
			));
		}

		universelan::util::safe_copy_str_n(contents, buffer, bufferLength);

		return (uint32_t)contents.length();
	}

	uint32_t ChatImpl::GetChatRoomMemberCount(ChatRoomID chatRoomID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICHAT };

		if (trace.has_flags(tracer::Trace::ARGUMENTS | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
		}

		lock_t lock{ mtx };
		auto chat_room = chatroom_manager.GetChatRoom(chatRoomID);
		if (chat_room != nullptr) {
			uint32_t member_count = chat_room->GetMemberCount();

			if (trace.has_flags(tracer::Trace::RETURN_VALUES | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
				trace.write_all(std::format("member_count: {}", member_count));
			}

			return member_count;
		}
		else {
			if (trace.has_flags(tracer::Trace::RETURN_VALUES | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
				trace.write_all("CHAT_ROOM==NULLPTR");
			}

			return 0;
		}
	}

	GalaxyID ChatImpl::GetChatRoomMemberUserIDByIndex(ChatRoomID chatRoomID, uint32_t index) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICHAT };

		if (trace.has_flags(tracer::Trace::ARGUMENTS | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
			trace.write_all(std::format("chatRoomID: {} index: {}", chatRoomID, index));
		}

		lock_t lock{ mtx };
		auto chat_room = chatroom_manager.GetChatRoom(chatRoomID);
		if (chat_room != nullptr) {
			auto user_id = container_get_by_index(chat_room->GetMembers(), index);

			if (trace.has_flags(tracer::Trace::RETURN_VALUES | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
				trace.write_all(std::format("UserID: {}", user_id));
			}

			return user_id;
		}
		else {
			if (trace.has_flags(tracer::Trace::RETURN_VALUES | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
				trace.write_all("CHAT_ROOM==NULLPTR");
			}

			return 0;
		}
	}

	uint32_t ChatImpl::GetChatRoomUnreadMessageCount(ChatRoomID chatRoomID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICHAT };

		if (trace.has_flags(tracer::Trace::ARGUMENTS | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
		}

		lock_t lock{ mtx };
		auto chat_room = chatroom_manager.GetChatRoom(chatRoomID);
		if (chat_room != nullptr) {
			uint32_t unread_count = chat_room->GetUnreadCount();

			if (trace.has_flags(tracer::Trace::RETURN_VALUES | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
				trace.write_all(std::format("unread_count: {}", unread_count));
			}

			return unread_count;
		}
		else {
			if (trace.has_flags(tracer::Trace::RETURN_VALUES | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
				trace.write_all("CHAT_ROOM==NULLPTR");
			}

			return 0;
		}
	}

	void ChatImpl::MarkChatRoomAsRead(ChatRoomID chatRoomID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICHAT };

		if (trace.has_flags(tracer::Trace::ARGUMENTS | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
			trace.write_all(std::format("chatRoomID: {}", chatRoomID));
		}

		lock_t lock{ mtx };
		auto chat_room = chatroom_manager.GetChatRoom(chatRoomID);
		if (chat_room != nullptr) {
			if (trace.has_flags(tracer::Trace::DETAILED | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
				trace.write_all("CHAT_ROOM!=NULLPTR");
			}
			chat_room->MarkAsRead();
		}
		else {
			if (trace.has_flags(tracer::Trace::DETAILED | tracer::Trace::HIGH_FREQUENCY_CALLS)) {
				trace.write_all("CHAT_ROOM==NULLPTR");
			}
		}
	}
}
#endif
