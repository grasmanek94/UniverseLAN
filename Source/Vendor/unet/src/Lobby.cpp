#include <Unet_common.h>
#include <Unet/Lobby.h>
#include <Unet/Context.h>
#include <Unet/LobbyPacket.h>

Unet::Lobby::Lobby(Internal::Context* ctx, const LobbyInfo &lobbyInfo)
{
	m_ctx = ctx;
	m_info = lobbyInfo;
	m_info.EntryPoints.clear();
}

Unet::Lobby::~Lobby()
{
	for (auto member : m_members) {
		delete member;
	}
}

const Unet::LobbyInfo &Unet::Lobby::GetInfo()
{
	return m_info;
}

bool Unet::Lobby::IsConnected()
{
	return m_info.EntryPoints.size() > 0;
}

Unet::ServiceID Unet::Lobby::GetPrimaryEntryPoint()
{
	if (m_info.EntryPoints.size() == 0) {
		return ServiceID();
	}

	auto primaryEntryPoint = m_info.GetEntryPoint(m_ctx->m_primaryService);
	if (primaryEntryPoint != nullptr) {
		return *primaryEntryPoint;
	}

	return m_info.EntryPoints[0];
}

const std::vector<Unet::LobbyMember*> &Unet::Lobby::GetMembers()
{
	return m_members;
}

Unet::LobbyMember* Unet::Lobby::GetMember(const xg::Guid &guid)
{
	for (auto member : m_members) {
		if (member->UnetGuid == guid) {
			return member;
		}
	}
	return nullptr;
}

Unet::LobbyMember* Unet::Lobby::GetMember(int peer)
{
	for (auto member : m_members) {
		if (member->UnetPeer == peer) {
			return member;
		}
	}
	return nullptr;
}

Unet::LobbyMember* Unet::Lobby::GetMember(const ServiceID &serviceId)
{
	for (auto member : m_members) {
		for (auto &id : member->IDs) {
			if (id == serviceId) {
				return member;
			}
		}
	}
	return nullptr;
}

Unet::LobbyMember* Unet::Lobby::GetHostMember()
{
	return GetMember(0);
}

