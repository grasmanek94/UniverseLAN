#pragma once

#include "Listeners/UserListener.hxx"

#include <GalaxyFunctional.hxx>
#include <IniData.hxx>
#include <ListenersContainer.hxx>

#include <GalaxyExport.h>
#include <IListenerRegistrar.h>
#include <IUser.h>

#if GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINCREDENTIALS
#define USER_SIGN_IN_CREDENTIALS SignInCredentials
#else
#define USER_SIGN_IN_CREDENTIALS SignIn
#endif

#if GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINSTEAM
#define USER_SIGN_IN_STEAM SignInSteam
#else
#define USER_SIGN_IN_STEAM SignIn
#endif

#if GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINGALAXY
#define USER_SIGN_IN_GALAXY SignInGalaxy
#else
#define USER_SIGN_IN_GALAXY SignIn
#endif

#if GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINPS4
#define USER_SIGN_IN_PS4 SignInPS4
#else
#define USER_SIGN_IN_PS4 SignIn
#endif

#if GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINSERVERKEY
#define USER_SIGN_IN_SERVER_KEY SignInServerKey
#else
#define USER_SIGN_IN_SERVER_KEY SignIn
#endif

namespace universelan::client {
	using namespace galaxy::api;

	/**
	 * @addtogroup api
	 * @{
	 */

	 /**
	  * The interface for handling the user account.
	  */
	class UserImpl : public IUser
	{
	public:

#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_REQUIREONLINE
		using SignInDataPtr_T = void;
#else
		using SignInDataPtr_T = char;
#endif

		using FuncT = functional::xt<std::function<GALAXY_DLL_EXPORT IUser* GALAXY_CALLTYPE(void)>>;
		using FuncPtr = typename FuncT::PTR;

	private:
		FuncT::F intf;
		IListenerRegistrar* notifications;
		ListenersContainer listeners;
		ClientIniData* config;

	public:
		UserImpl(FuncT::F intf, IListenerRegistrar* notifications, ClientIniData* config);
		virtual ~UserImpl();

		/**
		 * Checks if the user is signed in to Galaxy.
		 *
		 * The user should be reported as signed in as soon as the authentication
		 * process is finished.
		 *
		 * If the user is not able to sign in or gets signed out, there might be either
		 * a networking issue or a limited availability of Galaxy backend services.
		 *
		 * After loosing authentication the user needs to sign in again in order
		 * for the Galaxy Peer to operate.
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IAuthListener and the IOperationalStateChangeListener.
		 *
		 * @return true if the user is signed in, false otherwise.
		 */
		virtual bool SignedIn() override;

		/**
		 * Returns the ID of the user, provided that the user is signed in.
		 *
		 * @return The ID of the user.
		 */
		virtual GalaxyID GetGalaxyID() override;

