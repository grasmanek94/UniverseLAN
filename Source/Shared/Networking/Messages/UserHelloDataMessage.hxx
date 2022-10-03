#pragma once
#include <Networking/SendableEventMessage.hxx>

#include <AchievementsAndStatsContainer.hxx>

#include <GalaxyID.h>

#include <string>

namespace universelan {
	class UserHelloDataMessage
	{
	public:
		galaxy::api::GalaxyID id;
		AchievementsAndStatsContainer asuc;
		std::string nickname;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(id, asuc, nickname);
		}

		UniqueClassId_Declare(UserHelloDataMessage);

		UserHelloDataMessage() : id{ 0 }, asuc{}, nickname{} {}
		UserHelloDataMessage(const AchievementsAndStatsContainer& asuc) : id{ 0 }, asuc{ asuc }, nickname{} { }
		UserHelloDataMessage(galaxy::api::GalaxyID id, const AchievementsAndStatsContainer& asuc, const std::string& nickname) : id{ id }, asuc{ asuc }, nickname{ nickname } { }
	};
}
