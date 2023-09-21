#pragma once

#include "TestCaseClientDetails.hxx"

class GameInvitationReceivedListenerImplGlobal : public galaxy::api::GlobalGameInvitationReceivedListener
{
public:
	using on_game_invitation_received_func_t = std::function<void(GalaxyID userID, const char* connectionString)>;

private:
	on_game_invitation_received_func_t on_game_invitation_received;

public:
	GameInvitationReceivedListenerImplGlobal(
		on_game_invitation_received_func_t on_game_invitation_received = nullptr) :
		on_game_invitation_received{ on_game_invitation_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameInvitationReceivedListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnGameInvitationReceived(GalaxyID userID, const char* connectionString) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} connectionString: {}",
			userID, connectionString
		).c_str());


		if (on_game_invitation_received != nullptr) {
			on_game_invitation_received(userID, connectionString);
		}
	}

};

class GameInvitationReceivedListenerImplLocal : public galaxy::api::IGameInvitationReceivedListener
{
public:
	using on_game_invitation_received_func_t = std::function<void(GalaxyID userID, const char* connectionString)>;

private:
	on_game_invitation_received_func_t on_game_invitation_received;

public:
	GameInvitationReceivedListenerImplLocal(
		on_game_invitation_received_func_t on_game_invitation_received = nullptr) :
		on_game_invitation_received{ on_game_invitation_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameInvitationReceivedListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnGameInvitationReceived(GalaxyID userID, const char* connectionString) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} connectionString: {}",
			userID, connectionString
		).c_str());


		if (on_game_invitation_received != nullptr) {
			on_game_invitation_received(userID, connectionString);
		}
	}

};
