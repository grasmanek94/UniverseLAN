#ifndef GALAXY_I_CHAT_H
#define GALAXY_I_CHAT_H

/**
 * @file
 * Contains data structures and interfaces related to chat communication
 * with other Galaxy Users.
 */

#include "IListenerRegistrar.h"
#include "GalaxyID.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * The ID of a chat room.
		 */
		typedef uint64_t ChatRoomID;

		/**
		 * Global ID of a chat message.
		 */
		typedef uint64_t ChatMessageID;

		/**
		 * The type of a chat message.
		 */
		enum ChatMessageType
		{
			CHAT_MESSAGE_TYPE_UNKNOWN = 0, ///< Unknown message type.
			CHAT_MESSAGE_TYPE_CHAT_MESSAGE = 1, ///< Chat message.
			CHAT_MESSAGE_TYPE_GAME_INVITATION = 2 ///< Game invitation.
		};

		/**
		 * Listener for the event of retrieving a chat room with a specified user.
		 */
		class IChatRoomWithUserRetrieveListener : public GalaxyTypeAwareListener<CHAT_ROOM_WITH_USER_RETRIEVE_LISTENER>
		{
		public:

			/**
			 * Notification for the event of retrieving a chat room with a specified user.
			 *
			 * @param [in] userID The ID of the user with whom a chat room was requested.
			 * @param [in] chatRoomID The ID of the retrieved chat room.
			 */
			virtual void OnChatRoomWithUserRetrieveSuccess(GalaxyID userID, ChatRoomID chatRoomID) = 0;

			/**
			 * The reason of a failure in retrieving a chat room with a specified user.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_FORBIDDEN ///< Communication with a specified user is not allowed.
			};

			/**
			 * Notification for the event of a failure in retrieving a chat room with a specified user.
			 *
			 * @param [in] userID The ID of the user with whom a chat room was requested.
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnChatRoomWithUserRetrieveFailure(GalaxyID userID, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of IChatRoomWithUserRetrieveListener.
		 */
		typedef SelfRegisteringListener<IChatRoomWithUserRetrieveListener> GlobalChatRoomWithUserRetrieveListener;

		/**
		 * Listener for the event of sending a chat room message.
		 */
		class IChatRoomMessageSendListener : public GalaxyTypeAwareListener<CHAT_ROOM_MESSAGE_SEND_LISTENER>
		{
		public:

			/**
			 * Notification for the event of sending a chat room message.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @param [in] sentMessageIndex The internal index of the sent message.
			 * @param [in] messageID The ID of the sent message.
			 * @param [in] sendTime The time at which the message was sent.
			 */
			virtual void OnChatRoomMessageSendSuccess(ChatRoomID chatRoomID, uint32_t sentMessageIndex, ChatMessageID messageID, uint32_t sendTime) = 0;

			/**
			 * The reason of a failure in sending a message to a chat room.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_FORBIDDEN ///< Sending messages to the chat room is forbidden for the user.
			};

			/**
			 * Notification for the event of a failure in sending a message to a chat room.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @param [in] sentMessageIndex The internal index of the sent message.
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnChatRoomMessageSendFailure(ChatRoomID chatRoomID, uint32_t sentMessageIndex, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of IChatRoomMessageSendListener.
		 */
		typedef SelfRegisteringListener<IChatRoomMessageSendListener> GlobalChatRoomMessageSendListener;

		/**
		 * Listener for the event of receiving chat room messages.
		 */
		class IChatRoomMessagesListener : public GalaxyTypeAwareListener<CHAT_ROOM_MESSAGES_LISTENER>
		{
		public:

			/**
			 * Notification for the event of receiving chat room messages.
			 *
			 * In order to read subsequent messages, call IChat::GetChatRoomMessageByIndex().
			 *
			 * @remark First invocation of this notification initiates the dialog
			 * in the specified chat room on the receiving side. Chat room data is
			 * available at the time this notification comes.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @param [in] messageCount The amount of messages received in the chat room.
			 * @param [in] longestMessageLenght The length of the longest message.
			 */
			virtual void OnChatRoomMessagesReceived(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght) = 0;
		};

		/**
		 * Globally self-registering version of IChatRoomMessagesListener.
		 */
		typedef SelfRegisteringListener<IChatRoomMessagesListener> GlobalChatRoomMessagesListener;

		/**
		 * Listener for the event of retrieving chat room messages in a specified chat room.
		 */
		class IChatRoomMessagesRetrieveListener : public GalaxyTypeAwareListener<CHAT_ROOM_MESSAGES_RETRIEVE_LISTENER>
		{
		public:

			/**
			 * Notification for the event of retrieving chat room messages in a specified chat room.
			 *
			 * In order to read subsequent messages, call IChat::GetChatRoomMessageByIndex().
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @param [in] messageCount The amount of messages received in the chat room.
			 * @param [in] longestMessageLenght The length of the longest message.
			 */
			virtual void OnChatRoomMessagesRetrieveSuccess(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght) = 0;

			/**
			 * The reason of a failure in retrieving chat room messages in a specified chat room.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_FORBIDDEN ///< Retrieving messages from the chat room is forbidden for the user.
			};

			/**
			 * Notification for the event of a failure in retrieving chat room messages in a specified chat room.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnChatRoomMessagesRetrieveFailure(ChatRoomID chatRoomID, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of IChatRoomMessagesRetrieveListener.
		 */
		typedef SelfRegisteringListener<IChatRoomMessagesRetrieveListener> GlobalChatRoomMessagesRetrieveListener;

		/**
		 * The interface for chat communication with other Galaxy Users.
		 */
		class IChat
		{
		public:

			virtual ~IChat()
			{
			}

			/**
			 * Creates new, or retrieves already existing one-on-one chat room with a specified user.
			 *
			 * This call is asynchronous. Response comes to the IChatRoomWithUserRetrieveListener,
			 * provided that the chat room was created successfully, in which case chat room data
			 * is immediately available.
			 *
			 * @param [in] userID The ID of the interlocutor user.
			 */
			virtual void RequestChatRoomWithUser(GalaxyID userID) = 0;

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
			 */
			virtual void RequestChatRoomMessages(ChatRoomID chatRoomID, uint32_t limit, ChatMessageID referenceMessageID = 0) = 0;

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
			 * @return Internal message index.
			 */
			virtual uint32_t SendChatRoomMessage(ChatRoomID chatRoomID, const char* msg) = 0;

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
			virtual uint32_t GetChatRoomMessageByIndex(uint32_t index, ChatMessageID& messageID, ChatMessageType& messageType, GalaxyID& senderID, uint32_t& sendTime, char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Returns the number of users in a specified chat room.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @return The number of users in the specified chat room.
			 */
			virtual uint32_t GetChatRoomMemberCount(ChatRoomID chatRoomID) = 0;

			/**
			 * Returns the GalaxyID of a user in a specified chat room.
			 *
			 * @pre The user must be in the specified chat room in order to retrieve the room members.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @param [in] index Index as an integer in the range of [0, number of chat room members).
			 * @return The ID of the chat room member.
			 */
			virtual GalaxyID GetChatRoomMemberUserIDByIndex(ChatRoomID chatRoomID, uint32_t index) = 0;

			/**
			 * Returns the number of unread messages in a specified chat room.
			 *
			 * @pre The user must be in the specified chat room in order to retrieve the message count.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 * @return The number of unread messages in the chat room.
			 */
			virtual uint32_t GetChatRoomUnreadMessageCount(ChatRoomID chatRoomID) = 0;

			/**
			 * Marks a specified chat room as read.
			 *
			 * Marks all the messages in the specified chat room up to the one received last as read.
			 *
			 * @remark The user should have read messages in the specified chat room in order to mark it as read.
			 *
			 * @param [in] chatRoomID The ID of the chat room.
			 */
			virtual void MarkChatRoomAsRead(ChatRoomID chatRoomID) = 0;
		};

		/** @} */
	}
}

#endif
