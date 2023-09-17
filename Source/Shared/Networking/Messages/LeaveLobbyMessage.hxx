#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>
#include <IMatchmaking.h>

namespace universelan {
	class LeaveLobbyMessage
	{
	public:
		uint64_t request_id = 0;
		galaxy::api::GalaxyID lobby_id = 0;
#if (GALAXY_VERSION) > 11240
		galaxy::api::ILobbyLeftListener::LobbyLeaveReason reason = galaxy::api::ILobbyLeftListener::LOBBY_LEAVE_REASON_UNDEFINED;
#endif

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id
				, lobby_id
#if (GALAXY_VERSION) > 11240
				, reason
#endif
			);
		}

		UniqueClassId_Declare(LeaveLobbyMessage);

		LeaveLobbyMessage() {}

		LeaveLobbyMessage(uint64_t request_id
			, galaxy::api::GalaxyID lobby_id
		)	: request_id{ request_id }
			, lobby_id{ lobby_id }
		{}

#if (GALAXY_VERSION) > 11240
		LeaveLobbyMessage(uint64_t request_id
			, galaxy::api::GalaxyID lobby_id
			, galaxy::api::ILobbyLeftListener::LobbyLeaveReason reason
		)	: request_id{ request_id }
			, lobby_id{ lobby_id }
			, reason{ reason } 
		{}
#endif
	};
}
