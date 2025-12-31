cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE ENET_SRC CONFIGURE_DEPENDS "src/*.*")

add_library(enet-ipv6 STATIC ${ENET_SRC} )

target_compile_definitions(enet-ipv6 PRIVATE "_WINSOCK_DEPRECATED_NO_WARNINGS" "_CRT_SECURE_NO_WARNINGS")
target_compile_definitions(enet-ipv6 PUBLIC "WIN32_LEAN_AND_MEAN" "NOMINMAX")
target_include_directories(enet-ipv6 PUBLIC "include/")

target_link_libraries(
    enet-ipv6
    PRIVATE
        $<$<PLATFORM_ID:Windows>:Winmm>
        $<$<PLATFORM_ID:Windows>:Ws2_32>
)
