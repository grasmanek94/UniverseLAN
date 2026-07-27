#pragma once

#include "UniverseLAN.hxx"

#include <Networking/Networking.hxx>

#include <atomic>
#include <chrono>
#include <thread>

namespace universelan::client {
	struct InterfaceInstances;

	class Client : public MessageReceiver
	{
	public:
		using timepoint_t = std::chrono::time_point<std::chrono::steady_clock>;

	private:
		InterfaceInstances* interfaces;
		std::atomic_bool running;
		std::thread tick_thread;
		std::atomic<timepoint_t> last_ping;
		GalaxyNetworkClient connection;

		// Handlers:
		virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) override;
		virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) override;

#include <Networking/MessageHandlersDeclareOverride.hxx>

		void Tick();
		void Ping();

	public:

		Client(InterfaceInstances* interfaces);
		virtual ~Client();

		void Start();
		void Stop();
		void ProcessEvents();

		const GalaxyNetworkClient& GetConnection() const;
		bool IsConnected() const;
	};
}