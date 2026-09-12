#include <SharedFileUtils.hxx>

#include <gtest/gtest.h>

#include <array>
#include <chrono>
#include <filesystem>

namespace {

class TemporaryDirectory {
public:
    TemporaryDirectory() : path_(std::filesystem::temp_directory_path() / ("UniverseLANSharedFileTests_" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())))
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

TEST(SharedFileUtils, WritesReadsAndRemovesFilesByNameAndSharedId)
{
    TemporaryDirectory directory;
    universelan::SharedFileUtils files(directory.path());
    constexpr char contents[] = "abcdef";
    const std::vector<char> expected_contents{'a', 'b', 'c', 'd', 'e', 'f'};
    const std::array<char, 2> expected_buffer{'c', 'd'};

    constexpr galaxy::api::SharedFileID id = 42;
    ASSERT_TRUE(files.Write(files.storage, "save.dat", contents, 6));
    ASSERT_TRUE(files.CopyFromLocalToShared("save.dat", id));
    EXPECT_EQ(files.GetSharedFileID(files.shared, "save.dat"), id);
    EXPECT_TRUE(files.Exists(files.shared, "save.dat"));
    EXPECT_TRUE(files.Exists(files.shared, id));
    EXPECT_EQ(files.GetSize(files.shared, id), 6U);
    EXPECT_EQ(files.Read(files.shared, "save.dat"), expected_contents);

    std::array<char, 2> buffer{};
    EXPECT_EQ(files.Read(files.shared, id, buffer.data(), buffer.size(), 2), 2U);
    EXPECT_EQ(buffer, expected_buffer);
    EXPECT_TRUE(files.Remove(files.shared, id));
    EXPECT_FALSE(files.Exists(files.shared, "save.dat"));
}

TEST(SharedFileUtils, RejectsInvalidInputs)
{
    TemporaryDirectory directory;
    universelan::SharedFileUtils files(directory.path());

    EXPECT_FALSE(files.Write(nullptr, "file", "x", 1));
    EXPECT_FALSE(files.Write(files.storage, nullptr, "x", 1));
    EXPECT_FALSE(files.Write(files.storage, "", "x", 1));
    EXPECT_FALSE(files.Exists(nullptr, "file"));
    EXPECT_FALSE(files.Remove(files.storage, static_cast<galaxy::api::SharedFileID>(0)));
    EXPECT_TRUE(files.Read(files.storage, static_cast<galaxy::api::SharedFileID>(0)).empty());
}

} // namespace
