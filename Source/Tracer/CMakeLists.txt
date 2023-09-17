cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE COMMON_TRACER_SRC CONFIGURE_DEPENDS "*.*")

add_library(universelan-common-tracer STATIC ${COMMON_TRACER_SRC} )
#add_executable(universelan-common-tracer ${COMMON_TRACER_SRC} )
target_include_directories(universelan-common-tracer PUBLIC ".")

target_link_libraries(
    universelan-common-tracer
    PUBLIC
      boost
      detours
      $<$<PLATFORM_ID:Windows>:StackWalker>
    PRIVATE
      $<$<PLATFORM_ID:Windows>:Imagehlp>
)
