#include "Matchmaking.hxx"

namespace galaxy
{
	namespace api
	{
		MatchmakingImpl::MatchmakingImpl(ListenerRegistrarImpl* listeners) : listeners{ listeners }
		{}

		MatchmakingImpl::~MatchmakingImpl()
		{
		}

		void MatchmakingImpl::CreateLobby(
			LobbyType lobbyType,
			uint32_t maxMembers,
			bool joinable,
			LobbyTopologyType lobbyTopologyType,
			ILobbyCreatedListener* const lobbyCreatedListener,
			ILobbyEnteredListener* const lobbyEnteredListener) {

		}

		void MatchmakingImpl::RequestLobbyList(bool allowFullLobbies, ILobbyListListener* const listener) {

		}

		void MatchmakingImpl::AddRequestLobbyListResultCountFilter(uint32_t limit) {

		}

		void MatchmakingImpl::AddRequestLobbyListStringFilter(const char* keyToMatch, const char* valueToMatch, LobbyComparisonType comparisonType) {

		}

		void MatchmakingImpl::AddRequestLobbyListNumericalFilter(const char* keyToMatch, int32_t valueToMatch, LobbyComparisonType comparisonType) {

		}

		void MatchmakingImpl::AddRequestLobbyListNearValueFilter(const char* keyToMatch, int32_t valueToBeCloseTo) {

		}

		GalaxyID MatchmakingImpl::GetLobbyByIndex(uint32_t index) {
			return 0;
		}

		void MatchmakingImpl::JoinLobby(GalaxyID lobbyID, ILobbyEnteredListener* const listener) {

		}

		void MatchmakingImpl::LeaveLobby(GalaxyID lobbyID, ILobbyLeftListener* const listener) {

		}

		void MatchmakingImpl::SetMaxNumLobbyMembers(GalaxyID lobbyID, uint32_t maxNumLobbyMembers, ILobbyDataUpdateListener* const listener) {

		}

		uint32_t MatchmakingImpl::GetMaxNumLobbyMembers(GalaxyID lobbyID) {
			return 0;
		}

		uint32_t MatchmakingImpl::GetNumLobbyMembers(GalaxyID lobbyID) {
			return 0;
		}

		GalaxyID MatchmakingImpl::GetLobbyMemberByIndex(GalaxyID lobbyID, uint32_t index) {
			return 0;
		}

		void MatchmakingImpl::SetLobbyType(GalaxyID lobbyID, LobbyType lobbyType, ILobbyDataUpdateListener* const listener) {

		}

		LobbyType MatchmakingImpl::GetLobbyType(GalaxyID lobbyID) {
			return LOBBY_TYPE_PUBLIC;
		}

		void MatchmakingImpl::SetLobbyJoinable(GalaxyID lobbyID, bool joinable, ILobbyDataUpdateListener* const listener) {

		}

		bool MatchmakingImpl::IsLobbyJoinable(GalaxyID lobbyID) {
			return true;
		}

		void MatchmakingImpl::RequestLobbyData(GalaxyID lobbyID, ILobbyDataRetrieveListener* const listener) {

		}

		const char* MatchmakingImpl::GetLobbyData(GalaxyID lobbyID, const char* key) {
			return "";
		}

		void MatchmakingImpl::GetLobbyDataCopy(GalaxyID lobbyID, const char* key, char* buffer, uint32_t bufferLength) {

		}

		void MatchmakingImpl::SetLobbyData(GalaxyID lobbyID, const char* key, const char* value, ILobbyDataUpdateListener* const listener) {

		}

		uint32_t MatchmakingImpl::GetLobbyDataCount(GalaxyID lobbyID) {
			return 0;
		}

		bool MatchmakingImpl::GetLobbyDataByIndex(GalaxyID lobbyID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
			return false;
		}

		void MatchmakingImpl::DeleteLobbyData(GalaxyID lobbyID, const char* key, ILobbyDataUpdateListener* const listener) {

		}

		const char* MatchmakingImpl::GetLobbyMemberData(GalaxyID lobbyID, GalaxyID memberID, const char* key) {
			return "";
		}

		void MatchmakingImpl::GetLobbyMemberDataCopy(GalaxyID lobbyID, GalaxyID memberID, const char* key, char* buffer, uint32_t bufferLength) {

		}

		void MatchmakingImpl::SetLobbyMemberData(GalaxyID lobbyID, const char* key, const char* value, ILobbyMemberDataUpdateListener* const listener) {

		}

		uint32_t MatchmakingImpl::GetLobbyMemberDataCount(GalaxyID lobbyID, GalaxyID memberID) {
			return 0;
		}

		bool MatchmakingImpl::GetLobbyMemberDataByIndex(GalaxyID lobbyID, GalaxyID memberID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
			return false;
		}

		void MatchmakingImpl::DeleteLobbyMemberData(GalaxyID lobbyID, const char* key, ILobbyMemberDataUpdateListener* const listener) {

		}

		GalaxyID MatchmakingImpl::GetLobbyOwner(GalaxyID lobbyID) {
			return 0;
		}

		bool MatchmakingImpl::SendLobbyMessage(GalaxyID lobbyID, const void* data, uint32_t dataSize) {
			return false;
		}

		uint32_t MatchmakingImpl::GetLobbyMessage(GalaxyID lobbyID, uint32_t messageID, GalaxyID& senderID, char* msg, uint32_t msgLength) {
			return 0;
		}
	}
}
