#include "Friends.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>

#include <algorithm>

namespace universelan::client {
	using namespace galaxy::api;
	FriendsImpl::FriendsImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
#if (GALAXY_VERSION) > 112400
		user_information_requests{},
		retrieve_rich_presence_requests{},
#endif
		rich_presence_change_requests{},
		avatar_criteria{ 0 }
	{
		tracer::Trace trace{ __FUNCTION__ };
	}

	FriendsImpl::~FriendsImpl()
	{
		tracer::Trace trace{ __FUNCTION__ };
	}

	AvatarCriteriaImpl FriendsImpl::GetDefaultAvatarCriteria() {
		tracer::Trace trace{ __FUNCTION__ };

		return avatar_criteria;
	}

	void FriendsImpl::SetDefaultAvatarCriteria(AvatarCriteriaImpl defaultAvatarCriteria) {
		tracer::Trace trace{ __FUNCTION__ };

		avatar_criteria = defaultAvatarCriteria;
	}

	void FriendsImpl::RequestUserInformation(
		GalaxyID userID
		, AvatarCriteriaImpl avatarCriteria
#if (GALAXY_VERSION) > 112400
		, IUserInformationRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
#if (GALAXY_VERSION) > 112400
			listeners->NotifyAll(listener, &IUserInformationRetrieveListener::OnUserInformationRetrieveSuccess, userID);
#endif
			// TODO: IPerson blabla listener
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

#if (GALAXY_VERSION) > 112400
			user_information_requests.emplace(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeFriends, request_id, userID });
		}
	}

	void FriendsImpl::RequestUserInformationProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

#if (GALAXY_VERSION) > 112400
		IUserInformationRetrieveListener* listener = user_information_requests.pop(data->request_id);
#endif

		// TODO: IPerson blabla listener

		if (data->found) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			entry->stats = data->asuc;
			entry->nickname = data->nickname;
#if (GALAXY_VERSION) > 112400
			listeners->NotifyAll(listener, &IUserInformationRetrieveListener::OnUserInformationRetrieveSuccess, data->id);
#endif
		}
		else {
#if (GALAXY_VERSION) > 112400
			listeners->NotifyAll(listener, &IUserInformationRetrieveListener::OnUserInformationRetrieveFailure, data->id, IUserInformationRetrieveListener::FAILURE_REASON_UNDEFINED);
#endif
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

	void FriendsImpl::RequestFriendList(
#if (GALAXY_VERSION) > 112400
		IFriendListListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener, 
#endif
			&IFriendListListener::OnFriendListRetrieveSuccess);
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

	void FriendsImpl::SendFriendInvitation(GalaxyID userID
#if (GALAXY_VERSION) > 112400
		, IFriendInvitationSendListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener,
#endif
			&IFriendInvitationSendListener::OnFriendInvitationSendSuccess, userID);
	}

	void FriendsImpl::RequestFriendInvitationList(
#if (GALAXY_VERSION) > 112400
		IFriendInvitationListRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener,
#endif
			&IFriendInvitationListRetrieveListener::OnFriendInvitationListRetrieveSuccess);
	}

	void FriendsImpl::RequestSentFriendInvitationList(
#if (GALAXY_VERSION) > 112400
		ISentFriendInvitationListRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener, 
#endif
			&ISentFriendInvitationListRetrieveListener::OnSentFriendInvitationListRetrieveSuccess);
	}

	uint32_t FriendsImpl::GetFriendInvitationCount() {
		tracer::Trace trace{ __FUNCTION__ };

		return 0;
	}

	void FriendsImpl::GetFriendInvitationByIndex(uint32_t index, GalaxyID& userID, uint32_t& sendTime) {
		tracer::Trace trace{ __FUNCTION__ };
	}

	void FriendsImpl::RespondToFriendInvitation(GalaxyID userID, bool accept
#if (GALAXY_VERSION) > 112400
		, IFriendInvitationRespondToListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener,
#endif
			&IFriendInvitationRespondToListener::OnFriendInvitationRespondToFailure, userID, IFriendInvitationRespondToListener::FAILURE_REASON_UNDEFINED);
	}

	void FriendsImpl::DeleteFriend(GalaxyID userID
#if (GALAXY_VERSION) > 112400
		, IFriendDeleteListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener, 
#endif
			&IFriendDeleteListener::OnFriendDeleteFailure, userID, IFriendDeleteListener::FAILURE_REASON_UNDEFINED);
	}

	void FriendsImpl::SetRichPresence(const char* key, const char* value
#if (GALAXY_VERSION) > 112400
		, IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->GetLocalUserData()->stats.SetRichPresence(key, value);

		uint64_t request_id = MessageUniqueID::get();

#if (GALAXY_VERSION) > 112400
		rich_presence_change_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RichPresenceChangeMessage{ request_id, 0, RichPresenceChangeMessage::ACTION_SET, key, value });
	}

	void FriendsImpl::DeleteRichPresence(const char* key
#if (GALAXY_VERSION) > 112400
		, IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->GetLocalUserData()->stats.EraseRichPresence(key);

		uint64_t request_id = MessageUniqueID::get();

#if (GALAXY_VERSION) > 112400
		rich_presence_change_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RichPresenceChangeMessage{ request_id, 0, RichPresenceChangeMessage::ACTION_DELETE, key });
	}

	void FriendsImpl::ClearRichPresence(
#if (GALAXY_VERSION) > 112400
		IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->GetLocalUserData()->stats.ClearRichPresence();

		uint64_t request_id = MessageUniqueID::get();

#if (GALAXY_VERSION) > 112400
		rich_presence_change_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RichPresenceChangeMessage{ request_id, 0, RichPresenceChangeMessage::ACTION_CLEAR });
	}

	void FriendsImpl::RichPresenceChangeMessageProcessed(const std::shared_ptr<RichPresenceChangeMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(data->id)) {
			IRichPresenceChangeListener* listener = rich_presence_change_requests.pop(data->request_id);

			if (data->success) {
				listeners->NotifyAll(listener, &IRichPresenceChangeListener::OnRichPresenceChangeSuccess);
				listeners->NotifyAll(&IRichPresenceListener::OnRichPresenceUpdated, intf->config->GetApiGalaxyID());
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

	void FriendsImpl::RequestRichPresence(GalaxyID userID
#if (GALAXY_VERSION) > 112400
		, IRichPresenceRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
#if (GALAXY_VERSION) > 112400
			listeners->NotifyAll(listener, &IRichPresenceRetrieveListener::OnRichPresenceRetrieveSuccess, userID);
#endif
			listeners->NotifyAll(&IRichPresenceListener::OnRichPresenceUpdated, userID);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();
#if (GALAXY_VERSION) > 112400
			retrieve_rich_presence_requests.emplace(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeRichPresence, request_id, userID });
		}
	}

	void FriendsImpl::RequestRichPresenceProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

