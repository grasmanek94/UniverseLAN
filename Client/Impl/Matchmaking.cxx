#include "Matchmaking.hxx"

#include "UniverseLAN.hxx"

#include <Networking/Messages/CreateLobbyMessage.hxx>

namespace universelan::client {
	using namespace galaxy::api;
	MatchmakingImpl::MatchmakingImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		create_lobby_requests{}, create_lobby_entered_requests{}, list_lobbies_requests{},
		join_lobby_requests{}, leave_lobby_requests{}, set_max_lobby_members_requests{},
		set_lobby_type_requests{}, set_lobby_joinable_requests{}, get_lobby_data_requests{},
		set_lobby_data_requests{}, set_lobby_member_data_requests{},

		lobby_list_mtx{}, lobby_list{},

		lobby_list_filtered_mtx{}, lobby_list_filters{ {}, 250, true }, lobby_list_filtered{},

		joined_lobby_mtx{}, joined_lobby{},

		lobby_list_filtered_requests{}, lobby_list_requests{}
	{}

	MatchmakingImpl::~MatchmakingImpl() {}

	void MatchmakingImpl::CreateLobby(
		LobbyType lobbyType,
		uint32_t maxMembers,
		bool joinable,
		LobbyTopologyType lobbyTopologyType,
		ILobbyCreatedListener* const lobbyCreatedListener,
		ILobbyEnteredListener* const lobbyEnteredListener) {

		uint64_t request_id = MessageUniqueID::get();

		create_lobby_requests.emplace(request_id, lobbyCreatedListener);
		create_lobby_entered_requests.emplace(request_id, lobbyEnteredListener);

		intf->client->GetConnection().SendAsync(CreateLobbyMessage{ request_id, lobbyType, maxMembers, joinable, lobbyTopologyType });
	}

	void MatchmakingImpl::CreateLobbyProcessed(const std::shared_ptr<CreateLobbyResponseMessage>& data) {
		ILobbyCreatedListener* lobbyCreatedListener = create_lobby_requests.pop(data->request_id);
		ILobbyEnteredListener* lobbyEnteredListener = create_lobby_entered_requests.pop(data->request_id);

		if (data->lobby) {

			{
				lock_t lock{ lobby_list_mtx };
				lobby_list.emplace(data->lobby->GetID(), data->lobby);
			}

			lock_t lock{ joined_lobby_mtx };
			joined_lobby = data->lobby;

			listeners->NotifyAll(lobbyCreatedListener, &ILobbyCreatedListener::OnLobbyCreated, joined_lobby->GetID(), LobbyCreateResult::LOBBY_CREATE_RESULT_SUCCESS);
			listeners->NotifyAll(lobbyEnteredListener, &ILobbyEnteredListener::OnLobbyEntered, joined_lobby->GetID(), LobbyEnterResult::LOBBY_ENTER_RESULT_SUCCESS);
		}
		else {
			listeners->NotifyAll(lobbyCreatedListener, &ILobbyCreatedListener::OnLobbyCreated, GalaxyID(0), LobbyCreateResult::LOBBY_CREATE_RESULT_ERROR);
			// listeners->NotifyAll(lobbyEnteredListener, &ILobbyEnteredListener::OnLobbyEntered, GalaxyID(0), LobbyEnterResult::LOBBY_ENTER_RESULT_LOBBY_DOES_NOT_EXIST);
		}
	}

	void MatchmakingImpl::RequestLobbyList(bool allowFullLobbies, ILobbyListListener* const listener) {
		uint64_t request_id = MessageUniqueID::get();

		{
			lock_t lock{ lobby_list_filtered_mtx };
			lobby_list_filters.allow_full = allowFullLobbies;


			lobby_list_filtered_requests.emplace(request_id, std::make_shared<LobbyFilters>(lobby_list_filters));
			lobby_list_filters = LobbyFilters{ {}, 250, true };
		}

		lobby_list_requests.emplace(request_id, listener);

		intf->client->GetConnection().SendAsync(RequestLobbyListMessage{ request_id });
	}

