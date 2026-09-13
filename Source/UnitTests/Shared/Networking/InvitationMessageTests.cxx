#include <Networking/Messages/InvitationMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(InvitationMessage, SerializesRecipientAndConnectionString)
{
	galaxy::api::GalaxyID user(42);
	const auto restored = universelan::test::serialize_round_trip(universelan::InvitationMessage(7, user, "127.0.0.1:1234"));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.user_id.ToUint64(), user.ToUint64());
	EXPECT_EQ(restored.connection_string, "127.0.0.1:1234");
}
