cmake_minimum_required(VERSION 3.12)

if (MSVC)
  if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")

    add_subdirectory(x86-201706261340)

  elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")

    add_subdirectory(x64-1.121.2.0)
    add_subdirectory(x64-1.148.3.0)

  endif()
endif()
