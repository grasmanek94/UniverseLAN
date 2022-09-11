cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE ENET_SRC CONFIGURE_DEPENDS "Vendor/ENet/Source/*.*")

add_library(lsfdrmfg-enet STATIC ${ENET_SRC} )

target_compile_definitions(lsfdrmfg-enet PRIVATE "_WINSOCK_DEPRECATED_NO_WARNINGS" )
target_include_directories(lsfdrmfg-enet PUBLIC "Vendor/ENet/Source/include/")

target_link_libraries(
    lsfdrmfg-enet
    PRIVATE
        $<$<PLATFORM_ID:Windows>:Winmm>
        $<$<PLATFORM_ID:Windows>:ws2_32>
)
