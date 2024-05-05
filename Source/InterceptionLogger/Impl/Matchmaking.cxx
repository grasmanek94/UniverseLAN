#include "Matchmaking.hxx"

#include "Listeners/MatchmakingListener.hxx"

#include <GalaxyID.hxx>
#include <Tracer.hxx>
#include <SafeStringCopy.hxx>

#include <magic_enum/magic_enum.hpp>

#include <format>

namespace universelan::client {
	using namespace galaxy::api;

	namespace {
		const auto TraceContext = tracer::Trace::IMATCHMAKING;
	}

	MatchmakingImpl::MatchmakingImpl(FuncT::F intf, IListenerRegistrar* notifications) :
		intf{ intf },
		notifications{ notifications },
		listeners{ notifications } {
		listeners.AddListener<LobbyListListener>();
		listeners.AddListener<LobbyCreatedListener>();
		listeners.AddListener<LobbyEnteredListener>();
		listeners.AddListener<LobbyLeftListener>();
		listeners.AddListener<LobbyDataListener>();
		listeners.AddListener<LobbyDataUpdateListener>();
		listeners.AddListener<LobbyMemberDataUpdateListener>();
		listeners.AddListener<LobbyDataRetrieveListener>();
		listeners.AddListener<LobbyMemberStateListener>();
		listeners.AddListener<LobbyOwnerChangeListener>();
		listeners.AddListener<LobbyMessageListener>();
	}

	MatchmakingImpl::~MatchmakingImpl() {
		listeners.UnregisterAllListeners();
	}

	void MatchmakingImpl::CreateLobby(
		LobbyType lobbyType
		, uint32_t maxMembers
#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
		, bool joinable
		, LobbyTopologyType lobbyTopologyType
#endif
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyCreatedListener* const lobbyCreatedListener
		, ILobbyEnteredListener* const lobbyEnteredListener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyType: {}", magic_enum::enum_name(lobbyType)));
			trace.write_all(std::format("maxMembers: {}", maxMembers));
#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
			trace.write_all(std::format("maxMembers: {}", joinable));
			trace.write_all(std::format("lobbyTopologyType: {}", magic_enum::enum_name(lobbyTopologyType)));
#endif
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			trace.write_all(std::format("lobbyCreatedListener: {}", (void*)lobbyCreatedListener));
			trace.write_all(std::format("lobbyEnteredListener: {}", (void*)lobbyEnteredListener));
#endif
		}

		intf()->CreateLobby(lobbyType, maxMembers
#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
			, joinable
			, lobbyTopologyType
#endif	
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, lobbyCreatedListener
			, lobbyEnteredListener
#endif
		);
	}

	void MatchmakingImpl::RequestLobbyList(
#if GALAXY_BUILD_FEATURE_HAS_REQUESTLOBBYLIST_ARGS_ALLOWFULL
		bool allowFullLobbies
#endif
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyListListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
#if GALAXY_BUILD_FEATURE_HAS_REQUESTLOBBYLIST_ARGS_ALLOWFULL
			trace.write_all(std::format("allowFullLobbies: {}", allowFullLobbies));
#endif
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif	
		}

		intf()->RequestLobbyList(
#if GALAXY_BUILD_FEATURE_HAS_REQUESTLOBBYLIST_ARGS_ALLOWFULL
			allowFullLobbies
#endif
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, listener
#endif
		);
	}

#if GALAXY_BUILD_FEATURE_MATCHMAKING_RESULT_COUNT
	void MatchmakingImpl::AddRequestLobbyListResultCountFilter(uint32_t limit) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("limit: {}", limit));
		}

		intf()->AddRequestLobbyListResultCountFilter(limit);
	}
