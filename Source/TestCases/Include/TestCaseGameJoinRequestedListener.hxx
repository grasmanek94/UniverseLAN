#pragma once

#if GALAXY_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER

#include "TestCaseClientDetails.hxx"

class GameJoinRequestedListenerImplGlobal : public galaxy::api::GlobalGameJoinRequestedListener
{
public:
	using on_game_join_requested_func_t = std::function<void(GalaxyID userID, const char* connectionString)>;

private:
	on_game_join_requested_func_t on_game_join_requested;

public:
	GameJoinRequestedListenerImplGlobal(
		on_game_join_requested_func_t on_game_join_requested = nullptr) :
		on_game_join_requested{ on_game_join_requested } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameJoinRequestedListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnGameJoinRequested(GalaxyID userID, const char* connectionString) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} connectionString: {}",
			userID, connectionString
		).c_str());


		if (on_game_join_requested != nullptr) {
			on_game_join_requested(userID, connectionString);
		}
	}
};

class GameJoinRequestedListenerImplLocal : public galaxy::api::IGameJoinRequestedListener
{
public:
	using on_game_join_requested_func_t = std::function<void(GalaxyID userID, const char* connectionString)>;

private:
	on_game_join_requested_func_t on_game_join_requested;

public:
	GameJoinRequestedListenerImplLocal(
		on_game_join_requested_func_t on_game_join_requested = nullptr) :
		on_game_join_requested{ on_game_join_requested } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameJoinRequestedListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnGameJoinRequested(GalaxyID userID, const char* connectionString) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} connectionString: {}",
			userID, connectionString
		).c_str());


		if (on_game_join_requested != nullptr) {
			on_game_join_requested(userID, connectionString);
		}
	}
};

#endif
