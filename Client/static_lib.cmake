cmake_minimum_required(VERSION 3.12)

add_library(lsfdrmfg-client-lib STATIC ${CLIENT_SRC} )

target_include_directories(lsfdrmfg-client-lib PUBLIC ".")
target_compile_definitions(lsfdrmfg-client-lib PUBLIC "CLIENT" )

target_link_libraries(
    lsfdrmfg-client-lib
    PRIVATE lsfdrmfg-common-shared websocketpp boost
)
