#include "Friends.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>

#include <algorithm>

namespace universelan::client {
	using namespace galaxy::api;
	FriendsImpl::FriendsImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		user_information_requests{}, rich_presence_change_requests{},
		retrieve_rich_presence_requests{}, avatar_criteria { 0 }
	{
		tracer::Trace trace{ __FUNCTION__ };
	}

	FriendsImpl::~FriendsImpl()
	{
		tracer::Trace trace{ __FUNCTION__ };
	}

	AvatarCriteria FriendsImpl::GetDefaultAvatarCriteria() {
		tracer::Trace trace{ __FUNCTION__ };

		return avatar_criteria;
	}

	void FriendsImpl::SetDefaultAvatarCriteria(AvatarCriteria defaultAvatarCriteria) {
		tracer::Trace trace{ __FUNCTION__ };

		avatar_criteria = defaultAvatarCriteria;
	}

	void FriendsImpl::RequestUserInformation(
		GalaxyID userID,
		AvatarCriteria avatarCriteria,
		IUserInformationRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
			listeners->NotifyAll(listener, &IUserInformationRetrieveListener::OnUserInformationRetrieveSuccess, userID);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

			user_information_requests.emplace(request_id, listener);
			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeFriends, request_id, userID });
		}
	}

	void FriendsImpl::RequestUserInformationProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		IUserInformationRetrieveListener* listener = user_information_requests.pop(data->request_id);

		if (data->found) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			entry->stats = data->asuc;
			entry->nickname = data->nickname;

			listeners->NotifyAll(listener, &IUserInformationRetrieveListener::OnUserInformationRetrieveSuccess, data->id);
		}
		else {
			listeners->NotifyAll(listener, &IUserInformationRetrieveListener::OnUserInformationRetrieveFailure, data->id, IUserInformationRetrieveListener::FAILURE_REASON_UNDEFINED);
		}
	}

	bool FriendsImpl::IsUserInformationAvailable(GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->user->IsUserDataAvailable(userID);
	}

	const char* FriendsImpl::GetPersonaName() {
		tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.config->GetCustomPersonaName().c_str();
	}

	void FriendsImpl::GetPersonaNameCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		auto name = intf_inst.config->GetCustomPersonaName();

		std::copy_n(name.c_str(), std::min((size_t)bufferLength, name.length()), buffer);
	}

	PersonaState FriendsImpl::GetPersonaState() {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->client->IsConnected() ?
			PERSONA_STATE_ONLINE :
			PERSONA_STATE_OFFLINE;
	}

	const char* FriendsImpl::GetFriendPersonaName(GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->user->GetGalaxyUserData(userID)->nickname.c_str();
	}

	void FriendsImpl::GetFriendPersonaNameCopy(GalaxyID userID, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		std::string nickname = intf->user->GetGalaxyUserData(userID)->nickname;
		std::copy_n(nickname.c_str(), std::min((size_t)bufferLength, nickname.size()), buffer);
	}

	PersonaState FriendsImpl::GetFriendPersonaState(GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->user->GetGalaxyUserData(userID)->online ?
			PERSONA_STATE_ONLINE :
			PERSONA_STATE_OFFLINE;
	}

	const char* FriendsImpl::GetFriendAvatarUrl(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{ __FUNCTION__ };

		return "";
	}

	void FriendsImpl::GetFriendAvatarUrlCopy(GalaxyID userID, AvatarType avatarType, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		std::copy_n(GetFriendAvatarUrl(userID, avatarType), std::min((size_t)bufferLength, strlen(GetFriendAvatarUrl(userID, avatarType))), buffer);
	}

	uint32_t FriendsImpl::GetFriendAvatarImageID(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{ __FUNCTION__ };

		return 0;
	}

	void FriendsImpl::GetFriendAvatarImageRGBA(GalaxyID userID, AvatarType avatarType, void* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	bool FriendsImpl::IsFriendAvatarImageRGBAAvailable(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{ __FUNCTION__ };

		return false;
	}

	void FriendsImpl::RequestFriendList(IFriendListListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &IFriendListListener::OnFriendListRetrieveSuccess);
	}

	bool FriendsImpl::IsFriend(GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return false;
	}

	uint32_t FriendsImpl::GetFriendCount() {
		tracer::Trace trace{ __FUNCTION__ };

		return 0;
	}

	GalaxyID FriendsImpl::GetFriendByIndex(uint32_t index) {
		tracer::Trace trace{ __FUNCTION__ };

		return 0;
	}

	void FriendsImpl::SendFriendInvitation(GalaxyID userID, IFriendInvitationSendListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &IFriendInvitationSendListener::OnFriendInvitationSendSuccess, userID);
	}

	void FriendsImpl::RequestFriendInvitationList(IFriendInvitationListRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &IFriendInvitationListRetrieveListener::OnFriendInvitationListRetrieveSuccess);
	}

	void FriendsImpl::RequestSentFriendInvitationList(ISentFriendInvitationListRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &ISentFriendInvitationListRetrieveListener::OnSentFriendInvitationListRetrieveSuccess);
	}

	uint32_t FriendsImpl::GetFriendInvitationCount() {
		tracer::Trace trace{ __FUNCTION__ };

		return 0;
	}

	void FriendsImpl::GetFriendInvitationByIndex(uint32_t index, GalaxyID& userID, uint32_t& sendTime) {
		tracer::Trace trace{ __FUNCTION__ };
	}

	void FriendsImpl::RespondToFriendInvitation(GalaxyID userID, bool accept, IFriendInvitationRespondToListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &IFriendInvitationRespondToListener::OnFriendInvitationRespondToFailure, userID, IFriendInvitationRespondToListener::FAILURE_REASON_UNDEFINED);
	}

	void FriendsImpl::DeleteFriend(GalaxyID userID, IFriendDeleteListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &IFriendDeleteListener::OnFriendDeleteFailure, userID, IFriendDeleteListener::FAILURE_REASON_UNDEFINED);
	}

	void FriendsImpl::SetRichPresence(const char* key, const char* value, IRichPresenceChangeListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->GetLocalUserData()->stats.SetRichPresence(key, value);
		
		uint64_t request_id = MessageUniqueID::get();

		rich_presence_change_requests.emplace(request_id, listener);
		intf->client->GetConnection().SendAsync(RichPresenceChangeMessage{request_id, 0, RichPresenceChangeMessage ::ACTION_SET, key, value});
	}

	void FriendsImpl::DeleteRichPresence(const char* key, IRichPresenceChangeListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->GetLocalUserData()->stats.EraseRichPresence(key);

		uint64_t request_id = MessageUniqueID::get();

		rich_presence_change_requests.emplace(request_id, listener);
		intf->client->GetConnection().SendAsync(RichPresenceChangeMessage{ request_id, 0, RichPresenceChangeMessage::ACTION_DELETE, key });
	}

	void FriendsImpl::ClearRichPresence(IRichPresenceChangeListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->GetLocalUserData()->stats.ClearRichPresence();

		uint64_t request_id = MessageUniqueID::get();

		rich_presence_change_requests.emplace(request_id, listener);
		intf->client->GetConnection().SendAsync(RichPresenceChangeMessage{ request_id, 0, RichPresenceChangeMessage::ACTION_CLEAR });
	}

	void FriendsImpl::RichPresenceChangeMessageProcessed(const std::shared_ptr<RichPresenceChangeMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(data->id)) {
			IRichPresenceChangeListener* listener = rich_presence_change_requests.pop(data->request_id);

			if (data->success) {
				listeners->NotifyAll(listener, &IRichPresenceChangeListener::OnRichPresenceChangeSuccess);
			}
			else {
				listeners->NotifyAll(listener, &IRichPresenceChangeListener::OnRichPresenceChangeFailure, IRichPresenceChangeListener::FAILURE_REASON_UNDEFINED);
			}
			return;
		}
		else if (data->success) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			switch (data->action) {
			case RichPresenceChangeMessage::ACTION_SET:
				entry->stats.SetRichPresence(data->key, data->value);
				break;

			case RichPresenceChangeMessage::ACTION_DELETE:
				entry->stats.EraseRichPresence(data->key);
				break;

			case RichPresenceChangeMessage::ACTION_CLEAR:
				entry->stats.ClearRichPresence();
				break;

			case RichPresenceChangeMessage::ACTION_NONE:
				break;
			}
		}
	}

	void FriendsImpl::RequestRichPresence(GalaxyID userID, IRichPresenceRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
			listeners->NotifyAll(listener, &IRichPresenceRetrieveListener::OnRichPresenceRetrieveSuccess, userID);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

			retrieve_rich_presence_requests.emplace(request_id, listener);
			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeRichPresence, request_id, userID });
		}
	}

	void FriendsImpl::RequestRichPresenceProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		IRichPresenceRetrieveListener* listener = retrieve_rich_presence_requests.pop(data->request_id);

		if (data->found) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			entry->stats = data->asuc;
			entry->nickname = data->nickname;

			listeners->NotifyAll(listener, &IRichPresenceRetrieveListener::OnRichPresenceRetrieveSuccess, data->id);
		}
		else {
			listeners->NotifyAll(listener, &IRichPresenceRetrieveListener::OnRichPresenceRetrieveFailure, data->id, IRichPresenceRetrieveListener::FAILURE_REASON_UNDEFINED);
		}
	}

	const char* FriendsImpl::GetRichPresence(const char* key, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->user->GetGalaxyUserData(userID)->stats.GetRichPresence(key).c_str();
	}

	void FriendsImpl::GetRichPresenceCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		std::string value = intf->user->GetGalaxyUserData(userID)->stats.GetRichPresence(key);
		std::copy_n(value.c_str(), std::min((size_t)bufferLength, value.size()), buffer);
	}

	uint32_t FriendsImpl::GetRichPresenceCount(GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		auto entry = intf->user->GetGalaxyUserData(userID);
		return entry->stats.run_locked_richpresence<uint32_t>([&](auto& map) -> uint32_t {
			return (uint32_t)map.size();
			});
	}

	void FriendsImpl::GetRichPresenceByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		auto entry = intf->user->GetGalaxyUserData(userID);
		entry->stats.run_locked_richpresence<void>([&](auto& map) {
			if (map.size() < index) {
				return;
			}

			auto ref = container_get_by_index(map, index);
			std::copy_n(ref.first.begin(), std::min((uint32_t)ref.first.length(), keyLength), key);
			std::copy_n(ref.second.begin(), std::min((uint32_t)ref.second.length(), valueLength), value);
			});
	}

	void FriendsImpl::ShowOverlayInviteDialog(const char* connectionString) {
		tracer::Trace trace{ __FUNCTION__ };

		std::cout << "ShowOverlayInviteDialog\n\t" << connectionString << std::endl;
	}

	void FriendsImpl::SendInvitation(GalaxyID userID, const char* connectionString, ISendInvitationListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	void FriendsImpl::FindUser(const char* userSpecifier, IUserFindListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &IUserFindListener::OnUserFindFailure, userSpecifier, IUserFindListener::FAILURE_REASON_UNDEFINED);
	}

	bool FriendsImpl::IsUserInTheSameGame(GalaxyID userID) const {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->user->GetGalaxyUserData(userID)->online;
	}
}
