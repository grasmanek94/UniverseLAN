#pragma once
#include <cstdlib>
#include <Networking/SendableEventMessage.hxx>

class GameSetup
{
private:
	size_t player_id;

public:
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(player_id);
	}

	UniqueClassId_Declare(GameSetup, true);

	GameSetup(size_t id = -1);

	size_t GetId() const;
	void SetId(size_t id);
};
