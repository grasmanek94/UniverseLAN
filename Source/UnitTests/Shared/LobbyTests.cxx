#include <Lobby.hxx>

#include <gtest/gtest.h>

#include <array>

namespace {

TEST(Lobby, ManagesMembersAndCapacity)
{
    universelan::Lobby lobby;
    const galaxy::api::GalaxyID first_member(1);
    const galaxy::api::GalaxyID second_member(2);

    EXPECT_TRUE(lobby.IsJoinable());
    EXPECT_TRUE(lobby.IsFull());
    EXPECT_TRUE(lobby.AddMember(first_member));
    EXPECT_FALSE(lobby.AddMember(first_member));
    EXPECT_TRUE(lobby.IsMember(first_member));

    lobby.SetMaxMembers(2);
    EXPECT_FALSE(lobby.IsFull());
    EXPECT_TRUE(lobby.AddMember(second_member));
    EXPECT_TRUE(lobby.IsFull());
    EXPECT_EQ(lobby.GetMemberCount(), 2U);
    EXPECT_EQ(lobby.GetMemberByIndex(2).ToUint64(), 0U);

    EXPECT_TRUE(lobby.RemoveMember(first_member));
    EXPECT_FALSE(lobby.RemoveMember(first_member));
    EXPECT_FALSE(lobby.IsMember(first_member));
}

TEST(Lobby, ReturnsForcedMemberFirstWithoutDuplicatingOtherMembers)
{
    universelan::Lobby lobby;
    const galaxy::api::GalaxyID first_member(1);
    const galaxy::api::GalaxyID forced_member(2);
    const galaxy::api::GalaxyID last_member(3);

    ASSERT_TRUE(lobby.AddMember(first_member));
    ASSERT_TRUE(lobby.AddMember(forced_member));
    ASSERT_TRUE(lobby.AddMember(last_member));

    std::array<galaxy::api::GalaxyID, 2> expected_other_members{};
    std::size_t expected_other_count = 0;
    for (std::size_t index = 0; index < lobby.GetMemberCount(); ++index)
    {
        const galaxy::api::GalaxyID member = lobby.GetMemberByIndex(index);
        if (member != forced_member) expected_other_members.at(expected_other_count++) = member;
    }

    EXPECT_EQ(lobby.GetMemberByIndexWithForcedZero(0, forced_member), forced_member);
    ASSERT_EQ(expected_other_count, 2U);
    EXPECT_EQ(lobby.GetMemberByIndexWithForcedZero(1, forced_member), expected_other_members[0]);
    EXPECT_EQ(lobby.GetMemberByIndexWithForcedZero(2, forced_member), expected_other_members[1]);
}

TEST(Lobby, ReturnsInvalidMemberWhenForcedMemberIsAbsentOrIndexIsOutOfRange)
{
    universelan::Lobby lobby;
    const galaxy::api::GalaxyID member(1);
    const galaxy::api::GalaxyID absent_member(2);

    ASSERT_TRUE(lobby.AddMember(member));

    EXPECT_FALSE(lobby.GetMemberByIndexWithForcedZero(0, absent_member).IsValid());
    EXPECT_FALSE(lobby.GetMemberByIndexWithForcedZero(lobby.GetMemberCount(), member).IsValid());
}

TEST(Lobby, StoresLobbyAndMemberDataAndRejectsUnknownMembers)
{
    universelan::Lobby lobby;
    const galaxy::api::GalaxyID member(1);

    EXPECT_STREQ(lobby.GetData("missing"), "");
    lobby.SetData("mode", "coop");
    EXPECT_STREQ(lobby.GetData("mode"), "coop");
    EXPECT_EQ(lobby.GetDataCount(), 1U);

    EXPECT_FALSE(lobby.SetMemberData(member, "rank", "1"));
    EXPECT_EQ(lobby.GetMemberDataCount(member), 0U);
    EXPECT_TRUE(lobby.AddMember(member));
    EXPECT_TRUE(lobby.SetMemberData(member, "rank", "1"));
    EXPECT_STREQ(lobby.GetMemberData(member, "rank"), "1");
    EXPECT_EQ(lobby.GetMemberDataCount(member), 1U);
}

TEST(Lobby, DeliversMessagesOnlyFromMembersAndRespectsDestinationCapacity)
{
    universelan::Lobby lobby;
    const galaxy::api::GalaxyID member(1);
    const galaxy::api::GalaxyID outsider(2);
    galaxy::api::GalaxyID sender;
    std::array<char, 3> destination{};
    const std::array<char, 3> expected_destination{'m', 'e', 's'};

    EXPECT_EQ(lobby.SendMsg(outsider, "message"), 0U);
    ASSERT_TRUE(lobby.AddMember(member));
    const uint32_t message_id = lobby.SendMsg(member, "message");
    ASSERT_NE(message_id, 0U);

    EXPECT_EQ(lobby.GetMsg(message_id, sender, destination.data(), static_cast<uint32_t>(destination.size())), 3U);
    EXPECT_EQ(sender.ToUint64(), member.ToUint64());
    EXPECT_EQ(destination, expected_destination);
    EXPECT_EQ(lobby.GetMsg(message_id + 1, sender, destination.data(), static_cast<uint32_t>(destination.size())), 0U);
}

} // namespace
