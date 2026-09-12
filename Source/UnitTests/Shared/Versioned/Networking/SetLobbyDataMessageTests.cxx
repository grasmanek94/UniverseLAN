#include <Networking/Messages/SetLobbyDataMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>
TEST(SetLobbyDataMessage, SerializesLobbyKeyValue) { galaxy::api::GalaxyID id(42); const auto restored = universelan::test::serialize_round_trip(universelan::SetLobbyDataMessage(7, id, "key", "value")); EXPECT_EQ(restored.request_id, 7U); EXPECT_EQ(restored.lobby_id.ToUint64(), id.ToUint64()); EXPECT_EQ(restored.key, "key"); EXPECT_EQ(restored.value, "value"); EXPECT_TRUE(restored.success); }
