#include <EnvUtils.hxx>

#include <gtest/gtest.h>

#include <cstdlib>

namespace {

TEST(EnvUtils, ReturnsEmptyForMissingVariablesAndReadsConfiguredValues)
{
    constexpr const char* name = "UNIVERSELAN_UNIT_TEST_VALUE";
#ifdef _WIN32
    _putenv_s(name, "value");
#else
    setenv(name, "value", 1);
#endif
    EXPECT_EQ(universelan::env_utils::get_env(name), "value");
#ifdef _WIN32
    _putenv_s(name, "");
#else
    unsetenv(name);
#endif
    EXPECT_TRUE(universelan::env_utils::get_env(name).empty());
    EXPECT_TRUE(universelan::env_utils::get_env("UNIVERSELAN_UNIT_TEST_MISSING").empty());
}

TEST(EnvUtils, ReadsTheGameDataPrefix)
{
#ifdef _WIN32
    _putenv_s("UNIVERSELAN_GAMEDATA_PREFIX", "test-prefix");
#else
    setenv("UNIVERSELAN_GAMEDATA_PREFIX", "test-prefix", 1);
#endif
    EXPECT_EQ(universelan::env_utils::get_gamedata_path_prefix(), "test-prefix");
#ifdef _WIN32
    _putenv_s("UNIVERSELAN_GAMEDATA_PREFIX", "");
#else
    unsetenv("UNIVERSELAN_GAMEDATA_PREFIX");
#endif
}

} // namespace
