#ifndef LSFDRMFG_IMPL_CHAT_H
#define LSFDRMFG_IMPL_CHAT_H

/**
 * @file
 * Contains data structures and interfaces related to chat communication
 * with other Galaxy Users.
 */

#include "ListenerRegistrar.hxx"

#include <IChat.h>
#include <IListenerRegistrar.h>
#include <GalaxyID.h>

#include "InterfaceInstances.hxx"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * The interface for chat communication with other Galaxy Users.
		 */
		class ChatImpl : public IChat
		{
		private:
			InterfaceInstances* intf;
			ListenerRegistrarImpl* listeners;

		public:

			ChatImpl(InterfaceInstances* intf);
			virtual ~ChatImpl();

			/**
			 * Creates new, or retrieves already existing one-on-one chat room with a specified user.
			 *
			 * This call is asynchronous. Response comes to the IChatRoomWithUserRetrieveListener,
			 * provided that the chat room was created successfully, in which case chat room data
			 * is immediately available.
			 *
			 * @param [in] userID The ID of the interlocutor user.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void RequestChatRoomWithUser(GalaxyID userID, IChatRoomWithUserRetrieveListener* const listener = NULL) override;

			/**
			 * Retrieves historical messages in a specified chat room.
			 *
			 * This call is asynchronous. Response comes to the IChatRoomMessagesRetrieveListener.
			 *
			 * The list of retrieved messages contains a limited number of the latest messages
			 * that were sent prior to the one specified as the optional reference message.
			 *
			 * @pre The user must be in the specified chat room in order to retrieve the messages.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @param [in] limit The maximum number of messages to retrieve or 0 for using default.
			 * @param [in] referenceMessageID The ID of the oldest of the messages that were already retrieved.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void RequestChatRoomMessages(ChatRoomID chatRoomID, uint32_t limit, ChatMessageID referenceMessageID = 0, IChatRoomMessagesRetrieveListener* const listener = NULL) override;

			/**
			 * Sends a message to a chat room.
			 *
			 * This call is asynchronous. Result of sending message comes to the
			 * IChatRoomMessageSendListener. If message was sent successfully,
			 * for all the members in the chat room there comes a notification
			 * to the IChatRoomMessagesListener.
			 *
			 * @remark Internal message index returned by this method should only be used
			 * to identify sent messages in callbacks that come to the IChatRoomMessageSendListener.
			 *
			 * @pre The user needs to be in the chat room in order to send a message to its members.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @param [in] msg The message to send.
			 * @param [in] listener The listener for specific operation.
			 * @return Internal message index.
			 */
			virtual uint32_t SendChatRoomMessage(ChatRoomID chatRoomID, const char* msg, IChatRoomMessageSendListener* const listener = NULL) override;

			/**
			 * Reads an incoming chat room message by index.
			 *
			 * This call is non-blocking and operates on the messages available
			 * in the IChatRoomMessagesListener, thus instantly finishes.
			 *
			 * If the buffer that is supposed to take the message is too small,
			 * the message will be truncated to its size. The size of the longest message
			 * is provided in the notification about an incoming message from
			 * IChatRoomMessagesListener::OnChatRoomMessagesReceived().
			 *
			 * @remark This method can be used only inside of IChatRoomMessagesListener::OnChatRoomMessagesReceived().
			 *
			 * @param [in] index Index of the incomming message as an integer in the range of [0, number of messages).
			 * @param [out] messageID Global ID of the message.
			 * @param [out] messageType The type of the message.
			 * @param [out] senderID The ID of the sender of the message.
			 * @param [out] sendTime The time when the message was sent.
			 * @param [in, out] buffer The output buffer.
			 * @param [in] bufferLength The size of the output buffer.
			 * @return Actual message size in bytes.
			 */
			virtual uint32_t GetChatRoomMessageByIndex(uint32_t index, ChatMessageID& messageID, ChatMessageType& messageType, GalaxyID& senderID, uint32_t& sendTime, char* buffer, uint32_t bufferLength) override;

			/**
			 * Returns the number of users in a specified chat room.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @return The number of users in the specified chat room.
			 */
			virtual uint32_t GetChatRoomMemberCount(ChatRoomID chatRoomID) override;

			/**
			 * Returns the GalaxyID of a user in a specified chat room.
			 *
			 * @pre The user must be in the specified chat room in order to retrieve the room members.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @param [in] index Index as an integer in the range of [0, number of chat room members).
			 * @return The ID of the chat room member.
			 */
			virtual GalaxyID GetChatRoomMemberUserIDByIndex(ChatRoomID chatRoomID, uint32_t index) override;

			/**
			 * Returns the number of unread messages in a specified chat room.
			 *
			 * @pre The user must be in the specified chat room in order to retrieve the message count.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @return The number of unread messages in the chat room.
			 */
			virtual uint32_t GetChatRoomUnreadMessageCount(ChatRoomID chatRoomID) override;

			/**
			 * Marks a specified chat room as read.
			 *
			 * Marks all the messages in the specified chat room up to the one received last as read.
			 *
			 * @remark The user should have read messages in the specified chat room in order to mark it as read.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 */
			virtual void MarkChatRoomAsRead(ChatRoomID chatRoomID) override;
		};

		/** @} */
	}
}

#endif
