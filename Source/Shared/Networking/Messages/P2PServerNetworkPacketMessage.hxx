#pragma once

#include "P2PNetworkPacketMessage.hxx"

#include <memory>

namespace universelan {
	class P2PServerNetworkPacketMessage
	{
	public:
		std::shared_ptr<P2PNetworkPacketMessage> packet;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(packet);
		}

		UniqueClassId_Declare(P2PServerNetworkPacketMessage);

		P2PServerNetworkPacketMessage()
			: packet{ nullptr } {}

		P2PServerNetworkPacketMessage(galaxy::api::GalaxyID id, uint8_t channel, galaxy::api::P2PSendType send_type, const char* data, uint32_t data_length)
			: packet{ std::make_shared<P2PNetworkPacketMessage>(id, channel, send_type, data, data_length) } {}

		P2PServerNetworkPacketMessage(const P2PNetworkPacketMessage& packet)
			: packet{ std::make_shared<P2PNetworkPacketMessage>(packet) } {}

		P2PServerNetworkPacketMessage(const std::shared_ptr<P2PNetworkPacketMessage>& packet)
			: packet{ packet } {}
	};
}
