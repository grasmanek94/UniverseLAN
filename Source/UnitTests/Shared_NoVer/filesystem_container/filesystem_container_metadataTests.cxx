#include <filesystem_container/filesystem_container_metadata.hxx>

#include <gtest/gtest.h>

namespace {

TEST(FileEntryMetadataContainer, ReturnsDefaultsAndConvertsStoredValues)
{
    filesystem_container::file_entry_metadata_container metadata;

    EXPECT_TRUE(metadata.empty());
    EXPECT_EQ(metadata.get_ll("missing", 7), 7);
    EXPECT_EQ(metadata.get_str("missing", "fallback"), "fallback");
    metadata.set("number", 42LL);
    metadata.set("text", "value");
    metadata.set("invalid", "not-a-number");
    EXPECT_EQ(metadata.get_ll("number"), 42);
    EXPECT_EQ(metadata.get_ll("invalid", 9), 9);
    EXPECT_EQ(metadata.get_str("text"), "value");
    EXPECT_EQ(metadata.size(), 3U);
}

TEST(FileEntryMetadata, ResetsShareIdAndMetadata)
{
    filesystem_container::file_entry_metadata metadata;
    metadata.share_id = 99;
    metadata.user_metadata.set("user", "value");
    metadata.set_timestamp(123);

    EXPECT_FALSE(metadata.empty());
    EXPECT_EQ(metadata.get_timestamp(), 123);
    metadata.reset();
    EXPECT_TRUE(metadata.empty());
    EXPECT_EQ(metadata.share_id, 0U);
}

} // namespace