void Unet::Lobby::HandleMessage(const ServiceID &peer, uint8_t* data, size_t size)
{
	m_ctx->GetCallbacks()->OnLogDebug(strPrintF("Handle lobby message of %d bytes", (int)size));

	auto peerMember = GetMember(peer);

	uint32_t sizeJson = *(uint32_t*)data;

	uint8_t* binaryData = data + 4 + sizeJson;
	size_t binarySize = size - 4 - sizeJson;

	json js = JsonUnpack(data + 4, sizeJson);
	if (!js.is_object() || !js.contains("t")) {
		m_ctx->GetCallbacks()->OnLogError(strPrintF("[P2P] [%s] Message from 0x%016llX is not a valid data object!", GetServiceNameByType(peer.Service), peer.ID));
		return;
	}

	auto jsDump = js.dump();
	m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[P2P] [%s] Message object: \"%s\"", GetServiceNameByType(peer.Service), jsDump.c_str()));

	auto type = (LobbyPacketType)(uint8_t)js["t"];

	if (type == LobbyPacketType::Handshake) {
		if (!m_info.IsHosting) {
			return;
		}

		xg::Guid guid(js["guid"].get<std::string>());
		auto member = AddMemberService(guid, peer);

		if (member->Valid) {
			js = json::object();
			js["t"] = (uint8_t)LobbyPacketType::MemberNewService;
			js["guid"] = guid.str();
			js["service"] = (int)peer.Service;
			js["id"] = peer.ID;
			m_ctx->InternalSendToAll(js);
		}

	} else if (type == LobbyPacketType::Hello) {
		if (!m_info.IsHosting) {
			return;
		}

		auto member = GetMember(peer);
		if (member == nullptr) {
			m_ctx->GetCallbacks()->OnLogWarn(strPrintF("Received Hello packet from %s ID 0x%016llX before receiving any handshakes!",
				GetServiceNameByType(peer.Service), peer.ID
			));
			return;
		}

		// Update member
		member->Name = js["name"].get<std::string>();
		member->UnetPrimaryService = peer.Service;
		member->Valid = true;

		// Send LobbyInfo to new member
		js = json::object();
		js["t"] = (uint8_t)LobbyPacketType::LobbyInfo;
		js["data"] = SerializeData();
		js["members"] = json::array();
		for (auto member : m_members) {
			if (member->Valid) {
				js["members"].emplace_back(member->Serialize());
			}
		}
		m_ctx->InternalSendTo(member, js);

		// Send MemberInfo to existing members
		js = member->Serialize();
		js["t"] = (uint8_t)LobbyPacketType::MemberInfo;
		m_ctx->InternalSendToAllExcept(member, js);

		// Run callback
		m_ctx->GetCallbacks()->OnLobbyPlayerJoined(member);

	} else if (type == LobbyPacketType::Ping) {
		js = json::object();
		js["t"] = (uint8_t)LobbyPacketType::Pong;
		m_ctx->InternalSendTo(peer, js);

	} else if (type == LobbyPacketType::Pong) {
		auto member = GetMember(peer);
		if (member->UnetPeer != m_ctx->m_localPeer && member->LastPingRequest.time_since_epoch().count() > 0) {
			auto now = std::chrono::high_resolution_clock::now();
			auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - member->LastPingRequest);
			member->Ping = (int)dt.count();
			member->LastPingRequest = std::chrono::high_resolution_clock::time_point();
		}

	} else if (type == LobbyPacketType::LobbyInfo) {
		if (m_info.IsHosting) {
			return;
		}

		DeserializeData(js["data"]);
		m_info.Name = GetData("unet-name");
		m_info.UnetGuid = xg::Guid(GetData("unet-guid"));

		std::string strPrivacy = GetData("unet-privacy");
		m_info.Privacy = (LobbyPrivacy)atoi(strPrivacy.c_str());

		for (auto &member : js["members"]) {
			DeserializeMember(member);
		}

		for (auto member : m_members) {
			if (member->UnetGuid == m_ctx->m_localGuid) {
				m_ctx->m_localPeer = member->UnetPeer;
			}
		}

		m_ctx->m_status = ContextStatus::Connected;

		LobbyJoinResult result;
		result.Code = Result::OK;
		result.JoinedLobby = this;
		m_ctx->GetCallbacks()->OnLobbyJoined(result);

	} else if (type == LobbyPacketType::MemberInfo) {
		if (m_info.IsHosting) {
			return;
		}

		auto member = DeserializeMember(js);
		m_ctx->GetCallbacks()->OnLobbyPlayerJoined(member);

	} else if (type == LobbyPacketType::MemberLeft) {
		if (m_info.IsHosting) {
			return;
		}

		xg::Guid guid(js["guid"].get<std::string>());

		auto member = GetMember(guid);
		assert(member != nullptr);
		if (member == nullptr) {
			return;
		}

		RemoveMember(member);

	} else if (type == LobbyPacketType::MemberKick) {
		if (m_info.IsHosting) {
			return;
		}

		m_ctx->LeaveLobby(LeaveReason::Kicked);

	} else if (type == LobbyPacketType::MemberNewService) {
		if (m_info.IsHosting) {
			return;
		}

		xg::Guid guid(js["guid"].get<std::string>());

		ServiceID id;
		id.Service = (ServiceType)js["service"].get<int>();
		id.ID = js["id"].get<uint64_t>();

		AddMemberService(guid, id);

	} else if (type == LobbyPacketType::LobbyName) {
		if (m_info.IsHosting) {
			return;
		}

		auto name = js["name"].get<std::string>();
		SetName(name);

	} else if (type == LobbyPacketType::LobbyMaxPlayers) {
		if (m_info.IsHosting) {
			return;
		}

		auto amount = js["amount"].get<int>();
		SetMaxPlayers(amount);

	} else if (type == LobbyPacketType::LobbyData) {
		if (m_info.IsHosting) {
			return;
		}

		auto name = js["name"].get<std::string>();
		auto value = js["value"].get<std::string>();

		InternalSetData(name, value);
		m_ctx->GetCallbacks()->OnLobbyDataChanged(name);

	} else if (type == LobbyPacketType::LobbyDataRemoved) {
		if (m_info.IsHosting) {
			return;
		}

		auto name = js["name"].get<std::string>();

		InternalRemoveData(name);
		m_ctx->GetCallbacks()->OnLobbyDataChanged(name);

	} else if (type == LobbyPacketType::LobbyMemberData) {
		auto name = js["name"].get<std::string>();
		auto value = js["value"].get<std::string>();

		if (m_info.IsHosting) {
			peerMember->InternalSetData(name, value);

			js = json::object();
			js["t"] = (uint8_t)LobbyPacketType::LobbyMemberData;
			js["guid"] = peerMember->UnetGuid.str();
			js["name"] = name;
			js["value"] = value;
			m_ctx->InternalSendToAll(js);

			m_ctx->GetCallbacks()->OnLobbyMemberDataChanged(peerMember, name);

		} else {
			xg::Guid guid(js["guid"].get<std::string>());

			auto member = GetMember(guid);
			assert(member != nullptr);
			if (member == nullptr) {
				return;
			}

			member->InternalSetData(name, value);
			m_ctx->GetCallbacks()->OnLobbyMemberDataChanged(member, name);
		}

	} else if (type == LobbyPacketType::LobbyMemberDataRemoved) {
		auto name = js["name"].get<std::string>();

		if (m_info.IsHosting) {
			peerMember->InternalRemoveData(name);

			js = json::object();
			js["t"] = (uint8_t)LobbyPacketType::LobbyMemberData;
			js["guid"] = peerMember->UnetGuid.str();
			js["name"] = name;
			m_ctx->InternalSendToAll(js);

			m_ctx->GetCallbacks()->OnLobbyMemberDataChanged(peerMember, name);

		} else {
			xg::Guid guid(js["guid"].get<std::string>());

			auto member = GetMember(guid);
			assert(member != nullptr);
			if (member == nullptr) {
				return;
			}

			member->InternalRemoveData(name);
			m_ctx->GetCallbacks()->OnLobbyMemberDataChanged(member, name);
		}

	} else if (type == LobbyPacketType::LobbyMemberNameChanged) {
		auto name = js["name"].get<std::string>();

		if (m_info.IsHosting) {
			std::string oldname = peerMember->Name;
			peerMember->Name = name;

			js = json::object();
			js["t"] = (uint8_t)LobbyPacketType::LobbyMemberNameChanged;
			js["guid"] = peerMember->UnetGuid.str();
			js["name"] = name;
			m_ctx->InternalSendToAllExcept(peerMember, js);

			m_ctx->GetCallbacks()->OnLobbyMemberNameChanged(peerMember, oldname);

		} else {
			xg::Guid guid(js["guid"].get<std::string>());

			auto member = GetMember(guid);
			assert(member != nullptr);
			if (member == nullptr) {
				return;
			}

			std::string oldname = member->Name;
			member->Name = name;
			m_ctx->GetCallbacks()->OnLobbyMemberNameChanged(member, oldname);
		}

	} else if (type == LobbyPacketType::LobbyFileAdded) {
		auto filename = js["filename"].get<std::string>();
		auto size = js["size"].get<size_t>();
		auto hash = js["hash"].get<uint64_t>();

		auto newFile = new LobbyFile(filename);
		newFile->Prepare(size, hash);
		newFile->LoadFromCache();

		if (m_info.IsHosting) {
			peerMember->Files.emplace_back(newFile);

			js = json::object();
			js["t"] = (uint8_t)LobbyPacketType::LobbyFileAdded;
			js["guid"] = peerMember->UnetGuid.str();
			js["filename"] = filename;
			js["size"] = size;
			js["hash"] = hash;
			m_ctx->InternalSendToAllExcept(peerMember, js);

			m_ctx->GetCallbacks()->OnLobbyFileAdded(peerMember, newFile);

		} else {
			xg::Guid guid(js["guid"].get<std::string>());

			auto member = GetMember(guid);
			assert(member != nullptr);
			if (member == nullptr) {
				delete newFile;
				return;
			}

			member->Files.emplace_back(newFile);
			m_ctx->GetCallbacks()->OnLobbyFileAdded(member, newFile);
		}

	} else if (type == LobbyPacketType::LobbyFileRemoved) {
		auto filename = js["filename"].get<std::string>();

		if (m_info.IsHosting) {
			peerMember->InternalRemoveFile(filename);

			js = json::object();
			js["t"] = (uint8_t)LobbyPacketType::LobbyFileRemoved;
			js["guid"] = peerMember->UnetGuid.str();
			js["filename"] = filename;
			m_ctx->InternalSendToAllExcept(peerMember, js);

			m_ctx->GetCallbacks()->OnLobbyFileRemoved(peerMember, filename);

		} else {
			xg::Guid guid(js["guid"].get<std::string>());

			auto member = GetMember(guid);
			assert(member != nullptr);
			if (member == nullptr) {
				return;
			}

			member->InternalRemoveFile(filename);
			m_ctx->GetCallbacks()->OnLobbyFileRemoved(member, filename);
		}

	} else if (type == LobbyPacketType::LobbyFileRequested) {
		auto filename = js["filename"].get<std::string>();

		auto localMember = GetMember(m_ctx->m_localPeer);
		auto file = localMember->GetFile(filename);
		if (file == nullptr) {
			m_ctx->GetCallbacks()->OnLogWarn(strPrintF("Peer %d tried requesting file \"%s\" which we don't have!", (int)peerMember->UnetPeer, filename.c_str()));
			return;
		}

		if (!file->IsValid()) {
			m_ctx->GetCallbacks()->OnLogWarn(strPrintF("Peer %d tried requesting file \"%s\" which is not valid for us! (This should never happen!)", (int)peerMember->UnetPeer, filename.c_str()));
			return;
		}

		m_ctx->GetCallbacks()->OnLobbyFileRequested(peerMember, file);

		OutgoingFileTransfer newTransfer;
		newTransfer.FileHash = file->m_hash;
		newTransfer.MemberPeer = peerMember->UnetPeer;
		m_outgoingFileTransfers.emplace_back(newTransfer);

	} else if (type == LobbyPacketType::LobbyFileData) {
		auto filename = js["filename"].get<std::string>();

		auto file = peerMember->GetFile(filename);
		if (file == nullptr) {
			m_ctx->GetCallbacks()->OnLogWarn(strPrintF("Peer %d sent us data for file \"%s\" which they don't have!", (int)peerMember->UnetPeer, filename.c_str()));
			return;
		}

		//TODO: Verify that we actually requested this file

		file->AppendData(binaryData, binarySize);

		m_ctx->GetCallbacks()->OnLobbyFileDataReceiveProgress(peerMember, file);
		if (file->m_availableSize == file->m_size) {
			m_ctx->GetCallbacks()->OnLobbyFileDataReceiveFinished(peerMember, file, file->IsValid());
			file->SaveToCache();
		}

	} else if (type == LobbyPacketType::LobbyChatMessage) {
		auto text = js["text"].get<std::string>();

		if (m_info.IsHosting) {
			m_ctx->GetCallbacks()->OnLobbyChat(peerMember, text.c_str());

			js = json::object();
			js["t"] = (uint8_t)LobbyPacketType::LobbyChatMessage;
			js["guid"] = peerMember->UnetGuid.str();
			js["text"] = text;
			m_ctx->InternalSendToAllExcept(peerMember, js);

		} else {
			xg::Guid guid(js["guid"].get<std::string>());

			auto member = GetMember(guid);
			assert(member != nullptr);
			if (member == nullptr) {
				return;
			}

			m_ctx->GetCallbacks()->OnLobbyChat(member, text.c_str());
		}

	} else {
		m_ctx->GetCallbacks()->OnLogWarn(strPrintF("P2P packet type was not recognized: %d", (int)type));
	}
}

