#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

#include <string>

namespace universelan {
	class SetLobbyDataMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::GalaxyID lobby_id;
		bool success;
		galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason;
		std::string key;
		std::string value;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, lobby_id, success, fail_reason, key, value);
		}

		UniqueClassId_Declare(SetLobbyDataMessage);

		SetLobbyDataMessage()
			: request_id{ 0 }, lobby_id{ 0 },
			success{ true }, fail_reason{ galaxy::api::ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED },
			key{}, value{} {}
		SetLobbyDataMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, const std::string& key, const std::string& value)
			: request_id{ request_id }, lobby_id{ lobby_id },
			success{ true }, fail_reason{ galaxy::api::ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED },
			key{ key }, value{ value } {}
		SetLobbyDataMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason)
			: request_id{ request_id }, lobby_id{ lobby_id },
			success{ false }, fail_reason{ fail_reason },
			key{}, value{} {}
	};
}
