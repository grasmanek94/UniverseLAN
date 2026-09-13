#include <Networking/Messages/FileShareMessage.hxx>
#include "MessageSerializationTestUtils.hxx"
#include <gtest/gtest.h>

TEST(FileShareMessage, SerializesFilePayload)
{
	const auto restored = universelan::test::serialize_round_trip(universelan::FileShareMessage(7, "save.dat", { 'a', 'b' }));
	EXPECT_EQ(restored.request_id, 7U);
	EXPECT_EQ(restored.filename, "save.dat");
	EXPECT_EQ(restored.data, std::vector<char>({ 'a', 'b' }));
}
