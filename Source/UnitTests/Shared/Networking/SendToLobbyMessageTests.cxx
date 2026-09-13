#include <Networking/Messages/SendToLobbyMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(SendToLobbyMessage, SerializesLobbyAndMessagePayload)
{
	galaxy::api::GalaxyID lobby(42), sender(7);
	universelan::Lobby::Message message{ 3, sender, "payload" };
	const auto restored = universelan::test::serialize_round_trip(universelan::SendToLobbyMessage(lobby, message));
	EXPECT_EQ(restored.lobby_id.ToUint64(), lobby.ToUint64());
	EXPECT_EQ(restored.message.message_id, 3U);
	EXPECT_EQ(restored.message.sender.ToUint64(), sender.ToUint64());
	EXPECT_EQ(restored.message.data, "payload");
}
