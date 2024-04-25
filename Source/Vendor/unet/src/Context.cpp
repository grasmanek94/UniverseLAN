#include <Unet_common.h>
#include <Unet/Context.h>
#include <Unet/Service.h>

#if defined(UNET_MODULE_STEAM)
#	include <Unet/Services/ServiceSteam.h>
#endif

#if defined(UNET_MODULE_GALAXY)
#	include <Unet/Services/ServiceGalaxy.h>
#endif

#if defined(UNET_MODULE_ENET)
#	include <Unet/Services/ServiceEnet.h>
#endif

#include <Unet/LobbyPacket.h>

#include <Unet/xxhash.h>

Unet::Internal::Context::Context(int numChannels)
	: m_reassembly(this)
{
	m_numChannels = numChannels;
	m_queuedMessages.assign(numChannels, std::queue<NetworkMessage*>());

	m_status = ContextStatus::Idle;
	m_primaryService = ServiceType::None;

	m_callbacks = nullptr;

	m_currentLobby = nullptr;
	m_localPeer = -1;
}

Unet::Internal::Context::~Context()
{
	if (m_currentLobby != nullptr) {
		//TODO: Proper leave
		delete m_currentLobby;
	}

	if (m_callbacks != nullptr) {
		delete m_callbacks;
	}

	for (auto service : m_services) {
		delete service;
	}

	for (auto &channel : m_queuedMessages) {
		while (channel.size() > 0) {
			delete channel.front();
			channel.pop();
		}
	}
}

Unet::ContextStatus Unet::Internal::Context::GetStatus()
{
	return m_status;
}

void Unet::Internal::Context::SetCallbacks(ICallbacks* callbacks)
{
	if (m_callbacks != nullptr) {
		delete m_callbacks;
	}
	m_callbacks = callbacks;
}

Unet::ICallbacks* Unet::Internal::Context::GetCallbacks()
{
	return m_callbacks;
}

template<typename TResult, typename TFunc>
static void CheckCallback(Unet::Internal::Context* ctx, Unet::MultiCallback<TResult> &callback, TFunc func)
{
	if (!callback.Ready()) {
		return;
	}

	int numOK = callback.NumOK();
	int numRequests = callback.NumRequests();

	auto &result = callback.GetResult();
	if (numOK > 0) {
		result.Code = Unet::Result::OK;
	} else {
		result.Code = Unet::Result::Error;
	}

	if (numOK < numRequests) {
		ctx->GetCallbacks()->OnLogDebug(Unet::strPrintF("There were some errors in the multi-service callback: %d errors", numRequests - numOK));
	}

	(ctx->*func)(result);

	callback.Clear();
}

