#include <exception>
#include <thread>
#include <Networking/Networking.hxx>
#include <SharedUtility.h>

class Client : public V_Plus_NetworkClient, public MessageReceiver
{
private:
	void HandleTick()
	{
		if (GetAsyncKeyState('X'))
		{
			ChatMessage message;
			message.SetContents(L"Hello there, here is a Dummy Client!");
			V_Plus_NetworkClient::SendAsync(message);
		}
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) override
	{
		in_addr x;
		x.S_un.S_addr = peer->address.host;
		std::cout << "EventConnect: " << inet_ntoa(x) << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) override
	{
		in_addr x;
		x.S_un.S_addr = peer->address.host;
		std::cout << "EventDisconnect: " << inet_ntoa(x) << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;
	}


	void Handle(ENetPeer* peer, const std::shared_ptr<PeerConnected>& data) override
	{
		in_addr x;
		x.S_un.S_addr = peer->address.host;
		std::cout << "Host connected: " << inet_ntoa(x) << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<PeerDisconnected>& data) override
	{
		in_addr x;
		x.S_un.S_addr = peer->address.host;
		std::cout << "Host disconnected: " << inet_ntoa(x) << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<ChatMessage>& message) override
	{
		std::wcout << "[" << message->GetSender() << "]: " << message->GetContents() << std::endl;
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<PlayerJoin>& message) override
	{

	}

	void Handle(ENetPeer* peer, const std::shared_ptr<PlayerQuit>& message) override
	{

	}

	void Handle(ENetPeer* peer, const std::shared_ptr<PlayerSpawn>& message) override
	{

	}

	void Handle(ENetPeer* peer, const std::shared_ptr<PlayerDespawn>& message) override
	{

	}

	void Handle(ENetPeer* peer, const std::shared_ptr<WorldUpdate>& data) override
	{

	}

	void Handle(ENetPeer* peer, const std::shared_ptr<GameSetup>& data) override
	{

	}

	void Handle(ENetPeer* peer, const std::shared_ptr<OnFootSync>& message) override
	{
		static size_t cloned_id = -1;

		if (cloned_id == -1)
		{
			cloned_id = message->GetSender();
		}

		if (cloned_id == message->GetSender())
		{
			Vector3 position;
			message->GetPosition(position);
			position.y += 2;
			message->SetPosition(position);
			V_Plus_NetworkClient::SendAsync(message);
		}
	}

public:
	Client()
	{
		int init_code = V_Plus_NetworkClient::GetInitCode();

		if (init_code)
		{
			// TODO custom exception class
			throw std::exception(("Cannot initialize ENET, error code: " + std::to_string(init_code)).c_str());
		}

		if (!V_Plus_NetworkClient::Create() || !V_Plus_NetworkClient::Good())
		{
			// TODO custom exception class
			throw std::exception("ENET host member creation failed");
		}


		//ready to use Connect
	}

	void Tick()
	{
		// TODO : run this in another thread
		V_Plus_NetworkClient::RunNetworking();
		V_Plus_NetworkClient::ProcessEvents(this);
		HandleTick();
	}

	void Connect(const std::string& host, uint16_t port, const std::string& password)
	{
		V_Plus_NetworkClient::Connect(host, port);
	}

	~Client()
	{

	}
};

std::unique_ptr<Client> client;
int main()
{
	std::cout << "Plz add some light" << std::endl;
	client = std::make_unique<Client>();
	client->Connect("127.0.0.1", 5544, "");
	while (true)
	{
		client->Tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	return 0;
}
