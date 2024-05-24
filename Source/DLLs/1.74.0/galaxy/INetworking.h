#ifndef GALAXY_I_NETWORKING_H
#define GALAXY_I_NETWORKING_H

/**
 * @file
 * Contains data structures and interfaces related to communicating with other
 * Galaxy Peers.
 */

#include "IListenerRegistrar.h"
#include "GalaxyID.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * Listener for the events related to packets that come to the client.
		 */
		class INetworkingListener : public GalaxyTypeAwareListener<NETWORKING>
		{
		public:

			/**
			 * Notification for the event of receiving a packet.
			 *
			 * @param msgSize The length of the message.
			 * @param channel The number of the chanel used.
			 */
			virtual void OnP2PPacketAvailable(uint32_t msgSize, uint8_t channel) = 0;
		};

		/**
		 * Globally self-registering version of INetworkingListener.
		 */
		typedef SelfRegisteringListener<INetworkingListener> GlobalNetworkingListener;

		/**
		 * Listener for the events related to packets that come to server (the packets
		 * that were addressed to a LobbyID).
		 */
		class IServerNetworkingListener : public GalaxyTypeAwareListener<SERVER_NETWORKING>
		{
		public:

			/**
			 * Notification for the event of receiving a packet.
			 *
			 * @param msgSize The length of the message.
			 * @param channel The number of the chanel used.
			 */
			virtual void OnServerP2PPacketAvailable(uint32_t msgSize, uint8_t channel) = 0;
		};

		/**
		 * Globally self-registering version of IServerNetworkingListener.
		 */
		typedef SelfRegisteringListener<IServerNetworkingListener> GlobalServerNetworkingListener;

		/**
		 * Send type used when calling SendP2PPacket() in order to
		 * specify desired reliability of the data transfer for each packet that is
		 * being sent.
		 */
		enum P2PSendType
		{
			P2P_SEND_UNRELIABLE = 0, ///< UDP-like packet transfer.
			P2P_SEND_RELIABLE = 1 ///< TCP-like packet transfer.
		};

		/**
		 * The interface for communicating with other Galaxy Peers.
		 */
		class INetworking
		{
		public:

			virtual ~INetworking()
			{
			}

			/**
			 * Sends a P2P packet to a specified user.
			 *
			 * It is possible to communicate only with the users within the same lobby.
			 * It is recommended to send 1200 bytes at most in a single packet.
			 *
			 * The channel is a routing number that allows to implement
			 * separate layers of communication while using the same existing connection
			 * in order to save some network resources.
			 * Since there is only a single connection between each two Galaxy Peers,
			 * the Galaxy Peer that is supposed to receive the packet needs to know
			 * which channel number to use when checking for incoming packets.
			 *
			 * In order to receive the packet on the other Galaxy Peer, call there
			 * ReadP2PPacket() with the same channel number.
			 *
			 * Packets addressed to a user (by providing a user ID as the GalaxyID)
			 * need to be received with the standard networking interface.
			 * Packets addressed to a lobby (by providing a lobby ID as the GalaxyID)
			 * come to the lobby owner that also acts as the game server, thus they
			 * need to be received with the server networking interface.
			 *
			 * @param galaxyID ID of the specified user to whom the packet is to be sent.
			 * @param data The data to send.
			 * @param dataLen The length of the data.
			 * @param sendType The level of reliability of the operation.
			 * @param channel The number of the chanel to use.
			 * @return true if the packet was scheduled for sending, false otherwise.
			 */
			virtual bool SendP2PPacket(GalaxyID galaxyID, const void* data, uint32_t dataLen, P2PSendType sendType, uint8_t channel = 0) = 0;

			/**
			 * Reads an incoming packet that was sent from another Galaxy Peer
			 * by calling SendP2PPacket() with the same channel number.
			 * The packet that was read this way is left in the packet queue.
			 *
			 * If the buffer that is supposed to take the data is too small,
			 * the message will be truncated to its size. The size of the packet is
			 * provided in the notification about an incoming packet in either
			 * INetworkingListener or IServerNetworkingListener, during which this call
			 * is intended to be performed.
			 *
			 * This call is non-blocking and operates on the awaiting packets
			 * that have already come to the Galaxy Peer, thus instantly finishes,
			 * claiming a failure if there are no packets on the specified channel yet.
			 *
			 * @remark This call works similarly to ReadP2PPacket(), yet does not remove
			 * the packet from the packet queue.
			 *
			 * @param dest The buffer to pass the data to.
			 * @param destSize The size of the buffer.
			 * @param outMsgSize The size of the message.
			 * @param outGalaxyID The ID of the user who sent the packet.
			 * @param channel The number of the channel to use.
			 * @return true if succeeded, false when there are no packets.
			 */
			virtual bool PeekP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel = 0) = 0;

			/**
			 * Checks for any incoming packets on a specified channel.
			 *
			 * @remark Do not call this method if employing INetworkingListener and
			 * IServerNetworkingListener. Instead, during the notification about an
			 * incoming packet read packets by calling PeekP2PPacket().
			 *
			 * @param outMsgSize The size of the first incoming message if there is any.
			 * @param channel The number of the channel to use.
			 * @return true if there are any awaiting incoming packets, false otherwise.
			 */
			virtual bool IsP2PPacketAvailable(uint32_t* outMsgSize, uint8_t channel = 0) = 0;

			/**
			 * Reads an incoming packet that was sent from another Galaxy Peer
			 * by calling SendP2PPacket() with the same channel number.
			 * The packet that was read this way is removed from the packet queue.
			 *
			 * If the buffer that is supposed to take the data is too small,
			 * the message will be truncated to its size. For that reason prior to
			 * reading a packet it is recommended to check for it by calling
			 * IsP2PPacketAvailable(), which also returns the packet size.
			 *
			 * This call is non-blocking and operates on the awaiting packets
			 * that have already come to the Galaxy Peer, thus instantly finishes,
			 * claiming a failure if there are no packets on the specified channel yet.
			 *
			 * @remark This call is equivalent to calling PeekP2PPacket(), and then
			 * calling PopP2PPacket().
			 *
			 * @remark Do not call this method if employing INetworkingListener or
			 * IServerNetworkingListener, since the packet that the notification is
			 * related to is automatically removed from the packet queue right after all
			 * the related notifications are finished. Instead, read the incoming packet
			 * by calling PeekP2PPacket() during the notification.
			 *
			 * @param dest The buffer to pass the data to.
			 * @param destSize The size of the buffer.
			 * @param outMsgSize The size of the message.
			 * @param outGalaxyID The ID of the user who sent the packet.
			 * @param channel The number of the channel to use.
			 * @return true if succeeded, false when there are no packets.
			 */
			virtual bool ReadP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel = 0) = 0;

			/**
			 * Removes the first packet from the packet queue.
			 *
			 * @remark Do not call this method if employing INetworkingListener or
			 * IServerNetworkingListener, since the packet that the notification is
			 * related to is automatically removed from the packet queue right after all
			 * the related notifications are finished.
			 *
			 * @param channel The number of the channel to use.
			 */
			virtual void PopP2PPacket(uint8_t channel = 0) = 0;

			/**
			 * Retrieves current ping value in milliseconds with a specified entity, i.e.
			 * another member of the same lobby that the current user is in, or the lobby
			 * itself, in which case the returned value is the ping with the lobby owner.
			 *
			 * @param galaxyID ID of the specified user or lobby to check ping with.
			 * @return Ping with the target entity or -1 if the target entity is not
			 * connected or the ping has not been determined yet.
			 */
			virtual int GetPingWith(GalaxyID galaxyID) = 0;
		};

		/** @} */
	}
}

#endif
