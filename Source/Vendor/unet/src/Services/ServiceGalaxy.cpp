#include <Unet_common.h>
#include <Unet/Services/ServiceGalaxy.h>
#include <Unet/LobbyPacket.h>

void Unet::LobbyListListener::OnLobbyList(uint32_t lobbyCount
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
	, galaxy::api::LobbyListResult result
#else
	, bool result
#endif
)
{
	m_self->m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Lobby list received (%d)", (int)lobbyCount));

	m_listDataFetch.clear();

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
	if (result != galaxy::api::LOBBY_LIST_RESULT_SUCCESS)
#else
	if (result)
#endif
	{
		m_self->m_requestLobbyList->Code = Result::Error;
		m_self->m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Couldn't get lobby list due to error %d", (int)result));
		return;
	}

	if (lobbyCount == 0) {
		m_self->m_requestLobbyList->Code = Result::OK;
		return;
	}

	for (uint32_t i = 0; i < lobbyCount; i++) {
		auto lobbyId = galaxy::api::Matchmaking()->GetLobbyByIndex(i);
		if (!lobbyId.IsValid()) {
			continue;
		}

		try {
			galaxy::api::Matchmaking()->RequestLobbyData(lobbyId
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
				, this
#endif
			);
			m_listDataFetch.emplace_back(lobbyId);
		}
		catch (const galaxy::api::IError& error) {
			m_self->m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Couldn't get lobby data: %s", error.GetMsg()));
		}
	}

	if (m_listDataFetch.size() == 0) {
		m_self->m_requestLobbyList->Code = Result::Error;
	}
}

void Unet::LobbyListListener::LobbyDataUpdated()
{
	if (m_listDataFetch.size() == 0) {
		m_self->m_requestLobbyList->Code = Result::OK;
	}
}

void Unet::LobbyListListener::OnLobbyDataRetrieveSuccess(const galaxy::api::GalaxyID& lobbyID)
{
	auto it = std::find(m_listDataFetch.begin(), m_listDataFetch.end(), lobbyID);
	if (it != m_listDataFetch.end()) {
		m_listDataFetch.erase(it);
	}

	xg::Guid unetGuid(galaxy::api::Matchmaking()->GetLobbyData(lobbyID, "unet-guid"));
	if (!unetGuid.isValid()) {
		m_self->m_ctx->GetCallbacks()->OnLogWarn("[Galaxy] unet-guid is not valid!");
		LobbyDataUpdated();
		return;
	}

	ServiceID newEntryPoint;
	newEntryPoint.Service = ServiceType::Galaxy;
	newEntryPoint.ID = lobbyID.ToUint64();
	m_self->m_requestLobbyList->Data->AddEntryPoint(unetGuid, newEntryPoint);

	LobbyDataUpdated();
}

void Unet::LobbyListListener::OnLobbyDataRetrieveFailure(const galaxy::api::GalaxyID& lobbyID, FailureReason failureReason)
{
	auto it = std::find(m_listDataFetch.begin(), m_listDataFetch.end(), lobbyID);
	if (it != m_listDataFetch.end()) {
		m_listDataFetch.erase(it);
	}

	m_self->m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Failed to retrieve lobby data, error %d", (int)failureReason));

	LobbyDataUpdated();
}

Unet::ServiceGalaxy::ServiceGalaxy(Internal::Context* ctx, int numChannels) :
	Service(ctx, numChannels),
	m_lobbyListListener(this)
{
	galaxy::api::ListenerRegistrar()->Register(galaxy::api::LOBBY_LEFT, (galaxy::api::ILobbyLeftListener*)this);
	galaxy::api::ListenerRegistrar()->Register(galaxy::api::LOBBY_MEMBER_STATE, (galaxy::api::ILobbyMemberStateListener*)this);
}

Unet::ServiceGalaxy::~ServiceGalaxy()
{
	galaxy::api::ListenerRegistrar()->Unregister(galaxy::api::LOBBY_LEFT, (galaxy::api::ILobbyLeftListener*)this);
	galaxy::api::ListenerRegistrar()->Unregister(galaxy::api::LOBBY_MEMBER_STATE, (galaxy::api::ILobbyMemberStateListener*)this);
}

