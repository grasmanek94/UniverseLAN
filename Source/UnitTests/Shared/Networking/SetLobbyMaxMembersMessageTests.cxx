#include <Networking/Messages/SetLobbyMaxMembersMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(SetLobbyMaxMembersMessage, SerializesLobbyAndCapacity)
{
	galaxy::api::GalaxyID id(42);
	const auto restored = universelan::test::serialize_round_trip(universelan::SetLobbyMaxMembersMessage(7, id, 12));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.lobby_id.ToUint64(), id.ToUint64());
	EXPECT_EQ(restored.max_members, 12U);
	EXPECT_TRUE(restored.success);
}
