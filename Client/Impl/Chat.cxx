#include "Chat.hxx"

namespace galaxy
{
	namespace api
	{
		ChatImpl::ChatImpl(ListenerRegistrarImpl* listeners) : listeners{ listeners }
		{}

		ChatImpl::~ChatImpl()
		{
		}

		void ChatImpl::RequestChatRoomWithUser(GalaxyID userID, IChatRoomWithUserRetrieveListener* const listener) {

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
}
