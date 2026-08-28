#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING

#include "CustomNetworking.hxx"

#include "UniverseLAN.hxx"

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

namespace universelan::client {
	using namespace galaxy::api;
	CustomNetworkingImpl::Channel::Channel(CustomNetworkingImpl* custom_network)
		: custom_network{ custom_network }, client{}, runner{}, connection{},
		listener_open{}, listener_data{}, listener_close{}, connection_string{},
		buffer_mtx{}, buffer{}
	{ }

	bool CustomNetworkingImpl::Channel::connect(const char* connectionString, IConnectionOpenListener* listener)
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		// REVIEW: A null connectionString is passed into websocketpp before the
		// error path can run. Validate the ABI input before initializing a
		// connection so malformed callers receive the documented failure.
		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format(
				"connectionString: {} listener: {}",
				connectionString, (void*)listener
			));
		}

		// Initialize ASIO
		client.init_asio();

		// Register our message handler
		client.set_open_handler(bind(&CustomNetworkingImpl::WebSocketOnOpen, custom_network, shared_from_this(), ::_1));
		client.set_message_handler(bind(&CustomNetworkingImpl::WebSocketOnMessage, custom_network, shared_from_this(), ::_1, ::_2));
		client.set_close_handler(bind(&CustomNetworkingImpl::WebSocketOnClose, custom_network, shared_from_this(), ::_1));
		client.set_fail_handler(bind(&CustomNetworkingImpl::WebSocketOnFail, custom_network, shared_from_this(), ::_1));

		websocketpp::lib::error_code ec;
		custom_networking::client::connection_ptr con = client.get_connection(connectionString, ec);
		// REVIEW: `con` is never stored in Channel::connection. CloseConnection
		// consequently cannot close the socket and SendData dereferences null;
		// assign the successful connection before starting the channel.
		connection_string = connectionString;
		listener_open = listener;

		if (ec) {
			std::cerr << "CustomNetworking: Could not create connection because: " << ec.message() << std::endl;

			if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
				trace.write_all(std::format("connect: false ec.message(): {}", ec.message()));
			}

			custom_network->listeners->NotifyAll(listener, &IConnectionOpenListener::OnConnectionOpenFailure, connectionString
#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_FAILURE_REASON
				, IConnectionOpenListener::FAILURE_REASON_CONNECTION_FAILURE
#else
				, IConnectionOpenListener::FAILURE_REASON_UNDEFINED
#endif
			);

			return false;
		}

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all("connect: true");
		}

		client.connect(con);

		return true;
	}

	void CustomNetworkingImpl::Channel::start()
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		runner = std::jthread(&CustomNetworkingImpl::ChannelThread, custom_network, shared_from_this());
	}

	void CustomNetworkingImpl::ChannelThread(std::shared_ptr<Channel> channel)
	{	
		tracer::Trace trace_start{ "::before_run", __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING};	

		channel->client.run(); // this blocks
	
		tracer::Trace trace_finish{ "::after_run", __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };	

		// delete
		{
			lock_t lock(mtx);
			// REVIEW: The map is keyed by the Channel address, but this erases
			// the CustomNetworkingImpl address (`this`). The completed channel
			// therefore remains in the map with a cleared connection and is
			// returned by later GetChannel calls; erase `channel.get()` instead.
			channels.erase((ConnectionID)this);
		}

		channel->custom_network = nullptr;
		channel->connection = nullptr;
		channel->listener_open = nullptr;
		channel->listener_data = nullptr;
		channel->listener_close = nullptr;
		channel->connection_string.clear();
		channel->buffer.clear();

		channel->runner.detach();
		channel->runner = std::jthread{};

		channel = nullptr;
	}

	CustomNetworkingImpl::Channel::~Channel()
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };
	}

	CustomNetworkingImpl::CustomNetworkingImpl(InterfaceInstances* intf) :
		listeners{ intf->notification.get() }, mtx{}, channels{}
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };
	}

	CustomNetworkingImpl::~CustomNetworkingImpl()
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };
		// REVIEW: channels own active jthreads whose callbacks retain this raw
		// CustomNetworkingImpl pointer. Destroying the map without stopping those
		// clients permits callbacks into a freed object; stop/join all channels first.
	}

	void CustomNetworkingImpl::WebSocketOnOpen(std::shared_ptr<Channel> channel, websocketpp::connection_hdl hdl)
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		listeners->NotifyAll(&IConnectionOpenListener::OnConnectionOpenSuccess, channel->connection_string.c_str(), (ConnectionID)channel.get());
	}

	void CustomNetworkingImpl::WebSocketOnMessage(std::shared_ptr<Channel> channel, websocketpp::connection_hdl hdl, custom_networking::message_ptr msg)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING | tracer::Trace::HIGH_FREQUENCY_CALLS };

		uint32_t data_size = 0;

		{
			lock_t guard(channel->buffer_mtx);
			const std::string& data = msg->get_payload();

			data_size = (uint32_t)data.size();
			// REVIEW: Incoming WebSocket payloads are appended without a
			// configured bound. A peer can keep a channel's deque growing until
			// memory is exhausted; enforce a maximum buffered payload and define
			// the overflow notification behavior.
			channel->buffer.insert(channel->buffer.end(), data.c_str(), data.c_str() + data.size());
		}

		listeners->NotifyAll(&IConnectionDataListener::OnConnectionDataReceived, (ConnectionID)channel.get(), data_size);
	}

	void CustomNetworkingImpl::WebSocketOnClose(std::shared_ptr<Channel> channel, websocketpp::connection_hdl hdl)
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		// REVIEW: Report the channel ID, not the CustomNetworkingImpl address.
		// Returning this pointer makes the close callback refer to a connection
		// that callers cannot pass back to GetChannel().
		listeners->NotifyAll(channel->listener_close, &IConnectionCloseListener::OnConnectionClosed, (ConnectionID)this, IConnectionCloseListener::CLOSE_REASON_UNDEFINED);

		if (!channel->client.stopped()) {
			channel->client.stop();
		}
	}

	void CustomNetworkingImpl::WebSocketOnFail(std::shared_ptr<Channel> channel, websocketpp::connection_hdl hdl)
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		listeners->NotifyAll(channel->listener_open, &IConnectionOpenListener::OnConnectionOpenFailure, channel->connection_string.c_str()
#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_FAILURE_REASON
			, IConnectionOpenListener::FAILURE_REASON_CONNECTION_FAILURE
#else
			, IConnectionOpenListener::FAILURE_REASON_UNDEFINED
#endif
		);

		if (!channel->client.stopped()) {
			channel->client.stop();
		}
	}

	std::shared_ptr<CustomNetworkingImpl::Channel> CustomNetworkingImpl::GetChannel(ConnectionID connectionID) const
	{
		lock_t lock(mtx);
		auto entry = channels.find(connectionID);
		if (entry == channels.end()) {
			return nullptr;
		}

		return entry->second;
	}

	void CustomNetworkingImpl::OpenConnection(const char* connectionString
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
		, IConnectionOpenListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		// REVIEW: OpenConnection accepts a null connectionString and forwards it
		// into Channel::connect/websocketpp. Validate the public ABI argument
		// before creating a channel or formatting/logging the URL.
		auto channel = std::make_shared<Channel>(this);

		if (channel->connect(connectionString,
			BOOST_PP_IF(GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS, listener, nullptr)
		))
		{
			{
				lock_t lock(mtx);
				channels.emplace((ConnectionID)channel.get(), channel);
			}
			channel->start();
		}
	}

	void CustomNetworkingImpl::CloseConnection(ConnectionID connectionID
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
		, IConnectionCloseListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		std::shared_ptr<Channel> channel{ GetChannel(connectionID) };
		if (!channel) {
			return;
		}

		channel->listener_close = BOOST_PP_IF(GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS, listener, nullptr);

		if (channel->connection) {
			channel->connection->close(websocketpp::close::status::normal, "normal");
		}
	}

	void CustomNetworkingImpl::SendData(ConnectionID connectionID, const void* data, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING | tracer::Trace::HIGH_FREQUENCY_CALLS };

		std::shared_ptr<Channel> channel{ GetChannel(connectionID) };

		// REVIEW: Neither channel nor channel->connection is checked. Invalid IDs
		// (and every channel before the missing assignment in connect()) crash here;
		// return a failure/no-op when the connection is unavailable.
		// REVIEW: The data pointer is also converted to a string without
		// validation. Reject null data for nonzero dataSize (and define the
		// zero-length/null-pointer contract) before constructing the payload.
		channel->connection->send(std::string((const char*)data, dataSize), websocketpp::frame::opcode::value::BINARY);
	}

	uint32_t CustomNetworkingImpl::GetAvailableDataSize(ConnectionID connectionID) {
		std::shared_ptr<Channel> channel{ GetChannel(connectionID) };
		if (!channel) {
			return 0;
		}

		// REVIEW: WebSocketOnMessage writes buffer under buffer_mtx, but this read
		// is unlocked. Concurrent delivery and polling is a data race; take the
		// channel lock before reading size.
		return (uint32_t)channel->buffer.size();
	}

	void CustomNetworkingImpl::PeekData(ConnectionID connectionID, void* dest, uint32_t dataSize) {
		std::shared_ptr<Channel> channel{ GetChannel(connectionID) };
		if (!channel) {
			return;
		}

		lock_t guard(channel->buffer_mtx);
		// REVIEW: PeekData/ReadData copy into dest without checking it. A null
		// destination with available bytes is an immediate invalid write; reject
		// the argument or require a zero-length read.
		std::copy_n(channel->buffer.begin(), std::min(dataSize, (uint32_t)channel->buffer.size()), (char*)dest);
	}

	void CustomNetworkingImpl::ReadData(ConnectionID connectionID, void* dest, uint32_t dataSize) {
		std::shared_ptr<Channel> channel{ GetChannel(connectionID) };
		if (!channel) {
			return;
		}

		lock_t guard(channel->buffer_mtx);
		size_t size = std::min(dataSize, (uint32_t)channel->buffer.size());
		// REVIEW: As in PeekData, a null dest with a nonzero copy length is
		// dereferenced by copy_n. Validate the destination before consuming
		// bytes so an invalid call cannot partially alter the stream.
		std::copy_n(channel->buffer.begin(), size, (char*)dest);
		channel->buffer.erase(channel->buffer.begin(), channel->buffer.begin() + size);
	}

	void CustomNetworkingImpl::PopData(ConnectionID connectionID, uint32_t dataSize) {
		std::shared_ptr<Channel> channel{ GetChannel(connectionID) };
		if (!channel) {
			return;
		}

		lock_t guard(channel->buffer_mtx);
		size_t size = std::min(dataSize, (uint32_t)channel->buffer.size());
		channel->buffer.erase(channel->buffer.begin(), channel->buffer.begin() + size);
	}
}

#endif
