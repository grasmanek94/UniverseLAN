#include <Networking/Messages/CreateLobbyResponseMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(CreateLobbyResponseMessage, SerializesRequestWithoutLobbyResponse)
{
	const auto restored = universelan::test::serialize_round_trip(universelan::CreateLobbyResponseMessage(7, nullptr));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.lobby, nullptr);
}
