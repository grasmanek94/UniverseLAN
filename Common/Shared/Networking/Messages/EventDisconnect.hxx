#pragma once
#include <enet/enetpp.hxx>
#include <Networking/SendableEventMessage.hxx>

class EventDisconnect
{
public:
	UniqueClassId_Declare(EventDisconnect);

	EventDisconnect() {}
};
