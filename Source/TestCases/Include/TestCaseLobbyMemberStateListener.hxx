#pragma once

#include "TestCaseClientDetails.hxx"

class LobbyMemberStateListenerImplGlobal : public galaxy::api::GlobalLobbyMemberStateListener
{
public:
	using on_lobby_member_state_changed_func_t = std::function<void(const GalaxyID& lobbyID, const GalaxyID& memberID, LobbyMemberStateChange memberStateChange)>;

private:
	on_lobby_member_state_changed_func_t on_lobby_member_state_changed;

public:
	LobbyMemberStateListenerImplGlobal(
		on_lobby_member_state_changed_func_t on_lobby_member_state_changed = nullptr) :
		on_lobby_member_state_changed{ on_lobby_member_state_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyMemberStateListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyMemberStateChanged(const GalaxyID& lobbyID, const GalaxyID& memberID, LobbyMemberStateChange memberStateChange) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} memberID: {} memberStateChange: {}",
			lobbyID, memberID, magic_enum::enum_name(memberStateChange)
		).c_str());


		if (on_lobby_member_state_changed != nullptr) {
			on_lobby_member_state_changed(lobbyID, memberID, memberStateChange);
		}
	}
};

class LobbyMemberStateListenerImplLocal : public galaxy::api::ILobbyMemberStateListener
{
public:
	using on_lobby_member_state_changed_func_t = std::function<void(const GalaxyID& lobbyID, const GalaxyID& memberID, LobbyMemberStateChange memberStateChange)>;

private:
	on_lobby_member_state_changed_func_t on_lobby_member_state_changed;

public:
	LobbyMemberStateListenerImplLocal(
		on_lobby_member_state_changed_func_t on_lobby_member_state_changed = nullptr) :
		on_lobby_member_state_changed{ on_lobby_member_state_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyMemberStateListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyMemberStateChanged(const GalaxyID& lobbyID, const GalaxyID& memberID, LobbyMemberStateChange memberStateChange) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} memberID: {} memberStateChange: {}",
			lobbyID, memberID, magic_enum::enum_name(memberStateChange)
		).c_str());


		if (on_lobby_member_state_changed != nullptr) {
			on_lobby_member_state_changed(lobbyID, memberID, memberStateChange);
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerLobbyMemberStateListenerImplGlobal : public galaxy::api::GameServerGlobalLobbyMemberStateListener
{
public:
	using on_lobby_member_state_changed_func_t = std::function<void(const GalaxyID& lobbyID, const GalaxyID& memberID, LobbyMemberStateChange memberStateChange)>;

private:
	on_lobby_member_state_changed_func_t on_lobby_member_state_changed;

public:
	GameServerLobbyMemberStateListenerImplGlobal(
		on_lobby_member_state_changed_func_t on_lobby_member_state_changed = nullptr) :
		on_lobby_member_state_changed{ on_lobby_member_state_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerLobbyMemberStateListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyMemberStateChanged(const GalaxyID& lobbyID, const GalaxyID& memberID, LobbyMemberStateChange memberStateChange) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} memberID: {} memberStateChange: {}",
			lobbyID, memberID, magic_enum::enum_name(memberStateChange)
		).c_str());


		if (on_lobby_member_state_changed != nullptr) {
			on_lobby_member_state_changed(lobbyID, memberID, memberStateChange);
		}
	}
};

#endif
