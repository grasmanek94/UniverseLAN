#include <GalaxyUserData.hxx>

#include <gtest/gtest.h>

namespace {

TEST(GalaxyUserData, PreservesIdentityAndInitializesOfflineWithEmptyProfileState)
{
    const galaxy::api::GalaxyID id(0x123456789abcdef0ULL);
    universelan::GalaxyUserData user(id);

    EXPECT_EQ(user.id.ToUint64(), id.ToUint64());
	EXPECT_FALSE(user.online);
	EXPECT_FALSE(user.friend_information_retrieved);
	EXPECT_TRUE(user.nickname.empty());
    EXPECT_EQ(user.stats.GetPlayTime(), 0U);
}

TEST(GalaxyUserData, SupportsHashedLookupByGalaxyIdentifier)
{
    const galaxy::api::GalaxyID id(0x123456789abcdef0ULL);
    universelan::GalaxyUserData::map_t users;
    auto user = std::make_shared<universelan::GalaxyUserData>(id);

    users.emplace(id, user);

    ASSERT_EQ(users.count(id), 1U);
    EXPECT_EQ(users.at(id), user);
}

} // namespace
