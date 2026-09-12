#include <Networking/Messages/UserHelloDataMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(UserHelloDataMessage, SerializesUserAndNicknameWithEmptyStats)
{
	galaxy::api::GalaxyID user(42);
	const auto restored = universelan::test::serialize_round_trip(universelan::UserHelloDataMessage(user, {}, "player"));
	EXPECT_EQ(restored.id.ToUint64(), user.ToUint64());
	EXPECT_EQ(restored.nickname, "player");
}

TEST(UserHelloDataMessage, SerializesPopulatedUserData)
{
	galaxy::api::GalaxyID user(42);
	universelan::AchievementsAndStatsContainer stats;
	stats.SetStat("score", 42);
	stats.SetUserData("rank", "gold");
	stats.SetRichPresence("state", "ready");
	stats.SetPlayTime(12);

	auto restored = universelan::test::serialize_round_trip(universelan::UserHelloDataMessage(user, stats, "player"));
	EXPECT_EQ(restored.id.ToUint64(), user.ToUint64());
	EXPECT_EQ(restored.nickname, "player");
	EXPECT_EQ(restored.asuc.GetStat("score").i, 42);
	EXPECT_EQ(restored.asuc.GetUserData("rank"), "gold");
	EXPECT_EQ(restored.asuc.GetRichPresence("state"), "ready");
	EXPECT_EQ(restored.asuc.GetPlayTime(), 12U);
}
