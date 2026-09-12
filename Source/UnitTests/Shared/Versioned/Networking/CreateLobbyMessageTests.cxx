#include <Networking/Messages/CreateLobbyMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(CreateLobbyMessage, SerializesLobbyConfiguration)
{
	const auto restored = universelan::test::serialize_round_trip(universelan::CreateLobbyMessage(7, galaxy::api::LOBBY_TYPE_PUBLIC, 12, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.type, galaxy::api::LOBBY_TYPE_PUBLIC);
	EXPECT_EQ(restored.max_members, 12U);
	EXPECT_TRUE(restored.joinable);
	EXPECT_EQ(restored.topology_type, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM);
}
