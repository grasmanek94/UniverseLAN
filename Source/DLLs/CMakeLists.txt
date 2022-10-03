cmake_minimum_required(VERSION 3.12)

if (MSVC)
  if("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "X86")

    add_subdirectory(x86-1.100.2.0) # Metal Slug 3
    add_subdirectory(x86-1.124.0.0) # RPSGame
    add_subdirectory(x86-0.176.2.6) # AvP2000

  elseif("${MSVC_C_ARCHITECTURE_ID}" STREQUAL "x64")

    add_subdirectory(x64-1.121.2.0) # Aragami 2
    add_subdirectory(x64-1.124.0.0) # RPSGame
    add_subdirectory(x64-1.148.3.0) # RoboQuest
  endif()
endif()
