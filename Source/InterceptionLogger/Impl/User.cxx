#include "User.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
#define GET_LISTENER(listener) (listener)
#else
#define GET_LISTENER(listener) ((IAuthListener* const)nullptr)
#endif

	UserImpl::UserImpl(FuncT::F intf) : intf{ intf }
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };
	}

	UserImpl::~UserImpl()
	{
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };
	}

	bool UserImpl::SignedIn() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

	GalaxyID UserImpl::GetGalaxyID() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER | tracer::Trace::HIGH_FREQUENCY_CALLS };

	}

	void UserImpl::SignIn(IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

	void UserImpl::USER_SIGN_IN_STEAM(const SignInDataPtr_T* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

	void UserImpl::USER_SIGN_IN_CREDENTIALS(const char* login, const char* password
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

	void UserImpl::USER_SIGN_IN_GALAXY(
#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_PS4
		bool requireOnline
#endif
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_WITH_SERVERKEY
	void UserImpl::USER_SIGN_IN_SERVER_KEY(const char* serverKey
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API
	void UserImpl::SignInAnonymous(
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif

#if GALAXY_BUILD_FEATURE_USER_SIGNIN_CROSSPLATFORM
	void UserImpl::SignInToken(const char* refreshToken, IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINLAUNCHER
	void UserImpl::SignInLauncher(IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINEPIC
	void UserImpl::SignInEpic(const char* epicAccessToken, const char* epicUsername, IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif

#if GALAXY_BUILD_FEATURE_IUSER_UWP_TO_XBOX_RENAME
	void UserImpl::SignInXbox(uint64_t xboxID, IAuthListener* const listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#else
	void UserImpl::SignInUWP(IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif

	void UserImpl::SignInPS4(const char* ps4ClientID, IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

	void UserImpl::SignInXB1(const char* xboxOneUserID, IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINXBLIVE
	void UserImpl::SignInXBLive(const char* token, const char* signature, const char* marketplaceID, const char* locale, IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif

#if GALAXY_BUILD_FEATURE_ITELEMETRY_1_139_6_UPDATE
	void UserImpl::SignInAnonymousTelemetry(IAuthListener* const listener) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif

#else

	void UserImpl::SignIn(uint32_t xboxOneUserID
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_PS4
	void UserImpl::SignIn(const char* ps4ClientID, const char* ps4TitleID, const char* ps4TitleSecret, uint32_t ps4TitleSecretLength
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
		, IAuthListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNOUT
	void UserImpl::SignOut() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

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
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

#if GALAXY_BUILD_FEATURE_HAS_USERDATAINFOAVAILABLE
	bool UserImpl::IsUserDataAvailable(GalaxyID userID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif

	const char* UserImpl::GetUserData(const char* key
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		, GalaxyID userID
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
	void UserImpl::GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif

	void UserImpl::SetUserData(const char* key, const char* value
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

	uint32_t UserImpl::GetUserDataCount(
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		GalaxyID userID
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

	bool UserImpl::GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
		, GalaxyID userID
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

	void UserImpl::DeleteUserData(const char* key
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
		, ISpecificUserDataListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

	bool UserImpl::IsLoggedOn() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER | tracer::Trace::HIGH_FREQUENCY_CALLS };

	}

#if GALAXY_BUILD_FEATURE_ENCRYPTED_APP_TICKET
	void UserImpl::RequestEncryptedAppTicket(RequestEncryptedAppTicketDataT* data, uint32_t dataSize
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
		, IEncryptedAppTicketListener* const listener
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

	void UserImpl::GetEncryptedAppTicket(void* encryptedAppTicket, uint32_t maxEncryptedAppTicketSize, uint32_t& currentEncryptedAppTicketSize) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IOTHERSESSIONSTARTLISTENER
	SessionID UserImpl::GetSessionID() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
	const char* UserImpl::GetAccessToken() {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

	void UserImpl::GetAccessTokenCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}

	bool UserImpl::ReportInvalidAccessToken(const char* accessToken
#if GALAXY_BUILD_FEATURE_USER_ACCESS_TOKEN_INFO
		, const char* info
#endif
	) {
		tracer::Trace trace { nullptr, __FUNCTION__, tracer::Trace::IUSER };

	}
#endif

}