	static bool ShouldFilterOut(LobbyManager::lobby_t& lobby, const MatchmakingImpl::filter_container_t& filters) {
		bool add = true;

		for (auto& filter_entry : filters) {
			auto& key = filter_entry.key;
			auto& comparison_type = filter_entry.filter.comparison_type;
			auto& specified = filter_entry.filter.value;
			auto specified_str = std::get<1>(specified);
			auto specified_i = std::get<0>(specified);
			const auto value_str = std::string(lobby->GetData(key.c_str()));

			int32_t integer_converted{ 0 };
			try {
				integer_converted = std::stol(value_str);
			}
			catch (std::out_of_range) {}

			const int32_t value_i = integer_converted;

			bool compare_str = (specified.index() != 0);

			switch (comparison_type) {
			case LOBBY_COMPARISON_TYPE_EQUAL:
				if (compare_str && (value_str != specified_str)) {
					add = false;
				}
				else if (!compare_str && (value_i != specified_i)) {
					add = false;
				}
				break;

			case LOBBY_COMPARISON_TYPE_NOT_EQUAL:
				if (compare_str && (value_str == specified_str)) {
					add = false;
				}
				else if (!compare_str && (value_i == specified_i)) {
					add = false;
				}
				break;

			case LOBBY_COMPARISON_TYPE_GREATER:
				if (compare_str && (value_str > specified_str)) {
					add = false;
				}
				else if (!compare_str && (value_i > specified_i)) {
					add = false;
				}
				break;

			case LOBBY_COMPARISON_TYPE_GREATER_OR_EQUAL:
				if (compare_str && (value_str >= specified_str)) {
					add = false;
				}
				else if (!compare_str && (value_i >= specified_i)) {
					add = false;
				}
				break;

			case LOBBY_COMPARISON_TYPE_LOWER:
				if (compare_str && (value_str < specified_str)) {
					add = false;
				}
				else if (!compare_str && (value_i < specified_i)) {
					add = false;
				}
				break;

			case LOBBY_COMPARISON_TYPE_LOWER_OR_EQUAL:
				if (compare_str && (value_str <= specified_str)) {
					add = false;
				}
				else if (!compare_str && (value_i <= specified_i)) {
					add = false;
				}
				break;

			case LOBBY_COMPARISON_TYPE_NEAR:
				// TODO: figure out what to do with this, probably calculate the difference and then sort by this (highest to lowest, lowest to highest)?
				break;
			}
		}

		return !add;
	}

	void MatchmakingImpl::RequestLobbyListProcessed(const std::shared_ptr<RequestLobbyListMessage>& data) {
		auto listener = lobby_list_requests.pop(data->request_id);
		auto filter = lobby_list_filtered_requests.pop(data->request_id);

		if (data->error) {
			listeners->NotifyAll(listener, &ILobbyListListener::OnLobbyList, (uint32_t)0, LOBBY_LIST_RESULT_ERROR);
			return;
		}

		LobbyManager::lobbies_t filtered_list_of_lobbies{};
		for (auto& entry : data->lobby_list) {

			bool add{ true };
			auto lobby = entry.second;

			if (!filter->allow_full && (lobby->GetMemberCount() >= lobby->GetMaxMembers())) {
				add = false;
			}

			if (add && ShouldFilterOut(lobby, filter->filters)) {
				add = false;
			}

			if (add) {
				filtered_list_of_lobbies.emplace(entry.first, entry.second);

				if (filtered_list_of_lobbies.size() >= filter->max_entries) {
					break;
				}
			}
		}


		lock_t lock{ lobby_list_filtered_mtx };
		lobby_list_filtered = filtered_list_of_lobbies;
		listeners->NotifyAll(listener, &ILobbyListListener::OnLobbyList, (uint32_t)lobby_list_filtered.size(), LOBBY_LIST_RESULT_SUCCESS);
	}

	void MatchmakingImpl::AddRequestLobbyListResultCountFilter(uint32_t limit) {
		lock_t lock{ lobby_list_filtered_mtx };
		lobby_list_filters.max_entries = limit;
	}

	void MatchmakingImpl::AddRequestLobbyListStringFilter(const char* keyToMatch, const char* valueToMatch, LobbyComparisonType comparisonType) {
		lock_t lock{ lobby_list_filtered_mtx };

		lobby_list_filters.filters.push_back(filter_combined_t{
			keyToMatch,
			filter_entry_t{ filter_value_t{ valueToMatch }, comparisonType } }
		);
	}

	void MatchmakingImpl::AddRequestLobbyListNumericalFilter(const char* keyToMatch, int32_t valueToMatch, LobbyComparisonType comparisonType) {
		lock_t lock{ lobby_list_filtered_mtx };

		lobby_list_filters.filters.push_back(filter_combined_t{
			keyToMatch,
			filter_entry_t{ filter_value_t{ valueToMatch }, comparisonType } }
		);
	}

	void MatchmakingImpl::AddRequestLobbyListNearValueFilter(const char* keyToMatch, int32_t valueToBeCloseTo) {
		AddRequestLobbyListNumericalFilter(keyToMatch, valueToBeCloseTo, LOBBY_COMPARISON_TYPE_NEAR);
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
