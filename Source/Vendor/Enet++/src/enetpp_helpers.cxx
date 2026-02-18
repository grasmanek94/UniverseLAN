#include <enet6/enetpp_helpers.hxx>

/** Queues a packet to be sent to all peers associated with the host.
@param host host on which to broadcast the packet
@param channelID channel on which to broadcast
@param packet packet to broadcast
*/
extern "C" void enet_host_broadcast_except(ENetHost* host, enet_uint8 channelID,
	ENetPacket* packet, ENetPeer* except)
{
	ENetPeer* currentPeer;

	for (currentPeer = host->peers;
		currentPeer < &host->peers[host->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED || currentPeer == except)
		{
			continue;
		}

		enet_peer_send(currentPeer, channelID, packet);
	}

	if (packet->referenceCount == 0)
	{
		enet_packet_destroy(packet);
	}
}
