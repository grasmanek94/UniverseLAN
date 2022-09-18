#include "User.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>

namespace universelan::client {
	using namespace galaxy::api;
	UserImpl::UserImpl(InterfaceInstances* intf) :
		mtx_user_data{}, intf{ intf },
		listeners{ intf->notification.get() },
		specific_user_data_requests{},
		user_data{}
	{ }

	UserImpl::~UserImpl()
	{
	}

	bool UserImpl::SignedIn() {
		return intf->config->GetSignedIn();
	}

	GalaxyID UserImpl::GetGalaxyID() {
		return intf->config->GetCustomGalaxyID();
	}

	void UserImpl::SignIn(IAuthListener* const listener) {
		if (intf->config->GetSignedIn()) {
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
		if (intf->config->IsSelfUserID(userID)) {
			listeners->NotifyAll(listener, &ISpecificUserDataListener::OnSpecificUserDataUpdated, userID);
			listeners->NotifyAll<IUserDataListener>(&IUserDataListener::OnUserDataUpdated);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

			specific_user_data_requests.emplace(request_id, listener);
			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ request_id, userID });
		}
	}

	void UserImpl::SpecificUserDataRequestProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		ISpecificUserDataListener* listener = specific_user_data_requests.pop(data->request_id);

		if (data->found) {
			auto entry = GetGalaxyUserData(data->id);
			entry->stats = data->asuc;

			listeners->NotifyAll(listener, &ISpecificUserDataListener::OnSpecificUserDataUpdated, data->id);
		}
		else {
			listeners->NotifyAll(listener, &ISpecificUserDataListener::OnSpecificUserDataUpdated, data->id);
		}
	}

	bool UserImpl::IsUserDataAvailable(GalaxyID userID) {
		if (intf->config->IsSelfUserID(userID)) {
			return true;
		}
		else {
			auto entry = GetGalaxyUserData(userID);
			return !entry->stats.UserData.empty();
		}
	}

	const char* UserImpl::GetUserData(const char* key, GalaxyID userID) {
		if (intf->config->IsSelfUserID(userID)) {
			return intf->config->GetUserData(key).c_str();
		}
		else {
			auto entry = GetGalaxyUserData(userID);
			const char* ret = "";
			entry->stats.run_locked_userdata([&](AchievementsAndStatsContainer::map_t<std::string>& map) {
				auto it = map.find(key);
				if (it != map.end()) {
					ret = it->second.c_str();
				}
				});

			return ret;
		}
	}

	void UserImpl::GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		if (intf->config->IsSelfUserID(userID)) {
			const std::string& str = intf->config->GetUserData(key);
			std::copy_n(str.begin(), std::min((uint32_t)str.length(), bufferLength), buffer);
		}
		else {
			auto entry = GetGalaxyUserData(userID);
			entry->stats.run_locked_userdata([&](AchievementsAndStatsContainer::map_t<std::string>& map) {
				auto it = map.find(key);
				if (it != map.end()) {
					const std::string& str = it->second;
					std::copy_n(str.begin(), std::min((uint32_t)str.length(), bufferLength), buffer);
				}
				});
		}
	}

	void UserImpl::SetUserData(const char* key, const char* value, ISpecificUserDataListener* const listener) {
		intf->config->SetUserData(key, value);
		intf->config->SaveStatsAndAchievements();

		listeners->NotifyAll(listener, &ISpecificUserDataListener::OnSpecificUserDataUpdated, intf->config->GetApiGalaxyID());
		listeners->NotifyAll<IUserDataListener>(&IUserDataListener::OnUserDataUpdated);
	}

	uint32_t UserImpl::GetUserDataCount(GalaxyID userID) {
		if (intf->config->IsSelfUserID(userID)) {
			return (uint32_t)intf->config->GetASUC().UserData.size();
		}
		else {
			auto entry = GetGalaxyUserData(userID);
			return (uint32_t)entry->stats.UserData.size();
		}
	}

	bool UserImpl::GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
		if (intf->config->IsSelfUserID(userID)) {
			auto& map = intf->config->GetASUC().UserData;
			if (map.size() < index) {
				return false;
			}
			auto ref = container_get_by_index(map, index);
			std::copy_n(ref.first.begin(), std::min((uint32_t)ref.first.length(), keyLength), key);
			std::copy_n(ref.second.begin(), std::min((uint32_t)ref.second.length(), valueLength), value);
			return true;
		}
		else {
			bool ret = false;
			auto entry = GetGalaxyUserData(userID);
			entry->stats.run_locked_userdata([&](AchievementsAndStatsContainer::map_t<std::string>& map) {
				if (map.size() < index) {
					ret = false;
					return;
				}
				ret = true;

				auto ref = container_get_by_index(map, index);
				std::copy_n(ref.first.begin(), std::min((uint32_t)ref.first.length(), keyLength), key);
				std::copy_n(ref.second.begin(), std::min((uint32_t)ref.second.length(), valueLength), value);
				});
			return ret;
		}
	}

	void UserImpl::DeleteUserData(const char* key, ISpecificUserDataListener* const listener) {
		SetUserData(key, "", listener);
	}

	bool UserImpl::IsLoggedOn() {
		return intf->config->GetSignedIn();
	}

	void UserImpl::RequestEncryptedAppTicket(const void* data, uint32_t dataSize, IEncryptedAppTicketListener* const listener) {
		listeners->NotifyAll(listener, &IEncryptedAppTicketListener::OnEncryptedAppTicketRetrieveSuccess);
	}

	void UserImpl::GetEncryptedAppTicket(void* encryptedAppTicket, uint32_t maxEncryptedAppTicketSize, uint32_t& currentEncryptedAppTicketSize) {
		((char*)encryptedAppTicket)[maxEncryptedAppTicketSize - 1] = 0;
		currentEncryptedAppTicketSize = maxEncryptedAppTicketSize;
	}

	SessionID UserImpl::GetSessionID() {
		return (uint64_t)this;
	}

	const char* UserImpl::GetAccessToken() {
		return "95959595959595959595959595";
	}

	void UserImpl::GetAccessTokenCopy(char* buffer, uint32_t bufferLength) {
		std::copy_n(GetAccessToken(), std::min((uint32_t)strlen(GetAccessToken()), bufferLength), buffer);
	}

	bool UserImpl::ReportInvalidAccessToken(const char* accessToken, const char* info) {
		listeners->NotifyAll<IAccessTokenListener>(&IAccessTokenListener::OnAccessTokenChanged);
		return true;
	}

	std::shared_ptr<GalaxyUserData> UserImpl::GetGalaxyUserData(GalaxyID userID)
	{
		lock_t lock(mtx_user_data);
		return user_data.emplace(userID, std::make_shared<GalaxyUserData>(userID)).first->second;
	}
}
