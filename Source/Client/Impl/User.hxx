#ifndef LSFDRMFG_IMPL_USER_H
#define LSFDRMFG_IMPL_USER_H

/**
 * @file
 * Contains data structures and interfaces related to user account.
 */
#include "ListenerRegistrar.hxx"

#include <GalaxyUserData.hxx>

#include <Networking/Messages/RequestSpecificUserDataMessage.hxx>
#include <Networking/Messages/OnlineStatusChangeMessage.hxx>
#include <Networking/Messages/SetUserDataMessage.hxx>

#include <IUser.h>
#include <GalaxyID.h>
#include <IListenerRegistrar.h>

#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>

#if GALAXY_BUILD_FEATURE_USER_SIGNIN_CROSSPLATFORM

#define USER_SIGN_IN_CREDENTIALS SignInCredentials
#define USER_SIGN_IN_STEAM SignInSteam
#define USER_SIGN_IN_GALAXY SignInGalaxy
#define USER_SIGN_IN_PS4 SignInPS4
#define USER_SIGN_IN_SERVER_KEY SignInServerKey

#else

#define USER_SIGN_IN_CREDENTIALS SignIn
#define USER_SIGN_IN_STEAM SignIn
#define USER_SIGN_IN_GALAXY SignIn
#define USER_SIGN_IN_PS4 SignIn
#define USER_SIGN_IN_SERVER_KEY SignIn

#endif

namespace universelan::client {
	using namespace galaxy::api;
	struct InterfaceInstances;

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
		using mutex_t = std::recursive_mutex;
		using lock_t = std::scoped_lock<mutex_t>;

	private:
		mutable mutex_t mtx_user_data;

		InterfaceInstances* intf;
		ListenerRegistrarImpl* listeners;
		GalaxyUserData::map_t user_data;

		ListenersRequestHelper<ISpecificUserDataListener*> specific_user_data_requests;

	public:

		UserImpl(InterfaceInstances* intf);
		virtual ~UserImpl();

		void SignIn(IAuthListener* const listener);

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
		virtual void USER_SIGN_IN_STEAM(const void* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName
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
		 * @param [in] requireOnline Indicates if sing in with Galaxy backend is required.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void USER_SIGN_IN_GALAXY(bool requireOnline = false
#if GALAXY_BUILD_FEATURE_USER_SIGNIN_LISTENERS
			, IAuthListener* const listener = NULL
#endif
		) override;

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

#if GALAXY_BUILD_FEATURE_USER_SIGNIN_CROSSPLATFORM

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
		virtual void SignInPS4(const char* ps4ClientID, IAuthListener* const listener = NULL) override;

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

		/**
		 * Signs the Galaxy Peer out.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener and IOperationalStateChangeListener.
		 *
		 * @remark All pending asynchronous operations will be finished immediately.
		 * Their listeners will be called with the next call to the ProcessData().
		 */
		virtual void SignOut() override;
#else

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

		/**
		 * Retrieves/Refreshes user data storage.
		 *
		 * This call is asynchronous. Responses come to the IUserDataListener and ISpecificUserDataListener.
		 *
		 * @param [in] userID The ID of the user. It can be omitted when requesting for own data.
		 * @param [in] listener The listener for specific operation.
		 */
		virtual void RequestUserData(GalaxyID userID = GalaxyID()
#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
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
		virtual const char* GetUserData(const char* key, GalaxyID userID = GalaxyID()) override;

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
		virtual void GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID = GalaxyID()) override;

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
#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
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
		virtual uint32_t GetUserDataCount(GalaxyID userID = GalaxyID()) override;

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
		virtual bool GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID = GalaxyID()) override;

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
#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
			, ISpecificUserDataListener* const listener = NULL
#endif
		) override;

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
#if GALAXY_BUILD_FEATURE_USER_DATA_LISTENERS
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
		/**
		 * Returns the ID of current session.
		 *
		 * @return The session ID.
		 */
		virtual SessionID GetSessionID() override;

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

		void SpecificUserDataRequestProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data);
		void OnlineUserStateChange(const std::shared_ptr<OnlineStatusChangeMessage>& data);
		void SetUserDataMessageReceived(const std::shared_ptr<SetUserDataMessage>& data);

		GalaxyUserData::ptr_t GetGalaxyUserData(GalaxyID userID);
		bool IsGalaxyUserDataPresent(GalaxyID userID) const;
	};

	/** @} */
}

#endif
