#include <LobbyManager.hxx>

#include <gtest/gtest.h>

namespace {

TEST(LobbyManager, CreatesAndFindsLobbyWithConfiguredState)
{
    universelan::LobbyManager manager;
    const galaxy::api::GalaxyID owner(42);
    const auto type = static_cast<galaxy::api::LobbyType>(0);
    const auto topology = static_cast<galaxy::api::LobbyTopologyType>(0);

    const auto lobby = manager.CreateLobby(owner, type, 4, false, topology);

    ASSERT_NE(lobby, nullptr);
    EXPECT_EQ(manager.GetLobby(lobby->GetID()), lobby);
    EXPECT_EQ(manager.GetLobbies().size(), 1U);
    EXPECT_EQ(lobby->GetOwner().ToUint64(), owner.ToUint64());
    EXPECT_EQ(lobby->GetType(), type);
    EXPECT_EQ(lobby->GetTopology(), topology);
    EXPECT_EQ(lobby->GetMaxMembers(), 4U);
    EXPECT_FALSE(lobby->IsJoinable());
}

TEST(LobbyManager, ReturnsNullForUnknownLobbyAndRemovesKnownLobbyOnce)
{
    universelan::LobbyManager manager;
    const galaxy::api::GalaxyID unknown(42);
    const auto type = static_cast<galaxy::api::LobbyType>(0);
    const auto topology = static_cast<galaxy::api::LobbyTopologyType>(0);

    EXPECT_EQ(manager.GetLobby(unknown), nullptr);
    EXPECT_FALSE(manager.RemoveLobby(unknown));

    const auto lobby = manager.CreateLobby(unknown, type, 1, true, topology);
    ASSERT_NE(lobby, nullptr);
    EXPECT_TRUE(manager.RemoveLobby(lobby->GetID()));
    EXPECT_EQ(manager.GetLobby(lobby->GetID()), nullptr);
    EXPECT_FALSE(manager.RemoveLobby(lobby->GetID()));
}

} // namespace
