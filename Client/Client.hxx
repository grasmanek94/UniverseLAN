#pragma once

#include "UniverseLAN.hxx"

#include <Networking/Networking.hxx>

#include <atomic>
#include <thread>

namespace universelan::client {
	class Client : public MessageReceiver
	{
	private:
		InterfaceInstances* interfaces;
		std::atomic_bool running;
		std::thread tick_thread;
		GalaxyNetworkClient connection;

		// Handlers:
		virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) override;
		virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) override;

		SHARED_NETWORK_OVERRIDE_MESSAGE_HANDLERS();

		void Tick();

	public:

		Client(InterfaceInstances* interfaces);
		virtual ~Client();

		void Start();
		void Stop();
		void ProcessEvents();

		const GalaxyNetworkClient& GetConnection() const;
	};
}