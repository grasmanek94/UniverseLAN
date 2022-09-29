#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class RichPresenceChangeMessage
	{
	public:
		enum ACTION {
			ACTION_NONE,
			ACTION_SET,
			ACTION_DELETE,
			ACTION_CLEAR
		};

		uint64_t request_id;
		galaxy::api::GalaxyID id;
		ACTION action;
		bool success;
		std::string key;
		std::string value;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(request_id, id, action, success, key, value);
		}

		UniqueClassId_Declare(RichPresenceChangeMessage);

		RichPresenceChangeMessage()
			: request_id{ 0 }, id{ 0 }, action{ ACTION_NONE }, success{ false }, key{}, value{} {}
		RichPresenceChangeMessage(uint64_t request_id, galaxy::api::GalaxyID id, ACTION action)
			: request_id{ request_id }, id{ id }, action{ action }, success{ false }, key{}, value{} {}
		RichPresenceChangeMessage(uint64_t request_id, galaxy::api::GalaxyID id, ACTION action, const std::string& key)
			: request_id{ request_id }, id{ id }, action{ action }, success{ false }, key{ key }, value{ } {}
		RichPresenceChangeMessage(uint64_t request_id, galaxy::api::GalaxyID id, ACTION action, const std::string& key, const std::string& value)
			: request_id{ request_id }, id{ id }, action{ action }, success{ false }, key{ key }, value{ value } {}
	};
}
