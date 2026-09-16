#include <ContainerGetByIndex.hxx>

#include <gtest/gtest.h>

#include <list>
#include <map>
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

TEST(ContainerIteratorGetByIndex, ReturnsIteratorForRequestedSequentialElement)
{
    std::vector<int> values{ 10, 20, 30 };

    const auto first = universelan::container_iterator_get_by_index(values, 0);
    const auto middle = universelan::container_iterator_get_by_index(values, 1);
    const auto last = universelan::container_iterator_get_by_index(values, 2);

    ASSERT_NE(first, values.end());
    ASSERT_NE(middle, values.end());
    ASSERT_NE(last, values.end());
    EXPECT_EQ(*first, 10);
    EXPECT_EQ(*middle, 20);
    EXPECT_EQ(*last, 30);
}

TEST(ContainerIteratorGetByIndex, ReturnsEndForEmptyAndOutOfRangeContainers)
{
    std::vector<int> empty;
    std::vector<int> values{ 10 };

    EXPECT_EQ(universelan::container_iterator_get_by_index(empty, 0), empty.end());
    EXPECT_EQ(universelan::container_iterator_get_by_index(values, values.size()), values.end());
}

TEST(MapIteratorGetByIndexWithForcedZero, PlacesPresentForcedKeyFirst)
{
    std::map<int, std::string> values{ {10, "first"}, {20, "forced"}, {30, "last"} };

    const auto forced = universelan::map_iterator_get_by_index_with_forced_zero_key(values, 0, 20);
    const auto first = universelan::map_iterator_get_by_index_with_forced_zero_key(values, 1, 20);
    const auto last = universelan::map_iterator_get_by_index_with_forced_zero_key(values, 2, 20);

    ASSERT_NE(forced, values.end());
    ASSERT_NE(first, values.end());
    ASSERT_NE(last, values.end());
    EXPECT_EQ(forced->first, 20);
    EXPECT_EQ(first->first, 10);
    EXPECT_EQ(last->first, 30);
}

TEST(MapIteratorGetByIndexWithForcedZero, ReturnsEndWhenForcedKeyIsAbsentOrIndexIsOutOfRange)
{
    std::map<int, std::string> values{ {10, "first"}, {20, "last"} };

    EXPECT_EQ(universelan::map_iterator_get_by_index_with_forced_zero_key(values, 0, 30), values.end());
    EXPECT_EQ(universelan::map_iterator_get_by_index_with_forced_zero_key(values, values.size(), 10), values.end());
}

} // namespace
