#include <Networking/Messages/RichPresenceChangeMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>
TEST(RichPresenceChangeMessage, SerializesSetActionAndValue) { galaxy::api::GalaxyID id(42); const auto restored = universelan::test::serialize_round_trip(universelan::RichPresenceChangeMessage(7, id, universelan::RichPresenceChangeMessage::ACTION_SET, "key", "value")); EXPECT_EQ(restored.request_id, 7U); EXPECT_EQ(restored.id.ToUint64(), id.ToUint64()); EXPECT_EQ(restored.action, universelan::RichPresenceChangeMessage::ACTION_SET); EXPECT_EQ(restored.value, "value"); }
