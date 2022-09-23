#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class LobbyOwnerChangeMessage
	{
	public:
		galaxy::api::GalaxyID lobby_id;
		galaxy::api::GalaxyID member_id;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(lobby_id, member_id);
		}

		UniqueClassId_Declare(LobbyOwnerChangeMessage);

		LobbyOwnerChangeMessage()
			: lobby_id{ 0 }, member_id{ 0 } {}
		LobbyOwnerChangeMessage(galaxy::api::GalaxyID lobby_id, galaxy::api::GalaxyID member_id)
			: lobby_id{ lobby_id }, member_id{ member_id } {}
	};
}