#endif

	void MatchmakingImpl::AddRequestLobbyListStringFilter(const char* keyToMatch, const char* valueToMatch, LobbyComparisonType comparisonType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("keyToMatch: {}", util::safe_fix_null_char_ptr_annotate_ret(keyToMatch)));
			trace.write_all(std::format("valueToMatch: {}", util::safe_fix_null_char_ptr_annotate_ret(valueToMatch)));
			trace.write_all(std::format("comparisonType: {}", magic_enum::enum_name(comparisonType)));
		}

		intf()->AddRequestLobbyListStringFilter(keyToMatch, valueToMatch, comparisonType);
	}

	void MatchmakingImpl::AddRequestLobbyListNumericalFilter(const char* keyToMatch, int32_t valueToMatch, LobbyComparisonType comparisonType) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("keyToMatch: {}", util::safe_fix_null_char_ptr_annotate_ret(keyToMatch)));
			trace.write_all(std::format("valueToMatch: {}", valueToMatch));
			trace.write_all(std::format("comparisonType: {}", magic_enum::enum_name(comparisonType)));
		}

		intf()->AddRequestLobbyListNumericalFilter(keyToMatch, valueToMatch, comparisonType);
	}

	void MatchmakingImpl::AddRequestLobbyListNearValueFilter(const char* keyToMatch, int32_t valueToBeCloseTo) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("keyToMatch: {}", util::safe_fix_null_char_ptr_annotate_ret(keyToMatch)));
			trace.write_all(std::format("valueToBeCloseTo: {}", valueToBeCloseTo));
		}

		intf()->AddRequestLobbyListNearValueFilter(keyToMatch, valueToBeCloseTo);
	}

	GalaxyID MatchmakingImpl::GetLobbyByIndex(uint32_t index) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("index: {}", index));
		}

		auto result = intf()->GetLobbyByIndex(index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	void MatchmakingImpl::JoinLobby(GalaxyID lobbyID
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyEnteredListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->JoinLobby(lobbyID
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, listener
#endif
		);
	}

	void MatchmakingImpl::LeaveLobby(GalaxyID lobbyID
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyLeftListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->LeaveLobby(lobbyID
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, listener
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
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("maxNumLobbyMembers: {}", maxNumLobbyMembers));
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

#if !GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
		auto result =
#endif
			intf()->SetMaxNumLobbyMembers(lobbyID, maxNumLobbyMembers
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
				, listener
#endif
			);

#if !GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
#endif
	}
#endif

	uint32_t MatchmakingImpl::GetMaxNumLobbyMembers(GalaxyID lobbyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
		}

		auto result = intf()->GetMaxNumLobbyMembers(lobbyID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	uint32_t MatchmakingImpl::GetNumLobbyMembers(GalaxyID lobbyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
		}

		auto result = intf()->GetNumLobbyMembers(lobbyID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	GalaxyID MatchmakingImpl::GetLobbyMemberByIndex(GalaxyID lobbyID, uint32_t index) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("index: {}", index));
		}

		auto result = intf()->GetLobbyMemberByIndex(lobbyID, index);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
	MATCHMAKING_RET_TYPE::type MatchmakingImpl::SetLobbyType(GalaxyID lobbyID, LobbyType lobbyType
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyDataUpdateListener* const listener
#endif
	)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("lobbyType: {}", magic_enum::enum_name(lobbyType)));
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

#if !GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
		auto result =
#endif
			intf()->SetLobbyType(lobbyID, lobbyType
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
				, listener
#endif
			);

#if !GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
#endif
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
	LobbyType MatchmakingImpl::GetLobbyType(GalaxyID lobbyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
		}

		auto result = intf()->GetLobbyType(lobbyID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", magic_enum::enum_name(result)));
		}

		return result;
	}


	MATCHMAKING_RET_TYPE::type MatchmakingImpl::SetLobbyJoinable(GalaxyID lobbyID, bool joinable
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyDataUpdateListener* const listener
#endif
	)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("joinable: {}", joinable));
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

#if !GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
		auto result =
#endif
			intf()->SetLobbyJoinable(lobbyID, joinable
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
				, listener
#endif
			);

#if !GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
#endif
	}
#endif

#if GALAXY_BUILD_FEATURE_HAS_1_73_LOBBY_FEATURES
	bool MatchmakingImpl::IsLobbyJoinable(GalaxyID lobbyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
		}

		auto result = intf()->IsLobbyJoinable(lobbyID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}
#endif

	MATCHMAKING_RET_TYPE::type MatchmakingImpl::RequestLobbyData(GalaxyID lobbyID
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyDataRetrieveListener* const listener
#endif
	)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

#if !GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
		auto result =
#endif
			intf()->RequestLobbyData(lobbyID
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
				, listener
#endif
			);

#if !GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
#endif
	}

	const char* MatchmakingImpl::GetLobbyData(GalaxyID lobbyID, const char* key) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
		}

		auto result = intf()->GetLobbyData(lobbyID, key);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_IMATCHMAKING_GET_DATA_MEMBER_COPY
	void MatchmakingImpl::GetLobbyDataCopy(GalaxyID lobbyID, const char* key, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		intf()->GetLobbyDataCopy(lobbyID, key, buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}
#endif

	MATCHMAKING_RET_TYPE::type MatchmakingImpl::SetLobbyData(GalaxyID lobbyID, const char* key, const char* value
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyDataUpdateListener* const listener
#endif
	)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
			trace.write_all(std::format("value: {}", util::safe_fix_null_char_ptr_annotate_ret(value)));
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

#if !GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
		auto result =
#endif
			intf()->SetLobbyData(lobbyID, key, value
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
				, listener
#endif
			);

#if !GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
#endif
	}

	uint32_t MatchmakingImpl::GetLobbyDataCount(GalaxyID lobbyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
		}

		auto result = intf()->GetLobbyDataCount(lobbyID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	bool MatchmakingImpl::GetLobbyDataByIndex(GalaxyID lobbyID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("index: {}", index));
			trace.write_all(std::format("key: {}", (void*)key));
			trace.write_all(std::format("keyLength: {}", keyLength));
			trace.write_all(std::format("value: {}", (void*)value));
			trace.write_all(std::format("valueLength: {}", valueLength));
		}

		auto result = intf()->GetLobbyDataByIndex(lobbyID, index, key, keyLength, value, valueLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate(key, keyLength)));
			trace.write_all(std::format("value: {}", util::safe_fix_null_char_ptr_annotate(value, valueLength)));
		}

		return result;
	}


	MATCHMAKING_RET_TYPE::type MatchmakingImpl::DeleteLobbyData(GalaxyID lobbyID, const char* key
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyDataUpdateListener* const listener
#endif
	)
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

