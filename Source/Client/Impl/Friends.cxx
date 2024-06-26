#include "Friends.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>
#include <SafeStringCopy.hxx>

#include <algorithm>

namespace universelan::client {
	using namespace galaxy::api;
	FriendsImpl::FriendsImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		avatar_criteria{ 0 }, online_friends{}
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };
	}

	FriendsImpl::~FriendsImpl()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };
	}

#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_TYPE
	AvatarCriteriaImpl FriendsImpl::GetDefaultAvatarCriteria() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		return avatar_criteria;
	}

	void FriendsImpl::SetDefaultAvatarCriteria(AvatarCriteriaImpl defaultAvatarCriteria) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		avatar_criteria = defaultAvatarCriteria;
	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED
	void FriendsImpl::RequestUserInformation(
		GalaxyID userID
#if GALAXY_BUILD_FEATURE_HAS_1_73_AVATARTYPE_CRITERIA
		, AvatarCriteriaImpl avatarCriteria // we don't support avatars yet
#endif
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IUserInformationRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (intf->config->IsSelfUserID(userID)) {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->NotifyAll(listener, &IUserInformationRetrieveListener::OnUserInformationRetrieveSuccess, userID);
#endif
			listeners->NotifyAll(&IPersonaDataChangedListener::OnPersonaDataChanged, userID, IPersonaDataChangedListener::PERSONA_CHANGE_NONE);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->AddRequestListener(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeFriends, request_id, userID });
		}
	}
#endif

	void FriendsImpl::RequestUserInformationProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IUserInformationRetrieveListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
#endif

		if (data->found) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			entry->stats = data->asuc;
			if (entry->nickname != data->nickname) {
				entry->nickname = data->nickname;
			}
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->NotifyAllNow(listener, &IUserInformationRetrieveListener::OnUserInformationRetrieveSuccess, data->id);
#endif
		}
		else {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->NotifyAllNow(listener, &IUserInformationRetrieveListener::OnUserInformationRetrieveFailure, data->id, IUserInformationRetrieveListener::FAILURE_REASON_UNDEFINED);
#endif
		}
#if GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED
		listeners->NotifyAllNow(&IPersonaDataChangedListener::OnPersonaDataChanged, data->id, IPersonaDataChangedListener::PERSONA_CHANGE_NONE);
#endif
	}

#if GALAXY_BUILD_FEATURE_HAS_USERDATAINFOAVAILABLE
	bool FriendsImpl::IsUserInformationAvailable(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		return intf->user->IsUserDataAvailable(userID);
	}
#endif

	const char* FriendsImpl::GetPersonaName() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		return intf_inst.config->GetCustomPersonaName().c_str();
	}

