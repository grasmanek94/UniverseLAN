cmake_minimum_required(VERSION 3.12)

if (MSVC)
  if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")

    add_library(detours STATIC 
      creatwth.cpp
      detours.cpp
      detours.h
      detver.h
      disasm.hpp
      image.cpp
      modules.cpp
    )

    target_include_directories(detours PUBLIC ".")
    target_compile_definitions(detours 
      PUBLIC 
        "WIN32_LEAN_AND_MEAN"
        "_WIN32_WINNT=0x501"
    )

  elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")

    add_library(detours STATIC 
      creatwth.cpp
      detours.cpp
      detours.h
      detver.h
      disasm.hpp
      image.cpp
      modules.cpp
    )

    target_include_directories(detours PUBLIC ".")
    target_compile_definitions(detours 
      PUBLIC 
        "DETOURS_X86_OFFLINE_LIBRARY"
        "DETOURS_X86"
        "WIN32_LEAN_AND_MEAN"
        "_WIN32_WINNT=0x501"
    )
    
  else()
    # no
  endif()
elseif()
  # no
endif()

