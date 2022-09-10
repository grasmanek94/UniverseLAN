/**
 * @file
 * Contains data structures and interfaces related to communicating with custom endpoints.
 * @warning This API is experimental and can be changed or removed in following releases.
 */

#include "ICustomNetworking.h"
#include "IListenerRegistrar.h"

#include "CustomNetworking.hxx"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		 /**
		  * The interface for communicating with a custom endpoint.
		  */

		CustomNetworking::~CustomNetworking()
		{
		}

		/**
		 * Open a connection with a specific endpoint.
		 *
		 * This call is asynchronous. Responses come to the IConnectionOpenListener.
		 *
		 * @remark Currently only supported connection string is a WebSocket URL (e.g. ws://example.com:8000/path/to/ws).
		 *
		 * @param [in] connectionString The string which contains connection info.
		 * @param [in] listener The listener for specific operation.
		 */
		void CustomNetworking::OpenConnection(const char* connectionString, IConnectionOpenListener* const listener) {

		}

		/**
		 * Close a connection.
		 *
		 * This call is asynchronous. Responses come to the IConnectionCloseListener.
		 *
		 * @param [in] connectionID The ID of the connection.
		 * @param [in] listener The listener for specific operation.
		 */
		void CustomNetworking::CloseConnection(ConnectionID connectionID, IConnectionCloseListener* const listener) {

		}

		/**
		 * Send binary data over a specific connection.
		 *
		 * @param [in] connectionID The ID of the connection.
		 * @param [in] data The data to send.
		 * @param [in] dataSize The size of the data.
		 */
		void CustomNetworking::SendData(ConnectionID connectionID, const void* data, uint32_t dataSize) {

		}

		/**
		 * Returns the number of bytes in a specific connection incoming buffer.
		 *
		 * @param [in] connectionID The ID of the connection.
		 * @return The number of bytes in the connection incomming buffer.
		 */
		uint32_t CustomNetworking::GetAvailableDataSize(ConnectionID connectionID) {
			return 0;
		}

		/**
		 * Reads binary data received from a specific connection.
		 * The data that was read this way is left in the connection incomming buffer.
		 *
		 * @param [in] connectionID The ID of the connection.
		 * @param [in, out] dest The buffer to pass the data to.
		 * @param [in] dataSize The size of the data.
		 */
		void CustomNetworking::PeekData(ConnectionID connectionID, void* dest, uint32_t dataSize) {

		}

		/**
		 * Reads binary data received from a specific connection.
		 * The data that was read this way is removed from the connection incomming buffer.
		 *
		 * @param [in] connectionID The ID of the connection.
		 * @param [in, out] dest The buffer to pass the data to.
		 * @param [in] dataSize The size of the data.
		 */
		void CustomNetworking::ReadData(ConnectionID connectionID, void* dest, uint32_t dataSize) {

		}

		/**
		 * Removes a given number of bytes from a specific connection incomming buffer.
		 *
		 * @param [in] connectionID The ID of the connection.
		 * @param [in] dataSize The numbers of bytes to be removed from the buffer.
		 */
		void CustomNetworking::PopData(ConnectionID connectionID, uint32_t dataSize) {

		}

		/** @} */
	}
}


