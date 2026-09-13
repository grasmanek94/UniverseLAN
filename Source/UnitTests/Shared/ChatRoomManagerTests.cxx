#if GALAXY_BUILD_FEATURE_HAS_ICHAT

#include <ChatRoomManager.hxx>

#include <gtest/gtest.h>

namespace {

TEST(ChatRoomManager, CreatesFindsAndRemovesChatRooms)
{
    universelan::ChatRoomManager manager;

    const auto room = manager.CreateChatRoom();
    ASSERT_NE(room, nullptr);
    EXPECT_EQ(manager.GetChatRoom(room->GetID()), room);
    EXPECT_TRUE(manager.RemoveChatRoom(room->GetID()));
    EXPECT_EQ(manager.GetChatRoom(room->GetID()), nullptr);
    EXPECT_FALSE(manager.RemoveChatRoom(room->GetID()));
}

TEST(ChatRoomManager, AddsEachCopiedRoomOnlyOnce)
{
    universelan::ChatRoomManager manager;
    universelan::ChatRoom room;

    EXPECT_TRUE(manager.AddChatRoom(room));
    EXPECT_FALSE(manager.AddChatRoom(room));
    ASSERT_NE(manager.GetChatRoom(room.GetID()), nullptr);
    EXPECT_EQ(manager.GetChatRoom(room.GetID())->GetID(), room.GetID());
}

} // namespace

#endif
