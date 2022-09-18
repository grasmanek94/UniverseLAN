#include "Chat.hxx"

#include "UniverseLAN.hxx"

#include <Networking/Messages/RequestChatRoomWithUserMessage.hxx>

namespace universelan::client {
	using namespace galaxy::api;
	ChatImpl::ChatImpl(InterfaceInstances* intf) 
		: intf{ intf }, listeners{ intf->notification.get() },
		request_chat_room_with_user_requests{}
	{}

	ChatImpl::~ChatImpl()
	{
	}

	void ChatImpl::RequestChatRoomWithUser(GalaxyID userID, IChatRoomWithUserRetrieveListener* const listener) {
		uint64_t request_id = MessageUniqueID::get();

		request_chat_room_with_user_requests.emplace(request_id, listener);
		intf->client->GetConnection().SendAsync(RequestChatRoomWithUserMessage{ request_id, userID });
	}

	void ChatImpl::RequestChatRoomMessages(ChatRoomID chatRoomID, uint32_t limit, ChatMessageID referenceMessageID, IChatRoomMessagesRetrieveListener* const listener) {

	}

	uint32_t ChatImpl::SendChatRoomMessage(ChatRoomID chatRoomID, const char* msg, IChatRoomMessageSendListener* const listener) {
		return 0;
	}

	uint32_t ChatImpl::GetChatRoomMessageByIndex(uint32_t index, ChatMessageID& messageID, ChatMessageType& messageType, GalaxyID& senderID, uint32_t& sendTime, char* buffer, uint32_t bufferLength) {
		return 0;
	}

	uint32_t ChatImpl::GetChatRoomMemberCount(ChatRoomID chatRoomID) {
		return 0;
	}

	GalaxyID ChatImpl::GetChatRoomMemberUserIDByIndex(ChatRoomID chatRoomID, uint32_t index) {
		return 0;
	}

	uint32_t ChatImpl::GetChatRoomUnreadMessageCount(ChatRoomID chatRoomID) {
		return 0;
	}

	void ChatImpl::MarkChatRoomAsRead(ChatRoomID chatRoomID) {

	}
}
