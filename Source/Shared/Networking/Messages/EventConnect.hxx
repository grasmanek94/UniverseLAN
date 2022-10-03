#pragma once
#include <enet/enetpp.hxx>
#include <Networking/SendableEventMessage.hxx>

namespace universelan {
	class EventConnect
	{
	public:
		UniqueClassId_Declare(EventConnect);

		EventConnect() {}
	};
}