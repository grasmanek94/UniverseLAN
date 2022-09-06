add_library(GalaxySDK STATIC dummy.cpp)
target_include_directories(GalaxySDK PUBLIC "Include")

if (CMAKE_CL_64)
    target_link_directories(GalaxySDK PUBLIC "Libraries")
    add_custom_command(TARGET GalaxySDK POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Galaxy64.dll" "${CMAKE_BINARY_DIR}/bin"
            )
    target_link_libraries(GalaxySDK PUBLIC Galaxy64)
endif ()
