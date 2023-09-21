#pragma once

#include "TestCaseClientDetails.hxx"

class LobbyEnteredListenerImplGlobal : public galaxy::api::GlobalLobbyEnteredListener
{
public:
	using on_lobby_entered_func_t = std::function<void(const GalaxyID& lobbyID, LobbyEnterResult result)>;

private:
	on_lobby_entered_func_t on_lobby_entered;

public:
	LobbyEnteredListenerImplGlobal(
		on_lobby_entered_func_t on_lobby_entered = nullptr) :
		on_lobby_entered{ on_lobby_entered } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyEnteredListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyEntered(const GalaxyID& lobbyID, LobbyEnterResult result) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} result: {}",
			lobbyID, magic_enum::enum_name(result)
		).c_str());


		if (on_lobby_entered != nullptr) {
			on_lobby_entered(lobbyID, result);
		}
	}
};

class LobbyEnteredListenerImplLocal : public galaxy::api::ILobbyEnteredListener
{
public:
	using on_lobby_entered_func_t = std::function<void(const GalaxyID& lobbyID, LobbyEnterResult result)>;

private:
	on_lobby_entered_func_t on_lobby_entered;

public:
	LobbyEnteredListenerImplLocal(
		on_lobby_entered_func_t on_lobby_entered = nullptr) :
		on_lobby_entered{ on_lobby_entered } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyEnteredListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyEntered(const GalaxyID& lobbyID, LobbyEnterResult result) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} result: {}",
			lobbyID, magic_enum::enum_name(result)
		).c_str());


		if (on_lobby_entered != nullptr) {
			on_lobby_entered(lobbyID, result);
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerLobbyEnteredListenerImplGlobal : public galaxy::api::GameServerGlobalLobbyEnteredListener
{
public:
	using on_lobby_entered_func_t = std::function<void(const GalaxyID& lobbyID, LobbyEnterResult result)>;

private:
	on_lobby_entered_func_t on_lobby_entered;

public:
	GameServerLobbyEnteredListenerImplGlobal(
		on_lobby_entered_func_t on_lobby_entered = nullptr) :
		on_lobby_entered{ on_lobby_entered } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerLobbyEnteredListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyEntered(const GalaxyID& lobbyID, LobbyEnterResult result) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} result: {}",
			lobbyID, magic_enum::enum_name(result)
		).c_str());


		if (on_lobby_entered != nullptr) {
			on_lobby_entered(lobbyID, result);
		}
	}
};

#endif
