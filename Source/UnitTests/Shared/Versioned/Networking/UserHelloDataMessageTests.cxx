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
