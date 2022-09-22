#include "Matchmaking.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>
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
		lock_t lock{ lobby_list_filtered_mtx };

		if (lobby_list_filtered.size() < index) {
			return 0;
		}

		return container_get_by_index(lobby_list_filtered, index).first;
	}

	void MatchmakingImpl::JoinLobby(GalaxyID lobbyID, ILobbyEnteredListener* const listener) {
		// TODO : define msg
	}

	void MatchmakingImpl::LeaveLobby(GalaxyID lobbyID, ILobbyLeftListener* const listener) {
		// TODO : define msg
	}

	void MatchmakingImpl::SetMaxNumLobbyMembers(GalaxyID lobbyID, uint32_t maxNumLobbyMembers, ILobbyDataUpdateListener* const listener) {
		// TODO : define msg
	}

	uint32_t MatchmakingImpl::GetMaxNumLobbyMembers(GalaxyID lobbyID) {
		lock_t lock{ lobby_list_filtered_mtx };

		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return 0;
		}

		return lobby->second->GetMaxMembers();
	}

	uint32_t MatchmakingImpl::GetNumLobbyMembers(GalaxyID lobbyID) {
		lock_t lock{ lobby_list_filtered_mtx };

		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return 0;
		}

		return lobby->second->GetMemberCount();
	}

	GalaxyID MatchmakingImpl::GetLobbyMemberByIndex(GalaxyID lobbyID, uint32_t index) {
		lock_t lock{ lobby_list_filtered_mtx };

		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return 0;
		}

		return lobby->second->GetMemberByIndex(index);
	}

	void MatchmakingImpl::SetLobbyType(GalaxyID lobbyID, LobbyType lobbyType, ILobbyDataUpdateListener* const listener) {
		// TODO : define msg
	}

	LobbyType MatchmakingImpl::GetLobbyType(GalaxyID lobbyID) {
		lock_t lock{ lobby_list_filtered_mtx };

		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return LOBBY_TYPE_PRIVATE;
		}

		return lobby->second->GetType();
	}

	void MatchmakingImpl::SetLobbyJoinable(GalaxyID lobbyID, bool joinable, ILobbyDataUpdateListener* const listener) {
		// TODO : define msg
	}

	bool MatchmakingImpl::IsLobbyJoinable(GalaxyID lobbyID) {
		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return false;
		}

		return lobby->second->IsJoinable();
	}

	void MatchmakingImpl::RequestLobbyData(GalaxyID lobbyID, ILobbyDataRetrieveListener* const listener) {
		// TODO : define msg
	}

	const char* MatchmakingImpl::GetLobbyData(GalaxyID lobbyID, const char* key) {
		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return "";
		}

		return lobby->second->GetData(key);
	}

	void MatchmakingImpl::GetLobbyDataCopy(GalaxyID lobbyID, const char* key, char* buffer, uint32_t bufferLength) {
		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return;
		}

		const char* data = lobby->second->GetData(key);
		uint32_t min_size = std::min(bufferLength, (uint32_t)strlen(data));
		std::copy_n(data, min_size, buffer);
	}

	void MatchmakingImpl::SetLobbyData(GalaxyID lobbyID, const char* key, const char* value, ILobbyDataUpdateListener* const listener) {
		// TODO : define msg
	}

	uint32_t MatchmakingImpl::GetLobbyDataCount(GalaxyID lobbyID) {
		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return 0;
		}

		return lobby->second->GetDataCount();
	}

	bool MatchmakingImpl::GetLobbyDataByIndex(GalaxyID lobbyID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return false;
		}

		auto data = lobby->second->GetDataByIndex(index);
		if ((data.first.size() == 0) && (data.second.size() == 0)) {
			return false;
		}

		uint32_t min_key_size = std::min(keyLength, (uint32_t)data.first.size());
		uint32_t min_value_size = std::min(valueLength, (uint32_t)data.second.size());

		std::copy_n(data.first.c_str(), min_key_size, key);
		std::copy_n(data.second.c_str(), min_value_size, value);

		return true;
	}

	void MatchmakingImpl::DeleteLobbyData(GalaxyID lobbyID, const char* key, ILobbyDataUpdateListener* const listener) {
		SetLobbyData(lobbyID, key, "", listener);
	}

	const char* MatchmakingImpl::GetLobbyMemberData(GalaxyID lobbyID, GalaxyID memberID, const char* key) {
		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return "";
		}

		return lobby->second->GetMemberData(memberID, key);
	}

	void MatchmakingImpl::GetLobbyMemberDataCopy(GalaxyID lobbyID, GalaxyID memberID, const char* key, char* buffer, uint32_t bufferLength) {
		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return;
		}

		const char* data = lobby->second->GetMemberData(memberID, key);
		uint32_t min_size = std::min(bufferLength, (uint32_t)strlen(data));
		std::copy_n(data, min_size, buffer);
	}

	void MatchmakingImpl::SetLobbyMemberData(GalaxyID lobbyID, const char* key, const char* value, ILobbyMemberDataUpdateListener* const listener) {
		// TODO : define msg
	}

	uint32_t MatchmakingImpl::GetLobbyMemberDataCount(GalaxyID lobbyID, GalaxyID memberID) {
		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return 0;
		}

		return lobby->second->GetMemberDataCount(memberID);
	}

	bool MatchmakingImpl::GetLobbyMemberDataByIndex(GalaxyID lobbyID, GalaxyID memberID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return false;
		}

		auto data = lobby->second->GetMemberDataByIndex(memberID, index);
		if ((data.first.size() == 0) && (data.second.size() == 0)) {
			return false;
		}

		uint32_t min_key_size = std::min(keyLength, (uint32_t)data.first.size());
		uint32_t min_value_size = std::min(valueLength, (uint32_t)data.second.size());

		std::copy_n(data.first.c_str(), min_key_size, key);
		std::copy_n(data.second.c_str(), min_value_size, value);

		return true;
	}

	void MatchmakingImpl::DeleteLobbyMemberData(GalaxyID lobbyID, const char* key, ILobbyMemberDataUpdateListener* const listener) {
		SetLobbyMemberData(lobbyID, key, "", listener);
	}

	GalaxyID MatchmakingImpl::GetLobbyOwner(GalaxyID lobbyID) {
		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return 0;
		}

		return lobby->second->GetOwner();
	}

	bool MatchmakingImpl::SendLobbyMessage(GalaxyID lobbyID, const void* data, uint32_t dataSize) {
		return false;
	}

	uint32_t MatchmakingImpl::GetLobbyMessage(GalaxyID lobbyID, uint32_t messageID, GalaxyID& senderID, char* msg, uint32_t msgLength) {
		auto lobby = lobby_list_filtered.find(lobbyID);
		if (lobby == lobby_list_filtered.end()) {
			return 0;
		}

		return lobby->second->GetMsg(messageID, senderID, msg, msgLength);
	}
}
