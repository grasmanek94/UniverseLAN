#include "CustomNetworking.hxx"

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

namespace galaxy
{
	namespace api
	{
		// TODO: add data listener event
		CustomNetworkingImpl::Channel::Channel(CustomNetworkingImpl* custom_network)
			: custom_network{ custom_network }, client{}, runner{}, connection{}, 
			listener_open{}, listener_data{}, listener_close{}, connection_string{},
			mtx{}, buffer{}
		{ }

		void CustomNetworkingImpl::Channel::connect(const char* connectionString, IConnectionOpenListener* listener)
		{
			// Initialize ASIO
			client.init_asio();

			// Register our message handler
			client.set_open_handler(bind(&CustomNetworkingImpl::WebSocketOnOpen, custom_network, shared_from_this(), ::_1));
			client.set_message_handler(bind(&CustomNetworkingImpl::WebSocketOnMessage, custom_network, shared_from_this(), ::_1, ::_2));
			client.set_close_handler(bind(&CustomNetworkingImpl::WebSocketOnClose, custom_network, shared_from_this(), ::_1));
			client.set_fail_handler(bind(&CustomNetworkingImpl::WebSocketOnFail, custom_network, shared_from_this(), ::_1));

			websocketpp::lib::error_code ec;
			custom_networking::client::connection_ptr con = client.get_connection(connectionString, ec);
			connection_string = connectionString;
			listener_open = listener;

			if (ec) {
				std::cerr << "CustomNetworking: Could not create connection because: " << ec.message() << std::endl;
				if (listener_open) {
					listener_open->OnConnectionOpenFailure(connectionString, IConnectionOpenListener::FAILURE_REASON_CONNECTION_FAILURE);
				}
				return;
			}

			client.connect(con);

			runner = std::jthread(&custom_networking::client::run, &client);
		}

		CustomNetworkingImpl::Channel::~Channel()
		{
			if (connection) {
				connection->close(websocketpp::close::status::normal, "normal");
				client.stop();
				if (runner.joinable()) {
					runner.join();
				}
			}
		}

		CustomNetworkingImpl::CustomNetworkingImpl() :
			channels{}
		{ }

		CustomNetworkingImpl::~CustomNetworkingImpl()
		{ }

		void CustomNetworkingImpl::WebSocketOnOpen(std::shared_ptr<Channel> channel, websocketpp::connection_hdl hdl)
		{
			if (channel->listener_open != nullptr) {
				channel->listener_open->OnConnectionOpenSuccess(channel->connection_string.c_str(), (ConnectionID)channel.get());
			}
		}

		void CustomNetworkingImpl::WebSocketOnMessage(std::shared_ptr<Channel> channel, websocketpp::connection_hdl hdl, custom_networking::message_ptr msg)
		{
			std::scoped_lock<std::mutex> guard(channel->mtx);
			const std::string& data = msg->get_payload();

			channel->buffer.insert(channel->buffer.end(), data.c_str(), data.c_str() + data.size());
		}

		void CustomNetworkingImpl::WebSocketOnClose(std::shared_ptr<Channel> channel, websocketpp::connection_hdl hdl)
		{
			if (channel->listener_close) {
				channel->listener_close->OnConnectionClosed((ConnectionID)channel.get(), IConnectionCloseListener::CLOSE_REASON_UNDEFINED);
			}
		}

		void CustomNetworkingImpl::WebSocketOnFail(std::shared_ptr<Channel> channel, websocketpp::connection_hdl hdl)
		{
			switch (channel->connection->get_state()) 
			{
			case websocketpp::session::state::connecting:
				if (channel->listener_open) {
					channel->listener_open->OnConnectionOpenFailure(channel->connection_string.c_str(), IConnectionOpenListener::FAILURE_REASON_CONNECTION_FAILURE);
				}
				break;
			case websocketpp::session::state::open:
				
				break;
			case websocketpp::session::state::closing:

				break;
			case websocketpp::session::state::closed:

				break;
			}
		}

		void CustomNetworkingImpl::OpenConnection(const char* connectionString, IConnectionOpenListener* const listener) {
			auto channel = std::make_shared<Channel>(this);

			channels.emplace((ConnectionID)channel.get(), channel);

			channel->connect(connectionString, listener);
		}

		void CustomNetworkingImpl::CloseConnection(ConnectionID connectionID, IConnectionCloseListener* const listener) {
			auto entry = channels.find(connectionID);
			if (entry == channels.end()) {
				return;
			}

			auto& channel = entry->second;

			channel->listener_close = listener;
			channel->connection->close(websocketpp::close::status::normal, "normal");
		}

		void CustomNetworkingImpl::SendData(ConnectionID connectionID, const void* data, uint32_t dataSize) {

			auto entry = channels.find(connectionID);
			if (entry == channels.end()) {
				return;
			}

			auto& channel = entry->second;

			channel->connection->send(std::string((const char*)data, dataSize), websocketpp::frame::opcode::value::BINARY);
		}

		uint32_t CustomNetworkingImpl::GetAvailableDataSize(ConnectionID connectionID) {
			auto entry = channels.find(connectionID);
			if (entry == channels.end()) {
				return 0;
			}

			auto& channel = entry->second;

			return (uint32_t)channel->buffer.size();
		}

		void CustomNetworkingImpl::PeekData(ConnectionID connectionID, void* dest, uint32_t dataSize) {
			auto entry = channels.find(connectionID);
			if (entry == channels.end()) {
				return;
			}

			auto& channel = entry->second;

			std::scoped_lock<std::mutex> guard(channel->mtx);
			std::copy_n(channel->buffer.begin(), std::min(dataSize, (uint32_t)channel->buffer.size()), (char*)dest);
		}

		void CustomNetworkingImpl::ReadData(ConnectionID connectionID, void* dest, uint32_t dataSize) {
			auto entry = channels.find(connectionID);
			if (entry == channels.end()) {
				return;
			}

			auto& channel = entry->second;

			std::scoped_lock<std::mutex> guard(channel->mtx);
			size_t size = std::min(dataSize, (uint32_t)channel->buffer.size());
			std::copy_n(channel->buffer.begin(), size, (char*)dest);
			channel->buffer.erase(channel->buffer.begin(), channel->buffer.begin() + size);
		}

		void CustomNetworkingImpl::PopData(ConnectionID connectionID, uint32_t dataSize) {
			auto entry = channels.find(connectionID);
			if (entry == channels.end()) {
				return;
			}

			auto& channel = entry->second;

			std::scoped_lock<std::mutex> guard(channel->mtx);
			size_t size = std::min(dataSize, (uint32_t)channel->buffer.size());
			channel->buffer.erase(channel->buffer.begin(), channel->buffer.begin() + size);
		}
	}
}
