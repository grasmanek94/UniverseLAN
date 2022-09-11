cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE CEREAL_SRC CONFIGURE_DEPENDS "cereal-1.1.2/include/*.*")

target_sources(lsfdrmfg-all-headers PUBLIC ${CEREAL_SRC})

target_include_directories(lsfdrmfg-all-headers INTERFACE "cereal-1.1.2/include/")
