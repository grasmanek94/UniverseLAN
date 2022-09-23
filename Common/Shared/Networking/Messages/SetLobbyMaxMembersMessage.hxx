#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class SetLobbyMaxMembersMessage
	{
	public:
		uint64_t request_id;
		galaxy::api::GalaxyID lobby_id;
		uint32_t max_members;
		bool success;
		galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, lobby_id, max_members, success, fail_reason);
		}

		UniqueClassId_Declare(SetLobbyMaxMembersMessage);

		SetLobbyMaxMembersMessage()
			: request_id{ 0 }, lobby_id{ 0 }, max_members{ 0 }, success{ true }, 
			fail_reason{galaxy::api::ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED} {}
		SetLobbyMaxMembersMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, uint32_t max_members) 
			: request_id{ request_id }, lobby_id{ lobby_id }, max_members{ max_members }, success{ true },
			fail_reason{ galaxy::api::ILobbyDataUpdateListener::FAILURE_REASON_UNDEFINED } {}
		SetLobbyMaxMembersMessage(uint64_t request_id, galaxy::api::GalaxyID lobby_id, uint32_t max_members, galaxy::api::ILobbyDataUpdateListener::FailureReason fail_reason)
			: request_id{ request_id }, lobby_id{ lobby_id }, max_members{ max_members }, success{ false },
			fail_reason{ fail_reason } {}
	};
}
