cmake_minimum_required(VERSION 3.12)

add_library(lsfdrmfg-client-${GALAXY_VERSION} SHARED Factory.cxx UniverseLAN.def)

target_include_directories(lsfdrmfg-client-${GALAXY_VERSION} PUBLIC ".")

target_compile_definitions(lsfdrmfg-client-${GALAXY_VERSION} PUBLIC "CLIENT_FACTORY")

target_link_libraries(lsfdrmfg-client-${GALAXY_VERSION} PUBLIC lsfdrmfg-universelan-lib-${GALAXY_VERSION})

set_target_properties(lsfdrmfg-client-${GALAXY_VERSION} PROPERTIES OUTPUT_NAME "Galaxy-${GALAXY_VERSION}")