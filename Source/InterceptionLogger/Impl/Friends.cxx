#include "Friends.hxx"

#include <Tracer.hxx>
#include <GalaxyDLL.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;
	FriendsImpl::FriendsImpl()
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

		auto result = RealGalaxyDLL_Friends()->GetDefaultAvatarCriteria();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void FriendsImpl::SetDefaultAvatarCriteria(AvatarCriteriaImpl defaultAvatarCriteria) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("defaultAvatarCriteria: {}", defaultAvatarCriteria));
		}

		RealGalaxyDLL_Friends()->SetDefaultAvatarCriteria(defaultAvatarCriteria);
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
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
#if GALAXY_BUILD_FEATURE_HAS_1_73_AVATARTYPE_CRITERIA
			trace.write_all(std::format("avatarCriteria: {}", avatarCriteria));
#endif
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Friends()->RequestUserInformation(userID
#if GALAXY_BUILD_FEATURE_HAS_1_73_AVATARTYPE_CRITERIA
			, avatarCriteria
#endif
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, listener
#endif
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_USERDATAINFOAVAILABLE
	bool FriendsImpl::IsUserInformationAvailable(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = RealGalaxyDLL_Friends()->IsUserInformationAvailable(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif

	const char* FriendsImpl::GetPersonaName() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		auto result = RealGalaxyDLL_Friends()->GetPersonaName();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_IFRIENDS_GET_FRIEND_PERSONA_AVATAR_COPY
	void FriendsImpl::GetPersonaNameCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		RealGalaxyDLL_Friends()->GetPersonaNameCopy(buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_PERSONASTATE_ENUM
	PersonaState FriendsImpl::GetPersonaState() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = RealGalaxyDLL_Friends()->GetPersonaState();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;

	}
#endif

	const char* FriendsImpl::GetFriendPersonaName(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = RealGalaxyDLL_Friends()->GetFriendPersonaName(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_IFRIENDS_GET_FRIEND_PERSONA_AVATAR_COPY
	void FriendsImpl::GetFriendPersonaNameCopy(GalaxyID userID, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		RealGalaxyDLL_Friends()->GetFriendPersonaNameCopy(userID, buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_PERSONASTATE_ENUM
	PersonaState FriendsImpl::GetFriendPersonaState(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = RealGalaxyDLL_Friends()->GetFriendPersonaState(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;
	}
#endif

	const char* FriendsImpl::GetFriendAvatarUrl(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("avatarType: {}", avatarType));
		}

		auto result = RealGalaxyDLL_Friends()->GetFriendAvatarUrl(userID, avatarType);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_IFRIENDS_GET_FRIEND_PERSONA_AVATAR_COPY
	void FriendsImpl::GetFriendAvatarUrlCopy(GalaxyID userID, AvatarType avatarType, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("avatarType: {}", avatarType));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		RealGalaxyDLL_Friends()->GetFriendAvatarUrlCopy(userID, avatarType, buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_1_73_AVATARTYPE_CRITERIA
	uint32_t FriendsImpl::GetFriendAvatarImageID(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("avatarType: {}", avatarType));
		}

		auto result = RealGalaxyDLL_Friends()->GetFriendAvatarImageID(userID, avatarType);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void FriendsImpl::GetFriendAvatarImageRGBA(GalaxyID userID, AvatarType avatarType, GetImageRGBABufferType* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("avatarType: {}", avatarType));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		RealGalaxyDLL_Friends()->GetFriendAvatarImageRGBA(userID, avatarType, buffer, bufferLength);
	}

	bool FriendsImpl::IsFriendAvatarImageRGBAAvailable(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("avatarType: {}", avatarType));
		}

		auto result = RealGalaxyDLL_Friends()->IsFriendAvatarImageRGBAAvailable(userID, avatarType);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif

	void FriendsImpl::RequestFriendList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IFriendListListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Friends()->RequestFriendList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener
#endif
		);
	}

#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
	bool FriendsImpl::IsFriend(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = RealGalaxyDLL_Friends()->IsFriend(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif

	uint32_t FriendsImpl::GetFriendCount() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = RealGalaxyDLL_Friends()->GetFriendCount();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	GalaxyID FriendsImpl::GetFriendByIndex(uint32_t index) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		auto result = RealGalaxyDLL_Friends()->GetFriendByIndex(index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3

	void FriendsImpl::SendFriendInvitation(GalaxyID userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IFriendInvitationSendListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Friends()->SendFriendInvitation(userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, listener
#endif
		);
	}

	void FriendsImpl::RequestFriendInvitationList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IFriendInvitationListRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Friends()->RequestFriendInvitationList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener
#endif
		);
	}

#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER
	void FriendsImpl::RequestSentFriendInvitationList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		ISentFriendInvitationListRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Friends()->RequestSentFriendInvitationList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener
#endif
		);
	}
#endif

	uint32_t FriendsImpl::GetFriendInvitationCount() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = RealGalaxyDLL_Friends()->GetFriendInvitationCount();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void FriendsImpl::GetFriendInvitationByIndex(uint32_t index, GalaxyID& userID, uint32_t& sendTime) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		RealGalaxyDLL_Friends()->GetFriendInvitationByIndex(index, userID, sendTime);

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
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("accept: {}", accept));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Friends()->RespondToFriendInvitation(userID, accept
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, listener
#endif	
		);
	}

	void FriendsImpl::DeleteFriend(GalaxyID userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IFriendDeleteListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Friends()->DeleteFriend(userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, listener
#endif	
		);
	}

