#include <Unet_common.h>
#include <Unet/Services/ServiceEnet.h>
#include <Unet/LobbyPacket.h>

// I seriously hate Windows.h
#if defined(min)
#undef min
#endif

#define UNET_PORT 4450
#define UNET_ID_MASK 0x0000FFFFFFFFFFFF

static uint64_t AddressToInt(const ENetAddress &addr)
{
	return *(uint64_t*)& addr & UNET_ID_MASK;
}

namespace Unet
{
	Unet::ServiceID ServiceEnet::AddressToID(const ENetAddress &addr)
	{
		return Unet::ServiceID(Unet::ServiceType::Enet, AddressToInt(addr));
	}
}

static ENetAddress IDToAddress(const Unet::ServiceID &id)
{
	return *(ENetAddress*)&id.ID;
}

Unet::ServiceEnet::ServiceEnet(Internal::Context* ctx, int numChannels) :
	Service(ctx, numChannels)
{
}

Unet::ServiceEnet::~ServiceEnet()
{
}

void Unet::ServiceEnet::SimulateOutage()
{
	for (auto peer : m_peers) {
		enet_peer_disconnect_now(peer, 0);
	}
	m_peers.clear();

	if (m_host != nullptr) {
		enet_host_destroy(m_host);
	}

	m_host = nullptr;
	m_peerHost = nullptr;
}

void Unet::ServiceEnet::RunCallbacks()
{
	if (m_host != nullptr && m_waitingForPeers) {
		if (m_ctx->GetStatus() == ContextStatus::Connected) {
			m_waitingForPeers = false;

			auto &members = m_ctx->CurrentLobby()->GetMembers();
			for (auto member : members) {
				if (member->UnetPeer == m_ctx->GetLocalPeer()) {
					continue;
				}

				auto id = member->GetServiceID(ServiceType::Enet);
				if (!id.IsValid()) {
					continue;
				}

				if (GetPeer(id) != nullptr) {
					continue;
				}

				//TODO: Can we do NAT punching via the host?

				m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Enet] Connecting to client 0x%016llX", id.ID));

				auto addr = IDToAddress(id);
				m_peers.emplace_back(enet_host_connect(m_host, &addr, m_channels.size(), 0));
			}
		}
	}

	ENetEvent ev;
	while (m_host != nullptr && enet_host_service(m_host, &ev, 0)) {
		if (ev.type == ENET_EVENT_TYPE_CONNECT) {
			if (m_requestLobbyJoin != nullptr && m_requestLobbyJoin->Code != Result::OK) {
				m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Enet] Connection to host established: 0x%016llX", AddressToInt(ev.peer->address)));

				m_requestLobbyJoin->Code = Result::OK;
				m_requestLobbyJoin->Data->JoinedLobby->AddEntryPoint(AddressToID(ev.peer->address));

				json js;
				js["t"] = (uint8_t)LobbyPacketType::Handshake;
				js["guid"] = m_requestLobbyJoin->Data->JoinGuid.str();
				m_ctx->InternalSendTo(AddressToID(m_peerHost->address), js);

			} else {
				m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Enet] Client connected: 0x%016llX", AddressToInt(ev.peer->address)));

				auto it = std::find(m_peers.begin(), m_peers.end(), ev.peer);
				if (it == m_peers.end()) {
					m_peers.emplace_back(ev.peer);
				}
			}

		} else if (ev.type == ENET_EVENT_TYPE_DISCONNECT) {
			if (m_requestLobbyLeft != nullptr && m_requestLobbyLeft->Code != Result::OK) {
				enet_host_destroy(m_host);
				m_host = nullptr;
				m_peerHost = nullptr;

				m_requestLobbyLeft->Code = Result::OK;
				m_requestLobbyLeft = nullptr;

			} else {
				m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Enet] Client disconnected: 0x%016llX", AddressToInt(ev.peer->address)));

				auto it = std::find(m_peers.begin(), m_peers.end(), ev.peer);
				if (it == m_peers.end()) {
					m_ctx->GetCallbacks()->OnLogWarn("[Enet] Couldn't find peer in list of connected peers!");
				} else {
					m_peers.erase(it);
				}

				auto currentLobby = m_ctx->CurrentLobby();

				if (currentLobby != nullptr) {
					currentLobby->RemoveMemberService(AddressToID(ev.peer->address));
				}

				if (ev.peer == m_peerHost) {
					m_ctx->GetCallbacks()->OnLogDebug("[Enet] Disconnected from host!");

					for (auto peer : m_peers) {
						enet_peer_disconnect_now(peer, 0);
					}
					m_peers.clear();

					enet_host_destroy(m_host);
					m_host = nullptr;
					m_peerHost = nullptr;

					if (currentLobby != nullptr) {
						currentLobby->ServiceDisconnected(ServiceType::Enet);
					}
				}
			}

		} else if (ev.type == ENET_EVENT_TYPE_RECEIVE) {
			if (ev.channelID >= m_channels.size()) {
				m_ctx->GetCallbacks()->OnLogWarn(strPrintF("[Enet] Ignoring packet with %d bytes received in out-of-range channel ID %d", (int)ev.packet->dataLength, (int)ev.channelID));
				enet_packet_destroy(ev.packet);
				continue;
			}

			m_channels[ev.channelID].push({ ev.packet, ev.peer });
		}
	}
}

