#if GALAXY_BUILD_FEATURE_HAS_ICHAT
#include <Networking/Messages/RequestChatRoomMessagesMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(RequestChatRoomMessagesMessage, SerializesRequestAndPaginationWithoutMessages)
{
	const auto restored = universelan::test::serialize_round_trip(universelan::RequestChatRoomMessagesMessage(7, 42, 5, 3));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.id, 42U);
	EXPECT_EQ(restored.limit, 5U);
	EXPECT_EQ(restored.oldest_message, 3U);
	EXPECT_TRUE(restored.messages.empty());
}

TEST(RequestChatRoomMessagesMessage, SerializesMessageHistory)
{
	galaxy::api::GalaxyID sender(42);
	universelan::ChatRoom room;
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
	auto first = room.AddMessage(sender, galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE, "first");
	auto second = room.AddMessage(sender, galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE, "second");
#else
	auto first = room.AddMessage(sender, "first");
	auto second = room.AddMessage(sender, "second");
#endif
	const universelan::ChatRoom::messages_t messages{ first, second };
	const auto restored = universelan::test::serialize_round_trip(universelan::RequestChatRoomMessagesMessage(7, 42, 5, 3, messages));
	EXPECT_EQ(restored.limit, 5U);
	ASSERT_EQ(restored.messages.size(), 2U);
	EXPECT_EQ(restored.messages.at(0)->GetContents(), "first");
	EXPECT_EQ(restored.messages.at(1)->GetContents(), "second");
}
#endif