#if GALAXY_BUILD_FEATURE_IFRIENDS_GET_FRIEND_PERSONA_AVATAR_COPY
	void FriendsImpl::GetPersonaNameCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (buffer != nullptr) {
			auto name = intf_inst.config->GetCustomPersonaName();

			universelan::util::safe_copy_str_n(name, buffer, bufferLength);
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_PERSONASTATE_ENUM
	PersonaState FriendsImpl::GetPersonaState() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		return intf->client->IsConnected() ?
			PERSONA_STATE_ONLINE :
			PERSONA_STATE_OFFLINE;
	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_HAS_PERSONANAME_AND_AVATARURL
	const char* FriendsImpl::GetFriendPersonaName(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		return intf->user->GetGalaxyUserData(userID)->nickname.c_str();
	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_GET_FRIEND_PERSONA_AVATAR_COPY
	void FriendsImpl::GetFriendPersonaNameCopy(GalaxyID userID, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (buffer != nullptr) {
			std::string nickname = intf->user->GetGalaxyUserData(userID)->nickname;
			universelan::util::safe_copy_str_n(nickname, buffer, bufferLength);
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_PERSONASTATE_ENUM
	PersonaState FriendsImpl::GetFriendPersonaState(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (userID == intf->user->GetGalaxyID()) {
			return GetPersonaState();
		}

		lock_t lock(mtx_online_friends);
		return (online_friends.find(userID) != online_friends.end()) ?
			PERSONA_STATE_ONLINE :
			PERSONA_STATE_OFFLINE;
	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_HAS_PERSONANAME_AND_AVATARURL
	const char* FriendsImpl::GetFriendAvatarUrl(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		return "";
	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_GET_FRIEND_PERSONA_AVATAR_COPY
	void FriendsImpl::GetFriendAvatarUrlCopy(GalaxyID userID, AvatarType avatarType, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		universelan::util::safe_copy_str_n(GetFriendAvatarUrl(userID, avatarType), buffer, bufferLength);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_1_73_AVATARTYPE_CRITERIA
	uint32_t FriendsImpl::GetFriendAvatarImageID(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		return 0;
	}

	void FriendsImpl::GetFriendAvatarImageRGBA(GalaxyID userID, AvatarType avatarType, GetImageRGBABufferType* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };
	}

#if GALAXY_BUILD_FEATURE_IFRIENDS_HAS_ISAVATARRGBAIMAGEAVAILABLE
	bool FriendsImpl::IsFriendAvatarImageRGBAAvailable(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		return false;
	}
#endif
#endif

#if GALAXY_BUILD_FEATURE_HAS_IFRIENDLISTLISTENER
	void FriendsImpl::RequestFriendList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IFriendListListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener,
#endif
			& IFriendListListener::OnFriendListRetrieveSuccess);
	}
#endif

#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
	bool FriendsImpl::IsFriend(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		return false;
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IFRIENDLISTLISTENER
	uint32_t FriendsImpl::GetFriendCount() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		lock_t lock(mtx_online_friends);
		return (uint32_t)online_friends.size();
	}

	GalaxyID FriendsImpl::GetFriendByIndex(uint32_t index) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		lock_t lock(mtx_online_friends);
		return container_get_by_index(online_friends, index, GalaxyID(0));
	}
#endif

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3

	void FriendsImpl::SendFriendInvitation(GalaxyID userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IFriendInvitationSendListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener,
#endif
			& IFriendInvitationSendListener::OnFriendInvitationSendSuccess, userID);
	}

	void FriendsImpl::RequestFriendInvitationList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IFriendInvitationListRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener,
#endif
			& IFriendInvitationListRetrieveListener::OnFriendInvitationListRetrieveSuccess);
	}

#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER
	void FriendsImpl::RequestSentFriendInvitationList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		ISentFriendInvitationListRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener,
#endif
			& ISentFriendInvitationListRetrieveListener::OnSentFriendInvitationListRetrieveSuccess);
	}
#endif

	uint32_t FriendsImpl::GetFriendInvitationCount() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		return 0;
	}

	void FriendsImpl::GetFriendInvitationByIndex(uint32_t index, GalaxyID& userID, uint32_t& sendTime) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };
	}

	void FriendsImpl::RespondToFriendInvitation(GalaxyID userID, bool accept
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IFriendInvitationRespondToListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener,
#endif
			& IFriendInvitationRespondToListener::OnFriendInvitationRespondToFailure, userID,
#if GALAXY_BUILD_FEATURE_HAS_IFRIEND_INVITEEXTRAFAILREASONS
			IFriendInvitationRespondToListener::FAILURE_REASON_USER_ALREADY_FRIEND
#else
			IFriendInvitationRespondToListener::FAILURE_REASON_FRIEND_INVITATION_DOES_NOT_EXIST
#endif
		);
	}

	void FriendsImpl::DeleteFriend(GalaxyID userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IFriendDeleteListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener,
#endif
			& IFriendDeleteListener::OnFriendDeleteFailure, userID, IFriendDeleteListener::FAILURE_REASON_UNDEFINED);
	}

#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE
	void FriendsImpl::SetRichPresence(const char* key, const char* value
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		util::safe_fix_null_char_ptr(key);
		util::safe_fix_null_char_ptr(value);

		intf->config->GetLocalUserData()->stats.SetRichPresence(key, value);

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RichPresenceChangeMessage{ request_id, 0, RichPresenceChangeMessage::ACTION_SET, key, value });
	}

	void FriendsImpl::DeleteRichPresence(const char* key
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		util::safe_fix_null_char_ptr(key);

		intf->config->GetLocalUserData()->stats.EraseRichPresence(key);

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RichPresenceChangeMessage{ request_id, 0, RichPresenceChangeMessage::ACTION_DELETE, key });
	}

	void FriendsImpl::ClearRichPresence(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		intf->config->GetLocalUserData()->stats.ClearRichPresence();

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RichPresenceChangeMessage{ request_id, 0, RichPresenceChangeMessage::ACTION_CLEAR });
	}
