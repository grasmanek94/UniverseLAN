#pragma once

#include <GalaxyVersionedTypes.hxx>
#include <LobbyManager.hxx>
#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class RequestLobbyDataMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::GalaxyID lobby_id;
		LobbyManager::lobby_t data;
		galaxy::api::ILobbyDataRetrieveListener::FailureReason fail_reason;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, lobby_id, data, fail_reason);
		}

		UniqueClassId_Declare(RequestLobbyDataMessage);

		RequestLobbyDataMessage()
			: request_id{ 0 }, lobby_id{ 0 }, data{}, fail_reason{ galaxy::api::ILobbyDataRetrieveListener::FAILURE_REASON_UNDEFINED } {}
		RequestLobbyDataMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id)
			: request_id{ request_id }, lobby_id{ lobby_id }, data{}, fail_reason{ galaxy::api::ILobbyDataRetrieveListener::FAILURE_REASON_UNDEFINED } {}
		RequestLobbyDataMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, LobbyManager::lobby_t& data)
			: request_id{ request_id }, lobby_id{ lobby_id }, data{ data }, fail_reason{ galaxy::api::ILobbyDataRetrieveListener::FAILURE_REASON_UNDEFINED } {}
		RequestLobbyDataMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, galaxy::api::ILobbyDataRetrieveListener::FailureReason fail_reason)
			: request_id{ request_id }, lobby_id{ lobby_id }, data{ }, fail_reason{ fail_reason } {}
	};
}