void Unet::Internal::Context::RunCallbacks()
{
	for (auto service : m_services) {
		service->RunCallbacks();
	}

	if (m_currentLobby != nullptr) {
		m_currentLobby->HandleOutgoingFileTransfers();
	}

	CheckCallback(this, m_callbackCreateLobby, &Context::OnLobbyCreated);
	CheckCallback(this, m_callbackLobbyList, &Context::OnLobbyList);
	CheckCallback(this, m_callbackLobbyJoin, &Context::OnLobbyJoined);
	CheckCallback(this, m_callbackLobbyLeft, &Context::OnLobbyLeft);

	if (m_status == ContextStatus::Connected && m_currentLobby != nullptr) {
		if (!m_currentLobby->IsConnected()) {
			if (m_callbacks != nullptr) {
				m_callbacks->OnLogError("Connection to lobby was lost");
			}

			LobbyLeftResult result;
			result.Code = Result::OK;
			result.Reason = LeaveReason::Disconnected;
			OnLobbyLeft(result);

		} else {
			auto now = std::chrono::system_clock::now();
			for (auto member : m_currentLobby->m_members) {
				if (member->UnetPeer == m_localPeer) {
					continue;
				}

				if (now < member->NextPingRequest) {
					continue;
				}

				member->SendPing();
			}
		}
	}

	if (m_currentLobby != nullptr) {
		for (auto service : m_services) {
			size_t packetSizeLimit = service->ReliablePacketLimit();

			size_t packetSize;

			if (packetSizeLimit > 0) {
				// Re-assembly for internal lobby message channel
				while (service->IsPacketAvailable(&packetSize, 0)) {
					PrepareReceiveBuffer(packetSize);

					ServiceID peer;
					service->ReadPacket(m_receiveBuffer.data(), packetSize, &peer, 0);
					uint8_t * msgData = m_receiveBuffer.data();

					m_reassembly.HandleMessage(peer, -1, msgData, packetSize);
				}

				// Re-assembly for general purpose channels
				for (int channel = 0; channel < m_numChannels; channel++) {
					while (service->IsPacketAvailable(&packetSize, 2 + channel)) {
						PrepareReceiveBuffer(packetSize);

						ServiceID peer;
						service->ReadPacket(m_receiveBuffer.data(), packetSize, &peer, 2 + channel);
						uint8_t* msgData = m_receiveBuffer.data();

						m_reassembly.HandleMessage(peer, channel, msgData, packetSize);
					}
				}
			}

			// Relay packet channel
			while (service->IsPacketAvailable(&packetSize, 1)) {
				PrepareReceiveBuffer(packetSize);

				ServiceID peer;
				service->ReadPacket(m_receiveBuffer.data(), packetSize, &peer, 1);
				uint8_t* msgData = m_receiveBuffer.data();

				auto peerMember = m_currentLobby->GetMember(peer);

				if (m_currentLobby->m_info.IsHosting) {
					// We have to relay a packet to some client
					uint8_t peerRecipient = *(msgData++);
					uint8_t channel = *(msgData++);
					PacketType type = (PacketType)*(msgData++);
					packetSize -= 3;

					auto recipientMember = m_currentLobby->GetMember((int)peerRecipient);
					if (recipientMember == nullptr) {
						if (m_callbacks != nullptr) {
							m_callbacks->OnLogError(strPrintF("Tried relaying packet of %d bytes to unknown peer %d!", (int)packetSize, (int)peerRecipient));
						}
						continue;
					}

					PrepareSendBuffer(packetSize + 2);
					uint8_t* relayMsg = m_sendBuffer.data();
					relayMsg[0] = (uint8_t)peerMember->UnetPeer;
					relayMsg[1] = channel;
					memcpy(relayMsg + 2, msgData, packetSize);

					auto id = recipientMember->GetDataServiceID();
					assert(id.IsValid());
					if (!id.IsValid()) {
						continue;
					}

					auto recipientService = GetService(id.Service);
					assert(recipientService != nullptr);
					if (recipientService == nullptr) {
						continue;
					}

					recipientService->SendPacket(id, relayMsg, packetSize + 2, type, 1);

				} else {
					// We received a relayed packet from some client
					uint8_t peerSender = *(msgData++);
					uint8_t channel = *(msgData++);
					packetSize -= 2;

					if (channel >= (uint8_t)m_queuedMessages.size()) {
						if (m_callbacks != nullptr) {
							m_callbacks->OnLogError(strPrintF("Invalid channel index in relay packet: %d", (int)channel));
						}
						continue;
					}

					auto memberSender = m_currentLobby->GetMember(peerSender);
					assert(memberSender != nullptr);
					if (memberSender == nullptr) {
						if (m_callbacks != nullptr) {
							m_callbacks->OnLogError(strPrintF("Received a relay packet from unknown peer %d", (int)peerSender));
						}
						continue;
					}

					if (packetSizeLimit > 0) {
						m_reassembly.HandleMessage(memberSender->GetPrimaryServiceID(), (int)channel, msgData, packetSize);
					} else {
						auto newMessage = new NetworkMessage(msgData, packetSize);
						newMessage->m_channel = (int)channel;
						newMessage->m_peer = memberSender->GetPrimaryServiceID();
						m_queuedMessages[channel].push(newMessage);
					}
				}
			}

			if (packetSizeLimit == 0) {
				while (service->IsPacketAvailable(&packetSize, 0)) {
					PrepareReceiveBuffer(packetSize);

					ServiceID peer;
					service->ReadPacket(m_receiveBuffer.data(), packetSize, &peer, 0);

					m_currentLobby->HandleMessage(peer, m_receiveBuffer.data(), packetSize);
				}
			}
		}
	}

	// Pop any fragmented messages into the message queue
	while (auto msg = m_reassembly.PopReady()) {
		if (msg->m_channel == -1) {
			m_currentLobby->HandleMessage(msg->m_peer, msg->m_data, msg->m_size);
			delete msg;
		} else {
			m_queuedMessages[msg->m_channel].push(msg);
		}
	}
}

