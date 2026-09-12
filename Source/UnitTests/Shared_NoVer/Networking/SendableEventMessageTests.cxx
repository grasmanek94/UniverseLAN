#include <Networking/SendableEventMessage.hxx>

#include <gtest/gtest.h>

namespace universelan {

class NamedMessage {
public:
    UniqueClassId_Declare(NamedMessage)
};

} // namespace universelan

namespace {

static_assert(universelan::NamedMessage::UniqueClassId() == universelan::const_hash("NamedMessage", sizeof("NamedMessage")));

TEST(SendableEventMessage, GeneratesAStableCompileTimeClassIdentifier)
{
    EXPECT_EQ(universelan::NamedMessage::UniqueClassId(), universelan::const_hash("NamedMessage", sizeof("NamedMessage")));
}

} // namespace
