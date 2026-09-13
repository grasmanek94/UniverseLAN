#include <DynamicReturn.hxx>

#include <gtest/gtest.h>

namespace {

TEST(DynamicReturn, ProducesExpectedBooleanValues)
{
    EXPECT_TRUE(universelan::util::dynamic_return<bool>::value_true());
    EXPECT_FALSE(universelan::util::dynamic_return<bool>::value_false());
    EXPECT_TRUE(universelan::util::dynamic_return<bool>::value(1));
    EXPECT_FALSE(universelan::util::dynamic_return<bool>::value(0));
}

TEST(DynamicReturn, ConvertsValuesForNonBooleanTypes)
{
    EXPECT_EQ(universelan::util::dynamic_return<int>::value_true(), 1);
    EXPECT_EQ(universelan::util::dynamic_return<int>::value_false(), 0);
    EXPECT_EQ(universelan::util::dynamic_return<int>::value(42.8), 42);
}

} // namespace