		/**
		 * Authenticates the Galaxy Peer with specified user credentials.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @warning This method is only for testing purposes and is not meant
		 * to be used in production environment in any way.
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] login The user's login.
		 * @param [in] password The user's password.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void USER_SIGN_IN_CREDENTIALS(const char* login, const char* password
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, IAuthListener* const listener = NULL
#endif
		) override;

		/**
		 * Authenticates the Galaxy Peer based on Steam Encrypted App Ticket.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] steamAppTicket The Encrypted App Ticket from the Steam API.
		 * @param [in] steamAppTicketSize The size of the ticket.
		 * @param [in] personaName The user's persona name, i.e. the username from Steam.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void USER_SIGN_IN_STEAM(const SignInDataPtr_T* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, IAuthListener* const listener = NULL
#endif
		) override;

		/**
		 * Authenticates the Galaxy Peer based on Galaxy Client authentication.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] requireOnline Indicates if sign in with Galaxy backend is required.
		 * @param [in] timeout Time in seconds for AuthListener to trigger timeout
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void USER_SIGN_IN_GALAXY(
#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_REQUIREONLINE
			bool requireOnline = false
#endif
#if GALAXY_BUILD_FEATURE_HAS_IUSER_SIGNINGALAXY_TIMEOUT
			, uint32_t timeout = 15
#endif
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, IAuthListener* const listener = NULL
#endif
		) override;

#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_WITH_SERVERKEY
		/**
		 * Authenticates the Galaxy Peer with a specified server key.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener.
		 *
		 * @warning Make sure you do not put your server key in public builds.
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @remark Signing in with a server key is meant for server-side usage,
		 * meaning that typically there will be no user associated to the session.
		 *
		 * @param [in] serverKey The server key.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void USER_SIGN_IN_SERVER_KEY(const char* serverKey
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, IAuthListener* const listener = NULL
#endif
		) override;
#endif

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API
		/**
		 * Authenticates the Galaxy Game Server anonymously.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void SignInAnonymous(
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			IAuthListener* const listener = NULL
#endif
		) override;
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNINTOKEN
		/**
		 * Authenticates the Galaxy Peer with refresh token.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * This method is designed for application which renders Galaxy login page
		 * in its UI and obtains refresh token after user login.
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] refreshToken The refresh token obtained from Galaxy login page.
		 * @param [in] listener The listener for specific operation.
		 */

		virtual void SignInToken(const char* refreshToken, IAuthListener* const listener = NULL) override;
#endif

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINLAUNCHER
		/**
		 * Authenticates the Galaxy Peer based on CDPR launcher authentication.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @note This method is for internal uses only.
		 *
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void SignInLauncher(IAuthListener* const listener = NULL) override;
#endif

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINEPIC
		/**
		 * Authenticates the Galaxy Peer based on Epic Access Token.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] epicAccessToken The Authentication Token from the Epic API.
		 * @param [in] epicUsername The username of the Epic account.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void SignInEpic(const char* epicAccessToken, const char* epicUsername, IAuthListener* const listener = NULL) override;
#endif


#if GALAXY_BUILD_FEATURE_IUSER_UWP_TO_XBOX_RENAME
		/**
		 * Authenticates the Galaxy Peer based on XBOX GDK credentials.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] xboxID The XBOX user ID.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void SignInXbox(uint64_t xboxID, IAuthListener* const listener = NULL) override;
#endif
#if GALAXY_BUILD_FEATURE_HAS_SIGNINUWP
		/**
		 * Authenticates the Galaxy Peer based on Windows Store authentication
		 * in Universal Windows Platform application.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] listener The listener for specific operation.
		*/
		virtual void SignInUWP(IAuthListener* const listener = NULL) override;
#endif

#if GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINPS4
		/**
		 * Authenticates the Galaxy Peer based on PS4 credentials.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] ps4ClientID The PlayStation 4 client ID.
		 * @param [in] listener The listener for specific operation.
		 */

		virtual void USER_SIGN_IN_PS4(const char* ps4ClientID, IAuthListener* const listener = NULL) override;
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNINXB1
		/**
		 * Authenticates the Galaxy Peer based on XBOX ONE credentials.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] xboxOneUserID The XBOX ONE user ID.
		 * @param [in] listener The listener for specific operation.
		 */

