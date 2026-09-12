#include <ConsoleCoutRedirector.hxx>

#include <gtest/gtest.h>

#include <sstream>

namespace {

TEST(ConsoleCoutRedirector, TeeBufferWritesToBothDestinations)
{
    std::stringbuf first;
    std::stringbuf second;
    universelan::console::teebuf buffer(&first, &second);
    std::ostream stream(&buffer);

    stream << "message" << std::flush;

    EXPECT_EQ(first.str(), "message");
    EXPECT_EQ(second.str(), "message");
}

} // namespace
