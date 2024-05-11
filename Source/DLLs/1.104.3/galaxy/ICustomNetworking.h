#ifndef GALAXY_I_CUSTOM_NETWORKING_H
#define GALAXY_I_CUSTOM_NETWORKING_H

/**
 * @file
 * Contains data structures and interfaces related to communicating with custom endpoints.
 * @warning This API is experimental and can be changed or removed in following releases.
 */

#include "IListenerRegistrar.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * ID of a connection.
		 */
		typedef uint64_t ConnectionID;

		/**
		 * Listener for the events related to opening a connection.
		 */
		class IConnectionOpenListener : public GalaxyTypeAwareListener<CUSTOM_NETWORKING_CONNECTION_OPEN>
		{
		public:

			/**
			 * Notification for the event of a success in opening a connection.
			 *
			 * @param connectionString The connection string.
			 * @param connectionID The ID if the connection.
			 */
			virtual void OnConnectionOpenSuccess(const char* connectionString, ConnectionID connectionID) = 0;

			/**
			 * The reason of a failure in opening a connection.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED ///< Unspecified error.
			};

			/**
			 * Notification for the event of a failure in opening a connection.
			 *
			 * @param connectionString The connection string.
			 * @param failureReason The cause of the failure.
			 */
			virtual void OnConnectionOpenFailure(const char* connectionString, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of IConnectionOpenListener.
		 */
		typedef SelfRegisteringListener<IConnectionOpenListener> GlobalConnectionOpenListener;

		/**
		 * Listener for the event of closing a connection.
		 *
		 */
		class IConnectionCloseListener : public GalaxyTypeAwareListener<CUSTOM_NETWORKING_CONNECTION_CLOSE>
		{
		public:

			/**
			 * The reason of closing a connection.
			 */
			enum CloseReason
			{
				CLOSE_REASON_UNDEFINED ///< Unspecified reason.
			};

			/**
			 * Notification for the event of closing a connection.
			 *
			 * @param connectionID The ID if the connection.
			 * @param closeReason The reason why the connection is being closed.
			 */
			virtual void OnConnectionClosed(ConnectionID connectionID, CloseReason closeReason) = 0;
		};

		/**
		 * Globally self-registering version of IConnectionCloseListener.
		 */
		typedef SelfRegisteringListener<IConnectionCloseListener> GlobalConnectionCloseListener;

		/**
		 * Listener for the event of receiving data over the connection.
		 */
		class IConnectionDataListener : public GalaxyTypeAwareListener<CUSTOM_NETWORKING_CONNECTION_DATA>
		{
		public:

			/**
			 * Notification for the event of receiving data over the connection.
			 *
			 * @param connectionID The ID if the connection.
			 * @param dataSize The amount of new data received (in bytes).
			 */
			virtual void OnConnectionDataReceived(ConnectionID connectionID, uint32_t dataSize) = 0;
		};

		/**
		 * Globally self-registering version of IConnectionDataListener.
		 */
		typedef SelfRegisteringListener<IConnectionDataListener> GlobalConnectionDataListener;

		/**
		 * The interface for communicating with a custom endpoint.
		 */
		class ICustomNetworking
		{
		public:

			virtual ~ICustomNetworking()
			{
			}

			/**
			 * Open a connection with a specific endpoint.
			 *
			 * This call is asynchronous. Responses come to the IConnectionOpenListener.
			 *
			 * @remark Currently only supported connection string is a WebSocket URL (e.g. ws://example.com:8000/path/to/ws).
			 *
			 * @param connectionString The string which contains connection info.
			 */
			virtual void OpenConnection(const char* connectionString) = 0;

			/**
			 * Close a connection.
			 *
			 * This call is asynchronous. Responses come to the IConnectionCloseListener.
			 *
			 * @param connectionID The ID of the connection.
			 */
			virtual void CloseConnection(ConnectionID connectionID) = 0;

			/**
			 * Send binary data over a specific connection.
			 *
			 * @param connectionID The ID of the connection.
			 * @param data The data to send.
			 * @param dataSize The size of the data.
			 */
			virtual void SendData(ConnectionID connectionID, const void* data, uint32_t dataSize) = 0;

			/**
			 * Returns the number of bytes in a specific connection incoming buffer.
			 *
			 * @param connectionID The ID of the connection.
			 * @return The number of bytes in the connection incomming buffer.
			 */
			virtual uint32_t GetAvailableDataSize(ConnectionID connectionID) = 0;

			/**
			 * Reads binary data received from a specific connection.
			 * The data that was read this way is left in the connection incomming buffer.
			 *
			 * @param connectionID The ID of the connection.
			 * @param dest The buffer to pass the data to.
			 * @param dataSize The size of the data.
			 */
			virtual void PeekData(ConnectionID connectionID, void* dest, uint32_t dataSize) = 0;

			/**
			 * Reads binary data received from a specific connection.
			 * The data that was read this way is removed from the connection incomming buffer.
			 *
			 * @param connectionID The ID of the connection.
			 * @param dest The buffer to pass the data to.
			 * @param dataSize The size of the data.
			 */
			virtual void ReadData(ConnectionID connectionID, void* dest, uint32_t dataSize) = 0;

			/**
			 * Removes a given number of bytes from a specific connection incomming buffer.
			 *
			 * @param connectionID The ID of the connection.
			 * @param dataSize The numbers of bytes to be removed from the buffer.
			 */
			virtual void PopData(ConnectionID connectionID, uint32_t dataSize) = 0;
		};

		/** @} */
	}
}

#endif