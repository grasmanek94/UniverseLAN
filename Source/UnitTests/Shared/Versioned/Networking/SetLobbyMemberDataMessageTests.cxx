#include <Networking/Messages/SetLobbyMemberDataMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>
TEST(SetLobbyMemberDataMessage, SerializesLobbyMemberAndKeyValue) { galaxy::api::GalaxyID lobby(42), member(7); const auto restored = universelan::test::serialize_round_trip(universelan::SetLobbyMemberDataMessage(9, lobby, member, "key", "value")); EXPECT_EQ(restored.request_id, 9U); EXPECT_EQ(restored.lobby_id.ToUint64(), lobby.ToUint64()); EXPECT_EQ(restored.member_id.ToUint64(), member.ToUint64()); EXPECT_EQ(restored.value, "value"); }
