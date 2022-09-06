#pragma once
#include <Networking/SendableEventMessage.hxx>

class PeerConnected
{
private:
	size_t id;

public:
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(id);
	}

	UniqueClassId_Declare(PeerConnected, true);

	PeerConnected(size_t id = (size_t)-1);
	size_t Id() const;
};

class PeerDisconnected
{
private:
	size_t id;

public:
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(id);
	}

	UniqueClassId_Declare(PeerDisconnected, true);

	PeerDisconnected(size_t id = (size_t)-1);

	size_t Id() const;
};
