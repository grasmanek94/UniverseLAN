#include <MemoryInputStream.hxx>

#include <gtest/gtest.h>

#include <array>
#include <string>

namespace {

TEST(MemoryInputStream, ReadsTextFromVoidPointerAndSize)
{
    constexpr std::array<char, 5> contents{ 'h', 'e', 'l', 'l', 'o' };
    universelan::MemoryInputStream input(contents.data(), contents.size());
    std::string result;

    input.stream() >> result;

    EXPECT_EQ(result, "hello");
}

TEST(MemoryInputStream, PreservesEmbeddedNullBytesFromSpanInput)
{
    constexpr std::array<std::byte, 3> contents{ std::byte{ 'a' }, std::byte{ 0 }, std::byte{ 'b' } };
    universelan::MemoryInputStream input(contents);
    std::array<char, 3> result{};

    input.stream().read(result.data(), static_cast<std::streamsize>(result.size()));

    EXPECT_EQ(result[0], 'a');
    EXPECT_EQ(result[1], '\0');
    EXPECT_EQ(result[2], 'b');
    EXPECT_EQ(input.stream().peek(), std::char_traits<char>::eof());
    EXPECT_TRUE(input.stream().eof());
}

TEST(MemoryInputStream, ReportsEndOfFileForEmptyInput)
{
    constexpr std::array<std::byte, 1> storage{ std::byte{ 0 } };
    universelan::MemoryInputStream input(std::span<const std::byte>(storage.data(), 0));

    EXPECT_EQ(input.stream().peek(), std::char_traits<char>::eof());
    EXPECT_TRUE(input.stream().eof());
}

} // namespace
