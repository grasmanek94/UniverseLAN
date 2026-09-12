#if GALAXY_BUILD_FEATURE_HAS_ICHAT
#include <Networking/Messages/RequestChatRoomWithUserMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(RequestChatRoomWithUserMessage, SerializesRequestAndUserWithoutResponse)
{
	galaxy::api::GalaxyID user(42);
	const auto restored = universelan::test::serialize_round_trip(universelan::RequestChatRoomWithUserMessage(7, user));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.id.ToUint64(), user.ToUint64());
	EXPECT_EQ(restored.chat_room, nullptr);
}
#endif
