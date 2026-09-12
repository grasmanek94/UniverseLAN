#include <Networking/Messages/PingMessage.hxx>
#include <gtest/gtest.h>
TEST(PingMessage, PreservesTimestamp) { EXPECT_EQ(universelan::PingMessage(42).my_time, 42U); EXPECT_EQ(universelan::PingMessage().my_time, 0U); }
