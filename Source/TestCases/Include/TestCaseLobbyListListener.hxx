#pragma once

#include "TestCaseClientDetails.hxx"

class LobbyListListenerImplGlobal : public galaxy::api::GlobalLobbyListListener
{
public:
	using on_lobby_list_func_t = std::function<void(uint32_t lobbyCount
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
		, LobbyListResult result
#else
		, bool ioFailure
#endif
		)>;

private:
	on_lobby_list_func_t on_lobby_list;

public:
	LobbyListListenerImplGlobal(
		on_lobby_list_func_t on_lobby_list = nullptr) :
		on_lobby_list{ on_lobby_list } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyListListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyList(uint32_t lobbyCount
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
		, LobbyListResult result
#else
		, bool ioFailure
#endif
	) {
		tracer::Trace trace{ "", __FUNCTION__ };
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
		trace.write_all(std::format(
			"lobbyCount: {} result: {}",
			lobbyCount, magic_enum::enum_name(result)
		).c_str());
#else
		trace.write_all(std::format(
			"lobbyCount: {} ioFailure: {}",
			lobbyCount, ioFailure
		).c_str());
#endif


		if (on_lobby_list != nullptr) {
			on_lobby_list(lobbyCount
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
				, result
#else
				, ioFailure
#endif
			);
		}
	}
};

class LobbyListListenerImplLocal : public galaxy::api::ILobbyListListener
{
public:
	using on_lobby_list_func_t = std::function<void(uint32_t lobbyCount
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
		, LobbyListResult result
#else
		, bool ioFailure
#endif
		)>;

private:
	on_lobby_list_func_t on_lobby_list;

public:
	LobbyListListenerImplLocal(
		on_lobby_list_func_t on_lobby_list = nullptr) :
		on_lobby_list{ on_lobby_list } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyListListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyList(uint32_t lobbyCount
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
		, LobbyListResult result
#else
		, bool ioFailure
#endif
	) {
		tracer::Trace trace{ "", __FUNCTION__ };
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
		trace.write_all(std::format(
			"lobbyCount: {} result: {}",
			lobbyCount, magic_enum::enum_name(result)
		).c_str());
#else
		trace.write_all(std::format(
			"lobbyCount: {} ioFailure: {}",
			lobbyCount, ioFailure
		).c_str());
#endif


		if (on_lobby_list != nullptr) {
			on_lobby_list(lobbyCount
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LIST_RESULT
				, result
#else
				, ioFailure
#endif
			);
		}
	}

};