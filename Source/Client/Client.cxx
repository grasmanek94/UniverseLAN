#include "Client.hxx"

#include <stdexcept>
#include <string>

namespace universelan::client {
	Client::Client(InterfaceInstances* interfaces)
		: interfaces{ interfaces }, running{ false }, tick_thread{}, connection{}
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::NETCLIENT };

		int init_code = connection.GetInitCode();

		if (init_code)
		{
			tracer::Trace trace{ ("::Cannot initialize ENET, error code: " + std::to_string(init_code)).c_str(), __FUNCTION__, tracer::Trace::NETCLIENT };
			// TODO custom exception class
			throw std::runtime_error(
				("Cannot initialize ENET, error code: " + std::to_string(init_code)).c_str()
			);
		}

		std::cout << "Connecting to: " << interfaces->config->GetServerAddress() << ":" << interfaces->config->GetPort() << "\n";
		
		connection.SetNetworkReconnectTimeout(interfaces->config->GetNetworkTimeoutTime());

		if (connection.Connect(interfaces->config->GetServerAddress(), interfaces->config->GetPort()) == nullptr) {
			tracer::Trace trace{ "::ENET connection to host failed", __FUNCTION__, tracer::Trace::NETCLIENT };
			trace.write_all(std::string("Host: ") + interfaces->config->GetServerAddress() + ":" + std::to_string(interfaces->config->GetPort()));
			// TODO custom exception class
			throw std::runtime_error(
				"ENET connection to host failed"
			);
		}
	}

	void Client::Tick()
	{
		while (running) {
			connection.RunNetworking(2);
		}

		connection.Disconnect();
	}

	const GalaxyNetworkClient& Client::GetConnection() const
	{
		return connection;
	}

	bool Client::IsConnected() const {
		return connection.IsConnected();
	}

	Client::~Client()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::NETCLIENT };
		Stop();
	}

	void Client::Start()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::NETCLIENT };

		running = true;
		tick_thread = std::thread{ &Client::Tick, this };
	}

	void Client::Stop()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::NETCLIENT };

		running = false;
		if (tick_thread.joinable()) {
			tick_thread.join();
		}
	}

	void Client::ProcessEvents()
	{
		connection.ProcessEvents(this);
	}
}
