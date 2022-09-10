#include "Matchmaking.hxx"

namespace galaxy
{
	namespace api
	{

		Matchmaking::~Matchmaking()
		{
		}

		void Matchmaking::CreateLobby(
			LobbyType lobbyType,
			uint32_t maxMembers,
			bool joinable,
			LobbyTopologyType lobbyTopologyType,
			ILobbyCreatedListener* const lobbyCreatedListener,
			ILobbyEnteredListener* const lobbyEnteredListener) {

		}

		void Matchmaking::RequestLobbyList(bool allowFullLobbies, ILobbyListListener* const listener) {

		}

		void Matchmaking::AddRequestLobbyListResultCountFilter(uint32_t limit) {

		}

		void Matchmaking::AddRequestLobbyListStringFilter(const char* keyToMatch, const char* valueToMatch, LobbyComparisonType comparisonType) {

		}

		void Matchmaking::AddRequestLobbyListNumericalFilter(const char* keyToMatch, int32_t valueToMatch, LobbyComparisonType comparisonType) {

		}

		void Matchmaking::AddRequestLobbyListNearValueFilter(const char* keyToMatch, int32_t valueToBeCloseTo) {

		}

		GalaxyID Matchmaking::GetLobbyByIndex(uint32_t index) {
			return 0;
		}

		void Matchmaking::JoinLobby(GalaxyID lobbyID, ILobbyEnteredListener* const listener) {

		}

		void Matchmaking::LeaveLobby(GalaxyID lobbyID, ILobbyLeftListener* const listener) {

		}

		void Matchmaking::SetMaxNumLobbyMembers(GalaxyID lobbyID, uint32_t maxNumLobbyMembers, ILobbyDataUpdateListener* const listener) {

		}

		uint32_t Matchmaking::GetMaxNumLobbyMembers(GalaxyID lobbyID) {
			return 0;
		}

		uint32_t Matchmaking::GetNumLobbyMembers(GalaxyID lobbyID) {
			return 0;
		}

		GalaxyID Matchmaking::GetLobbyMemberByIndex(GalaxyID lobbyID, uint32_t index) {
			return 0;
		}

		void Matchmaking::SetLobbyType(GalaxyID lobbyID, LobbyType lobbyType, ILobbyDataUpdateListener* const listener) {

		}

		LobbyType Matchmaking::GetLobbyType(GalaxyID lobbyID) {
			return LOBBY_TYPE_PUBLIC;
		}

		void Matchmaking::SetLobbyJoinable(GalaxyID lobbyID, bool joinable, ILobbyDataUpdateListener* const listener) {

		}

		bool Matchmaking::IsLobbyJoinable(GalaxyID lobbyID) {
			return true;
		}

		void Matchmaking::RequestLobbyData(GalaxyID lobbyID, ILobbyDataRetrieveListener* const listener) {

		}

		const char* Matchmaking::GetLobbyData(GalaxyID lobbyID, const char* key) {
			return "";
		}

		void Matchmaking::GetLobbyDataCopy(GalaxyID lobbyID, const char* key, char* buffer, uint32_t bufferLength) {

		}

		void Matchmaking::SetLobbyData(GalaxyID lobbyID, const char* key, const char* value, ILobbyDataUpdateListener* const listener) {

		}

		uint32_t Matchmaking::GetLobbyDataCount(GalaxyID lobbyID) {
			return 0;
		}

		bool Matchmaking::GetLobbyDataByIndex(GalaxyID lobbyID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
			return false;
		}

		void Matchmaking::DeleteLobbyData(GalaxyID lobbyID, const char* key, ILobbyDataUpdateListener* const listener) {

		}

		const char* Matchmaking::GetLobbyMemberData(GalaxyID lobbyID, GalaxyID memberID, const char* key) {
			return "";
		}

		void Matchmaking::GetLobbyMemberDataCopy(GalaxyID lobbyID, GalaxyID memberID, const char* key, char* buffer, uint32_t bufferLength) {

		}

		void Matchmaking::SetLobbyMemberData(GalaxyID lobbyID, const char* key, const char* value, ILobbyMemberDataUpdateListener* const listener) {

		}

		uint32_t Matchmaking::GetLobbyMemberDataCount(GalaxyID lobbyID, GalaxyID memberID) {
			return 0;
		}

		bool Matchmaking::GetLobbyMemberDataByIndex(GalaxyID lobbyID, GalaxyID memberID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
			return false;
		}

		void Matchmaking::DeleteLobbyMemberData(GalaxyID lobbyID, const char* key, ILobbyMemberDataUpdateListener* const listener) {

		}

		GalaxyID Matchmaking::GetLobbyOwner(GalaxyID lobbyID) {
			return 0;
		}

		bool Matchmaking::SendLobbyMessage(GalaxyID lobbyID, const void* data, uint32_t dataSize) {
			return false;
		}

		uint32_t Matchmaking::GetLobbyMessage(GalaxyID lobbyID, uint32_t messageID, GalaxyID& senderID, char* msg, uint32_t msgLength) {
			return 0;
		}
	}
}


