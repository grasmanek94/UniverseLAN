#include "User.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>
#include <SafeStringCopy.hxx>

#include <boost/preprocessor/control/if.hpp>
#include <string>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const std::string SOME_TOKEN_STRING{ "dGhpcyBpcyBhbiBlbmNyeXB0ZWQgYXBwIHRpY2tldCBmb3IgVW5pdmVyc2VMQU4gbG9jYXRlZCBpbiBVc2VyLmN4eCBpbnNpZGUgdm9pZCBVc2VySW1wbDo6R2V0RW5jcnlwdGVkQXBwVGlja2V0KHZvaWQqIGVuY3J5cHRlZEFwcFRpY2tldCwgdWludDMyX3QgbWF4RW5jcnlwdGVkQXBwVGlja2V0U2l6ZSwgdWludDMyX3QmIGN1cnJlbnRFbmNyeXB0ZWRBcHBUaWNrZXRTaXplKQ==" };
	}

#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
#define GET_LISTENER(listener) (listener)
#else
#define GET_LISTENER(listener) ((IAuthListener* const)nullptr)
#endif

	UserImpl::UserImpl(InterfaceInstances* intf) :
		mtx_user_data{}, intf{ intf },
		listeners{ intf->notification.get() },
		user_data{}, logged_on{ false }, connected{ false },
		waiting_auth_listeners{}
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		// add local user
		user_data.emplace(intf->config->GetApiGalaxyID(), intf->config->GetLocalUserData());
		user_data.emplace(GalaxyID(0), intf->config->GetLocalUserData());
		user_data.emplace(GalaxyID(static_cast<uint64_t>(galaxy::api::IDType::ID_TYPE_USER) << 56), intf->config->GetLocalUserData());
	}

	UserImpl::~UserImpl()
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };
	}

	bool UserImpl::SignedIn() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		return intf->config->GetSignedIn();
	}

	GalaxyID UserImpl::GetGalaxyID() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER | tracer::Trace::HIGH_FREQUENCY_CALLS };

		return intf->config->GetApiGalaxyID();
	}

	void UserImpl::SignIn(IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		if (intf->config->GetSignedIn()) {
			if (logged_on) {
#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
				listeners->NotifyAll(&IAccessTokenListener::OnAccessTokenChanged);
#endif
				listeners->NotifyAll(listener, &IAuthListener::OnAuthSuccess);
#if GALAXY_BUILD_FEATURE_HAS_OPERATIONALSTATECHANGELISTENER
				listeners->NotifyAll(&IOperationalStateChangeListener::OnOperationalStateChanged, (IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN | IOperationalStateChangeListener::OPERATIONAL_STATE_LOGGED_ON));
#endif
#if GALAXY_BUILD_FEATURE_HAS_IFRIENDS_ONPERSONADATACHANGED
				listeners->NotifyAll(&IPersonaDataChangedListener::OnPersonaDataChanged, intf->user->GetGalaxyID(), IPersonaDataChangedListener::PERSONA_CHANGE_NONE);
#endif
#if GALAXY_BUILD_FEATURE_HAS_IFRIENDLISTLISTENER	
				listeners->NotifyAll(&IFriendListListener::OnFriendListRetrieveSuccess);
#endif
			}
			else if (listener != nullptr) {
				lock_t lock{ mtx_waiting_auth_listeners };
				waiting_auth_listeners.insert(listener);
			}
		}
		else {
			listeners->NotifyAll(listener, &IAuthListener::OnAuthFailure, IAuthListener::FAILURE_REASON_GALAXY_SERVICE_NOT_AVAILABLE);
#if GALAXY_BUILD_FEATURE_HAS_OPERATIONALSTATECHANGELISTENER
			listeners->NotifyAll(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN);
#endif
		}
	}

	void UserImpl::USER_SIGN_IN_STEAM(const SignInDataPtr_T* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		SignIn(GET_LISTENER(listener));
	}

	void UserImpl::USER_SIGN_IN_CREDENTIALS(const char* login, const char* password
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		SignIn(GET_LISTENER(listener));
	}

	void UserImpl::USER_SIGN_IN_GALAXY(
#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_REQUIREONLINE
		bool requireOnline
#endif
#if GALAXY_BUILD_FEATURE_HAS_IUSER_SIGNINGALAXY_TIMEOUT
		, uint32_t timeout
#endif
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		SignIn(GET_LISTENER(listener));
	}

#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_WITH_SERVERKEY
	void UserImpl::USER_SIGN_IN_SERVER_KEY(const char* serverKey
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		SignIn(GET_LISTENER(listener));
	}
