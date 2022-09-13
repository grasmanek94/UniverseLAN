#pragma once

#include <Networking/Networking.hxx>

#include <atomic>
#include <thread>

class Client: public MessageReceiver
{
private:
	std::atomic_bool running;
	std::thread tick_thread;
	GalaxyNetworkClient connection;

	// Handlers:
	void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) override;
	void Handle(ENetPeer* peer, const std::shared_ptr<ChatMessage>& message) override;

	void Tick();

public:
	Client(const std::string& address, uint16_t port);
	virtual ~Client();

	void Start();
	void Stop();
	void ProcessEvents();
};