void Unet::ServiceGalaxy::SimulateOutage()
{
	auto lobby = m_ctx->CurrentLobby();
	if (lobby == nullptr) {
		return;
	}

	auto& lobbyInfo = lobby->GetInfo();
	auto entryPoint = lobbyInfo.GetEntryPoint(Unet::ServiceType::Galaxy);
	if (entryPoint == nullptr) {
		return;
	}

	try {
		galaxy::api::Matchmaking()->LeaveLobby(entryPoint->ID);
	}
	catch (const galaxy::api::IError& error) {
		m_ctx->GetCallbacks()->OnLogError(strPrintF("[Galaxy] Failed to simulate outage: %s", error.GetMsg()));
	}
}

Unet::ServiceType Unet::ServiceGalaxy::GetType()
{
	return ServiceType::Galaxy;
}

Unet::ServiceID Unet::ServiceGalaxy::GetUserID()
{
	return ServiceID(ServiceType::Galaxy, galaxy::api::User()->GetGalaxyID().ToUint64());
}

std::string Unet::ServiceGalaxy::GetUserName()
{
	return galaxy::api::Friends()->GetPersonaName();
}

void Unet::ServiceGalaxy::SetRichPresence(const char* key, const char* value)
{
	galaxy::api::Friends()->SetRichPresence(key, value);
}

void Unet::ServiceGalaxy::CreateLobby(LobbyPrivacy privacy, int maxPlayers)
{
	galaxy::api::LobbyType type = galaxy::api::LOBBY_TYPE_PUBLIC;
	switch (privacy) {
	case LobbyPrivacy::Public: type = galaxy::api::LOBBY_TYPE_PUBLIC; break;
	case LobbyPrivacy::Private: type = galaxy::api::LOBBY_TYPE_PRIVATE; break;
	}

	m_requestLobbyCreated = m_ctx->m_callbackCreateLobby.AddServiceRequest(this);

	try {
		galaxy::api::Matchmaking()->CreateLobby(type, maxPlayers, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, this
#endif
		);
	}
	catch (const galaxy::api::IError& error) {
		m_requestLobbyCreated->Code = Result::Error;
		m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Failed to create lobby: %s", error.GetMsg()));
	}
}

void Unet::ServiceGalaxy::SetLobbyPrivacy(const ServiceID& lobbyId, LobbyPrivacy privacy)
{
	galaxy::api::LobbyType type = galaxy::api::LOBBY_TYPE_PUBLIC;
	switch (privacy) {
	case LobbyPrivacy::Public: type = galaxy::api::LOBBY_TYPE_PUBLIC; break;
	case LobbyPrivacy::Private: type = galaxy::api::LOBBY_TYPE_PRIVATE; break;
	}

	assert(lobbyId.Service == ServiceType::Galaxy);
	try {
		galaxy::api::Matchmaking()->SetLobbyType(lobbyId.ID, type);
	}
	catch (const galaxy::api::IError& error) {
		m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Failed to set lobby privacy: %s", error.GetMsg()));
	}
}

void Unet::ServiceGalaxy::SetLobbyJoinable(const ServiceID& lobbyId, bool joinable)
{
	assert(lobbyId.Service == ServiceType::Galaxy);
	try {
		galaxy::api::Matchmaking()->SetLobbyJoinable(lobbyId.ID, joinable);
	}
	catch (const galaxy::api::IError& error) {
		m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Failed to make lobby joinable: %s", error.GetMsg()));
	}
}

void Unet::ServiceGalaxy::GetLobbyList()
{
	m_requestLobbyList = m_ctx->m_callbackLobbyList.AddServiceRequest(this);

	try {
		galaxy::api::Matchmaking()->RequestLobbyList(false
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, & m_lobbyListListener
#endif
		);
	}
	catch (const galaxy::api::IError& error) {
		m_requestLobbyList->Code = Result::Error;
		m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Failed to list lobbies: %s", error.GetMsg()));
	}
}

bool Unet::ServiceGalaxy::FetchLobbyInfo(const ServiceID& id)
{
	assert(id.Service == ServiceType::Galaxy);

	try {
		galaxy::api::Matchmaking()->RequestLobbyData(id.ID
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, this
#endif
		);
		m_dataFetch.emplace_back(id.ID);
		return true;
	}
	catch (const galaxy::api::IError& error) {
		m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Failed to fetch lobby info: %s", error.GetMsg()));
		return false;
	}
}

