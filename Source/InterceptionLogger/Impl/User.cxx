#include "User.hxx"

#include "Listeners/UserListener.hxx"

#include <EnvUtils.hxx>
#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>
#include <IniData.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::IUSER;

		const char UNIVERSELAN_OVERRIDE_USERNAME[] = "UNIVERSELAN_OVERRIDE_USERNAME";
		const char UNIVERSELAN_OVERRIDE_PASSWORD[] = "UNIVERSELAN_OVERRIDE_PASSWORD";
	}

#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
#define GET_LISTENER(listener) (listener)
#else
#define GET_LISTENER(listener) ((IAuthListener* const)nullptr)
#endif

	UserImpl::UserImpl(FuncT::F intf, IListenerRegistrar* notifications, ClientIniData* config) :
		intf{ intf },
		notifications{ notifications },
		listeners{ notifications },
		config{ config } {
		listeners.AddListener<AuthListener>();
#if GALAXY_BUILD_FEATURE_HAS_IOTHERSESSIONSTARTLISTENER
		listeners.AddListener<OtherSessionStartListener>();
#endif
		listeners.AddListener<OperationalStateChangeListener>();
		listeners.AddListener<UserDataListener>();
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		listeners.AddListener<SpecificUserDataListener>();
#endif
		listeners.AddListener<EncryptedAppTicketListener>();
#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
		listeners.AddListener<AccessTokenListener>();
#endif
	}

	UserImpl::~UserImpl() {
		listeners.UnregisterAllListeners();
	}

	bool UserImpl::SignedIn() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->SignedIn();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	GalaxyID UserImpl::GetGalaxyID() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = intf()->GetGalaxyID();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void UserImpl::USER_SIGN_IN_STEAM(const SignInDataPtr_T* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("steamAppTicket: {}", (void*)steamAppTicket));
			trace.write_all(std::format("steamAppTicketSize: {}", steamAppTicketSize));
			trace.write_all(std::format("personaName: {}", util::safe_fix_null_char_ptr_annotate_ret(personaName)));
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->USER_SIGN_IN_STEAM(steamAppTicket, steamAppTicketSize, personaName
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, AuthListener::encapsulate(listener)
#endif	
		);
	}

	void UserImpl::USER_SIGN_IN_CREDENTIALS(const char* login, const char* password
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("login: {}", util::safe_fix_null_char_ptr_annotate_ret(login)));
			trace.write_all(std::format("password: {}", (void*)password)); // Only print pw address

#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->USER_SIGN_IN_CREDENTIALS(login, password
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, AuthListener::encapsulate(listener)
#endif	
		);
	}

	void UserImpl::USER_SIGN_IN_GALAXY(
#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_REQUIREONLINE
		bool requireOnline
#endif
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINSTEAM
			trace.write_all(std::format("requireOnline: {}", requireOnline));
#endif
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		if (config->OverrideSignInEnabled()) {
			std::string id = env_utils::get_env(UNIVERSELAN_OVERRIDE_USERNAME);
			std::string password = env_utils::get_env(UNIVERSELAN_OVERRIDE_PASSWORD);

			if (id.length() < 1) {
				id = config->GetOverrideSignInId();
			}

			if (password.length() < 1) {
				password = config->GetOverrideSignInPassword();
			}

			intf()->USER_SIGN_IN_CREDENTIALS(
				id.c_str(),
				password.c_str()
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
				, AuthListener::encapsulate(listener)
#endif
			);
		}
		else {
			intf()->USER_SIGN_IN_GALAXY(
#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_REQUIREONLINE
				requireOnline
#endif
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
				, AuthListener::encapsulate(listener)
#endif	
			);
		}
	}

