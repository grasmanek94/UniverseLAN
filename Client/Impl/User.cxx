#include "User.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>

namespace galaxy
{
	namespace api
	{
		UserImpl::UserImpl(ListenerRegistrarImpl* listeners) :listeners{ listeners } 
		{ }

		UserImpl::~UserImpl()
		{
		}

		bool UserImpl::SignedIn() {
			return config->GetSignedIn();
		}

		GalaxyID UserImpl::GetGalaxyID() {
			return config->GetCustomGalaxyID();
		}

		void UserImpl::SignIn(IAuthListener* const listener) {
			if (config->GetSignedIn()) {
				listeners->NotifyAll(listener, &IAuthListener::OnAuthSuccess);
				listeners->NotifyAll<IOperationalStateChangeListener>(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_LOGGED_ON);

			}
			else {
				listeners->NotifyAll(listener, &IAuthListener::OnAuthFailure, IAuthListener::FAILURE_REASON_EXTERNAL_SERVICE_FAILURE);
				listeners->NotifyAll<IOperationalStateChangeListener>(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN);
			}
		}

		void UserImpl::SignInCredentials(const char* login, const char* password, IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignInToken(const char* refreshToken, IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignInLauncher(IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignInSteam(const void* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName, IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignInEpic(const char* epicAccessToken, const char* epicUsername, IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignInGalaxy(bool requireOnline, IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignInUWP(IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignInPS4(const char* ps4ClientID, IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignInXB1(const char* xboxOneUserID, IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignInXBLive(const char* token, const char* signature, const char* marketplaceID, const char* locale, IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignInAnonymous(IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignInAnonymousTelemetry(IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignInServerKey(const char* serverKey, IAuthListener* const listener) {
			SignIn(listener);
		}

		void UserImpl::SignOut() {
			listeners->NotifyAll<IAuthListener>(&IAuthListener::OnAuthLost);
			listeners->NotifyAll<IOperationalStateChangeListener>(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN);
		}

		void UserImpl::RequestUserData(GalaxyID userID, ISpecificUserDataListener* const listener) {
			if (config->IsSelfUserID(userID)) {
				listeners->NotifyAll(listener, &ISpecificUserDataListener::OnSpecificUserDataUpdated, userID);
			}
			else {
				// TODO
			}
		}

		bool UserImpl::IsUserDataAvailable(GalaxyID userID) {
			if (config->IsSelfUserID(userID)) {
				return true;
			}
			else {
				return false;
			}
		}

		const char* UserImpl::GetUserData(const char* key, GalaxyID userID) {
			if (config->IsSelfUserID(userID)) {
				return config->GetUserData(key).c_str();
			}
			else {
				return "";
			}
		}

		void UserImpl::GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
			if (config->IsSelfUserID(userID)) {
				const std::string& str = config->GetUserData(key);
				std::copy_n(str.begin(), std::min((uint32_t)str.length(), bufferLength), buffer);
			}
			else {
				
			}
		}

		void UserImpl::SetUserData(const char* key, const char* value, ISpecificUserDataListener* const listener) {
			config->SetUserData(key, value);
			config->SaveStatsAndAchievements();

			listeners->NotifyAll(listener, &ISpecificUserDataListener::OnSpecificUserDataUpdated, config->GetApiGalaxyID());
		}

		uint32_t UserImpl::GetUserDataCount(GalaxyID userID) {
			if (config->IsSelfUserID(userID)) {
				return (uint32_t)config->GetASUC().UserData.size();
			}
			else {
				return 0;
			}	
		}

		bool UserImpl::GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
			if (config->IsSelfUserID(userID)) {
				auto ref = container_get_by_index(config->GetASUC().UserData, index);
				std::copy_n(ref.first.begin(), std::min((uint32_t)ref.first.length(), keyLength), key);
				std::copy_n(ref.second.begin(), std::min((uint32_t)ref.second.length(), valueLength), value);
			}
			else {

			}
			return false;
		}

		void UserImpl::DeleteUserData(const char* key, ISpecificUserDataListener* const listener) {
			config->SetUserData(key, "");
			config->SaveStatsAndAchievements();

			listeners->NotifyAll(listener, &ISpecificUserDataListener::OnSpecificUserDataUpdated, config->GetApiGalaxyID());
		}

		bool UserImpl::IsLoggedOn() {
			return config->GetSignedIn();
		}

		void UserImpl::RequestEncryptedAppTicket(const void* data, uint32_t dataSize, IEncryptedAppTicketListener* const listener) {
			listeners->NotifyAll(listener, &IEncryptedAppTicketListener::OnEncryptedAppTicketRetrieveSuccess);
		}

		void UserImpl::GetEncryptedAppTicket(void* encryptedAppTicket, uint32_t maxEncryptedAppTicketSize, uint32_t& currentEncryptedAppTicketSize) {
			((char*)encryptedAppTicket)[maxEncryptedAppTicketSize-1] = 0;
			currentEncryptedAppTicketSize = maxEncryptedAppTicketSize;
		}

		SessionID UserImpl::GetSessionID() {
			return 1;
		}

		const char* UserImpl::GetAccessToken() {
			return " ";
		}

		void UserImpl::GetAccessTokenCopy(char* buffer, uint32_t bufferLength) {
			buffer[0] = ' ';
			buffer[1] = 0;
		}

		bool UserImpl::ReportInvalidAccessToken(const char* accessToken, const char* info) {
			return true;
		}
	}
}


