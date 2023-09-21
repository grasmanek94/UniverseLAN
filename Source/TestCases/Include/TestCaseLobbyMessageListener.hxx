#pragma once

#include "TestCaseClientDetails.hxx"

class LobbyMessageListenerImplGlobal : public galaxy::api::GlobalLobbyMessageListener
{
public:
	using on_lobby_message_received_func_t = std::function<void(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength)>;
private:
	on_lobby_message_received_func_t on_lobby_message_received;

public:
	LobbyMessageListenerImplGlobal(
		on_lobby_message_received_func_t on_lobby_message_received = nullptr) :
		on_lobby_message_received{ on_lobby_message_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyMessageListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyMessageReceived(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} senderID: {} messageID: {} messageLength: {}",
			lobbyID, senderID, messageID, messageLength
		).c_str());


		if (on_lobby_message_received != nullptr) {
			on_lobby_message_received(lobbyID, senderID, messageID, messageLength);
		}
	}
};

class LobbyMessageListenerImplLocal : public galaxy::api::ILobbyMessageListener
{
public:
	using on_lobby_message_received_func_t = std::function<void(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength)>;

private:
	on_lobby_message_received_func_t on_lobby_message_received;

public:
	LobbyMessageListenerImplLocal(
		on_lobby_message_received_func_t on_lobby_message_received = nullptr) :
		on_lobby_message_received{ on_lobby_message_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~LobbyMessageListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyMessageReceived(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} senderID: {} messageID: {} messageLength: {}",
			lobbyID, senderID, messageID, messageLength
		).c_str());


		if (on_lobby_message_received != nullptr) {
			on_lobby_message_received(lobbyID, senderID, messageID, messageLength);
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerLobbyMessageListenerImplGlobal : public galaxy::api::GameServerGlobalLobbyMessageListener
{
public:
	using on_lobby_message_received_func_t = std::function<void(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength)>;
private:
	on_lobby_message_received_func_t on_lobby_message_received;

public:
	GameServerLobbyMessageListenerImplGlobal(
		on_lobby_message_received_func_t on_lobby_message_received = nullptr) :
		on_lobby_message_received{ on_lobby_message_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerLobbyMessageListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnLobbyMessageReceived(const GalaxyID& lobbyID, const GalaxyID& senderID, uint32_t messageID, uint32_t messageLength) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"lobbyID: {} senderID: {} messageID: {} messageLength: {}",
			lobbyID, senderID, messageID, messageLength
		).c_str());


		if (on_lobby_message_received != nullptr) {
			on_lobby_message_received(lobbyID, senderID, messageID, messageLength);
		}
	}
};

#endif
