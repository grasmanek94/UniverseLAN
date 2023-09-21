#pragma once

#include "TestCaseClientDetails.hxx"

class LobbyOwnerChangeListenerImplGlobal : public galaxy::api::GlobalLobbyOwnerChangeListener
{
public:
	using on_lobby_owner_changed_func_t = std::function<void(const GalaxyID& lobbyID, const GalaxyID& newOwnerID)>;

private:
	on_lobby_owner_changed_func_t on_lobby_owner_changed;

public:
	LobbyOwnerChangeListenerImplGlobal(
		on_lobby_owner_changed_func_t on_lobby_owner_changed = nullptr) :
		on_lobby_owner_changed{ on_lobby_owner_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyOwnerChangeListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyOwnerChanged(const GalaxyID& lobbyID, const GalaxyID& newOwnerID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} newOwnerID: {}",
			lobbyID, newOwnerID
		).c_str());


		if (on_lobby_owner_changed != nullptr) {
			on_lobby_owner_changed(lobbyID, newOwnerID);
		}
	}
};

class LobbyOwnerChangeListenerImplLocal : public galaxy::api::ILobbyOwnerChangeListener
{
public:
	using on_lobby_owner_changed_func_t = std::function<void(const GalaxyID& lobbyID, const GalaxyID& newOwnerID)>;

private:
	on_lobby_owner_changed_func_t on_lobby_owner_changed;

public:
	LobbyOwnerChangeListenerImplLocal(
		on_lobby_owner_changed_func_t on_lobby_owner_changed = nullptr) :
		on_lobby_owner_changed{ on_lobby_owner_changed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyOwnerChangeListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyOwnerChanged(const GalaxyID& lobbyID, const GalaxyID& newOwnerID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} newOwnerID: {}",
			lobbyID, newOwnerID
		).c_str());


		if (on_lobby_owner_changed != nullptr) {
			on_lobby_owner_changed(lobbyID, newOwnerID);
		}
	}
};
