#include <Impl/InitOptionsModern.hxx>

#include <gtest/gtest.h>

namespace {

TEST(InitOptionsModern, DefaultConstructionUsesEmptyAndDisabledValues)
{
	universelan::client::InitOptionsModern options;

	EXPECT_TRUE(options.clientID.empty());
	EXPECT_TRUE(options.clientSecret.empty());
	EXPECT_TRUE(options.configFilePath.empty());
	EXPECT_TRUE(options.storagePath.empty());
	EXPECT_FALSE(options.throwExceptions);
#if GALAXY_BUILD_FEATURE_ALLOCATOR
	EXPECT_EQ(options.galaxyAllocator, nullptr);
#endif
#if GALAXY_BUILD_FEATURE_HAS_IGALAXYTHREADFACTORY
	EXPECT_EQ(options.galaxyThreadFactory, nullptr);
#endif
#if GALAXY_BUILD_FEATURE_HAS_INITOPTIONS_HOST_PORT
	EXPECT_TRUE(options.host.empty());
	EXPECT_EQ(options.port, 0U);
#endif
}

} // namespace