void Unet::Internal::Context::SetPrimaryService(ServiceType service)
{
	auto s = GetService(service);
	if (s == nullptr) {
		if (m_callbacks != nullptr) {
			m_callbacks->OnLogError(strPrintF("Service %s is not enabled, so it can't be set as the primary service!", GetServiceNameByType(service)));
		}
		return;
	}

	m_primaryService = service;

	auto newName = s->GetUserName();
	if (!newName.empty()) {
		m_personaName = newName;
	}
}

Unet::ServiceType Unet::Internal::Context::GetPrimaryService()
{
	return m_primaryService;
}

void Unet::Internal::Context::EnableService(ServiceType service)
{
	Service* newService = nullptr;
	switch (service) {
#if defined(UNET_MODULE_STEAM)
	case ServiceType::Steam: newService = new ServiceSteam(this, m_numChannels); break;
#endif

#if defined(UNET_MODULE_GALAXY)
	case ServiceType::Galaxy: newService = new ServiceGalaxy(this, m_numChannels); break;
#endif

#if defined(UNET_MODULE_ENET)
	case ServiceType::Enet: newService = new ServiceEnet(this, m_numChannels); break;
#endif

	default: assert(false);
	}

	if (newService == nullptr) {
		if (m_callbacks != nullptr) {
			m_callbacks->OnLogError(strPrintF("Couldn't make new \"%s\" service!", GetServiceNameByType(service)));
		}
		return;
	}

	m_services.emplace_back(newService);

	if (m_primaryService == ServiceType::None) {
		SetPrimaryService(service);
	}
}

int Unet::Internal::Context::ServiceCount()
{
	return (int)m_services.size();
}

void Unet::Internal::Context::SimulateServiceOutage(ServiceType type)
{
	if (m_currentLobby == nullptr) {
		return;
	}

	auto service = GetService(type);
	if (service != nullptr) {
		service->SimulateOutage();
		m_currentLobby->ServiceDisconnected(type);
	}
}

void Unet::Internal::Context::CreateLobby(LobbyPrivacy privacy, int maxPlayers, const char* name)
{
	m_status = ContextStatus::Connecting;

	m_callbackCreateLobby.Begin();

	m_localGuid = xg::newGuid();
	m_localPeer = 0;

	for (auto &channel : m_queuedMessages) {
		while (channel.size() > 0) {
			delete channel.front();
			channel.pop();
		}
	}

	auto &result = m_callbackCreateLobby.GetResult();
	LobbyInfo newLobbyInfo;
	newLobbyInfo.IsHosting = true;
	newLobbyInfo.Privacy = privacy;
	newLobbyInfo.NumPlayers = 1;
	newLobbyInfo.MaxPlayers = maxPlayers;
	newLobbyInfo.UnetGuid = xg::newGuid();
	if (name != nullptr) {
		newLobbyInfo.Name = name;
	}
	result.CreatedLobby = new Lobby(this, newLobbyInfo);

	for (auto service : m_services) {
		service->CreateLobby(privacy, maxPlayers);
	}
}

void Unet::Internal::Context::GetLobbyList(const LobbyListFilter &filter)
{
	m_callbackLobbyList.Begin();

	auto &result = m_callbackLobbyList.GetResult();
	result.Ctx = this;
	result.Filter = filter;

	for (auto service : m_services) {
		service->GetLobbyList();
	}
}

bool Unet::Internal::Context::FetchLobbyInfo(const ServiceID &id)
{
	auto service = GetService(id.Service);
	if (service == nullptr) {
		if (m_callbacks != nullptr) {
			m_callbacks->OnLogError(strPrintF("Can't fetch info for lobby with service ID for %s, service is not enabled!", GetServiceNameByType(id.Service)));
		}
		return false;
	}

	return service->FetchLobbyInfo(id);
}

