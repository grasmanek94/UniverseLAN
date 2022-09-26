#include "Friends.hxx"

#include "UniverseLAN.hxx"

#include <algorithm>

namespace universelan::client {
	using namespace galaxy::api;
	FriendsImpl::FriendsImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() }
	{
		tracer::Trace trace{ __FUNCTION__ };
	}

	FriendsImpl::~FriendsImpl()
	{
		tracer::Trace trace{ __FUNCTION__ };

	}

	AvatarCriteria FriendsImpl::GetDefaultAvatarCriteria() {
		tracer::Trace trace{ __FUNCTION__ };

		return 0;
	}

	void FriendsImpl::SetDefaultAvatarCriteria(AvatarCriteria defaultAvatarCriteria) {
		tracer::Trace trace{ __FUNCTION__ };

	}

	void FriendsImpl::RequestUserInformation(
		GalaxyID userID,
		AvatarCriteria avatarCriteria,
		IUserInformationRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

	}

	bool FriendsImpl::IsUserInformationAvailable(GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return false;
	}

	const char* FriendsImpl::GetPersonaName() {
		tracer::Trace trace{ __FUNCTION__ };

		return intf_inst.config->GetCustomPersonaName().c_str();
	}

	void FriendsImpl::GetPersonaNameCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		std::copy_n(intf_inst.config->GetCustomPersonaName().c_str(), std::min((size_t)bufferLength, intf_inst.config->GetCustomPersonaName().length()), buffer);
	}

	PersonaState FriendsImpl::GetPersonaState() {
		tracer::Trace trace{ __FUNCTION__ };

		return PERSONA_STATE_ONLINE;
	}

	const char* FriendsImpl::GetFriendPersonaName(GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return "GetFriendPersonaName";
	}

	void FriendsImpl::GetFriendPersonaNameCopy(GalaxyID userID, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		std::copy_n(GetFriendPersonaName(userID), std::min((size_t)bufferLength, strlen(GetFriendPersonaName(userID))), buffer);
	}

	PersonaState FriendsImpl::GetFriendPersonaState(GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return PERSONA_STATE_OFFLINE;
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


	}

	void FriendsImpl::RequestFriendInvitationList(IFriendInvitationListRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	void FriendsImpl::RequestSentFriendInvitationList(ISentFriendInvitationListRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };


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


	}

	void FriendsImpl::DeleteFriend(GalaxyID userID, IFriendDeleteListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	void FriendsImpl::SetRichPresence(const char* key, const char* value, IRichPresenceChangeListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	void FriendsImpl::DeleteRichPresence(const char* key, IRichPresenceChangeListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	void FriendsImpl::ClearRichPresence(IRichPresenceChangeListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	void FriendsImpl::RequestRichPresence(GalaxyID userID, IRichPresenceRetrieveListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	const char* FriendsImpl::GetRichPresence(const char* key, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return "";
	}

	void FriendsImpl::GetRichPresenceCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	uint32_t FriendsImpl::GetRichPresenceCount(GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return 0;
	}

	void FriendsImpl::GetRichPresenceByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	void FriendsImpl::ShowOverlayInviteDialog(const char* connectionString) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	void FriendsImpl::SendInvitation(GalaxyID userID, const char* connectionString, ISendInvitationListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	void FriendsImpl::FindUser(const char* userSpecifier, IUserFindListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };


	}

	bool FriendsImpl::IsUserInTheSameGame(GalaxyID userID) const {
		tracer::Trace trace{ __FUNCTION__ };

		return true;
	}
}
