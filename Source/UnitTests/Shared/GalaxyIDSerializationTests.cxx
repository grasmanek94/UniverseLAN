#include <GalaxyIDSerialization.hxx>

#include <gtest/gtest.h>

namespace {

struct Archive {};

TEST(GalaxyIDSerialization, SavesAndLoadsTheExactUnderlyingIdentifier)
{
    const galaxy::api::GalaxyID source(0x123456789abcdef0ULL);
    galaxy::api::GalaxyID destination;

    const uint64_t saved = galaxy::api::save_minimal(Archive{}, source);
    galaxy::api::load_minimal(Archive{}, destination, saved);

    EXPECT_EQ(saved, source.ToUint64());
    EXPECT_EQ(destination.ToUint64(), source.ToUint64());
}

} // namespace
