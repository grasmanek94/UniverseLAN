#pragma once
#include <enet/enetpp.hxx>
#include "NetPlayer.hxx"

class Link
{
private:
	ENetPeer* peer;
	NetPlayer player;

public:
	Link();
	void SetPeer(ENetPeer* p);
	ENetPeer* GetPeer() const;
	NetPlayer* GetPlayer();
	static NetPlayer* GetPlayer(ENetPeer* peer);
};
