#include "User.hxx"

#include "UniverseLAN.hxx"

namespace galaxy
{
	namespace api
	{
		UserImpl::~UserImpl()
		{
		}

		bool UserImpl::SignedIn() {
			return config->GetSignedIn();
		}

		GalaxyID UserImpl::GetGalaxyID() {
			return config->GetCustomGalaxyID();
		}

		void UserImpl::SignInCredentials(const char* login, const char* password, IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignInToken(const char* refreshToken, IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignInLauncher(IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignInSteam(const void* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName, IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignInEpic(const char* epicAccessToken, const char* epicUsername, IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignInGalaxy(bool requireOnline, IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignInUWP(IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignInPS4(const char* ps4ClientID, IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignInXB1(const char* xboxOneUserID, IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignInXBLive(const char* token, const char* signature, const char* marketplaceID, const char* locale, IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignInAnonymous(IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignInAnonymousTelemetry(IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignInServerKey(const char* serverKey, IAuthListener* const listener) {
			// Empty
		}

		void UserImpl::SignOut() {
			// Empty
		}

		void UserImpl::RequestUserData(GalaxyID userID, ISpecificUserDataListener* const listener) {

		}

		bool UserImpl::IsUserDataAvailable(GalaxyID userID) {
			return true;
		}

		const char* UserImpl::GetUserData(const char* key, GalaxyID userID) {
			return "";
		}

		void UserImpl::GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {

		}

		void UserImpl::SetUserData(const char* key, const char* value, ISpecificUserDataListener* const listener) {

		}

		uint32_t UserImpl::GetUserDataCount(GalaxyID userID) {
			return 0;
		}

		bool UserImpl::GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
			return false;
		}

		void UserImpl::DeleteUserData(const char* key, ISpecificUserDataListener* const listener) {

		}

		bool UserImpl::IsLoggedOn() {
			return true;
		}

		void UserImpl::RequestEncryptedAppTicket(const void* data, uint32_t dataSize, IEncryptedAppTicketListener* const listener) {

		}

		void UserImpl::GetEncryptedAppTicket(void* encryptedAppTicket, uint32_t maxEncryptedAppTicketSize, uint32_t& currentEncryptedAppTicketSize) {

		}

		SessionID UserImpl::GetSessionID() {
			return 0;
		}

		const char* UserImpl::GetAccessToken() {
			return "";
		}

		void UserImpl::GetAccessTokenCopy(char* buffer, uint32_t bufferLength) {

		}

		bool UserImpl::ReportInvalidAccessToken(const char* accessToken, const char* info) {
			return true;
		}
	}
}


