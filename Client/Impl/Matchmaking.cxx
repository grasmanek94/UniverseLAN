/**
 * @file
 * Contains data structures and interfaces related to matchmaking.
 */

#include "IMatchmaking.h"
#include "GalaxyID.h"
#include "IListenerRegistrar.h"

#include "Matchmaking.hxx"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		 /**
		  * The interface for managing game lobbies.
		  */
		Matchmaking::~Matchmaking()
		{
		}

		/**
		 * Creates a lobby.
		 *
		 * Depending on the lobby type specified, the lobby will be visible for
		 * other users and joinable either for everyone or just specific users.
		 *
		 * This call is asynchronous. Responses come to the ILobbyCreatedListener,
		 * as well as ILobbyEnteredListener, provided that the lobby was created
		 * successfully, in which case the owning user enters it automatically.
		 *
		 * @param [in] lobbyType The type of the lobby.
		 * @param [in] maxMembers The maximum number of members allowed for the lobby with the limit of 250 members.
		 * @param [in] joinable Is the lobby joinable.
		 * @param [in] lobbyTopologyType The type of the lobby topology.
		 * @param [in] lobbyCreatedListener The lobby creation listener for specific operation call.
		 * @param [in] lobbyEnteredListener The lobby entering listener for specific operation call.
		 */
		void Matchmaking::CreateLobby(
			LobbyType lobbyType,
			uint32_t maxMembers,
			bool joinable,
			LobbyTopologyType lobbyTopologyType,
			ILobbyCreatedListener* const lobbyCreatedListener,
			ILobbyEnteredListener* const lobbyEnteredListener) {

		}

		/**
		 * Performs a request for a list of relevant lobbies.
		 *
		 * This call is asynchronous. When the list is received, a notification will
		 * come to the ILobbyListListener. The notification contains only the number
		 * of lobbies that were found and are available for reading.
		 *
		 * In order to read subsequent lobbies, call GetLobbyByIndex().
		 *
		 * @remark The resulting list of lobbies is filtered according to all the
		 * filters that were specified prior to this call and after the previous
		 * request for lobby list, since filters are consumed only once and not used
		 * again.
		 *
		 * @remark Full lobbies are never included in the list.
		 *
		 * @param [in] allowFullLobbies Are full lobbies allowed.
		 * @param [in] listener The listener for specific operation call.
		 */
		void Matchmaking::RequestLobbyList(bool allowFullLobbies, ILobbyListListener* const listener) {

		}

		/**
		 * Sets the maximum number of lobbies to be returned next time you call RequestLobbyList().
		 *
		 * You can add multiple filters. All filters operate on lobby properties.
		 *
		 * @remark After each call to RequestLobbyList() all filters are cleared.
		 *
		 * @param [in] limit The maximum non-zero number of lobbies to retrieve.
		 */
		void Matchmaking::AddRequestLobbyListResultCountFilter(uint32_t limit) {

		}

		/**
		 * Adds a string filter to be applied next time you call RequestLobbyList().
		 *
		 * You can add multiple filters. All filters operate on lobby properties.
		 *
		 * @remark After each call to RequestLobbyList() all filters are cleared.
		 *
		 * @param [in] keyToMatch The key to match.
		 * @param [in] valueToMatch The value to match.
		 * @param [in] comparisonType The type of comparison.
		 */
		void Matchmaking::AddRequestLobbyListStringFilter(const char* keyToMatch, const char* valueToMatch, LobbyComparisonType comparisonType) {

		}

		/**
		 * Adds a numerical filter to be applied next time you call RequestLobbyList().
		 *
		 * You can add multiple filters. All filters operate on lobby properties.
		 *
		 * @remark After each call to RequestLobbyList() all filters are cleared.
		 *
		 * @param [in] keyToMatch The key to match.
		 * @param [in] valueToMatch The value to match.
		 * @param [in] comparisonType The type of comparison.
		 */
		void Matchmaking::AddRequestLobbyListNumericalFilter(const char* keyToMatch, int32_t valueToMatch, LobbyComparisonType comparisonType) {

		}

		/**
		 * Adds a near value filter to be applied next time you call RequestLobbyList().
		 *
		 * You can add multiple filters. All filters operate on lobby properties.
		 *
		 * @remark After each call to RequestLobbyList() all filters are cleared.
		 *
		 * @param [in] keyToMatch The key to match.
		 * @param [in] valueToBeCloseTo The value to be close to.
		 */
		void Matchmaking::AddRequestLobbyListNearValueFilter(const char* keyToMatch, int32_t valueToBeCloseTo) {

		}

		/**
		 * Returns GalaxyID of a retrieved lobby by index.
		 *
		 * Use this call to iterate over last retrieved lobbies, indexed from 0.
		 *
		 * @remark This method can be used only inside of ILobbyListListener::OnLobbyList().
		 *
		 * @pre In order to retrieve lobbies and get their count, you need to call
		 * RequestLobbyList() first.
		 *
		 * @param [in] index Index as an integer in the range of [0, number of lobbies fetched).
		 * @return The ID of the lobby, valid only if the index is valid.
		 */
		GalaxyID Matchmaking::GetLobbyByIndex(uint32_t index) {
			return 0;
		}

		/**
		 * Joins a specified existing lobby.
		 *
		 * This call is asynchronous. Responses come to the ILobbyEnteredListener.
		 *
		 * For other lobby members notifications come to the ILobbyMemberStateListener.
		 *
		 * @param [in] lobbyID The ID of the lobby to join.
		 * @param [in] listener The listener for specific operation call.
		 */
		void Matchmaking::JoinLobby(GalaxyID lobbyID, ILobbyEnteredListener* const listener) {

		}

		/**
		 * Leaves a specified lobby.
		 *
		 * ILobbyLeftListener will be called when lobby is left.
		 * For other lobby members notifications come to the ILobbyMemberStateListener.
		 *
		 * Lobby data and lobby messages will not be reachable for lobby that we left.
		 *
		 * @param [in] lobbyID The ID of the lobby to leave.
		 * @param [in] listener The listener for specific operation call.
		 */
		void Matchmaking::LeaveLobby(GalaxyID lobbyID, ILobbyLeftListener* const listener) {

		}

		/**
		 * Sets the maximum number of users that can be in a specified lobby.
		 *
		 * @param [in] lobbyID The ID of the lobby to check.
		 * @param [in] maxNumLobbyMembers The maximum number of members allowed for the lobby with the limit of 250 members.
		 * @param [in] listener The listener for specific operation.
		 */
		void Matchmaking::SetMaxNumLobbyMembers(GalaxyID lobbyID, uint32_t maxNumLobbyMembers, ILobbyDataUpdateListener* const listener) {

		}

		/**
		 * Returns the maximum number of users that can be in a specified lobby.
		 *
		 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
		 *
		 * @param [in] lobbyID The ID of the lobby to check.
		 * @return The maximum number of members allowed for the lobby.
		 */
		uint32_t Matchmaking::GetMaxNumLobbyMembers(GalaxyID lobbyID) {
			return 0;
		}

		/**
		 * Returns the number of users in a specified lobby.
		 *
		 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
		 *
		 * @param [in] lobbyID The ID of the lobby to check.
		 * @return The number of members of the lobby.
		 */
		uint32_t Matchmaking::GetNumLobbyMembers(GalaxyID lobbyID) {
			return 0;
		}

		/**
		 * Returns the GalaxyID of a user in a specified lobby.
		 *
		 * @pre The user must be in the lobby in order to retrieve the lobby members.
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] index Index as an integer in the range of [0, number of lobby members).
		 * @return The ID of the lobby member, valid only if the index is valid.
		 */
		GalaxyID Matchmaking::GetLobbyMemberByIndex(GalaxyID lobbyID, uint32_t index) {
			return 0;
		}

		/**
		 * Sets the type of a specified lobby.
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] lobbyType The type of the lobby.
		 * @param [in] listener The listener for specific operation.
		 */
		void Matchmaking::SetLobbyType(GalaxyID lobbyID, LobbyType lobbyType, ILobbyDataUpdateListener* const listener) {

		}

		/**
		 * Returns the type of a specified lobby.
		 *
		 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @return lobbyType The type of the lobby.
		 */
		LobbyType Matchmaking::GetLobbyType(GalaxyID lobbyID) {
			return LOBBY_TYPE_PUBLIC;
		}

		/**
		 * Sets if a specified lobby is joinable.
		 *
		 * @remark When a lobby is not joinable, no user can join in even if there are still
		 * some empty slots for lobby members. The lobby is also hidden from matchmaking.
		 *
		 * @remark Newly created lobbies are joinable by default. Close a lobby by making it
		 * not joinable e.g. when the game has started and no new lobby members are allowed.
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] joinable Is the lobby joinable.
		 * @param [in] listener The listener for specific operation.
		 */
		void Matchmaking::SetLobbyJoinable(GalaxyID lobbyID, bool joinable, ILobbyDataUpdateListener* const listener) {

		}

		/**
		 * Checks if a specified lobby is joinable.
		 *
		 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @return If the lobby is joinable.
		 */
		bool Matchmaking::IsLobbyJoinable(GalaxyID lobbyID) {
			return true;
		}

		/**
		 * Refreshes info about a specified lobby.
		 *
		 * This is needed only for the lobbies that the user is not currently in,
		 * since for entered lobbies any info is updated automatically.
		 *
		 * This call is asynchronous. Responses come to the ILobbyDataListener and
		 * ILobbyDataRetrieveListener.
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] listener The listener for specific operation call.
		 */
		void Matchmaking::RequestLobbyData(GalaxyID lobbyID, ILobbyDataRetrieveListener* const listener) {

		}

		/**
		 * Returns an entry from the properties of a specified lobby.
		 *
		 * It returns an empty string if there is no such property of the lobby, or
		 * if the ID of the lobby is invalid.
		 *
		 * @remark This call is not thread-safe as opposed to GetLobbyDataCopy().
		 *
		 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] key The name of the property of the lobby.
		 * @return The value of the property, or an empty string if failed.
		 */
		const char* Matchmaking::GetLobbyData(GalaxyID lobbyID, const char* key) {
			return "";
		}

		/**
		 * Copies an entry from the properties of a specified lobby.
		 *
		 * It copies an empty string if there is no such property of the lobby, or
		 * if the ID of the lobby is invalid.
		 *
		 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] key The name of the property of the lobby.
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		void Matchmaking::GetLobbyDataCopy(GalaxyID lobbyID, const char* key, char* buffer, uint32_t bufferLength) {

		}

		/**
		 * Creates or updates an entry in the properties of a specified lobby.
		 *
		 * The properties can be used for matchmaking or broadcasting any lobby data
		 * (e.g. the name of the lobby) to other Galaxy Peers.
		 *
		 * The properties are assigned to the lobby and available for matchmaking.
		 * Each user that is a member of the lobby will receive a notification when
		 * the properties of the lobby are changed. The notifications come to ILobbyDataListener.
		 *
		 * Any user that joins the lobby will be able to read the data.
		 *
		 * @remark To clear a property, set it to an empty string.
		 *
		 * @pre Only the owner of the lobby can edit its properties.
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] key The name of the property of the lobby with the limit of 1023 bytes.
		 * @param [in] value The value of the property to set with the limit of 4095 bytes.
		 * @param [in] listener The listener for specific operation.
		 */
		void Matchmaking::SetLobbyData(GalaxyID lobbyID, const char* key, const char* value, ILobbyDataUpdateListener* const listener) {

		}

		/**
		 * Returns the number of entries in the properties of a specified lobby.
		 *
		 * @pre If not currently in the lobby, retrieve the data first by calling
		 * RequestLobbyData().
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @return The number of entries, or 0 if failed.
		 */
		uint32_t Matchmaking::GetLobbyDataCount(GalaxyID lobbyID) {
			return 0;
		}

		/**
		 * Returns a property of a specified lobby by index.
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] index Index as an integer in the range of [0, number of entries).
		 * @param [in, out] key The name of the property of the lobby.
		 * @param [in] keyLength The length of the name of the property of the lobby.
		 * @param [in, out] value The value of the property of the lobby.
		 * @param [in] valueLength The length of the value of the property of the lobby.
		 * @return true if succeeded, false when there is no such property.
		 */
		bool Matchmaking::GetLobbyDataByIndex(GalaxyID lobbyID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
			return false;
		}

		/**
		 * Clears a property of a specified lobby by its name.
		 *
		 * This is the same as calling SetLobbyData() and providing an empty string
		 * as the value of the property that is to be altered.
		 *
		 * Each user that is a member of the lobby will receive a notification when
		 * the properties of the lobby are changed. The notifications come to ILobbyDataListener.
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] key The name of the property of the lobby.
		 * @param [in] listener The listener for specific operation.
		 */
		void Matchmaking::DeleteLobbyData(GalaxyID lobbyID, const char* key, ILobbyDataUpdateListener* const listener) {

		}

		/**
		 * Returns an entry from the properties of a specified member
		 * of a specified lobby.
		 *
		 * It returns an empty string if there is no such property of the member of
		 * the lobby, or if any of the specified IDs are invalid (including false
		 * membership).
		 *
		 * @remark This call is not thread-safe as opposed to GetLobbyMemberDataCopy().
		 *
		 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] memberID The ID of the lobby member.
		 * @param [in] key The name of the property of the lobby member.
		 * @return The value of the property, or an empty string if failed.
		 */
		const char* Matchmaking::GetLobbyMemberData(GalaxyID lobbyID, GalaxyID memberID, const char* key) {
			return "";
		}

		/**
		 * Copies an entry from the properties of a specified member
		 * of a specified lobby.
		 *
		 * It copies an empty string if there is no such property of the member of
		 * the lobby, or if any of the specified IDs are invalid (including false
		 * membership).
		 *
		 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] memberID The ID of the lobby member.
		 * @param [in] key The name of the property of the lobby member.
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		void Matchmaking::GetLobbyMemberDataCopy(GalaxyID lobbyID, GalaxyID memberID, const char* key, char* buffer, uint32_t bufferLength) {

		}

		/**
		 * Creates or updates an entry in the user's properties (as a lobby member)
		 * in a specified lobby.
		 *
		 * The properties can be used for broadcasting any data as the lobby member data
		 * (e.g. the name of the user in the lobby) to other lobby members.
		 *
		 * The properties are assigned to the user as a lobby member in the lobby.
		 * Each user that is a member of the lobby will receive a notification when
		 * the lobby member properties are changed. The notifications come to ILobbyDataListener.
		 *
		 * Any user that joins the lobby will be able to read the data.
		 *
		 * @remark To clear a property, set it to an empty string.
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] key The name of the property of the lobby member with the limit of 1023 bytes.
		 * @param [in] value The value of the property to set with the limit of 4095 bytes.
		 * @param [in] listener The listener for specific operation.
		 */
		void Matchmaking::SetLobbyMemberData(GalaxyID lobbyID, const char* key, const char* value, ILobbyMemberDataUpdateListener* const listener) {

		}

		/**
		 * Returns the number of entries in the properties of a specified member
		 * of a specified lobby.
		 *
		 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] memberID The ID of the lobby member.
		 * @return The number of entries, or 0 if failed.
		 */
		uint32_t Matchmaking::GetLobbyMemberDataCount(GalaxyID lobbyID, GalaxyID memberID) {
			return 0;
		}

		/**
		 * Returns a property of a specified lobby member by index.
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] memberID The ID of the lobby member.
		 * @param [in] index Index as an integer in the range of [0, number of entries).
		 * @param [in, out] key The name of the property of the lobby member.
		 * @param [in] keyLength The length of the name of the property of the lobby member.
		 * @param [in, out] value The value of the property of the lobby member.
		 * @param [in] valueLength The length of the value of the property of the lobby member.
		 * @return true if succeeded, false when there is no such property.
		 */
		bool Matchmaking::GetLobbyMemberDataByIndex(GalaxyID lobbyID, GalaxyID memberID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
			return false;
		}

		/**
		 * Clears a property of a specified lobby member by its name.
		 *
		 * This is the same as calling SetLobbyMemberData() and providing an empty
		 * string as the value of the property that is to be altered.
		 *
		 * Each user that is a member of the lobby will receive a notification when
		 * the lobby member properties are changed. The notifications come to ILobbyDataListener.
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] key The name of the property of the lobby member.
		 * @param [in] listener The listener for specific operation.
		 */
		void Matchmaking::DeleteLobbyMemberData(GalaxyID lobbyID, const char* key, ILobbyMemberDataUpdateListener* const listener) {

		}

		/**
		 * Returns the owner of a specified lobby.
		 *
		 * @pre If not currently in the lobby, retrieve the data first by calling RequestLobbyData().
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @return The ID of the lobby member who is also its owner, valid only when called by a member.
		 */
		GalaxyID Matchmaking::GetLobbyOwner(GalaxyID lobbyID) {
			return 0;
		}

		/**
		 * Sends a message to all lobby members, including the sender.
		 *
		 * For all the lobby members there comes a notification to the
		 * ILobbyMessageListener. Since that moment it is possible to retrieve the
		 * message by ID using GetLobbyMessage().
		 *
		 * @pre The user needs to be in the lobby in order to send a message to its members.
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] data The data to send.
		 * @param [in] dataSize The length of the data.
		 * @return true if the message was scheduled for sending, false otherwise.
		 */
		bool Matchmaking::SendLobbyMessage(GalaxyID lobbyID, const void* data, uint32_t dataSize) {
			return false;
		}

		/**
		 * Receives a specified message from one of the members of a specified lobby.
		 *
		 * @param [in] lobbyID The ID of the lobby.
		 * @param [in] messageID The ID of the message.
		 * @param [out] senderID The ID of the sender.
		 * @param [in, out] msg The buffer to pass the data to.
		 * @param [in] msgLength The size of the buffer.
		 * @return The number of bytes written to the buffer.
		 */
		uint32_t Matchmaking::GetLobbyMessage(GalaxyID lobbyID, uint32_t messageID, GalaxyID& senderID, char* msg, uint32_t msgLength) {
			return 0;
		}

		/** @} */
	}
}


