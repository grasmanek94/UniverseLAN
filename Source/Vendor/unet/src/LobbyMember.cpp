#include <Unet_common.h>
#include <Unet/LobbyMember.h>
#include <Unet/Context.h>
#include <Unet/LobbyPacket.h>

Unet::LobbyMember::LobbyMember(Internal::Context* ctx)
{
	m_ctx = ctx;

	SetNextPingRequest();
}

Unet::LobbyMember::~LobbyMember()
{
	for (auto file : Files) {
		delete file;
	}
}

Unet::ServiceID Unet::LobbyMember::GetServiceID(ServiceType type) const
{
	for (auto &id : IDs) {
		if (id.Service == type) {
			return id;
		}
	}
	return ServiceID();
}

Unet::ServiceID Unet::LobbyMember::GetDataServiceID() const
{
	assert(IDs.size() > 0);

	// Prefer our primary service, if the client supports it
	for (auto &id : IDs) {
		if (id.Service == m_ctx->m_primaryService) {
			return id;
		}
	}

	// Prefer the client's primary service, if we support it
	for (auto &id : IDs) {
		if (id.Service == UnetPrimaryService) {
			if (m_ctx->GetService(id.Service) != nullptr) {
				return id;
			}
			break;
		}
	}

	// As a fallback, just pick any ID that we support
	for (auto &id : IDs) {
		if (m_ctx->GetService(id.Service) != nullptr) {
			return id;
		}
	}

	// We can't send messages to this member
	return ServiceID();
}

Unet::ServiceID Unet::LobbyMember::GetPrimaryServiceID() const
{
	return GetServiceID(UnetPrimaryService);
}

json Unet::LobbyMember::Serialize() const
{
	json js;
	js["guid"] = UnetGuid.str();
	js["peer"] = UnetPeer;
	js["primary"] = (int)UnetPrimaryService;
	js["name"] = Name;
	js["ids"] = json::array();
	for (auto &id : IDs) {
		js["ids"].emplace_back(json::array({ (int)id.Service, id.ID }));
	}
	js["data"] = SerializeData();
	js["files"] = json::array();
	for (auto file : Files) {
		json jsFile = json::object();
		jsFile["filename"] = file->m_filename;
		jsFile["size"] = file->m_size;
		jsFile["hash"] = file->m_hash;
		js["files"].emplace_back(jsFile);
	}
	return js;
}

void Unet::LobbyMember::Deserialize(const json &js)
{
	Valid = true;

	UnetPeer = js["peer"].get<int>();
	UnetPrimaryService = (Unet::ServiceType)js["primary"].get<int>();
	Name = js["name"].get<std::string>();

	DeserializeData(js["data"]);

	for (auto &jsFile : js["files"]) {
		auto newFile = new LobbyFile(jsFile["filename"].get<std::string>());
		size_t size = jsFile["size"].get<size_t>();
		uint64_t hash = jsFile["hash"].get<uint64_t>();
		newFile->Prepare(size, hash);
		newFile->LoadFromCache();
		Files.emplace_back(newFile);
	}
}

void Unet::LobbyMember::SetData(const std::string &name, const std::string &value)
{
	LobbyDataContainer::SetData(name, value);

	auto currentLobby = m_ctx->CurrentLobby();
	assert(currentLobby != nullptr);
	if (currentLobby != nullptr && currentLobby->GetInfo().IsHosting) {
		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyMemberData;
		js["guid"] = UnetGuid.str();
		js["name"] = name;
		js["value"] = value;
		m_ctx->InternalSendToAll(js);

		m_ctx->GetCallbacks()->OnLobbyMemberDataChanged(this, name);

	} else if (UnetPeer == m_ctx->m_localPeer) {
		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyMemberData;
		js["name"] = name;
		js["value"] = value;
		m_ctx->InternalSendToHost(js);
	}
}

