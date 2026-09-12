#include <AchievementsAndStatsContainer.hxx>

#include <gtest/gtest.h>

namespace {

TEST(AchievementsAndStatsContainer, CreatesAndReturnsStableAchievementData)
{
    universelan::AchievementsAndStatsContainer container;

    universelan::AchievementData* const created = container.GetAchievementData("achievement");
    ASSERT_NE(created, nullptr);
    EXPECT_EQ(created->GetName(), "achievement");
    EXPECT_TRUE(created->IsDirty());

    created->ResetDirty();
    EXPECT_EQ(container.GetAchievementData("achievement"), created);
    EXPECT_FALSE(container.GetAchievementData("achievement")->IsDirty());
}

TEST(AchievementsAndStatsContainer, StoresIntegerAndFloatingPointStats)
{
    universelan::AchievementsAndStatsContainer container;

    EXPECT_EQ(container.GetStat("missing").i, 0);
    container.SetStat("score", 42);
    EXPECT_EQ(container.GetStat("score").i, 42);
    container.SetStat("ratio", 1.5F);
    EXPECT_FLOAT_EQ(container.GetStat("ratio").f, 1.5F);
}

TEST(AchievementsAndStatsContainer, CreatesUpdatesAndCopiesUserDataAndRichPresence)
{
    universelan::AchievementsAndStatsContainer container;

    EXPECT_FALSE(container.IsUserDataAvailable());
    EXPECT_TRUE(container.GetUserData("missing").empty());
    EXPECT_TRUE(container.IsUserDataAvailable());
    container.SetUserData("key", "value");
    EXPECT_EQ(container.GetUserData("key"), "value");

    container.SetRichPresence("status", "online");
    EXPECT_EQ(container.GetRichPresence("status"), "online");
    container.EraseRichPresence("status");
    EXPECT_TRUE(container.GetRichPresence("status").empty());
    container.SetRichPresence("one", "1");
    container.SetRichPresence("two", "2");
    container.ClearRichPresence();
    EXPECT_TRUE(container.GetRichPresence("one").empty());

    universelan::AchievementsAndStatsContainer copy(container);
    EXPECT_EQ(copy.GetUserData("key"), "value");
}

TEST(AchievementsAndStatsContainer, PreservesConfiguredPlayTime)
{
    universelan::AchievementsAndStatsContainer container;
    container.SetPlayTime(123);

    EXPECT_GE(container.GetPlayTime(), 123U);
}

} // namespace
