#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class SetLobbyTypeMessage
	{
	public:
		uint64_t request_id = 0;
		galaxy::api::GalaxyID lobby_id = 0;
		galaxy::api::LobbyType type = galaxy::api::LOBBY_TYPE_PRIVATE;
		bool success = true;
#if (GALAXY_VERSION) > 11240
		galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason = galaxy::api::ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED;
#endif

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id
				, lobby_id
				, type
				, success
#if (GALAXY_VERSION) > 11240
				, fail_reason
#endif
			);
		}

		UniqueClassId_Declare(SetLobbyTypeMessage);

		SetLobbyTypeMessage() {}

		SetLobbyTypeMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, galaxy::api::LobbyType type)
			: request_id{ request_id }, lobby_id{ lobby_id }, type{ type }, success{ true } {}

#if (GALAXY_VERSION) > 11240
		SetLobbyTypeMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, galaxy::api::LobbyType type, galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason)
			: request_id{ request_id }, lobby_id{ lobby_id }, type{ type }, success{ false },
			fail_reason{ fail_reason } {}
#endif

	};
}
