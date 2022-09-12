#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <set>
#include <Common.hxx>
#include <sstream>
#include <exception>
#include <algorithm>
#include <iterator>

#include <IdCounter.hxx>
#include <NetPlayer.hxx>

#include <Networking/Networking.hxx>
#include <Networking/Link.hxx>

#include "UniverseLAN.hxx"

extern "C" GALAXY_DLL_EXPORT uint32_t load() {
	return 0;
}

class Client: public MessageReceiver
{
private:
	GalaxyNetworkClient connection;
	IdCounter id_generator;
	std::vector<Link> peers;
	std::set<Link*> connected_peers;

	// Handlers:
	void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) override
	{
		size_t id = id_generator.GetNewId();

		Link* link = &peers[id];
		link->SetPeer(peer);
		connected_peers.insert(link);

		//connection.Send(peer, GameSetup( id ));
		std::cout << "Peer connected: " << peer->address.host << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) override
	{
		NetPlayer* player = Link::GetPlayer(peer);

		//PlayerQuit player_quit;
		//player_quit.SetSender(player->id);

		//connection.Broadcast(player_quit, peer);

		std::cout << "Peer disconnected: " << peer->address.host << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;

		peers[player->id].SetPeer(nullptr);
		connected_peers.erase(&peers[player->id]);
		id_generator.FreeId(player->id);
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<ChatMessage>& message) override
	{
		NetPlayer* player = Link::GetPlayer(peer);

		message->SetSender(player->id);

		std::wcout << "[" << message->GetSender() << "]: " << message->GetContents() << std::endl;

		connection.SendAsync(message);
	}

public:
	Client(const std::string address, uint16_t port)
		: id_generator()
	{
		int init_code = connection.GetInitCode();

		if (init_code)
		{
			// TODO custom exception class
			throw std::exception(
#ifdef _WIN32
				("Cannot initialize ENET, error code: " + std::to_string(init_code)).c_str()
#endif
			);
		}

		if (!connection.Create() || !connection.Good())
		{
#ifdef _WIN32
			// TODO custom exception class
			throw std::exception("ENET host member creation failed");
#endif
		}
		//ready to ->Connect
		connection.Connect(address, port);
	}

	void Tick()
	{
		if (connection.Pull())
		{
			ProcessEvent(connection.Event());
		}
	}

	virtual ~Client()
	{

	}
};
