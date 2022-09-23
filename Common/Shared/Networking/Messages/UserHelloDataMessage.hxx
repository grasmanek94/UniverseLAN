#pragma once
#include <Networking/SendableEventMessage.hxx>

#include <AchievementsAndStatsContainer.hxx>

#include <GalaxyID.h>

namespace universelan {
	class UserHelloDataMessage
	{
	public:
		galaxy::api::GalaxyID id;
		AchievementsAndStatsContainer asuc;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(id, asuc);
		}

		UniqueClassId_Declare(UserHelloDataMessage);

		UserHelloDataMessage() : id{ 0 }, asuc {} {}
		UserHelloDataMessage(const AchievementsAndStatsContainer& asuc) : id{ 0 }, asuc{ asuc } { }
		UserHelloDataMessage(galaxy::api::GalaxyID id, const AchievementsAndStatsContainer& asuc) : id{ id }, asuc { asuc } { }
	};
}
