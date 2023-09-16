cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE ENET_SRC CONFIGURE_DEPENDS "Source/*.*")

add_library(universelan-enet STATIC ${ENET_SRC} )

target_compile_definitions(universelan-enet PRIVATE "_WINSOCK_DEPRECATED_NO_WARNINGS")
target_compile_definitions(universelan-enet PUBLIC "WIN32_LEAN_AND_MEAN" "NOMINMAX")
target_include_directories(universelan-enet PUBLIC "Source/include/")

target_link_libraries(
    universelan-enet
    PRIVATE
        $<$<PLATFORM_ID:Windows>:Winmm>
        $<$<PLATFORM_ID:Windows>:Ws2_32>
)
