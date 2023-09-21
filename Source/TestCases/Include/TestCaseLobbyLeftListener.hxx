#pragma once

#include "TestCaseClientDetails.hxx"

class LobbyLeftListenerImplGlobal : public galaxy::api::GlobalLobbyLeftListener
{
public:
	using on_lobby_left_func_t = std::function<void(const GalaxyID& lobbyID
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		, LobbyLeaveReason leaveReason
#else
		, bool ioFailure
#endif
		)>;

private:
	on_lobby_left_func_t on_lobby_left;

public:
	LobbyLeftListenerImplGlobal(
		on_lobby_left_func_t on_lobby_left = nullptr) :
		on_lobby_left{ on_lobby_left } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyLeftListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyLeft(const GalaxyID& lobbyID
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		, LobbyLeaveReason leaveReason
#else
		, bool ioFailure
#endif
	) {
		tracer::Trace trace{ "", __FUNCTION__ };

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		trace.write_all(std::format(
			"lobbyID: {} leaveReason: {}",
			lobbyID, magic_enum::enum_name(leaveReason)
		).c_str());
#else
		trace.write_all(std::format(
			"lobbyID: {} ioFailure: {}",
			lobbyID, ioFailure
		).c_str());
#endif


		if (on_lobby_left != nullptr) {
			on_lobby_left(lobbyID
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
				, leaveReason
#else
				, ioFailure
#endif
			);
		}
	}
};

class LobbyLeftListenerImplLocal : public galaxy::api::ILobbyLeftListener
{
public:
	using on_lobby_left_func_t = std::function<void(const GalaxyID& lobbyID
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		, LobbyLeaveReason leaveReason
#else
		, bool ioFailure
#endif
		)>;

private:
	on_lobby_left_func_t on_lobby_left;

public:
	LobbyLeftListenerImplLocal(
		on_lobby_left_func_t on_lobby_left = nullptr) :
		on_lobby_left{ on_lobby_left } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyLeftListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyLeft(const GalaxyID& lobbyID
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		, LobbyLeaveReason leaveReason
#else
		, bool ioFailure
#endif
	) {
		tracer::Trace trace{ "", __FUNCTION__ };

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		trace.write_all(std::format(
			"lobbyID: {} leaveReason: {}",
			lobbyID, magic_enum::enum_name(leaveReason)
		).c_str());
#else
		trace.write_all(std::format(
			"lobbyID: {} ioFailure: {}",
			lobbyID, ioFailure
		).c_str());
#endif


		if (on_lobby_left != nullptr) {
			on_lobby_left(lobbyID
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
				, leaveReason
#else
				, ioFailure
#endif
			);
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerLobbyLeftListenerImplGlobal : public galaxy::api::GameServerGlobalLobbyLeftListener
{
public:
	using on_lobby_left_func_t = std::function<void(const GalaxyID& lobbyID
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		, LobbyLeaveReason leaveReason
#else
		, bool ioFailure
#endif
		)>;

private:
	on_lobby_left_func_t on_lobby_left;

public:
	GameServerLobbyLeftListenerImplGlobal(
		on_lobby_left_func_t on_lobby_left = nullptr) :
		on_lobby_left{ on_lobby_left } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerLobbyLeftListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyLeft(const GalaxyID& lobbyID
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		, LobbyLeaveReason leaveReason
#else
		, bool ioFailure
#endif
	) {
		tracer::Trace trace{ "", __FUNCTION__ };

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		trace.write_all(std::format(
			"lobbyID: {} leaveReason: {}",
			lobbyID, magic_enum::enum_name(leaveReason)
		).c_str());
#else
		trace.write_all(std::format(
			"lobbyID: {} ioFailure: {}",
			lobbyID, ioFailure
		).c_str());
#endif


		if (on_lobby_left != nullptr) {
			on_lobby_left(lobbyID
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
				, leaveReason
#else
				, ioFailure
#endif
			);
		}
	}
};

#endif
