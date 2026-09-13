#include <Networking/Messages/P2PNetworkPacketMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(P2PNetworkPacketMessage, SerializesDeliveryMetadataAndBytes)
{
	galaxy::api::GalaxyID user(42);
	const char data[] = { 'a', 'b' };
	const auto restored = universelan::test::serialize_round_trip(universelan::P2PNetworkPacketMessage(user, 3, galaxy::api::P2P_SEND_UNRELIABLE, data, 2));
	EXPECT_EQ(restored.id.ToUint64(), user.ToUint64());
	EXPECT_EQ(restored.channel, 3U);
	EXPECT_EQ(restored.send_type, galaxy::api::P2P_SEND_UNRELIABLE);
	EXPECT_EQ(restored.data, std::vector<char>({ 'a', 'b' }));
}
