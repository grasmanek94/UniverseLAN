#pragma once

#include <Lobby.hxx>
#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>
#include <IMatchmaking.h>

#include <memory>

namespace universelan {
	class CreateLobbyResponseMessage
	{
	public:
		uint64_t request_id;
		std::shared_ptr<Lobby> lobby;
	
		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, lobby);
		}

		UniqueClassId_Declare(CreateLobbyResponseMessage);

		CreateLobbyResponseMessage() : request_id{ 0 }, lobby{} {}
		CreateLobbyResponseMessage(uint64_t request_id,const std::shared_ptr<Lobby>& lobby)
			: request_id{ request_id }, lobby{lobby} {}
	};
}