#if (GALAXY_VERSION) > 112400
		IRichPresenceRetrieveListener* listener = retrieve_rich_presence_requests.pop(data->request_id);
#endif

		if (data->found) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			entry->stats = data->asuc;
			entry->nickname = data->nickname;

#if (GALAXY_VERSION) > 112400
			listeners->NotifyAll(listener, &IRichPresenceRetrieveListener::OnRichPresenceRetrieveSuccess, data->id);
#endif

			listeners->NotifyAll(&IRichPresenceListener::OnRichPresenceUpdated, data->id);
		}
		else {
#if (GALAXY_VERSION) > 112400
			listeners->NotifyAll(listener, &IRichPresenceRetrieveListener::OnRichPresenceRetrieveFailure, data->id, IRichPresenceRetrieveListener::FAILURE_REASON_UNDEFINED);
#endif
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

	GetRichPresenceReturnT FriendsImpl::GetRichPresenceByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		auto entry = intf->user->GetGalaxyUserData(userID);
		return entry->stats.run_locked_richpresence<GetRichPresenceReturnT>([&](auto& map) -> GetRichPresenceReturnT {
			if (map.size() < index) {
#if (GALAXY_VERSION) <= 112400
				return false;
#endif
			}

			auto ref = container_get_by_index(map, index);
			std::copy_n(ref.first.begin(), std::min((uint32_t)ref.first.length(), keyLength), key);
			std::copy_n(ref.second.begin(), std::min((uint32_t)ref.second.length(), valueLength), value);

#if (GALAXY_VERSION) <= 112400
			return true;
#endif
			});
	}

	void FriendsImpl::ShowOverlayInviteDialog(const char* connectionString) {
		tracer::Trace trace{ __FUNCTION__ };

		std::cout << "ShowOverlayInviteDialog\n\t" << connectionString << std::endl;
	}

	void FriendsImpl::SendInvitation(GalaxyID userID, const char* connectionString
#if (GALAXY_VERSION) > 112400
		, ISendInvitationListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		// TODO: implement this sometime

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener,
#endif
			&ISendInvitationListener::OnInvitationSendFailure, userID, connectionString, ISendInvitationListener::FAILURE_REASON_RECEIVER_DOES_NOT_ALLOW_INVITING);
	}

	void FriendsImpl::FindUser(const char* userSpecifier
#if (GALAXY_VERSION) > 112400
		, IUserFindListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if (GALAXY_VERSION) > 112400
			listener, 
#endif
			&IUserFindListener::OnUserFindFailure, userSpecifier, IUserFindListener::FAILURE_REASON_UNDEFINED);
	}

#if (GALAXY_VERSION) > 112400
	bool FriendsImpl::IsUserInTheSameGame(GalaxyID userID) const {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->user->GetGalaxyUserData(userID)->online;
	}
#endif
}
