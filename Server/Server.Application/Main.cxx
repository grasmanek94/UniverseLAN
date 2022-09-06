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

using Player = NetPlayer;

class Server: public MessageReceiver
{
private:
	V_Plus_NetworkServer connection;
	IdCounter id_generator;
	const size_t max_players;
	std::vector<Link> peers;
	std::set<Link*> connected_peers;

	// Not used in svr:
	void Handle(ENetPeer* peer, const std::shared_ptr<GameSetup>& data) override { }
	void Handle(ENetPeer* peer, const std::shared_ptr<WorldUpdate>& data) override { }
	void Handle(ENetPeer* peer, const std::shared_ptr<PeerConnected>& data) override { }
	void Handle(ENetPeer* peer, const std::shared_ptr<PeerDisconnected>& data) override { }

	// Handlers:
	void Handle(ENetPeer* peer, const std::shared_ptr<EventConnect>& data) override
	{
		size_t id = id_generator.GetId();

		Link* link = &peers[id];
		link->SetPeer(peer);
		connected_peers.insert(link);

		connection.Send(peer, GameSetup( id ));
		std::cout << "Peer connected: " << peer->address.host << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<EventDisconnect>& data) override
	{
		Player* player = Link::GetPlayer(peer);

		PlayerQuit player_quit;
		player_quit.SetSender(player->id);

		connection.Broadcast(player_quit, peer);

		std::cout << "Peer disconnected: " << peer->address.host << ":" << peer->address.port << " with ID: " << reinterpret_cast<size_t>(peer->data) << std::endl;

		peers[player->id].SetPeer(nullptr);
		connected_peers.erase(&peers[player->id]);
		id_generator.FreeId(player->id);
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<ChatMessage>& message) override
	{
		Player* player = Link::GetPlayer(peer);

		message->SetSender(player->id);

		std::wcout << "[" << message->GetSender() << "]: " << message->GetContents() << std::endl;

		connection.Broadcast(message);
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<PlayerJoin>& message) override
	{
		Player* player = Link::GetPlayer(peer);

		message->SetSender(player->id);

		message->SetSender(player->id);
		message->SetName(player->name);

		for(auto& link: connected_peers)
		{
			Player* remote = link->GetPlayer();
			if(remote != player)
			{
				if(remote->spawned)
				{
					PlayerSpawn player_spawn;
					player_spawn.SetSender(remote->id);
					player_spawn.SetModelHash(remote->model_hash);
					player_spawn.SetPosition(remote->position);
					player_spawn.SetRotation(remote->rotation);
					connection.Send(peer, player_spawn);
				}
			}
		}

		connection.Broadcast(message, peer);

		std::wcout << "Player joined: " << message->GetName() << " with ID:" << message->GetSender() << std::endl;
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<PlayerQuit>& message) override
	{
		Player* player = Link::GetPlayer(peer);

		message->SetSender(player->id);

		connection.Broadcast(message, peer);
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<PlayerSpawn>& message) override
	{
		Player* player = Link::GetPlayer(peer);

		message->SetSender(player->id);

		Vector3
			_position,
			_rotation;

		player->model_hash = message->GetModelHash();

		message->GetPosition(_position);
		player->position = _position;

		message->GetRotation(_rotation);
		player->rotation = _rotation;

		player->spawned = true;

		connection.Broadcast(message, peer);
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<PlayerDespawn>& message) override
	{
		Player* player = Link::GetPlayer(peer);

		message->SetSender(player->id);

		connection.Broadcast(message, peer);
	}

	void Handle(ENetPeer* peer, const std::shared_ptr<OnFootSync>& message) override
	{
		Player* player = Link::GetPlayer(peer);

		message->SetSender(player->id);

		connection.Broadcast(message, peer);
	}
public:
	Server(const std::string bind_address, uint16_t port, size_t max_players)
		: id_generator(max_players), max_players(max_players)
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

		connection.SetHost(bind_address, port);

		if (!connection.Create(max_players) || !connection.Good())
		{
#ifdef _WIN32
			// TODO custom exception class
			throw std::exception("ENET host member creation failed");
#endif
		}		

		peers.resize(max_players);
		for (size_t i = 0; i < max_players; ++i)
		{
			peers[i].GetPlayer()->id = i;
		}
		//ready
	}

	void Tick()
	{
		if (connection.Pull())
		{
			ProcessEvent(connection.Event());
		}
	}

	~Server()
	{

	}
};

std::unique_ptr<Server> server;
int main()
{
	std::cout << "Plz add some light" << std::endl;
	server = std::make_unique<Server>("0.0.0.0", 5544, 32);
	while (true)
	{
		server->Tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	return 0;
}
