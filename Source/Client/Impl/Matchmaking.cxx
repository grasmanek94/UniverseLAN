#include "Matchmaking.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>
#include <Networking/Messages.hxx>
#include <SafeStringCopy.hxx>

namespace universelan::client {
	using namespace galaxy::api;
	MatchmakingImpl::MatchmakingImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		mtx{}, lobby_list{}, lobby_list_filters{ {}, 250, true },
		lobby_list_filtered{}, joined_lobbies{}, lobby_list_filtered_requests{}
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };
	}

	MatchmakingImpl::~MatchmakingImpl() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };
	}

	void MatchmakingImpl::CreateLobby(
		LobbyType lobbyType
		, uint32_t maxMembers
#if GALAXY_BUILD_FEATURE_HAS_LOBBYTOPOLOGYTYPE_ENUM
		, bool joinable
		, LobbyTopologyType lobbyTopologyType
#endif
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyCreatedListener* const lobbyCreatedListener
		, ILobbyEnteredListener* const lobbyEnteredListener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		listeners->AddRequestListener(request_id, lobbyCreatedListener);
		listeners->AddRequestListener(request_id, lobbyEnteredListener);
#endif
#if GALAXY_BUILD_FEATURE_HAS_NAT_FUNCTIONALITY
		listeners->NotifyAll(&INatTypeDetectionListener::OnNatTypeDetectionSuccess, galaxy::api::NatType::NAT_TYPE_PORT_RESTRICTED);
#endif

#if !GALAXY_BUILD_FEATURE_HAS_LOBBYTOPOLOGYTYPE_ENUM
		bool joinable = true;
		LobbyTopologyType lobbyTopologyType = (LobbyTopologyType)0;
#endif

		intf->client->GetConnection().SendAsync(CreateLobbyMessage{ request_id, lobbyType, maxMembers, joinable, lobbyTopologyType });
	}

	void MatchmakingImpl::CreateLobbyProcessed(const std::shared_ptr<CreateLobbyResponseMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		ILobbyCreatedListener* lobbyCreatedListener = nullptr;
		ILobbyEnteredListener* lobbyEnteredListener = nullptr;

		listeners->PopRequestListener(data->request_id, lobbyCreatedListener);
		listeners->PopRequestListener(data->request_id, lobbyEnteredListener);

		if (data->lobby) {

			{
				lock_t lock{ mtx };
				lobby_list.emplace(data->lobby->GetID(), data->lobby);
				joined_lobbies.emplace(data->lobby->GetID(), data->lobby);
			}

			// Double check if no adverse effects after changing to NotifyNow
			listeners->NotifyAllNow(lobbyCreatedListener, &ILobbyCreatedListener::OnLobbyCreated, data->lobby->GetID(), LobbyCreateResult::LOBBY_CREATE_RESULT_SUCCESS);
			listeners->NotifyAllNow(lobbyEnteredListener, &ILobbyEnteredListener::OnLobbyEntered, data->lobby->GetID(), LobbyEnterResult::LOBBY_ENTER_RESULT_SUCCESS);

			// TODO: Real Galaxy doesn't do this, maybe remove?
			//listeners->NotifyAll(&ILobbyMemberStateListener::OnLobbyMemberStateChanged, data->lobby->GetID(), intf->user->GetGalaxyID(), LobbyMemberStateChange::LOBBY_MEMBER_STATE_CHANGED_ENTERED);
		}
		else {
			listeners->NotifyAllNow(lobbyCreatedListener, &ILobbyCreatedListener::OnLobbyCreated, GalaxyID(0), LobbyCreateResult::LOBBY_CREATE_RESULT_ERROR);
			// listeners->NotifyAll(lobbyEnteredListener, &ILobbyEnteredListener::OnLobbyEntered, GalaxyID(0), LobbyEnterResult::LOBBY_ENTER_RESULT_LOBBY_DOES_NOT_EXIST);
		}
	}

	void MatchmakingImpl::RequestLobbyList(
#if GALAXY_BUILD_FEATURE_HAS_REQUESTLOBBYLIST_ARGS_ALLOWFULL
		bool allowFullLobbies
#endif
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyListListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		uint64_t request_id = MessageUniqueID::get();

		{
			lock_t lock{ mtx };
			lobby_list_filters.allow_full =
#if GALAXY_BUILD_FEATURE_HAS_REQUESTLOBBYLIST_ARGS_ALLOWFULL
				allowFullLobbies;
#else
				true;
#endif

			// create a copy
			lobby_list_filtered_requests.emplace(request_id, std::make_shared<LobbyFilters>(lobby_list_filters));

			// reset
			lobby_list_filters = LobbyFilters{ {}, 250, true };
		}

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RequestLobbyListMessage{ request_id });
	}

	static bool ShouldFilterOut(LobbyManager::lobby_t& lobby, const MatchmakingImpl::filter_container_t& filters) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		bool add = true;

		for (auto& filter_entry : filters) {
			auto& key = filter_entry.key;
			auto& comparison_type = filter_entry.filter.comparison_type;
			auto& specified = filter_entry.filter.value;
			auto specified_str = specified.index() == 1 ? std::get<1>(specified) : "";
			auto specified_i = specified.index() == 0 ? std::get<0>(specified) : (int32_t)0;
			const auto value_str = std::string(lobby->GetData(key.c_str()));

			int32_t integer_converted{ 0 };
			try {
				integer_converted = std::stol(value_str);
			}
			catch (...) {}

			const int32_t value_i = integer_converted;

			bool compare_str = (specified.index() != 0);

			switch (comparison_type) {
			case LOBBY_COMPARISON_TYPE_EQUAL:
				if (compare_str && !(value_str == specified_str)) {
					add = false;
				}
				else if (!compare_str && !(value_i == specified_i)) {
					add = false;
				}
				break;

			case LOBBY_COMPARISON_TYPE_NOT_EQUAL:
				if (compare_str && !(value_str != specified_str)) {
					add = false;
				}
				else if (!compare_str && !(value_i != specified_i)) {
					add = false;
				}
				break;

			case LOBBY_COMPARISON_TYPE_GREATER:
				if (compare_str && !(value_str > specified_str)) {
					add = false;
				}
				else if (!compare_str && !(value_i > specified_i)) {
					add = false;
				}
				break;

			case LOBBY_COMPARISON_TYPE_GREATER_OR_EQUAL:
				if (compare_str && !(value_str >= specified_str)) {
					add = false;
				}
				else if (!compare_str && !(value_i >= specified_i)) {
					add = false;
				}
				break;

			case LOBBY_COMPARISON_TYPE_LOWER:
				if (compare_str && !(value_str < specified_str)) {
					add = false;
				}
				else if (!compare_str && !(value_i < specified_i)) {
					add = false;
				}
				break;

			case LOBBY_COMPARISON_TYPE_LOWER_OR_EQUAL:
				if (compare_str && !(value_str <= specified_str)) {
					add = false;
				}
				else if (!compare_str && !(value_i <= specified_i)) {
					add = false;
				}
				break;

#if GALAXY_BUILD_FEATURE_NEAR_FILTER_ENUM
			case LOBBY_COMPARISON_TYPE_NEAR:
				// TODO: figure out what to do with this, probably calculate the difference and then sort by this (highest to lowest, lowest to highest)?
				break;
#endif

			}
		}

		return !add;
	}

	void MatchmakingImpl::RequestLobbyListProcessed(const std::shared_ptr<RequestLobbyListMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__ };

		ILobbyListListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
		auto filter = lobby_list_filtered_requests.pop(data->request_id);

		if (data->error) {
			listeners->NotifyAllNow(
				listener
				, &ILobbyListListener::OnLobbyList
				, (uint32_t)0
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
				, LOBBY_LIST_RESULT_ERROR
#else
				, true
#endif
			);
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
		listeners->NotifyAllNow(
			listener
			, &ILobbyListListener::OnLobbyList
			, (uint32_t)lobby_list_filtered.size()
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, LOBBY_LIST_RESULT_SUCCESS
#else
			, false
#endif
		);
	}

