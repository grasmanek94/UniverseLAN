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
		 * Listener for the event of retrieving a chat room with a specified user.
		 *
		 * @remark This class is experimental and may change in the future.
		 */
		class IChatRoomWithUserRetrieveListener : public GalaxyTypeAwareListener<CHAT_ROOM_WITH_USER_RETRIEVE_LISTENER>
		{
		public:

			/**
			 * Notification for the event of retrieving a chat room with a specified user.
			 *
			 * @remark This method is experimental and may change in the future.
			 *
			 * @param userID The ID of the user with whom a chat room was requested.
			 * @param chatRoomID The ID of the retrieved chat room.
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
			 * @remark This method is experimental and may change in the future.
			 *
			 * @param userID The ID of the user with whom a chat room was requested.
			 * @param failureReason The cause of the failure.
			 */
			virtual void OnChatRoomWithUserRetrieveFailure(GalaxyID userID, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of IChatRoomWithUserRetrieveListener.
		 */
		typedef SelfRegisteringListener<IChatRoomWithUserRetrieveListener> GlobalChatRoomWithUserRetrieveListener;

		/**
		 * Listener for the event of sending a chat room message.
		 *
		 * @remark This class is experimental and may change in the future.
		 */
		class IChatRoomMessageSendListener : public GalaxyTypeAwareListener<CHAT_ROOM_MESSAGE_SEND_LISTENER>
		{
		public:

			/**
			 * Notification for the event of sending a chat room message.
			 *
			 * @remark This method is experimental and may change in the future.
			 *
			 * @param chatRoomID The ID of the chat room.
			 * @param sentMessageIndex The internal index of the sent message.
			 * @param messageID The ID of the sent message.
			 * @param sendTime The time at which the message was sent.
			 */
			virtual void OnChatRoomMessageSendSuccess(ChatRoomID chatRoomID, uint32_t sentMessageIndex, ChatMessageID messageID, uint32_t sendTime) = 0;

			/**
			 * The reason of a failure in sending a message to a chat room.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_FORBIDDEN ///< Message sending in the chat room is forbidden for the user.
			};

			/**
			 * Notification for the event of a failure in sending a message to a chat room.
			 *
			 * @remark This method is experimental and may change in the future.
			 *
			 * @param chatRoomID The ID of the chat room.
			 * @param sentMessageIndex The internal index of the sent message.
			 * @param failureReason The cause of the failure.
			 */
			virtual void OnChatRoomMessageSendFailure(ChatRoomID chatRoomID, uint32_t sentMessageIndex, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of ILobbyMessageListener.
		 */
		typedef SelfRegisteringListener<IChatRoomMessageSendListener> GlobalChatRoomMessageSendListener;

		/**
		 * Listener for the event of receiving chat room messages.
		 *
		 * @remark This class is experimental and may change in the future.
		 */
		class IChatRoomMessagesListener : public GalaxyTypeAwareListener<CHAT_ROOM_MESSAGES_LISTENER>
		{
		public:

			/**
			 * Notification for the event of receiving chat room messages.
			 *
			 * In order to read subsequent messages, call IChat::GetChatRoomMessageByIndex().
			 *
			 * @remark This method is experimental and may change in the future.
			 *
			 * @remark First invocation of this notification initiates the dialog
			 * in the specified chat room on the receiving side. Chat room data is
			 * available at the time this notification comes.
			 *
			 * @param chatRoomID The ID of the chat room.
			 * @param messageCount The amount of messages received in the chat room.
			 * @param longestMessageLenght The length of the longest message.
			 */
			virtual void OnChatRoomMessagesReceived(ChatRoomID chatRoomID, uint32_t messageCount, uint32_t longestMessageLenght) = 0;
		};

		/**
		 * Globally self-registering version of IChatRoomMessagesListener.
		 */
		typedef SelfRegisteringListener<IChatRoomMessagesListener> GlobalChatRoomMessagesListener;

		/**
		 * The interface for chat communication with other Galaxy Users.
		 *
		 * @remark This class is experimental and may change in the future.
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
			 * @remark This method is experimental and may change in the future.
			 *
			 * @param userID The ID of the interlocutor user.
			 */
			virtual void RequestChatRoomWithUser(GalaxyID userID) = 0;

			/**
			 * Sends a message to a chat room.
			 *
			 * This call is asynchronous. Result of sending message comes to the
			 * IChatRoomMessageSendListener. If message was sent successfully,
			 * for all the members in the chat room comes a notification to the
			 * IChatRoomMessageReceiveListener.
			 *
			 * @remark This method is experimental and may change in the future.
			 *
			 * @remark The user needs to be in the chat room in order to send a message
			 * to its members.
			 *
			 * @remark Internal message index returned by this method should only be used
			 * to identify sent messages in callbacks that come to the IChatRoomMessageSendListener.
			 *
			 * @param chatRoomID The ID of the chat room.
			 * @param msg The message to send.
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
			 * @remark This method is experimental and may change in the future.
			 *
			 * @remark This method can be used only inside of
			 * IChatRoomMessagesListener::OnChatRoomMessagesReceived().
			 *
			 * @param index Index of the incomming message as an integer in the range of [0, number of messages).
			 * @param messageID Global ID of the message.
			 * @param senderID The ID of the sender of the message.
			 * @param sendTime The time when the message was sent.
			 * @param buffer The output buffer.
			 * @param bufferLength The size of the output buffer.
			 * @return Actual message size in bytes.
			 */
			virtual uint32_t GetChatRoomMessageByIndex(uint32_t index, ChatMessageID& messageID, GalaxyID& senderID, uint32_t& sendTime, char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Returns the number of users in a specified chat room.
			 *
			 * @remark This method is experimental and may change in the future.
			 *
			 * @param chatRoomID The ID of the chat room.
			 * @return The number of users in the specified chat room.
			 */
			virtual uint32_t GetChatRoomMemberCount(ChatRoomID chatRoomID) = 0;

			/**
			 * Returns the GalaxyID of a user in a specified chat room.
			 *
			 * The user must be in the specified chat room in order to retrieve the room members.
			 *
			 * @remark This method is experimental and may change in the future.
			 *
			 * @param chatRoomID The ID of the chat room.
			 * @param index Index as an integer in the range of [0, number of chat room members).
			 * @return The ID of the chat room member.
			 */
			virtual GalaxyID GetChatRoomMemberUserIDByIndex(ChatRoomID chatRoomID, uint32_t index) = 0;

			/**
			 * Marks a specified chat room as read.
			 *
			 * @remark This method is experimental and may change in the future.
			 *
			 * @remark Marks all the messages in the specified chat room
			 * up to the last one received as read.
			 *
			 * @param chatRoomID The ID of the chat room.
			 */
			virtual void MarkChatRoomAsRead(ChatRoomID chatRoomID) = 0;
		};

		/** @} */
	}
}

#endif