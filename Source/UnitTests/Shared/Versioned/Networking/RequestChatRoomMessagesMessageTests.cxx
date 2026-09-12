#if GALAXY_BUILD_FEATURE_HAS_ICHAT
#include <Networking/Messages/RequestChatRoomMessagesMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(RequestChatRoomMessagesMessage, SerializesRequestAndPaginationWithoutMessages)
{
	const auto restored = universelan::test::serialize_round_trip(universelan::RequestChatRoomMessagesMessage(7, 42, 3));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.id, 42U);
	EXPECT_EQ(restored.oldest_message, 3U);
	EXPECT_TRUE(restored.messages.empty());
}
#endif
