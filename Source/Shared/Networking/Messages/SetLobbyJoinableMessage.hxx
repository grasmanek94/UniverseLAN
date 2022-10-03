#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class SetLobbyJoinableMessage
	{
	public:
		uint64_t request_id = 0;
		galaxy::api::GalaxyID lobby_id = 0;
		bool joinable = true;
		bool success = true;
#if (GALAXY_VERSION) > 112400
		galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason = galaxy::api::ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED;
#endif

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id
				, lobby_id
				, joinable
				, success
#if (GALAXY_VERSION) > 112400
				, fail_reason
#endif
			);
		}

		UniqueClassId_Declare(SetLobbyJoinableMessage);

		SetLobbyJoinableMessage() {}

		SetLobbyJoinableMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, bool joinable)
			: request_id{ request_id }, lobby_id{ lobby_id }, joinable{ joinable }
			 {}

#if (GALAXY_VERSION) > 112400
		SetLobbyJoinableMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, bool joinable, galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason)
			: request_id{ request_id }, lobby_id{ lobby_id }, joinable{ joinable }, success{ false },
			fail_reason{ fail_reason } {}
#endif
	};
}
