#include <GalaxyID.hxx>

#include <gtest/gtest.h>

namespace {

TEST(GalaxyID, PreservesTypeAndMasksRealIdentifierToSupportedWidth)
{
    constexpr uint64_t value = 0xff123456789abcdeULL;
    #if GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
    constexpr auto user_type = galaxy::api::GalaxyID::ID_TYPE_USER;
    #else
    constexpr auto user_type = galaxy::api::ID_TYPE_USER;
    #endif
    const auto id = galaxy::api::FromRealID(user_type, value);

    EXPECT_EQ(galaxy::api::GetIDType(id), user_type);
    EXPECT_EQ(galaxy::api::GetRealID(id), 0x123456789abcdeULL);
}

TEST(GalaxyID, HashesByFullUnderlyingIdentifier)
{
    #if GALAXY_BUILD_FEATURE_GALAXYID_HAS_IDTYPE
    constexpr auto user_type = galaxy::api::GalaxyID::ID_TYPE_USER;
    constexpr auto lobby_type = galaxy::api::GalaxyID::ID_TYPE_LOBBY;
    #else
    constexpr auto user_type = galaxy::api::ID_TYPE_USER;
    constexpr auto lobby_type = galaxy::api::ID_TYPE_LOBBY;
    #endif
    const auto first = galaxy::api::FromRealID(user_type, 1);
    const auto second = galaxy::api::FromRealID(lobby_type, 1);

    EXPECT_NE(universelan::GalaxyIDHash{}(first), universelan::GalaxyIDHash{}(second));
}

} // namespace
