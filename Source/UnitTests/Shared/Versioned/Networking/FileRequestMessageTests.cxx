#include <Networking/Messages/FileRequestMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(FileRequestMessage, SerializesFilePayload)
{
	galaxy::api::SharedFileID id(42);
	const auto restored = universelan::test::serialize_round_trip(universelan::FileRequestMessage(7, id, "save.dat", { 'a', 'b' }));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.id, id);
	EXPECT_EQ(restored.filename, "save.dat");
	EXPECT_EQ(restored.data, std::vector<char>({ 'a', 'b' }));
}
