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
	{
		tracer::Trace trace{ __FUNCTION__ };

		// add local user
		user_data.emplace(intf->config->GetApiGalaxyID(), intf->config->GetLocalUserData());
		user_data.emplace(GalaxyID(0), intf->config->GetLocalUserData());
		user_data.emplace(GalaxyID::FromRealID(GalaxyID::ID_TYPE_USER, 0), intf->config->GetLocalUserData());
	}

	UserImpl::~UserImpl()
	{
		tracer::Trace trace{ __FUNCTION__ };
	}

	bool UserImpl::SignedIn() {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->config->GetSignedIn();
	}

	GalaxyID UserImpl::GetGalaxyID() {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->config->GetCustomGalaxyID();
	}

	void UserImpl::SignIn(IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->GetSignedIn()) {
			listeners->NotifyAll(listener, &IAuthListener::OnAuthSuccess);
			listeners->NotifyAll(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_LOGGED_ON);
		}
		else {
			listeners->NotifyAll(listener, &IAuthListener::OnAuthFailure, IAuthListener::FAILURE_REASON_EXTERNAL_SERVICE_FAILURE);
			listeners->NotifyAll(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN);
		}
	}

	void UserImpl::SignInCredentials(const char* login, const char* password, IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInToken(const char* refreshToken, IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInLauncher(IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInSteam(const void* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName, IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInEpic(const char* epicAccessToken, const char* epicUsername, IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInGalaxy(bool requireOnline, IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInUWP(IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInPS4(const char* ps4ClientID, IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInXB1(const char* xboxOneUserID, IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInXBLive(const char* token, const char* signature, const char* marketplaceID, const char* locale, IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInAnonymous(IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInAnonymousTelemetry(IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInServerKey(const char* serverKey, IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignOut() {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(&IAuthListener::OnAuthLost);
		listeners->NotifyAll(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN);
	}

	void UserImpl::RequestUserData(GalaxyID userID, ISpecificUserDataListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
			listeners->NotifyAll(listener, &ISpecificUserDataListener::OnSpecificUserDataUpdated, userID);
			listeners->NotifyAll(&IUserDataListener::OnUserDataUpdated);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

			specific_user_data_requests.emplace(request_id, listener);
			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeUserData, request_id, userID });
		}
	}

	void UserImpl::SpecificUserDataRequestProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

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
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
			return true;
		}

		auto entry = GetGalaxyUserData(userID);
		return entry->stats.run_locked_userdata<bool>([&](auto& map) -> bool {
			return !map.empty();
			});
	}

	const char* UserImpl::GetUserData(const char* key, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		auto entry = GetGalaxyUserData(userID);
		return entry->stats.run_locked_userdata<const char*>([&](auto& map) -> const char* {
			auto it = map.find(key);
			if (it != map.end()) {
				return it->second.c_str();
			}
			return "";
			});
	}

	void UserImpl::GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		auto entry = GetGalaxyUserData(userID);
		entry->stats.run_locked_userdata<void>([&](auto& map) {
			auto it = map.find(key);
			if (it != map.end()) {
				const std::string& str = it->second;
				std::copy_n(str.begin(), std::min((uint32_t)str.length(), bufferLength), buffer);
			}
			});
	}

	void UserImpl::SetUserData(const char* key, const char* value, ISpecificUserDataListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->SetUserData(key, value);
		intf->config->SaveStatsAndAchievements();

		intf->client->GetConnection().SendAsync(SetUserDataMessage{ intf->config->GetApiGalaxyID(), key, value });

		listeners->NotifyAll(listener, &ISpecificUserDataListener::OnSpecificUserDataUpdated, intf->config->GetApiGalaxyID());
		listeners->NotifyAll(&IUserDataListener::OnUserDataUpdated);
	}

	uint32_t UserImpl::GetUserDataCount(GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		auto entry = GetGalaxyUserData(userID);
		return entry->stats.run_locked_userdata<uint32_t>([&](auto& map) -> uint32_t {
			return (uint32_t)map.size();
			});
	}

	bool UserImpl::GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		auto entry = GetGalaxyUserData(userID);
		return entry->stats.run_locked_userdata<bool>([&](auto& map) -> bool {
			if (map.size() < index) {
				return false;
			}

			auto ref = container_get_by_index(map, index);
			std::copy_n(ref.first.begin(), std::min((uint32_t)ref.first.length(), keyLength), key);
			std::copy_n(ref.second.begin(), std::min((uint32_t)ref.second.length(), valueLength), value);
			return true;
			});
	}

	void UserImpl::DeleteUserData(const char* key, ISpecificUserDataListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SetUserData(key, "", listener);
	}

	bool UserImpl::IsLoggedOn() {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->config->GetSignedIn();
	}

	void UserImpl::RequestEncryptedAppTicket(const void* data, uint32_t dataSize, IEncryptedAppTicketListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(listener, &IEncryptedAppTicketListener::OnEncryptedAppTicketRetrieveSuccess);
	}

	void UserImpl::GetEncryptedAppTicket(void* encryptedAppTicket, uint32_t maxEncryptedAppTicketSize, uint32_t& currentEncryptedAppTicketSize) {
		tracer::Trace trace{ __FUNCTION__ };

		((char*)encryptedAppTicket)[maxEncryptedAppTicketSize - 1] = 0;
		currentEncryptedAppTicketSize = maxEncryptedAppTicketSize;
	}

	SessionID UserImpl::GetSessionID() {
		tracer::Trace trace{ __FUNCTION__ };

		return (uint64_t)this;
	}

	const char* UserImpl::GetAccessToken() {
		tracer::Trace trace{ __FUNCTION__ };

		return "95959595959595959595959595";
	}

	void UserImpl::GetAccessTokenCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ __FUNCTION__ };

		std::copy_n(GetAccessToken(), std::min((uint32_t)strlen(GetAccessToken()), bufferLength), buffer);
	}

	bool UserImpl::ReportInvalidAccessToken(const char* accessToken, const char* info) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(&IAccessTokenListener::OnAccessTokenChanged);
		return true;
	}

	void UserImpl::OnlineUserStateChange(const std::shared_ptr<OnlineStatusChangeMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		GetGalaxyUserData(data->id)->online = data->online;
	}

	void UserImpl::SetUserDataMessageReceived(const std::shared_ptr<SetUserDataMessage>& data) {
		GetGalaxyUserData(data->id)->stats.run_locked_userdata<void>([&](auto& UserData) {
			auto emplace = UserData.emplace(data->key, data->value);
			if (!emplace.second) {
				emplace.first->second = data->value;
			}
			});
	}

	GalaxyUserData::ptr_t UserImpl::GetGalaxyUserData(GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
			return intf->config->GetLocalUserData();
		}

		lock_t lock(mtx_user_data);
		auto user = user_data.find(userID);
		if (user == user_data.end()) {
			user = user_data.emplace(userID, std::make_shared<GalaxyUserData>(userID)).first;
		}

		return user->second;
	}

	bool UserImpl::IsGalaxyUserDataPresent(GalaxyID userID) const {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
			return true;
		}

		lock_t lock(mtx_user_data);
		auto user = user_data.find(userID);
		if (user != user_data.end()) {
			return true;
		}

		return false;
	}
}
