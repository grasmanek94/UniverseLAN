#include <Networking/Messages/JoinLobbyMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>
TEST(JoinLobbyMessage, SerializesRequestLobbyAndResult) { galaxy::api::GalaxyID lobby(42); universelan::JoinLobbyMessage message(7, lobby); const auto restored = universelan::test::serialize_round_trip(message); EXPECT_EQ(restored.request_id, 7U); EXPECT_EQ(restored.lobby_id.ToUint64(), lobby.ToUint64()); EXPECT_EQ(restored.result, galaxy::api::LOBBY_ENTER_RESULT_ERROR); }