Unet::ServiceType Unet::ServiceEnet::GetType()
{
	return ServiceType::Enet;
}

Unet::ServiceID Unet::ServiceEnet::GetUserID()
{
	//TODO: Use local Mac address or something
	return ServiceID(ServiceType::Enet, 0);
}

std::string Unet::ServiceEnet::GetUserName()
{
	//TODO: Use Windows name or something
	return "";
}

void Unet::ServiceEnet::SetRichPresence(const char* key, const char* value)
{
}

void Unet::ServiceEnet::CreateLobby(LobbyPrivacy privacy, int maxPlayers)
{
	ENetAddress addr;
	addr.host = ENET_HOST_ANY;
	addr.port = UNET_PORT;

	size_t maxChannels = m_numChannels + 2;

	Clear(maxChannels);

	m_host = enet_host_create(&addr, maxPlayers, maxChannels, 0, 0);
	m_peerHost = nullptr;
	m_peers.clear();

	m_waitingForPeers = false;

	auto req = m_ctx->m_callbackCreateLobby.AddServiceRequest(this);
	req->Data->CreatedLobby->AddEntryPoint(AddressToID(addr));
	req->Code = Result::OK;
}

void Unet::ServiceEnet::SetLobbyPrivacy(const ServiceID &lobbyId, LobbyPrivacy privacy)
{
}

void Unet::ServiceEnet::SetLobbyJoinable(const ServiceID &lobbyId, bool joinable)
{
}

void Unet::ServiceEnet::GetLobbyList()
{
	//TODO: Broadcast to LAN

	auto req = m_ctx->m_callbackLobbyList.AddServiceRequest(this);
	req->Code = Result::OK;
}

bool Unet::ServiceEnet::FetchLobbyInfo(const ServiceID &id)
{
	//TODO: Maybe this is possible somehow
	return false;
}

void Unet::ServiceEnet::JoinLobby(const ServiceID &id)
{
	assert(id.Service == ServiceType::Enet);

	m_requestLobbyJoin = m_ctx->m_callbackLobbyJoin.AddServiceRequest(this);

	auto addr = IDToAddress(id);
	size_t maxPeers = 128; //TODO: Make this customizable
	size_t maxChannels = m_numChannels + 2;

	Clear(maxChannels);

	m_host = enet_host_create(nullptr, maxPeers, maxChannels, 0, 0);
	m_peerHost = enet_host_connect(m_host, &addr, maxChannels, 0);

	m_peers.clear();
	m_peers.emplace_back(m_peerHost);

	m_waitingForPeers = true;
}

void Unet::ServiceEnet::LeaveLobby()
{
	m_requestLobbyLeft = m_ctx->m_callbackLobbyLeft.AddServiceRequest(this);

	if (m_peerHost != nullptr) {
		enet_peer_disconnect(m_peerHost, 0);

	} else {
		enet_host_destroy(m_host);
		m_host = nullptr;

		m_requestLobbyLeft->Code = Result::OK;
		m_requestLobbyLeft = nullptr;

		auto currentLobby = m_ctx->CurrentLobby();
		if (currentLobby != nullptr) {
			currentLobby->ServiceDisconnected(ServiceType::Enet);
		}
	}
}

