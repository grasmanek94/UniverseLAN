#include "User.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>

namespace universelan::client {
	using namespace galaxy::api;

#if GALAXY_VERSION_LISTENER_TO_FUNCTION_SIGNATURES_ADDED
#define GET_LISTENER(listener) (listener)
#else
#define GET_LISTENER(listener) ((IAuthListener* const)nullptr)
#endif

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
		user_data.emplace(GalaxyID(static_cast<uint64_t>(GalaxyID::ID_TYPE_USER) << 56), intf->config->GetLocalUserData());

		if (intf->config->GetSignedIn()) {
			listeners->NotifyAll(&IAuthListener::OnAuthSuccess);
			listeners->NotifyAll(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_LOGGED_ON);
		}
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

	void UserImpl::USER_SIGN_IN_STEAM(const void* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName
#if GALAXY_VERSION_LISTENER_TO_FUNCTION_SIGNATURES_ADDED
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}

	void UserImpl::USER_SIGN_IN_CREDENTIALS(const char* login, const char* password
#if GALAXY_VERSION_LISTENER_TO_FUNCTION_SIGNATURES_ADDED
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}

	void UserImpl::USER_SIGN_IN_GALAXY(bool requireOnline
#if GALAXY_VERSION_LISTENER_TO_FUNCTION_SIGNATURES_ADDED
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}

	void UserImpl::USER_SIGN_IN_SERVER_KEY(const char* serverKey
#if GALAXY_VERSION_LISTENER_TO_FUNCTION_SIGNATURES_ADDED
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}

	void UserImpl::SignInAnonymous(
#if GALAXY_VERSION_LISTENER_TO_FUNCTION_SIGNATURES_ADDED
		IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}

#if GALAXY_VERSION_NEW_SIGN_IN_FUNCTIONS_ADDED
	void UserImpl::SignInToken(const char* refreshToken, IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInLauncher(IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInEpic(const char* epicAccessToken, const char* epicUsername, IAuthListener* const listener) {
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

	void UserImpl::SignInAnonymousTelemetry(IAuthListener* const listener) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(listener);
	}
#else

	void UserImpl::SignIn(uint32_t xboxOneUserID
#if GALAXY_VERSION_LISTENER_TO_FUNCTION_SIGNATURES_ADDED
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}

	void UserImpl::SignIn(const char* ps4ClientID, const char* ps4TitleID, const char* ps4TitleSecret, uint32_t ps4TitleSecretLength
#if GALAXY_VERSION_LISTENER_TO_FUNCTION_SIGNATURES_ADDED
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}
#endif


#if GALAXY_VERSION_NEW_SIGN_IN_FUNCTIONS_ADDED

	void UserImpl::SignOut() {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(&IAuthListener::OnAuthLost);
		listeners->NotifyAll(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN);
	}
#endif

	void UserImpl::RequestUserData(GalaxyID userID
#if GALAXY_VERSION_LISTENER_TO_USERDATA_FUNCTION_SIGNATURES_ADDED
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
			listeners->NotifyAll(
#if GALAXY_VERSION_LISTENER_TO_USERDATA_FUNCTION_SIGNATURES_ADDED
				listener,
#endif
				&ISpecificUserDataListener::OnSpecificUserDataUpdated, userID);
			listeners->NotifyAll(&IUserDataListener::OnUserDataUpdated);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

#if GALAXY_VERSION_LISTENER_TO_USERDATA_FUNCTION_SIGNATURES_ADDED
			specific_user_data_requests.emplace(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeUserData, request_id, userID });
		}
	}

	void UserImpl::SpecificUserDataRequestProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		ISpecificUserDataListener* listener = specific_user_data_requests.pop(data->request_id);

		if (data->found) {
			auto entry = GetGalaxyUserData(data->id);
			entry->stats = data->asuc;
			entry->nickname = data->nickname;

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

		return GetGalaxyUserData(userID)->stats.IsUserDataAvailable();
	}

	const char* UserImpl::GetUserData(const char* key, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		return GetGalaxyUserData(userID)->stats.GetUserData(key).c_str();
	}

	void UserImpl::GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace{ __FUNCTION__ };

		const std::string& str = GetGalaxyUserData(userID)->stats.GetUserData(key);
		std::copy_n(str.begin(), std::min((uint32_t)str.length(), bufferLength), buffer);
	}

	void UserImpl::SetUserData(const char* key, const char* value
#if GALAXY_VERSION_LISTENER_TO_USERDATA_FUNCTION_SIGNATURES_ADDED
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		intf->config->GetLocalUserData()->stats.SetUserData(key, value);
		intf->config->SaveStatsAndAchievements();

		intf->client->GetConnection().SendAsync(SetUserDataMessage{ intf->config->GetApiGalaxyID(), key, value });

		listeners->NotifyAll(
#if GALAXY_VERSION_LISTENER_TO_USERDATA_FUNCTION_SIGNATURES_ADDED
			listener,
#endif
			&ISpecificUserDataListener::OnSpecificUserDataUpdated, intf->config->GetApiGalaxyID());
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

	void UserImpl::DeleteUserData(const char* key
#if GALAXY_VERSION_LISTENER_TO_USERDATA_FUNCTION_SIGNATURES_ADDED
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		SetUserData(key, ""
#if GALAXY_VERSION_LISTENER_TO_USERDATA_FUNCTION_SIGNATURES_ADDED
			, listener
#endif
		);
	}

	bool UserImpl::IsLoggedOn() {
		tracer::Trace trace{ __FUNCTION__ };

		return intf->config->GetSignedIn();
	}

	void UserImpl::RequestEncryptedAppTicket(const void* data, uint32_t dataSize
#if GALAXY_VERSION_LISTENER_TO_USERDATA_FUNCTION_SIGNATURES_ADDED
		, IEncryptedAppTicketListener* const listener
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(
#if GALAXY_VERSION_LISTENER_TO_USERDATA_FUNCTION_SIGNATURES_ADDED
			listener,
#endif
			&IEncryptedAppTicketListener::OnEncryptedAppTicketRetrieveSuccess);
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

	bool UserImpl::ReportInvalidAccessToken(const char* accessToken
#if GALAXY_VERSION_INVALID_ACCESS_TOKEN_INFO_ADDED
		, const char* info
#endif
	) {
		tracer::Trace trace{ __FUNCTION__ };

		listeners->NotifyAll(&IAccessTokenListener::OnAccessTokenChanged);
		return true;
	}

	void UserImpl::OnlineUserStateChange(const std::shared_ptr<OnlineStatusChangeMessage>& data) {
		tracer::Trace trace{ __FUNCTION__ };

		GetGalaxyUserData(data->id)->online = data->online;
	}

	void UserImpl::SetUserDataMessageReceived(const std::shared_ptr<SetUserDataMessage>& data) {
		GetGalaxyUserData(data->id)->stats.SetUserData(data->key, data->value);
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
