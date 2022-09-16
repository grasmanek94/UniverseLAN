#include "Friends.hxx"

#include "UniverseLAN.hxx"

#include <algorithm>

namespace galaxy
{
	namespace api
	{
		FriendsImpl::FriendsImpl(ListenerRegistrarImpl* listeners) : listeners{ listeners }
		{}

		FriendsImpl::~FriendsImpl()
		{
		}

		AvatarCriteria FriendsImpl::GetDefaultAvatarCriteria() {
			return 0;
		}

		void FriendsImpl::SetDefaultAvatarCriteria(AvatarCriteria defaultAvatarCriteria) {

		}

		void FriendsImpl::RequestUserInformation(
			GalaxyID userID,
			AvatarCriteria avatarCriteria,
			IUserInformationRetrieveListener* const listener) {

		}

		bool FriendsImpl::IsUserInformationAvailable(GalaxyID userID) {
			return false;
		}

		const char* FriendsImpl::GetPersonaName() {
			return config->GetCustomPersonaName().c_str();
		}

		void FriendsImpl::GetPersonaNameCopy(char* buffer, uint32_t bufferLength) {
			std::copy_n(config->GetCustomPersonaName().c_str(), std::min((size_t)bufferLength, config->GetCustomPersonaName().length()), buffer);
		}

		PersonaState FriendsImpl::GetPersonaState() {
			return PERSONA_STATE_ONLINE;
		}

		const char* FriendsImpl::GetFriendPersonaName(GalaxyID userID) {
			return "PersonaName";
		}

		void FriendsImpl::GetFriendPersonaNameCopy(GalaxyID userID, char* buffer, uint32_t bufferLength) {
			std::copy_n(GetFriendPersonaName(userID), std::min((size_t)bufferLength, strlen(GetFriendPersonaName(userID))), buffer);
		}

		PersonaState FriendsImpl::GetFriendPersonaState(GalaxyID userID) {
			return PERSONA_STATE_OFFLINE;
		}

		const char* FriendsImpl::GetFriendAvatarUrl(GalaxyID userID, AvatarType avatarType) {
			return "";
		}

		void FriendsImpl::GetFriendAvatarUrlCopy(GalaxyID userID, AvatarType avatarType, char* buffer, uint32_t bufferLength) {
			std::copy_n(GetFriendAvatarUrl(userID, avatarType), std::min((size_t)bufferLength, strlen(GetFriendAvatarUrl(userID, avatarType))), buffer);
		}

		uint32_t FriendsImpl::GetFriendAvatarImageID(GalaxyID userID, AvatarType avatarType) {
			return 0;
		}

		void FriendsImpl::GetFriendAvatarImageRGBA(GalaxyID userID, AvatarType avatarType, void* buffer, uint32_t bufferLength) {

		}

		bool FriendsImpl::IsFriendAvatarImageRGBAAvailable(GalaxyID userID, AvatarType avatarType) {
			return false;
		}

		void FriendsImpl::RequestFriendList(IFriendListListener* const listener) {

		}

		bool FriendsImpl::IsFriend(GalaxyID userID) {
			return true;
		}

		uint32_t FriendsImpl::GetFriendCount() {
			return 0;
		}

		GalaxyID FriendsImpl::GetFriendByIndex(uint32_t index) {
			return 0;
		}

		void FriendsImpl::SendFriendInvitation(GalaxyID userID, IFriendInvitationSendListener* const listener) {

		}

		void FriendsImpl::RequestFriendInvitationList(IFriendInvitationListRetrieveListener* const listener) {

		}

		void FriendsImpl::RequestSentFriendInvitationList(ISentFriendInvitationListRetrieveListener* const listener) {

		}

		uint32_t FriendsImpl::GetFriendInvitationCount() {
			return 0;
		}

		void FriendsImpl::GetFriendInvitationByIndex(uint32_t index, GalaxyID& userID, uint32_t& sendTime) {

		}

		void FriendsImpl::RespondToFriendInvitation(GalaxyID userID, bool accept, IFriendInvitationRespondToListener* const listener) {

		}

		void FriendsImpl::DeleteFriend(GalaxyID userID, IFriendDeleteListener* const listener) {

		}

		void FriendsImpl::SetRichPresence(const char* key, const char* value, IRichPresenceChangeListener* const listener) {

		}

		void FriendsImpl::DeleteRichPresence(const char* key, IRichPresenceChangeListener* const listener) {

		}

		void FriendsImpl::ClearRichPresence(IRichPresenceChangeListener* const listener) {

		}

		void FriendsImpl::RequestRichPresence(GalaxyID userID, IRichPresenceRetrieveListener* const listener) {

		}

		const char* FriendsImpl::GetRichPresence(const char* key, GalaxyID userID) {
			return "";
		}

		void FriendsImpl::GetRichPresenceCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {

		}

		uint32_t FriendsImpl::GetRichPresenceCount(GalaxyID userID) {
			return 0;
		}

		void FriendsImpl::GetRichPresenceByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {

		}

		void FriendsImpl::ShowOverlayInviteDialog(const char* connectionString) {

		}

		void FriendsImpl::SendInvitation(GalaxyID userID, const char* connectionString, ISendInvitationListener* const listener) {

		}

		void FriendsImpl::FindUser(const char* userSpecifier, IUserFindListener* const listener) {

		}

		bool FriendsImpl::IsUserInTheSameGame(GalaxyID userID) const {
			return true;
		}
	}
}
