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
