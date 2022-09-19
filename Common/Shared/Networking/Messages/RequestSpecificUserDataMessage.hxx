#pragma once
#include <Networking/SendableEventMessage.hxx>

#include <AchievementsAndStatsContainer.hxx>

#include <GalaxyApi.h>

namespace universelan {
	class RequestSpecificUserDataMessage
	{
	public:
		enum RequestType {
			RequestTypeUserData,
			RequestTypeAchievementsAndStats
		};
		uint64_t request_id;
		galaxy::api::GalaxyID id;
		bool found;
		AchievementsAndStatsContainer asuc;
		RequestType type;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, id, found, asuc);
		}

		UniqueClassId_Declare(RequestSpecificUserDataMessage);

		RequestSpecificUserDataMessage() : request_id{}, id{}, found{ false }, asuc{}, type{ RequestTypeUserData } {}
		RequestSpecificUserDataMessage(RequestType type, const galaxy::api::GalaxyID& id) : request_id{}, id{ id }, found{ false }, asuc{}, type{ RequestTypeUserData } {}
		RequestSpecificUserDataMessage(RequestType type, uint64_t request_id, const galaxy::api::GalaxyID& id) : request_id{ request_id }, id{ id }, found{ false }, asuc{}, type{ RequestTypeUserData } {}
	};
}
