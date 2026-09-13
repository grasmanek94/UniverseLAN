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

TEST(RequestChatRoomWithUserMessage, SerializesPopulatedChatRoomResponse)
{
	galaxy::api::GalaxyID user(42);
	auto room = std::make_shared<universelan::ChatRoom>();
	ASSERT_TRUE(room->AddMember(user));
#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
	room->AddMessage(user, galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE, "hello");
#else
	room->AddMessage(user, "hello");
#endif

	universelan::RequestChatRoomWithUserMessage message(7, user);
	message.chat_room = room;
	const auto restored = universelan::test::serialize_round_trip(message);
	ASSERT_NE(restored.chat_room, nullptr);
	EXPECT_TRUE(restored.chat_room->IsMember(user));
	EXPECT_EQ(restored.chat_room->GetMessageCount(), 1U);
	EXPECT_EQ(restored.chat_room->GetMessageByIndex(0)->GetContents(), "hello");
}
#endif