void Unet::Internal::Context::JoinLobby(const LobbyInfo &lobbyInfo)
{
	if (m_status != ContextStatus::Idle) {
		if (m_callbacks != nullptr) {
			m_callbacks->OnLogWarn("Can't join new lobby while still in a lobby!");
		}
		return;
	}

	m_status = ContextStatus::Connecting;

	m_callbackLobbyJoin.Begin();

	m_localGuid = xg::newGuid();
	m_localPeer = -1;

	for (auto &channel : m_queuedMessages) {
		while (channel.size() > 0) {
			delete channel.front();
			channel.pop();
		}
	}

	auto &result = m_callbackLobbyJoin.GetResult();
	result.JoinGuid = m_localGuid;
	result.JoinedLobby = new Lobby(this, lobbyInfo);

	for (auto service : m_services) {
		auto entry = lobbyInfo.GetEntryPoint(service->GetType());
		if (entry != nullptr) {
			service->JoinLobby(*entry);
		}
	}
}

void Unet::Internal::Context::JoinLobby(const ServiceID &id)
{
	if (m_status != ContextStatus::Idle) {
		if (m_callbacks != nullptr) {
			m_callbacks->OnLogError("Can't join new lobby while still in a lobby!");
		}
		return;
	}

	auto service = GetService(id.Service);
	if (service == nullptr) {
		if (m_callbacks != nullptr) {
			m_callbacks->OnLogError(strPrintF("Can't join lobby with service ID for %s, service is not enabled!", GetServiceNameByType(id.Service)));
		}
		return;
	}

	m_status = ContextStatus::Connecting;

	m_callbackLobbyJoin.Begin();

	m_localGuid = xg::newGuid();
	m_localPeer = -1;

	auto &result = m_callbackLobbyJoin.GetResult();
	result.JoinGuid = m_localGuid;

	LobbyInfo newLobbyInfo;
	newLobbyInfo.EntryPoints.emplace_back(id);
	result.JoinedLobby = new Lobby(this, newLobbyInfo);

	service->JoinLobby(id);
}

void Unet::Internal::Context::LeaveLobby(LeaveReason reason)
{
	if (m_status == ContextStatus::Connected) {
		m_callbackLobbyLeft.Begin();
		m_callbackLobbyLeft.GetResult().Reason = reason;

		for (auto service : m_services) {
			service->LeaveLobby();
		}

	} else if (m_status == ContextStatus::Connecting) {
		//TODO: Proper cancelation

	} else {
		if (m_currentLobby != nullptr) {
			delete m_currentLobby;
			m_currentLobby = nullptr;
		}

		m_status = ContextStatus::Idle;
	}
}

void Unet::Internal::Context::KickMember(LobbyMember* member)
{
	if (!m_currentLobby->m_info.IsHosting) {
		if (m_callbacks != nullptr) {
			m_callbacks->OnLogError("Can't kick members when not hosting!");
		}
		return;
	}

	json js;
	js["t"] = (uint8_t)LobbyPacketType::MemberKick;
	InternalSendTo(member, js);
}

bool Unet::Internal::Context::IsHosting()
{
	if (m_currentLobby == nullptr) {
		return false;
	}

	return m_currentLobby->GetInfo().IsHosting;
}

Unet::Lobby* Unet::Internal::Context::CurrentLobby()
{
	return m_currentLobby;
}

int Unet::Internal::Context::GetLocalPeer()
{
	return m_localPeer;
}

xg::Guid Unet::Internal::Context::GetLocalGuid()
{
	return m_localGuid;
}

void Unet::Internal::Context::SetPersonaName(const char* str)
{
	m_personaName = str;

	if (m_currentLobby != nullptr) {
		auto localMember = m_currentLobby->GetMember(m_localPeer);
		assert(localMember != nullptr);
		if (localMember != nullptr) {
			localMember->Name = str;
		}

		if (m_currentLobby->m_info.IsHosting) {
			json js;
			js["t"] = (uint8_t)LobbyPacketType::LobbyMemberNameChanged;
			js["guid"] = m_localGuid.str();
			js["name"] = str;
			InternalSendToAll(js);

		} else {
			json js;
			js["t"] = (uint8_t)LobbyPacketType::LobbyMemberNameChanged;
			js["name"] = str;
			InternalSendToHost(js);
		}
	}
}

const char* Unet::Internal::Context::GetPersonaName()
{
	return m_personaName.c_str();
}

void Unet::Internal::Context::AddFile(const char* filename, const char* filenameOnDisk)
{
	if (m_currentLobby == nullptr) {
		return;
	}

	auto localMember = m_currentLobby->GetMember(m_localPeer);
	assert(localMember != nullptr);
	if (localMember == nullptr) {
		return;
	}

	localMember->AddFile(filename, filenameOnDisk);
}

