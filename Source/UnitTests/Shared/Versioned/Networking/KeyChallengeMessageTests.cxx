#include <Networking/Messages/KeyChallengeMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>
TEST(KeyChallengeMessage, EncryptsHashesAndSerializesResponse) { constexpr uint64_t key = 0x12; constexpr uint64_t value = 0x34; universelan::KeyChallengeMessage message(galaxy::api::GalaxyID(42)); EXPECT_EQ(message.challenge(key, value).encrypted, key ^ value); message.response(key, key ^ value); EXPECT_EQ(message.encrypted, universelan::const_hash64_data(reinterpret_cast<const char*>(&value), sizeof(value))); const auto restored = universelan::test::serialize_round_trip(message); EXPECT_EQ(restored.id.ToUint64(), message.id.ToUint64()); EXPECT_EQ(restored.encrypted, message.encrypted); }