void Unet::ServiceGalaxy::JoinLobby(const ServiceID& id)
{
	assert(id.Service == ServiceType::Galaxy);

	m_requestLobbyJoin = m_ctx->m_callbackLobbyJoin.AddServiceRequest(this);

	try {
		galaxy::api::Matchmaking()->JoinLobby(id.ID
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, this
#endif
		);
	}
	catch (const galaxy::api::IError& error) {
		m_requestLobbyJoin->Code = Result::Error;
		m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Failed to join lobby: %s", error.GetMsg()));
	}
}

void Unet::ServiceGalaxy::LeaveLobby()
{
	auto lobby = m_ctx->CurrentLobby();
	if (lobby == nullptr) {
		return;
	}

	auto& lobbyInfo = lobby->GetInfo();
	auto entryPoint = lobbyInfo.GetEntryPoint(Unet::ServiceType::Galaxy);
	if (entryPoint == nullptr) {
		return;
	}

	m_requestLobbyLeft = m_ctx->m_callbackLobbyLeft.AddServiceRequest(this);

	try {
		galaxy::api::Matchmaking()->LeaveLobby(entryPoint->ID
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, this
#endif
		);
	}
	catch (const galaxy::api::IError& error) {
		m_requestLobbyLeft->Code = Result::Error;
		m_ctx->GetCallbacks()->OnLogError(strPrintF("[Galaxy] Failed to leave lobby: %s", error.GetMsg()));
	}
}

int Unet::ServiceGalaxy::GetLobbyPlayerCount(const ServiceID& lobbyId)
{
	assert(lobbyId.Service == ServiceType::Galaxy);

	return galaxy::api::Matchmaking()->GetNumLobbyMembers(lobbyId.ID);
}

void Unet::ServiceGalaxy::SetLobbyMaxPlayers(const ServiceID& lobbyId, int amount)
{
	assert(lobbyId.Service == ServiceType::Galaxy);

	galaxy::api::Matchmaking()->SetMaxNumLobbyMembers(lobbyId.ID, amount);
}

int Unet::ServiceGalaxy::GetLobbyMaxPlayers(const ServiceID& lobbyId)
{
	assert(lobbyId.Service == ServiceType::Galaxy);

	return (int)galaxy::api::Matchmaking()->GetMaxNumLobbyMembers(lobbyId.ID);
}

std::string Unet::ServiceGalaxy::GetLobbyData(const ServiceID& lobbyId, const char* name)
{
	assert(lobbyId.Service == ServiceType::Galaxy);

	return galaxy::api::Matchmaking()->GetLobbyData(lobbyId.ID, name);
}

int Unet::ServiceGalaxy::GetLobbyDataCount(const ServiceID& lobbyId)
{
	assert(lobbyId.Service == ServiceType::Galaxy);

	return galaxy::api::Matchmaking()->GetLobbyDataCount(lobbyId.ID);
}

Unet::LobbyData Unet::ServiceGalaxy::GetLobbyData(const ServiceID& lobbyId, int index)
{
	assert(lobbyId.Service == ServiceType::Galaxy);

	char szKey[512];
	char szValue[512];

	LobbyData ret;
	if (galaxy::api::Matchmaking()->GetLobbyDataByIndex(lobbyId.ID, index, szKey, 512, szValue, 512)) {
		ret.Name = szKey;
		ret.Value = szValue;
	}

	return ret;
}

Unet::ServiceID Unet::ServiceGalaxy::GetLobbyHost(const ServiceID& lobbyId)
{
	assert(lobbyId.Service == ServiceType::Galaxy);

	return ServiceID(ServiceType::Galaxy, galaxy::api::Matchmaking()->GetLobbyOwner(lobbyId.ID).ToUint64());
}

void Unet::ServiceGalaxy::SetLobbyData(const ServiceID& lobbyId, const char* name, const char* value)
{
	assert(lobbyId.Service == ServiceType::Galaxy);

	galaxy::api::Matchmaking()->SetLobbyData(lobbyId.ID, name, value);
}

void Unet::ServiceGalaxy::RemoveLobbyData(const ServiceID& lobbyId, const char* name)
{
	assert(lobbyId.Service == ServiceType::Galaxy);

	galaxy::api::Matchmaking()->DeleteLobbyData(lobbyId.ID, name);
}

