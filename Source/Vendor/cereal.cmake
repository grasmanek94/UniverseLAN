cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE CEREAL_SRC CONFIGURE_DEPENDS "cereal-1.3.2/include/*.*")

add_library(universelan-cereal STATIC ${CEREAL_SRC})
target_sources(universelan-cereal PRIVATE dummy.c)

target_include_directories(universelan-cereal PUBLIC "cereal-1.3.2/include/")
