#include <ContainerGetByIndex.hxx>

#include <gtest/gtest.h>

#include <list>
#include <string>
#include <vector>

namespace {

TEST(ContainerGetByIndex, ReturnsRequestedValueFromSequentialContainers)
{
    const std::vector<int> values{ 10, 20, 30 };
    const std::list<std::string> names{ "first", "second" };

    EXPECT_EQ(universelan::container_get_by_index(values, 0), 10);
    EXPECT_EQ(universelan::container_get_by_index(values, 2), 30);
    EXPECT_EQ(universelan::container_get_by_index(names, 1), "second");
}

TEST(ContainerGetByIndex, ReturnsEmptyOptionalForEmptyAndOutOfRangeContainers)
{
    const std::vector<int> empty;
    const std::vector<int> values{ 10 };

    EXPECT_FALSE(universelan::container_get_by_index(empty, 0).has_value());
    EXPECT_FALSE(universelan::container_get_by_index(values, values.size()).has_value());
}

TEST(ContainerGetByIndex, ReturnsProvidedDefaultForOutOfRangeIndex)
{
    const std::vector<std::string> values{ "value" };

    EXPECT_EQ(universelan::container_get_by_index(values, 0, std::string("fallback")), "value");
    EXPECT_EQ(universelan::container_get_by_index(values, 1, std::string("fallback")), "fallback");
}

} // namespace
