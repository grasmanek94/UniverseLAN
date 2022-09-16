#pragma once
#include <Networking/SendableEventMessage.hxx>

class ConnectionAccepted
{
public:
	template<class Archive>
	void serialize(Archive & ar){ }

	UniqueClassId_Declare(ConnectionAccepted);

	ConnectionAccepted() {}
};
