#pragma once

#include "TestCaseClientDetails.hxx"

class LobbyDataListenerImplGlobal : public galaxy::api::GlobalLobbyDataListener
{
public:
	using on_lobby_data_updated_func_t = std::function<void(const GalaxyID& lobbyID, const GalaxyID& memberID)>;

private:
	on_lobby_data_updated_func_t on_lobby_data_updated;

public:
	LobbyDataListenerImplGlobal(
		on_lobby_data_updated_func_t on_lobby_data_updated = nullptr) :
		on_lobby_data_updated{ on_lobby_data_updated } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyDataListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyDataUpdated(const GalaxyID& lobbyID, const GalaxyID& memberID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} memberID: {}",
			lobbyID, memberID
		).c_str());


		if (on_lobby_data_updated != nullptr) {
			on_lobby_data_updated(lobbyID, memberID);
		}
	}
};

class LobbyDataListenerImplLocal : public galaxy::api::ILobbyDataListener
{
public:
	using on_lobby_data_updated_func_t = std::function<void(const GalaxyID& lobbyID, const GalaxyID& memberID)>;

private:
	on_lobby_data_updated_func_t on_lobby_data_updated;

public:
	LobbyDataListenerImplLocal(
		on_lobby_data_updated_func_t on_lobby_data_updated = nullptr) :
		on_lobby_data_updated{ on_lobby_data_updated } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyDataListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyDataUpdated(const GalaxyID& lobbyID, const GalaxyID& memberID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} memberID: {}",
			lobbyID, memberID
		).c_str());


		if (on_lobby_data_updated != nullptr) {
			on_lobby_data_updated(lobbyID, memberID);
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerLobbyDataListenerImplGlobal : public galaxy::api::GameServerGlobalLobbyDataListener
{
public:
	using on_lobby_data_updated_func_t = std::function<void(const GalaxyID& lobbyID, const GalaxyID& memberID)>;

private:
	on_lobby_data_updated_func_t on_lobby_data_updated;

public:
	GameServerLobbyDataListenerImplGlobal(
		on_lobby_data_updated_func_t on_lobby_data_updated = nullptr) :
		on_lobby_data_updated{ on_lobby_data_updated } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerLobbyDataListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyDataUpdated(const GalaxyID& lobbyID, const GalaxyID& memberID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} memberID: {}",
			lobbyID, memberID
		).c_str());


		if (on_lobby_data_updated != nullptr) {
			on_lobby_data_updated(lobbyID, memberID);
		}
	}
};

#endif
