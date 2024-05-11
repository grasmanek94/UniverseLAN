#pragma once

#include "TestCaseClientDetails.hxx"

#if GALAXY_BUILD_FEATURE_HAS_ILOBBYDATARETRIEVELISTENER
class LobbyDataRetrieveListenerImplGlobal : public galaxy::api::GlobalLobbyDataRetrieveListener
{
public:
	using on_lobby_data_retrieve_success_func_t = std::function<void(const GalaxyID& lobbyID)>;
	using on_lobby_data_retrieve_failure_func_t = std::function<void(const GalaxyID& lobbyID, FailureReason failureReason)>;

private:
	on_lobby_data_retrieve_success_func_t on_lobby_data_retrieve_success;
	on_lobby_data_retrieve_failure_func_t on_lobby_data_retrieve_failure;

public:
	LobbyDataRetrieveListenerImplGlobal(
		on_lobby_data_retrieve_success_func_t on_lobby_data_retrieve_success = nullptr,
		on_lobby_data_retrieve_failure_func_t on_lobby_data_retrieve_failure = nullptr) :
		on_lobby_data_retrieve_success{ on_lobby_data_retrieve_success },
		on_lobby_data_retrieve_failure{ on_lobby_data_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyDataRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyDataRetrieveSuccess(const GalaxyID& lobbyID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {}",
			lobbyID
		).c_str());


		if (on_lobby_data_retrieve_success != nullptr) {
			on_lobby_data_retrieve_success(lobbyID);
		}
	}

	virtual void OnLobbyDataRetrieveFailure(const GalaxyID& lobbyID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} failureReason: {}",
			lobbyID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_lobby_data_retrieve_failure != nullptr) {
			on_lobby_data_retrieve_failure(lobbyID, failureReason);
		}
	}
};

class LobbyDataRetrieveListenerImplLocal : public galaxy::api::ILobbyDataRetrieveListener
{
public:
	using on_lobby_data_retrieve_success_func_t = std::function<void(const GalaxyID& lobbyID)>;
	using on_lobby_data_retrieve_failure_func_t = std::function<void(const GalaxyID& lobbyID, FailureReason failureReason)>;

private:
	on_lobby_data_retrieve_success_func_t on_lobby_data_retrieve_success;
	on_lobby_data_retrieve_failure_func_t on_lobby_data_retrieve_failure;

public:
	LobbyDataRetrieveListenerImplLocal(
		on_lobby_data_retrieve_success_func_t on_lobby_data_retrieve_success = nullptr,
		on_lobby_data_retrieve_failure_func_t on_lobby_data_retrieve_failure = nullptr) :
		on_lobby_data_retrieve_success{ on_lobby_data_retrieve_success },
		on_lobby_data_retrieve_failure{ on_lobby_data_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyDataRetrieveListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyDataRetrieveSuccess(const GalaxyID& lobbyID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {}",
			lobbyID
		).c_str());


		if (on_lobby_data_retrieve_success != nullptr) {
			on_lobby_data_retrieve_success(lobbyID);
		}
	}

	virtual void OnLobbyDataRetrieveFailure(const GalaxyID& lobbyID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} failureReason: {}",
			lobbyID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_lobby_data_retrieve_failure != nullptr) {
			on_lobby_data_retrieve_failure(lobbyID, failureReason);
		}
	}
};
#endif

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerLobbyDataRetrieveListenerImplGlobal : public galaxy::api::GameServerGlobalLobbyDataRetrieveListener
{
public:
	using on_lobby_data_retrieve_success_func_t = std::function<void(const GalaxyID& lobbyID)>;
	using on_lobby_data_retrieve_failure_func_t = std::function<void(const GalaxyID& lobbyID, FailureReason failureReason)>;

private:
	on_lobby_data_retrieve_success_func_t on_lobby_data_retrieve_success;
	on_lobby_data_retrieve_failure_func_t on_lobby_data_retrieve_failure;

public:
	GameServerLobbyDataRetrieveListenerImplGlobal(
		on_lobby_data_retrieve_success_func_t on_lobby_data_retrieve_success = nullptr,
		on_lobby_data_retrieve_failure_func_t on_lobby_data_retrieve_failure = nullptr) :
		on_lobby_data_retrieve_success{ on_lobby_data_retrieve_success },
		on_lobby_data_retrieve_failure{ on_lobby_data_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerLobbyDataRetrieveListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyDataRetrieveSuccess(const GalaxyID& lobbyID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {}",
			lobbyID
		).c_str());


		if (on_lobby_data_retrieve_success != nullptr) {
			on_lobby_data_retrieve_success(lobbyID);
		}
	}

	virtual void OnLobbyDataRetrieveFailure(const GalaxyID& lobbyID, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} failureReason: {}",
			lobbyID, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_lobby_data_retrieve_failure != nullptr) {
			on_lobby_data_retrieve_failure(lobbyID, failureReason);
		}
	}
};

#endif
