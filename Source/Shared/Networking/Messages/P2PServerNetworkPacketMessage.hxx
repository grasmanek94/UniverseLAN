#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKING
#include "P2PNetworkPacketMessage.hxx"

namespace universelan {
	class P2PServerNetworkPacketMessage : public P2PNetworkPacketMessage
	{
	public:
		template<class Archive>
		void serialize(Archive& ar)
		{
			P2PNetworkPacketMessage::serialize<Archive>(ar);
		}

		UniqueClassId_Declare(P2PServerPNetworkPacketMessage);

		P2PServerNetworkPacketMessage()
			: P2PNetworkPacketMessage{} {}

		P2PServerNetworkPacketMessage(galaxy::api::GalaxyID id, uint8_t channel, galaxy::api::P2PSendType send_type, const char* data, uint32_t data_length)
			: P2PNetworkPacketMessage{ id, channel, send_type, data, data_length } {}

		P2PServerNetworkPacketMessage(const P2PNetworkPacketMessage& packet)
			: P2PNetworkPacketMessage{ packet } {}

		virtual ~P2PServerNetworkPacketMessage() {}
	};
}
#endif
