cmake_minimum_required(VERSION 3.12)

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_library(lsfdrmfg-client-${PARENT_DIR} SHARED Factory.cxx GalaxyFactory.h UniverseLAN.def)
add_executable(lsfdrmfg-dllhost-${PARENT_DIR} WIN32 FactoryHost.cxx )

target_include_directories(lsfdrmfg-client-${PARENT_DIR} PUBLIC ".")
target_include_directories(lsfdrmfg-dllhost-${PARENT_DIR} PUBLIC ".")

target_compile_definitions(lsfdrmfg-client-${PARENT_DIR} PUBLIC "CLIENT_FACTORY")
target_compile_definitions(lsfdrmfg-dllhost-${PARENT_DIR} PUBLIC "HOST_FACTORY")

target_link_libraries(lsfdrmfg-client-${PARENT_DIR} PUBLIC lsfdrmfg-universelan-lib)
target_link_libraries(lsfdrmfg-dllhost-${PARENT_DIR} PUBLIC lsfdrmfg-client-${PARENT_DIR} )

##################################################################################

set_target_properties(lsfdrmfg-client-${PARENT_DIR} PROPERTIES OUTPUT_NAME "Galaxy-${PARENT_DIR}")
set_target_properties(lsfdrmfg-dllhost-${PARENT_DIR} PROPERTIES OUTPUT_NAME "UniverseLANDllHost-${PARENT_DIR}")

set_property(TARGET lsfdrmfg-dllhost-${PARENT_DIR} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Debug/")
