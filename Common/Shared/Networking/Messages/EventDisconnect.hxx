#pragma once
#include <enet/enetpp.hxx>
#include <Networking/SendableEventMessage.hxx>

class EventDisconnect
{
public:
	UniqueClassId_Declare(EventDisconnect);

	ENetPeer* peer;
	EventDisconnect(ENetPeer* peer);
};
