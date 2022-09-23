#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class SetLobbyMemberDataMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::GalaxyID lobby_id;
		galaxy::api::GalaxyID member_id;
		bool success;
		galaxy::api::ILobbyMemberDataUpdateListener::FailureReason fail_reason;
		std::string key;
		std::string value;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, lobby_id, member_id, success, fail_reason, key, value);
		}

		UniqueClassId_Declare(SetLobbyMemberDataMessage);

		SetLobbyMemberDataMessage()
			: request_id{ 0 }, lobby_id{ 0 }, member_id{ 0 },
			success{ true }, fail_reason{ galaxy::api::ILobbyMemberDataUpdateListener::FAILURE_REASON_UNDEFINED },
			key{}, value{} {}
		SetLobbyMemberDataMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, galaxy::api::GalaxyID member_id, const std::string& key, const std::string& value)
			: request_id{ request_id }, lobby_id{ lobby_id }, member_id{ member_id },
			success{ true }, fail_reason{ galaxy::api::ILobbyMemberDataUpdateListener::FAILURE_REASON_UNDEFINED },
			key{ key }, value{ value } {}
		SetLobbyMemberDataMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, galaxy::api::GalaxyID member_id, galaxy::api::ILobbyMemberDataUpdateListener::FailureReason fail_reason)
			: request_id{ request_id }, lobby_id{ lobby_id }, member_id{ member_id },
			success{ false }, fail_reason{ fail_reason },
			key{}, value{} {}
	};
}
