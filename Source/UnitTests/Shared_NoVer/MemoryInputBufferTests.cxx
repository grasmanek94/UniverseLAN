#include <MemoryInputBuffer.hxx>

#include <gtest/gtest.h>

#include <array>
#include <istream>

namespace {

TEST(MemoryInputBuffer, ReadsAllProvidedBytesInOrder)
{
    constexpr std::array<std::byte, 3> contents{ std::byte{ 'a' }, std::byte{ 'b' }, std::byte{ 'c' } };
    universelan::MemoryInputBuffer buffer(contents);
    std::istream stream(&buffer);
    std::array<char, 3> read{};

    stream.read(read.data(), static_cast<std::streamsize>(read.size()));

    EXPECT_EQ(read[0], 'a');
    EXPECT_EQ(read[1], 'b');
    EXPECT_EQ(read[2], 'c');
    EXPECT_EQ(stream.peek(), std::char_traits<char>::eof());
    EXPECT_TRUE(stream.eof());
}

TEST(MemoryInputBuffer, IsImmediatelyAtEndForAnEmptySpan)
{
    constexpr std::array<std::byte, 1> storage{ std::byte{ 0 } };
    universelan::MemoryInputBuffer buffer(std::span<const std::byte>(storage.data(), 0));
    std::istream stream(&buffer);

    EXPECT_EQ(stream.peek(), std::char_traits<char>::eof());
    EXPECT_TRUE(stream.eof());
}

} // namespace
