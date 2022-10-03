cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE CEREAL_SRC CONFIGURE_DEPENDS "cereal-1.1.2/include/*.*")

add_library(lsfdrmfg-cereal STATIC ${CEREAL_SRC})
target_sources(lsfdrmfg-cereal PRIVATE dummy.c)

target_include_directories(lsfdrmfg-cereal PUBLIC "cereal-1.1.2/include/")
