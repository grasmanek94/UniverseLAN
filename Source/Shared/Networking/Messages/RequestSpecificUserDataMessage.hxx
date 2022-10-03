#pragma once
#include <Networking/SendableEventMessage.hxx>

#include <AchievementsAndStatsContainer.hxx>

#include <GalaxyApi.h>

#include <string>

namespace universelan {
	class RequestSpecificUserDataMessage
	{
	public:
		enum RequestType {
			RequestTypeUserData,
			RequestTypeAchievementsAndStats,
			RequestTypePlayTime,
			RequestTypeFriends,
			RequestTypeRichPresence
		};

		uint64_t request_id;
		galaxy::api::GalaxyID id;
		bool found;
		AchievementsAndStatsContainer asuc;
		RequestType type;
		std::string nickname;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, id, found, asuc, type, nickname);
		}

		UniqueClassId_Declare(RequestSpecificUserDataMessage);

		RequestSpecificUserDataMessage() 
			: request_id{}, id{}, found{ false }, asuc{}, 
			type{ RequestTypeUserData }, nickname{} {}
		RequestSpecificUserDataMessage(RequestType type, const galaxy::api::GalaxyID& id)
			: request_id{}, id{ id }, found{ false }, asuc{}, 
			type{ RequestTypeUserData }, nickname{} {}
		RequestSpecificUserDataMessage(RequestType type, uint64_t request_id, const galaxy::api::GalaxyID& id) 
			: request_id{ request_id }, id{ id }, found{ false },
			asuc{}, type{ RequestTypeUserData }, nickname{} {}
	};
}
