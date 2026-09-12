#include <SafeStringCopy.hxx>

#include <gtest/gtest.h>

#include <array>
#include <string>

namespace {

TEST(SafeStringCopy, CopiesStringsAndAlwaysNullTerminates)
{
    std::array<char, 4> buffer{};

    EXPECT_EQ(universelan::util::safe_copy_str_n("hello", buffer.data(), buffer.size()), 4U);
    EXPECT_STREQ(buffer.data(), "hel");
    EXPECT_EQ(universelan::util::safe_copy_str_n(std::string(""), buffer.data(), buffer.size()), 1U);
    EXPECT_STREQ(buffer.data(), "");
}

TEST(SafeStringCopy, RejectsInvalidStringDestinationsAndSources)
{
    std::array<char, 4> buffer{};

    EXPECT_EQ(universelan::util::safe_copy_str_n("value", nullptr, buffer.size()), 0U);
    EXPECT_EQ(universelan::util::safe_copy_str_n("value", buffer.data(), 0), 0U);
    EXPECT_EQ(universelan::util::safe_copy_str_n(static_cast<const char*>(nullptr), buffer.data(), buffer.size()), 0U);
}

TEST(SafeStringCopy, CopiesBinaryDataWithoutWritingATerminator)
{
    const std::string value("a\0b", 3);
    std::array<char, 2> buffer{ 'x', 'y' };

    EXPECT_EQ(universelan::util::safe_copy_binary_n(value, buffer.data(), buffer.size()), 2U);
    EXPECT_EQ(buffer[0], 'a');
    EXPECT_EQ(buffer[1], '\0');
    EXPECT_EQ(universelan::util::safe_copy_binary_n(value.data(), value.size(), nullptr, buffer.size()), 0U);
}

TEST(SafeStringCopy, NormalizesAndAnnotatesNullPointers)
{
    const char* value = nullptr;

    EXPECT_STREQ(universelan::util::safe_fix_null_char_ptr(value), "");
    EXPECT_STREQ(value, "");
    EXPECT_STREQ(universelan::util::safe_fix_null_char_ptr_ret(nullptr), "");
    EXPECT_STREQ(universelan::util::safe_fix_null_char_ptr_annotate_ret(nullptr), "!!(nullptr)");
    EXPECT_EQ(universelan::util::safe_fix_null_char_ptr_annotate(nullptr, 3), "!!(nullptr)");
}

TEST(SafeStringCopy, BoundsLengthsAndConvertsBytesToLowercaseHex)
{
    constexpr std::array<char, 4> terminated{ 'a', 'b', '\0', 'c' };
    constexpr std::array<char, 3> unterminated{ 'a', 'b', 'c' };
    constexpr std::array<unsigned char, 3> bytes{ 0, 10, 255 };

    EXPECT_EQ(universelan::util::bounded_strlen(nullptr, 3), 0U);
    EXPECT_EQ(universelan::util::bounded_strlen(terminated.data(), 0), 0U);
    EXPECT_EQ(universelan::util::bounded_strlen(terminated.data(), terminated.size()), 2U);
    EXPECT_EQ(universelan::util::bounded_strlen(unterminated.data(), unterminated.size()), unterminated.size());
    EXPECT_EQ(universelan::util::safe_fix_null_char_ptr_annotate(unterminated.data(), unterminated.size()), "abc");
    EXPECT_EQ(universelan::util::bytes_to_hex(bytes.data(), bytes.size()), "000aff");
    EXPECT_EQ(universelan::util::bytes_to_hex(nullptr, bytes.size()), "");
}

} // namespace