		virtual void SignInXB1(const char* xboxOneUserID, IAuthListener* const listener = NULL) override;
#endif

#if GALAXY_BUILD_FEATURE_IUSER_SIGNINXBLIVE
		/**
		 * Authenticates the Galaxy Peer based on Xbox Live tokens.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] token The XSTS token.
		 * @param [in] signature The digital signature for the HTTP request.
		 * @param [in] marketplaceID The Marketplace ID
		 * @param [in] locale The user locale (example values: EN-US, FR-FR).
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void SignInXBLive(const char* token, const char* signature, const char* marketplaceID, const char* locale, IAuthListener* const listener = NULL) override;
#endif

#if GALAXY_BUILD_FEATURE_ITELEMETRY_1_139_6_UPDATE
		/**
		 * Authenticates the Galaxy Peer anonymously.
		 *
		 * This authentication method enables the peer to send anonymous telemetry events.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void SignInAnonymousTelemetry(IAuthListener* const listener = NULL) override;
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_CLASSIC_XBOX
		/**
		* Initializes the Galaxy Peer based on XBOX ONE credentials.
		*
		* This call is asynchronous. Responses come to the IAuthListener
		* (for all GlobalAuthListener-derived and optional listener passed as argument).
		*
		* @remark Information about being signed in or signed out also comes to
		* the IOperationalStateChangeListener.
		*
		* @param [in] xboxOneUserID The XBOX ONE user ID.
		* @param [in] listener The listener for specific operation [EXPERIMENTAL].
		*/
		virtual void SignIn(uint32_t xboxOneUserID
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, IAuthListener* listener = NULL
#endif
		);
#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNIN_PS4
		/**
		 * Initializes the Galaxy Peer based on PS4 credentials.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] ps4ClientID The PlayStation 4 client ID.
		 * @param [in] ps4TitleID Not used anymore. Will be removed in future releases.
		 * @param [in] ps4TitleSecret Not used anymore. Will be removed in future releases.
		 * @param [in] ps4TitleSecretLength Not used anymore. Will be removed in future releases.
		 * @param [in] listener The listener for specific operation [EXPERIMENTAL].
		 */
		virtual void SignIn(const char* ps4ClientID, const char* ps4TitleID, const char* ps4TitleSecret, uint32_t ps4TitleSecretLength
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, IAuthListener* const listener = NULL
#endif
		) override;

#endif

#if GALAXY_BUILD_FEATURE_HAS_SIGNOUT
		/**
		 * Signs the Galaxy Peer out.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener and IOperationalStateChangeListener.
		 *
		 * @remark All pending asynchronous operations will be finished immediately.
		 * Their listeners will be called with the next call to the ProcessData().
		 */
		virtual void SignOut() override;
#endif

		/**
		 * Retrieves/Refreshes user data storage.
		 *
		 * This call is asynchronous. Responses come to the IUserDataListener and ISpecificUserDataListener.
		 *
		 * @param [in] userID The ID of the user. It can be omitted when requesting for own data.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void RequestUserData(
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			GalaxyID userID = GalaxyID()
#endif
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
			, ISpecificUserDataListener* const listener = NULL
#endif
		) override;

#if GALAXY_BUILD_FEATURE_HAS_USERDATAINFOAVAILABLE
		/**
		 * Checks if user data exists.
		 *
		 * @pre Retrieve the user data first by calling RequestUserData().
		 *
		 * @param [in] userID The ID of the user. It can be omitted when checking for own data.
		 * @return true if user data exists, false otherwise.
		 */
		virtual bool IsUserDataAvailable(GalaxyID userID = GalaxyID()) override;
#endif

		/**
		 * Returns an entry from the data storage of current user.
		 *
		 * @remark This call is not thread-safe as opposed to GetUserDataCopy().
		 *
		 * @pre Retrieve the user data first by calling RequestUserData().
		 *
		 * @param [in] key The name of the property of the user data storage.
		 * @param [in] userID The ID of the user. It can be omitted when reading own data.
		 * @return The value of the property, or an empty string if failed.
		 */
		virtual const char* GetUserData(const char* key
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			, GalaxyID userID = GalaxyID()
#endif
		) override;

#if GALAXY_BUILD_FEATURE_IUSER_GET_DATA_ACCESSTOKEN_COPY
		/**
		 * Copies an entry from the data storage of current user.
		 *
		 * @pre Retrieve the user data first by calling RequestUserData().
		 *
		 * @param [in] key The name of the property of the user data storage.
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 * @param [in] userID The ID of the user. It can be omitted when reading own data.
		 */
		virtual void GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			, GalaxyID userID = GalaxyID()
#endif
		) override;
#endif

