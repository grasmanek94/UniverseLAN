#pragma once
#include <Networking/SendableEventMessage.hxx>

#include <AchievementsAndStatsContainer.hxx>

#include <GalaxyApi.h>

class UserHelloDataMessage
{
public:
	galaxy::api::GalaxyID id;
	AchievementsAndStatsContainer asuc;

	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(id, asuc);
	}

	UniqueClassId_Declare(UserHelloDataMessage);

	UserHelloDataMessage() : id{}, asuc{} {}
	UserHelloDataMessage(const galaxy::api::GalaxyID& id) : id{ id }, asuc{} {}
};