#endif

	void FriendsImpl::RichPresenceChangeMessageProcessed(const std::shared_ptr<RichPresenceChangeMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

#if GALAXY_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE
		if (intf->config->IsSelfUserID(data->id)) {
			IRichPresenceChangeListener* listener = nullptr;
			listeners->PopRequestListener(data->request_id, listener);

			if (data->success) {
				listeners->NotifyAllNow(listener, &IRichPresenceChangeListener::OnRichPresenceChangeSuccess);
#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
				listeners->NotifyAllNow(&IRichPresenceListener::OnRichPresenceUpdated, intf->config->GetApiGalaxyID());
#endif
			}
			else {
				listeners->NotifyAllNow(listener, &IRichPresenceChangeListener::OnRichPresenceChangeFailure, IRichPresenceChangeListener::FAILURE_REASON_UNDEFINED);
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
#endif
	}

#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
	void FriendsImpl::RequestRichPresence(GalaxyID userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IRichPresenceRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (intf->config->IsSelfUserID(userID)) {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->NotifyAll(listener, &IRichPresenceRetrieveListener::OnRichPresenceRetrieveSuccess, userID);
#endif
#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
			listeners->NotifyAll(&IRichPresenceListener::OnRichPresenceUpdated, userID);
#endif
		}
		else {
			uint64_t request_id = MessageUniqueID::get();
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->AddRequestListener(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeRichPresence, request_id, userID });
		}
	}

	const char* FriendsImpl::GetRichPresence(const char* key, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		util::safe_fix_null_char_ptr(key);

		return intf->user->GetGalaxyUserData(userID)->stats.GetRichPresence(key).c_str();
	}

	void FriendsImpl::GetRichPresenceCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		util::safe_fix_null_char_ptr(key);

		if (buffer != nullptr) {
			std::string value = intf->user->GetGalaxyUserData(userID)->stats.GetRichPresence(key);
			universelan::util::safe_copy_str_n(value, buffer, bufferLength);
		}
	}

	uint32_t FriendsImpl::GetRichPresenceCount(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto entry = intf->user->GetGalaxyUserData(userID);
		return entry->stats.run_locked_richpresence<uint32_t>([&](auto& map) -> uint32_t {
			return (uint32_t)map.size();
			});
	}

	GetRichPresenceReturnT::type FriendsImpl::GetRichPresenceByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto entry = intf->user->GetGalaxyUserData(userID);
		return entry->stats.run_locked_richpresence<GetRichPresenceReturnT::type>([&](auto& map) -> GetRichPresenceReturnT::type {
			auto ref = container_get_by_index(map, index);

			if (!ref) {
				return GetRichPresenceReturnT::value_false();
			}

			if (key != nullptr) {
				universelan::util::safe_copy_str_n(ref->first, key, keyLength);
			}
			if (value != nullptr) {
				universelan::util::safe_copy_str_n(ref->second, value, valueLength);
			}

			return GetRichPresenceReturnT::value_true();
			});
	}
#endif

	void FriendsImpl::RequestRichPresenceProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IRichPresenceRetrieveListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
#endif

		if (data->found) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			entry->stats = data->asuc;
			if (entry->nickname != data->nickname) {
				entry->nickname = data->nickname;
			}

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->NotifyAllNow(listener, &IRichPresenceRetrieveListener::OnRichPresenceRetrieveSuccess, data->id);
#endif
#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
			listeners->NotifyAllNow(&IRichPresenceListener::OnRichPresenceUpdated, data->id);
#endif

		}
		else {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->NotifyAllNow(listener, &IRichPresenceRetrieveListener::OnRichPresenceRetrieveFailure, data->id, IRichPresenceRetrieveListener::FAILURE_REASON_UNDEFINED);
#endif
		}
	}