		/**
		 * Creates or updates an entry in the user data storage.
		 *
		 * This call in asynchronous. Responses come to the IUserDataListener and ISpecificUserDataListener.
		 *
		 * @remark To clear a property, set it to an empty string.
		 *
		 * @param [in] key The name of the property of the user data storage with the limit of 1023 bytes.
		 * @param [in] value The value of the property to set with the limit of 4095 bytes.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void SetUserData(const char* key, const char* value
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
			, ISpecificUserDataListener* const listener = NULL
#endif
		) override;

		/**
		 * Returns the number of entries in the user data storage
		 *
		 * @pre Retrieve the user data first by calling RequestUserData().
		 *
		 * @param [in] userID The ID of the user. It can be omitted when reading own data.
		 * @return The number of entries, or 0 if failed.
		 */
		virtual uint32_t GetUserDataCount(
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			GalaxyID userID = GalaxyID()
#endif
		) override;

		/**
		 * Returns a property from the user data storage by index.
		 *
		 * @pre Retrieve the user data first by calling RequestUserData().
		 *
		 * @param [in] index Index as an integer in the range of [0, number of entries).
		 * @param [in, out] key The name of the property of the user data storage.
		 * @param [in] keyLength The length of the name of the property of the user data storage.
		 * @param [in, out] value The value of the property of the user data storage.
		 * @param [in] valueLength The length of the value of the property of the user data storage.
		 * @param [in] userID The ID of the user. It can be omitted when reading own data.
		 * @return true if succeeded, false when there is no such property.
		 */
		virtual bool GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength
#if GALAXY_BUILD_FEATURE_HAS_SPECIFICUSERDATALISTENER
			, GalaxyID userID = GalaxyID()
#endif
		) override;

		/**
		 * Clears a property of user data storage
		 *
		 * This is the same as calling SetUserData() and providing an empty string
		 * as the value of the property that is to be altered.
		 *
		 * This call in asynchronous. Responses come to the IUserDataListener and ISpecificUserDataListener.
		 *
		 * @param [in] key The name of the property of the user data storage.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void DeleteUserData(const char* key
#if GALAXY_BUILD_FEATURE_HAS_SETUSERDATA_ISPECIFICLISTENER
			, ISpecificUserDataListener* const listener = NULL
#endif
		) override;

#if GALAXY_BUILD_FEATURE_IUSER_HAS_ISLOGGEDON
		/**
		 * Checks if the user is logged on to Galaxy backend services.
		 *
		 * @remark Only a user that has been successfully signed in within Galaxy Service
		 * can be logged on to Galaxy backend services, hence a user that is logged on
		 * is also signed in, and a user that is not signed in is also not logged on.
		 *
		 * @remark Information about being logged on or logged off also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @return true if the user is logged on to Galaxy backend services, false otherwise.
		 */
		virtual bool IsLoggedOn() override;
#endif

#if GALAXY_BUILD_FEATURE_ENCRYPTED_APP_TICKET
#if GALAXY_BUILD_FEATURE_ENCRYPTED_APP_TICKET_CONST
		using RequestEncryptedAppTicketDataT = const void;
#else
		using RequestEncryptedAppTicketDataT = void;