#if GALAXY_BUILD_FEATURE_MATCHMAKING_RESULT_COUNT
	void MatchmakingImpl::AddRequestLobbyListResultCountFilter(uint32_t limit) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };
		lobby_list_filters.max_entries = limit;
	}
#endif

	void MatchmakingImpl::AddRequestLobbyListStringFilter(const char* keyToMatch, const char* valueToMatch, LobbyComparisonType comparisonType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		lobby_list_filters.filters.push_back(filter_combined_t{
			keyToMatch,
			filter_entry_t{ filter_value_t{ valueToMatch }, comparisonType } }
		);
	}

	void MatchmakingImpl::AddRequestLobbyListNumericalFilter(const char* keyToMatch, int32_t valueToMatch, LobbyComparisonType comparisonType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		lobby_list_filters.filters.push_back(filter_combined_t{
			keyToMatch,
			filter_entry_t{ filter_value_t{ valueToMatch }, comparisonType } }
		);
	}

	void MatchmakingImpl::AddRequestLobbyListNearValueFilter(const char* keyToMatch, int32_t valueToBeCloseTo) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };
#if GALAXY_BUILD_FEATURE_NEAR_FILTER_ENUM
		AddRequestLobbyListNumericalFilter(keyToMatch, valueToBeCloseTo, LOBBY_COMPARISON_TYPE_NEAR);
