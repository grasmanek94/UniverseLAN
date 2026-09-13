#include <Networking/Messages/SetLobbyJoinableMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>
TEST(SetLobbyJoinableMessage, SerializesRequestLobbyAndJoinableState) { galaxy::api::GalaxyID lobby(42); universelan::SetLobbyJoinableMessage message(7, lobby, false); const auto restored = universelan::test::serialize_round_trip(message); EXPECT_EQ(restored.request_id, 7U); EXPECT_EQ(restored.lobby_id.ToUint64(), lobby.ToUint64()); EXPECT_FALSE(restored.joinable); EXPECT_TRUE(restored.success); }
