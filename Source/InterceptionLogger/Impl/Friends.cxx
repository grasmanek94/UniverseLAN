#include "Friends.hxx"

#include "Listeners/FriendsListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>
#include <magic_enum/magic_enum_flags.hpp>

#include <format>

template <>
struct magic_enum::customize::enum_range<galaxy::api::AvatarType> {
	static constexpr bool is_flags = true;
};

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::IFRIENDS;
	}

	FriendsImpl::FriendsImpl(FuncT::F intf, IListenerRegistrar* notifications) :
		intf{ intf },
		notifications{ notifications },
		listeners{ notifications } {
#if GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED
		listeners.AddListener<PersonaDataChangedListener>();
#endif
#if GALAXY_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER
		listeners.AddListener<GameJoinRequestedListener>();
#endif
#if GALAXY_BUILD_FEATURE_HAS_IGAMEINVITATIONRECEIVEDLISTENER
		listeners.AddListener<GameInvitationReceivedListener>();
#endif
#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER
		listeners.AddListener<SendInvitationListener>();
#endif
#if GALAXY_BUILD_FEATURE_HAS_IFRIENDLISTLISTENER
		listeners.AddListener<FriendListListener>();
#endif
#if GALAXY_BUILD_FEATURE_HAS_IRICHPRECENSECHANGELISTENER
		listeners.AddListener<RichPresenceChangeListener>();
#endif
#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
		listeners.AddListener<RichPresenceListener>();
#endif
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		listeners.AddListener<UserInformationRetrieveListener>();
#endif
#if GALAXY_BUILD_FEATURE_HAS_FRIENDADDLISTENER
		listeners.AddListener<FriendAddListener>();
#endif
#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3
		listeners.AddListener<FriendInvitationSendListener>();
#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER
		listeners.AddListener<SentFriendInvitationListRetrieveListener>();
#endif
		listeners.AddListener<FriendInvitationListener>();
		listeners.AddListener<FriendInvitationRespondToListener>();
		listeners.AddListener<FriendDeleteListener>();
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		listeners.AddListener<RichPresenceRetrieveListener>();
#endif

#if GALAXY_BUILD_FEATURE_FIND_USER
		listeners.AddListener<UserFindListener>();
#endif
	}

	FriendsImpl::~FriendsImpl() {
		listeners.UnregisterAllListeners();
	}

