cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE CEREAL_SRC CONFIGURE_DEPENDS "cereal-1.1.2/include/*.*")

add_library(lsfdrmfg-cereal INTERFACE ${CEREAL_SRC} )

target_include_directories(lsfdrmfg-cereal INTERFACE "cereal-1.1.2/include/")
