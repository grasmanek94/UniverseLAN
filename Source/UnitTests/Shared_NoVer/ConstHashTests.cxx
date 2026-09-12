#include <ConstHash.hxx>

#include <gtest/gtest.h>

#include <array>
#include <string>

namespace {

static_assert(universelan::const_hash("hello") == 0x4f9f2cab);
static_assert(universelan::const_hash64("hello") == 0xa430d84680aabd0bULL);

TEST(ConstHash, ReturnsInitialValueForEmptyInput)
{
    EXPECT_EQ(universelan::const_hash(""), 0x811c9dc5U);
    EXPECT_EQ(universelan::const_hash64(""), 0xcbf29ce484222325ULL);
    EXPECT_EQ(universelan::const_hash64_data("", 0), 0xcbf29ce484222325ULL);
}

TEST(ConstHash, ProducesKnownFnv1aValuesForStringInputs)
{
    const std::string value = "hello";

    EXPECT_EQ(universelan::const_hash(value), 0x4f9f2cabU);
    EXPECT_EQ(universelan::const_hash64(value), 0xa430d84680aabd0bULL);
}

TEST(ConstHash, HashesEmbeddedNullBytesWhenGivenAnExplicitSize)
{
    constexpr std::array<char, 3> value{ 'a', '\0', 'b' };

    EXPECT_EQ(universelan::const_hash64_data(value.data(), value.size()), 0xe5d29919042666b2ULL);
    EXPECT_EQ(universelan::const_hash64_data(value.data(), value.size()),
        universelan::const_hash64_data_loop(value.data(), value.size()));
}

TEST(ConstHash, RespectsCustomInitialValues)
{
    constexpr uint64_t initialValue = 7;

    EXPECT_EQ(universelan::const_hash64_data("data", 4, initialValue),
        universelan::const_hash64_data_loop("data", 4, initialValue));
}

} // namespace
