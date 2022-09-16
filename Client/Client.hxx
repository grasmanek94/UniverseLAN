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
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) override;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) override;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<KeyChallenge>& data) override;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<ChatMessage>& message) override;
	virtual void Handle(ENetPeer* peer, const std::shared_ptr<ConnectionAccepted>& data) override;

	void Tick();

public:
	Client(const std::string& address, uint16_t port);
	virtual ~Client();

	void Start();
	void Stop();
	void ProcessEvents();
};