#endif

		/**
		 * Performs a request for an Encrypted App Ticket.
		 *
		 * This call is asynchronous. Responses come to the IEncryptedAppTicketListener.
		 *
		 * @param [in] data The additional data to be placed within the Encrypted App Ticket with the limit of 1023 bytes.
		 * @param [in] dataSize The size of the additional data.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void RequestEncryptedAppTicket(RequestEncryptedAppTicketDataT* data, uint32_t dataSize
#if GALAXY_BUILD_FEATURE_HAS_REQUESTUSERDATA_ISPECIFICLISTENER
			, IEncryptedAppTicketListener* const listener = NULL
#endif
		) override;

		/**
		 * Returns the Encrypted App Ticket.
		 *
		 * If the buffer that is supposed to take the data is too small,
		 * the Encrypted App Ticket will be truncated to its size.
		 *
		 * @pre Retrieve an Encrypted App Ticket first by calling RequestEncryptedAppTicket().
		 *
		 * @param [in, out] encryptedAppTicket The buffer for the Encrypted App Ticket.
		 * @param [in] maxEncryptedAppTicketSize The maximum size of the Encrypted App Ticket buffer.
		 * @param [out] currentEncryptedAppTicketSize The actual size of the Encrypted App Ticket.
		 */
		virtual void GetEncryptedAppTicket(void* encryptedAppTicket, uint32_t maxEncryptedAppTicketSize, uint32_t& currentEncryptedAppTicketSize) override;
#endif

#if GALAXY_BUILD_FEATURE_HAS_IOTHERSESSIONSTARTLISTENER
		/**
		 * Returns the ID of current session.
		 *
		 * @return The session ID.
		 */
		virtual SessionID GetSessionID() override;
#endif

#if GALAXY_BUILD_FEATURE_HAS_IACCESSTOKENLISTENER
		/**
		 * Returns the access token for current session.
		 *
		 * @remark This call is not thread-safe as opposed to GetAccessTokenCopy().
		 *
		 * @remark The access token that is used for current session might be
		 * updated in the background automatically, without any request for that.
		 * Each time the access token is updated, a notification comes to the
		 * IAccessTokenListener.
		 *
		 * @return The access token.
		 */
		virtual const char* GetAccessToken() override;

