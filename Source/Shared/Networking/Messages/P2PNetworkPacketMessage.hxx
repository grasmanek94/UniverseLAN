#pragma once

#include <ChatRoom.hxx>

#include <Networking/SendableEventMessage.hxx>

#include <GalaxyApi.h>

#include <vector>

namespace universelan {
	class P2PNetworkPacketMessage
	{
	public:
		galaxy::api::GalaxyID id;
		uint8_t channel;
		galaxy::api::P2PSendType send_type;
		std::vector<char> data;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(id, channel, send_type, data);
		}

		UniqueClassId_Declare(P2PNetworkPacketMessage);

		P2PNetworkPacketMessage()
			: id{ 0 }, channel{ 0 }, send_type{ galaxy::api::P2P_SEND_UNRELIABLE }, data{} {}

		P2PNetworkPacketMessage(galaxy::api::GalaxyID id, uint8_t channel, galaxy::api::P2PSendType send_type, const char* data, uint32_t data_length)
			: id{ id }, channel{ channel }, send_type{ send_type }, data{data, data + data_length} {}
	};
}
