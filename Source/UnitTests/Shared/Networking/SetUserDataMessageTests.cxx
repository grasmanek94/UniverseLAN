#include <Networking/Messages/SetUserDataMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>
TEST(SetUserDataMessage, SerializesIdentityAndKeyValue) { galaxy::api::GalaxyID id(42); const auto restored = universelan::test::serialize_round_trip(universelan::SetUserDataMessage(id, "key", "value")); EXPECT_EQ(restored.id.ToUint64(), id.ToUint64()); EXPECT_EQ(restored.key, "key"); EXPECT_EQ(restored.value, "value"); }
