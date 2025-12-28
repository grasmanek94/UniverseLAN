cmake_minimum_required(VERSION 3.13)

file(GLOB_RECURSE JSON_SRC CONFIGURE_DEPENDS "nlohmann-json/include/*.*")

add_library(json STATIC ${JSON_SRC})
target_sources(json PRIVATE dummy.c)

target_include_directories(json PUBLIC "nlohmann-json/include")
