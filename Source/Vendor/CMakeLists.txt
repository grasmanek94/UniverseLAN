cmake_minimum_required(VERSION 3.12)

add_subdirectory(Enet-IPv6)
add_subdirectory(Enet++)
add_subdirectory(boost)
add_subdirectory(Detours)

if(WIN32)
add_subdirectory(StackWalker)
endif()

include(simpleini.cmake)
include(miniz-cpp.cmake)
include(magic_enum.cmake)

include(cereal.cmake)
include(ixwebsocket.cmake)

include(galaxy.cmake)
include(unet.cmake)
include(json.cmake)

if(EXPERIMENTAL_FAST_BUILD)
    function(get_targets_recursive dir out_var)
        get_property(targets DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)

        get_property(subdirs DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)

        foreach(subdir ${subdirs})
            get_targets_recursive(${subdir} sub_targets)
            list(APPEND targets ${sub_targets})
        endforeach()

        set(${out_var} "${targets}" PARENT_SCOPE)
    endfunction()

    get_targets_recursive(${CMAKE_CURRENT_SOURCE_DIR} VENDOR_TARGETS)

    foreach(t ${VENDOR_TARGETS})
        set_target_properties(${t} PROPERTIES
            UNITY_BUILD OFF
        )
    endforeach()
endif()
