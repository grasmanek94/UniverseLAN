#ifndef GALAXY_I_USER_H
#define GALAXY_I_USER_H

/**
 * @file
 * Contains data structures and interfaces related to user account.
 */

#include "IListenerRegistrar.h"
#include "GalaxyID.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * The ID of the session.
		 */
		typedef uint64_t SessionID;

		/**
		 * Listener for the events related to user authentication.
		 */
		class IAuthListener : public GalaxyTypeAwareListener<AUTH>
		{
		public:

			/**
			 * Notification for the event of successful sign in.
			 */
			virtual void OnAuthSuccess() = 0;

			/**
			 * Reason of authentication failure.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED = 0, ///< Undefined error.
				FAILURE_REASON_GALAXY_SERVICE_NOT_AVAILABLE = 1, ///< Galaxy Service is not installed properly or fails to start.
				FAILURE_REASON_GALAXY_SERVICE_NOT_SIGNED_IN = 2, ///< Galaxy Service is not signed in properly.
				FAILURE_REASON_CONNECTION_FAILURE = 3, ///< Unable to communicate with backend services.
				FAILURE_REASON_NO_LICENSE = 4, ///< User that is being signed in has no license for this application.
				FAILURE_REASON_INVALID_CREDENTIALS = 5, ///< Unable to match client credentials (ID, secret) or user credentials (username, password).
				FAILURE_REASON_GALAXY_NOT_INITIALIZED = 6 ///< Galaxy has not been initialized.
			};

			/**
			 * Notification for the event of unsuccessful sign in.
			 *
			 * @param failureReason The cause of the failure.
			 */
			virtual void OnAuthFailure(FailureReason failureReason) = 0;

			/**
			 * Notification for the event of loosing authentication.
			 *
			 * @remark Might occur any time after successfully signing in.
			 */
			virtual void OnAuthLost() = 0;
		};

		/**
		 * Globally self-registering version of IAuthListener.
		 */
		typedef SelfRegisteringListener<IAuthListener> GlobalAuthListener;

		/**
		 * Listener for the events related to starting of other sessions.
		 */
		class IOtherSessionStartListener : public GalaxyTypeAwareListener<OTHER_SESSION_START>
		{
		public:

			/**
			 * Notification for the event of other session being started.
			 */
			virtual void OnOtherSessionStarted() = 0;
		};

		/**
		 * Globally self-registering version of IOtherSessionStartListener.
		 */
		typedef SelfRegisteringListener<IOtherSessionStartListener> GlobalOtherSessionStartListener;

		/**
		 * Listener for the event of a change of the operational state.
		 */
		class IOperationalStateChangeListener : public GalaxyTypeAwareListener<OPERATIONAL_STATE_CHANGE>
		{
		public:

			/**
			 * Aspect of the operational state.
			 */
			enum OperationalState
			{
				OPERATIONAL_STATE_SIGNED_IN = 0x0001, ///< User signed in.
				OPERATIONAL_STATE_LOGGED_ON = 0x0002 ///< User logged on.
			};

			/**
			 * Notification for the event of a change of the operational state.
			 *
			 * @param operationalState The sum of the bit flags representing the operational state, as defined in IOperationalStateChangeListener::OperationalState.
			 */
			virtual void OnOperationalStateChanged(uint32_t operationalState) = 0;
		};

		/**
		 * Globally self-registering version of IOperationalStateChangeListener.
		 */
		typedef SelfRegisteringListener<IOperationalStateChangeListener> GlobalOperationalStateChangeListener;

		/**
		 * Listener for the events related to user data changes of current user only.
		 *
		 * @remark In order to get notifications about changes to user data of all users,
		 * use ISpecificUserDataListener instead.
		 */
		class IUserDataListener : public GalaxyTypeAwareListener<USER_DATA>
		{
		public:

			/**
			 * Notification for the event of user data change.
			 */
			virtual void OnUserDataUpdated() = 0;
		};

		/**
		 * Globally self-registering version of IUserDataListener.
		 */
		typedef SelfRegisteringListener<IUserDataListener> GlobalUserDataListener;

		/**
		 * Listener for the events related to user data changes.
		 */
		class ISpecificUserDataListener : public GalaxyTypeAwareListener<SPECIFIC_USER_DATA>
		{
		public:

			/**
			 * Notification for the event of user data change.
			 *
			 * @param userID The ID of the user.
			 */
			virtual void OnSpecificUserDataUpdated(GalaxyID userID) = 0;
		};

		/**
		 * Globally self-registering version of ISpecificUserDataListener.
		 */
		typedef SelfRegisteringListener<ISpecificUserDataListener> GlobalSpecificUserDataListener;

		/**
		 * Listener for the event of retrieving a requested Encrypted App Ticket.
		 */
		class IEncryptedAppTicketListener : public GalaxyTypeAwareListener<ENCRYPTED_APP_TICKET_RETRIEVE>
		{
		public:

			/**
			 * Notification for an event of a success in retrieving the Encrypted App Ticket.
			 *
			 * In order to read the Encrypted App Ticket, call IUser::GetEncryptedAppTicket().
			 */
			virtual void OnEncryptedAppTicketRetrieveSuccess() = 0;

			/**
			 * The reason of a failure in retrieving an Encrypted App Ticket.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED = 0 ///< Unspecified error.
			};

			/**
			 * Notification for the event of a failure in retrieving an Encrypted App Ticket.
			 *
			 * @param failureReason The cause of the failure.
			 */
			virtual void OnEncryptedAppTicketRetrieveFailure(FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of IEncryptedAppTicketListener.
		 */
		typedef SelfRegisteringListener<IEncryptedAppTicketListener> GlobalEncryptedAppTicketListener;

		/**
		 * Listener for the event of a change of current access token.
		 */
		class IAccessTokenListener : public GalaxyTypeAwareListener<ACCESS_TOKEN_CHANGE>
		{
		public:

			/**
			 * Notification for an event of retrieving an access token.
			 *
			 * In order to read the access token, call IUser::GetAccessToken().
			 */
			virtual void OnAccessTokenChanged() = 0;
		};

		/**
		 * Globally self-registering version of IAccessTokenListener.
		 */
		typedef SelfRegisteringListener<IAccessTokenListener> GlobalAccessTokenListener;

		/**
		 * The interface for handling the user account.
		 */
		class IUser
		{
		public:

			virtual ~IUser()
			{
			}

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
			virtual bool SignedIn() = 0;

			/**
			 * Returns the ID of the user, provided that the user is signed in.
			 *
			 * @return The ID of the user.
			 */
			virtual GalaxyID GetGalaxyID() = 0;

			/**
			 * Initializes the Galaxy Peer with specified user credentials.
			 *
			 * This call is asynchronous. Responses come to the IAuthListener.
			 *
			 * @remark Information about being signed in or signed out also comes to
			 * the IOperationalStateChangeListener.
			 *
			 * @warning This method is only for testing purposes and is not meant
			 * to be used in production environment in any way.
			 *
			 * @param login The user's login.
			 * @param password The user's password.
			 */
			virtual void SignIn(const char* login, const char* password) = 0;

			/**
			 * Initializes the Galaxy Peer based on Steam Encrypted App Ticket.
			 *
			 * This call is asynchronous. Responses come to the IAuthListener.
			 *
			 * @remark Information about being signed in or signed out also comes to
			 * the IOperationalStateChangeListener.
			 *
			 * @param steamAppTicket The Encrypted App Ticket from the Steam API.
			 * @param steamAppTicketSize The size of the ticket.
			 * @param personaName The user's persona name, i.e. the username from Steam.
			 */
			virtual void SignIn(const void* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName) = 0;

			/**
			 * Initializes the Galaxy Peer based on Galaxy Client authentication.
			 *
			 * This call is asynchronous. Responses come to the IAuthListener.
			 *
			 * @remark Information about being signed in or signed out also comes to
			 * the IOperationalStateChangeListener.
			 *
			 * @param requireOnline Indicates if sing in with Galaxy backend is required.
			 */
			virtual void SignIn(bool requireOnline = false) = 0;

			/**
			 * Initializes the Galaxy Peer based on PS4 credentials.
			 *
			 * This call is asynchronous. Responses come to the IAuthListener.
			 *
			 * @remark Information about being signed in or signed out also comes to
			 * the IOperationalStateChangeListener.
			 *
			 * @param ps4ClientID The PlayStation 4 client ID.
			 * @param ps4TitleID The PlayStation 4 title ID.
			 * @param ps4TitleSecret The PlayStation 4 title secret.
			 * @param ps4TitleSecretLength The length of the title secret.
			 */
			virtual void SignIn(const char* ps4ClientID, const char* ps4TitleID, const char* ps4TitleSecret, uint32_t ps4TitleSecretLength) = 0;

			/**
			 * Initializes the Galaxy Peer based on XBOX ONE credentials.
			 *
			 * This call is asynchronous. Responses come to the IAuthListener.
			 *
			 * @remark Information about being signed in or signed out also comes to
			 * the IOperationalStateChangeListener.
			 *
			 * @param xboxOneUserID The XBOX ONE user ID.
			 */
			virtual void SignIn(uint32_t xboxOneUserID) = 0;

			/**
			 * Retrieves/Refreshes user data storage.
			 *
			 * This call is asynchronous. Responses come to the IUserDataListener and ISpecificUserDataListener.
			 *
			 * @param userID The ID of the user. It can be omitted when requesting for own data.
			 */
			virtual void RequestUserData(GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Returns an entry from the data storage of current user.
			 *
			 * @remark Retrieve the user data first by calling RequestUserData().
			 * @remark This call is not thread-safe as opposed to GetUserDataCopy().
			 *
			 * @param key The name of the property of the user data storage.
			 * @param userID The ID of the user. It can be omitted when reading own data.
			 * @return The value of the property, or an empty string if failed.
			 */
			virtual const char* GetUserData(const char* key, GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Copies an entry from the data storage of current user.
			 *
			 * @remark Retrieve the user data first by calling RequestUserData().
			 *
			 * @param key The name of the property of the user data storage.
			 * @param buffer The output buffer.
			 * @param bufferLength The size of the output buffer.
			 * @param userID The ID of the user. It can be omitted when reading own data.
			 */
			virtual void GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Creates or updates an entry in the user data storage.
			 *
			 * This call in asynchronous. Responses come to the IUserDataListener and ISpecificUserDataListener.
			 *
			 * @remark To clear a property, set it to an empty string.
			 *
			 * @param key The name of the property of the user data storage with the limit of 1023 bytes.
			 * @param value The value of the property to set with the limit of 4095 bytes.
			 */
			virtual void SetUserData(const char* key, const char* value) = 0;

			/**
			 * Returns the number of entries in the user data storage
			 *
			 * @remark Retrieve the user data first by calling RequestUserData().
			 *
			 * @param userID The ID of the user. It can be omitted when reading own data.
			 * @return The number of entries, or 0 if failed.
			 */
			virtual uint32_t GetUserDataCount(GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Returns a property from the user data storage by index.
			 *
			 * @remark Retrieve the user data first by calling RequestUserData().
			 *
			 * @param index Index as an integer in the range of [0, number of entries).
			 * @param key The name of the property of the user data storage.
			 * @param keyLength The length of the name of the property of the user data storage.
			 * @param value The value of the property of the user data storage.
			 * @param valueLength The length of the value of the property of the user data storage.
			 * @param userID The ID of the user. It can be omitted when reading own data.
			 * @return true if succeeded, false when there is no such property.
			 */
			virtual bool GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID = GalaxyID()) = 0;

			/**
			 * Clears a property of user data storage
			 *
			 * This is the same as calling SetUserData() and providing an empty string
			 * as the value of the property that is to be altered.
			 *
			 * This call in asynchronous. Responses come to the IUserDataListener and ISpecificUserDataListener.
			 *
			 * @param key The name of the property of the user data storage.
			 */
			virtual void DeleteUserData(const char* key) = 0;

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
			virtual bool IsLoggedOn() = 0;

			/**
			 * Performs a request for an Encrypted App Ticket.
			 *
			 * If the buffer that is supposed to take the data is too small,
			 * the Encrypted App Ticket will be truncated to its size.
			 *
			 * This call is asynchronous. Responses come to the IEncryptedAppTicketListener.
			 *
			 * @param data The additional data to be placed within the Encrypted App Ticket with the limit of 1023 bytes.
			 * @param dataSize The size of the additional data.
			 */
			virtual void RequestEncryptedAppTicket(const void* data, uint32_t dataSize) = 0;

			/**
			 * Returns the Encrypted App Ticket.
			 *
			 * @remark Retrieve an Encrypted App Ticket first by calling RequestEncryptedAppTicket().
			 *
			 * @param encryptedAppTicket The Encrypted App Ticket.
			 * @param maxEncryptedAppTicketSize The maximum size of the Encrypted App Ticket.
			 * @param currentEncryptedAppTicketSize The actual size of the Encrypted App Ticket.
			 */
			virtual void GetEncryptedAppTicket(void* encryptedAppTicket, uint32_t maxEncryptedAppTicketSize, uint32_t& currentEncryptedAppTicketSize) = 0;

			/**
			 * Initializes the Galaxy Peer with a specified server key.
			 *
			 * This call is asynchronous. Responses come to the IAuthListener.
			 *
			 * @remark Information about being signed in or signed out also comes to
			 * the IOperationalStateChangeListener.
			 *
			 * @remark Signing in with a server key is meant for server-side usage,
			 * meaning that typically there will be no user associated to the session.
			 *
			 * @warning Make sure you do not put your server key in user builds.
			 *
			 * @param serverKey The server key.
			 */
			virtual void SignIn(const char* serverKey) = 0;

			/**
			 * Returns the ID of current session.
			 *
			 * @return The session ID.
			 */
			virtual SessionID GetSessionID() = 0;

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
			virtual const char* GetAccessToken() = 0;

			/**
			 * Copies the access token for current session.
			 *
			 * @remark The access token that is used for current session might be
			 * updated in the background automatically, without any request for that.
			 * Each time the access token is updated, a notification comes to the
			 * IAccessTokenListener.
			 *
			 * @param buffer The output buffer.
			 * @param bufferLength The size of the output buffer.
			 */
			virtual void GetAccessTokenCopy(char* buffer, uint32_t bufferLength) = 0;

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
			 * @param accessToken The invalid access token.
			 * @return true if the report was accepted, false otherwise.
			 */
			virtual bool ReportInvalidAccessToken(const char* accessToken) = 0;
		};

		/** @} */
	}
}

#endif