#endif
	}

	GalaxyID MatchmakingImpl::GetLobbyByIndex(uint32_t index) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto ref = container_get_by_index(lobby_list_filtered, index);
		if (!ref) {
			return 0;
		}

		return ref->first;
	}

	void MatchmakingImpl::JoinLobby(GalaxyID lobbyID
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyEnteredListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

#if GALAXY_BUILD_FEATURE_HAS_NAT_FUNCTIONALITY
		listeners->NotifyAll(&INatTypeDetectionListener::OnNatTypeDetectionSuccess, galaxy::api::NatType::NAT_TYPE_SYMMETRIC);
#endif

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(JoinLobbyMessage{ request_id, lobbyID });
	}

	void MatchmakingImpl::JoinLobbyProcessed(const std::shared_ptr<JoinLobbyMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		ILobbyEnteredListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);

		if (data->result == LOBBY_ENTER_RESULT_SUCCESS) {
			lock_t lock{ mtx };
			auto lobby_entry = lobby_list.find(data->lobby_id);

			// Aragami2 fix?
			//assert(lobby_entry != lobby_list.end());
			if (lobby_entry == lobby_list.end()) {
				trace.write_all("LOBBY_NOT_FOUND_CREATED_DEFAULT_ENTRY");

				lobby_list.emplace(data->lobby_id, std::make_shared<Lobby>(data->lobby_id));
				lobby_entry = lobby_list.find(data->lobby_id);
			}

			joined_lobbies.emplace(lobby_entry->first, lobby_entry->second);
			lobby_entry->second->AddMember(intf->config->GetApiGalaxyID());
		}

		listeners->NotifyAllNow(listener, &ILobbyEnteredListener::OnLobbyEntered, data->lobby_id, data->result);
		//listeners->NotifyAllNow(&ILobbyMemberStateListener::OnLobbyMemberStateChanged, data->lobby_id, intf->user->GetGalaxyID(), LobbyMemberStateChange::LOBBY_MEMBER_STATE_CHANGED_ENTERED); // TODO: this is probably superfluous (or at least on some version)
	}

	void MatchmakingImpl::LeaveLobby(GalaxyID lobbyID
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyLeftListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(LeaveLobbyMessage{ request_id, lobbyID });
	}

	void MatchmakingImpl::LeaveLobbyProcessed(const std::shared_ptr<LeaveLobbyMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		ILobbyLeftListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);

		{
			lock_t lock{ mtx };
			auto joined_lobby_it = joined_lobbies.find(data->lobby_id);
			if (joined_lobby_it != joined_lobbies.end()) {
				auto joined_lobby = joined_lobby_it->second;
				if (joined_lobby != nullptr) {
					joined_lobby->RemoveMember(intf->config->GetApiGalaxyID());
				}
				joined_lobbies.erase(data->lobby_id);
			}
		}

		listeners->NotifyAllNow(
			listener
			, &ILobbyLeftListener::OnLobbyLeft
			, data->lobby_id
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, data->reason
#else
			, false
#endif
		);
	}