#endif

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API
	void UserImpl::SignInAnonymous(
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		SignIn(GET_LISTENER(listener));
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNINTOKEN
	void UserImpl::SignInToken(const char* refreshToken, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		SignIn(listener);
	}
#endif

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINLAUNCHER
	void UserImpl::SignInLauncher(IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		SignIn(listener);
	}
#endif

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINEPIC
	void UserImpl::SignInEpic(const char* epicAccessToken, const char* epicUsername, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };
		if (epicAccessToken != nullptr && epicUsername != nullptr) {
			SignIn(listener);
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_IUSER_UWP_TO_XBOX_RENAME
	void UserImpl::SignInXbox(uint64_t xboxID, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		SignIn(listener);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNINUWP
	void UserImpl::SignInUWP(IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		SignIn(listener);
	}
#endif

#if GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINPS4
	void UserImpl::USER_SIGN_IN_PS4(const char* ps4ClientID, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		if (ps4ClientID != nullptr) {
			SignIn(listener);
		}
	}

#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNINXB1
	void UserImpl::SignInXB1(const char* xboxOneUserID, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		if (xboxOneUserID != nullptr) {
			SignIn(listener);
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINXBLIVE
	void UserImpl::SignInXBLive(const char* token, const char* signature, const char* marketplaceID, const char* locale, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		if (token != nullptr && signature != nullptr && marketplaceID != nullptr && locale != nullptr) {
			SignIn(listener);
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_ITELEMETRY_1_139_6_UPDATE
	void UserImpl::SignInAnonymousTelemetry(IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		SignIn(listener);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_CLASSIC_XBOX
	void UserImpl::SignIn(uint32_t xboxOneUserID
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		SignIn(GET_LISTENER(listener));
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_PS4
	void UserImpl::SignIn(const char* ps4ClientID, const char* ps4TitleID, const char* ps4TitleSecret, uint32_t ps4TitleSecretLength
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		if (ps4ClientID != nullptr && ps4TitleID != nullptr && ps4TitleSecret != nullptr) {
			SignIn(GET_LISTENER(listener));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNOUT
	void UserImpl::SignOut() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		listeners->NotifyAll(&IAuthListener::OnAuthLost);
		listeners->NotifyAll(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN);
	}
#endif

	void UserImpl::RequestUserData(
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		GalaxyID userID
#endif
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

#if !GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		GalaxyID userID = intf->config->GetApiGalaxyID();
#endif

		if (intf->config->IsSelfUserID(userID)) {
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
				listener,
#endif
				& ISpecificUserDataListener::OnSpecificUserDataUpdated, userID);
#endif
			listeners->NotifyAll(&IUserDataListener::OnUserDataUpdated);
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
			listeners->AddRequestListener(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeUserData, request_id, userID });
		}
	}

	void UserImpl::SpecificUserDataRequestProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
		ISpecificUserDataListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
#endif

		if (data->found) {
			auto entry = GetGalaxyUserData(data->id);
			entry->stats = data->asuc;
			if (entry->nickname != data->nickname) {
				entry->nickname = data->nickname;
			}
		}

#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
		listeners->NotifyAllNow(listener, &ISpecificUserDataListener::OnSpecificUserDataUpdated, data->id);
#endif
		if (intf->config->IsSelfUserID(data->id)) {
			listeners->NotifyAllNow(&IUserDataListener::OnUserDataUpdated);
		}
	}

#if GALAXY_BUILD_FEATURE_HAS_USERDATAINFOAVAILABLE
	bool UserImpl::IsUserDataAvailable(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		if (intf->config->IsSelfUserID(userID)) {
			return true;
		}

		return GetGalaxyUserData(userID)->stats.IsUserDataAvailable();
	}
#endif

	const char* UserImpl::GetUserData(const char* key
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		, GalaxyID userID
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

#if !GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		GalaxyID userID = intf->config->GetApiGalaxyID();
#endif

		return GetGalaxyUserData(userID)->stats.GetUserData(key).c_str();
	}

#if GALAXY_BUILD_FEATURE_IUSER_GET_DATA_ACCESSTOKEN_COPY
	void UserImpl::GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		, GalaxyID userID
#endif	
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		GalaxyID id = BOOST_PP_IF(GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER, userID, 0);
		const std::string& str = GetGalaxyUserData(id)->stats.GetUserData(key);
		universelan::util::safe_copy_str_n(str, buffer, bufferLength);
	}
#endif

	void UserImpl::SetUserData(const char* key, const char* value
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		intf->config->GetLocalUserData()->stats.SetUserData(key, value);
		intf->config->SaveStatsAndAchievements();

		intf->client->GetConnection().SendAsync(SetUserDataMessage{ intf->config->GetApiGalaxyID(), key, value });

#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
			listener,
#endif
			& ISpecificUserDataListener::OnSpecificUserDataUpdated, intf->config->GetApiGalaxyID());
#endif

		listeners->NotifyAll(&IUserDataListener::OnUserDataUpdated);
	}

	uint32_t UserImpl::GetUserDataCount(
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		GalaxyID userID
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

#if !GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		GalaxyID userID = intf->config->GetApiGalaxyID();
#endif

		auto entry = GetGalaxyUserData(userID);
		return entry->stats.run_locked_userdata<uint32_t>([&](auto& map) -> uint32_t {
			return (uint32_t)map.size();
			});
	}

	bool UserImpl::GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		, GalaxyID userID
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

#if !GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		GalaxyID userID = intf->config->GetApiGalaxyID();
#endif

		auto entry = GetGalaxyUserData(userID);
		return entry->stats.run_locked_userdata<bool>([&](auto& map) -> bool {
			auto ref = container_get_by_index(map, index);
			if (!ref) {
				return false;
			}

			universelan::util::safe_copy_str_n(ref->first, key, keyLength);
			universelan::util::safe_copy_str_n(ref->second, value, valueLength);

			return true;
			});
	}

	void UserImpl::DeleteUserData(const char* key
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		SetUserData(key, ""
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
			, listener
#endif
		);
	}

#if GALAXY_BUILD_FEATURE_IUSER_HAS_ISLOGGEDON
	bool UserImpl::IsLoggedOn() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER | tracer::Trace::HIGH_FREQUENCY_CALLS };

		return logged_on && SignedIn();
	}
#endif

#if GALAXY_BUILD_FEATURE_ENCRYPTED_APP_TICKET
	void UserImpl::RequestEncryptedAppTicket(RequestEncryptedAppTicketDataT* data, uint32_t dataSize
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
		, IEncryptedAppTicketListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
			listener,
#endif
			& IEncryptedAppTicketListener::OnEncryptedAppTicketRetrieveSuccess);
	}

	void UserImpl::GetEncryptedAppTicket(void* encryptedAppTicket, uint32_t maxEncryptedAppTicketSize, uint32_t& currentEncryptedAppTicketSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		currentEncryptedAppTicketSize = universelan::util::safe_copy_str_n(SOME_TOKEN_STRING, (char*)encryptedAppTicket, maxEncryptedAppTicketSize);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IOTHERSESSIONSTARTLISTENER
	SessionID UserImpl::GetSessionID() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		return (uint64_t)this;
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
	const char* UserImpl::GetAccessToken() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		return SOME_TOKEN_STRING.c_str();
	}

#if GALAXY_BUILD_FEATURE_IUSER_GET_DATA_ACCESSTOKEN_COPY
	void UserImpl::GetAccessTokenCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		universelan::util::safe_copy_str_n(SOME_TOKEN_STRING, buffer, bufferLength);
	}
