#pragma once
#include <Networking/SendableEventMessage.hxx>

#include <GalaxyApi.h>

namespace universelan {
	
	class OnlineStatusChangeMessage
	{
	public:
		galaxy::api::GalaxyID id;
		bool online;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(id, online);
		}

		UniqueClassId_Declare(OnlineStatusChangeMessage);

		OnlineStatusChangeMessage() : id{ 0 }, online{ false } {}
		OnlineStatusChangeMessage(galaxy::api::GalaxyID id, bool online) : id{ id }, online{ online } {}
	};
}
