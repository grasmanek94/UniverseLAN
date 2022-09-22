#pragma once

#include "UniverseLAN.hxx"

#include <Networking/Networking.hxx>

#include <atomic>
#include <thread>

namespace universelan::client {
	struct InterfaceInstances;

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

#include <Networking/MessageHandlersDeclareOverride.hxx>

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