#include "User.hxx"

namespace galaxy
{
	namespace api
	{
		User::~User()
		{
		}

		bool User::SignedIn() {
			return true;
		}

		GalaxyID User::GetGalaxyID() {
			return 0;
		}

		void User::SignInCredentials(const char* login, const char* password, IAuthListener* const listener) {

		}

		void User::SignInToken(const char* refreshToken, IAuthListener* const listener) {

		}

		void User::SignInLauncher(IAuthListener* const listener) {

		}

		void User::SignInSteam(const void* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName, IAuthListener* const listener) {

		}

		void User::SignInEpic(const char* epicAccessToken, const char* epicUsername, IAuthListener* const listener) {

		}

		void User::SignInGalaxy(bool requireOnline, IAuthListener* const listener) {

		}

		void User::SignInUWP(IAuthListener* const listener) {

		}

		void User::SignInPS4(const char* ps4ClientID, IAuthListener* const listener) {

		}

		void User::SignInXB1(const char* xboxOneUserID, IAuthListener* const listener) {

		}

		void User::SignInXBLive(const char* token, const char* signature, const char* marketplaceID, const char* locale, IAuthListener* const listener) {

		}

		void User::SignInAnonymous(IAuthListener* const listener) {

		}

		void User::SignInAnonymousTelemetry(IAuthListener* const listener) {

		}

		void User::SignInServerKey(const char* serverKey, IAuthListener* const listener) {

		}

		void User::SignOut() {

		}

		void User::RequestUserData(GalaxyID userID, ISpecificUserDataListener* const listener) {

		}

		bool User::IsUserDataAvailable(GalaxyID userID) {
			return true;
		}

		const char* User::GetUserData(const char* key, GalaxyID userID) {
			return "";
		}

		void User::GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {

		}

		void User::SetUserData(const char* key, const char* value, ISpecificUserDataListener* const listener) {

		}

		uint32_t User::GetUserDataCount(GalaxyID userID) {
			return 0;
		}

		bool User::GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
			return false;
		}

		void User::DeleteUserData(const char* key, ISpecificUserDataListener* const listener) {

		}

		bool User::IsLoggedOn() {
			return true;
		}

		void User::RequestEncryptedAppTicket(const void* data, uint32_t dataSize, IEncryptedAppTicketListener* const listener) {

		}

		void User::GetEncryptedAppTicket(void* encryptedAppTicket, uint32_t maxEncryptedAppTicketSize, uint32_t& currentEncryptedAppTicketSize) {

		}

		SessionID User::GetSessionID() {
			return 0;
		}

		const char* User::GetAccessToken() {
			return "";
		}

		void User::GetAccessTokenCopy(char* buffer, uint32_t bufferLength) {

		}

		bool User::ReportInvalidAccessToken(const char* accessToken, const char* info) {
			return false;
		}
	}
}