Unet::LobbyMember* Unet::Lobby::DeserializeMember(const json &member)
{
	xg::Guid guid(member["guid"].get<std::string>());

	for (auto &memberId : member["ids"]) {
		auto service = (Unet::ServiceType)memberId[0].get<int>();
		auto id = memberId[1].get<uint64_t>();

		AddMemberService(guid, Unet::ServiceID(service, id));
	}

	auto lobbyMember = GetMember(guid);
	assert(lobbyMember != nullptr); // If this fails, there's no service IDs given for this member

	lobbyMember->Deserialize(member);

	return lobbyMember;
}

void Unet::Lobby::AddEntryPoint(const ServiceID &entryPoint)
{
	auto entry = m_info.GetEntryPoint(entryPoint.Service);
	if (entry != nullptr) {
		if (entry->ID != entryPoint.ID) {
			m_ctx->GetCallbacks()->OnLogWarn(strPrintF("Tried adding an entry point for service %s that already exists, with different ID's! Old: 0x%016llX, new: 0x%016llX. Keeping old!",
				GetServiceNameByType(entry->Service),
				entry->ID, entryPoint.ID
			));
		}
		return;
	}
	m_info.EntryPoints.emplace_back(entryPoint);
}

void Unet::Lobby::ServiceDisconnected(ServiceType service)
{
	auto it = std::find_if(m_info.EntryPoints.begin(), m_info.EntryPoints.end(), [service](const ServiceID & entryPoint) {
		return entryPoint.Service == service;
	});

	if (it == m_info.EntryPoints.end()) {
		return;
	}

	m_info.EntryPoints.erase(it);

	for (auto member : m_members) {
		for (int i = (int)member->IDs.size() - 1; i >= 0; i--) {
			if (member->IDs[i].Service == service) {
				RemoveMemberService(member->IDs[i]);
			}
		}
	}

	if (IsConnected()) {
		m_ctx->GetCallbacks()->OnLogWarn(strPrintF("Lost connection to entry point %s (%d points still open)", GetServiceNameByType(service), (int)m_info.EntryPoints.size()));
		SetRichPresence();
	} else {
		m_ctx->GetCallbacks()->OnLogError("Lost connection to all entry points!");

		LobbyLeftResult result;
		result.Code = Result::OK;
		result.Reason = LeaveReason::Disconnected;
		m_ctx->OnLobbyLeft(result);
	}
}