size_t Unet::ServiceGalaxy::ReliablePacketLimit()
{
	return 0;
}

void Unet::ServiceGalaxy::SendPacket(const ServiceID& peerId, const void* data, size_t size, PacketType type, uint8_t channel)
{
	assert(peerId.Service == ServiceType::Galaxy);

	galaxy::api::P2PSendType sendType = galaxy::api::P2P_SEND_UNRELIABLE;
	switch (type) {
	case PacketType::Unreliable: sendType = galaxy::api::P2P_SEND_UNRELIABLE; break;
	case PacketType::Reliable: sendType = galaxy::api::P2P_SEND_RELIABLE; break;
	}
	galaxy::api::Networking()->SendP2PPacket(peerId.ID, data, (uint32_t)size, sendType, channel);
}

size_t Unet::ServiceGalaxy::ReadPacket(void* data, size_t maxSize, ServiceID* peerId, uint8_t channel)
{
	uint32_t readSize;
	galaxy::api::GalaxyID peer;
	galaxy::api::Networking()->ReadP2PPacket(data, (uint32_t)maxSize, &readSize, peer, channel);

	if (peerId != nullptr) {
		*peerId = ServiceID(ServiceType::Galaxy, peer.ToUint64());
	}
	return (size_t)readSize;
}

bool Unet::ServiceGalaxy::IsPacketAvailable(size_t* outPacketSize, uint8_t channel)
{
	uint32_t packetSize;
	bool ret = galaxy::api::Networking()->IsP2PPacketAvailable(&packetSize, channel);

	if (outPacketSize != nullptr) {
		*outPacketSize = (size_t)packetSize;
	}
	return ret;
}

void Unet::ServiceGalaxy::OnLobbyCreated(const galaxy::api::GalaxyID& lobbyID, galaxy::api::LobbyCreateResult result)
{
	if (result != galaxy::api::LOBBY_CREATE_RESULT_SUCCESS) {
		m_requestLobbyCreated->Code = Result::Error;
		m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Error %d while creating lobby", (int)result));
		return;
	}

	ServiceID newEntryPoint;
	newEntryPoint.Service = ServiceType::Galaxy;
	newEntryPoint.ID = lobbyID.ToUint64();
	m_requestLobbyCreated->Data->CreatedLobby->AddEntryPoint(newEntryPoint);

	m_requestLobbyCreated->Code = Result::OK;

	m_ctx->GetCallbacks()->OnLogDebug("[Galaxy] Lobby created");
}

void Unet::ServiceGalaxy::OnLobbyEntered(const galaxy::api::GalaxyID& lobbyID, galaxy::api::LobbyEnterResult result)
{
	if (result != galaxy::api::LOBBY_ENTER_RESULT_SUCCESS) {
		m_requestLobbyJoin->Code = Result::Error;
		m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Couldn't join lobby due to error %d", (int)result));
		return;
	}

	ServiceID newEntryPoint;
	newEntryPoint.Service = ServiceType::Galaxy;
	newEntryPoint.ID = lobbyID.ToUint64();
	m_requestLobbyJoin->Data->JoinedLobby->AddEntryPoint(newEntryPoint);

	m_requestLobbyJoin->Code = Result::OK;

	m_ctx->GetCallbacks()->OnLogDebug("[Galaxy] Lobby joined");

	auto lobbyOwner = galaxy::api::Matchmaking()->GetLobbyOwner(lobbyID);

	json js;
	js["t"] = (uint8_t)LobbyPacketType::Handshake;
	js["guid"] = m_requestLobbyJoin->Data->JoinGuid.str();
	m_ctx->InternalSendTo(ServiceID(ServiceType::Galaxy, lobbyOwner.ToUint64()), js);

	m_ctx->GetCallbacks()->OnLogDebug("[Galaxy] Handshake sent");
}

