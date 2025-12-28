cmake_minimum_required(VERSION 3.13)

set(websocketpp_DIR ${CMAKE_CURRENT_SOURCE_DIR}/websocketpp-0.8.2/cmake/ )

find_package(websocketpp REQUIRED)

file(GLOB_RECURSE WEBSOCKETPP_SRC CONFIGURE_DEPENDS "websocketpp-0.8.2/include/*.*")

add_library(websocketpp STATIC ${WEBSOCKETPP_SRC})
target_sources(websocketpp PRIVATE dummy.c)

target_link_libraries(websocketpp PUBLIC websocketpp::websocketpp)

target_include_directories(websocketpp PUBLIC "websocketpp-0.8.2/include")