Unet::LobbyMember* Unet::Lobby::AddMemberService(const xg::Guid &guid, const ServiceID &id)
{
	for (size_t i = 0; i < m_members.size(); i++) {
		bool foundMember = false;
		auto member = m_members[i];

		if (member->UnetGuid == guid) {
			continue;
		}

		for (auto &memberId : member->IDs) {
			if (memberId != id) {
				continue;
			}

			auto strGuid = guid.str();
			auto strExistingGuid = member->UnetGuid.str();

			m_ctx->GetCallbacks()->OnLogWarn(strPrintF("Tried adding %s ID 0x%016llX to member with guid %s, but another member with guid %s already has this ID! Assuming existing member is no longer connected, removing from member list.",
				GetServiceNameByType(id.Service), id.ID,
				strGuid.c_str(), strExistingGuid.c_str()
			));

			m_members.erase(m_members.begin() + i);
			m_info.NumPlayers--;
			foundMember = true;
			break;
		}

		if (foundMember) {
			break;
		}
	}

	for (auto member : m_members) {
		if (member->UnetGuid == guid) {
			auto existingId = member->GetServiceID(id.Service);
			if (existingId.IsValid()) {
				auto strGuid = guid.str();
				m_ctx->GetCallbacks()->OnLogWarn(strPrintF("Tried adding player service %s for guid %s, but it already exists!",
					GetServiceNameByType(id.Service), strGuid.c_str()
				));
			} else {
				member->IDs.emplace_back(id);
			}
			return member;
		}
	}

	auto newMember = new LobbyMember(m_ctx);
	newMember->Valid = false;
	newMember->UnetGuid = guid;
	newMember->UnetPeer = GetNextAvailablePeer();
	newMember->IDs.emplace_back(id);
	m_members.emplace_back(newMember);
	m_info.NumPlayers++;

	return newMember;
}

