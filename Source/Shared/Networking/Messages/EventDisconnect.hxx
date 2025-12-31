#pragma once
#include <Networking/SendableEventMessage.hxx>

namespace universelan {
	class EventDisconnect
	{
	public:
		UniqueClassId_Declare(EventDisconnect);

		EventDisconnect() {}
	};
}
