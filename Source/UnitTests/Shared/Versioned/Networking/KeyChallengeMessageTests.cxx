#include <Networking/Messages/KeyChallengeMessage.hxx>
#include <gtest/gtest.h>
TEST(KeyChallengeMessage, EncryptsChallengeAndHashesResponse) { constexpr uint64_t key = 0x12; constexpr uint64_t value = 0x34; universelan::KeyChallengeMessage message(galaxy::api::GalaxyID(42)); EXPECT_EQ(message.challenge(key, value).encrypted, key ^ value); EXPECT_EQ(message.response(key, key ^ value).encrypted, universelan::const_hash64_data(reinterpret_cast<const char*>(&value), sizeof(value))); }
