#pragma once
#include <cstdlib>
#include <enet/enetpp.hxx>

class NetPlayer
{
public:
	ENetPeer* peer;
	size_t id;
	std::wstring name;
	bool spawned;
	uint32_t model_hash;
};
