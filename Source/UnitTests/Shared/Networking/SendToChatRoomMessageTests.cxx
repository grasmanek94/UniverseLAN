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

TEST(SendToChatRoomMessage, SerializesMessagePayload)
{
	galaxy::api::GalaxyID sender(42);
	universelan::ChatRoom room;
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
	auto message = room.AddMessage(sender, galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE, "hello");
#else
	auto message = room.AddMessage(sender, "hello");
#endif

	const auto restored = universelan::test::serialize_round_trip(universelan::SendToChatRoomMessage(7, 42, message));
	ASSERT_NE(restored.message, nullptr);
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.message->GetUser().ToUint64(), sender.ToUint64());
	EXPECT_EQ(restored.message->GetContents(), "hello");
}
#endif
