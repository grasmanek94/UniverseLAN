cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE COMMON_TRACER_SRC CONFIGURE_DEPENDS "*.*")

add_library(lsfdrmfg-common-tracer STATIC ${COMMON_TRACER_SRC} )
#add_executable(lsfdrmfg-common-tracer ${COMMON_TRACER_SRC} )
target_include_directories(lsfdrmfg-common-tracer PUBLIC ".")

target_link_libraries(
    lsfdrmfg-common-tracer
    PUBLIC
      boost
      detours
      StackWalker
    PRIVATE
      $<$<PLATFORM_ID:Windows>:Imagehlp>
)
