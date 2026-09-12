#include <filesystem_container/filesystem_container.hxx>

#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>

namespace {

class TemporaryDirectory {
public:
    TemporaryDirectory() : path_(std::filesystem::temp_directory_path() / ("UniverseLANEntryTests_" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())))
    {
        std::filesystem::create_directories(path_);
    }

    ~TemporaryDirectory()
    {
        std::error_code error;
        std::filesystem::remove_all(path_, error);
    }

    const std::filesystem::path& path() const { return path_; }

private:
    std::filesystem::path path_;
};

TEST(FilesystemEntry, PersistsMetadataAndMaintainsCacheIndexState)
{
    TemporaryDirectory directory;
    {
        filesystem_container::filesystem_container container(directory.path());
        const auto entry = container.get_or_create("file.bin");
        ASSERT_NE(entry, nullptr);
        entry->set_metadata("key", "value");
        entry->set_timestamp_metadata(123);
        entry->set_cache_index(4);

        ASSERT_TRUE(entry->save_metadata());
        EXPECT_EQ(entry->get_metadata("key"), "value");
        EXPECT_EQ(entry->get_metadata("missing", "fallback"), "fallback");
        EXPECT_EQ(entry->get_metadata_count(), 1U);
        EXPECT_EQ(entry->get_timestamp_metadata(), 123U);
        EXPECT_EQ(entry->get_cache_index(), 4U);
        entry->clear_cache_index();
        EXPECT_FALSE(entry->get_cache_index().has_value());
    }

    filesystem_container::filesystem_container reloaded(directory.path());
    const auto entry = reloaded.get("file.bin");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->get_metadata("key"), "value");
    EXPECT_EQ(entry->get_timestamp_metadata(), 123U);
}

} // namespace
