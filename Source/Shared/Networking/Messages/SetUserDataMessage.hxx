#pragma once

#include <LobbyManager.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyID.h>

namespace universelan {
	class SetUserDataMessage
	{
	public:
		galaxy::api::GalaxyID id;
		std::string key;
		std::string value;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(id, key, value);
		}

		UniqueClassId_Declare(SetUserDataMessage);

		SetUserDataMessage()
			: id{ 0 }, key{}, value{} {}
		SetUserDataMessage(galaxy::api::GalaxyID id, const std::string& key, const std::string& value)
			: id{ id }, key{ key }, value{ value } {}
	};
}
