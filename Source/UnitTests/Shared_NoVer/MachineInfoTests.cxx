#include <MachineInfo.hxx>

#include <gtest/gtest.h>

namespace {

TEST(MachineInfo, ReportsAProcessAndConsistentKnownPaths)
{
    const universelan::MachineInfo info;
    const auto paths = info.GetKnownPaths();

    EXPECT_GT(info.GetProcessID(), 0U);
    EXPECT_EQ(info.GetOperatingPath().available, paths.chosen_operating_directory.available);
    EXPECT_EQ(info.GetBootFile().available, paths.boot_file_path.available);
    if (paths.chosen_operating_directory.available) {
        EXPECT_FALSE(paths.chosen_operating_directory.path.empty());
    }
}

} // namespace