void Unet::Lobby::RemoveMemberService(const ServiceID &id)
{
	auto member = GetMember(id);
	if (member == nullptr) {
		return;
	}

	auto it = std::find(member->IDs.begin(), member->IDs.end(), id);
	assert(it != member->IDs.end());
	if (it == member->IDs.end()) {
		return;
	}

	member->IDs.erase(it);
	if (member->IDs.size() == 0) {
		auto itMember = std::find(m_members.begin(), m_members.end(), member);
		if (itMember != m_members.end()) {
			m_members.erase(itMember);
			m_info.NumPlayers--;
		}

		m_ctx->OnLobbyPlayerLeft(member);
		delete member;
	}
}

void Unet::Lobby::RemoveMember(LobbyMember* member)
{
	auto it = std::find(m_members.begin(), m_members.end(), member);
	assert(it != m_members.end());

	m_members.erase(it);
	m_info.NumPlayers--;

	m_ctx->OnLobbyPlayerLeft(member);
	delete member;
}

void Unet::Lobby::SetName(const std::string &name)
{
	if (m_info.Name == name) {
		return;
	}

	std::string oldname = m_info.Name;
	m_info.Name = name;

	if (m_info.IsHosting) {
		for (auto &entryPoint : m_info.EntryPoints) {
			auto service = m_ctx->GetService(entryPoint.Service);
			assert(service != nullptr);
			service->SetLobbyData(entryPoint, "unet-name", name.c_str());
		}

		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyName;
		js["name"] = name;
		m_ctx->InternalSendToAll(js);
	}

	m_ctx->GetCallbacks()->OnLobbyNameChanged(oldname, name);
}

