#include <ConcurrentQueue.hxx>

#include <gtest/gtest.h>

#include <string>

namespace {

TEST(ConcurrentQueue, EmptyQueueDoesNotProduceValues)
{
    Concurrency::concurrent_queue<int> queue;
    int value = 0;

    EXPECT_TRUE(queue.empty());
    EXPECT_FALSE(queue.try_pop(value));
    EXPECT_TRUE(queue.empty());
}

TEST(ConcurrentQueue, PushPreservesFirstInFirstOutOrder)
{
    Concurrency::concurrent_queue<std::string> queue;
    std::string first = "first";
    std::string value;

    queue.push(first);
    queue.push(std::string("second"));

    ASSERT_TRUE(queue.try_pop(value));
    EXPECT_EQ(value, "first");
    ASSERT_TRUE(queue.try_pop(value));
    EXPECT_EQ(value, "second");
    EXPECT_TRUE(queue.empty());
}

} // namespace