#if GALAXY_BUILD_FEATURE_HAS_GETRICHPRESENCEKEYBYINDEX
	/**
	 * Returns a key from the rich presence storage by index.
	 *
	 * @remark This call is not thread-safe as opposed to GetRichPresenceKeyByIndexCopy().
	 *
	 * @pre Retrieve the rich presence first by calling RequestRichPresence().
	 *
	 * @param [in] index Index as an integer in the range of [0, number of entries).
	 * @param [in] userID The ID of the user.
	 * @return The rich presence key under the index of the user.
	 */
	const char* FriendsImpl::GetRichPresenceKeyByIndex(uint32_t index, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		auto entry = intf->user->GetGalaxyUserData(userID);
		return entry->stats.run_locked_richpresence<const char*>([&](auto& map) -> const char* {
			auto ref = container_get_by_index(map, index);

			if (!ref) {
				return "";
			}

			return ref->first.c_str();
			});
	}

	/**
	 * Copies a key from the rich presence storage by index to a buffer.
	 *
	 * @pre Retrieve the rich presence first by calling RequestRichPresence().
	 *
	 * @param [in] index Index as an integer in the range of [0, number of entries).
	 * @param [in, out] buffer The output buffer.
	 * @param [in] bufferLength The size of the output buffer.
	 * @param [in] userID The ID of the user.
	 */
	void FriendsImpl::GetRichPresenceKeyByIndexCopy(uint32_t index, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		auto entry = intf->user->GetGalaxyUserData(userID);
		entry->stats.run_locked_richpresence<void>([&](auto& map) -> void {
			auto ref = container_get_by_index(map, index);
			if (ref && buffer != nullptr) {
				universelan::util::safe_copy_str_n(ref->first, buffer, bufferLength);
			}
			});
	}

#endif

#if GALAXY_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER
	void FriendsImpl::ShowOverlayInviteDialog(const char* connectionString) {
		tracer::Trace trace{ connectionString, __FUNCTION__, tracer::Trace::IFRIENDS };

		util::safe_fix_null_char_ptr(connectionString);

		std::cout << "ShowOverlayInviteDialog\n\t" << connectionString << std::endl;
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISENDINVITATIONLISTENER
	void FriendsImpl::SendInvitation(GalaxyID userID, const char* connectionString
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, ISendInvitationListener* const listener
#endif
	) {
		tracer::Trace trace{ connectionString, __FUNCTION__, tracer::Trace::IFRIENDS };

		bool contains = false;
		{
			lock_t lock(mtx_online_friends);
			contains = online_friends.contains(userID);
		}

		if (!contains) {
			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
				listener,
#endif
				& ISendInvitationListener::OnInvitationSendFailure, userID, connectionString, ISendInvitationListener::FAILURE_REASON_RECEIVER_DOES_NOT_ALLOW_INVITING);
			return;
		}

		intf->client->GetConnection().SendAsync(InvitationMessage{ MessageUniqueID::get(), userID, util::safe_fix_null_char_ptr_ret(connectionString)});

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener,
#endif
			& ISendInvitationListener::OnInvitationSendSuccess, userID, connectionString);
	}
#endif

#if GALAXY_BUILD_FEATURE_FIND_USER
	void FriendsImpl::FindUser(const char* userSpecifier
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IUserFindListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener,
#endif
			& IUserFindListener::OnUserFindFailure, userSpecifier, IUserFindListener::FAILURE_REASON_UNDEFINED);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISUSERINTHESAMEGAME
	bool FriendsImpl::IsUserInTheSameGame(GalaxyID userID) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		lock_t lock(mtx_online_friends);
		return (userID == intf->user->GetGalaxyID()) || online_friends.contains(userID);
	}
#endif

	void FriendsImpl::ChangeOnlineStatus(GalaxyID userID, bool isOnline)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (isOnline) {
			{
				lock_t lock(mtx_online_friends);
				online_friends.insert(userID);
			}
#if GALAXY_BUILD_FEATURE_HAS_FRIENDADDLISTENER
			listeners->NotifyAllNow(&IFriendAddListener::OnFriendAdded, userID, IFriendAddListener::INVITATION_DIRECTION_INCOMING);
#endif
		}
		else {
			{
				lock_t lock(mtx_online_friends);
				online_friends.erase(userID);
			}
#if GALAXY_BUILD_FEATURE_HAS_FRIENDADDLISTENER
			listeners->NotifyAllNow(&IFriendDeleteListener::OnFriendDeleteSuccess, userID);
#endif
		}
	}

	void FriendsImpl::InvitationReceived(const std::shared_ptr<InvitationMessage>& data)
	{
#if GALAXY_BUILD_FEATURE_HAS_IGAMEINVITATIONRECEIVEDLISTENER
		listeners->NotifyAllNow(&IGameInvitationReceivedListener::OnGameInvitationReceived, data->user_id, data->connection_string.c_str());

		if (intf->config->AutoAcceptGameInvitationsEnabled()) {
			listeners->NotifyAllNow(&IGameJoinRequestedListener::OnGameJoinRequested, data->user_id, data->connection_string.c_str());
		}
#endif
	}
}
