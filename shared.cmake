cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE COMMON_SHARED_SRC CONFIGURE_DEPENDS "Common/Common.Shared/*.*")

add_library(lsfdrmfg-common-shared STATIC ${COMMON_SHARED_SRC} )

target_include_directories(lsfdrmfg-common-shared PUBLIC "Common/Common.Shared/")

target_link_libraries(
    lsfdrmfg-common-shared
    PUBLIC
      lsfdrmfg-cereal
      lsfdrmfg-enet
      lsfdrmfg-galaxy
      lsfdrmfg-simpleini
      lsfdrmfg-common-version
)
