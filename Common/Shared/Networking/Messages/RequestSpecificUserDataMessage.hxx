#pragma once
#include <Networking/SendableEventMessage.hxx>

#include <AchievementsAndStatsContainer.hxx>

#include <GalaxyApi.h>

class RequestSpecificUserDataMessage
{
public:
	MessageUniqueID request_id;
	galaxy::api::GalaxyID id;
	bool found;
	AchievementsAndStatsContainer asuc;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(request_id, id, found, asuc);
	}

	UniqueClassId_Declare(RequestSpecificUserDataMessage);

	RequestSpecificUserDataMessage() : request_id{}, id{}, found{ false }, asuc{} {}
	RequestSpecificUserDataMessage(const galaxy::api::GalaxyID& id) : request_id{}, id{ id }, found{ false }, asuc{} {}
	RequestSpecificUserDataMessage(MessageUniqueID request_id, const galaxy::api::GalaxyID& id) : request_id{ request_id }, id{ id }, found{ false }, asuc{} {}
};
