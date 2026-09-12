#include <Impl/DelayRunner.hxx>

#include <gtest/gtest.h>

#include <vector>

namespace {

TEST(DelayRunner, DoesNothingWhenNoCallbacksAreQueued)
{
    universelan::client::DelayRunner runner;

    runner.Run();
}

TEST(DelayRunner, RunsCallbacksInFirstInFirstOutOrder)
{
    universelan::client::DelayRunner runner;
    std::vector<int> calls;

    runner.Add([&calls] { calls.push_back(1); });
    runner.Add([&calls] { calls.push_back(2); });
    runner.Run();

    EXPECT_EQ(calls, (std::vector<int>{ 1, 2 }));
}

TEST(DelayRunner, DrainsCallbacksAddedDuringExecution)
{
    universelan::client::DelayRunner runner;
    std::vector<int> calls;

    runner.Add([&] {
        calls.push_back(1);
        runner.Add([&calls] { calls.push_back(2); });
    });
    runner.Run();

    EXPECT_EQ(calls, (std::vector<int>{ 1, 2 }));
}

} // namespace
