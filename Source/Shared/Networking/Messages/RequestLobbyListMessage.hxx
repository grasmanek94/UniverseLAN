#pragma once

#include <LobbyManager.hxx>
#include <Networking/SendableEventMessage.hxx>

#include <GalaxyApi.h>

namespace universelan {
	class RequestLobbyListMessage
	{
	public:
		uint64_t request_id;
		bool error;
		LobbyManager::lobbies_t lobby_list;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, lobby_list);
		}

		UniqueClassId_Declare(RequestLobbyListMessage);

		RequestLobbyListMessage() : request_id{}, error{ false }, lobby_list {} {}
		RequestLobbyListMessage(uint64_t request_id) : request_id{ request_id }, error{ false }, lobby_list{} {}
		RequestLobbyListMessage(uint64_t request_id, bool error, const LobbyManager::lobbies_t& lobby_list) : request_id{ request_id }, error{ error }, lobby_list{ lobby_list } {}
	};
}