void Unet::Internal::Context::AddFile(const char* filename, uint8_t* buffer, size_t size)
{
	if (m_currentLobby == nullptr) {
		return;
	}

	auto localMember = m_currentLobby->GetMember(m_localPeer);
	assert(localMember != nullptr);
	if (localMember == nullptr) {
		return;
	}

	localMember->AddFile(filename, buffer, size);
}

void Unet::Internal::Context::RemoveFile(const char* filename)
{
	if (m_currentLobby == nullptr) {
		return;
	}

	auto localMember = m_currentLobby->GetMember(m_localPeer);
	assert(localMember != nullptr);
	if (localMember == nullptr) {
		return;
	}

	localMember->RemoveFile(filename);
}

void Unet::Internal::Context::RequestFile(LobbyMember* member, const char* filename)
{
	auto file = member->GetFile(filename);
	if (file == nullptr) {
		if (m_callbacks != nullptr) {
			m_callbacks->OnLogError(strPrintF("Couldn't find file \"%s\" on member!", filename));
		}
		return;
	}

	RequestFile(member, file);
}

void Unet::Internal::Context::RequestFile(LobbyMember* member, LobbyFile* file)
{
	if (file->IsValid()) {
		if (m_callbacks != nullptr) {
			m_callbacks->OnLogError(strPrintF("Attempted requesting file \"%s\" from member, but the file is already valid!", file->m_filename.c_str()));
		}
		return;
	}

	json js;
	js["t"] = (uint8_t)LobbyPacketType::LobbyFileRequested;
	js["filename"] = file->m_filename;
	InternalSendTo(member, js);
}

void Unet::Internal::Context::SendChat(const char* message)
{
	if (m_currentLobby == nullptr) {
		return;
	}

	if (m_callbacks != nullptr) {
		auto localMember = m_currentLobby->GetMember(m_localGuid);
		if (m_callbacks != nullptr) {
			m_callbacks->OnLobbyChat(localMember, message);
		}
	}

	if (m_currentLobby->m_info.IsHosting) {
		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyChatMessage;
		js["guid"] = m_localGuid.str();
		js["text"] = message;
		InternalSendToAll(js);

	} else {
		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyChatMessage;
		js["text"] = message;
		InternalSendToHost(js);
	}
}

bool Unet::Internal::Context::IsMessageAvailable(int channel)
{
	if (channel < 0) {
		return false;
	}

	if (channel < (int)m_queuedMessages.size()) {
		auto &queuedChannel = m_queuedMessages[channel];
		if (queuedChannel.size() > 0) {
			return true;
		}
	}

	for (auto service : m_services) {
		// For services that have a reliable packet limit, we only allow queued messages
		if (service->ReliablePacketLimit() > 0) {
			continue;
		}

		if (service->IsPacketAvailable(nullptr, 2 + channel)) {
			return true;
		}
	}

	return false;
}

Unet::NetworkMessageRef Unet::Internal::Context::ReadMessage(int channel)
{
	if (channel < 0) {
		return nullptr;
	}

	if (channel < (int)m_queuedMessages.size()) {
		auto &queuedChannel = m_queuedMessages[channel];
		if (queuedChannel.size() > 0) {
			NetworkMessageRef ret(queuedChannel.front());
			queuedChannel.pop();
			return ret;
		}
	}

	for (auto service : m_services) {
		// For services that have a reliable packet limit, we only allow queued messages
		//TODO: Optimization: Unreliable packets can still be read from here without issue! The first byte
		//      will have the 0x80 bit set to 0 if the packet is unreliable. If we read this byte, we can
		//      just return the message from there.
		if (service->ReliablePacketLimit() > 0) {
			continue;
		}

		size_t packetSize;
		if (service->IsPacketAvailable(&packetSize, 2 + channel)) {
			//TODO: Optimization: Don't allocate memory for every message! We could send a local value instead
			//      and leave the message allocation to RunCallbacks() for packets that need re-assembly.
			NetworkMessageRef newMessage(new NetworkMessage(packetSize));
			newMessage->m_channel = channel;
			newMessage->m_size = service->ReadPacket(newMessage->m_data, packetSize, &newMessage->m_peer, 2 + channel);
			return newMessage;
		}
	}

	return nullptr;
}

