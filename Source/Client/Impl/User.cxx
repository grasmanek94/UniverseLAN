#include "User.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>
#include <SafeStringCopy.hxx>

namespace universelan::client {
	using namespace galaxy::api;

#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
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
		tracer::Trace trace { nullptr, __FUNCTION__ };

		// add local user
		user_data.emplace(intf->config->GetApiGalaxyID(), intf->config->GetLocalUserData());
		user_data.emplace(GalaxyID(0), intf->config->GetLocalUserData());
		user_data.emplace(GalaxyID(static_cast<uint64_t>(galaxy::api::IDType::ID_TYPE_USER) << 56), intf->config->GetLocalUserData());

		if (intf->config->GetSignedIn()) {
			listeners->NotifyAll(&IAuthListener::OnAuthSuccess);
			listeners->NotifyAll(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_LOGGED_ON);
		}
	}

	UserImpl::~UserImpl()
	{
		tracer::Trace trace { nullptr, __FUNCTION__ };
	}

	bool UserImpl::SignedIn() {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		return intf->config->GetSignedIn();
	}

	GalaxyID UserImpl::GetGalaxyID() {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		return intf->config->GetCustomGalaxyID();
	}

	void UserImpl::SignIn(IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		if (intf->config->GetSignedIn()) {
			listeners->NotifyAll(listener, &IAuthListener::OnAuthSuccess);
			listeners->NotifyAll(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_LOGGED_ON);
		}
		else {
			listeners->NotifyAll(listener, &IAuthListener::OnAuthFailure, IAuthListener::FAILURE_REASON_GALAXY_SERVICE_NOT_AVAILABLE);
			listeners->NotifyAll(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN);
		}
	}

	void UserImpl::USER_SIGN_IN_STEAM(const void* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}

	void UserImpl::USER_SIGN_IN_CREDENTIALS(const char* login, const char* password
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}

	void UserImpl::USER_SIGN_IN_GALAXY(bool requireOnline
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}

	void UserImpl::USER_SIGN_IN_SERVER_KEY(const char* serverKey
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API
	void UserImpl::SignInAnonymous(
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}
#endif

#if GALAXY_BUILD_FEATURE_USER_SIGNIN_CROSSPLATFORM
	void UserImpl::SignInToken(const char* refreshToken, IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		SignIn(listener);
	}

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINLAUNCHER
	void UserImpl::SignInLauncher(IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		SignIn(listener);
	}
#endif

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINEPIC
	void UserImpl::SignInEpic(const char* epicAccessToken, const char* epicUsername, IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__ };
		if (epicAccessToken != nullptr && epicUsername != nullptr) {
			SignIn(listener);
		}
	}
#endif

	void UserImpl::SignInUWP(IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		SignIn(listener);
	}

	void UserImpl::SignInPS4(const char* ps4ClientID, IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		if (ps4ClientID != nullptr) {
			SignIn(listener);
		}
	}

	void UserImpl::SignInXB1(const char* xboxOneUserID, IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		if (xboxOneUserID != nullptr) {
			SignIn(listener);
		}
	}

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINXBLIVE
	void UserImpl::SignInXBLive(const char* token, const char* signature, const char* marketplaceID, const char* locale, IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		if (token != nullptr && signature != nullptr && marketplaceID != nullptr && locale != nullptr) {
			SignIn(listener);
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_ITELEMETRY_1_139_6_UPDATE
	void UserImpl::SignInAnonymousTelemetry(IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		SignIn(listener);
	}
#endif

#else

	void UserImpl::SignIn(uint32_t xboxOneUserID
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		SignIn(GET_LISTENER(listener));
	}

	void UserImpl::SignIn(const char* ps4ClientID, const char* ps4TitleID, const char* ps4TitleSecret, uint32_t ps4TitleSecretLength
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		if (ps4ClientID != nullptr && ps4TitleID != nullptr && ps4TitleSecret != nullptr) {
			SignIn(GET_LISTENER(listener));
		}
	}
#endif


#if GALAXY_BUILD_FEATURE_USER_SIGNIN_CROSSPLATFORM

	void UserImpl::SignOut() {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		listeners->NotifyAll(&IAuthListener::OnAuthLost);
		listeners->NotifyAll(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN);
	}
#endif

	void UserImpl::RequestUserData(GalaxyID userID
#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
				listener,
#endif
				&ISpecificUserDataListener::OnSpecificUserDataUpdated, userID);
			listeners->NotifyAll(&IUserDataListener::OnUserDataUpdated);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
			specific_user_data_requests.emplace(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeUserData, request_id, userID });
		}
	}

	void UserImpl::SpecificUserDataRequestProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

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

