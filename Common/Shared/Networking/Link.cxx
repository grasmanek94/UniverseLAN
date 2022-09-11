#include "Link.hxx"

Link::Link()
	: peer(nullptr)
{ }

void Link::SetPeer(ENetPeer* p)
{
	if (peer)
	{
		peer->data = nullptr;
	}

	peer = p;
	player.peer = p;
	if (p)
	{
		p->data = reinterpret_cast<void*>(&player);
	}
}

ENetPeer* Link::GetPeer() const
{
	return peer;
}

NetPlayer* Link::GetPlayer()
{
	return &player;
}

NetPlayer* Link::GetPlayer(ENetPeer* peer)
{
	return reinterpret_cast<NetPlayer*>(peer ? peer->data : nullptr);
}
