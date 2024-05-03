#include "Client.hxx"

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
			throw std::exception(
#ifdef _WIN32
			("Cannot initialize ENET, error code: " + std::to_string(init_code)).c_str()
#endif
			);
		}

		if (!connection.Create() || !connection.Good())
		{
			tracer::Trace trace{ "::ENET host member creation failed", __FUNCTION__, tracer::Trace::NETCLIENT };
			// TODO custom exception class
			throw std::exception(
#ifdef _WIN32
				"ENET host member creation failed"
#endif
			);
		}

		connection.Connect(interfaces->config->GetServerAddress(), interfaces->config->GetPort());
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
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::NETCLIENT };

		running = true;
		tick_thread = std::thread{ &Client::Tick, this };
	}

	void Client::Stop()
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::NETCLIENT };

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
