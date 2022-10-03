#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

#include <string>

namespace universelan {
	class SendToLobbyMessage
	{
	public:
		galaxy::api::GalaxyID lobby_id;
		Lobby::Message message;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(lobby_id, message);
		}

		UniqueClassId_Declare(SendToLobbyMessage);

		SendToLobbyMessage()
			: lobby_id{ 0 }, message{} {}
		SendToLobbyMessage(galaxy::api::GalaxyID lobby_id, const Lobby::Message& data)
			: lobby_id{ lobby_id }, message{ data } {}
	};
}
