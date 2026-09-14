#if GALAXY_BUILD_FEATURE_HAS_ICHAT

#include <ChatRoom.hxx>

#include <gtest/gtest.h>

namespace {

TEST(ChatRoom, ManagesMembershipWithoutDuplicates)
{
    universelan::ChatRoom room;
    const galaxy::api::GalaxyID member(42);

    EXPECT_TRUE(room.AddMember(member));
    EXPECT_FALSE(room.AddMember(member));
    EXPECT_TRUE(room.IsMember(member));
    EXPECT_EQ(room.GetMemberCount(), 1U);
    EXPECT_TRUE(room.RemoveMember(member));
    EXPECT_FALSE(room.RemoveMember(member));
    EXPECT_FALSE(room.IsMember(member));
}

TEST(ChatRoom, TracksMessagesAndReadState)
{
    universelan::ChatRoom room;
    const galaxy::api::GalaxyID sender(42);

    #if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
    const auto first = room.AddMessage(sender, galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE, "short");
    const auto second = room.AddMessage(sender, galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE, "longer");
    #else
    const auto first = room.AddMessage(sender, "short");
    const auto second = room.AddMessage(sender, "longer");
    #endif

    EXPECT_EQ(room.GetMessageCount(), 2U);
    EXPECT_EQ(room.GetLongestMessage(), 6U);
    EXPECT_EQ(room.GetMessageByIndex(0), first);
    const auto newest_message = room.GetMessages(0, 1);
    ASSERT_EQ(newest_message.size(), 1U);
    EXPECT_EQ(newest_message.front(), second);
    const auto messages_before_second = room.GetMessages(second->GetID(), 1);
    ASSERT_EQ(messages_before_second.size(), 1U);
    EXPECT_EQ(messages_before_second.front(), first);
    EXPECT_EQ(room.GetUnreadCount(), 2U);
    EXPECT_FALSE(room.IsRead());

	room.MarkAsRead();
	EXPECT_TRUE(room.IsRead());
	EXPECT_EQ(room.GetUnreadCount(), 0U);

	#if GALAXY_BUILD_FEATURE_HAS_ICHAT_MESSAGETYPE
	room.AddMessage(sender, galaxy::api::CHAT_MESSAGE_TYPE_CHAT_MESSAGE, "new");
	#else
	room.AddMessage(sender, "new");
	#endif
	EXPECT_FALSE(room.IsRead());
	EXPECT_EQ(room.GetUnreadCount(), 1U);

	room.MarkAsUnread();
	EXPECT_FALSE(room.IsRead());
	EXPECT_EQ(room.GetUnreadCount(), 3U);
}

} // namespace

#endif
