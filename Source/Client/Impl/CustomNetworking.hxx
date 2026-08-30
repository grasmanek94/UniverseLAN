#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING

/**
 * @file
 * Contains data structures and interfaces related to communicating with custom endpoints.
 * @warning This API is experimental and can be changed or removed in following releases.
 */

#include "ListenerRegistrar.hxx"

#include <ICustomNetworking.h>
#include <IListenerRegistrar.h>

#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXWebSocketMessage.h>

#include <atomic>
#include <deque>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <unordered_map>

namespace universelan::client {
	using namespace galaxy::api;
	struct InterfaceInstances;

	namespace custom_networking
	{
		using client = ix::WebSocket;
	}
	/**
	 * @addtogroup api
	 * @{
	 */

	 /**
	  * The interface for communicating with a custom endpoint.
	  */
	class CustomNetworkingImpl : public ICustomNetworking
	{
	public:
		using mutex_t = std::recursive_mutex;
		using lock_t = std::scoped_lock<mutex_t>;

		struct Channel : public std::enable_shared_from_this<Channel> {
			ListenerRegistrarImpl* listeners;
			custom_networking::client client;
			IConnectionOpenListener* listener_open;
			IConnectionDataListener* listener_data;
			IConnectionCloseListener* listener_close;
			std::string connection_string;

			mutex_t buffer_mtx;
			std::deque<char> buffer;
			std::atomic_bool cleanup{ false };

			Channel(CustomNetworkingImpl* custom_network);
			bool connect(const char* connectionString, IConnectionOpenListener* listener);
			virtual ~Channel();
			void close();

			void WebSocketOnOpen();
			void WebSocketOnMessage(const std::string& data, const bool binary);
			void WebSocketOnClose();
			void WebSocketOnFail(const std::string& reason);

			void WebSocketCallback(const ix::WebSocketMessagePtr& message);
		};

	private:
		ListenerRegistrarImpl* listeners;
		mutable mutex_t mtx;
		std::unordered_map<ConnectionID, std::shared_ptr<Channel>> channels;

		std::shared_ptr<Channel> GetChannel(ConnectionID connectionID) const;

		void PerformCleanup();
	public:

		CustomNetworkingImpl(InterfaceInstances* intf);
		virtual ~CustomNetworkingImpl() override;

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
		virtual void OpenConnection(const char* connectionString
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
			, IConnectionOpenListener* const listener = NULL
#endif
		) override;

		/**
		 * Close a connection.
		 *
		 * This call is asynchronous. Responses come to the IConnectionCloseListener.
		 *
		 * @param [in] connectionID The ID of the connection.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void CloseConnection(ConnectionID connectionID
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
			, IConnectionCloseListener* const listener = NULL
#endif
		) override;

		/**
		 * Send binary data over a specific connection.
		 *
		 * @param [in] connectionID The ID of the connection.
		 * @param [in] data The data to send.
		 * @param [in] dataSize The size of the data.
		 */
		virtual void SendData(ConnectionID connectionID, const void* data, uint32_t dataSize) override;

		/**
		 * Returns the number of bytes in a specific connection incoming buffer.
		 *
		 * @param [in] connectionID The ID of the connection.
		 * @return The number of bytes in the connection incomming buffer.
		 */
		virtual uint32_t GetAvailableDataSize(ConnectionID connectionID) override;

		/**
		 * Reads binary data received from a specific connection.
		 * The data that was read this way is left in the connection incomming buffer.
		 *
		 * @param [in] connectionID The ID of the connection.
		 * @param [in, out] dest The buffer to pass the data to.
		 * @param [in] dataSize The size of the data.
		 */
		virtual void PeekData(ConnectionID connectionID, void* dest, uint32_t dataSize) override;

		/**
		 * Reads binary data received from a specific connection.
		 * The data that was read this way is removed from the connection incomming buffer.
		 *
		 * @param [in] connectionID The ID of the connection.
		 * @param [in, out] dest The buffer to pass the data to.
		 * @param [in] dataSize The size of the data.
		 */
		virtual void ReadData(ConnectionID connectionID, void* dest, uint32_t dataSize) override;

		/**
		 * Removes a given number of bytes from a specific connection incomming buffer.
		 *
		 * @param [in] connectionID The ID of the connection.
		 * @param [in] dataSize The numbers of bytes to be removed from the buffer.
		 */
		virtual void PopData(ConnectionID connectionID, uint32_t dataSize) override;
	};

	/** @} */
}

#endif
