#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

#include <string>

namespace universelan {
	class SetLobbyDataMessage
	{
	public:
		uint64_t request_id = 0;
		galaxy::api::GalaxyID lobby_id = 0;
		bool success = true;
#if (GALAXY_VERSION) > 112400
		galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason = galaxy::api::ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED;
#endif
		std::string key = "";
		std::string value = "";

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id
				, lobby_id
				, success
#if (GALAXY_VERSION) > 112400
				, fail_reason
#endif
				, key
				, value);
		}

		UniqueClassId_Declare(SetLobbyDataMessage);

		SetLobbyDataMessage(){}

		SetLobbyDataMessage(uint64_t request_id
			, galaxy::api::GalaxyID lobby_id
			, const std::string& key
			, const std::string& value)
			: request_id{ request_id }
			, lobby_id{ lobby_id }
			, success{ true }
			, key{ key }
			, value{ value } {}

#if (GALAXY_VERSION) > 112400
		SetLobbyDataMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason)
			: request_id{ request_id }, lobby_id{ lobby_id },
			success{ false }, fail_reason{ fail_reason },
			key{}, value{} {}
#endif

	};
}
