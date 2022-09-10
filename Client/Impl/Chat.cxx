#include "Chat.hxx"

namespace galaxy
{
	namespace api
	{
		Chat::~Chat()
		{
		}

		void Chat::RequestChatRoomWithUser(GalaxyID userID, IChatRoomWithUserRetrieveListener* const listener) {

		}

		void Chat::RequestChatRoomMessages(ChatRoomID chatRoomID, uint32_t limit, ChatMessageID referenceMessageID, IChatRoomMessagesRetrieveListener* const listener) {

		}

		uint32_t Chat::SendChatRoomMessage(ChatRoomID chatRoomID, const char* msg, IChatRoomMessageSendListener* const listener) {
			return 0;
		}

		uint32_t Chat::GetChatRoomMessageByIndex(uint32_t index, ChatMessageID& messageID, ChatMessageType& messageType, GalaxyID& senderID, uint32_t& sendTime, char* buffer, uint32_t bufferLength) {
			return 0;
		}

		uint32_t Chat::GetChatRoomMemberCount(ChatRoomID chatRoomID) {
			return 0;
		}

		GalaxyID Chat::GetChatRoomMemberUserIDByIndex(ChatRoomID chatRoomID, uint32_t index) {
			return 0;
		}

		uint32_t Chat::GetChatRoomUnreadMessageCount(ChatRoomID chatRoomID) {
			return 0;
		}

		void Chat::MarkChatRoomAsRead(ChatRoomID chatRoomID) {

		}
	}
}
