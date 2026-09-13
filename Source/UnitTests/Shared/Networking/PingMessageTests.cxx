#include <Networking/Messages/PingMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>
TEST(PingMessage, SerializesTimestamp) { const auto restored = universelan::test::serialize_round_trip(universelan::PingMessage(42)); EXPECT_EQ(restored.my_time, 42U); }
