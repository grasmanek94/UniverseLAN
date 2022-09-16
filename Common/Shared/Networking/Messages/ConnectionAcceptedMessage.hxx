#pragma once
#include <Networking/SendableEventMessage.hxx>

class ConnectionAcceptedMessage
{
public:
	template<class Archive>
	void serialize(Archive & ar){ }

	UniqueClassId_Declare(ConnectionAcceptedMessage);

	ConnectionAcceptedMessage() {}
};