#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
	MATCHMAKING_RET_TYPE::type MatchmakingImpl::SetMaxNumLobbyMembers(GalaxyID lobbyID, uint32_t maxNumLobbyMembers
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyDataUpdateListener* const listener
#endif
	)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		uint64_t request_id = MessageUniqueID::get();
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif	
		intf->client->GetConnection().SendAsync(SetLobbyMaxMembersMessage{ request_id, lobbyID, maxNumLobbyMembers });

		return MATCHMAKING_RET_TYPE::value_true();
	}
#endif

	void MatchmakingImpl::SetLobbyMaxMembersProcessed(const std::shared_ptr<SetLobbyMaxMembersMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		ILobbyDataUpdateListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
#endif

		if (data->success) {
			{
				lock_t lock{ mtx };
				auto lobby_entry = lobby_list.find(data->lobby_id);
				if (lobby_entry == lobby_list.end()) {
					lobby_entry = lobby_list.emplace(data->lobby_id, std::make_shared<Lobby>(data->lobby_id)).first;
				}

				auto lobby = lobby_entry->second;
				lobby->SetMaxMembers(data->max_members);
			}

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			listeners->NotifyAllNow(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateSuccess, data->lobby_id);
#endif

			listeners->NotifyAllNow(&ILobbyDataListener::OnLobbyDataUpdated, data->lobby_id, 0);
		}
		else {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			listeners->NotifyAllNow(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateFailure, data->lobby_id, data->fail_reason);
#endif
		}
	}

	uint32_t MatchmakingImpl::GetMaxNumLobbyMembers(GalaxyID lobbyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetMaxMembers();
	}

	uint32_t MatchmakingImpl::GetNumLobbyMembers(GalaxyID lobbyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetMemberCount();
	}

	GalaxyID MatchmakingImpl::GetLobbyMemberByIndex(GalaxyID lobbyID, uint32_t index) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetMemberByIndex(index);
	}

#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
	MATCHMAKING_RET_TYPE::type MatchmakingImpl::SetLobbyType(GalaxyID lobbyID, LobbyType lobbyType
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyDataUpdateListener* const listener
#endif
	)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(SetLobbyTypeMessage{ request_id, lobbyID, lobbyType });

		return MATCHMAKING_RET_TYPE::value_true();
	}
#endif

	void MatchmakingImpl::SetLobbyTypeProcessed(const std::shared_ptr<SetLobbyTypeMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		ILobbyDataUpdateListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
#endif

		if (data->success) {
			{
				lock_t lock{ mtx };
				auto lobby_entry = lobby_list.find(data->lobby_id);
				if (lobby_entry == lobby_list.end()) {
					lobby_entry = lobby_list.emplace(data->lobby_id, std::make_shared<Lobby>(data->lobby_id)).first;
				}

				auto lobby = lobby_entry->second;
				lobby->SetType(data->type);
			}

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			listeners->NotifyAllNow(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateSuccess, data->lobby_id);
#endif

			listeners->NotifyAllNow(&ILobbyDataListener::OnLobbyDataUpdated, data->lobby_id, 0);
		}
		else {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			listeners->NotifyAllNow(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateFailure, data->lobby_id, data->fail_reason);
#endif
		}
	}

#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
	LobbyType MatchmakingImpl::GetLobbyType(GalaxyID lobbyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return galaxy::api::LobbyType::LOBBY_TYPE_PUBLIC;
		}

		return lobby->second->GetType();
	}


	MATCHMAKING_RET_TYPE::type MatchmakingImpl::SetLobbyJoinable(GalaxyID lobbyID, bool joinable
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyDataUpdateListener* const listener
#endif
	)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif	
		intf->client->GetConnection().SendAsync(SetLobbyJoinableMessage{ request_id, lobbyID, joinable });

		return MATCHMAKING_RET_TYPE::value_true();
	}
