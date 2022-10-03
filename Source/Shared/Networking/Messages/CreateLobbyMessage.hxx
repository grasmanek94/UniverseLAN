#pragma once

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>
#include <IMatchmaking.h>

namespace universelan {
	class CreateLobbyMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::LobbyType type;
		uint32_t max_members;
		bool joinable;
		galaxy::api::LobbyTopologyType topology_type;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, type, max_members, joinable, topology_type);
		}

		UniqueClassId_Declare(CreateLobbyMessage);

		CreateLobbyMessage() : request_id{ 0 }, type{}, max_members{}, joinable{}, topology_type{} {}
		CreateLobbyMessage(uint64_t request_id, galaxy::api::LobbyType type, uint32_t max_members,
			bool joinable, galaxy::api::LobbyTopologyType topology_type)
			: request_id{ request_id }, type{ type }, max_members{ max_members }, 
			joinable{ joinable }, topology_type{ topology_type } {}
	};
}
