cmake_minimum_required(VERSION 3.12)

add_executable(universelan-dllhost-${GALAXY_VERSION} WIN32 DllHost.cxx )

target_include_directories(universelan-dllhost-${GALAXY_VERSION} PUBLIC ".")

target_compile_definitions(universelan-dllhost-${GALAXY_VERSION} PUBLIC "HOST_DLL")

target_link_libraries(universelan-dllhost-${GALAXY_VERSION} PUBLIC universelan-client-${GALAXY_VERSION} )

set_target_properties(universelan-dllhost-${GALAXY_VERSION} PROPERTIES OUTPUT_NAME "UniverseLANDllHost-${GALAXY_VERSION}")

set_property(TARGET universelan-dllhost-${GALAXY_VERSION} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Debug/")
