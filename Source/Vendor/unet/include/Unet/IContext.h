#pragma once

#include <Unet_common.h>
#include <Unet/NetworkMessage.h>
#include <Unet/LobbyMember.h>
#include <Unet/LobbyListFilter.h>

namespace Unet
{
	enum class ContextStatus
	{
		// Not connected to anything and ready to connect.
		Idle,

		// Busy connecting to a host or creating a lobby.
		Connecting,

		// Currently in a lobby.
		Connected,
	};

	class IContext
	{
	public:
		virtual ~IContext() {}

		// Get the current connection status of the context.
		virtual ContextStatus GetStatus() = 0;

		// Set the callbacks object. (Context takes ownership of the callbacks object!)
		virtual void SetCallbacks(ICallbacks* callbacks) = 0;

		// Get the current callbacks object.
		virtual ICallbacks* GetCallbacks() = 0;

		// Call this every frame in order to run callbacks and handle all the networking logic.
		virtual void RunCallbacks() = 0;

		// Set the primary service to the given service type. The service type must already be enabled
		// using EnableService.
		//
		// This also automatically sets the persona name to the name reported by the service, if any.
		virtual void SetPrimaryService(ServiceType service) = 0;

		// Gets the currently set primary service.
		virtual ServiceType GetPrimaryService() = 0;

		// Enable a service.
		virtual void EnableService(ServiceType service) = 0;

		// Gets how many services are currently enabled.
		virtual int ServiceCount() = 0;

		// Simulate a service outage on the given service. This should only be used for testing!
		virtual void SimulateServiceOutage(ServiceType service) = 0;

		// Create a lobby. Before a lobby can be created, at least 1 service needs to be enabled.
		//
		// The callback OnLobbyCreated will be called with a CreateLobbyResult object.
		virtual void CreateLobby(LobbyPrivacy privacy, int maxPlayers, const char* name = nullptr) = 0;

		// Request a list of valid Unet lobbies, scattered across all enabled services.
		// Note that only valid Unet lobbies will be listed, non-Unet lobbies are ignored.
		//
		// The callback OnLobbyList will be called with a LobbyListResult object.
		virtual void GetLobbyList(const LobbyListFilter &filter) = 0;

		// Request information about a lobby by its entry point ID. This will only return with the entry
		// point to that service.
		//
		// The callback OnLobbyInfoFetched will be called with a LobbyInfoFetchResult object.
		virtual bool FetchLobbyInfo(const ServiceID &id) = 0;

		// Joins a lobby by the lobby info. This will connect to all entry points that are contained
		// within the lobby info.
		//
		// The callback OnLobbyJoined will be called with a LobbyJoinResult object.
		virtual void JoinLobby(const LobbyInfo &lobbyInfo) = 0;

		// Joins a lobby by a service entry point ID. This will only connect to that service, so it is
		// not recommended to use this function if you're not connecting directly via IP.
		//
		// The callback OnLobbyJoined will be called with a LobbyJoinResult object.
		virtual void JoinLobby(const ServiceID &id) = 0;

		// Leaves the lobby that we're currently in.
		//
		// The callback OnLobbyLeft will be called with a LobbyLeftResult object.
		virtual void LeaveLobby(LeaveReason reason = LeaveReason::UserLeave) = 0;

		// Kick a member from the lobby. We must be the host in order to kick someone.
		virtual void KickMember(LobbyMember* member) = 0;

		// Check if we're currently hosting. Returns false if we're a client or if we're not currently in
		// a lobby.
		virtual bool IsHosting() = 0;

		// Get the lobby that the we're currently in.
		virtual Lobby* CurrentLobby() = 0;

		// Get our own peer number.
		virtual int GetLocalPeer() = 0;

		// Get our own Guid.
		virtual xg::Guid GetLocalGuid() = 0;

		// Sets our name, which will be shown to other players. Typically you don't have to call this,
		// as the persona name will automatically be set to the name of the first service you enable. For
		// example, enabling the Steam service will automatically set the persona name to your Steam name.
		virtual void SetPersonaName(const char* str) = 0;

		// Gets our current name that is shown to other players.
		virtual const char* GetPersonaName() = 0;

		// Adds a file available for all clients to download from this peer, using a local file on disk.
		virtual void AddFile(const char* filename, const char* filenameOnDisk) = 0;

		// Adds a file available for all clients to download from this peer, using a buffer. Context will
		// copy the buffer, so there is no need to keep the memory around.
		virtual void AddFile(const char* filename, uint8_t* buffer, size_t size) = 0;

		// Removes a file from the list of available files from this peer.
		virtual void RemoveFile(const char* filename) = 0;

		// Requests a file from the given lobby member. The filename must exist on the client's list of
		// shared files. Currently, a direct connection must exist between the two clients transferring the
		// file. This should always be the case when transferring files between server and client.
		virtual void RequestFile(LobbyMember* member, const char* filename) = 0;

		// Requests a file from the given lobby member. Currently, a direct connection must exist between
		// the two clients transferring the file. This should always be the case when transferring files
		// between server and client.
		virtual void RequestFile(LobbyMember* member, LobbyFile* file) = 0;

		// Sends a chat message to the lobby. This will also immediately trigger OnLobbyChat in the callbacks
		// for the local chat message.
		virtual void SendChat(const char* message) = 0;

		// Checks if a message is available on the given channel.
		virtual bool IsMessageAvailable(int channel) = 0;

		// Reads the next available message from the given channel.
		virtual NetworkMessageRef ReadMessage(int channel) = 0;

		// Send a message to the given lobby member. The service to send the message on is automatically
		// picked from the best possible option. If there is no direct connection possible to this player,
		// it will be relayed through the host.
		//
		// Packet relaying is only possible for clients talking to other clients. Any communication between
		// client and server is guaranteed to never be relayed, as connections should always exist between
		// them.
		//
		// Sending messages reliably does not have a packet size limit, but be aware that sending very big
		// messages will not always be fast, depending on which service the data is being sent through.
		// Typical LAN tests show that speeds can be as low as 1 MB/s.
		//
		// Unreliable packets should not be bigger than 1198 bytes. Unreliable packets are always sent
		// unsequenced, and as such don't allow for bigger sizes than MTU. While MTU may be 1200 bytes,
		// we have to account for the possibility of sending relay-packet header data, so having a safety
		// margin of at least 2 bytes is recommended.
		//
		// The channel you send data on is an index starting at 0. You must have created the context with
		// a sufficient number of channels if you wish to use multiple channels.
		virtual void SendTo(LobbyMember* member, uint8_t* data, size_t size, PacketType type = PacketType::Reliable, uint8_t channel = 0) = 0;

		// Send a message to all clients in the lobby. See SendTo for more details.
		virtual void SendToAll(uint8_t* data, size_t size, PacketType type = PacketType::Reliable, uint8_t channel = 0) = 0;

		// Send a message to all clients in the lobby, except the given one. See SendTo for more details.
		virtual void SendToAllExcept(LobbyMember* exceptMember, uint8_t* data, size_t size, PacketType type = PacketType::Reliable, uint8_t channel = 0) = 0;

		// Send a message to the host of the lobby. See SendTo for more details.
		virtual void SendToHost(uint8_t* data, size_t size, PacketType type = PacketType::Reliable, uint8_t channel = 0) = 0;
	};
}
