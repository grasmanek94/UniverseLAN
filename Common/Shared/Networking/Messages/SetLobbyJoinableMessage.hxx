#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class SetLobbyJoinableMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::GalaxyID lobby_id;
		bool joinable;
		bool success;
		galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, lobby_id, joinable, success, fail_reason);
		}

		UniqueClassId_Declare(SetLobbyJoinableMessage);

		SetLobbyJoinableMessage()
			: request_id{ 0 }, lobby_id{ 0 }, joinable{ true }, success{ true },
			fail_reason{ galaxy::api::ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED } {}
		SetLobbyJoinableMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id,bool joinable)
			: request_id{ request_id }, lobby_id{ lobby_id }, joinable{ joinable }, success{ true },
			fail_reason{ galaxy::api::ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED } {}
		SetLobbyJoinableMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, bool joinable, galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason)
			: request_id{ request_id }, lobby_id{ lobby_id }, joinable{ joinable }, success{ false },
			fail_reason{ fail_reason } {}
	};
}
