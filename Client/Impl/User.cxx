/**
 * @file
 * Contains data structures and interfaces related to user account.
 */

#include "IUser.h"
#include "GalaxyID.h"
#include "IListenerRegistrar.h"

#include "User.hxx"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		 /**
		  * The interface for handling the user account.
		  */

		User::~User()
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
		bool User::SignedIn() {
			return true;
		}

		/**
		 * Returns the ID of the user, provided that the user is signed in.
		 *
		 * @return The ID of the user.
		 */
		GalaxyID User::GetGalaxyID() {
			return 0;
		}

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
		void User::SignInCredentials(const char* login, const char* password, IAuthListener* const listener) {

		}

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
		void User::SignInToken(const char* refreshToken, IAuthListener* const listener) {

		}

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
		void User::SignInLauncher(IAuthListener* const listener) {

		}

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
		void User::SignInSteam(const void* steamAppTicket, uint32_t steamAppTicketSize, const char* personaName, IAuthListener* const listener) {

		}

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
		void User::SignInEpic(const char* epicAccessToken, const char* epicUsername, IAuthListener* const listener) {

		}

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
		void User::SignInGalaxy(bool requireOnline, IAuthListener* const listener) {

		}

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
		void User::SignInUWP(IAuthListener* const listener) {

		}

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
		void User::SignInPS4(const char* ps4ClientID, IAuthListener* const listener) {

		}

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
		void User::SignInXB1(const char* xboxOneUserID, IAuthListener* const listener) {

		}

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
		void User::SignInXBLive(const char* token, const char* signature, const char* marketplaceID, const char* locale, IAuthListener* const listener) {

		}

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
		void User::SignInAnonymous(IAuthListener* const listener) {

		}

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
		void User::SignInAnonymousTelemetry(IAuthListener* const listener) {

		}

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
		void User::SignInServerKey(const char* serverKey, IAuthListener* const listener) {

		}

		/**
		 * Signs the Galaxy Peer out.
		 *
		 * This call is asynchronous. Responses come to the IAuthListener and IOperationalStateChangeListener.
		 *
		 * @remark All pending asynchronous operations will be finished immediately.
		 * Their listeners will be called with the next call to the ProcessData().
		 */
		void User::SignOut() {

		}

		/**
		 * Retrieves/Refreshes user data storage.
		 *
		 * This call is asynchronous. Responses come to the IUserDataListener and ISpecificUserDataListener.
		 *
		 * @param [in] userID The ID of the user. It can be omitted when requesting for own data.
		 * @param [in] listener The listener for specific operation.
		 */
		void User::RequestUserData(GalaxyID userID, ISpecificUserDataListener* const listener) {

		}

		/**
		 * Checks if user data exists.
		 *
		 * @pre Retrieve the user data first by calling RequestUserData().
		 *
		 * @param [in] userID The ID of the user. It can be omitted when checking for own data.
		 * @return true if user data exists, false otherwise.
		 */
		bool User::IsUserDataAvailable(GalaxyID userID) {
			return true;
		}

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
		const char* User::GetUserData(const char* key, GalaxyID userID) {
			return "";
		}

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
		void User::GetUserDataCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {

		}

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
		void User::SetUserData(const char* key, const char* value, ISpecificUserDataListener* const listener) {

		}

		/**
		 * Returns the number of entries in the user data storage
		 *
		 * @pre Retrieve the user data first by calling RequestUserData().
		 *
		 * @param [in] userID The ID of the user. It can be omitted when reading own data.
		 * @return The number of entries, or 0 if failed.
		 */
		uint32_t User::GetUserDataCount(GalaxyID userID) {
			return 0;
		}

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
		bool User::GetUserDataByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
			return false;
		}

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
		void User::DeleteUserData(const char* key, ISpecificUserDataListener* const listener) {

		}

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
		bool User::IsLoggedOn() {
			return true;
		}

		/**
		 * Performs a request for an Encrypted App Ticket.
		 *
		 * This call is asynchronous. Responses come to the IEncryptedAppTicketListener.
		 *
		 * @param [in] data The additional data to be placed within the Encrypted App Ticket with the limit of 1023 bytes.
		 * @param [in] dataSize The size of the additional data.
		 * @param [in] listener The listener for specific operation.
		 */
		void User::RequestEncryptedAppTicket(const void* data, uint32_t dataSize, IEncryptedAppTicketListener* const listener) {

		}

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
		void User::GetEncryptedAppTicket(void* encryptedAppTicket, uint32_t maxEncryptedAppTicketSize, uint32_t& currentEncryptedAppTicketSize) {

		}

		/**
		 * Returns the ID of current session.
		 *
		 * @return The session ID.
		 */
		SessionID User::GetSessionID() {
			return 0;
		}

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
		const char* User::GetAccessToken() {
			return "";
		}

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
		void User::GetAccessTokenCopy(char* buffer, uint32_t bufferLength) {

		}

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
		bool User::ReportInvalidAccessToken(const char* accessToken, const char* info) {
			return false;
		}

		/** @} */
	}
}


