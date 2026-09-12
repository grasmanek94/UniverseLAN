#if GALAXY_BUILD_FEATURE_HAS_ICHAT

#include <ChatMessage.hxx>

#include <gtest/gtest.h>

namespace {

TEST(ChatMessage, StoresConstructionValues)
{
    const galaxy::api::GalaxyID sender(42);
    constexpr galaxy::api::ChatRoomID room = 7;
    constexpr uint32_t send_time = 123;

    #if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
    universelan::ChatMessage message(
        galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE, room, sender, send_time, "hello");
    EXPECT_EQ(message.GetType(), galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE);
    #else
    universelan::ChatMessage message(room, sender, send_time, "hello");
    #endif

    EXPECT_NE(message.GetID(), 0U);
    EXPECT_EQ(message.GetRoom(), room);
    EXPECT_EQ(message.GetUser().ToUint64(), sender.ToUint64());
    EXPECT_EQ(message.GetSendTime(), send_time);
    EXPECT_EQ(message.GetContents(), "hello");
}

TEST(ChatMessage, DefaultConstructionUsesEmptyValues)
{
    universelan::ChatMessage message;

    EXPECT_EQ(message.GetID(), 0U);
    EXPECT_EQ(message.GetRoom(), 0U);
    EXPECT_EQ(message.GetUser().ToUint64(), 0U);
    EXPECT_EQ(message.GetSendTime(), 0U);
    EXPECT_TRUE(message.GetContents().empty());
    #if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
    EXPECT_EQ(message.GetType(), galaxy::api::CHAT_MESSAGE_TYPE_UNKNOWN);
    #endif
}

} // namespace

#endif
