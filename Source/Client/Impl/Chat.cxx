#if GALAXY_BUILD_FEATURE_HAS_ICHAT 

#include "Chat.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>
#include <SafeStringCopy.hxx>

namespace universelan::client {
	using namespace galaxy::api;
	ChatImpl::ChatImpl(InterfaceInstances* intf)
		: intf{ intf }, listeners{ intf->notification.get() },
		chatroom_manager{}, incomming_messages_buffer{ nullptr },
		request_chat_room_with_user_requests{},
		request_chat_room_messages_requests{},
		send_to_chat_room_requests{},
		mtx{}
	{}

	ChatImpl::~ChatImpl()
	{
	}

	void ChatImpl::RequestChatRoomWithUser(GalaxyID userID
#if (GALAXY_VERSION) > 11240
		, IChatRoomWithUserRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		uint64_t request_id = MessageUniqueID::get();

#if (GALAXY_VERSION) > 11240
		request_chat_room_with_user_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RequestChatRoomWithUserMessage{ request_id, userID });
	}

	void ChatImpl::RequestChatRoomWithUserProcessed(const std::shared_ptr<RequestChatRoomWithUserMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		IChatRoomWithUserRetrieveListener* listener = request_chat_room_with_user_requests.pop(data->request_id);

		bool success{ false };
		{
			lock_t lock{ mtx };
			success = data->chat_room && chatroom_manager.AddChatRoom(*data->chat_room);
		}

		if (success) {
			listeners->NotifyAll(listener,
				&IChatRoomWithUserRetrieveListener::OnChatRoomWithUserRetrieveSuccess,
				data->id, data->chat_room->GetID());
		}
		else {
			listeners->NotifyAll(listener,
				&IChatRoomWithUserRetrieveListener::OnChatRoomWithUserRetrieveFailure,
				data->id, IChatRoomWithUserRetrieveListener::FAILURE_REASON_UNDEFINED);
		}
	}

	void ChatImpl::RequestChatRoomMessages(ChatRoomID chatRoomID, uint32_t limit, ChatMessageID referenceMessageID
#if (GALAXY_VERSION) > 11240
		, IChatRoomMessagesRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		uint64_t request_id = MessageUniqueID::get();

#if (GALAXY_VERSION) > 11240
		request_chat_room_messages_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RequestChatRoomMessagesMessage{ request_id, chatRoomID, referenceMessageID });
	}

	void ChatImpl::RequestChatRoomMessagesProcessed(const std::shared_ptr<RequestChatRoomMessagesMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

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
			listeners->NotifyAll(listener,
				&IChatRoomMessagesRetrieveListener::OnChatRoomMessagesRetrieveFailure,
				data->id, IChatRoomMessagesRetrieveListener::FAILURE_REASON_UNDEFINED);
		}
	}

	uint32_t ChatImpl::SendChatRoomMessage(ChatRoomID chatRoomID, const char* msg
#if (GALAXY_VERSION) > 11240
		, IChatRoomMessageSendListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		uint64_t request_id = MessageUniqueID::get();

		SendToChatRoomMessage message{ request_id, chatRoomID, std::make_shared<ChatMessage>(CHAT_MESSAGE_TYPE_CHAT_MESSAGE, chatRoomID, intf->config->GetApiGalaxyID(), 0UL, msg) };

#if (GALAXY_VERSION) > 11240
		send_to_chat_room_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(message);

		// would be quite the feat to submit over 4B requests, ~45days @ 1K/s
		return (uint32_t)request_id;
	}

	void ChatImpl::SendChatRoomMessageProcessed(const std::shared_ptr<SendToChatRoomMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		IChatRoomMessageSendListener* listener = send_to_chat_room_requests.pop(data->request_id);

		if (data->message) {
			{
				lock_t lock{ mtx };
				auto chat_room = chatroom_manager.GetChatRoom(data->id);
				if (chat_room) {
					chat_room->AddMessage(*data->message);
				}
			}

			listeners->NotifyAll(listener,
				&IChatRoomMessageSendListener::OnChatRoomMessageSendSuccess, 
				data->id, (uint32_t)data->request_id, data->message->GetID(), data->message->GetSendTime());
		}
		else {
			listeners->NotifyAll(listener,
				&IChatRoomMessageSendListener::OnChatRoomMessageSendFailure,
				data->id, (uint32_t)data->request_id, IChatRoomMessageSendListener::FAILURE_REASON_UNDEFINED);
		}
	}

	uint32_t ChatImpl::GetChatRoomMessageByIndex(uint32_t index, ChatMessageID& messageID, ChatMessageType& messageType, GalaxyID& senderID, uint32_t& sendTime, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

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
		universelan::util::safe_copy_str_n(contents, buffer, bufferLength);

		return (uint32_t)contents.length();
	}

	uint32_t ChatImpl::GetChatRoomMemberCount(ChatRoomID chatRoomID) {
		tracer::Trace trace{ __FUNCTION__ };

		lock_t lock{ mtx };
		auto chat_room = chatroom_manager.GetChatRoom(chatRoomID);
		if (chat_room != nullptr) {
			return chat_room->GetMemberCount();
		}
		else {
			return 0;
		}
	}

	GalaxyID ChatImpl::GetChatRoomMemberUserIDByIndex(ChatRoomID chatRoomID, uint32_t index) {
		tracer::Trace trace{ __FUNCTION__ };

		lock_t lock{ mtx };
		auto chat_room = chatroom_manager.GetChatRoom(chatRoomID);
		if (chat_room != nullptr) {
			return container_get_by_index(chat_room->GetMembers(), index);
		}
		else {
			return 0;
		}
	}

	uint32_t ChatImpl::GetChatRoomUnreadMessageCount(ChatRoomID chatRoomID) {
		tracer::Trace trace{ __FUNCTION__ };

		lock_t lock{ mtx };
		auto chat_room = chatroom_manager.GetChatRoom(chatRoomID);
		if (chat_room != nullptr) {
			return chat_room->GetUnreadCount();
		}
		else {
			return 0;
		}
	}

	void ChatImpl::MarkChatRoomAsRead(ChatRoomID chatRoomID) {
		tracer::Trace trace{ __FUNCTION__ };

		lock_t lock{ mtx };
		auto chat_room = chatroom_manager.GetChatRoom(chatRoomID);
		if (chat_room != nullptr) {
			chat_room->MarkAsRead();
		}
	}
}
#endif
