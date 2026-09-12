#include <filesystem_container/filesystem_container_utils.hxx>

#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>
#include <stdexcept>

namespace {

TEST(FilesystemContainerUtils, EncodesReservedCharactersAndRoundTripsValues)
{
    const std::string value = "folder/name%?:\x01";
    const std::string encoded = filesystem_container::filename_encode(value);

    EXPECT_EQ(encoded, "folder/name%25%3F%3A%01");
    EXPECT_EQ(filesystem_container::filename_decode(encoded), value);
    EXPECT_EQ(filesystem_container::filename_encode_with_slashes(value), "folder%2Fname%25%3F%3A%01");
}

TEST(FilesystemContainerUtils, RejectsPathTraversalOutsideTheSandbox)
{
    const std::filesystem::path base = std::filesystem::temp_directory_path() / "UniverseLANUnitTestsSandbox";

    EXPECT_TRUE(filesystem_container::inside_basepath(base, "nested/file"));
    EXPECT_FALSE(filesystem_container::inside_basepath(base, "../outside"));
    EXPECT_THROW(filesystem_container::sandbox_secure_path_concat(base, "../outside"), std::runtime_error);
    EXPECT_NO_THROW(filesystem_container::sandbox_secure_path_concat(base, ""));
}

TEST(FilesystemContainerUtils, NormalizesPathsAndProvidesCurrentEpochSeconds)
{
    const std::filesystem::path relative = filesystem_container::sanitize_relative_path("a/../b");
    EXPECT_EQ(relative, std::filesystem::path("b"));
    EXPECT_TRUE(filesystem_container::sanitize_path(relative).is_absolute());

    const uint64_t before = filesystem_container::file_time_now_since_epoch();
    const uint64_t after = filesystem_container::file_time_now_since_epoch();
    EXPECT_LE(before, after);
}

} // namespace
