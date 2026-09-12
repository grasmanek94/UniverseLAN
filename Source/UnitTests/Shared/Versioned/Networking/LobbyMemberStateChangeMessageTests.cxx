#include <Networking/Messages/LobbyMemberStateChangeMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(LobbyMemberStateChangeMessage, SerializesLobbyMemberAndState)
{
	galaxy::api::GalaxyID lobby(42), member(7);
	const auto restored = universelan::test::serialize_round_trip(universelan::LobbyMemberStateChangeMessage(lobby, member, galaxy::api::LOBBY_MEMBER_STATE_CHANGED_ENTERED));
	EXPECT_EQ(restored.lobby_id.ToUint64(), lobby.ToUint64());
	EXPECT_EQ(restored.member_id.ToUint64(), member.ToUint64());
	EXPECT_EQ(restored.state, galaxy::api::LOBBY_MEMBER_STATE_CHANGED_ENTERED);
}
