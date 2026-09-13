#include <Networking/Messages/P2PServerNetworkPacketMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(P2PServerNetworkPacketMessage, SerializesOwnedPacket)
{
	galaxy::api::GalaxyID user(42);
	const char data[] = { 'a', 'b' };
	const auto restored = universelan::test::serialize_round_trip(universelan::P2PServerNetworkPacketMessage(user, 3, galaxy::api::P2P_SEND_UNRELIABLE, data, 2));
	ASSERT_NE(restored.packet, nullptr);
	EXPECT_EQ(restored.packet->id.ToUint64(), user.ToUint64());
	EXPECT_EQ(restored.packet->channel, 3U);
	EXPECT_EQ(restored.packet->data, std::vector<char>({ 'a', 'b' }));
}
