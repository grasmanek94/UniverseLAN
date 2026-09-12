#include <Networking/Messages/SetLobbyTypeMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(SetLobbyTypeMessage, SerializesLobbyAndType)
{
	galaxy::api::GalaxyID id(42);
	const auto restored = universelan::test::serialize_round_trip(universelan::SetLobbyTypeMessage(7, id, galaxy::api::LOBBY_TYPE_PUBLIC));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.lobby_id.ToUint64(), id.ToUint64());
	EXPECT_EQ(restored.type, galaxy::api::LOBBY_TYPE_PUBLIC);
	EXPECT_TRUE(restored.success);
}
