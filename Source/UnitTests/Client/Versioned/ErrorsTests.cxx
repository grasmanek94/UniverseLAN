#include <Impl/Errors.hxx>

#include <gtest/gtest.h>

namespace {

TEST(Errors, ExposesGenericErrorDetails)
{
	universelan::client::Error error;

	EXPECT_STREQ(error.GetName(), "Generic Unknown Error");
	EXPECT_STREQ(error.GetMsg(), "Generic Unknown Error");
	EXPECT_EQ(error.GetType(), galaxy::api::IError::RUNTIME_ERROR);
}

TEST(Errors, ExposesSpecificErrorTypes)
{
	universelan::client::UnauthorizedAccessError unauthorized;
	universelan::client::InvalidArgumentError invalid_argument;
	universelan::client::InvalidStateError invalid_state;
	universelan::client::RuntimeError runtime;

	EXPECT_EQ(unauthorized.GetType(), galaxy::api::IError::UNAUTHORIZED_ACCESS);
	EXPECT_EQ(invalid_argument.GetType(), galaxy::api::IError::INVALID_ARGUMENT);
	EXPECT_EQ(invalid_state.GetType(), galaxy::api::IError::INVALID_STATE);
	EXPECT_EQ(runtime.GetType(), galaxy::api::IError::RUNTIME_ERROR);
}

} // namespace
