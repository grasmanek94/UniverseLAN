#include <Networking/Messages/RequestLobbyListMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(RequestLobbyListMessage, SerializesErrorResponseWithoutLobbies)
{
	const auto restored = universelan::test::serialize_round_trip(universelan::RequestLobbyListMessage(7, true, {}));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_TRUE(restored.error);
	EXPECT_TRUE(restored.lobby_list.empty());
}
