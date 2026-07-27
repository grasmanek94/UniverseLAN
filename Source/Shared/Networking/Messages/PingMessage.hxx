#pragma once

#include <Networking/SendableEventMessage.hxx>

namespace universelan {
	class PingMessage
	{
	public:
		uint64_t my_time;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(my_time);
		}

		UniqueClassId_Declare(PingMessage);

		PingMessage()
			: my_time{ 0 } {}

		PingMessage(uint64_t my_time)
			: my_time{ my_time } {
		}
	};
}
