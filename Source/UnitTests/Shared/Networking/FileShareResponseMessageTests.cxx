#include <Networking/Messages/FileShareResponseMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(FileShareResponseMessage, SerializesSharedFileIdentity)
{
	galaxy::api::SharedFileID id(42);
	const auto restored = universelan::test::serialize_round_trip(universelan::FileShareResponseMessage(7, id, "save.dat"));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.id, id);
	EXPECT_EQ(restored.filename, "save.dat");
}
