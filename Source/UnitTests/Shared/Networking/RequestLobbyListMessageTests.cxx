#include <Networking/Messages/RequestLobbyListMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(RequestLobbyListMessage, SerializesErrorResponseWithoutLobbies)
{
	const auto restored = universelan::test::serialize_round_trip(universelan::RequestLobbyListMessage(7, true, {}));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_TRUE(restored.error);
	EXPECT_TRUE(restored.lobby_list.empty());
}

TEST(RequestLobbyListMessage, SerializesPopulatedLobbyList)
{
	galaxy::api::GalaxyID first_owner(42), second_owner(7);
	universelan::LobbyManager::lobbies_t lobbies;
	lobbies.emplace(first_owner, std::make_shared<universelan::Lobby>(first_owner, galaxy::api::LOBBY_TYPE_PUBLIC, 12, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM));
	lobbies.emplace(second_owner, std::make_shared<universelan::Lobby>(second_owner, galaxy::api::LOBBY_TYPE_PUBLIC, 4, false, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM));
	lobbies.at(first_owner)->SetData("mode", "co-op");

	const auto restored = universelan::test::serialize_round_trip(universelan::RequestLobbyListMessage(9, false, lobbies));
	ASSERT_EQ(restored.lobby_list.size(), 2U);
	ASSERT_NE(restored.lobby_list.at(first_owner), nullptr);
	ASSERT_NE(restored.lobby_list.at(second_owner), nullptr);
	EXPECT_EQ(restored.lobby_list.at(first_owner)->GetMaxMembers(), 12U);
	EXPECT_TRUE(restored.lobby_list.at(first_owner)->IsJoinable());
	EXPECT_STREQ(restored.lobby_list.at(first_owner)->GetData("mode"), "co-op");
	EXPECT_EQ(restored.lobby_list.at(second_owner)->GetMaxMembers(), 4U);
	EXPECT_FALSE(restored.lobby_list.at(second_owner)->IsJoinable());
}
