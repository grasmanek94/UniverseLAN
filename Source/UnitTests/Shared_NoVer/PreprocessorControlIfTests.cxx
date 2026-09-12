#include <PreprocessorControlIf.hxx>

#include <gtest/gtest.h>

static_assert(UNIVERSELAN_PP_IF(0, 1, 2) == 2);
static_assert(UNIVERSELAN_PP_IF(1, 1, 2) == 1);

namespace {

TEST(PreprocessorControlIf, SelectsTheExpectedValueAtCompileTime)
{
    EXPECT_EQ(UNIVERSELAN_PP_IF(0, 10, 20), 20);
    EXPECT_EQ(UNIVERSELAN_PP_IF(1, 10, 20), 10);
}

} // namespace
