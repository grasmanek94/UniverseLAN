#if GALAXY_BUILD_FEATURE_HAS_ICHAT
#include <Networking/Messages/SendToChatRoomMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(SendToChatRoomMessage, SerializesRequestAndRoomWithoutMessage)
{
	const auto restored = universelan::test::serialize_round_trip(universelan::SendToChatRoomMessage(7, 42, nullptr));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.id, 42U);
	EXPECT_EQ(restored.message, nullptr);
}
#endif
