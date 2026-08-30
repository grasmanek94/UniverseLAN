#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING

#include "CustomNetworking.hxx"

#include "UniverseLAN.hxx"
#include "Tracer.hxx"

#include <ixwebsocket/IXWebSocketMessage.h>
#include <ixwebsocket/IXWebSocketMessageType.h>

#include <functional>

namespace universelan::client {
	using namespace galaxy::api;
	using namespace std::placeholders;

	CustomNetworkingImpl::Channel::Channel(CustomNetworkingImpl* custom_network)
		: listeners{ custom_network->listeners }, client{},
		listener_open{}, listener_data{}, listener_close{}, connection_string{},
		buffer_mtx{}, buffer{}, cleanup{ false }
	{
	}

	bool CustomNetworkingImpl::Channel::connect(const char* connectionString, IConnectionOpenListener* listener)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format(
				"connectionString: {} listener: {}",
				connectionString, (void*)listener
			));
		}

		client.disableAutomaticReconnection();
		client.disablePerMessageDeflate();

		if (connectionString == nullptr || connectionString[0] == '\0') {

			if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
				trace.write_all("connect: false (null)");
			}

			listeners->NotifyAll(listener, &IConnectionOpenListener::OnConnectionOpenFailure, connectionString
#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_FAILURE_REASON
				, IConnectionOpenListener::FAILURE_REASON_CONNECTION_FAILURE
#else
				, IConnectionOpenListener::FAILURE_REASON_UNDEFINED
#endif
			);

			return false;
		}

		connection_string = connectionString;
		listener_open = listener;

		client.setUrl(connection_string);

		client.setOnMessageCallback(std::bind(&CustomNetworkingImpl::Channel::WebSocketCallback, this, _1));

		client.start();

		return true;
	}

	void CustomNetworkingImpl::Channel::WebSocketOnOpen()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		listeners->NotifyAll(&IConnectionOpenListener::OnConnectionOpenSuccess, connection_string.c_str(), (ConnectionID)this);
	}

	void CustomNetworkingImpl::Channel::WebSocketOnMessage(const std::string& data, const bool binary)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING | tracer::Trace::HIGH_FREQUENCY_CALLS };

		uint32_t data_size = 0;

		{
			lock_t guard{ buffer_mtx };
			data_size = (uint32_t)data.size();
			buffer.insert(buffer.end(), data.c_str(), data.c_str() + data.size());
		}

		listeners->NotifyAll(&IConnectionDataListener::OnConnectionDataReceived, (ConnectionID)this, data_size);
	}

	void CustomNetworkingImpl::Channel::WebSocketOnClose()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		listeners->NotifyAll(listener_close, &IConnectionCloseListener::OnConnectionClosed, (ConnectionID)this, IConnectionCloseListener::CLOSE_REASON_UNDEFINED);

		cleanup.exchange(true);
	}

	void CustomNetworkingImpl::Channel::WebSocketOnFail(const std::string& reason)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		listeners->NotifyAll(listener_open, &IConnectionOpenListener::OnConnectionOpenFailure, connection_string.c_str()
#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_FAILURE_REASON
			, IConnectionOpenListener::FAILURE_REASON_CONNECTION_FAILURE
#else
			, IConnectionOpenListener::FAILURE_REASON_UNDEFINED
#endif
		);

		cleanup.exchange(true);
	}

	void CustomNetworkingImpl::Channel::WebSocketCallback(const ix::WebSocketMessagePtr& message)
	{
		switch (message->type) {
		case ix::WebSocketMessageType::Open:
			WebSocketOnOpen();
			break;

		case ix::WebSocketMessageType::Message:
			WebSocketOnMessage(message->str, message->binary);
			break;

		case ix::WebSocketMessageType::Close:
			WebSocketOnClose();
			break;

		case ix::WebSocketMessageType::Error:
			WebSocketOnFail(message->errorInfo.reason);
			break;

		case ix::WebSocketMessageType::Ping:
		case ix::WebSocketMessageType::Pong:
		case ix::WebSocketMessageType::Fragment:
			break;

		default:
			break;
		}
	}

	void CustomNetworkingImpl::Channel::close() {
		client.disableAutomaticReconnection();
		client.close();
	}

	void CustomNetworkingImpl::PerformCleanup() {
		std::vector<ConnectionID> cleanup_channels = {};
		for (const auto& channel : channels) {
			if (channel.second->cleanup) {
				cleanup_channels.push_back(channel.first);
			}
		}

		while (!cleanup_channels.empty()) {
			auto channel = std::move(cleanup_channels.back());
			cleanup_channels.pop_back();

			/* Will call destructor so should stop also */
			channels.erase(channel);
		}
	}

	CustomNetworkingImpl::Channel::~Channel()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		client.stop();
	}

	CustomNetworkingImpl::CustomNetworkingImpl(InterfaceInstances* intf) :
		listeners{ intf->notification.get() }, mtx{}, channels{}
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };
	}

	CustomNetworkingImpl::~CustomNetworkingImpl()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		lock_t lock(mtx);
		channels.clear();
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
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		auto channel = std::make_shared<Channel>(this);

		if (channel->connect(connectionString,
			BOOST_PP_IF(GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS, listener, nullptr)
		))
		{
			lock_t lock(mtx);

			PerformCleanup();

			channels.emplace((ConnectionID)channel.get(), channel);
		}
	}

	void CustomNetworkingImpl::CloseConnection(ConnectionID connectionID
#if GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS
		, IConnectionCloseListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING };

		std::shared_ptr<Channel> channel{ GetChannel(connectionID) };
		if (!channel) {
			return;
		}

		channel->listener_close = BOOST_PP_IF(GALAXY_BUILD_FEATURE_HAS_ICONNECTIONLISTENERS, listener, nullptr);
		channel->client.close();
	}

	void CustomNetworkingImpl::SendData(ConnectionID connectionID, const void* data, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICUSTOMNETWORKING | tracer::Trace::HIGH_FREQUENCY_CALLS };

		std::shared_ptr<Channel> channel{ GetChannel(connectionID) };

		channel->client.send(std::string((const char*)data, dataSize), true);
	}

	uint32_t CustomNetworkingImpl::GetAvailableDataSize(ConnectionID connectionID) {
		std::shared_ptr<Channel> channel{ GetChannel(connectionID) };
		if (!channel) {
			return 0;
		}

		return (uint32_t)channel->buffer.size();
	}

	void CustomNetworkingImpl::PeekData(ConnectionID connectionID, void* dest, uint32_t dataSize) {
		std::shared_ptr<Channel> channel{ GetChannel(connectionID) };
		if (!channel) {
			return;
		}

		lock_t guard(channel->buffer_mtx);
		std::copy_n(channel->buffer.begin(), std::min(dataSize, (uint32_t)channel->buffer.size()), (char*)dest);
	}

	void CustomNetworkingImpl::ReadData(ConnectionID connectionID, void* dest, uint32_t dataSize) {
		std::shared_ptr<Channel> channel{ GetChannel(connectionID) };
		if (!channel) {
			return;
		}

		lock_t guard(channel->buffer_mtx);
		size_t size = std::min(dataSize, (uint32_t)channel->buffer.size());
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