#endif

	void MatchmakingImpl::SetLobbyJoinableProcessed(const std::shared_ptr<SetLobbyJoinableMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		ILobbyDataUpdateListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
#endif

		if (data->success) {
			{
				lock_t lock{ mtx };
				auto lobby_entry = lobby_list.find(data->lobby_id);
				if (lobby_entry == lobby_list.end()) {
					lobby_entry = lobby_list.emplace(data->lobby_id, std::make_shared<Lobby>(data->lobby_id)).first;
				}

				auto lobby = lobby_entry->second;
				lobby->SetJoinable(data->joinable);
			}

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			listeners->NotifyAllNow(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateSuccess, data->lobby_id);
#endif
			listeners->NotifyAllNow(&ILobbyDataListener::OnLobbyDataUpdated, data->lobby_id, 0);
		}
		else {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			listeners->NotifyAllNow(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateFailure, data->lobby_id, data->fail_reason);
#endif
		}
	}

#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
	bool MatchmakingImpl::IsLobbyJoinable(GalaxyID lobbyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return false;
		}

		return lobby->second->IsJoinable();
	}
#endif

	MATCHMAKING_RET_TYPE::type MatchmakingImpl::RequestLobbyData(GalaxyID lobbyID
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyDataRetrieveListener* const listener
#endif
	)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RequestLobbyDataMessage{ request_id, lobbyID });

		return MATCHMAKING_RET_TYPE::value_true();
	}

	void MatchmakingImpl::RequestLobbyDataProcessed(const std::shared_ptr<RequestLobbyDataMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

#if GALAXY_BUILD_FEATURE_HAS_ILOBBYDATARETRIEVELISTENER
		ILobbyDataRetrieveListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
#endif

		if (data->data) {
			{
				lock_t lock{ mtx };
				auto lobby_entry = lobby_list.find(data->lobby_id);
				if (lobby_entry == lobby_list.end()) {
					lobby_entry = lobby_list.emplace(data->lobby_id, data->data).first;
				}

				auto lobby = lobby_entry->second;
				lobby->SetAllData(data->data->GetAllData());
				lobby->SetAllMemberData(data->data->GetAllMemberData());
			}

#if GALAXY_BUILD_FEATURE_HAS_ILOBBYDATARETRIEVELISTENER
			listeners->NotifyAllNow(listener, &ILobbyDataRetrieveListener::OnLobbyDataRetrieveSuccess, data->lobby_id);
#endif
			listeners->NotifyAllNow(&ILobbyDataListener::OnLobbyDataUpdated, data->lobby_id, 0);
		}
		else {
#if GALAXY_BUILD_FEATURE_HAS_ILOBBYDATARETRIEVELISTENER
			listeners->NotifyAllNow(listener, &ILobbyDataRetrieveListener::OnLobbyDataRetrieveFailure, data->lobby_id, data->fail_reason);
#endif
		}
	}

	const char* MatchmakingImpl::GetLobbyData(GalaxyID lobbyID, const char* key) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return "";
		}

		return lobby->second->GetData(key);
	}

#if GALAXY_BUILD_FEATURE_IMATCHMAKING_GET_DATA_MEMBER_COPY
	void MatchmakingImpl::GetLobbyDataCopy(GalaxyID lobbyID, const char* key, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return;
		}

		const char* data = lobby->second->GetData(key);
		universelan::util::safe_copy_str_n(data, buffer, bufferLength);
	}
