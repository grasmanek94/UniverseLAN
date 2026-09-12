#include <AchievementData.hxx>

#include <gtest/gtest.h>

namespace {

TEST(AchievementData, HasDocumentedDefaultValues)
{
    const universelan::AchievementData achievement;

    EXPECT_FALSE(achievement.IsDirty());
    EXPECT_TRUE(achievement.GetName().empty());
    EXPECT_TRUE(achievement.GetDescription().empty());
    EXPECT_FALSE(achievement.GetUnlocked());
    EXPECT_EQ(achievement.GetUnlockTime(), 0U);
    EXPECT_TRUE(achievement.GetVisible());
    EXPECT_TRUE(achievement.GetVisibleWhileLocked());
}

TEST(AchievementData, SettersUpdateStateAndMarkDataDirty)
{
    universelan::AchievementData achievement;

    achievement.SetName("name");
    achievement.SetDescription("description");
    achievement.SetUnlocked(true);
    achievement.SetUnlockTime(123);
    achievement.SetVisible(false);
    achievement.SetVisibleWhileLocked(false);

    EXPECT_TRUE(achievement.IsDirty());
    EXPECT_EQ(achievement.GetName(), "name");
    EXPECT_EQ(achievement.GetDescription(), "description");
    EXPECT_TRUE(achievement.GetUnlocked());
    EXPECT_EQ(achievement.GetUnlockTime(), 123U);
    EXPECT_FALSE(achievement.GetVisible());
    EXPECT_FALSE(achievement.GetVisibleWhileLocked());
}

TEST(AchievementData, ResetDirtyPreservesAchievementState)
{
    universelan::AchievementData achievement;
    achievement.SetName("name");
    achievement.SetUnlocked(true);

    achievement.ResetDirty();

    EXPECT_FALSE(achievement.IsDirty());
    EXPECT_EQ(achievement.GetName(), "name");
    EXPECT_TRUE(achievement.GetUnlocked());
}

} // namespace
