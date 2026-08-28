cmake_minimum_required(VERSION 3.13)

file(GLOB_RECURSE COMMON_SHARED_SRC_NO_VER CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Source/Shared_NoVer/*.*")

add_library(universelan-common-shared-no-ver STATIC ${COMMON_SHARED_SRC_NO_VER} )

target_include_directories(universelan-common-shared-no-ver PUBLIC "${CMAKE_SOURCE_DIR}/Source/Shared_NoVer/")

# Target Win 7
target_compile_definitions(universelan-common-shared-no-ver PRIVATE
  $<$<PLATFORM_ID:Windows>:_WIN32_WINNT=0x0601>
  $<$<PLATFORM_ID:Windows>:WINVER=0x0601>
)

target_link_libraries(
  universelan-common-shared-no-ver
  PUBLIC
    universelan-magic_enum
    universelan-cereal
    universelan-enet
    universelan-simpleini
    universelan-common-version
    universelan-common-tracer
    json
    $<$<PLATFORM_ID:Linux>:tbb>
  PRIVATE
    $<$<PLATFORM_ID:Windows>:iphlpapi>
    $<$<PLATFORM_ID:Windows>:shell32>
    $<$<PLATFORM_ID:Windows>:ole32>
)