#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_WITH_SERVERKEY
	void UserImpl::USER_SIGN_IN_SERVER_KEY(const char* serverKey
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("serverKey: {}", util::safe_fix_null_char_ptr_annotate_ret(serverKey)));
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}
		intf()->USER_SIGN_IN_SERVER_KEY(serverKey
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, AuthListener::encapsulate(listener)
#endif	
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API
	void UserImpl::SignInAnonymous(
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}
		intf()->SignInAnonymous(
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			AuthListener::encapsulate(listener)
#endif	
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNINTOKEN
	void UserImpl::SignInToken(const char* refreshToken, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("refreshToken: {}", util::safe_fix_null_char_ptr_annotate_ret(refreshToken)));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}
		intf()->SignInToken(refreshToken
			, AuthListener::encapsulate(listener)
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINLAUNCHER
	void UserImpl::SignInLauncher(IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}
		intf()->SignInLauncher(
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			AuthListener::encapsulate(listener)
#endif	
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINEPIC
	void UserImpl::SignInEpic(const char* epicAccessToken, const char* epicUsername, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("epicAccessToken: {}", util::safe_fix_null_char_ptr_annotate_ret(epicAccessToken)));
			trace.write_all(std::format("epicUsername: {}", util::safe_fix_null_char_ptr_annotate_ret(epicUsername)));
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}
		intf()->SignInEpic(epicAccessToken, epicUsername
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, AuthListener::encapsulate(listener)
#endif	
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_IUSER_UWP_TO_XBOX_RENAME
	void UserImpl::SignInXbox(uint64_t xboxID, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("xboxID: {}", xboxID));
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}
		intf()->SignInXbox(xboxID
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, AuthListener::encapsulate(listener)
#endif	
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNINUWP
	void UserImpl::SignInUWP(IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		intf()->SignInUWP(AuthListener::encapsulate(listener));
	}
#endif

#if GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINPS4
	void UserImpl::USER_SIGN_IN_PS4(const char* ps4ClientID, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("ps4ClientID: {}", util::safe_fix_null_char_ptr_annotate_ret(ps4ClientID)));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		intf()->USER_SIGN_IN_PS4(ps4ClientID, AuthListener::encapsulate(listener));
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNINXB1
	void UserImpl::SignInXB1(const char* xboxOneUserID, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("xboxOneUserID: {}", util::safe_fix_null_char_ptr_annotate_ret(xboxOneUserID)));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		intf()->SignInXB1(xboxOneUserID, AuthListener::encapsulate(listener));
	}
#endif

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINXBLIVE
	void UserImpl::SignInXBLive(const char* token, const char* signature, const char* marketplaceID, const char* locale, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("token: {}", util::safe_fix_null_char_ptr_annotate_ret(token)));
			trace.write_all(std::format("signature: {}", util::safe_fix_null_char_ptr_annotate_ret(signature)));
			trace.write_all(std::format("marketplaceID: {}", util::safe_fix_null_char_ptr_annotate_ret(marketplaceID)));
			trace.write_all(std::format("locale: {}", util::safe_fix_null_char_ptr_annotate_ret(locale)));
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		intf()->SignInXBLive(token, signature, marketplaceID, locale, AuthListener::encapsulate(listener));
	}
#endif

#if GALAXY_BUILD_FEATURE_ITELEMETRY_1_139_6_UPDATE
	void UserImpl::SignInAnonymousTelemetry(IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("listener: {}", (void*)listener));
		}

		intf()->SignInAnonymousTelemetry(AuthListener::encapsulate(listener));
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_CLASSIC_XBOX
	void UserImpl::SignIn(uint32_t xboxOneUserID
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("xboxOneUserID: {}", xboxOneUserID));
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}
		intf()->SignIn(xboxOneUserID
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, AuthListener::encapsulate(listener)
#endif
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_PS4
	void UserImpl::SignIn(const char* ps4ClientID, const char* ps4TitleID, const char* ps4TitleSecret, uint32_t ps4TitleSecretLength
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("ps4ClientID: {}", util::safe_fix_null_char_ptr_annotate_ret(ps4ClientID)));
			trace.write_all(std::format("ps4TitleID: {}", util::safe_fix_null_char_ptr_annotate_ret(ps4TitleID)));
			trace.write_all(std::format("ps4TitleSecret (addr): {}", (void*)ps4TitleSecret));
			trace.write_all(std::format("ps4TitleSecretLength: {}", ps4TitleSecretLength));
			trace.write_all(std::format("ps4TitleSecret: {}", util::safe_fix_null_char_ptr_annotate(ps4TitleSecret, ps4TitleSecretLength)));
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}
		intf()->SignIn(ps4ClientID, ps4TitleID, ps4TitleSecret, ps4TitleSecretLength
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, AuthListener::encapsulate(listener)
#endif
		);
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNOUT
	void UserImpl::SignOut() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		intf()->SignOut();
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
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			trace.write_all(std::format("userID: {}", userID));
#endif
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->RequestUserData(
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			userID
#endif
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
			, SpecificUserDataListener::encapsulate(listener)
#endif
		);
	}