void Unet::Lobby::SetMaxPlayers(int amount)
{
	if (m_info.MaxPlayers == amount) {
		return;
	}

	int oldamount = m_info.MaxPlayers;
	m_info.MaxPlayers = amount;

	if (m_info.IsHosting) {
		for (auto &entryPoint : m_info.EntryPoints) {
			auto service = m_ctx->GetService(entryPoint.Service);
			assert(service != nullptr);
			service->SetLobbyMaxPlayers(entryPoint, amount);
		}

		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyMaxPlayers;
		js["amount"] = amount;
		m_ctx->InternalSendToAll(js);
	}

	m_ctx->GetCallbacks()->OnLobbyMaxPlayersChanged(oldamount, amount);
}

void Unet::Lobby::SetPrivacy(LobbyPrivacy privacy)
{
	for (auto &entryPoint : m_info.EntryPoints) {
		auto service = m_ctx->GetService(entryPoint.Service);
		assert(service != nullptr);
		service->SetLobbyPrivacy(entryPoint, privacy);
	}
}

void Unet::Lobby::SetJoinable(bool joinable)
{
	for (auto &entryPoint : m_info.EntryPoints) {
		auto service = m_ctx->GetService(entryPoint.Service);
		assert(service != nullptr);
		service->SetLobbyJoinable(entryPoint, joinable);
	}
}

void Unet::Lobby::SetRichPresence()
{
	json js;
	for (auto& entryPoint : m_info.EntryPoints) {
		const char* serviceName = GetServiceNameByType(entryPoint.Service);
		js[serviceName] = entryPoint.ID;
	}
	std::string connectionString = js.dump();

	// steam = 256 bytes
	// galaxy = 4096 bytes
	assert(connectionString.length() <= 256);

	for (auto& entry : m_info.EntryPoints) {
		auto service = m_ctx->GetService(entry.Service);
		assert(service != nullptr);
		service->SetRichPresence("connect", connectionString.c_str());
	}
}

