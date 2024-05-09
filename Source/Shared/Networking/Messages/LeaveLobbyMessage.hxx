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
#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		galaxy::api::ILobbyLeftListener::LobbyLeaveReason reason = galaxy::api::ILobbyLeftListener::LOBBY_LEAVE_REASON_UNDEFINED;
#else
		bool reason; // ioFailure
#endif

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id
				, lobby_id
				, reason
			);
		}

		UniqueClassId_Declare(LeaveLobbyMessage);

		LeaveLobbyMessage() {}

		LeaveLobbyMessage(uint64_t request_id
			, galaxy::api::GalaxyID lobby_id
		)	: request_id{ request_id }
			, lobby_id{ lobby_id }
		{}

#if GALAXY_BUILD_FEATURE_HAS_IMATCHMAKING_LOBBY_LEAVE_REASON
		LeaveLobbyMessage(uint64_t request_id
			, galaxy::api::GalaxyID lobby_id
			, galaxy::api::ILobbyLeftListener::LobbyLeaveReason reason
		)	: request_id{ request_id }
			, lobby_id{ lobby_id }
			, reason{ reason } 
		{}
#else
		LeaveLobbyMessage(uint64_t request_id
			, galaxy::api::GalaxyID lobby_id
			, bool ioFailure
		) : request_id{ request_id }
			, lobby_id{ lobby_id }
			, reason{ ioFailure }
		{}
#endif
	};
}
