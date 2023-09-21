#pragma once

#include "TestCaseClientDetails.hxx"

class LobbyCreatedListenerImplGlobal : public galaxy::api::GlobalLobbyCreatedListener
{
public:
	using on_lobby_created_func_t = std::function<void(const GalaxyID& lobbyID, LobbyCreateResult result)>;

private:
	on_lobby_created_func_t on_lobby_created;

public:
	LobbyCreatedListenerImplGlobal(
		on_lobby_created_func_t on_lobby_created = nullptr) :
		on_lobby_created{ on_lobby_created } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyCreatedListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyCreated(const GalaxyID& lobbyID, LobbyCreateResult result) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} result: {}",
			lobbyID, magic_enum::enum_name(result)
		).c_str());


		if (on_lobby_created != nullptr) {
			on_lobby_created(lobbyID, result);
		}
	}
};

class LobbyCreatedListenerImplLocal : public galaxy::api::ILobbyCreatedListener
{
public:
	using on_lobby_created_func_t = std::function<void(const GalaxyID& lobbyID, LobbyCreateResult result)>;

private:
	on_lobby_created_func_t on_lobby_created;

public:
	LobbyCreatedListenerImplLocal(
		on_lobby_created_func_t on_lobby_created = nullptr) :
		on_lobby_created{ on_lobby_created } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyCreatedListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyCreated(const GalaxyID& lobbyID, LobbyCreateResult result) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} failureReason: {}",
			lobbyID, magic_enum::enum_name(result)
		).c_str());


		if (on_lobby_created != nullptr) {
			on_lobby_created(lobbyID, result);
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerLobbyCreatedListenerImplGlobal : public galaxy::api::GameServerGlobalLobbyCreatedListener
{
public:
	using on_lobby_created_func_t = std::function<void(const GalaxyID& lobbyID, LobbyCreateResult result)>;

private:
	on_lobby_created_func_t on_lobby_created;

public:
	GameServerLobbyCreatedListenerImplGlobal(
		on_lobby_created_func_t on_lobby_created = nullptr) :
		on_lobby_created{ on_lobby_created } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerLobbyCreatedListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyCreated(const GalaxyID& lobbyID, LobbyCreateResult result) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} failureReason: {}",
			lobbyID, magic_enum::enum_name(result)
		).c_str());


		if (on_lobby_created != nullptr) {
			on_lobby_created(lobbyID, result);
		}
	}
};

#endif
