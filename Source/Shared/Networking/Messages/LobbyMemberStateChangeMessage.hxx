#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class LobbyMemberStateChangeMessage
	{
	public:
		galaxy::api::GalaxyID lobby_id;
		galaxy::api::GalaxyID member_id;
		galaxy::api::LobbyMemberStateChange state;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(lobby_id, member_id, state);
		}

		UniqueClassId_Declare(LobbyMemberStateChangeMessage);

		LobbyMemberStateChangeMessage()
			: lobby_id{ 0 }, member_id{ 0 }, state{ galaxy::api::LOBBY_MEMBER_STATE_CHANGED_DISCONNECTED } {}
		LobbyMemberStateChangeMessage(galaxy::api::GalaxyID lobby_id, galaxy::api::GalaxyID member_id, galaxy::api::LobbyMemberStateChange state)
			: lobby_id{ lobby_id }, member_id{ member_id }, state{ state } {}
	};
}
