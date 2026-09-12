#include <Networking/Messages/OnlineStatusChangeMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>
TEST(OnlineStatusChangeMessage, SerializesUserAndStatus) { galaxy::api::GalaxyID id(42); const auto restored = universelan::test::serialize_round_trip(universelan::OnlineStatusChangeMessage(id, true)); EXPECT_EQ(restored.id.ToUint64(), id.ToUint64()); EXPECT_TRUE(restored.online); }
