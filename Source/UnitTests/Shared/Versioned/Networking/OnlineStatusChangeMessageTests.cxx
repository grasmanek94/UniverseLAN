#include <Networking/Messages/OnlineStatusChangeMessage.hxx>
#include <gtest/gtest.h>
TEST(OnlineStatusChangeMessage, PreservesUserAndStatus) { galaxy::api::GalaxyID id(42); universelan::OnlineStatusChangeMessage message(id, true); EXPECT_EQ(message.id.ToUint64(), id.ToUint64()); EXPECT_TRUE(message.online); EXPECT_FALSE(universelan::OnlineStatusChangeMessage().online); }
