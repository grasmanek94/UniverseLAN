cmake_minimum_required(VERSION 3.12)

add_executable(lsfdrmfg-dllhost-${GALAXY_VERSION} WIN32 DllHost.cxx )

target_include_directories(lsfdrmfg-dllhost-${GALAXY_VERSION} PUBLIC ".")

target_compile_definitions(lsfdrmfg-dllhost-${GALAXY_VERSION} PUBLIC "HOST_DLL")

target_link_libraries(lsfdrmfg-dllhost-${GALAXY_VERSION} PUBLIC lsfdrmfg-client-${GALAXY_VERSION} )

set_target_properties(lsfdrmfg-dllhost-${GALAXY_VERSION} PROPERTIES OUTPUT_NAME "UniverseLANDllHost-${GALAXY_VERSION}")

set_property(TARGET lsfdrmfg-dllhost-${GALAXY_VERSION} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Debug/")
