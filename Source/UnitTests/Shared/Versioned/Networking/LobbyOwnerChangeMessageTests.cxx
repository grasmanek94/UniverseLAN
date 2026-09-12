#include <Networking/Messages/LobbyOwnerChangeMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(LobbyOwnerChangeMessage, SerializesLobbyAndNewOwner)
{
	galaxy::api::GalaxyID lobby(42), owner(7);
	const auto restored = universelan::test::serialize_round_trip(universelan::LobbyOwnerChangeMessage(lobby, owner));
	EXPECT_EQ(restored.lobby_id.ToUint64(), lobby.ToUint64());
	EXPECT_EQ(restored.member_id.ToUint64(), owner.ToUint64());
}