#if GALAXY_BUILD_FEATURE_HAS_USERDATAINFOAVAILABLE
	bool UserImpl::IsUserDataAvailable(GalaxyID userID) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		if (intf->config->IsSelfUserID(userID)) {
			return true;
		}

		return GetGalaxyUserData(userID)->stats.IsUserDataAvailable();
	}
#endif

	const char* UserImpl::GetUserData(const char* key, GalaxyID userID) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		return GetGalaxyUserData(userID)->stats.GetUserData(key).c_str();
	}

	void UserImpl::GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		const std::string& str = GetGalaxyUserData(userID)->stats.GetUserData(key);
		universelan::util::safe_copy_str_n(str, buffer, bufferLength);
	}

	void UserImpl::SetUserData(const char* key, const char* value
#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		intf->config->GetLocalUserData()->stats.SetUserData(key, value);
		intf->config->SaveStatsAndAchievements();

		intf->client->GetConnection().SendAsync(SetUserDataMessage{ intf->config->GetApiGalaxyID(), key, value });

/*		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
			listener,
#endif
			&ISpecificUserDataListener::OnSpecificUserDataUpdated, intf->config->GetApiGalaxyID());*/
		listeners->NotifyAll(&IUserDataListener::OnUserDataUpdated);
	}

	uint32_t UserImpl::GetUserDataCount(GalaxyID userID) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		auto entry = GetGalaxyUserData(userID);
		return entry->stats.run_locked_userdata<uint32_t>([&](auto& map) -> uint32_t {
			return (uint32_t)map.size();
			});
	}

	bool UserImpl::GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		auto entry = GetGalaxyUserData(userID);
		return entry->stats.run_locked_userdata<bool>([&](auto& map) -> bool {
			if (map.size() < index) {
				return false;
			}

			auto ref = container_get_by_index(map, index);
			universelan::util::safe_copy_str_n(ref.first, key, keyLength);
			universelan::util::safe_copy_str_n(ref.second, value, valueLength);

			return true;
			});
	}

	void UserImpl::DeleteUserData(const char* key
#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		SetUserData(key, ""
#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
			, listener
#endif
		);
	}

	bool UserImpl::IsLoggedOn() {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		return intf->config->GetSignedIn();
	}

#if GALAXY_BUILD_FEATURE_ENCRYPTED_APP_TICKET
	void UserImpl::RequestEncryptedAppTicket(RequestEncryptedAppTicketDataT* data, uint32_t dataSize
#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
		, IEncryptedAppTicketListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
			listener,
#endif
			&IEncryptedAppTicketListener::OnEncryptedAppTicketRetrieveSuccess);
	}

	void UserImpl::GetEncryptedAppTicket(void* encryptedAppTicket, uint32_t maxEncryptedAppTicketSize, uint32_t& currentEncryptedAppTicketSize) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		((char*)encryptedAppTicket)[maxEncryptedAppTicketSize - 1] = 0;
		currentEncryptedAppTicketSize = maxEncryptedAppTicketSize;
	}
#endif

	SessionID UserImpl::GetSessionID() {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		return (uint64_t)this;
	}

	const char* UserImpl::GetAccessToken() {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		return "95959595959595959595959595";
	}

	void UserImpl::GetAccessTokenCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		universelan::util::safe_copy_str_n(GetAccessToken(), buffer, bufferLength);
	}

	bool UserImpl::ReportInvalidAccessToken(const char* accessToken
#if GALAXY_BUILD_FEATURE_USER_ACCESS_TOKEN_INFO
		, const char* info
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		listeners->NotifyAll(&IAccessTokenListener::OnAccessTokenChanged);
		return true;
	}

	void UserImpl::OnlineUserStateChange(const std::shared_ptr<OnlineStatusChangeMessage>& data) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

		GetGalaxyUserData(data->id)->online = data->online;
	}

	void UserImpl::SetUserDataMessageReceived(const std::shared_ptr<SetUserDataMessage>& data) {
		GetGalaxyUserData(data->id)->stats.SetUserData(data->key, data->value);
	}

	GalaxyUserData::ptr_t UserImpl::GetGalaxyUserData(GalaxyID userID) {
		tracer::Trace trace { nullptr, __FUNCTION__ };

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
		tracer::Trace trace { nullptr, __FUNCTION__ };

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