#endif

	MATCHMAKING_RET_TYPE::type MatchmakingImpl::SetLobbyData(GalaxyID lobbyID, const char* key, const char* value
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyDataUpdateListener* const listener
#endif
	)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(SetLobbyDataMessage{ request_id, lobbyID, key, value });

		return MATCHMAKING_RET_TYPE::value_true();
	}

	void MatchmakingImpl::SetLobbyDataProcessed(const std::shared_ptr<SetLobbyDataMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		ILobbyDataUpdateListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
#endif

		if (data->success) {
			{
				lock_t lock{ mtx };
				auto lobby_entry = lobby_list.find(data->lobby_id);
				if (lobby_entry == lobby_list.end()) {
					lobby_entry = lobby_list.emplace(data->lobby_id, std::make_shared<Lobby>(data->lobby_id)).first;
				}

				auto lobby = lobby_entry->second;
				lobby->SetData(data->key.c_str(), data->value.c_str());
			}

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			listeners->NotifyAllNow(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateSuccess, data->lobby_id);
#endif
			listeners->NotifyAllNow(&ILobbyDataListener::OnLobbyDataUpdated, data->lobby_id, 0);
		}
		else {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			listeners->NotifyAllNow(listener, &ILobbyDataUpdateListener::OnLobbyDataUpdateFailure, data->lobby_id, data->fail_reason);
#endif
		}
	}

	uint32_t MatchmakingImpl::GetLobbyDataCount(GalaxyID lobbyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetDataCount();
	}

	bool MatchmakingImpl::GetLobbyDataByIndex(GalaxyID lobbyID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return false;
		}

		auto data = lobby->second->GetDataByIndex(index);
		if ((data.first.size() == 0) && (data.second.size() == 0)) {
			return false;
		}

		universelan::util::safe_copy_str_n(data.first, key, keyLength);
		universelan::util::safe_copy_str_n(data.second, value, valueLength);

		return true;
	}


	MATCHMAKING_RET_TYPE::type MatchmakingImpl::DeleteLobbyData(GalaxyID lobbyID, const char* key
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyDataUpdateListener* const listener
#endif
	)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };


		SetLobbyData(lobbyID, key, ""
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, listener
#endif
		);

		return MATCHMAKING_RET_TYPE::value_true();
	}

	const char* MatchmakingImpl::GetLobbyMemberData(GalaxyID lobbyID, GalaxyID memberID, const char* key) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return "";
		}

		return lobby->second->GetMemberData(memberID, key);
	}

#if GALAXY_BUILD_FEATURE_IMATCHMAKING_GET_DATA_MEMBER_COPY
	void MatchmakingImpl::GetLobbyMemberDataCopy(GalaxyID lobbyID, GalaxyID memberID, const char* key, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return;
		}

		const char* data = lobby->second->GetMemberData(memberID, key);
		universelan::util::safe_copy_str_n(data, buffer, bufferLength);
	}
