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

TEST(ChatRoomManager, FindsOnlyExactTwoUserRooms)
{
    universelan::ChatRoomManager manager;
    const galaxy::api::GalaxyID first(1);
    const galaxy::api::GalaxyID second(2);
    const galaxy::api::GalaxyID third(3);

    const auto groupRoom = manager.CreateChatRoom();
    groupRoom->AddMember(first);
    groupRoom->AddMember(second);
    groupRoom->AddMember(third);
    const auto directRoom = manager.CreateChatRoom();
    directRoom->AddMember(first);
    directRoom->AddMember(second);

    EXPECT_EQ(manager.GetChatRoomWithUsers(first, second), directRoom);
    EXPECT_EQ(manager.GetChatRoomWithUsers(first, third), nullptr);
}

} // namespace

#endif
