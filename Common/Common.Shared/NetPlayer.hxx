#pragma once
#include <cstdlib>
#include <enet/enetpp.hxx>

class NetPlayer
{
public:
	ENetPeer* peer;
	size_t id;
};
