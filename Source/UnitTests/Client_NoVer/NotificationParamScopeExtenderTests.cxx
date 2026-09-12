#include <Impl/NotificationParamScopeExtender.hxx>

#include <gtest/gtest.h>

#include <string>

namespace {

TEST(NotificationParamScopeExtender, RepresentsNullAndStringInputs)
{
    const universelan::client::NotificationParamScopeExtender empty;
    const universelan::client::NotificationParamScopeExtender nullValue(nullptr);
    const universelan::client::NotificationParamScopeExtender value("text");

    EXPECT_EQ(static_cast<const char*>(empty), nullptr);
    EXPECT_EQ(static_cast<const char*>(nullValue), nullptr);
    ASSERT_NE(static_cast<const char*>(value), nullptr);
    EXPECT_STREQ(static_cast<const char*>(value), "text");
}

TEST(NotificationParamScopeExtender, OwnsCopiedStringDataAcrossSourceLifetime)
{
    universelan::client::NotificationParamScopeExtender value;
    {
        const std::string source = "temporary";
        value = universelan::client::NotificationParamScopeExtender(source);
    }

    ASSERT_NE(static_cast<const char*>(value), nullptr);
    EXPECT_STREQ(static_cast<const char*>(value), "temporary");
}

TEST(NotificationParamScopeExtender, SupportsCopyMoveAndIdentityHelpers)
{
    universelan::client::NotificationParamScopeExtender original("value");
    const universelan::client::NotificationParamScopeExtender copy(original);
    universelan::client::NotificationParamScopeExtender moved(std::move(original));
    const char* const literal = "literal";

    EXPECT_STREQ(static_cast<const char*>(copy), "value");
    EXPECT_STREQ(static_cast<const char*>(moved), "value");
    EXPECT_STREQ(universelan::client::notification_param_push_identity(copy), "value");
    EXPECT_EQ(universelan::client::notification_param_push_identity(literal), literal);
    EXPECT_STREQ(universelan::client::notification_param_extend_life(literal), "literal");
}

} // namespace
