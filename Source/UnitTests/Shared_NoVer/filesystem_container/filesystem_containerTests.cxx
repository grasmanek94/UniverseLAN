#include <filesystem_container/filesystem_container.hxx>

#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>
#include <vector>

namespace {

class TemporaryDirectory {
public:
    TemporaryDirectory() : path_(std::filesystem::temp_directory_path() / ("UniverseLANUnitTests_" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())))
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

TEST(FilesystemContainer, CreatesWritesReadsSharesAndRemovesFiles)
{
    TemporaryDirectory directory;
    filesystem_container::filesystem_container container(directory.path());
    const auto entry = container.get_or_create("nested/file.bin");
    const std::vector<char> contents{ 'a', '\0', 'b' };

    ASSERT_NE(entry, nullptr);
    EXPECT_TRUE(entry->exists());
    EXPECT_TRUE(entry->write(contents));
    EXPECT_EQ(entry->read(), contents);
    EXPECT_EQ(entry->read(nullptr, 3), 0U);
    EXPECT_EQ(entry->get_size(), contents.size());
    EXPECT_EQ(container.get_file_count(), 1U);

    const auto shared = container.create_shared("nested/file.bin", 77);
    ASSERT_EQ(shared, entry);
    EXPECT_EQ(container.get(77), entry);
    EXPECT_TRUE(container.exists(77));
    EXPECT_TRUE(container.remove(77));
    EXPECT_FALSE(container.exists("nested/file.bin"));
    EXPECT_EQ(container.get_file_count(), 0U);

    EXPECT_NE(container.create_shared("replacement.bin", 77), nullptr);
}

} // namespace