int Unet::ServiceEnet::GetLobbyPlayerCount(const ServiceID &lobbyId)
{
	//TODO
	return m_host->connectedPeers;
}

void Unet::ServiceEnet::SetLobbyMaxPlayers(const ServiceID &lobbyId, int amount)
{
	//TODO
}

int Unet::ServiceEnet::GetLobbyMaxPlayers(const ServiceID &lobbyId)
{
	//TODO
	return (int)m_host->peerCount;
}

std::string Unet::ServiceEnet::GetLobbyData(const ServiceID &lobbyId, const char* name)
{
	return "";
}

int Unet::ServiceEnet::GetLobbyDataCount(const ServiceID &lobbyId)
{
	return 0;
}

Unet::LobbyData Unet::ServiceEnet::GetLobbyData(const ServiceID &lobbyId, int index)
{
	return LobbyData();
}

Unet::ServiceID Unet::ServiceEnet::GetLobbyHost(const ServiceID &lobbyId)
{
	return AddressToID(m_peerHost->address);
}

void Unet::ServiceEnet::SetLobbyData(const ServiceID &lobbyId, const char* name, const char* value)
{
}

void Unet::ServiceEnet::RemoveLobbyData(const ServiceID &lobbyId, const char* name)
{
}

size_t Unet::ServiceEnet::ReliablePacketLimit()
{
	return 0;
}

void Unet::ServiceEnet::SendPacket(const ServiceID &peerId, const void* data, size_t size, PacketType type, uint8_t channel)
{
	auto peer = GetPeer(peerId);
	if (peer == nullptr) {
		m_ctx->GetCallbacks()->OnLogWarn(strPrintF("[Enet] Tried sending packet of %d bytes to unidentified peer 0x%016llX on channel %d", (int)size, peerId.ID, (int)channel));
		return;
	}

	enet_uint32 flags = ENET_PACKET_FLAG_RELIABLE;
	switch (type) {
	case PacketType::Reliable: flags = ENET_PACKET_FLAG_RELIABLE; break;
	case PacketType::Unreliable: flags = 0; break;
	}

	auto packet = enet_packet_create(data, size, flags);
	enet_peer_send(peer, channel, packet);
}

size_t Unet::ServiceEnet::ReadPacket(void* data, size_t maxSize, ServiceID* peerId, uint8_t channel)
{
	if (channel >= m_channels.size()) {
		assert(false);
		return 0;
	}

	auto &queue = m_channels[channel];
	auto &packet = queue.front();

	size_t actualSize = std::min(packet.Packet->dataLength, maxSize);
	memcpy(data, packet.Packet->data, actualSize);

	if (peerId != nullptr) {
		if (packet.Peer == m_peerHost) {
			*peerId = ServiceID(ServiceType::Enet, 0);
		} else {
			*peerId = AddressToID(packet.Peer->address);
		}
	}

	enet_packet_destroy(packet.Packet);
	queue.pop();

	return actualSize;
}

bool Unet::ServiceEnet::IsPacketAvailable(size_t* outPacketSize, uint8_t channel)
{
	if (m_host == nullptr) {
		return false;
	}

	if (channel >= m_channels.size()) {
		assert(false);
		return false;
	}

	auto &queue = m_channels[channel];
	if (queue.size() == 0) {
		return false;
	}

	auto &packet = queue.front();
	if (outPacketSize != nullptr) {
		*outPacketSize = packet.Packet->dataLength;
	}

	return true;
}

ENetPeer* Unet::ServiceEnet::GetPeer(const ServiceID &id)
{
	if (id.IsValid() && id.ID == 0) {
		return m_peerHost;
	}

	for (auto peer : m_peers) {
		if (AddressToID(peer->address) == id) {
			return peer;
		}
	}
	return nullptr;
}

void Unet::ServiceEnet::Clear(size_t numChannels)
{
	for (auto &queue : m_channels) {
		while (queue.size() > 0) {
			auto &packet = queue.front();
			enet_packet_destroy(packet.Packet);
			queue.pop();
		}
	}
	m_channels.clear();

	for (int i = 0; i < (int)numChannels; i++) {
		m_channels.emplace_back(std::queue<EnetPacket>());
	}
}
