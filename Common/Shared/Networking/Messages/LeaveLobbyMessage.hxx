#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>
#include <IMatchMaking.h>

namespace universelan {
	class LeaveLobbyMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::GalaxyID lobby_id;
		galaxy::api::ILobbyLeftListener::LobbyLeaveReason reason;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, lobby_id, reason);
		}

		UniqueClassId_Declare(LeaveLobbyMessage);

		LeaveLobbyMessage()
			: request_id{ 0 }, lobby_id{ 0 }, reason{ galaxy::api::ILobbyLeftListener::LOBBY_LEAVE_REASON_UNDEFINED} {}
		LeaveLobbyMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id)
			: request_id{ request_id }, lobby_id{ lobby_id }, reason{ galaxy::api::ILobbyLeftListener::LOBBY_LEAVE_REASON_UNDEFINED } {}
		LeaveLobbyMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, galaxy::api::ILobbyLeftListener::LobbyLeaveReason reason)
			: request_id{ request_id }, lobby_id{ lobby_id }, reason{ reason } {}
	};
}
