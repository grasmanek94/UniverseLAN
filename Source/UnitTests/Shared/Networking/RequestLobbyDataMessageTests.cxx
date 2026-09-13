#include <Networking/Messages/RequestLobbyDataMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(RequestLobbyDataMessage, SerializesRequestAndLobbyWithoutResponse)
{
	galaxy::api::GalaxyID lobby(42);
	const auto restored = universelan::test::serialize_round_trip(universelan::RequestLobbyDataMessage(7, lobby));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.lobby_id.ToUint64(), lobby.ToUint64());
	EXPECT_EQ(restored.data, nullptr);
	EXPECT_EQ(restored.fail_reason, galaxy::api::ILobbyDataRetrieveListener::FAILURE_REASON_UNDEFINED);
}

TEST(RequestLobbyDataMessage, SerializesPopulatedLobbyResponse)
{
	galaxy::api::GalaxyID owner(42), member(7);
	auto lobby = std::make_shared<universelan::Lobby>(owner, galaxy::api::LOBBY_TYPE_PUBLIC, 12, true, galaxy::api::LOBBY_TOPOLOGY_TYPE_FCM);
	lobby->SetData("mode", "co-op");
	ASSERT_TRUE(lobby->AddMember(member));

	const auto restored = universelan::test::serialize_round_trip(universelan::RequestLobbyDataMessage(9, owner, lobby));
	ASSERT_NE(restored.data, nullptr);
	EXPECT_EQ(restored.request_id, 9U);
	EXPECT_EQ(restored.lobby_id.ToUint64(), owner.ToUint64());
	EXPECT_EQ(restored.data->GetOwner().ToUint64(), owner.ToUint64());
	EXPECT_STREQ(restored.data->GetData("mode"), "co-op");
	EXPECT_TRUE(restored.data->IsMember(member));
}