#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_TYPE
	AvatarCriteriaImpl FriendsImpl::GetDefaultAvatarCriteria() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->GetDefaultAvatarCriteria();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void FriendsImpl::SetDefaultAvatarCriteria(AvatarCriteriaImpl defaultAvatarCriteria) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("defaultAvatarCriteria: {}", defaultAvatarCriteria));
		}

		intf()->SetDefaultAvatarCriteria(defaultAvatarCriteria);
	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED
	void FriendsImpl::RequestUserInformation(
		GalaxyID userID
#if GALAXY_BUILD_FEATURE_HAS_1_73_AVATARTYPE_CRITERIA
		, AvatarCriteriaImpl avatarCriteria
#endif
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IUserInformationRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
#if GALAXY_BUILD_FEATURE_HAS_1_73_AVATARTYPE_CRITERIA
			trace.write_all(std::format("avatarCriteria: {}({})", avatarCriteria, 
				magic_enum::enum_flags_name((AvatarType)avatarCriteria)));
#endif
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->RequestUserInformation(userID
#if GALAXY_BUILD_FEATURE_HAS_1_73_AVATARTYPE_CRITERIA
			, avatarCriteria
#endif
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, UserInformationRetrieveListener::encapsulate(listener)
#endif
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_USERDATAINFOAVAILABLE
	bool FriendsImpl::IsUserInformationAvailable(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = intf()->IsUserInformationAvailable(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
}
#endif

	const char* FriendsImpl::GetPersonaName() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->GetPersonaName();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_IFRIENDS_GET_FRIEND_PERSONA_AVATAR_COPY
	void FriendsImpl::GetPersonaNameCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("buffer(addr): {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		intf()->GetPersonaNameCopy(buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_PERSONASTATE_ENUM
	PersonaState FriendsImpl::GetPersonaState() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = intf()->GetPersonaState();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;

	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_HAS_PERSONANAME_AND_AVATARURL
	const char* FriendsImpl::GetFriendPersonaName(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = intf()->GetFriendPersonaName(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_GET_FRIEND_PERSONA_AVATAR_COPY
	void FriendsImpl::GetFriendPersonaNameCopy(GalaxyID userID, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		intf()->GetFriendPersonaNameCopy(userID, buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_PERSONASTATE_ENUM
	PersonaState FriendsImpl::GetFriendPersonaState(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = intf()->GetFriendPersonaState(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;
	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_HAS_PERSONANAME_AND_AVATARURL
	const char* FriendsImpl::GetFriendAvatarUrl(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("avatarType: {}", magic_enum::enum_flags_name(avatarType)));
		}

		auto result = intf()->GetFriendAvatarUrl(userID, avatarType);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_GET_FRIEND_PERSONA_AVATAR_COPY
	void FriendsImpl::GetFriendAvatarUrlCopy(GalaxyID userID, AvatarType avatarType, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("avatarType: {}", magic_enum::enum_flags_name(avatarType)));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		intf()->GetFriendAvatarUrlCopy(userID, avatarType, buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_1_73_AVATARTYPE_CRITERIA
	uint32_t FriendsImpl::GetFriendAvatarImageID(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("avatarType: {}", magic_enum::enum_flags_name(avatarType)));
		}

		auto result = intf()->GetFriendAvatarImageID(userID, avatarType);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void FriendsImpl::GetFriendAvatarImageRGBA(GalaxyID userID, AvatarType avatarType, GetImageRGBABufferType* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("avatarType: {}", magic_enum::enum_flags_name(avatarType)));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		intf()->GetFriendAvatarImageRGBA(userID, avatarType, buffer, bufferLength);
	}

#if GALAXY_BUILD_FEATURE_IFRIENDS_HAS_ISAVATARRGBAIMAGEAVAILABLE
	bool FriendsImpl::IsFriendAvatarImageRGBAAvailable(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("avatarType: {}", magic_enum::enum_flags_name(avatarType)));
		}

		auto result = intf()->IsFriendAvatarImageRGBAAvailable(userID, avatarType);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif
#endif

#if GALAXY_BUILD_FEATURE_HAS_IFRIENDLISTLISTENER
	void FriendsImpl::RequestFriendList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IFriendListListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
	}

		intf()->RequestFriendList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			FriendListListener::encapsulate(listener)
#endif
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
	bool FriendsImpl::IsFriend(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = intf()->IsFriend(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IFRIENDLISTLISTENER
	uint32_t FriendsImpl::GetFriendCount() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = intf()->GetFriendCount();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	GalaxyID FriendsImpl::GetFriendByIndex(uint32_t index) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		auto result = intf()->GetFriendByIndex(index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3

	void FriendsImpl::SendFriendInvitation(GalaxyID userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IFriendInvitationSendListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->SendFriendInvitation(userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, FriendInvitationSendListener::encapsulate(listener)
#endif
		);
	}

	void FriendsImpl::RequestFriendInvitationList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IFriendInvitationListRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->RequestFriendInvitationList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			FriendInvitationListRetrieveListener::encapsulate(listener)
#endif
		);
	}

#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER
	void FriendsImpl::RequestSentFriendInvitationList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		ISentFriendInvitationListRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->RequestSentFriendInvitationList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			SentFriendInvitationListRetrieveListener::encapsulate(listener)
#endif
		);
	}
#endif

	uint32_t FriendsImpl::GetFriendInvitationCount() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = intf()->GetFriendInvitationCount();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void FriendsImpl::GetFriendInvitationByIndex(uint32_t index, GalaxyID& userID, uint32_t& sendTime) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		intf()->GetFriendInvitationByIndex(index, userID, sendTime);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("sendTime: {}", sendTime));
		}
	}

	void FriendsImpl::RespondToFriendInvitation(GalaxyID userID, bool accept
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IFriendInvitationRespondToListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("accept: {}", accept));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->RespondToFriendInvitation(userID, accept
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, FriendInvitationRespondToListener::encapsulate(listener)
#endif	
		);
	}

	void FriendsImpl::DeleteFriend(GalaxyID userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IFriendDeleteListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->DeleteFriend(userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, FriendDeleteListener::encapsulate(listener)
#endif	
		);
	}

#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_SET_DEL_CLR_RICHPRESENCE
	void FriendsImpl::SetRichPresence(const char* key, const char* value
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
			trace.write_all(std::format("value: {}", util::safe_fix_null_char_ptr_annotate_ret(value)));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->SetRichPresence(key, value
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, RichPresenceChangeListener::encapsulate(listener)
#endif	
		);
	}

	void FriendsImpl::DeleteRichPresence(const char* key
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
	}

		intf()->DeleteRichPresence(key
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, RichPresenceChangeListener::encapsulate(listener)
#endif	
		);
	}

	void FriendsImpl::ClearRichPresence(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
	}

		intf()->ClearRichPresence(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			RichPresenceChangeListener::encapsulate(listener)
#endif	
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
	void FriendsImpl::RequestRichPresence(GalaxyID userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IRichPresenceRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
	}

		intf()->RequestRichPresence(userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, RichPresenceRetrieveListener::encapsulate(listener)
#endif	
		);
	}

	const char* FriendsImpl::GetRichPresence(const char* key, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = intf()->GetRichPresence(key, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	void FriendsImpl::GetRichPresenceCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
			trace.write_all(std::format("userID: {}", userID));
		}

		intf()->GetRichPresenceCopy(key, buffer, bufferLength, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}

	uint32_t FriendsImpl::GetRichPresenceCount(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = intf()->GetRichPresenceCount(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	GetRichPresenceReturnT::type FriendsImpl::GetRichPresenceByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
			trace.write_all(std::format("key: {}", (void*)key));
			trace.write_all(std::format("keyLength: {}", keyLength));
			trace.write_all(std::format("value: {}", (void*)value));
			trace.write_all(std::format("valueLength: {}", valueLength));
			trace.write_all(std::format("userID: {}", userID));
		}

#if !GALAXY_BUILD_FEATURE_IFRIENDS_ISTATS_UPDATE_1_127_0
		auto result =
#endif
			intf()->GetRichPresenceByIndex(index, key, keyLength, value, valueLength, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
#if !GALAXY_BUILD_FEATURE_IFRIENDS_ISTATS_UPDATE_1_127_0
			trace.write_all(std::format("result: {}", result));
#endif
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate(key, keyLength)));
			trace.write_all(std::format("value: {}", util::safe_fix_null_char_ptr_annotate(value, valueLength)));
		}