void Unet::ServiceGalaxy::OnLobbyLeft(const galaxy::api::GalaxyID& lobbyID
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
	, galaxy::api::LobbyLeaveReason leaveReason
#else
, bool result
#endif
)
{
	auto currentLobby = m_ctx->CurrentLobby();
	if (currentLobby == nullptr) {
		return;
	}

	auto& lobbyInfo = currentLobby->GetInfo();
	auto entryPoint = lobbyInfo.GetEntryPoint(ServiceType::Galaxy);
	if (entryPoint == nullptr) {
		return;
	}

	if (entryPoint->ID != lobbyID.ToUint64()) {
		return;
	}

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
	if (leaveReason == LOBBY_LEAVE_REASON_USER_LEFT)
#else
	if(!result)
#endif
	{
		m_requestLobbyLeft->Code = Result::OK;
	}
	else {
		currentLobby->ServiceDisconnected(ServiceType::Galaxy);
	}
}

void Unet::ServiceGalaxy::OnLobbyMemberStateChanged(const galaxy::api::GalaxyID& lobbyID, const galaxy::api::GalaxyID& memberID, galaxy::api::LobbyMemberStateChange memberStateChange)
{
	auto currentLobby = m_ctx->CurrentLobby();
	if (currentLobby == nullptr) {
		return;
	}

	auto& lobbyInfo = currentLobby->GetInfo();
	auto entryPoint = lobbyInfo.GetEntryPoint(ServiceType::Galaxy);
	if (entryPoint == nullptr) {
		return;
	}

	if (entryPoint->ID != lobbyID.ToUint64()) {
		return;
	}

	if (memberStateChange & galaxy::api::LOBBY_MEMBER_STATE_CHANGED_ENTERED) {
		m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Player entered: 0x%016llX", memberID.ToUint64()));
	}
	else {
		m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Player left: 0x%016llX (code %X)", memberID.ToUint64(), memberStateChange));

		currentLobby->RemoveMemberService(ServiceID(ServiceType::Galaxy, memberID.ToUint64()));
	}
}

void Unet::ServiceGalaxy::OnLobbyDataRetrieveSuccess(const galaxy::api::GalaxyID& lobbyID)
{
	auto it = std::find(m_dataFetch.begin(), m_dataFetch.end(), lobbyID);
	if (it == m_dataFetch.end()) {
		m_ctx->GetCallbacks()->OnLogWarn("[Galaxy] Received an unexpected lobby data retrieval callback!");
		return;
	}
	m_dataFetch.erase(it);

	LobbyInfoFetchResult res;
	res.ID = ServiceID(ServiceType::Galaxy, lobbyID.ToUint64());

	xg::Guid unetGuid(galaxy::api::Matchmaking()->GetLobbyData(lobbyID, "unet-guid"));
	if (!unetGuid.isValid()) {
		m_ctx->GetCallbacks()->OnLogDebug("[Galaxy] unet-guid is not valid!");

		res.Code = Result::Error;
		m_ctx->GetCallbacks()->OnLobbyInfoFetched(res);
		return;
	}

	res.Info.IsHosting = galaxy::api::Matchmaking()->GetLobbyOwner(lobbyID) == galaxy::api::User()->GetGalaxyID();
	res.Info.Privacy = (LobbyPrivacy)atoi(galaxy::api::Matchmaking()->GetLobbyData(lobbyID, "unet-privacy"));
	res.Info.NumPlayers = galaxy::api::Matchmaking()->GetNumLobbyMembers(lobbyID);
	res.Info.MaxPlayers = galaxy::api::Matchmaking()->GetMaxNumLobbyMembers(lobbyID);
	res.Info.UnetGuid = unetGuid;
	res.Info.Name = galaxy::api::Matchmaking()->GetLobbyData(lobbyID, "unet-name");
	res.Info.EntryPoints.emplace_back(ServiceID(ServiceType::Galaxy, lobbyID.ToUint64()));

	res.Code = Result::OK;
	m_ctx->GetCallbacks()->OnLobbyInfoFetched(res);
}

void Unet::ServiceGalaxy::OnLobbyDataRetrieveFailure(const galaxy::api::GalaxyID& lobbyID, FailureReason failureReason)
{
	m_ctx->GetCallbacks()->OnLogDebug(strPrintF("[Galaxy] Failed to retrieve lobby data, error %d", (int)failureReason));

	LobbyInfoFetchResult res;
	res.ID = ServiceID(ServiceType::Galaxy, lobbyID.ToUint64());
	res.Code = Result::Error;
	m_ctx->GetCallbacks()->OnLobbyInfoFetched(res);
}