void Unet::Internal::Context::SendTo_Impl(LobbyMember* member, uint8_t* data, size_t size, PacketType type, uint8_t channel)
{
	// Sending a message to yourself isn't very useful.
	assert(member->UnetPeer != m_localPeer);
	if (member->UnetPeer == m_localPeer) {
		return;
	}

	auto id = member->GetDataServiceID();
	auto service = GetService(id.Service);

	if (!id.IsValid() || service == nullptr) {
		// Data service to peer is not available, so we have to relay it through the host
		auto hostMember = m_currentLobby->GetHostMember();
		assert(hostMember != nullptr);

		auto idHost = hostMember->GetDataServiceID();
		assert(idHost.IsValid());
		auto serviceHost = GetService(idHost.Service);
		assert(serviceHost != nullptr);

		PrepareSendBuffer(size + 3);

		uint8_t* msg = m_sendBuffer.data();
		msg[0] = (uint8_t)member->UnetPeer;
		msg[1] = channel;
		msg[2] = (uint8_t)type;
		memcpy(msg + 3, data, size);

		serviceHost->SendPacket(idHost, msg, size + 3, type, 1);
		return;
	}

	service->SendPacket(id, data, size, type, channel + 2);
}

void Unet::Internal::Context::SendTo(LobbyMember* member, uint8_t* data, size_t size, PacketType type, uint8_t channel)
{
	auto id = member->GetDataServiceID();

	auto service = GetService(id.Service);
	if (service == nullptr) {
		return;
	}

	size_t sizeLimit = service->ReliablePacketLimit();

	if (type == PacketType::Reliable) {
		if (sizeLimit == 0) {
			SendTo_Impl(member, data, size, PacketType::Reliable, channel);
			return;
		}

		m_reassembly.SplitMessage(data, size, type, sizeLimit, [this, member, channel](uint8_t * data, size_t size) {
			SendTo_Impl(member, data, size, PacketType::Reliable, channel);
		});

	} else {
		if (sizeLimit == 0) {
			SendTo_Impl(member, data, size, type, channel);
			return;
		}

		PrepareSendBuffer(size + 1);
		m_sendBuffer[0] = 0;
		memcpy(m_sendBuffer.data() + 1, data, size);
		SendTo_Impl(member, m_sendBuffer.data(), size + 1, type, channel);
	}
}

void Unet::Internal::Context::SendToAll(uint8_t* data, size_t size, PacketType type, uint8_t channel)
{
	assert(m_currentLobby != nullptr);
	if (m_currentLobby == nullptr) {
		return;
	}

	for (auto member : m_currentLobby->m_members) {
		if (!member->Valid) {
			continue;
		}

		if (member->UnetPeer == m_localPeer) {
			continue;
		}

		SendTo(member, data, size, type, channel);
	}
}

void Unet::Internal::Context::SendToAllExcept(LobbyMember* exceptMember, uint8_t* data, size_t size, PacketType type, uint8_t channel)
{
	assert(m_currentLobby != nullptr);
	if (m_currentLobby == nullptr) {
		return;
	}

	for (auto member : m_currentLobby->m_members) {
		if (!member->Valid) {
			continue;
		}

		if (member->UnetPeer == m_localPeer) {
			continue;
		}

		if (member->UnetPeer == exceptMember->UnetPeer) {
			continue;
		}

		SendTo(member, data, size, type, channel);
	}
}

void Unet::Internal::Context::SendToHost(uint8_t* data, size_t size, PacketType type, uint8_t channel)
{
	assert(m_currentLobby != nullptr);
	if (m_currentLobby == nullptr) {
		return;
	}

	auto hostMember = m_currentLobby->GetHostMember();
	assert(hostMember != nullptr);
	if (hostMember == nullptr) {
		return;
	}

	SendTo(hostMember, data, size, type, channel);
}

Unet::Service* Unet::Internal::Context::PrimaryService()
{
	auto ret = GetService(m_primaryService);
	assert(ret != nullptr);
	return ret;
}

Unet::Service* Unet::Internal::Context::GetService(ServiceType type)
{
	for (auto service : m_services) {
		if (service->GetType() == type) {
			return service;
		}
	}
	return nullptr;
}