#endif

	bool UserImpl::ReportInvalidAccessToken(const char* accessToken
#if GALAXY_BUILD_FEATURE_USER_ACCESS_TOKEN_INFO
		, const char* info
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		listeners->NotifyAll(&IAccessTokenListener::OnAccessTokenChanged);

		return true;
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSER_REFRESHTOKEN
	void UserImpl::GetRefreshTokenCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		universelan::util::safe_copy_str_n(SOME_TOKEN_STRING, buffer, bufferLength);
	}

	const char* UserImpl::GetRefreshToken() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		return SOME_TOKEN_STRING.c_str();
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSER_AUTHORIZATION_IDTOKEN
	void UserImpl::SignInAuthorizationCode(const char* authorizationCode, const char* redirectURI, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		if (authorizationCode != nullptr && redirectURI != nullptr && listener != nullptr) {
			SignIn(listener);
		}
	}

	const char* UserImpl::GetIDToken() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		return SOME_TOKEN_STRING.c_str();
	}

	void UserImpl::GetIDTokenCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		universelan::util::safe_copy_str_n(SOME_TOKEN_STRING, buffer, bufferLength);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSER_OPENID
	void UserImpl::CreateOpenIDConnection(const char* secretKey, const char* titleID, const char* connectionID,
		bool ignoreNonce, IPlayFabCreateOpenIDConnectionListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		listeners->NotifyAll(&IPlayFabCreateOpenIDConnectionListener::OnPlayFabCreateOpenIDConnectionFailure, 
			IPlayFabCreateOpenIDConnectionListener::FAILURE_REASON_CONNECTION_FAILURE);
	}

	void UserImpl::LoginWithOpenIDConnect(const char* titleID, const char* connectionID, const char* idToken,
		bool createAccount, const char* encryptedRequest, const char* playerSecret, IPlayFabLoginWithOpenIDConnectListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		listeners->NotifyAll(&IPlayFabLoginWithOpenIDConnectListener::OnPlayFabLoginWithOpenIDConnectFailure,
			IPlayFabLoginWithOpenIDConnectListener::FAILURE_REASON_CONNECTION_FAILURE);
	}