#if !GALAXY_BUILD_FEATURE_IFRIENDS_ISTATS_UPDATE_1_127_0
		return result;
#endif
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_GETRICHPRESENCEKEYBYINDEX
	const char* FriendsImpl::GetRichPresenceKeyByIndex(uint32_t index, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = intf()->GetRichPresenceKeyByIndex(index, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	void FriendsImpl::GetRichPresenceKeyByIndexCopy(uint32_t index, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
			trace.write_all(std::format("userID: {}", userID));
		}

		intf()->GetPersonaNameCopy(buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}

#endif

#if GALAXY_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER
	void FriendsImpl::ShowOverlayInviteDialog(const char* connectionString) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
		}

		intf()->ShowOverlayInviteDialog(connectionString);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISENDINVITATIONLISTENER
	void FriendsImpl::SendInvitation(GalaxyID userID, const char* connectionString
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, ISendInvitationListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif	
		}

		intf()->SendInvitation(userID, connectionString
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, SendInvitationListener::encapsulate(listener)
#endif	
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_FIND_USER
	void FriendsImpl::FindUser(const char* userSpecifier
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IUserFindListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userSpecifier: {}", util::safe_fix_null_char_ptr_annotate_ret(userSpecifier)));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif	
		}

		intf()->FindUser(userSpecifier
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, UserFindListener::encapsulate(listener)
#endif	
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISUSERINTHESAMEGAME
	bool FriendsImpl::IsUserInTheSameGame(GalaxyID userID) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = intf()->IsUserInTheSameGame(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif
}