#endif

	void MatchmakingImpl::SetLobbyMemberData(GalaxyID lobbyID, const char* key, const char* value
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyMemberDataUpdateListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		listeners->AddRequestListener(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(SetLobbyMemberDataMessage{ request_id, lobbyID, 0, key, value });
	}

	void MatchmakingImpl::SetLobbyMemberDataProcessed(const std::shared_ptr<SetLobbyMemberDataMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		ILobbyMemberDataUpdateListener* listener = nullptr;
		listeners->PopRequestListener(data->request_id, listener);
#endif

		if (data->success) {
			{
				lock_t lock{ mtx };
				auto lobby_entry = lobby_list.find(data->lobby_id);
				if (lobby_entry == lobby_list.end()) {
					lobby_entry = lobby_list.emplace(data->lobby_id, std::make_shared<Lobby>(data->lobby_id)).first;
				}

				auto lobby = lobby_entry->second;
				lobby->SetMemberData(data->member_id, data->key.c_str(), data->value.c_str());
			}

#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			listeners->NotifyAllNow(listener, &ILobbyMemberDataUpdateListener::OnLobbyMemberDataUpdateSuccess, data->lobby_id, data->member_id);
#endif

			listeners->NotifyAllNow(&ILobbyDataListener::OnLobbyDataUpdated, data->lobby_id, data->member_id);
		}
		else {
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			listeners->NotifyAllNow(listener, &ILobbyMemberDataUpdateListener::OnLobbyMemberDataUpdateFailure, data->lobby_id, data->member_id, data->fail_reason);
#endif
		}
	}

	uint32_t MatchmakingImpl::GetLobbyMemberDataCount(GalaxyID lobbyID, GalaxyID memberID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetMemberDataCount(memberID);
	}

	bool MatchmakingImpl::GetLobbyMemberDataByIndex(GalaxyID lobbyID, GalaxyID memberID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return false;
		}

		auto data = lobby->second->GetMemberDataByIndex(memberID, index);
		if ((data.first.size() == 0) && (data.second.size() == 0)) {
			return false;
		}

		universelan::util::safe_copy_str_n(data.first, key, keyLength);
		universelan::util::safe_copy_str_n(data.second, value, valueLength);

		return true;
	}

	void MatchmakingImpl::DeleteLobbyMemberData(GalaxyID lobbyID, const char* key
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyMemberDataUpdateListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		SetLobbyMemberData(lobbyID, key, ""
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, listener
#endif
		);
	}

	GalaxyID MatchmakingImpl::GetLobbyOwner(GalaxyID lobbyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetOwner();
	}

	bool MatchmakingImpl::SendLobbyMessage(GalaxyID lobbyID, SEND_LOBBY_MESSAGE_DATA_T* data, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto joined_lobby_ptr = joined_lobbies.find(lobbyID);
		if (joined_lobby_ptr == joined_lobbies.end()) {
			return false;
		}

		return intf->client->GetConnection()
			.SendAsync(SendToLobbyMessage{ lobbyID, Lobby::Message{0, 0, std::string(static_cast<const char*>(data), dataSize) } });
	}

	void MatchmakingImpl::SendLobbyMessageProcessed(const std::shared_ptr<SendToLobbyMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		if (data->message.message_id == 0) {
			return;
		}

		{
			lock_t lock{ mtx };

			auto lobby_entry = lobby_list.find(data->lobby_id);
			if (lobby_entry != lobby_list.end()) {
				auto lobby = lobby_entry->second;
				lobby->AddMsg(data->message);
			}
		}

		listeners->NotifyAllNow(&ILobbyMessageListener::OnLobbyMessageReceived, data->lobby_id, data->message.sender, data->message.message_id, (uint32_t)data->message.data.size());
	}

	uint32_t MatchmakingImpl::GetLobbyMessage(GalaxyID lobbyID, uint32_t messageID, GalaxyID& senderID, char* msg, uint32_t msgLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		lock_t lock{ mtx };

		auto lobby = lobby_list.find(lobbyID);
		if (lobby == lobby_list.end()) {
			return 0;
		}

		return lobby->second->GetMsg(messageID, senderID, msg, msgLength);
	}

	void MatchmakingImpl::LobbyMemberStateChange(const std::shared_ptr<LobbyMemberStateChangeMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		{
			lock_t lock{ mtx };

			auto lobby_entry = lobby_list.find(data->lobby_id);
			if (lobby_entry != lobby_list.end()) {
				auto lobby = lobby_entry->second;

				switch (data->state) {
				case LOBBY_MEMBER_STATE_CHANGED_ENTERED:
					lobby->AddMember(data->member_id);
					break;

				case LOBBY_MEMBER_STATE_CHANGED_DISCONNECTED:
				case LOBBY_MEMBER_STATE_CHANGED_BANNED:
				case LOBBY_MEMBER_STATE_CHANGED_KICKED:
				case LOBBY_MEMBER_STATE_CHANGED_LEFT:
					lobby->RemoveMember(data->member_id);
					break;
				}
			}
		}

		listeners->NotifyAll(&ILobbyMemberStateListener::OnLobbyMemberStateChanged, data->lobby_id, data->member_id, data->state);
	}

	void MatchmakingImpl::LobbyOwnerChange(const std::shared_ptr<LobbyOwnerChangeMessage>& data) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::IMATCHMAKING };

		{
			lock_t lock{ mtx };

			auto lobby_entry = lobby_list.find(data->lobby_id);
			if (lobby_entry != lobby_list.end()) {
				auto lobby = lobby_entry->second;
				lobby->SetOwner(data->member_id);
			}
		}

		listeners->NotifyAll(&ILobbyOwnerChangeListener::OnLobbyOwnerChanged, data->lobby_id, data->member_id);
	}
}
