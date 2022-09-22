#pragma once
#include <Networking/SendableEventMessage.hxx>

#include <AchievementsAndStatsContainer.hxx>

namespace universelan {
	class UserHelloDataMessage
	{
	public:
		AchievementsAndStatsContainer asuc;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(asuc);
		}

		UniqueClassId_Declare(UserHelloDataMessage);

		UserHelloDataMessage() : asuc{} {}
		UserHelloDataMessage(const AchievementsAndStatsContainer& p_asuc) : asuc{} { asuc = p_asuc; }
	};
}
