#include "Client.hxx"

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
			throw std::exception(
#ifdef _WIN32
			("Cannot initialize ENET, error code: " + std::to_string(init_code)).c_str()
#endif
			);
		}

		std::cout << "Connecting to: " << interfaces->config->GetServerAddress() << ":" << interfaces->config->GetPort() << "\n";
		
		connection.SetNetworkReconnectTimeout(interfaces->config->GetNetworkTimeoutTime());

		if (connection.Connect(interfaces->config->GetServerAddress(), interfaces->config->GetPort()) == nullptr) {
			tracer::Trace trace{ "::ENET connection to host failed", __FUNCTION__, tracer::Trace::NETCLIENT };
			trace.write_all(std::string("Host: ") + interfaces->config->GetServerAddress() + ":" + std::to_string(interfaces->config->GetPort()));
			// TODO custom exception class
			throw std::exception(
#ifdef _WIN32
				"ENET connection to host failed"
#endif
			);
		}
	}

	void Client::Tick()
	{
		// REVIEW: This is the std::thread entry point and has no exception
		// boundary. An allocation, serialization, or ENet exception escaping
		// RunNetworking invokes std::terminate; report the failure and shut down
		// the client through an explicit thread-safe error path.
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
		// REVIEW: IsConnected reads connection state maintained by Tick's
		// networking thread. The state must be atomic or otherwise synchronized
		// before exposing it to API callers.
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

		// REVIEW: Assigning a new std::thread while tick_thread is still
		// joinable invokes std::terminate. Reject duplicate starts (or join/clear
		// the previous thread) before creating another worker.
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
		// REVIEW: ProcessEvents dispatches queued network events through raw
		// InterfaceInstances pointers. Serialize this call with InterfaceInstances
		// reset/destruction; Stop() only joins Tick and does not quiesce this
		// caller or protect wrapper teardown.
		connection.ProcessEvents(this);
	}
}
