#include <Networking/Messages/CreateLobbyResponseMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(CreateLobbyResponseMessage, SerializesRequestWithoutLobbyResponse)
{
	const auto restored = universelan::test::serialize_round_trip(universelan::CreateLobbyResponseMessage(7, nullptr));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.lobby, nullptr);
}

TEST(CreateLobbyResponseMessage, SerializesPopulatedLobbyResponse)
{
	galaxy::api::GalaxyID owner(42), member(7);
	auto lobby = std::make_shared<universelan::Lobby>(owner, galaxy::api::LOBBY_TYPE_PUBLIC, 12, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM);
	lobby->SetData("mode", "co-op");
	ASSERT_TRUE(lobby->AddMember(member));

	const auto restored = universelan::test::serialize_round_trip(universelan::CreateLobbyResponseMessage(9, lobby));
	ASSERT_NE(restored.lobby, nullptr);
	EXPECT_EQ(restored.request_id, 9U);
	EXPECT_EQ(restored.lobby->GetOwner().ToUint64(), owner.ToUint64());
	EXPECT_EQ(restored.lobby->GetMaxMembers(), 12U);
	EXPECT_TRUE(restored.lobby->IsJoinable());
	EXPECT_STREQ(restored.lobby->GetData("mode"), "co-op");
	EXPECT_TRUE(restored.lobby->IsMember(member));
}