void Unet::Internal::Context::InternalSendTo(LobbyMember* member, const json &js, uint8_t* binaryData, size_t binarySize)
{
	// Sending a message to yourself isn't very useful.
	assert(member->UnetPeer != m_localPeer);

	auto id = member->GetDataServiceID();
	assert(id.IsValid());
	if (!id.IsValid()) {
		return;
	}

	InternalSendTo(id, js, binaryData, binarySize);
}

void Unet::Internal::Context::InternalSendTo(const ServiceID &id, const json &js, uint8_t* binaryData, size_t binarySize)
{
	//TODO: Implement relaying through host if this is a client-to-client message where there's no compatible connection (eg. Steam to Galaxy communication)
	//NOTE: The above is not important yet for internal messages, as all internal messages are sent between client & server, not client & client

	auto service = GetService(id.Service);
	assert(service != nullptr);
	if (service == nullptr) {
		return;
	}

	auto msg = JsonPack(js);

	size_t finalMsgSize = msg.size() + binarySize + 4;
	PrepareSendBuffer(finalMsgSize);

	uint32_t msgSize = (uint32_t)msg.size();
	memcpy(m_sendBuffer.data(), &msgSize, 4);
	memcpy(m_sendBuffer.data() + 4, msg.data(), msg.size());
	if (binaryData != nullptr && binarySize > 0) {
		memcpy(m_sendBuffer.data() + 4 + msg.size(), binaryData, binarySize);
	}

	size_t sizeLimit = service->ReliablePacketLimit();
	if (sizeLimit == 0) {
		service->SendPacket(id, m_sendBuffer.data(), finalMsgSize, PacketType::Reliable, 0);
		return;
	}

	m_reassembly.SplitMessage(m_sendBuffer.data(), finalMsgSize, PacketType::Reliable, sizeLimit, [service, id](uint8_t* data, size_t size) {
		service->SendPacket(id, data, size, PacketType::Reliable, 0);
	});
}

void Unet::Internal::Context::InternalSendToAll(const json &js, uint8_t* binaryData, size_t binarySize)
{
	assert(m_currentLobby != nullptr);
	if (m_currentLobby == nullptr) {
		return;
	}

	for (auto member : m_currentLobby->m_members) {
		if (member->UnetPeer != m_localPeer) {
			InternalSendTo(member, js, binaryData, binarySize);
		}
	}
}

void Unet::Internal::Context::InternalSendToAllExcept(LobbyMember* exceptMember, const json &js, uint8_t* binaryData, size_t binarySize)
{
	assert(m_currentLobby != nullptr);
	if (m_currentLobby == nullptr) {
		return;
	}

	for (auto member : m_currentLobby->m_members) {
		if (member->UnetPeer != m_localPeer && member->UnetPeer != exceptMember->UnetPeer) {
			InternalSendTo(member, js, binaryData, binarySize);
		}
	}
}

void Unet::Internal::Context::InternalSendToHost(const json &js, uint8_t* binaryData, size_t binarySize)
{
	assert(m_currentLobby != nullptr);
	if (m_currentLobby == nullptr) {
		return;
	}

	auto hostMember = m_currentLobby->GetHostMember();
	if (hostMember != nullptr) {
		InternalSendTo(hostMember, js, binaryData, binarySize);

	} else {
		auto primaryEntryPoint = m_currentLobby->GetPrimaryEntryPoint();
		assert(primaryEntryPoint.IsValid());

		auto service = GetService(primaryEntryPoint.Service);
		assert(service != nullptr);

		auto hostId = service->GetLobbyHost(primaryEntryPoint);
		InternalSendTo(hostId, js, binaryData, binarySize);
	}
}