void Unet::LobbyMember::RemoveData(const std::string &name)
{
	LobbyDataContainer::RemoveData(name);

	auto currentLobby = m_ctx->CurrentLobby();
	assert(currentLobby != nullptr);
	if (currentLobby != nullptr && currentLobby->GetInfo().IsHosting) {
		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyMemberDataRemoved;
		js["guid"] = UnetGuid.str();
		js["name"] = name;
		m_ctx->InternalSendToAll(js);

		m_ctx->GetCallbacks()->OnLobbyMemberDataChanged(this, name);

	} else if (UnetPeer == m_ctx->m_localPeer) {
		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyMemberDataRemoved;
		js["name"] = name;
		m_ctx->InternalSendToHost(js);
	}
}

Unet::LobbyFile* Unet::LobbyMember::GetFile(const std::string &filename)
{
	for (auto file : Files) {
		if (file->m_filename == filename) {
			return file;
		}
	}
	return nullptr;
}

Unet::LobbyFile* Unet::LobbyMember::GetFile(uint64_t hash)
{
	for (auto file : Files) {
		if (file->m_hash == hash) {
			return file;
		}
	}
	return nullptr;
}

void Unet::LobbyMember::AddFile(const std::string &filename, const std::string &filenameOnDisk)
{
	auto newFile = new LobbyFile(filename);
	newFile->LoadFromFile(filenameOnDisk);
	AddFile(newFile);
}

void Unet::LobbyMember::AddFile(const std::string &filename, uint8_t* buffer, size_t size)
{
	auto newFile = new LobbyFile(filename);
	newFile->Load(buffer, size);
	AddFile(newFile);
}

void Unet::LobbyMember::AddFile(LobbyFile* file)
{
	Files.emplace_back(file);

	auto currentLobby = m_ctx->CurrentLobby();
	assert(currentLobby != nullptr);

	if (currentLobby != nullptr) {
		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyFileAdded;
		js["filename"] = file->m_filename;
		js["size"] = file->m_size;
		js["hash"] = file->m_hash;

		if (currentLobby->GetInfo().IsHosting) {
			js["guid"] = UnetGuid.str();
			m_ctx->InternalSendToAll(js);
		} else if (UnetPeer == m_ctx->m_localPeer) {
			m_ctx->InternalSendToHost(js);
		}
	}
}

void Unet::LobbyMember::RemoveFile(const std::string &filename)
{
	InternalRemoveFile(filename);

	auto currentLobby = m_ctx->CurrentLobby();
	assert(currentLobby != nullptr);

	if (currentLobby != nullptr) {
		json js;
		js["t"] = (uint8_t)LobbyPacketType::LobbyFileRemoved;
		js["filename"] = filename;

		if (currentLobby->GetInfo().IsHosting) {
			js["guid"] = UnetGuid.str();
			m_ctx->InternalSendToAll(js);
		} else if (UnetPeer == m_ctx->m_localPeer) {
			m_ctx->InternalSendToHost(js);
		}
	}
}

void Unet::LobbyMember::InternalRemoveFile(const std::string &filename)
{
	auto it = std::find_if(Files.begin(), Files.end(), [filename](LobbyFile * file) {
		return file->m_filename == filename;
	});

	if (it == Files.end()) {
		m_ctx->GetCallbacks()->OnLogError(strPrintF("No such file \"%s\"!", filename.c_str()));
		return;
	}

	delete *it;
	Files.erase(it);
}

void Unet::LobbyMember::SendPing()
{
	json js;
	js["t"] = (uint8_t)LobbyPacketType::Ping;
	m_ctx->InternalSendTo(this, js);

	m_ctx->GetCallbacks()->OnLogDebug(strPrintF("Sent ping to %d", UnetPeer));

	LastPingRequest = std::chrono::high_resolution_clock::now();
	SetNextPingRequest();
}

void Unet::LobbyMember::SetNextPingRequest()
{
	NextPingRequest = std::chrono::system_clock::now() + std::chrono::milliseconds(800 + (rand() % 400));
}
