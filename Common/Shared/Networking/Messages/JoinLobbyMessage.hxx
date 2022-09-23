#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class JoinLobbyMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::GalaxyID lobby_id;
		galaxy::api::LobbyEnterResult result;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, lobby_id, result);
		}

		UniqueClassId_Declare(JoinLobbyMessage);

		JoinLobbyMessage() 
			: request_id{ 0 }, lobby_id{ 0 }, result{ galaxy::api::LOBBY_ENTER_RESULT_ERROR } {}
		JoinLobbyMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id) 
			: request_id{ request_id }, lobby_id{ lobby_id }, result{ galaxy::api::LOBBY_ENTER_RESULT_ERROR } {}
		JoinLobbyMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, galaxy::api::LobbyEnterResult result) 
			: request_id{ request_id }, lobby_id{ lobby_id }, result{ result } {}
	};
}