#if GALAXY_BUILD_FEATURE_IUSER_GET_DATA_ACCESSTOKEN_COPY
		/**
		 * Copies the access token for current session.
		 *
		 * @remark The access token that is used for current session might be
		 * updated in the background automatically, without any request for that.
		 * Each time the access token is updated, a notification comes to the
		 * IAccessTokenListener.
		 *
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		virtual void GetAccessTokenCopy(char* buffer, uint32_t bufferLength) override;
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSER_REFRESHTOKEN
		/**
		 * Returns the refresh token for the current session.
		 *
		 * @remark This call is not thread-safe as opposed to GetRefreshTokenCopy().
		 *
		 * @remark Calling this function is allowed when the session has been signed in
		 * with IUser::SignInToken() only.
		 *
		 * The refresh token that is used for the current session might be
		 * updated in the background automatically, together with the access token,
		 * without any request for that. Each time the access or refresh token
		 * is updated, a notification comes to the IAccessTokenListener.
		 *
		 * @return The refresh token.
		 */
		virtual const char* GetRefreshToken() override;

		/**
		 * Copies the refresh token for the current session.
		 *
		 * @remark Calling this function is allowed when the session has been signed in
		 * with IUser::SignInToken() only.
		 *
		 * The refresh token that is used for the current session might be
		 * updated in the background automatically, together with access token,
		 * without any request for that. Each time the access or refresh token
		 * is updated, a notification comes to the IAccessTokenListener.
		 *
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		virtual void GetRefreshTokenCopy(char* buffer, uint32_t bufferLength) override;
#endif

		/**
		 * Reports current access token as no longer working.
		 *
		 * This starts the process of refreshing access token, unless the process
		 * is already in progress. The notifications come to IAccessTokenListener.
		 *
		 * @remark The access token that is used for current session might be
		 * updated in the background automatically, without any request for that.
		 * Each time the access token is updated, a notification comes to the
		 * IAccessTokenListener.
		 *
		 * @remark If the specified access token is not the same as the access token
		 * for current session that would have been returned by GetAccessToken(),
		 * the report will not be accepted and no further action will be performed.
		 * In such case do not expect a notification to IAccessTokenListener and
		 * simply get the new access token by calling GetAccessToken().
		 *
		 * @param [in] accessToken The invalid access token.
		 * @param [in] info Additional information, e.g. the URI of the resource it was used for.
		 * @return true if the report was accepted, false otherwise.
		 */
		virtual bool ReportInvalidAccessToken(const char* accessToken
#if GALAXY_BUILD_FEATURE_USER_ACCESS_TOKEN_INFO
			, const char* info = NULL
#endif
		) override;
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSER_AUTHORIZATION_IDTOKEN
		/**
		 * Authenticates the Galaxy Peer based on OpenID Connect generated authorization code.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener
		 * (for all GlobalAuthListener-derived and optional listener passed as argument).
		 *
		 * @remark Information about being signed in or signed out also comes to
		 * the IOperationalStateChangeListener.
		 *
		 * @param [in] requireOnline Indicates if sign in with Galaxy backend is required.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void SignInAuthorizationCode(const char* authorizationCode, const char* redirectURI, IAuthListener* const listener = NULL) override;

		/**
		 * Returns the id token for the current session.
		 *
		 * @remark This call is not thread-safe as opposed to GetIDTokenCopy().
		 *
		 * @remark Calling this function is allowed when the session has been signed in
		 * with IUser::SignInToken() only.
		 *
		 * The id token that is used for the current session might be
		 * updated in the background automatically, together with the access token,
		 * without any request for that. Each time the access or id token
		 * is updated, a notification comes to the IAccessTokenListener.
		 *
		 * @return The id token.
		 */
		virtual const char* GetIDToken() override;

		/**
		 * Copies the id token for the current session.
		 *
		 * @remark Calling this function is allowed when the session has been signed in
		 * with IUser::SignInToken() only.
		 *
		 * The id token that is used for the current session might be
		 * updated in the background automatically, together with access token,
		 * without any request for that. Each time the access or id token
		 * is updated, a notification comes to the IAccessTokenListener.
		 *
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		virtual void GetIDTokenCopy(char* buffer, uint32_t bufferLength) override;
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSER_OPENID
		/**
		 * Performs a request for a PlayFab's CreateOpenIdConnection
		 *
		 * This call is asynchronous. Responses come to the IPlayFabCreateOpenIDConnectionListener.
		 *
		 * @param [in] secretKey This API requires a title secret key, available to title admins, from PlayFab Game Manager.
		 * @param [in] titleID Unique identifier for the title, found in the Settings > Game Properties section of the PlayFab developer site when a title has been selected.
		 * @param [in] connectionID A name for the connection that identifies it within the title.
		 * @param [in] ignoreNounce Ignore 'nonce' claim in identity tokens.
		*/
		virtual void CreateOpenIDConnection(const char* secretKey, const char* titleID, const char* connectionID, bool ignoreNonce = true, IPlayFabCreateOpenIDConnectionListener* const listener = NULL) override;

		/**
		 * Performs a request for a PlayFab's LoginWithOpenIdConnect
		 *
		 * This call is asynchronous. Responses come to the IPlayFabLoginWithOpenIDConnectListener.
		 *
		 * @param [in] titleID Unique identifier for the title, found in the Settings > Game Properties section of the PlayFab developer site when a title has been selected.
		 * @param [in] connectionID A name that identifies which configured OpenID Connect provider relationship to use.
		 * @param [in] idToken The JSON Web token (JWT) returned by the identity provider after login.
		 * @param [in] createAccount Automatically create a PlayFab account if one is not currently linked to this ID.
		 * @param [in] encryptedRequest Base64 encoded body that is encrypted with the Title's public RSA key (Enterprise Only).
		 * @param [in] playerSecret Player secret that is used to verify API request signatures (Enterprise Only).
		*/
		virtual void LoginWithOpenIDConnect(const char* titleID, const char* connectionID, const char* idToken, bool createAccount = true, const char* encryptedRequest = NULL, const char* playerSecret = NULL, IPlayFabLoginWithOpenIDConnectListener* const listener = NULL) override;
#endif

	};

	/** @} */
}
