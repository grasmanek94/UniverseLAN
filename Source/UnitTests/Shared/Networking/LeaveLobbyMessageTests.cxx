#include <Networking/Messages/LeaveLobbyMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>
TEST(LeaveLobbyMessage, SerializesRequestAndLobby) { galaxy::api::GalaxyID lobby(42); universelan::LeaveLobbyMessage message(7, lobby); const auto restored = universelan::test::serialize_round_trip(message); EXPECT_EQ(restored.request_id, 7U); EXPECT_EQ(restored.lobby_id.ToUint64(), lobby.ToUint64()); }