#if !GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
		auto result =
#endif
			intf()->DeleteLobbyData(lobbyID, key
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
				, listener
#endif
			);

#if !GALAXY_BUILD_FEATURE_MATCHMAKING_RET_TYPE_VOID
		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
#endif
	}

	const char* MatchmakingImpl::GetLobbyMemberData(GalaxyID lobbyID, GalaxyID memberID, const char* key) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("lobbyID: {}", memberID));
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
		}

		auto result = intf()->GetLobbyMemberData(lobbyID, memberID, key);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", util::safe_fix_null_char_ptr_annotate_ret(result)));
		}

		return result;
	}

#if GALAXY_BUILD_FEATURE_IMATCHMAKING_GET_DATA_MEMBER_COPY
	void MatchmakingImpl::GetLobbyMemberDataCopy(GalaxyID lobbyID, GalaxyID memberID, const char* key, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("lobbyID: {}", memberID));
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
			trace.write_all(std::format("buffer: {}", (void*)buffer));
			trace.write_all(std::format("bufferLength: {}", bufferLength));
		}

		intf()->GetLobbyMemberDataCopy(lobbyID, memberID, key, buffer, bufferLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("buffer: {}", util::safe_fix_null_char_ptr_annotate(buffer, bufferLength)));
		}
	}
#endif

	void MatchmakingImpl::SetLobbyMemberData(GalaxyID lobbyID, const char* key, const char* value
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyMemberDataUpdateListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
			trace.write_all(std::format("value: {}", util::safe_fix_null_char_ptr_annotate_ret(value)));
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

		intf()->SetLobbyMemberData(lobbyID, key, value
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			, listener
#endif
		);
	}

	uint32_t MatchmakingImpl::GetLobbyMemberDataCount(GalaxyID lobbyID, GalaxyID memberID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("memberID: {}", memberID));
		}

		auto result = intf()->GetLobbyMemberDataCount(lobbyID, memberID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	bool MatchmakingImpl::GetLobbyMemberDataByIndex(GalaxyID lobbyID, GalaxyID memberID, uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("memberID: {}", memberID));
			trace.write_all(std::format("index: {}", index));
			trace.write_all(std::format("key: {}", (void*)key));
			trace.write_all(std::format("keyLength: {}", keyLength));
			trace.write_all(std::format("value: {}", (void*)value));
			trace.write_all(std::format("valueLength: {}", valueLength));
		}

		auto result = intf()->GetLobbyMemberDataByIndex(lobbyID, memberID, index, key, keyLength, value, valueLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate(key, keyLength)));
			trace.write_all(std::format("value: {}", util::safe_fix_null_char_ptr_annotate(value, valueLength)));
		}

		return result;
	}

	void MatchmakingImpl::DeleteLobbyMemberData(GalaxyID lobbyID, const char* key
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
		, ILobbyMemberDataUpdateListener* const listener
#endif
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("key: {}", util::safe_fix_null_char_ptr_annotate_ret(key)));
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
			trace.write_all(std::format("listener: {}", (void*)listener));
#endif
		}

			intf()->DeleteLobbyMemberData(lobbyID, key
#if GALAXY_BUILD_FEATURE_LOBBY_LISTENERS
				, listener
#endif
			);
	}

	GalaxyID MatchmakingImpl::GetLobbyOwner(GalaxyID lobbyID) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
		}

		auto result = intf()->GetLobbyOwner(lobbyID);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	bool MatchmakingImpl::SendLobbyMessage(GalaxyID lobbyID, SEND_LOBBY_MESSAGE_DATA_T* data, uint32_t dataSize) {
		tracer::Trace trace{ nullptr, __FUNCTION__, TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("data: {}", (void*)data));
			trace.write_all(std::format("dataSize: {}", dataSize));
		}

		auto result = intf()->SendLobbyMessage(lobbyID, data, dataSize);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
		}

		return result;
	}

	uint32_t MatchmakingImpl::GetLobbyMessage(GalaxyID lobbyID, uint32_t messageID, GalaxyID& senderID, char* msg, uint32_t msgLength) {
		tracer::Trace trace{ nullptr, __FUNCTION__,  TraceContext | tracer::Trace::HIGH_FREQUENCY_CALLS };

		if (trace.has_flags(tracer::Trace::ARGUMENTS)) {
			trace.write_all(std::format("lobbyID: {}", lobbyID));
			trace.write_all(std::format("messageID: {}", messageID));
			trace.write_all(std::format("msg: {}", (void*)msg));
			trace.write_all(std::format("msgLength: {}", msgLength));
		}

		auto result = intf()->GetLobbyMessage(lobbyID, messageID, senderID, msg, msgLength);

		if (trace.has_flags(tracer::Trace::RETURN_VALUES)) {
			trace.write_all(std::format("result: {}", result));
			trace.write_all(std::format("msg: {}", util::safe_fix_null_char_ptr_annotate(msg, std::min(result, msgLength))));
		}

		return result;
	}
}
