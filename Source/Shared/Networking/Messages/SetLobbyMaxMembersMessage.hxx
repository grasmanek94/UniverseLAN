#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class SetLobbyMaxMembersMessage
	{
	public:
		uint64_t request_id = 0;
		galaxy::api::GalaxyID lobby_id = 0;
		uint32_t max_members = 0;
		bool success = true;
#if (GALAXY_VERSION) > 11240
		galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason = galaxy::api::ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED;
#endif

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id
				, lobby_id
				, max_members
				, success
#if (GALAXY_VERSION) > 11240
				, fail_reason
#endif
			);
		}

		UniqueClassId_Declare(SetLobbyMaxMembersMessage);

		SetLobbyMaxMembersMessage() {}
		SetLobbyMaxMembersMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, uint32_t max_members)
			: request_id{ request_id }, lobby_id{ lobby_id }, max_members{ max_members } {}

#if (GALAXY_VERSION) > 11240
		SetLobbyMaxMembersMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, uint32_t max_members, galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason)
			: request_id{ request_id }, lobby_id{ lobby_id }, max_members{ max_members }, success{ false },
			fail_reason{ fail_reason } {}
#endif
	};
}
