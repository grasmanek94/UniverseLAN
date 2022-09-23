#include "Matchmaking.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>
#include <Networking/Messages.hxx>

namespace universelan::client {
	using namespace galaxy::api;
	MatchmakingImpl::MatchmakingImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		create_lobby_requests{}, create_lobby_entered_requests{}, list_lobbies_requests{},
		join_lobby_requests{}, leave_lobby_requests{}, set_max_lobby_members_requests{},
		set_lobby_type_requests{}, set_lobby_joinable_requests{}, get_lobby_data_requests{},
		set_lobby_data_requests{}, set_lobby_member_data_requests{},
		mtx{}, lobby_list{}, lobby_list_filters{ {}, 250, true },
		lobby_list_filtered{}, joined_lobby{}, lobby_list_filtered_requests{}
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
				lock_t lock{ mtx };
				lobby_list.emplace(data->lobby->GetID(), data->lobby);
				joined_lobby = data->lobby;
			}

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
			lock_t lock{ mtx };
			lobby_list_filters.allow_full = allowFullLobbies;


			lobby_list_filtered_requests.emplace(request_id, std::make_shared<LobbyFilters>(lobby_list_filters));
			lobby_list_filters = LobbyFilters{ {}, 250, true };
		}

		list_lobbies_requests.emplace(request_id, listener);

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
		auto listener = list_lobbies_requests.pop(data->request_id);
		auto filter = lobby_list_filtered_requests.pop(data->request_id);

		if (data->error) {
			listeners->NotifyAll(listener, &ILobbyListListener::OnLobbyList, (uint32_t)0, LOBBY_LIST_RESULT_ERROR);
			return;
		}

		LobbyManager::lobbies_t filtered_list_of_lobbies{};
		for (auto& entry : data->lobby_list) {
			auto lobby = entry.second;
			bool skip{ !filter->allow_full && lobby->IsFull() };

			if (!skip && !ShouldFilterOut(lobby, filter->filters)) {
				filtered_list_of_lobbies.emplace(entry.first, entry.second);

				if (filtered_list_of_lobbies.size() >= filter->max_entries) {
					break;
				}
			}
		}

		lock_t lock{ mtx };
		lobby_list = data->lobby_list;
		lobby_list_filtered = filtered_list_of_lobbies;
		listeners->NotifyAll(listener, &ILobbyListListener::OnLobbyList, (uint32_t)lobby_list_filtered.size(), LOBBY_LIST_RESULT_SUCCESS);
	}

	void MatchmakingImpl::AddRequestLobbyListResultCountFilter(uint32_t limit) {
		lock_t lock{ mtx };
		lobby_list_filters.max_entries = limit;
	}

	void MatchmakingImpl::AddRequestLobbyListStringFilter(const char* keyToMatch, const char* valueToMatch, LobbyComparisonType comparisonType) {
		lock_t lock{ mtx };

		lobby_list_filters.filters.push_back(filter_combined_t{
			keyToMatch,
			filter_entry_t{ filter_value_t{ valueToMatch }, comparisonType } }
		);
	}

	void MatchmakingImpl::AddRequestLobbyListNumericalFilter(const char* keyToMatch, int32_t valueToMatch, LobbyComparisonType comparisonType) {
		lock_t lock{ mtx };

		lobby_list_filters.filters.push_back(filter_combined_t{
			keyToMatch,
			filter_entry_t{ filter_value_t{ valueToMatch }, comparisonType } }
		);
	}

	void MatchmakingImpl::AddRequestLobbyListNearValueFilter(const char* keyToMatch, int32_t valueToBeCloseTo) {
		AddRequestLobbyListNumericalFilter(keyToMatch, valueToBeCloseTo, LOBBY_COMPARISON_TYPE_NEAR);
	}

	GalaxyID MatchmakingImpl::GetLobbyByIndex(uint32_t index) {
		lock_t lock{ mtx };

		if (lobby_list_filtered.size() < index) {
			return 0;
		}

		return container_get_by_index(lobby_list_filtered, index).first;
	}

	void MatchmakingImpl::JoinLobby(GalaxyID lobbyID, ILobbyEnteredListener* const listener) {
		uint64_t request_id = MessageUniqueID::get();

		join_lobby_requests.emplace(request_id, listener);
		intf->client->GetConnection().SendAsync(JoinLobbyMessage{ request_id, lobbyID });
	}

	void MatchmakingImpl::JoinLobbyProcessed(const std::shared_ptr<JoinLobbyMessage>& data) {
		auto listener = join_lobby_requests.pop(data->request_id);

		if (data->result == LOBBY_ENTER_RESULT_SUCCESS) {
			lock_t lock{ mtx };
			auto lobby_entry = lobby_list.find(data->lobby_id);
			assert(lobby_entry != lobby_list.end());

			joined_lobby = lobby_entry->second;
			joined_lobby->AddMember(intf->config->GetApiGalaxyID());
		}

		listeners->NotifyAll(listener, &ILobbyEnteredListener::OnLobbyEntered, data->lobby_id, data->result);
	}

	void MatchmakingImpl::LeaveLobby(GalaxyID lobbyID, ILobbyLeftListener* const listener) {
		uint64_t request_id = MessageUniqueID::get();

		leave_lobby_requests.emplace(request_id, listener);

		intf->client->GetConnection().SendAsync(LeaveLobbyMessage{ request_id, lobbyID });
	}

	void MatchmakingImpl::LeaveLobbyProcessed(const std::shared_ptr<LeaveLobbyMessage>& data) {
		auto listener = leave_lobby_requests.pop(data->request_id);

		{
			lock_t lock{ mtx };
			joined_lobby->RemoveMember(intf->config->GetApiGalaxyID());
			joined_lobby = nullptr;
		}

		listeners->NotifyAll(listener, &ILobbyLeftListener::OnLobbyLeft, data->lobby_id, data->reason);
	}

	void MatchmakingImpl::SetMaxNumLobbyMembers(GalaxyID lobbyID, uint32_t maxNumLobbyMembers, ILobbyDataUpdateListener* const listener) {
		uint64_t request_id = MessageUniqueID::get();

		set_max_lobby_members_requests.emplace(request_id, listener);
		intf->client->GetConnection().SendAsync(SetLobbyMaxMembersMessage{ request_id, lobbyID, maxNumLobbyMembers });
	}

	void MatchmakingImpl::SetLobbyMaxMembersProcessed(const std::shared_ptr<SetLobbyMaxMembersMessage>& data) {
		uint64_t request_id = MessageUniqueID::get();

		auto listener = set_max_lobby_members_requests.pop(request_id);
		if (data->success) {
			{
				lock_t lock{ mtx };
				auto lobby_entry = lobby_list.find(data->lobby_id);
				assert(lobby_entry != lobby_list.end());

				auto lobby = lobby_entry->second;
				lobby->SetMaxMembers(data->max_members);
			}
			listeners->NotifyAll(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateSuccess, data->lobby_id);
		}
		else {
			listeners->NotifyAll(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateFailure, data->lobby_id, data->fail_reason);
		}
	}

	uint32_t MatchmakingImpl::GetMaxNumLobbyMembers(GalaxyID lobbyID) {
		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetMaxMembers();
	}

	uint32_t MatchmakingImpl::GetNumLobbyMembers(GalaxyID lobbyID) {
		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetMemberCount();
	}

	GalaxyID MatchmakingImpl::GetLobbyMemberByIndex(GalaxyID lobbyID, uint32_t index) {
		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetMemberByIndex(index);
	}

	void MatchmakingImpl::SetLobbyType(GalaxyID lobbyID, LobbyType lobbyType, ILobbyDataUpdateListener* const listener) {
		uint64_t request_id = MessageUniqueID::get();

		set_lobby_type_requests.emplace(request_id, listener);
		intf->client->GetConnection().SendAsync(SetLobbyTypeMessage{ request_id, lobbyID, lobbyType });
	}

	void MatchmakingImpl::SetLobbyTypeProcessed(const std::shared_ptr<SetLobbyTypeMessage>& data) {
		uint64_t request_id = MessageUniqueID::get();

		auto listener = set_lobby_type_requests.pop(request_id);
		if (data->success) {
			{
				lock_t lock{ mtx };
				auto lobby_entry = lobby_list.find(data->lobby_id);
				assert(lobby_entry != lobby_list.end());

				auto lobby = lobby_entry->second;
				lobby->SetType(data->type);
			}
			listeners->NotifyAll(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateSuccess, data->lobby_id);
		}
		else {
			listeners->NotifyAll(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateFailure, data->lobby_id, data->fail_reason);
		}
	}

	LobbyType MatchmakingImpl::GetLobbyType(GalaxyID lobbyID) {
		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return LOBBY_TYPE_PRIVATE;
		}

		return lobby->second->GetType();
	}

	void MatchmakingImpl::SetLobbyJoinable(GalaxyID lobbyID, bool joinable, ILobbyDataUpdateListener* const listener) {
		uint64_t request_id = MessageUniqueID::get();

		set_lobby_joinable_requests.emplace(request_id, listener);
		intf->client->GetConnection().SendAsync(SetLobbyJoinableMessage{ request_id, lobbyID, joinable });
	}

	void MatchmakingImpl::SetLobbyJoinableProcessed(const std::shared_ptr<SetLobbyJoinableMessage>& data) {
		uint64_t request_id = MessageUniqueID::get();

		auto listener = set_lobby_joinable_requests.pop(request_id);
		if (data->success) {
			{
				lock_t lock{ mtx };
				auto lobby_entry = lobby_list.find(data->lobby_id);
				assert(lobby_entry != lobby_list.end());

				auto lobby = lobby_entry->second;
				lobby->SetJoinable(data->joinable);
			}
			listeners->NotifyAll(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateSuccess, data->lobby_id);
		}
		else {
			listeners->NotifyAll(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateFailure, data->lobby_id, data->fail_reason);
		}
	}

	bool MatchmakingImpl::IsLobbyJoinable(GalaxyID lobbyID) {
		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return false;
		}

		return lobby->second->IsJoinable();
	}

	void MatchmakingImpl::RequestLobbyData(GalaxyID lobbyID, ILobbyDataRetrieveListener* const listener) {
		uint64_t request_id = MessageUniqueID::get();

		get_lobby_data_requests.emplace(request_id, listener);
		intf->client->GetConnection().SendAsync(RequestLobbyDataMessage{ request_id, lobbyID });
	}

	void MatchmakingImpl::RequestLobbyDataProcessed(const std::shared_ptr<RequestLobbyDataMessage>& data) {
		auto listener = get_lobby_data_requests.pop(data->request_id);

		if (data->data) {
			{
				lock_t lock{ mtx };
				auto lobby_entry = lobby_list.find(data->lobby_id);
				assert(lobby_entry != lobby_list.end());

				auto lobby = lobby_entry->second;
				lobby->SetAllData(data->data->GetAllData());
				lobby->SetAllMemberData(data->data->GetAllMemberData());
			}

			listeners->NotifyAll(listener, &ILobbyDataRetrieveListener::OnLobbyDataRetrieveSuccess, data->lobby_id);
			listeners->NotifyAll<ILobbyDataListener>(&ILobbyDataListener::OnLobbyDataUpdated, data->lobby_id, 0);
		}
		else {
			listeners->NotifyAll(listener, &ILobbyDataRetrieveListener::OnLobbyDataRetrieveFailure, data->lobby_id, data->fail_reason);
		}
	}

	const char* MatchmakingImpl::GetLobbyData(GalaxyID lobbyID, const char* key) {
		lock_t lock{ mtx }; 
		
		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return "";
		}

		return lobby->second->GetData(key);
	}

	void MatchmakingImpl::GetLobbyDataCopy(GalaxyID lobbyID, const char* key, char* buffer, uint32_t bufferLength) {
		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return;
		}

		const char* data = lobby->second->GetData(key);
		uint32_t min_size = std::min(bufferLength, (uint32_t)strlen(data));
		std::copy_n(data, min_size, buffer);
	}

	void MatchmakingImpl::SetLobbyData(GalaxyID lobbyID, const char* key, const char* value, ILobbyDataUpdateListener* const listener) {
		uint64_t request_id = MessageUniqueID::get();

		set_lobby_data_requests.emplace(request_id, listener);
		intf->client->GetConnection().SendAsync(SetLobbyDataMessage{ request_id, lobbyID, key, value });
	}

	void MatchmakingImpl::SetLobbyDataProcessed(const std::shared_ptr<SetLobbyDataMessage>& data) {
		auto listener = set_lobby_data_requests.pop(data->request_id);

		if (data->success) {
			{
				lock_t lock{ mtx };
				auto lobby_entry = lobby_list.find(data->lobby_id);
				assert(lobby_entry != lobby_list.end());

				auto lobby = lobby_entry->second;
				lobby->SetData(data->key.c_str(), data->value.c_str());
			}

			listeners->NotifyAll(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateSuccess, data->lobby_id);
			listeners->NotifyAll<ILobbyDataListener>(&ILobbyDataListener::OnLobbyDataUpdated, data->lobby_id, 0);
		}
		else {
			listeners->NotifyAll(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateFailure, data->lobby_id, data->fail_reason);
		}
	}

	uint32_t MatchmakingImpl::GetLobbyDataCount(GalaxyID lobbyID) {
		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetDataCount();
	}

	bool MatchmakingImpl::GetLobbyDataByIndex(GalaxyID lobbyID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
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
		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return "";
		}

		return lobby->second->GetMemberData(memberID, key);
	}

	void MatchmakingImpl::GetLobbyMemberDataCopy(GalaxyID lobbyID, GalaxyID memberID, const char* key, char* buffer, uint32_t bufferLength) {
		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return;
		}

		const char* data = lobby->second->GetMemberData(memberID, key);
		uint32_t min_size = std::min(bufferLength, (uint32_t)strlen(data));
		std::copy_n(data, min_size, buffer);
	}

	void MatchmakingImpl::SetLobbyMemberData(GalaxyID lobbyID, const char* key, const char* value, ILobbyMemberDataUpdateListener* const listener) {
		uint64_t request_id = MessageUniqueID::get();

		set_lobby_member_data_requests.emplace(request_id, listener);
		intf->client->GetConnection().SendAsync(SetLobbyMemberDataMessage{ request_id, 0, lobbyID, key, value });
	}

	void MatchmakingImpl::SetLobbyMemberDataProcessed(const std::shared_ptr<SetLobbyMemberDataMessage>& data) {
		auto listener = set_lobby_member_data_requests.pop(data->request_id);

		if (data->success) {
			{
				lock_t lock{ mtx };
				auto lobby_entry = lobby_list.find(data->lobby_id);
				assert(lobby_entry != lobby_list.end());

				auto lobby = lobby_entry->second;
				lobby->SetMemberData(data->member_id, data->key.c_str(), data->value.c_str());
			}

			listeners->NotifyAll(listener, &ILobbyMemberDataUpdateListener::OnLobbyMemberDataUpdateSuccess, data->lobby_id, data->member_id);
			listeners->NotifyAll<ILobbyDataListener>(&ILobbyDataListener::OnLobbyDataUpdated, data->lobby_id, data->member_id);
		}
		else {
			listeners->NotifyAll(listener, &ILobbyMemberDataUpdateListener::OnLobbyMemberDataUpdateFailure, data->lobby_id, data->member_id, data->fail_reason);
		}
	}

	uint32_t MatchmakingImpl::GetLobbyMemberDataCount(GalaxyID lobbyID, GalaxyID memberID) {
		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetMemberDataCount(memberID);
	}

	bool MatchmakingImpl::GetLobbyMemberDataByIndex(GalaxyID lobbyID, GalaxyID memberID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
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
		lock_t lock{ mtx }; 
		
		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetOwner();
	}

	bool MatchmakingImpl::SendLobbyMessage(GalaxyID lobbyID, const void* data, uint32_t dataSize) {
		lock_t lock{ mtx }; 
		
		if (!joined_lobby) {
			return false;
		}

		return intf->client->GetConnection()
			.SendAsync(SendToLobbyMessage{ lobbyID, Lobby::Message{0, 0, std::string(static_cast<const char*>(data), dataSize) } });
	}

	void MatchmakingImpl::SendLobbyMessageProcessed(const std::shared_ptr<SendToLobbyMessage>& data) {
		if (data->message.message_id == 0) {
			return;
		}

		{
			lock_t lock{ mtx };

			auto lobby_entry = lobby_list.find(data->lobby_id);
			assert(lobby_entry != lobby_list.end());

			auto lobby = lobby_entry->second;
			lobby->AddMsg(data->message);
		}

		listeners->NotifyAll<ILobbyMessageListener>(&ILobbyMessageListener::OnLobbyMessageReceived, data->lobby_id, data->message.sender, data->message.message_id, (uint32_t)data->message.data.size());	
	}

	uint32_t MatchmakingImpl::GetLobbyMessage(GalaxyID lobbyID, uint32_t messageID, GalaxyID& senderID, char* msg, uint32_t msgLength) {
		lock_t lock{ mtx }; 
		
		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetMsg(messageID, senderID, msg, msgLength);
	}
}
