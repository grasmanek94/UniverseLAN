#include <SharedLibUtils.hxx>

#include <gtest/gtest.h>

#include <stdexcept>

namespace {

TEST(SharedLibUtils, RejectsNullAndEmptyFunctionNamesBeforeLoadingALibrary)
{
    EXPECT_THROW(universelan::SharedLibUtils::get_func_ptr(nullptr), std::runtime_error);
    EXPECT_THROW(universelan::SharedLibUtils::get_func_ptr(""), std::runtime_error);
    EXPECT_THROW(universelan::SharedLibUtils::get_function_match(nullptr), std::runtime_error);
    EXPECT_THROW(universelan::SharedLibUtils::get_function_match(""), std::runtime_error);
}

} // namespace