void Unet::Lobby::SetData(const std::string &name, const std::string &value)
{
	LobbyDataContainer::SetData(name, value);

	if (m_info.IsHosting) {
		for (auto &entry : m_info.EntryPoints) {
			auto service = m_ctx->GetService(entry.Service);
			if (service != nullptr) {
				service->SetLobbyData(entry, name.c_str(), value.c_str());
			}
		}

		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyData;
		js["name"] = name;
		js["value"] = value;
		m_ctx->InternalSendToAll(js);

		m_ctx->GetCallbacks()->OnLobbyDataChanged(name);
	}
}

std::string Unet::Lobby::GetData(const std::string &name) const
{
	std::string ret = LobbyDataContainer::GetData(name);
	if (ret != "") {
		return ret;
	}

	ServiceType firstService = ServiceType::None;

	for (size_t i = 0; i < m_info.EntryPoints.size(); i++) {
		auto &entry = m_info.EntryPoints[i];

		auto service = m_ctx->GetService(entry.Service);
		if (service == nullptr) {
			continue;
		}

		std::string str = service->GetLobbyData(entry, name.c_str());
		if (str == "") {
			continue;
		}

		if (i == 0) {
			firstService = entry.Service;
			ret = str;
		} else if (ret != str) {
			m_ctx->GetCallbacks()->OnLogWarn(strPrintF("Data \"%s\" is different between service %s and %s! (\"%s\" and \"%s\")",
				name.c_str(),
				GetServiceNameByType(firstService), GetServiceNameByType(entry.Service),
				ret.c_str(), str.c_str()
			));
		}
	}

	return ret;
}

void Unet::Lobby::RemoveData(const std::string &name)
{
	LobbyDataContainer::RemoveData(name);

	if (m_info.IsHosting) {
		for (auto &entry : m_info.EntryPoints) {
			auto service = m_ctx->GetService(entry.Service);
			if (service != nullptr) {
				service->RemoveLobbyData(entry, name.c_str());
			}
		}

		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyDataRemoved;
		js["name"] = name;
		m_ctx->InternalSendToAll(js);
	}
}

int Unet::Lobby::GetNextAvailablePeer()
{
	int i = 0;
	while (GetMember(i) != nullptr) {
		i++;
	}
	return i;
}

void Unet::Lobby::HandleOutgoingFileTransfers()
{
	auto localMember = GetMember(m_ctx->m_localPeer);

	for (int i = (int)m_outgoingFileTransfers.size() - 1; i >= 0; i--) {
		auto &transfer = m_outgoingFileTransfers[i];

		auto file = localMember->GetFile(transfer.FileHash);
		auto member = GetMember(transfer.MemberPeer);

		if (file == nullptr || member == nullptr) {
			//TODO: Run callback about canceled outgoing file transfer
			m_outgoingFileTransfers.erase(m_outgoingFileTransfers.begin() + i);
			continue;
		}

		// We use a relatively small block size to avoid making the download progress indicator too slow,
		// as well as making sure we're under the reliable packet size limit in most cases.
		const size_t blockSize = 1024 * 64;
		const int maxBlocks = 3;

		uint8_t* p = file->m_buffer + transfer.CurrentPos;
		size_t bytesLeft = file->m_size - transfer.CurrentPos;
		int numBlocks = 0;

		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyFileData;
		js["filename"] = file->m_filename;

		for (int i = 0; i < maxBlocks && bytesLeft > 0; i++) {
			size_t sendSize = std::min(blockSize, bytesLeft);

			m_ctx->InternalSendTo(member, js, p, sendSize);

			p += sendSize;
			transfer.CurrentPos += sendSize;
			numBlocks++;

			bytesLeft -= sendSize;
		}

		m_ctx->GetCallbacks()->OnLobbyFileDataSendProgress(transfer);

		if (transfer.CurrentPos == file->m_availableSize) {
			m_ctx->GetCallbacks()->OnLobbyFileDataSendFinished(transfer);

			m_outgoingFileTransfers.erase(m_outgoingFileTransfers.begin() + i);
		}
	}
}