#endif

	void UserImpl::OnlineUserStateChange(const std::shared_ptr<OnlineStatusChangeMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		GetGalaxyUserData(data->id)->online = data->online;

		intf->friends->ChangeOnlineStatus(data->id, data->online);
	}

	void UserImpl::SetUserDataMessageReceived(const std::shared_ptr<SetUserDataMessage>& data) {
		GetGalaxyUserData(data->id)->stats.SetUserData(data->key, data->value);
	}

	GalaxyUserData::ptr_t UserImpl::GetGalaxyUserData(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

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
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

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

	void UserImpl::RunForAllWaitingAuthListeners(std::function<void(IGalaxyListener*)> function) {
		std::set<IGalaxyListener*> copy_waiting_auth_listeners;

		{
			lock_t lock{ mtx_waiting_auth_listeners };
			copy_waiting_auth_listeners = waiting_auth_listeners;
			waiting_auth_listeners.clear();
		}

		for (auto& listener : copy_waiting_auth_listeners) {
			function(listener);
		}
	}

	void UserImpl::ConnectionStateChangeReceived(bool connection_state, bool key_challenge_accepted) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

		logged_on = key_challenge_accepted;
		connected = connection_state;

		if (!SignedIn()) {
			RunForAllWaitingAuthListeners([&](IGalaxyListener* listener) {
				listeners->NotifyAllNowSpecificOnly(listener, &IAuthListener::OnAuthFailure, IAuthListener::FAILURE_REASON_GALAXY_SERVICE_NOT_AVAILABLE);
				});

			listeners->NotifyAllNow(&IAuthListener::OnAuthFailure, IAuthListener::FAILURE_REASON_GALAXY_SERVICE_NOT_AVAILABLE);
#if GALAXY_BUILD_FEATURE_HAS_OPERATIONALSTATECHANGELISTENER
			listeners->NotifyAllNow(&IOperationalStateChangeListener::OnOperationalStateChanged, IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN);
#endif
			return;
		}

		if (key_challenge_accepted) {
			// Connected & Can exchange messages
#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
			listeners->NotifyAllNow(&IAccessTokenListener::OnAccessTokenChanged);
#endif
			RunForAllWaitingAuthListeners([&](IGalaxyListener* listener) {
				listeners->NotifyAllNowSpecificOnly(listener, &IAuthListener::OnAuthSuccess);
				});

			listeners->NotifyAllNow(&IAuthListener::OnAuthSuccess);
#if GALAXY_BUILD_FEATURE_HAS_OPERATIONALSTATECHANGELISTENER
			listeners->NotifyAllNow(&IOperationalStateChangeListener::OnOperationalStateChanged, (IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN | IOperationalStateChangeListener::OPERATIONAL_STATE_LOGGED_ON));
#endif
#if GALAXY_BUILD_FEATURE_HAS_IFRIENDS_ONPERSONADATACHANGED
			listeners->NotifyAllNow(&IPersonaDataChangedListener::OnPersonaDataChanged, intf->user->GetGalaxyID(), IPersonaDataChangedListener::PERSONA_CHANGE_NONE);
#endif
#if GALAXY_BUILD_FEATURE_HAS_IFRIENDLISTLISTENER	
			listeners->NotifyAllNow(&IFriendListListener::OnFriendListRetrieveSuccess);
#endif
		}
		else if (connection_state) {
			// Connected
			//listeners->NotifyAllNow(&IOperationalStateChangeListener::OnOperationalStateChanged, (IOperationalStateChangeListener::OPERATIONAL_STATE_SIGNED_IN));
		}
		else {
			// Disconnected
#if GALAXY_BUILD_FEATURE_HAS_OPERATIONALSTATECHANGELISTENER
			listeners->NotifyAllNow(&IOperationalStateChangeListener::OnOperationalStateChanged, (IOperationalStateChangeListener::OperationalState::OPERATIONAL_STATE_SIGNED_IN));
#endif
		}
	}
}
