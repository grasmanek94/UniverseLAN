cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE ENET_SRC CONFIGURE_DEPENDS "src/*.*")

add_library(universelan-enet STATIC ${ENET_SRC} )

target_compile_definitions(universelan-enet PRIVATE "_WINSOCK_DEPRECATED_NO_WARNINGS" "_CRT_SECURE_NO_WARNINGS")
target_include_directories(universelan-enet PUBLIC "include/")

target_link_libraries(
    universelan-enet
    PUBLIC
      enet-ipv6
    PRIVATE
        $<$<PLATFORM_ID:Windows>:winmm>
        $<$<PLATFORM_ID:Windows>:ws2_32>
)