void Unet::Internal::Context::OnLobbyCreated(const CreateLobbyResult &result)
{
	if (result.Code != Result::OK) {
		m_status = ContextStatus::Idle;
		LeaveLobby();

	} else {
		m_status = ContextStatus::Connected;
		m_currentLobby = result.CreatedLobby;

		auto &lobbyInfo = m_currentLobby->GetInfo();
		auto unetGuid = lobbyInfo.UnetGuid.str();

		m_currentLobby->SetData("unet-guid", unetGuid.c_str());
		m_currentLobby->SetData("unet-name", lobbyInfo.Name.c_str());
		m_currentLobby->SetData("unet-privacy", strPrintF("%d", (int)lobbyInfo.Privacy));

		auto newMember = new LobbyMember(this);
		newMember->UnetGuid = m_localGuid;
		newMember->UnetPeer = 0;
		newMember->UnetPrimaryService = m_primaryService;
		newMember->Name = m_personaName;
		for (auto service : m_services) {
			newMember->IDs.emplace_back(service->GetUserID());
		}
		m_currentLobby->m_members.emplace_back(newMember);
		m_currentLobby->m_info.NumPlayers++;

		m_currentLobby->SetRichPresence();
	}

	if (m_callbacks != nullptr) {
		m_callbacks->OnLobbyCreated(result);
	}
}

void Unet::Internal::Context::OnLobbyList(const LobbyListResult &result)
{
	LobbyListResult newResult(result);

	for (int i = (int)newResult.Lobbies.size() - 1; i >= 0; i--) {
		auto &lobbyInfo = newResult.Lobbies[i];

		bool passesFilter = true;
		for (auto &stringFilter : newResult.Filter.m_stringFilters) {
			std::string value = result.GetLobbyData(lobbyInfo, stringFilter.m_key.c_str());
			if (stringFilter.m_type == LobbyListFilter::StringFilter::Matches) {
				if (value != stringFilter.m_value) {
					passesFilter = false;
					break;
				}
			} else if (stringFilter.m_type == LobbyListFilter::StringFilter::Contains) {
				if (value.find(stringFilter.m_value) == std::string::npos) {
					passesFilter = false;
					break;
				}
			}
		}

		if (!passesFilter) {
			newResult.Lobbies.erase(newResult.Lobbies.begin() + i);
			newResult.NumFiltered++;
			continue;
		}

		lobbyInfo.NumPlayers = result.GetLobbyNumPlayers(lobbyInfo);
		lobbyInfo.MaxPlayers = result.GetLobbyMaxPlayers(lobbyInfo);
		lobbyInfo.Name = result.GetLobbyData(lobbyInfo, "unet-name");
	}

	if (m_callbacks != nullptr) {
		m_callbacks->OnLobbyList(newResult);
	}
}

void Unet::Internal::Context::OnLobbyJoined(const LobbyJoinResult &result)
{
	if (result.Code != Result::OK) {
		m_status = ContextStatus::Idle;
		LeaveLobby();

		if (m_callbacks != nullptr) {
			m_callbacks->OnLobbyJoined(result);
		}
		return;

	} else {
		m_currentLobby = result.JoinedLobby;
		m_currentLobby->SetRichPresence();
	}

	json js;
	js["t"] = (uint8_t)LobbyPacketType::Hello;
	js["name"] = m_personaName;
	InternalSendToHost(js);

	if (m_callbacks != nullptr) {
		m_callbacks->OnLogDebug("Hello sent");
	}
}

void Unet::Internal::Context::OnLobbyLeft(const LobbyLeftResult &result)
{
	m_status = ContextStatus::Idle;
	m_localPeer = -1;

	for (auto &channel : m_queuedMessages) {
		while (channel.size() > 0) {
			delete channel.front();
			channel.pop();
		}
	}

	if (m_callbacks != nullptr) {
		m_callbacks->OnLobbyLeft(result);
	}

	if (m_currentLobby != nullptr) {
		delete m_currentLobby;
		m_currentLobby = nullptr;
	}
}

void Unet::Internal::Context::OnLobbyPlayerLeft(LobbyMember* member)
{
	if (!member->Valid) {
		return;
	}

	if (m_currentLobby->m_info.IsHosting) {
		json js;
		js["t"] = (uint8_t)LobbyPacketType::MemberLeft;
		js["guid"] = member->UnetGuid.str();
		InternalSendToAll(js);
	}

	if (m_callbacks != nullptr) {
		m_callbacks->OnLobbyPlayerLeft(member);
	}
}

void Unet::Internal::Context::PrepareReceiveBuffer(size_t size)
{
	if (m_receiveBuffer.size() < size) {
		m_receiveBuffer.resize((size_t)(size * 1.5));
	}
}

void Unet::Internal::Context::PrepareSendBuffer(size_t size)
{
	if (m_sendBuffer.size() < size) {
		m_sendBuffer.resize((size_t)(size * 1.5));
	}
}
