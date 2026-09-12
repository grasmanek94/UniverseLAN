#include <GlobalUniqueID.hxx>

#include <gtest/gtest.h>

namespace {

TEST(GlobalUniqueID, ReturnsMonotonicallyIncreasingValues)
{
    const uint64_t first = universelan::GlobalUniqueID::get();
    const uint64_t second = universelan::GlobalUniqueID::get();

    EXPECT_LT(first, second);
}

} // namespace
