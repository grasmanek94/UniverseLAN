#include <Networking/Messages/RequestSpecificUserDataMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(RequestSpecificUserDataMessage, SerializesRequestTypeAndUserWithoutResponse)
{
	galaxy::api::GalaxyID user(42);
	const auto restored = universelan::test::serialize_round_trip(universelan::RequestSpecificUserDataMessage(universelan::RequestSpecificUserDataMessage::RequestTypeRichPresence, 7, user));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.id.ToUint64(), user.ToUint64());
	EXPECT_EQ(restored.type, universelan::RequestSpecificUserDataMessage::RequestTypeRichPresence);
	EXPECT_FALSE(restored.found);
	EXPECT_TRUE(restored.nickname.empty());
}

TEST(RequestSpecificUserDataMessage, SerializesPopulatedUserDataResponse)
{
	galaxy::api::GalaxyID user(42);
	universelan::RequestSpecificUserDataMessage message(universelan::RequestSpecificUserDataMessage::RequestTypeAchievementsAndStats, 9, user);
	message.found = true;
	message.nickname = "player";
	message.asuc.SetStat("score", 42);
	message.asuc.SetUserData("rank", "gold");
	message.asuc.SetRichPresence("state", "ready");
	message.asuc.SetPlayTime(12);

	auto restored = universelan::test::serialize_round_trip(message);
	EXPECT_TRUE(restored.found);
	EXPECT_EQ(restored.nickname, "player");
	EXPECT_EQ(restored.asuc.GetStat("score").i, 42);
	EXPECT_EQ(restored.asuc.GetUserData("rank"), "gold");
	EXPECT_EQ(restored.asuc.GetRichPresence("state"), "ready");
	EXPECT_EQ(restored.asuc.GetPlayTime(), 12U);
}
