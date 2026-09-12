#include <Networking/MessageUniqueID.hxx>

#include <gtest/gtest.h>

namespace {

TEST(MessageUniqueID, ConstructsWithAnAutomaticallyGeneratedIdentifier)
{
    const universelan::MessageUniqueID first;
    const universelan::MessageUniqueID second;

    EXPECT_LT(first.id, second.id);
}

TEST(MessageUniqueID, PreservesAnExplicitIdentifier)
{
    const universelan::MessageUniqueID identifier(42);

    EXPECT_EQ(identifier.id, 42U);
}

TEST(MessageUniqueID, ReturnsMonotonicallyIncreasingIdentifiers)
{
    const uint64_t first = universelan::MessageUniqueID::get();
    const uint64_t second = universelan::MessageUniqueID::get();

    EXPECT_LT(first, second);
}

} // namespace
