#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class SetLobbyTypeMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::GalaxyID lobby_id;
		galaxy::api::LobbyType type;
		bool success;
		galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, lobby_id, type, success, fail_reason);
		}

		UniqueClassId_Declare(SetLobbyTypeMessage);

		SetLobbyTypeMessage()
			: request_id{ 0 }, lobby_id{ 0 }, type{ galaxy::api::LOBBY_TYPE_PRIVATE }, success{ true },
			fail_reason{ galaxy::api::ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED } {}
		SetLobbyTypeMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, galaxy::api::LobbyType type)
			: request_id{ request_id }, lobby_id{ lobby_id }, type{ type }, success{ true },
			fail_reason{ galaxy::api::ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED } {}
		SetLobbyTypeMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, galaxy::api::LobbyType type, galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason)
			: request_id{ request_id }, lobby_id{ lobby_id }, type{ type }, success{ false },
			fail_reason{ fail_reason } {}
	};
}
