#include "PeerConnection.hxx"

PeerConnected::PeerConnected(size_t id)
	: id(id)
{ }

size_t PeerConnected::Id() const
{
	return id;
}

PeerDisconnected::PeerDisconnected(size_t id)
	: id(id)
{ }

size_t PeerDisconnected::Id() const
{
	return id;
}
