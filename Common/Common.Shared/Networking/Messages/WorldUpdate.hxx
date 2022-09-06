#pragma once
#include <Networking/SendableEventMessage.hxx>

class WorldUpdate
{
private:
	size_t time;
public:
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(time);
	}

	UniqueClassId_Declare(WorldUpdate, true);
};