#if GALAXY_BUILD_FEATURE_HAS_USERDATAINFOAVAILABLE
	bool UserImpl::IsUserDataAvailable(GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("userID: {}", userID));
		}

		auto result = intf()->IsUserDataAvailable(userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif

	const char* UserImpl::GetUserData(const char* key
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		, GalaxyID userID
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			trace.write_all(std::format("userID: {}", userID));
#endif
		}

		auto result = intf()->GetUserData(key
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			, userID
#endif
		);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
	void UserImpl::GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
			trace.write_all(std::format("userID: {}", userID));
		}

		intf()->GetUserDataCopy(key, buffer, bufferLength, userID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}
#endif

	void UserImpl::SetUserData(const char* key, const char* value
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
			trace.write_all(std::format("value: {}", util::safe_fix_null_char_ptr_annotate_ret(value)));
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->SetUserData(key, value
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
			, SpecificUserDataListener::encapsulate(listener)
#endif
		);
	}

	uint32_t UserImpl::GetUserDataCount(
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		GalaxyID userID
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			trace.write_all(std::format("userID: {}", userID));
#endif
		}

		auto result = intf()->GetUserDataCount(
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			userID
#endif	
		);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	bool UserImpl::GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		, GalaxyID userID
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
			trace.write_all(std::format("key: {}", (void*)key));
			trace.write_all(std::format("keyLength: {}", keyLength));
			trace.write_all(std::format("value: {}", (void*)value));
			trace.write_all(std::format("valueLength: {}", valueLength));
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			trace.write_all(std::format("userID: {}", userID));
#endif
		}

		auto result = intf()->GetUserDataByIndex(index, key, keyLength, value, valueLength
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			, userID
#endif	
		);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate(key, keyLength)));
			trace.write_all(std::format("value: {}", util::safe_fix_null_char_ptr_annotate(value, valueLength)));
		}

		return result;
	}

	void UserImpl::DeleteUserData(const char* key
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->DeleteUserData(key
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
			, SpecificUserDataListener::encapsulate(listener)
#endif
		);
	}

	bool UserImpl::IsLoggedOn() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		auto result = intf()->IsLoggedOn();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_ENCRYPTED_APP_TICKET
	void UserImpl::RequestEncryptedAppTicket(RequestEncryptedAppTicketDataT* data, uint32_t dataSize
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
		, IEncryptedAppTicketListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("data: {}", (void*)data));
			trace.write_all(std::format("dataSize: {}", dataSize));
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->RequestEncryptedAppTicket(data, dataSize
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
			, EncryptedAppTicketListener::encapsulate(listener)
#endif
		);
	}

	void UserImpl::GetEncryptedAppTicket(void* encryptedAppTicket, uint32_t maxEncryptedAppTicketSize, uint32_t& currentEncryptedAppTicketSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("encryptedAppTicket: {}", (void*)encryptedAppTicket));
			trace.write_all(std::format("maxEncryptedAppTicketSize: {}", maxEncryptedAppTicketSize));
		}

		intf()->GetEncryptedAppTicket(encryptedAppTicket, maxEncryptedAppTicketSize, currentEncryptedAppTicketSize);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("currentEncryptedAppTicketSize: {}", currentEncryptedAppTicketSize));
		}
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IOTHERSESSIONSTARTLISTENER
	SessionID UserImpl::GetSessionID() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->GetSessionID();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
	const char* UserImpl::GetAccessToken() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->GetAccessToken();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

	void UserImpl::GetAccessTokenCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		intf()->GetAccessTokenCopy(buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}

	bool UserImpl::ReportInvalidAccessToken(const char* accessToken
#if GALAXY_BUILD_FEATURE_USER_ACCESS_TOKEN_INFO
		, const char* info
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("accessToken: {}", util::safe_fix_null_char_ptr_annotate_ret(accessToken)));
#if GALAXY_BUILD_FEATURE_USER_ACCESS_TOKEN_INFO
			trace.write_all(std::format("info: {}", util::safe_fix_null_char_ptr_annotate_ret(info)));
#endif
		}

		auto result = intf()->ReportInvalidAccessToken(accessToken
#if GALAXY_BUILD_FEATURE_USER_ACCESS_TOKEN_INFO
			, info
#endif
		);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSER_REFRESHTOKEN
	void UserImpl::GetRefreshTokenCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		intf()->GetRefreshTokenCopy(buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}

	const char* UserImpl::GetRefreshToken() {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		auto result = intf()->GetRefreshToken();

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}
#endif

}