#endif

	void FriendsImpl::SetRichPresence(const char* key, const char* value
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
			trace.write_all(std::format("value: {}", util::safe_fix_null_char_ptr_annotate_ret(value)));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Friends()->SetRichPresence(key, value
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, listener
#endif	
		);
	}

	void FriendsImpl::DeleteRichPresence(const char* key
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Friends()->DeleteRichPresence(key
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, listener
#endif	
		);
	}

	void FriendsImpl::ClearRichPresence(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Friends()->ClearRichPresence(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener
#endif	
		);
	}

#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
	void FriendsImpl::RequestRichPresence(GalaxyID userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IRichPresenceRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		RealGalaxyDLL_Friends()->RequestRichPresence(userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, listener
#endif	
		);
	}

	const char* FriendsImpl::GetRichPresence(const char* key, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = RealGalaxyDLL_Friends()->GetRichPresence(key, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	void FriendsImpl::GetRichPresenceCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
			trace.write_all(std::format("userID: {}", userID));
		}

		RealGalaxyDLL_Friends()->GetRichPresenceCopy(key, buffer, bufferLength, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}

	uint32_t FriendsImpl::GetRichPresenceCount(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = RealGalaxyDLL_Friends()->GetRichPresenceCount(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	GetRichPresenceReturnT::type FriendsImpl::GetRichPresenceByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
			trace.write_all(std::format("key: {}", (void*)key));
			trace.write_all(std::format("keyLength: {}", keyLength));
			trace.write_all(std::format("key: {}", (void*)value));
			trace.write_all(std::format("keyLength: {}", valueLength));
			trace.write_all(std::format("userID: {}", userID));
		}

#if !GALAXY_BUILD_FEATURE_IFRIENDS_ISTATS_UPDATE_1_127_0
		auto result =
#endif
		RealGalaxyDLL_Friends()->GetRichPresenceByIndex(index, key, keyLength, value, valueLength, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
#if !GALAXY_BUILD_FEATURE_IFRIENDS_ISTATS_UPDATE_1_127_0
			trace.write_all(std::format("result: {}", result));
#endif
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate(key, keyLength)));
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate(value, valueLength)));
		}

#if !GALAXY_BUILD_FEATURE_IFRIENDS_ISTATS_UPDATE_1_127_0
		return result;
#endif
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_GETRICHPRESENCEKEYBYINDEX
	const char* FriendsImpl::GetRichPresenceKeyByIndex(uint32_t index, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = RealGalaxyDLL_Friends()->GetRichPresenceKeyByIndex(index, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	void FriendsImpl::GetRichPresenceKeyByIndexCopy(uint32_t index, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
			trace.write_all(std::format("userID: {}", userID));
		}

		RealGalaxyDLL_Friends()->GetPersonaNameCopy(buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}

#endif

	void FriendsImpl::ShowOverlayInviteDialog(const char* connectionString) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
		}

		RealGalaxyDLL_Friends()->ShowOverlayInviteDialog(connectionString);
	}

#if GALAXY_BUILD_FEATURE_HAS_ISENDINVITATIONLISTENER
	void FriendsImpl::SendInvitation(GalaxyID userID, const char* connectionString
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, ISendInvitationListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
			trace.write_all(std::format("connectionString: {}", util::safe_fix_null_char_ptr_annotate_ret(connectionString)));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif	
		}

		RealGalaxyDLL_Friends()->SendInvitation(userID, connectionString
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, listener
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
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userSpecifier: {}", util::safe_fix_null_char_ptr_annotate_ret(userSpecifier)));
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif	
		}

		RealGalaxyDLL_Friends()->FindUser(userSpecifier
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			, listener
#endif	
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISUSERINTHESAMEGAME
	bool FriendsImpl::IsUserInTheSameGame(GalaxyID userID) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IFRIENDS | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = RealGalaxyDLL_Friends()->IsUserInTheSameGame(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif
}
